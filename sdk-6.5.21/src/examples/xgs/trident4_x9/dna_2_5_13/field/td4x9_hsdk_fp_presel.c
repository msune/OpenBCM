/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

/*  Feature  : FP Presel demonstration. How to attach a presel to an FP entry.
 *
 *  Usage : BCM.0> cint td4x9_hsdk_fp_presel.c YES [WithPresel=0/1] [Stage=1/2/3]
 *           E.g.  cint td4x9_hsdk_fp_presel.c YES 0 1      <<<<< WithoutPresel   Stage: VFP
 *           E.g.  cint td4x9_hsdk_fp_presel.c YES 1 1      <<<<< WithPresel      Stage: VFP
 *           E.g.  cint td4x9_hsdk_fp_presel.c YES 0 2      <<<<< WithoutPresel   Stage: IFP
 *           E.g.  cint td4x9_hsdk_fp_presel.c YES 1 2      <<<<< WithPresel      Stage: IFP
 *           E.g.  cint td4x9_hsdk_fp_presel.c YES 0 3      <<<<< WithoutPresel   Stage: EFP
 *           E.g.  cint td4x9_hsdk_fp_presel.c YES 1 3      <<<<< WithPresel      Stage: EFP
 *
 *  config   : BCM956780-56780_A0-fp-config.yml
 *
 *  Log file : td4x9_hsdk_fp_presel_log.txt
 *
 *  Test Topology :
 *
 *                   +------------------------------+
 *                   |                              +-----------------+
 *                   |                              |
 *                   |                              |
 *                   |                              |
 *  +----------------+          SWITCH              +-----------------+
 *                   |                              |
 *                   |                              |
 *  +----------------+                              |
 *                   |                              |
 *                   |                              |
 *                   +------------------------------+
 *
 *  Summary:
 *  ========
 *      This CINT create a presel entry/group with a qualifier suitable for the stage (VFP or IFP
 *      or EFP). It also creates main TCAM group with presel. Entry in the main TCAM group also
 *      has qualifiers auitable for that stage. A STAT is also attached to the entry to verify.
 *      Whether to create a presel or not is controlled by the command line option.
 *
 *  Detailed steps done in the CINT script:
 *  ====================================
 *    1) Step1 - Test Setup (Done in test_setup())
 *    ================================
 *       a) Port 2 ports in loopback for testing.
 *       b) Create a vlan.
 *       c) Add ports to the VLAN.
 *       d) Add test DMAC to the L2 Entry table for this VLAN for the selected Egress Port.
 *
 *    2) Step2 - Configuration (Done in TestFpPresel()).
 *    ===================================================
 *       a) Create Presel entry
 *          VFP QUALIFIERS: L2MacInfo (To match if SMAC is less than DMAC numerically)
 *          IFP QUALIFIERS: L2MacInfo (To match if SMAC is less than DMAC numerically)
 *          EFP QUALIFIERS: PktType = IpUdp (IPv4 UDP)
 *       b) Create main TCAM entry with Presel associated with it.
 *       c) Attach STAT
 *
 *    2) Step3 - Verification (Done in verify())
 *    ==============================
 *       a) For VFP and IFP, send packet with SMAC < DMAC for positive case. SMAC > DMAC for
 *          negative case.
 *       b) For EFP, send IP UDP packet for +ve case and Non IP packet for -ve case.
 *       b) Expected Result:
 *          ================
 *          STAT should increase only for +ve case. When without presel, stat will only increment
 *          for Main TCAM qualifiers match. When WITH presel, stat will increment for both stages
 *          qualfiers match (Presel and Main TCAM).
 *
 * NOTE: Use opt_* variables to change the test variant
 */

cint_reset();

/****************   GENERIC UTILITY FUNCTIONS STARTS  **************************
 */
bcm_port_t PORT_ANY = -1;                                                  /*H*/
bcm_port_t __next_port_to_return = 1;                                      /*H*/
int _max_group_id = 61;                                                    /*H*/
bcm_port_t         // Get next valid Ethernet port                         /*H*/
 portGetNextE(int unit, bcm_port_t PreferredPort)                          /*H*/
{                                                                          /*H*/
  int i=0, rv=0;                                                           /*H*/
  bcm_port_config_t configP;                                               /*H*/
  bcm_pbmp_t ports_pbmp;                                                   /*H*/
  if( PreferredPort != PORT_ANY ) {                                        /*H*/
    printf("Using preferred port %d\n", PreferredPort);                    /*H*/
    return PreferredPort;                                                  /*H*/
  }                                                                        /*H*/
  rv = bcm_port_config_get(unit, &configP);                                /*H*/
  if(BCM_FAILURE(rv)) {                                                    /*H*/
    printf("\nError in retrieving port configuration: %s %d.\n",           /*H*/
        bcm_errmsg(rv), __next_port_to_return);                            /*H*/
    exit;                                                                  /*H*/
  }                                                                        /*H*/
  ports_pbmp = configP.e;    // configP.hg;                                /*H*/
  for (i= __next_port_to_return; i < BCM_PBMP_PORT_MAX; i++) {             /*H*/
    if ( BCM_PBMP_MEMBER(&ports_pbmp, i) ) {                               /*H*/
        __next_port_to_return = i+1; // point to a probable next port      /*H*/
        return i;                                                          /*H*/
    }                                                                      /*H*/
  }                                                                        /*H*/
  printf("ERROR: Not enough ports %d\n", __next_port_to_return);           /*H*/
  exit;                                                                    /*H*/
}                                                                          /*H*/
bcm_error_t                                                                /*H*/
 common_fp_port_setup(int unit, bcm_port_t port, int LoopBackType, int Ing)/*H*/
{                                                                          /*H*/
  bcm_field_group_t group;                                                 /*H*/
  bcm_field_group_config_t group_config;                                   /*H*/
  uint32  pri, fp_statid, match_id, ctr_action_id, ObjId=1;                /*H*/
  bcm_field_entry_t entry;                                                 /*H*/
  if(Ing) {                                                                /*H*/
      group = _max_group_id-2; match_id = (1<<7); pri=1;                   /*H*/
      fp_statid = test_setup_flexctr_cfg_index_base+0;                     /*H*/
  } else {                                                                 /*H*/
      group = _max_group_id-1; match_id = (1<<6); pri=2;                   /*H*/
      fp_statid = test_setup_flexctr_cfg_index_base+1;                     /*H*/
      BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, port,                 /*H*/
                                    bcmPortControlTrustIncomingVlan, 0));  /*H*/
  }                                                                        /*H*/
  entry = group;                                                           /*H*/
  //printf("\n1.Doing port loopback set...\n");                            /*H*/
  if( LoopBackType != -1 )                                                 /*H*/
    BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port, LoopBackType));  /*H*/
  bcm_field_group_config_t_init(&group_config);                            /*H*/
  BCM_FIELD_ASET_INIT(group_config.aset);                                  /*H*/
  BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionCopyToCpu);          /*H*/
  BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionStatGroup);          /*H*/
  group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_ID;                    /*H*/
  group_config.mode = bcmFieldGroupModeAuto;                               /*H*/
  group_config.group = group;                                              /*H*/
  group_config.priority = pri;                                             /*H*/
  BCM_FIELD_QSET_INIT(group_config.qset);                                  /*H*/
  BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInPort);            /*H*/
  BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStageIngress);      /*H*/
  //printf("1.Doing field group create...\n");                             /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_group_config_create(unit, &group_config)); /*H*/
  //printf("1.Doing field entry create...\n");                             /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_entry_create_id(unit, group, entry));      /*H*/
  //printf("1.Doing qualify InPort...\n");                                 /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_qualify_InPort(unit, entry, port,          /*H*/
            BCM_FIELD_EXACT_MATCH_MASK));                                  /*H*/
  //printf("1.Doing action add...\n");                                     /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry,                    /*H*/
            bcmFieldActionCopyToCpu, 1, match_id));                        /*H*/
  //printf("1.Doing flexctr create...\n");                                 /*H*/
  BCM_IF_ERROR_RETURN(flexctr_fp_stat_create(unit, group,                  /*H*/
                 bcmFieldStageIngress, ObjId, 2*1024, 1, &ctr_action_id)); /*H*/
  flexctr_cfg[fp_statid-1].flexctr_action_id = ctr_action_id;              /*H*/
  flexctr_cfg[fp_statid-1].counter_index = fp_statid;                      /*H*/
  //printf("1.Doing flexctr attach...\n");                                 /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_entry_flexctr_attach(unit, entry,          /*H*/
            &flexctr_cfg[fp_statid-1]));                                   /*H*/
  //printf("1.Doing entry install...\n");                                  /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, entry));               /*H*/
  return BCM_E_NONE;                                                       /*H*/
}                                                                          /*H*/
bcm_error_t                                                                /*H*/
 ingress_port_setup(int unit, bcm_port_t port, int LoopBackType)           /*H*/
{                                                                          /*H*/
  return common_fp_port_setup(unit, port, LoopBackType, 1);                /*H*/
}                                                                          /*H*/
bcm_error_t                                                                /*H*/
 egress_port_setup(int unit, bcm_port_t port, int LoopBackType)            /*H*/
{                                                                          /*H*/
  return common_fp_port_setup(unit, port, LoopBackType, 0);                /*H*/
}                                                                          /*H*/
bcm_error_t       /* YAML: FP_ING_OPERMODE: GLOBAL_PIPE_AWARE */           /*H*/
 egress_port_multi_setup(int unit, bcm_pbmp_t pbm, int LoopBackType)       /*H*/
{       /* ifp_inports_support_enable */                                   /*H*/
  bcm_field_group_t group = _max_group_id-0;                               /*H*/
  uint32  pri, fp_statid, match_id, ctr_action_id, ObjId=1;                /*H*/
  bcm_field_group_config_t group_config;                                   /*H*/
  bcm_field_entry_t        entry;                                          /*H*/
  bcm_port_t               port;                                           /*H*/
  if( LoopBackType != -1 )                                                 /*H*/
   BCM_PBMP_ITER(pbm, port) {                                              /*H*/
     BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port, LoopBackType)); /*H*/
     BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, port,                  /*H*/
                                     bcmPortControlTrustIncomingVlan, 0)); /*H*/
  }                                                                        /*H*/
  print pbm;                                                               /*H*/
  bcm_pbmp_t pbm_mask;                                                     /*H*/
  BCM_PBMP_CLEAR(pbm_mask);                                                /*H*/
  BCM_PBMP_NEGATE(pbm_mask, pbm_mask);                                     /*H*/
  entry = group; fp_statid = test_setup_flexctr_cfg_index_base+2;          /*H*/
  match_id = (1<<5); pri = 3;                                              /*H*/
  bcm_port_config_t port_config;                                           /*H*/
  bcm_port_config_t_init(&port_config);                                    /*H*/
  BCM_IF_ERROR_RETURN(bcm_port_config_get(unit, &port_config));            /*H*/
  bcm_field_group_config_t_init(&group_config);                            /*H*/
  BCM_FIELD_ASET_INIT(group_config.aset);                                  /*H*/
  BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionCopyToCpu);          /*H*/
  BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionStatGroup);          /*H*/
  group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_ID;                    /*H*/
  group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_PORT;                  /*H*/
  group_config.ports = port_config.all;                                    /*H*/
  group_config.mode = bcmFieldGroupModeAuto;                               /*H*/
  group_config.group = group;                                              /*H*/
  group_config.priority = pri;                                             /*H*/
  BCM_FIELD_QSET_INIT(group_config.qset);                                  /*H*/
  BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInPorts);           /*H*/
  BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStageIngress);      /*H*/
  printf("2.Doing group config create...\n");                              /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_group_config_create(unit,                  /*H*/
                                                    &group_config));       /*H*/
  //printf("2.Doing entry create...\n");                                   /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_entry_create_id(unit, group, entry));      /*H*/
  //printf("2.Doing qualify add InPorts...\n");                            /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_qualify_InPorts(unit, entry,               /*H*/
              pbm, pbm));                                                  /*H*/
  //printf("2.Doing actions add...\n");                                    /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry,                    /*H*/
              bcmFieldActionCopyToCpu, 1, match_id));                      /*H*/
  //printf("2.Doing flex stat create...\n");                               /*H*/
  BCM_IF_ERROR_RETURN(flexctr_fp_stat_create(unit, group,                  /*H*/
                 bcmFieldStageIngress, ObjId, 2*1024, 1, &ctr_action_id)); /*H*/
  flexctr_cfg[fp_statid-1].flexctr_action_id = ctr_action_id;              /*H*/
  flexctr_cfg[fp_statid-1].counter_index = fp_statid;                      /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_entry_flexctr_attach(unit, entry,          /*H*/
            &flexctr_cfg[fp_statid-1]));                                   /*H*/
  BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, entry));               /*H*/
  return BCM_E_NONE;                                                       /*H*/
}                                                                          /*H*/
int chartoint(int c)                                                       /*H*/
{                                                                          /*H*/
    char *hex = "aAbBcCdDeEfF";                                            /*H*/
    int i, result = 0;                                                     /*H*/
    for(i = 0; (result == 0) && (hex[i] != '\0'); i++) {                   /*H*/
        if(hex[i] == c) {                                                  /*H*/
            result = 10 + (i / 2);                                         /*H*/
        }                                                                  /*H*/
    }                                                                      /*H*/
    return result;                                                         /*H*/
}                                                                          /*H*/
uint32 mine_dtoi(char *str)                                                /*H*/
{                                                                          /*H*/
    int i;                                                                 /*H*/
    uint32 dec = 0;                                                        /*H*/
    for(i=0; str[i]!=0; i++) {                                             /*H*/
        dec = dec * 10 + ( str[i] - '0' );                                 /*H*/
    }                                                                      /*H*/
    return dec;                                                            /*H*/
}                                                                          /*H*/
/* Converts String to Hexadecimal or Decimal. Hex is preceding is */       /*H*/
/* 'x' or 'X'. Else Decimal */                                             /*H*/
uint32 mine_atoi(char *str)                                                /*H*/
{                                                                          /*H*/
    uint32 result = 0;                                                     /*H*/
    int i = 0, proper = 1, temp, is_decimal = 1;                           /*H*/
    //To take care of 0x and 0X added before the hex no.                   /*H*/
    if((str[0] == 'x') || (str[0] == 'X') ) {                              /*H*/
        is_decimal = 0;                                                    /*H*/
    }                                                                      /*H*/
    if(str[0] == '0') {                                                    /*H*/
        is_decimal = 0;                                                    /*H*/
        ++i;                                                               /*H*/
        if((str[i] == 'x') || (str[i] == 'X') ) {                          /*H*/
            ++i;                                                           /*H*/
        } else {                                                           /*H*/
            i--; // '0' was a valid 0 as no trailing 'x' found             /*H*/
        }                                                                  /*H*/
    }                                                                      /*H*/
    if( is_decimal ) {                                                     /*H*/
        return mine_dtoi(str);                                             /*H*/
    }                                                                      /*H*/
    while(proper && (str[i] != '\0') ) {                                   /*H*/
        result = result * 16;                                              /*H*/
        if((str[i] >= '0') && (str[i] <= '9') ) {                          /*H*/
            result = result + (str[i] - '0');                              /*H*/
        } else {                                                           /*H*/
            temp = chartoint(str[i]);                                      /*H*/
            if(temp == 0) {                                                /*H*/
                printf("Improper char 0x%X", str[i]);                      /*H*/
                proper = 0;                                                /*H*/
            } else {                                                       /*H*/
                result = result + temp;                                    /*H*/
            }                                                              /*H*/
        }                                                                  /*H*/
        ++i;                                                               /*H*/
    }                                                                      /*H*/
    //If any character is not a proper hex no. ,  return 0                 /*H*/
    if(!proper) {                                                          /*H*/
     printf("ERROR EVALUATING IN mine_atoi [%s]. Defaulting to 0.\n", str);/*H*/
     result = 0;                                                           /*H*/
    }                                                                      /*H*/
    return result;                                                         /*H*/
}                                                                          /*H*/
uint32 ip4_sum_n_size_update(char *headerStr,                              /*H*/
                                int StartOfIpHdrByte,int SkipEqualCheck)   /*H*/
{                                                                          /*H*/
    uint32 word16, sum=0, i=0, ip4len;                                     /*H*/
    char numStr1[5], numStr2[5];                                           /*H*/
    unsigned char byte1, byte2;                                            /*H*/
    if( !SkipEqualCheck )                                                  /*H*/
        while(i<2) { if( *headerStr++ == '=' ) i++; }                      /*H*/
    StartOfIpHdrByte = StartOfIpHdrByte * 2;  // ascii in text, hence *2   /*H*/
    headerStr = &headerStr[StartOfIpHdrByte];                              /*H*/
    ip4len = (sal_strlen(&headerStr[4*2]))/2;                              /*H*/
    sprintf(numStr1, "%04X", ip4len);                                      /*H*/
    headerStr[4] = numStr1[0]; headerStr[5] = numStr1[1];                  /*H*/
    headerStr[6] = numStr1[2]; headerStr[7] = numStr1[3];                  /*H*/
    numStr1[0] = '0'; numStr1[1] = 'x'; numStr1[2] = 0;                    /*H*/
    numStr1[3] = 0; numStr1[4] = 0;                                        /*H*/
    numStr2[0] = '0'; numStr2[1] = 'x'; numStr2[2] = 0;                    /*H*/
    numStr2[3] = 0; numStr2[4] = 0;                                        /*H*/
    // make 16 bit words out of every two adjacent 8 bit words in          /*H*/
    // the packet and add them up                                          /*H*/
    for (i=0;i<20;i+=2){                                                   /*H*/
        if(i>=10 && i<=11) {                                               /*H*/
            continue;                                                      /*H*/
        } else {                                                           /*H*/
            numStr1[2] = headerStr[i*2];                                   /*H*/
            numStr1[3] = headerStr[(i*2)+1];                               /*H*/
            numStr2[2] = headerStr[(i*2)+2];                               /*H*/
            numStr2[3] = headerStr[(i*2)+3];                               /*H*/
        }                                                                  /*H*/
        byte1 = mine_atoi(numStr1); byte2 = mine_atoi(numStr2);            /*H*/
        word16 =((byte1<<8)&0xFF00)+(byte2&0xFF);                          /*H*/
        sum = sum + word16;                                                /*H*/
    }                                                                      /*H*/
    // take only 16 bits out of the 32 bit sum and add up the carries      /*H*/
    while (sum>>16) sum = (sum & 0xFFFF)+(sum >> 16);                      /*H*/
    sum = (~sum) & 0xFFFF;                                                 /*H*/
    sprintf(numStr1, "%04X", sum);                                         /*H*/
    headerStr[20] = numStr1[0]; headerStr[21] = numStr1[1];                /*H*/
    headerStr[22] = numStr1[2]; headerStr[23] = numStr1[3];                /*H*/
    return sum;                                                            /*H*/
}                                                                          /*H*/
int FORM_VID(int PCP, int DEI, int VID) {                                  /*H*/
    return ( ((PCP)<<13) | ((DEI)<<12) | ((VID) & 0xFFF) );                /*H*/
}                                                                          /*H*/
int FORM_MPLS(int LABEL, int EXP, int S, int TTL) {                        /*H*/
    return ( ((LABEL)<<12) | ((EXP)<<9) | ((S)<<8) | ((TTL) & 0xFF) );     /*H*/
}                                                                          /*H*/
void bbshell(int unit, char *str)                                          /*H*/
{                                                                          /*H*/
  printf("B_CM.%d> %s\n", unit, str);                                      /*H*/
  bshell(unit, str);                                                       /*H*/
}                                                                          /*H*/
/****************   GENERIC UTILITY FUNCTIONS ENDS  ****************************
 */

// 1st parameter is YES. E.g. cint thisflie.c YES 1 1

// 1st parameter is YES. E.g. cint thisflie.c YES 1 1
int opt_TestWithPresel = 1;
int opt_IsVfp = 0;
int opt_IsIfp = 1;
int opt_IsEfp = 0;

print ARGC;

/* WithPresel? With:1 Without:0 */
if( ARGC >= 2 ) {
    if( *ARGV[1] == '1' ) {
        opt_TestWithPresel = 1;
    } else {
        opt_TestWithPresel = 0;
    }
}
/* Which Stage? VFP:1  IFP:2  EFP:3 */
if( ARGC >= 3 ) {
    if( *ARGV[2] == '1' ) {
        opt_IsVfp = 1; opt_IsIfp = 0; opt_IsEfp = 0;
    } else if( *ARGV[2] == '2' ) {
        opt_IsVfp = 0; opt_IsIfp = 1; opt_IsEfp = 0;
    } else if( *ARGV[2] == '3' ) {
        opt_IsVfp = 0; opt_IsIfp = 0; opt_IsEfp = 1;
    }
}

bcm_field_stage_t   opt_TestFpStage;
bcm_field_qualify_t opt_TestFpQualStage;

if( opt_IsVfp ) {
    opt_TestFpStage = bcmFieldStageLookup; opt_TestFpQualStage = bcmFieldQualifyStageLookup;
} else if( opt_IsIfp ) {
    opt_TestFpStage = bcmFieldStageIngress; opt_TestFpQualStage = bcmFieldQualifyStageIngress;
} else if( opt_IsEfp ) {
    opt_TestFpStage = bcmFieldStageEgress; opt_TestFpQualStage = bcmFieldQualifyStageEgress;
}

print opt_TestWithPresel;
print opt_TestFpStage;
print opt_TestFpQualStage;
print opt_IsVfp;
print opt_IsIfp;
print opt_IsEfp;

int opt_IsForSimulator = 0;
int opt_UsePipeUnique = 0;

print opt_IsForSimulator;
print opt_UsePipeUnique;

// //////////////////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////////////////
int unit = 0;

bcm_vlan_t  test_vid64 = 0x64;

bcm_mac_t   test_mac_dd = {0x00, 0x00, 0x00, 0x00, 0x00, 0xDD};
bcm_mac_t   test_mac_cc = {0x00, 0x00, 0x00, 0x00, 0x00, 0xCC};

bcm_mac_t   test_mac_mask = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

bcm_ip_t    test_sip = 0x10101011;
bcm_ip_t    test_dip = 0x20202021;
bcm_ip_t    test_ip_mask = 0xFFFFFFFF;

uint16      test_udp_src_port = 0x1111;
uint16      test_udp_dst_port = 0x2222;

int prio1 = 58;
int prio2 = 61;

bcm_port_t cpu_port = 0;
bcm_module_t module_id = 0;

bcm_port_t ing_port1 = PORT_ANY; // Set to a valid port if known already.
bcm_port_t ing_port2 = PORT_ANY;
bcm_port_t ing_port3 = PORT_ANY;

bcm_port_t egr_port1 = PORT_ANY;
bcm_port_t egr_port2 = PORT_ANY;

/* Populate the XE/CE/CD ports */
ing_port1 = portGetNextE(unit, ing_port1);
ing_port2 = portGetNextE(unit, ing_port2);
ing_port3 = portGetNextE(unit, ing_port3);

egr_port1 = portGetNextE(unit, egr_port1);
egr_port2 = portGetNextE(unit, egr_port2);

print ing_port1;
print ing_port2;
print ing_port3;
print egr_port1;
print egr_port2;

// ////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////
int         statid_used = 0;
int         actionid_created = 0;
int         test_setup_flexctr_cfg_index_base = 11;
bcm_field_flexctr_config_t flexctr_cfg[test_setup_flexctr_cfg_index_base+3];/* 3 extra for test setup */
int _accu_stat[test_setup_flexctr_cfg_index_base+3];    // accumulated stat
char * stat_desc[test_setup_flexctr_cfg_index_base+3];

bcm_error_t
 flexctr_fp_stat_create(int unit, int group_id, bcm_field_stage_t FpStage, int CObjId,
                          int index_num, int CountDrop, uint32 *stat_action_id /*OUT*/)
{
    bcm_flexctr_action_t action = {0};
    bcm_flexctr_index_operation_t *index_op = &action.index_operation;
    bcm_flexctr_value_operation_t *value_a_op = &action.operation_a;
    bcm_flexctr_value_operation_t *value_b_op = &action.operation_b;
    int options = 0;

    bcm_flexctr_action_t_init(&action);

    action.mode = bcmFlexctrCounterModeNormal;
    action.hint = group_id;
    if( CountDrop ) action.drop_count_mode = bcmFlexctrDropCountModeAll;
    action.index_num = index_num;

    if( FpStage == bcmFieldStageLookup ) {
        action.source = bcmFlexctrSourceVfp;
        if( CObjId ) {
            //index_op->object[0] = bcmFlexctrObjectIngVfpOpaqueObj1;
        } else {
            index_op->object[0] = bcmFlexctrObjectIngVfpOpaqueObj0;
        }
    } else if( FpStage == bcmFieldStageIngress ) {
        action.source = bcmFlexctrSourceIfp;
        if( CObjId ) {
            printf("OBJ1\n");
            index_op->object[0] = bcmFlexctrObjectIngIfpOpaqueObj1; // Obj2 is also there
        } else {
            printf("OBJ0\n");
            index_op->object[0] = bcmFlexctrObjectIngIfpOpaqueObj0;
        }
    } else if( FpStage == bcmFieldStageEgress ) {
        action.source = bcmFlexctrSourceEfp;
        if( CObjId ) {
            index_op->object[0] = bcmFlexctrObjectEgrEfpOpaqueObj2;
        } else {
            index_op->object[0] = bcmFlexctrObjectEgrEfpOpaqueObj1;
        }
    } else if( FpStage == bcmFlexctrSourceExactMatch ) {
        action.source = bcmFlexctrSourceExactMatch;
        if( CObjId ) {
            index_op->object[0] = bcmFlexctrObjectIngEmFtOpaqueObj1;
        } else {
            index_op->object[0] = bcmFlexctrObjectIngEmFtOpaqueObj0;
        }
    }

    //index_op->object[0] = bcmFlexctrObjectConstZero;
    index_op->mask_size[0] = 11;
    index_op->shift[0] = 0;
    index_op->object[1] = bcmFlexctrObjectConstZero;    // always = 0
    index_op->mask_size[1] = 1;
    index_op->shift[1] = 0;

    /* Increase counter per packet. */
    value_a_op->select = bcmFlexctrValueSelectCounterValue;
    value_a_op->object[0] = bcmFlexctrObjectConstOne; // Increment by '1'
    value_a_op->mask_size[0] = 16;
    value_a_op->shift[0] = 0;
    value_a_op->object[1] = bcmFlexctrObjectConstZero;  // NOOP
    value_a_op->mask_size[1] = 1;
    value_a_op->shift[1] = 0;
    value_a_op->type = bcmFlexctrValueOperationTypeInc;

    /* Increase counter per packet bytes. */
    value_b_op->select = bcmFlexctrValueSelectPacketLength;
    value_b_op->type = bcmFlexctrValueOperationTypeInc;

    if( opt_UsePipeUnique ) {
        bcm_port_config_t pc;
        bcm_port_config_t_init(&pc);
        bcm_port_config_get(unit, &pc);
        BCM_PBMP_ASSIGN(action.ports, pc.per_pp_pipe[0]);
    }

    //print action;

    BCM_IF_ERROR_RETURN( bcm_flexctr_action_create(unit, options, &action, stat_action_id) );
    printf(">>\t stat_action_id=0x%08X\n", *stat_action_id);

    actionid_created++;

    return BCM_E_NONE;
}

void PrintStat(int unit)
{
    int i, rv, isIncremented = 0;
    bcm_flexctr_counter_value_t     counter_value;
    uint32 aid, cid;
    int opt_ClearCounterOnRead = 1;

    printf("\n");

    for(i=test_setup_flexctr_cfg_index_base; i<test_setup_flexctr_cfg_index_base+3; ++i) {
        aid = flexctr_cfg[i-1].flexctr_action_id;
        cid = flexctr_cfg[i-1].counter_index;
        if( aid ) {
            rv = bcm_flexctr_stat_sync_get(unit, aid, 1, &cid, &counter_value);
            if(BCM_E_NONE != rv) {
                printf("Error in reading TEST_SETUP stat %d. i=%d\n", rv, i); return;
            }
            if( (COMPILER_64_HI(counter_value.value[0]) != 0) ||
                (COMPILER_64_LO(counter_value.value[0]) != 0) ) {
                switch(i) {
                  case test_setup_flexctr_cfg_index_base: printf("Ctr tst ing:\n"); break;
                  case test_setup_flexctr_cfg_index_base+1: printf("Ctr tst egr:\n"); break;
                  case test_setup_flexctr_cfg_index_base+2: printf("Ctr tst egr multi:\n"); break;
                }
                printf("Ctr:0x%08X-0x%08X -     0x%08X    0x%08X  (val0_low / val1_low)\n",
                    aid, cid, COMPILER_64_LO(counter_value.value[0]),
                    COMPILER_64_LO(counter_value.value[1]));
                //print counter_value;
            }
        }
    }
    printf("\n------- ActionIds=%d Statids=%d -------\n", actionid_created, statid_used);
    for(i=0; i<statid_used; ++i)
    {
        char *desc;
        rv = bcm_flexctr_stat_sync_get(unit,
                                  flexctr_cfg[i].flexctr_action_id, 1,
                                  &flexctr_cfg[i].counter_index,
                                  &counter_value);
        if(BCM_E_NONE!=rv) {
            printf("1Error in reading stat %d\n", rv);
            return;
        }
        if( (COMPILER_64_HI(counter_value.value[0]) != 0) ||
            (COMPILER_64_LO(counter_value.value[0]) != 0) ) {
            isIncremented++;
            _accu_stat[i] += COMPILER_64_LO(counter_value.value[0]);
            if( !stat_desc[i] ) desc = ""; else desc = stat_desc[i];
            printf("%s Ctr:0x%08X-0x%08X: VAL0LO:%d(%d)-VAL1LO:0x%08X\n", desc,
               flexctr_cfg[i].flexctr_action_id, flexctr_cfg[i].counter_index,
               COMPILER_64_LO(counter_value.value[0]), _accu_stat[i],
               COMPILER_64_LO(counter_value.value[1]) );
            //print counter_value;
            if( opt_ClearCounterOnRead ) {   // Clear counter
                COMPILER_64_SET(counter_value.value[0], 0, 0);
                COMPILER_64_SET(counter_value.value[1], 0, 0);
                bcm_flexctr_stat_set(unit, flexctr_cfg[i].flexctr_action_id, 1,
                                 &flexctr_cfg[i].counter_index, &counter_value);
            } else {
                _accu_stat[i] = 0;
            }
        }
    }
    if( !isIncremented ) printf(">>>> No Counter Increments This Time  <<<<<<\n");
    printf("--------------------------\n");
    return;
}


// ///////////////////////////////////////////////////////////

bcm_error_t
    TestFunc(int prio)
{
    bcm_field_entry_t entry;
    bcm_field_group_config_t group_config;
    int entry1_prio = 100;
    bcm_field_presel_t presel_id1 = 1; //0x01000001;
    bcm_field_presel_group_config_t gcfg_pre;

    if( opt_TestWithPresel ) {
        int fp_id_base;
        if( opt_IsVfp ) fp_id_base = BCM_FIELD_VFP_ID_BASE;
        if( opt_IsIfp ) fp_id_base = BCM_FIELD_IFP_ID_BASE;
        if( opt_IsEfp ) fp_id_base = BCM_FIELD_EFP_ID_BASE;

        bcm_field_presel_config_t presel_config;

        bcm_field_presel_group_config_t_init(&gcfg_pre);

        BCM_FIELD_QSET_INIT(gcfg_pre.qset);

        if( opt_IsVfp ) BCM_FIELD_QSET_ADD(gcfg_pre.qset, bcmFieldQualifyL2MacInfo);
        if( !opt_IsVfp ) BCM_FIELD_QSET_ADD(gcfg_pre.qset, bcmFieldQualifyPktType);

        BCM_FIELD_QSET_ADD(gcfg_pre.qset, opt_TestFpQualStage);

        printf("Doing presel group config create...\n");
        BCM_IF_ERROR_RETURN( bcm_field_presel_group_config_create(unit, &gcfg_pre) );

        bcm_field_presel_config_t_init(&presel_config);
        presel_config.stage = opt_TestFpStage;
        presel_config.flags = BCM_FIELD_PRESEL_CREATE_WITH_ID;
        presel_config.presel_id = presel_id1 | fp_id_base;

        printf("Doing presel config create...");
        BCM_IF_ERROR_RETURN( bcm_field_presel_config_create(unit, &presel_config) );
        presel_id1 = presel_config.presel_id;
        printf("preselid=0x%08X...\n", presel_id1);

        if( opt_IsVfp )
        {
            printf("Doing presel qual L2MacInfo SMAC_LT_DMAC...\n");
            BCM_IF_ERROR_RETURN( bcm_field_qualify_L2MacInfo(unit,
                              BCM_FIELD_QUALIFY_PRESEL | presel_id1, BCM_FIELD_L2MAC_SMAC_LT_DMAC,
                              BCM_FIELD_L2MAC_SMAC_LT_DMAC) );
        }
        if( !opt_IsVfp )
        {
            printf("Doing presel qual PktType IpUdp...\n");
            BCM_IF_ERROR_RETURN( bcm_field_qualify_PktType(unit,
                              BCM_FIELD_QUALIFY_PRESEL | presel_id1, bcmFieldPktTypeIpUdp) );
        }
        presel_id1 = presel_id1 ^ fp_id_base;
    }

    /* IFP Group Configuration and Creation */
    bcm_field_group_config_t_init(&group_config);
    group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_MODE;
    group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_ASET;
    if( opt_UsePipeUnique ) group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_PORT;
    if( opt_TestWithPresel ) {
        group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_PRESELSET;
        group_config.flags |= BCM_FIELD_GROUP_CREATE_WITH_PRESEL_GROUP;
        BCM_FIELD_PRESEL_ADD(group_config.preselset, presel_id1 & BCM_FIELD_ID_MASK);   // BCM_FIELD_ID_MASK
        group_config.presel_group = gcfg_pre.presel_group;
    }
    group_config.priority = prio;
    group_config.mode = bcmFieldGroupModeAuto;
    BCM_FIELD_QSET_INIT(group_config.qset);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifySrcPort);
    BCM_FIELD_QSET_ADD(group_config.qset, opt_TestFpQualStage); // bcmFieldQualifyStageIngress

    BCM_FIELD_ASET_INIT(group_config.aset);
    BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionDrop);
    if( !opt_IsEfp )
        BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionCopyToCpu);
    BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionStatGroup);
    //BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionStatGroupWithoutCounterIndex);

    if( opt_UsePipeUnique ) {
        bcm_port_config_t pc;
        bcm_port_config_t_init(&pc);
        printf("Doing port config get...\n");
        BCM_IF_ERROR_RETURN( bcm_port_config_get(unit, &pc) );
        BCM_PBMP_ASSIGN(group_config.ports, pc.per_pp_pipe[0]);
    }

    if( opt_IsIfp ) {
        bcm_field_hint_t hint;
        bcm_field_hintid_t hint_id;
        printf("Doing field hint create...\n");
        BCM_IF_ERROR_RETURN(bcm_field_hints_create(unit, &hint_id));
        /* configuring hint type, and opaque object to be used */
        bcm_field_hint_t_init(&hint);
        hint.hint_type = bcmFieldHintTypeFlexCtrOpaqueObjectSel;
        hint.value = bcmFlexctrObjectIngIfpOpaqueObj0;
        printf("Doing field hint add %d...\n", hint_id);
        /* Associating the above configured hints to hint id */
        BCM_IF_ERROR_RETURN(bcm_field_hints_add(unit, hint_id, &hint));

        group_config.hintid = hint_id;
    }

    printf("Doing group config create...\n");
    BCM_IF_ERROR_RETURN(bcm_field_group_config_create(unit, &group_config));

    printf("Doing entry create to group 0x%08X...\n", group_config.group);
    BCM_IF_ERROR_RETURN( bcm_field_entry_create(unit, group_config.group, &entry) );

    printf("Doing qualify SrcPort...\n");
    BCM_IF_ERROR_RETURN(bcm_field_qualify_SrcPort(unit, entry, module_id, -1, ing_port1, -1) );

    //printf("Doing action add Drop...\n");
    //BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry, bcmFieldActionDrop, 0, 0));
    if( !opt_IsEfp )
    {
        /* If testing for L3, comment our this action for monitoring.
           Else it interferes with the utility FP actions defined above in UTILITY section .
        */
        printf("Doing action add CopyToCpu...\n");
        BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry, bcmFieldActionCopyToCpu, 1, 0x0C));
    }

    BCM_IF_ERROR_RETURN(bcm_field_entry_prio_set(unit, entry, entry1_prio));

    if( 1 )
    {
        uint32 ctr_action_id;
        int CObjId = 0;
        printf("Doing flexctr create to group 0x%08X...\n", group_config.group);
        BCM_IF_ERROR_RETURN( flexctr_fp_stat_create(unit, group_config.group,
                opt_TestFpStage /*bcmFieldStageIngress*/, CObjId, 2*1024, 1, &ctr_action_id) );
        ////////////////////
        flexctr_cfg[statid_used].flexctr_action_id = ctr_action_id;
        flexctr_cfg[statid_used].counter_index = statid_used;
        printf("Doing flexctr stat attach to entry 0x%08X. StatID:0x%08X:%d...\n", entry,
                                                                 ctr_action_id, statid_used);
        BCM_IF_ERROR_RETURN( bcm_field_entry_flexctr_attach(unit, entry,
                                        &flexctr_cfg[statid_used]) );
        stat_desc[statid_used] = "Entry 1 : ";
        statid_used++;
    }
    /* Installing FP Entry to FP TCAM */
    printf("Doing entry install...\n");
    BCM_IF_ERROR_RETURN( bcm_field_entry_install(unit, entry) );

    return BCM_E_NONE;
}

/*
 * This functions gets the port numbers and sets up ingress and
 * egress ports. Check ingress_port_setup() and egress_port_setup().
 */
bcm_error_t test_setup(int unit)
{
    int rv;

    int loopBackType = BCM_PORT_LOOPBACK_MAC;   // BCM_PORT_LOOPBACK_PHY

    if( 1 )
    {
        bcm_pbmp_t     vlan_pbmp;
        bcm_pbmp_t     ut_pbmp;

        BCM_PBMP_CLEAR(vlan_pbmp);
        BCM_PBMP_PORT_ADD(vlan_pbmp, ing_port1);
        BCM_PBMP_PORT_ADD(vlan_pbmp, ing_port2);
        BCM_PBMP_PORT_ADD(vlan_pbmp, ing_port3);
        BCM_PBMP_PORT_ADD(vlan_pbmp, egr_port1);     // MTP port need not be part of the VLAN
        BCM_PBMP_PORT_ADD(vlan_pbmp, egr_port2);

        BCM_PBMP_CLEAR(ut_pbmp);
        BCM_IF_ERROR_RETURN(bcm_vlan_create(unit, test_vid64));
        BCM_IF_ERROR_RETURN(bcm_vlan_port_add(unit, test_vid64, vlan_pbmp, ut_pbmp));
        BCM_IF_ERROR_RETURN(bcm_vlan_port_remove(unit, 1, vlan_pbmp)); // remove from default vlan
    }

    if( 1 )
    {
        bcm_l2_addr_t l2_addr;

        bcm_l2_addr_t_init(&l2_addr, test_mac_dd, test_vid64);
        l2_addr.flags = BCM_L2_STATIC;
        l2_addr.port = egr_port1;
        printf("Doing L2 entry add\n");
        BCM_IF_ERROR_RETURN(bcm_l2_addr_add(unit, &l2_addr));
    }

    if( 1 ) {
        //bshell(unit, "pw start report +raw +decode dma");
        bshell(unit, "pw start report +all");
    }

    if( opt_IsForSimulator ) {
        return BCM_E_NONE;
    }

    if( 0 )
    {
        rv = ingress_port_setup(unit, ing_port1, loopBackType);
        if ( rv != BCM_E_NONE ) {
            printf("ingress_port_setup() failed for port %d (Error: %d)\n", ing_port1, rv);
            return rv;
        }

        rv = egress_port_setup(unit, egr_port1, loopBackType);
        if ( rv != BCM_E_NONE ) {
            printf("egress_port_setup() failed for port %d (Error: %d)\n", egr_port1, rv);
            return rv;
        }
    }
    else  if( 1 ) {
        char cmd[128];

        printf("Doing port loopbacks and mirror...\n");

        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, ing_port1, loopBackType));

        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, egr_port1, loopBackType));
        BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, egr_port1,
                    bcmPortControlTrustIncomingVlan, 0));   // DISCARD_ALL

        sprintf(cmd, "dmirror %d mode=ingress dp=cpu0 dm=0", ing_port1); bbshell(unit, cmd);
        sprintf(cmd, "dmirror %d mode=ingress dp=cpu0 dm=0", ing_port1); bbshell(unit, cmd);
    }
    else if( 1 )
    {
        printf("Doing port loopbacks...\n");

        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, ing_port1, loopBackType));

        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, egr_port1, loopBackType));
        BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, egr_port1,
                    bcmPortControlTrustIncomingVlan, 0));
    }

    if( 1 ) {
        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, ing_port2, loopBackType));
        BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, ing_port2,
                    bcmPortControlTrustIncomingVlan, 0));
        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, ing_port3, loopBackType));
        BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, ing_port3,
                    bcmPortControlTrustIncomingVlan, 0));
        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, egr_port2, loopBackType));
        BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, egr_port2,
                    bcmPortControlTrustIncomingVlan, 0));
    }

    return BCM_E_NONE;
}

bcm_error_t verify()
{
    char cmd[2*1024];
    int i;
    int prio = 0;

    sprintf(cmd, "a"); bbshell(unit, cmd);
    sprintf(cmd, "ver"); bbshell(unit, cmd);
    printf("\n\n");

    if( opt_IsVfp )
    {
        printf("##########  Sending SMAC<DMAC packet ########\n");
        sprintf(cmd, "tx 1 pbm=%d data=%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X8100%04X08004500LLLL000000004011SSSS%08X%08X%04X%04X0036C6B0000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D29197737CCCCCCCCCCCC",
            ing_port1,
            test_mac_dd[0], test_mac_dd[1], test_mac_dd[2],
            test_mac_dd[3], test_mac_dd[4], test_mac_dd[5],
            test_mac_cc[0], test_mac_cc[1], test_mac_cc[2],
            test_mac_cc[3], test_mac_cc[4], test_mac_cc[5],
            FORM_VID(prio, 0, test_vid64), test_sip, test_dip,
            test_udp_src_port,
            test_udp_dst_port );
        //printf("BEFORE: %s\n", cmd);
        /* For single tag IP packet; 18th byte starts at ->4500... Byte in hex; not ascii. */
        ip4_sum_n_size_update(cmd, 18, 0);
        //ip4_sum_n_size_update(cmd, 18+20, 0); // for inner ipv4 in Ip-in-IP packet with single tag
        //printf("AFTER:  %s\n", cmd);
        bbshell(unit, cmd);

        sprintf(cmd, "sleep %d", 1);
        bbshell(unit, cmd);
        PrintStat(unit);
        printf("#####################################################\n\n");
    }
    if( opt_IsVfp )
    {
        printf("##########  Sending SMAC>DMAC packet ########\n");
        sprintf(cmd, "tx 1 pbm=%d data=%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X8100%04X08004500LLLL000000004011SSSS%08X%08X%04X%04X0036C6B0000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D29197737CCCCCCCCCCCC",
            ing_port1,
            test_mac_dd[0], test_mac_dd[1], test_mac_dd[2],
            test_mac_dd[3], test_mac_dd[4], test_mac_dd[5],
            test_mac_cc[0], test_mac_cc[1], test_mac_cc[2],
            test_mac_cc[3], test_mac_cc[4]+0x1, test_mac_cc[5],
            FORM_VID(prio, 0, test_vid64), test_sip, test_dip,
            test_udp_src_port,
            test_udp_dst_port );
        //printf("BEFORE: %s\n", cmd);
        /* For single tag IP packet; 18th byte starts at ->4500... Byte in hex; not ascii. */
        ip4_sum_n_size_update(cmd, 18, 0);
        //ip4_sum_n_size_update(cmd, 18+20, 0); // for inner ipv4 in Ip-in-IP packet with single tag
        //printf("AFTER:  %s\n", cmd);
        bbshell(unit, cmd);

        sprintf(cmd, "sleep %d", 1);
        bbshell(unit, cmd);
        PrintStat(unit);
        printf("#####################################################\n\n");
    }

    if( opt_IsIfp || opt_IsEfp )
    {
        printf("##########  Sending IP packet ########\n");
        sprintf(cmd, "tx 1 pbm=%d data=%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X8100%04X08004500LLLL000000004011SSSS%08X%08X%04X%04X0036C6B0000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D29197737CCCCCCCCCCCC",
            ing_port1,
            test_mac_dd[0], test_mac_dd[1], test_mac_dd[2],
            test_mac_dd[3], test_mac_dd[4], test_mac_dd[5],
            test_mac_cc[0], test_mac_cc[1], test_mac_cc[2],
            test_mac_cc[3], test_mac_cc[4], test_mac_cc[5],
            FORM_VID(prio, 0, test_vid64), test_sip, test_dip,
            test_udp_src_port,
            test_udp_dst_port );
        //printf("BEFORE: %s\n", cmd);
        /* For single tag IP packet; 18th byte starts at ->4500... Byte in hex; not ascii. */
        ip4_sum_n_size_update(cmd, 18, 0);
        //ip4_sum_n_size_update(cmd, 18+20, 0); // for inner ipv4 in Ip-in-IP packet with single tag
        //printf("AFTER:  %s\n", cmd);
        bbshell(unit, cmd);

        sprintf(cmd, "sleep %d", 1);
        bbshell(unit, cmd);
        PrintStat(unit);
        printf("#####################################################\n\n");
    }

    if( opt_IsIfp || opt_IsEfp )
    {
        printf("##########  Sending Non IP packet ########\n");
        sprintf(cmd, "tx 1 pbm=%d data=%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X8100%04XFFFFFFFFLLLL000000004011SSSS%08X%08X%04X%04X0036C6B0000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D29197737CCCCCCCCCCCC",
            ing_port1,
            test_mac_dd[0], test_mac_dd[1], test_mac_dd[2],
            test_mac_dd[3], test_mac_dd[4], test_mac_dd[5],
            test_mac_cc[0], test_mac_cc[1], test_mac_cc[2],
            test_mac_cc[3], test_mac_cc[4], test_mac_cc[5],
            FORM_VID(prio, 0, test_vid64), test_sip, test_dip,
            test_udp_src_port,
            test_udp_dst_port );
        //printf("BEFORE: %s\n", cmd);
        /* For single tag IP packet; 18th byte starts at ->4500... Byte in hex; not ascii. */
        ip4_sum_n_size_update(cmd, 18, 0);
        //ip4_sum_n_size_update(cmd, 18+20, 0); // for inner ipv4 in Ip-in-IP packet with single tag
        //printf("AFTER:  %s\n", cmd);
        bbshell(unit, cmd);

        sprintf(cmd, "sleep %d", 1);
        bbshell(unit, cmd);
        PrintStat(unit);
        printf("#####################################################\n\n");
    }
    if( 0 )
    {
        // bsh -c "lt DT_IFP_PRESEL_GRP_TEMPLATE  attr=filter_dflt traverse -l"
        if( opt_IsVfp ) {
            bbshell(unit, "bsh -c \"lt DT_VFP_PRESEL_GRP_TEMPLATE  attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_VFP_PRESEL_TEMPLATE attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_VFP_GRP_TEMPLATE attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_VFP_RULE_TEMPLATE  attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_VFP_ENTRY attr=filter_dflt  traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_VFP_ACTION_TEMPLATE attr=filter_dflt  traverse -l\"");
        }
        if( opt_IsIfp ) {
            bbshell(unit, "bsh -c \"lt DT_IFP_PRESEL_GRP_TEMPLATE  attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_IFP_PRESEL_TEMPLATE attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_IFP_GRP_TEMPLATE attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_IFP_RULE_TEMPLATE  attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_IFP_ENTRY attr=filter_dflt  traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_IFP_ACTION_TEMPLATE attr=filter_dflt  traverse -l\"");
        }
        if( opt_IsEfp ) {
            bbshell(unit, "bsh -c \"lt DT_EFP_PRESEL_GRP_TEMPLATE  attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_EFP_PRESEL_TEMPLATE attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_EFP_GRP_TEMPLATE attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_EFP_RULE_TEMPLATE  attr=filter_dflt traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_EFP_ENTRY attr=filter_dflt  traverse -l\"");
            bbshell(unit, "bsh -c \"lt DT_EFP_ACTION_TEMPLATE attr=filter_dflt  traverse -l\"");
        }
    }

    return BCM_E_NONE;
}

bcm_error_t execute()
{
    int rv;

    if( (rv = test_setup(unit)) != BCM_E_NONE )
    {
        printf("Creating the test setup failed %d - %s\n", rv, bcm_errmsg(rv));
        return rv;
    }

    if( (rv = TestFunc(unit)) != BCM_E_NONE )
    {
        printf("Configuring TestFpPresel() failed with %d - %s\n", rv, bcm_errmsg(rv));
        return rv;
    }

    if( (rv = verify()) != BCM_E_NONE )
    {
        printf("Verify TestFpPresel failed with %d - %s\n", rv, bcm_errmsg(rv));
        return rv;
    }

    return BCM_E_NONE;
}


char *auto_execute;
if( ARGC >= 1 ) {
    auto_execute =  ARGV[0];
} else {
    auto_execute = "YES";
}

if (!sal_strcmp(auto_execute, "YES")) {
  print execute();
}
