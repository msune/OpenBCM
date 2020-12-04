/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

/*
 * Feature  : Vxlan Bridging, IPv4 network to access tunnel
 *            termination flow and copy [CFI + DOT1P] value from
 *            underlay L2 header to overlay L2 header.
 *
 * Usage    : BCM.0> cint td4x9_hsdk_vxlan_ipv4_NtoA_L2_qos_copy.c
 *
 * config   : BCM956780-56780_A0-Default-config.yml
 *
 * Log file : td4x9_hsdk_vxlan_ipv4_NtoA_L2_qos_copy_log.txt
 *
 * Test Topology :
 *
 *                                  +----------------------+
 *                                  |                      |   VLAN-22        Underlay-NextHop
 *                                  |                      | ingress_port       +---+
 *   MAC 00::bb:bb                  |                      +--------------------+   |
 *            +---+          VLAN-21|                      |00::22:22           +---+
 *   Host(acc)|   +-----------------+         DUT          |                    00::02
 *            +---+     egress_port |                      |
 *                                  |                      |
 *                                  |                      |
 *                                  |                      |
 *                                  +----------------------+
 *
 * Summary:
 * ========
 * Cint example to demonstrate VxLAN  Bridging configuration for tunnel termination
 * with copying [CFI + DOT1P] value from underlay L2 header to overlay L2 header.
 *
 * Detailed steps done in the CINT script:
 * =======================================
 *   1) Step1 - Test Setup (Done in test_setup()):
 *   =============================================
 *     a) Selects two ports and configure them in Loopback mode. Out of these
 *        two ports, one port is used as ingress_port and the other as
 *        egress_port.
 *
 *     b) Install an IFP rule to copy ingress & egress packets to CPU and start
 *        packet watcher.
 *
 *     Note: IFP rule is meant for a verification purpose and is not part of the
 *           feature configuration.
 *
 *   2) Step2 - Configuration (Done in config_vxlan_ipv4_vtep()):
 *   ===========================================================
 *     a) Configure a VxLAN Bridging configuration.
 *        This does the necessary configurations of vxlan global settings,
 *        enable VPN, port learning, vlan, access port setting, network port
 *       setting,ingress Qos & Egress Qos map, tunnel setup interface
 *       and next hop.
 *
 *   3) Step3 - Verification (Done in verify()):
 *   ===========================================
 *     a) Check the configurations by 'vlan show', 'l2 show', traversing the vpn
 *        and vp's
 *
 *     b) Transmit the known unicast packets with incrementing [DOT1p + CFI] values in
 *        the undelay L2 header.
 *
 *     c) Expected Result:
 *     ===================
 *       We can see the tunnel terminated packet on the access egress port and
 *       the DOT1p + CFI] value copied from underlay L2 header to overlay L2 header.
 */

/*
Decap-case: packet sent from ingress port (network) to egress port (access)
Input packet (network port):
===========================
[bcmPWN.0]Packet[31]: data[0000]: {000000002222} {000000000002} 8100 f016  <<<< [CFI + DOT1P] value is 0xF in underlay L2 header
[bcmPWN.0]Packet[31]: data[0010]: 0800 4500 0082 0000 4000 3f11 65b7 c0a8
[bcmPWN.0]Packet[31]: data[0020]: 0101 0a0a 0a01 d903 12b5 006e ee32 0800
[bcmPWN.0]Packet[31]: data[0030]: 0000 0123 4500 0000 0000 bbbb 0000 0000
[bcmPWN.0]Packet[31]: data[0040]: aaaa 8100 0015 0800 4500 0050 0001 0000  <<<< [CFI + DOT1P] value is 0x0 in overlay L2 header
[bcmPWN.0]Packet[31]: data[0050]: 4011 7497 0202 0202 0101 0101 0035 0035
[bcmPWN.0]Packet[31]: data[0060]: 003c 32f6 7465 7374 7465 7374 7465 7374
[bcmPWN.0]Packet[31]: data[0070]: 7465 7374 7465 7374 7465 7374 7465 7374
[bcmPWN.0]Packet[31]: data[0080]: 7465 7374 7465 7374 7465 7374 7465 7374
[bcmPWN.0]Packet[31]: data[0090]: 7465 7374 7465 7374

Output packet (access port):
============================
[bcmPWN.0]Packet[32]: data[0000]: {00000000bbbb} {00000000aaaa} 8100 f015  <<<< [CFI + DOT1P] value is 0xF in overlay L2 header
[bcmPWN.0]Packet[32]: data[0010]: 0800 4500 0050 0001 0000 4011 7497 0202
[bcmPWN.0]Packet[32]: data[0020]: 0202 0101 0101 0035 0035 003c 32f6 7465
[bcmPWN.0]Packet[32]: data[0030]: 7374 7465 7374 7465 7374 7465 7374 7465
[bcmPWN.0]Packet[32]: data[0040]: 7374 7465 7374 7465 7374 7465 7374 7465
[bcmPWN.0]Packet[32]: data[0050]: 7374 7465 7374 7465 7374 7465 7374 7465
[bcmPWN.0]Packet[32]: data[0060]: 7374

*/

/* Reset C interpreter*/
cint_reset();

bcm_error_t show_vxlan_vtep_config(int unit);

bcm_gport_t   ing_net_gport_1;
bcm_gport_t   egr_acc_gport_1;
bcm_port_t    ing_net_port_1;
bcm_port_t    egr_acc_port_1;


/* struct for Access Port Params for creating access VP*/
struct vxlan_acc_cfg_t {
  bcm_gport_t   phy_Gport;/* Input : gport of the port/trunk*/
  bcm_vlan_t    acc_vlan;
  bcm_vlan_t    acc_inner_vlan;
  bcm_mac_t     acc_local_mac;
  bcm_mac_t     acc_remote_mac;
  bcm_mac_t     acc_remote_mc_mac;
  bcm_gport_t   acc_gport;
  int           port_class;
};

/* struct for Network Port params */
struct vxlan_net_cfg_t {
  bcm_port_t    phy_Gport;/* Input : gport of the port/trunk*/
  bcm_vlan_t    net_vlan;
  bcm_mac_t     net_local_mac;
  bcm_mac_t     net_remote_mac;
  bcm_ip_t      remote_ip;
  bcm_ip_t      remote_mc_ip;
  uint32        vxlan_vnid;
  bcm_ip_t      local_ip;
  uint16        udp_sp;
  bcm_gport_t   nw_gport;
  int           dvp_group_id;
};

struct vxlan_cfg_t {
  uint16          udp_dp;
  bcm_vpn_t       vxlan_vpn;
  bcm_multicast_t bc_group;
  bcm_multicast_t mc_group;
};

/*
 * This function is written so that hardcoding of port
 * numbers in Cint scripts is removed. This function gives
 * required number of ports
 */
bcm_error_t
portNumbersGet(int unit, int *port_list, int num_ports)
{
  bcm_port_config_t configP;
  bcm_pbmp_t        ports_pbmp;
  int               i=0, port=0, rv=0;

  rv = bcm_port_config_get(unit, &configP);
  if (BCM_FAILURE(rv)) {
    printf("\nError in retrieving port configuration: %s.\n",
                                                   bcm_errmsg(rv));
    return rv;
  }

  ports_pbmp = configP.e;
  for (i= 1; i < BCM_PBMP_PORT_MAX; i++) {
    if (BCM_PBMP_MEMBER(&ports_pbmp, i) && (port < num_ports)) {
      port_list[port] = i;
      port++;
    }
  }

  if ((0 == port) || (port != num_ports)) {
    printf("portNumbersGet() failed \n");
    return -1;
  }

  return BCM_E_NONE;
}

/*
 * Configures the port in loopback mode and installs
 * an IFP rule. This IFP rule copies the packets ingressing
 * on the specified port to CPU.
 */
bcm_error_t
ingress_port_multi_setup(int unit, bcm_pbmp_t pbm)
{
    bcm_field_group_config_t group_config;
    bcm_field_entry_t        entry;
    bcm_port_t               port;

    bcm_field_group_config_t_init(&group_config);
    BCM_FIELD_QSET_INIT(group_config.qset);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStageIngress);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInPort);
    BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionCopyToCpu);
    group_config.priority = 1;
    BCM_IF_ERROR_RETURN(bcm_field_group_config_create(unit, &group_config));

    BCM_PBMP_ITER(pbm, port) {
      printf("ingress_port_multi_setup port: %d setup\n", port);
      BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port,
                                                BCM_PORT_LOOPBACK_MAC));

      BCM_IF_ERROR_RETURN(bcm_field_entry_create(unit, group_config.group,
                                                 &entry));

      BCM_IF_ERROR_RETURN(bcm_field_qualify_InPort(unit, entry, port,
                                                BCM_FIELD_EXACT_MATCH_MASK));

      BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry,
                                               bcmFieldActionCopyToCpu,
                                               0, 0));

      BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, entry));
  }

  return BCM_E_NONE;
}

/*
 * Configures the port in loopback mode and installs
 * an IFP rule. This IFP rule copies the packets ingressing
 * on the specified port to CPU. Port is also configured
 * to discard all packets. This is to avoid continuous
 * loopback of the packet.
 */
bcm_error_t
egress_port_multi_setup(int unit, bcm_pbmp_t pbm)
{
    bcm_field_group_t group;
    bcm_field_entry_t entry;
    bcm_port_t        port;

    bcm_field_group_config_t group_config;

    bcm_field_group_config_t_init(&group_config);
    BCM_FIELD_QSET_INIT(group_config.qset);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStageIngress);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInPort);
    BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionCopyToCpu);
    BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionDrop);
    group_config.priority = 2;
    BCM_IF_ERROR_RETURN(bcm_field_group_config_create(unit, &group_config));

    BCM_PBMP_ITER(pbm, port) {
        printf("egress_port_multi_setup port: %d setup\n", port);

        BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port,
                                                  BCM_PORT_LOOPBACK_MAC));

        BCM_IF_ERROR_RETURN(bcm_field_entry_create(unit, group_config.group,
                                                   &entry));

        BCM_IF_ERROR_RETURN(bcm_field_qualify_InPort(unit, entry, port,
                                                  BCM_FIELD_EXACT_MATCH_MASK));

        BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry,
                                                 bcmFieldActionCopyToCpu, 0,
                                                 0));
        BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry,
                                                 bcmFieldActionDrop, 0, 0));

        BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, entry));
    }

    return BCM_E_NONE;
}

/*
 * Test Setup:
 * This functions gets the port numbers and sets up ingress and
 * egress ports. Check ingress_port_multi_setup() and egress_port_multi_setup().
 */
bcm_error_t
test_setup(int unit)
{
  bcm_pbmp_t    pbmp;
  int           port_list[2];

  if (BCM_E_NONE != portNumbersGet(unit, port_list, 2)) {
    printf("portNumbersGet() failed\n");
    return -1;
  }

  ing_net_port_1 = port_list[0];
  egr_acc_port_1 = port_list[1];

  if (BCM_E_NONE != bcm_port_gport_get(unit, ing_net_port_1,
                                         &(ing_net_gport_1)))
  {
        printf("bcm_port_gport_get() failed to get gport for port %d\n",
                                                  ing_net_port_1);
    return -1;
  }

  if (BCM_E_NONE !=bcm_port_gport_get(unit, egr_acc_port_1,
                                        &(egr_acc_gport_1)))
  {
        printf("bcm_port_gport_get() failed to get gport for port %d\n",
                                                  egr_acc_port_1);
    return -1;
  }

  BCM_PBMP_CLEAR(pbmp);
  BCM_PBMP_PORT_ADD(pbmp, ing_net_port_1);
  if (BCM_E_NONE != ingress_port_multi_setup(unit, pbmp))
  {
      printf("ingress_port_multi_setup() failed for port %d\n",
                                                ing_net_port_1);
      return -1;
  }

  BCM_PBMP_CLEAR(pbmp);
  BCM_PBMP_PORT_ADD(pbmp, egr_acc_port_1);
  if (BCM_E_NONE != egress_port_multi_setup(unit, pbmp))
  {
      printf("egress_port_multi_setup() failed for port %d\n",
                                                egr_acc_port_1);
      return -1;
  }

  bshell(unit, "pw start report +all");

  return BCM_E_NONE;
}

/*
 * Verification:
 */
void
verify(int unit)
{
  char str[512];
    uint64 in_pkt, out_pkt, in_bytes, out_bytes;
  int i;
  bshell(unit, "vlan show");
  bshell(unit, "l2 show");
  bshell(unit, "clear c");

  for(i = 0; i <= 15; i++) {
    snprintf(str, 512, "tx 1 pbm=%d data=0x0000000022220000000000028100%x016080045000082000040003F1165B7C0A801010A0A0A01D90312b5006EEE32080000000123450000000000BBBB00000000AAAA810000150800450000500001000040117497020202020101010100350035003C32F674657374746573747465737474657374746573747465737474657374746573747465737474657374746573747465737474657374; sleep quiet 1", ing_net_port_1, i);
    printf ("%s\n", str);
    bshell(unit, str);
  }
  bshell(unit, "show c");

  bshell(unit, "l2 show");

  /* Dump the Configured VPN & VP's*/
  show_vxlan_vtep_config(unit);

  printf("\n******Port stats check******\n");

  printf("--------Network port (%d) stats--------\n", ing_net_port_1);
  COMPILER_64_ZERO(in_pkt);
  COMPILER_64_ZERO(in_bytes);
  BCM_IF_ERROR_RETURN(bcm_stat_get(unit, ing_net_port_1,
                                   snmpDot1dTpPortInFrames, &in_pkt));
  BCM_IF_ERROR_RETURN(bcm_stat_get(unit, ing_net_port_1,
                                   snmpIfInOctets, &in_bytes));
  printf("Rx : %d packets / %d bytes\n", COMPILER_64_LO(in_pkt),
                                         COMPILER_64_LO(in_bytes));


  printf("--------Access port (%d) stats--------\n", egr_acc_port_1);
  COMPILER_64_ZERO(out_pkt);
  COMPILER_64_ZERO(out_bytes);
  BCM_IF_ERROR_RETURN(bcm_stat_sync_get(unit, egr_acc_port_1,
                                   snmpDot1dTpPortOutFrames, &out_pkt));
  BCM_IF_ERROR_RETURN(bcm_stat_sync_get(unit, egr_acc_port_1,
                                   snmpIfOutOctets, &out_bytes));
  printf("Tx : %d packets / %d bytes\n", COMPILER_64_LO(out_pkt),
                                         COMPILER_64_LO(out_bytes));
  if (COMPILER_64_LO(out_pkt) != 16) {
      printf("Packet verify failed. Expected out packet 16 but get %d\n",
                                         COMPILER_64_LO(out_pkt));
      return -1;
  }

  return;
}

/* Create vlan and add port to vlan */
int
vlan_create_add_port(int unit, int vid, int port)
{
  bcm_pbmp_t pbmp, upbmp;

  BCM_IF_ERROR_RETURN(bcm_vlan_create(unit, vid));

    /* Set port default vlan id */
    BCM_IF_ERROR_RETURN(bcm_port_untagged_vlan_set(unit, port, vid));

  BCM_PBMP_CLEAR(pbmp);
  BCM_PBMP_CLEAR(upbmp);
  BCM_PBMP_PORT_ADD(pbmp, port);
  return bcm_vlan_port_add(unit, vid, pbmp, upbmp);
}

int
vxlan_system_config(int unit, vxlan_cfg_t *vxlan_cfg)
{
  printf("Configure Vxlan Global Configuration.\n");
  BCM_IF_ERROR_RETURN(bcm_vlan_control_set(unit, bcmVlanTranslate, TRUE));

  return BCM_E_NONE;
}


int
vxlan_access_port_config(int unit, int port_acc, bcm_gport_t gport_acc)
{
  int rv;
  int egr_map_id;

  printf("Configure Vxlan Access Port Configuration.\n");

  BCM_IF_ERROR_RETURN(bcm_port_tpid_set(unit, port_acc, 0x8100));
  BCM_IF_ERROR_RETURN(bcm_port_inner_tpid_set(unit, port_acc, 0x9100));

  BCM_IF_ERROR_RETURN(bcm_vlan_control_port_set(unit, port_acc,
        bcmVlanTranslateIngressEnable,
        TRUE));

  BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, gport_acc,
        bcmPortControlVxlanEnable,
        FALSE));
  BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, gport_acc,
        bcmPortControlVxlanTunnelbasedVnId,
        FALSE));

  /*Configure Egress QOS MAP */
  printf("Creating  Access QOS configuration.\n");
  rv=create_qos_egress_dot1p_map(unit,BCM_QOS_MAP_L2|BCM_QOS_MAP_EGRESS,&egr_map_id);
  if (BCM_FAILURE(rv)) {
    printf("\nError executing create_qos_dot1p_map for Access Port: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  /*Attach Egress QOS MAP */
  printf("Egress Qos map :%d.\n",egr_map_id);
  rv = bcm_qos_port_map_set(unit, gport_acc, -1, egr_map_id);
  if (BCM_FAILURE(rv)) {
    printf("\nError  bcm_qos_port_map_set for Access Port: %s.\n", bcm_errmsg(rv));
    return rv;
  }



  return BCM_E_NONE;
}

int
vxlan_network_port_config(int unit, int port_net, bcm_gport_t gport_net)
{
  printf("Configure Vxlan Network Port Configuration.\n");

  BCM_IF_ERROR_RETURN(bcm_port_tpid_set(unit, port_net, 0x8100));
  BCM_IF_ERROR_RETURN(bcm_port_inner_tpid_set(unit, port_net, 0x9100));

  BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, gport_net,
                                             bcmPortControlVxlanEnable, TRUE));
  BCM_IF_ERROR_RETURN(bcm_port_control_set(unit, gport_net,
                                             bcmPortControlVxlanTunnelbasedVnId,
                                             FALSE));


  return BCM_E_NONE;
}

/* Create L3 interface */
int
create_l3_interface(int unit, int flags, bcm_mac_t local_mac, int vid,
                    bcm_if_t *intf_id, int intf_flags)
{
  bcm_l3_intf_t l3_intf;
  bcm_error_t   rv=BCM_E_NONE;

  /* L3 interface and egress object for access */
  bcm_l3_intf_t_init(&l3_intf);
  sal_memcpy(l3_intf.l3a_mac_addr, local_mac, sizeof(local_mac));
  l3_intf.l3a_flags      |= flags;
  l3_intf.l3a_intf_flags |= intf_flags;
  l3_intf.l3a_vid         = vid;
  rv = bcm_l3_intf_create(unit, &l3_intf);
  *intf_id = l3_intf.l3a_intf_id;

  return rv;
}

/* Create EGRESS Object */
int
vxlan_create_egr_obj(int unit, uint32 flag, int l3_if, bcm_mac_t nh_mac,
                     bcm_gport_t gport, int vid, bcm_if_t *egr_obj_id)
{
  bcm_l3_egress_t l3_egress;

  bcm_l3_egress_t_init(&l3_egress);
  sal_memcpy(l3_egress.mac_addr,  nh_mac, sizeof(nh_mac));
  l3_egress.flags2 |= flag;
  l3_egress.intf    = l3_if;
  l3_egress.vlan    = vid;
  l3_egress.port    = gport;
  return bcm_l3_egress_create(unit, 0, &l3_egress, egr_obj_id);
}

int
create_vxlan_vpn(int unit, vxlan_cfg_t *vxlan_cfg)
{
  bcm_flow_vpn_config_t vpn_info;
  bcm_multicast_t       bc_group=0;
  bcm_error_t           rv=BCM_E_NONE;

  printf("Create Multicast group for UUC/MC/BC.\n");
  rv = bcm_multicast_create(unit, BCM_MULTICAST_TYPE_FLOW, &bc_group);
  if (BCM_FAILURE(rv)) {
    printf("\nError in multicast create: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  printf("Create Flow VPN.\n");
  bcm_flow_vpn_config_t_init (&vpn_info);
  vpn_info.flags                   = BCM_FLOW_VPN_ELAN |
                                       BCM_FLOW_VPN_WITH_ID;
  vpn_info.broadcast_group         = bc_group;
  vpn_info.unknown_unicast_group   = bc_group;
  vpn_info.unknown_multicast_group = bc_group;
  BCM_IF_ERROR_RETURN(bcm_flow_vpn_create(unit, vxlan_cfg->vxlan_vpn,
                                            &vpn_info));
  vxlan_cfg->bc_group=bc_group;

  return BCM_E_NONE;
}

int
create_vxlan_vp(int unit, bcm_vpn_t vpn, uint32 flags, bcm_gport_t *vp)
{
  bcm_flow_port_t  flow_port;
  bcm_error_t      rv=BCM_E_NONE;
  int ing_map_id=0;

  if(flags & BCM_FLOW_PORT_NETWORK){
    /*Configure QOS MAP */
    printf("Creating Nw Port Ingress Qos configuration\n");
    rv=create_qos_ingress_dot1p_map(unit, BCM_QOS_MAP_L2 | BCM_QOS_MAP_INGRESS, &ing_map_id);
    if (BCM_FAILURE(rv)) {
      printf("\nError executing create_qos_dot1p_map for Nw Port: %s.\n", bcm_errmsg(rv));
      return rv;
    }

  }

  printf("Create Flow VP.\n");
  bcm_flow_port_t_init(&flow_port);
  flow_port.flags = flags;
  rv = bcm_flow_port_create(unit, vpn, &flow_port);
  if (BCM_FAILURE(rv)) {
    printf("\nbcm_flow_port_create() failed: %s\n", bcm_errmsg(rv));
    return rv;
  }

  rv = bcm_vlan_control_port_set(unit, flow_port.flow_port_id, bcmVlanPortUseOuterPri, 1);
  if (BCM_FAILURE(rv)) {
    printf("\nbcm_vlan_control_port_set() failed: %s\n", bcm_errmsg(rv));
    return rv;
  }

  *vp = flow_port.flow_port_id;

  /*Attach ingress QOS MAP */
  printf("ingress Qos map :%d.\n",ing_map_id);
  rv = bcm_qos_port_map_set(unit, ing_net_gport_1, ing_map_id, -1);
  if (BCM_FAILURE(rv)) {
    printf("\nError  bcm_qos_port_map_set for network Port: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  return BCM_E_NONE;
}

int
vxlan_flow_match_add(int unit, bcm_flow_match_config_t match_info)
{
  bcm_error_t rv=BCM_E_NONE;

  rv = bcm_flow_match_add(unit, &match_info, 0, NULL);
  if (BCM_FAILURE(rv)) {
    printf("\nbcm_flow_match_add() failed: %s\n", bcm_errmsg(rv));
    return rv;
  }
  return rv;
}

int
vxlan_flow_port_encap_set(int unit, bcm_flow_port_encap_t peinfo)
{
  bcm_error_t rv=BCM_E_NONE;

  rv =  bcm_flow_port_encap_set(unit, &peinfo, 0, NULL);
  if (BCM_FAILURE(rv)) {
    printf("\nAccess: bcm_flow_port_encap_set() failed: %s\n",
                                                  bcm_errmsg(rv));
    return rv;
  }
  return rv;
}

/* Static L2MC entry for forwarding */
int
add_l2_mc_entry(int unit, bcm_mac_t mac, bcm_vpn_t vpn_id,
                bcm_multicast_t mc_group)
{
    bcm_l2_addr_t l2_addr;

    bcm_l2_addr_t_init(&l2_addr, mac, vpn_id);
    l2_addr.flags |= BCM_L2_STATIC | BCM_L2_MCAST;
    l2_addr.l2mc_group = mc_group;
    return bcm_l2_addr_add(unit, &l2_addr);
}

int
add_to_l2_table(int unit, bcm_mac_t mac, bcm_vpn_t vpn_id, int port)
{
  bcm_l2_addr_t l2_addr;

  bcm_l2_addr_t_init(&l2_addr, mac, vpn_id);
  l2_addr.flags |= BCM_L2_STATIC;
  l2_addr.port   = port;
  return bcm_l2_addr_add(unit, &l2_addr);
}

int
config_vxlan_access(int unit, vxlan_cfg_t *vxlan_cfg,
                    vxlan_acc_cfg_t *vxlan_acc, bcm_gport_t *acc_flow_port,
                    bcm_flow_handle_t flow_handle)
{
  /* Access Configuartion variables */
  bcm_flow_match_config_t match_info;
  bcm_vlan_action_set_t   vlan_action;
  bcm_flow_port_encap_t   peinfo;
  bcm_error_t             rv=BCM_E_NONE;
  bcm_port_t              phy_port;

  rv = bcm_port_local_get(unit, vxlan_acc->phy_Gport, &(phy_port));
  if (BCM_FAILURE(rv)) {
    printf("\nError in getting LocalPort: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  /* Configure ingress port group */
  BCM_IF_ERROR_RETURN(bcm_port_class_set(unit, phy_port, bcmPortClassIngress,
                                         vxlan_acc->port_class));

  /* Port must be added to VPN to pass membership check */
  BCM_IF_ERROR_RETURN(bcm_vlan_gport_add(unit, vxlan_cfg->vxlan_vpn,
                                         vxlan_acc->phy_Gport, 0));

  printf("Configure L2 Learning property on the access port \n");
  rv = bcm_port_learn_set(unit, phy_port, BCM_PORT_LEARN_ARL |
                                          BCM_PORT_LEARN_CPU |
                                          BCM_PORT_LEARN_FWD);
  if (BCM_FAILURE(rv)) {
       printf("\n Error in configuring L2 Learning property on the access VP: %s.\n",
                                           bcm_errmsg(rv));
       return rv;
  }

  printf("Configure VLAN \n");
  rv = vlan_create_add_port(unit, vxlan_acc->acc_vlan, phy_port);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring vlan: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  rv = vxlan_access_port_config(unit, phy_port, vxlan_acc->phy_Gport);
  if (BCM_FAILURE(rv)) {
    printf("\nError in access config: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  printf("Create Access Flow Port (VP).\n");
  rv = create_vxlan_vp(unit, vxlan_cfg->vxlan_vpn, 0, acc_flow_port);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring access vp: %s.\n", bcm_errmsg(rv));
    return rv;
  }
  vxlan_acc->acc_gport=(*acc_flow_port);

  printf("Access SVP assignment \n");
  bcm_flow_match_config_t_init(&match_info);
  match_info.flow_handle = flow_handle;
  match_info.criteria    = BCM_FLOW_MATCH_CRITERIA_PORT;
  match_info.flow_port   = *acc_flow_port;
  match_info.port        = vxlan_acc->phy_Gport;
  match_info.valid_elements = (BCM_FLOW_MATCH_PORT_VALID |
                           BCM_FLOW_MATCH_FLOW_PORT_VALID);
  rv = vxlan_flow_match_add(unit, match_info);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring access flow match: %s.\n",
                                                  bcm_errmsg(rv));
    return rv;
  }

  printf("VPN assignment Incoming Port -> VPN \n");

  bcm_vlan_action_set_t_init(&vlan_action);
  rv = bcm_vlan_port_default_action_get(unit, vxlan_acc->phy_Gport,
                                        &vlan_action);
  if (BCM_FAILURE(rv)) {
      printf("\nError in bcm_vlan_port_default_action_get(): %s.\n",
                                        bcm_errmsg(rv));
      return rv;
  }

  vlan_action.forwarding_domain = vxlan_cfg->vxlan_vpn;
  rv =  bcm_vlan_port_default_action_set(unit, vxlan_acc->phy_Gport,
                                         vlan_action);
  if (BCM_FAILURE(rv)) {
      printf("\nError executing bcm_port_untagged_vlan_set(): %s.\n",
                                         bcm_errmsg(rv));
      return rv;
  }

  /*Configure ING_L2_IIF_TABLE.VLAN_TO_VFI_MAPPING_ENABLE to 0*/
  rv = bcm_port_control_set(unit, vxlan_acc->phy_Gport,
                            bcmPortControlTrustIncomingVlan, 0);
  if (BCM_FAILURE(rv)) {
      printf("\nError executing bcm_port_control_set(): %s.\n",
                                        bcm_errmsg(rv));
      return rv;
  }

  return BCM_E_NONE;
}

int
config_vxlan_tunnel(int unit, vxlan_cfg_t *vxlan_cfg,
                    vxlan_net_cfg_t *vxlan_net, bcm_gport_t net_flow_port,
                    bcm_flow_handle_t flow_handle)
{
  /* Tunnel Configuration variables */
  bcm_flow_tunnel_terminator_t ttinfo;
  bcm_flow_tunnel_initiator_t  tiinfo;
  bcm_error_t                  rv=BCM_E_NONE;

  printf("Tunnel_init: Create Flow Tunnel Initiator.\n");
  bcm_flow_tunnel_initiator_t_init(&tiinfo);
  tiinfo.flow_handle = flow_handle;
  tiinfo.flow_port   = net_flow_port;
  tiinfo.type        = bcmTunnelTypeVxlan;
  tiinfo.sip         = vxlan_net->local_ip;
  tiinfo.dip         = vxlan_net->remote_ip;
  tiinfo.ttl         = 0x3f;
  tiinfo.udp_dst_port = vxlan_cfg->udp_dp;
  tiinfo.valid_elements = BCM_FLOW_TUNNEL_INIT_DIP_VALID |
                        BCM_FLOW_TUNNEL_INIT_SIP_VALID |
                        BCM_FLOW_TUNNEL_INIT_UDP_DPORT_VALID |
                        BCM_FLOW_TUNNEL_INIT_TTL_VALID;
  rv = bcm_flow_tunnel_initiator_create(unit, &tiinfo, 0,NULL);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring tunnel: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  printf("Tunnel_term: Create Flow Tunnel Terminator.\n");
  bcm_flow_tunnel_terminator_t_init(&ttinfo);
  ttinfo.flow_handle    = flow_handle;
  ttinfo.valid_elements = BCM_FLOW_TUNNEL_TERM_DIP_VALID;
  ttinfo.dip            = vxlan_net->local_ip;
  ttinfo.type           = bcmTunnelTypeVxlan;
  ttinfo.flags |= BCM_TUNNEL_TERM_USE_OUTER_QOS;
  rv = bcm_flow_tunnel_terminator_create(unit, &ttinfo, 0, NULL);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring tunnel: %s.\n", bcm_errmsg(rv));
    return rv;
  }
  return BCM_E_NONE;
}

int
config_vxlan_network(int unit, vxlan_cfg_t *vxlan_cfg,
                     vxlan_net_cfg_t *vxlan_net, bcm_gport_t *net_flow_port,
                     bcm_flow_handle_t flow_handle)
{
  /* Network Configuartion variables */
  bcm_flow_match_config_t match_info;
  bcm_flow_encap_config_t einfo;
  bcm_flow_port_encap_t   peinfo;
  bcm_error_t             rv = BCM_E_NONE;
  bcm_port_t              phy_port;
  bcm_if_t                net_intf_id;
  bcm_if_t                net_egr_id;
  uint32                  flags=0;

  rv = bcm_port_local_get(unit, vxlan_net->phy_Gport, &(phy_port));
  if (BCM_FAILURE(rv)) {
    printf("\nError in getting LocalPort: %s.\n", bcm_errmsg(rv));
    return rv;
  }

    /* Port must be added to VPN to pass membership check */
    BCM_IF_ERROR_RETURN(bcm_vlan_gport_add(unit, vxlan_cfg->vxlan_vpn,
                                           vxlan_net->phy_Gport, 0));

  rv = vlan_create_add_port(unit, vxlan_net->net_vlan, phy_port);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring vlan: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  rv = vxlan_network_port_config(unit, phy_port, vxlan_net->phy_Gport);
  if (BCM_FAILURE(rv)) {
    printf("\nError in network config: %s.\n", bcm_errmsg(rv));
    return rv;
  }


  printf("Create network L3 interface\n");
  rv = create_l3_interface(unit, 0, vxlan_net->net_local_mac,
                             vxlan_net->net_vlan, &net_intf_id,
                             BCM_L3_INTF_UNDERLAY);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring l3 interface: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  printf("Create network L3 Egress object.\n");
  rv = vxlan_create_egr_obj(unit, BCM_L3_FLAGS2_UNDERLAY, net_intf_id,
                              vxlan_net->net_remote_mac, vxlan_net->phy_Gport,
                              vxlan_net->net_vlan, &net_egr_id);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring egress obj: %s.\n", bcm_errmsg(rv));
    return rv;
  }


  printf("Create Network Flow Port.\n");
    flags = BCM_FLOW_PORT_NETWORK;
  rv = create_vxlan_vp(unit, vxlan_cfg->vxlan_vpn, flags, net_flow_port);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring network vp: %s.\n", bcm_errmsg(rv));
    return rv;
  }
  vxlan_net->nw_gport=*net_flow_port;

  printf("Network; Set Encapsulation. VP=>egress-obj{Device,Port}.\n");
  bcm_flow_port_encap_t_init(&peinfo);
  peinfo.flow_handle    = flow_handle;
  peinfo.dvp_group      = vxlan_net->dvp_group_id;
  peinfo.flow_port      = *net_flow_port;
  peinfo.valid_elements = BCM_FLOW_PORT_ENCAP_DVP_GROUP_VALID |
                        BCM_FLOW_PORT_ENCAP_EGRESS_IF_VALID;
  peinfo.egress_if      = net_egr_id;
  rv = vxlan_flow_port_encap_set(unit, peinfo);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring network encap: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  printf("Network: encap add, VFI-->VNID\n");
  bcm_flow_encap_config_t_init(&einfo);
  einfo.flow_handle    = flow_handle;
  einfo.criteria       = BCM_FLOW_ENCAP_CRITERIA_VFI_DVP_GROUP;
  einfo.dvp_group      = vxlan_net->dvp_group_id;
  einfo.vnid           = vxlan_net->vxlan_vnid;
  einfo.vpn            = vxlan_cfg->vxlan_vpn;
  einfo.valid_elements = BCM_FLOW_ENCAP_VNID_VALID |
                       BCM_FLOW_ENCAP_VPN_VALID |
                           BCM_FLOW_ENCAP_DVP_GROUP_VALID;
  rv = bcm_flow_encap_add(unit, &einfo, 0, NULL);
    if (BCM_FAILURE(rv)) {
        printf("\nNetwork: bcm_flow_encap_add() failed: %s\n", bcm_errmsg(rv));
        return rv;
  }

  printf("Network: Configure match condition to derive VPN (Match: {VN_ID}, Derive: VFI (VPN))\n");
  bcm_flow_match_config_t_init(&match_info);
  match_info.flow_handle    = flow_handle;
  match_info.criteria       = BCM_FLOW_MATCH_CRITERIA_VN_ID;
  match_info.vpn            = vxlan_cfg->vxlan_vpn;
  match_info.vnid           = vxlan_net->vxlan_vnid;
  match_info.valid_elements = BCM_FLOW_MATCH_VPN_VALID |
                            BCM_FLOW_MATCH_VNID_VALID;
  rv = vxlan_flow_match_add(unit, match_info);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring network flow match: %s.\n",
                                                  bcm_errmsg(rv));
    return rv;
  }

  printf("Network: Add flow match (match: SIP => network SVP)\n");
  bcm_flow_match_config_t_init(&match_info);
  match_info.flow_handle    = flow_handle;
  match_info.criteria       = BCM_FLOW_MATCH_CRITERIA_SIP;
  match_info.sip            = vxlan_net->remote_ip;
  match_info.flow_port      = *net_flow_port;
  match_info.valid_elements = BCM_FLOW_MATCH_SIP_VALID |
                            BCM_FLOW_MATCH_FLOW_PORT_VALID;
  rv = vxlan_flow_match_add(unit, match_info);
  if (BCM_FAILURE(rv)) {
    printf("\nError in configuring network flow match: %s.\n",
                                                  bcm_errmsg(rv));
    return rv;
  }

  return BCM_E_NONE;
}

bcm_error_t
config_vxlan_ipv4_vtep(int unit)
{
    bcm_l2_station_t   l2_station;
  bcm_error_t        rv = BCM_E_NONE;
    int                station_id;

  /* VPN Configuration variables */
  vxlan_cfg_t vxlan_cfg = {
    0x12b5,
    0x8064,
    0,
    0
  };

  vxlan_acc_cfg_t vxlan_acc = {
    egr_acc_gport_1,     /* gPort */
    21,                  /* vlan */
    5,                   /* Inner VLAN */
    "00:00:00:00:11:11", /* local mac */
    "00:00:00:00:bb:bb", /* remote mac */
    "01:00:5E:01:01:01", /* remote MC mac */
    0,
    33
  };

  vxlan_net_cfg_t vxlan_net = {
    ing_net_gport_1,     /* gPort */
    22,                  /* vlan */
    "00:00:00:00:22:22", /* local mac */
    "00:00:00:00:00:02", /* remote mac */
    0xC0A80101,          /* 192.168.1.1 remote IP*/
    0xe1020101,          /* 225.2.1.1 remote MC IP*/
    0x12345,             /* vnid */
    0x0a0a0a01,          /* 10.10.10.1 local IP*/
    0xffff,
    0,
    0xBC2
  };


  /* flow API */
  bcm_flow_handle_t flow_handle;
  bcm_gport_t       acc_flow_port;
  bcm_gport_t       net_flow_port;

  rv = vxlan_system_config(unit, &vxlan_cfg);
  if (BCM_FAILURE(rv)) {
    printf("\nError in global setting: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  printf("Get flow-handler for Classic_Vxlan\n");
  rv = bcm_flow_handle_get(unit, "CLASSIC_VXLAN", &flow_handle);
  if (BCM_FAILURE(rv)) {
    printf("\nError in getting flow handle: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  rv = create_vxlan_vpn(unit, &vxlan_cfg);
  if (BCM_FAILURE(rv)) {
    printf("\nError in vpn create: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  printf("Configure known multicast group\n");
  rv = bcm_multicast_create(unit, BCM_MULTICAST_TYPE_FLOW,
                            vxlan_cfg.mc_group);
  if (BCM_FAILURE(rv)) {
      printf("\nError in multicast create: %s.\n", bcm_errmsg(rv));
      return rv;
  }

  rv = config_vxlan_access(unit, &vxlan_cfg, &vxlan_acc, &acc_flow_port,
                             flow_handle);
  if (BCM_FAILURE(rv)) {
    printf("\nError in access config: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  rv = config_vxlan_network(unit, &vxlan_cfg, &vxlan_net, &net_flow_port,
                              flow_handle);
  if (BCM_FAILURE(rv)) {
    printf("\nError in network config: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  rv = config_vxlan_tunnel(unit, &vxlan_cfg, &vxlan_net, net_flow_port,
                             flow_handle);
  if (BCM_FAILURE(rv)) {
    printf("\nError in tunnel config: %s.\n", bcm_errmsg(rv));
    return rv;
  }

  /* Payload switch */
  printf("Network-to-Access: Add payload-Unicast-mac Address => Access-flow-port (VP).\n");
  rv = add_to_l2_table(unit, vxlan_acc.acc_remote_mac, vxlan_cfg.vxlan_vpn,
                       egr_acc_port_1);
  if (BCM_FAILURE(rv)) {
      printf("\nError in l2 entry config: %s.\n", bcm_errmsg(rv));
      return rv;
  }

  printf("Network-to-Access: L2 station add \n");
  bcm_l2_station_t_init(&l2_station);
  sal_memcpy(l2_station.dst_mac, vxlan_net.net_local_mac,
             sizeof(vxlan_net.net_local_mac));
  l2_station.dst_mac_mask = "ff:ff:ff:ff:ff:ff";
  rv = bcm_l2_station_add(unit, &station_id, &l2_station);
  if (BCM_FAILURE(rv)) {
      printf("\nError in l2 station add: %s.\n", bcm_errmsg(rv));
      return rv;
  }

  return BCM_E_NONE;
}
int
vpn_traverse(int unit,bcm_vpn_t vpn, bcm_flow_vpn_config_t *info, void *data)
{
    int             maxArr=20;
    bcm_flow_port_t flow_portArr[maxArr];
    int             count=0, iter=0;

    printf("\n Vpn :%d \n",vpn);
    printf("\n VpnInfo : \n");
    print *info;
    BCM_IF_ERROR_RETURN(bcm_flow_port_get_all(unit, vpn, maxArr, flow_portArr,
                                              &count));

    printf("\n Flow Ports %d\n",count);
    for(iter=0;(iter<count) && (iter < maxArr);++iter)
    {
        print flow_portArr[iter];
    }
}

bcm_error_t
show_vxlan_vtep_config(int unit)
{
  int user_data;

  bcm_flow_vpn_traverse(unit, vpn_traverse, &user_data);
  return 0;
}

bcm_error_t
create_qos_ingress_dot1p_map(int unit ,uint32 qos_flags,int *qos_map_id)
{
    bcm_qos_map_t map;
    int rv, pri, cfi;

    rv = bcm_qos_map_create(unit, qos_flags, qos_map_id);
    if (BCM_FAILURE(rv)) {
      printf("\nError executing bcm_qos_map_create with flags: 0x%s: %s.\n", bcm_errmsg(rv),qos_flags);
      return rv;
    }

    for (pri = 0; pri <= 7; pri++) {
      for (cfi = 0; cfi <=1 ; cfi++) {
        bcm_qos_map_t_init(&map);
        map.pkt_pri = pri;
        map.pkt_cfi = cfi;
        map.int_pri = pri;
        if (cfi == 0) {
          map.color = bcmColorGreen;
        } else {
          map.color = bcmColorRed;
        }
        rv = bcm_qos_map_add(unit, qos_flags, &map, *qos_map_id);
        if (rv != BCM_E_NONE) {
          printf("bcm_qos_map_add() error , rv=%s\n", bcm_errmsg(rv));
          return rv;
        }
      }
    }
    return BCM_E_NONE;
}

bcm_error_t
create_qos_egress_dot1p_map(int unit ,uint32 qos_flags,int *qos_map_id)
{
  /*Configure QOS MAP */
    bcm_qos_map_t map;
    int rv, pri, color;

    rv = bcm_qos_map_create(unit, qos_flags, qos_map_id);
    if (BCM_FAILURE(rv)) {
      printf("\nError executing bcm_qos_map_create with flags: 0x%s: %s.\n", bcm_errmsg(rv),qos_flags);
      return rv;
    }
    for (pri = 0; pri <= 7; pri++) {
      for (color = bcmColorGreen; color <= bcmColorRed ; color++) {
        bcm_qos_map_t_init(&map);
        map.int_pri = pri;
        map.color = color;
        map.pkt_pri = pri;
        if (bcmColorRed == color) {
          map.pkt_cfi = 1;
        } else if (bcmColorGreen == color) {
          map.pkt_cfi = 0;
        } else if (bcmColorYellow == color) {
          continue;
        }
        rv = bcm_qos_map_add(unit, qos_flags, &map, *qos_map_id);
        if (rv != BCM_E_NONE) {
          printf("bcm_qos_map_add() error , rv=%s\n", bcm_errmsg(rv));
          return rv;
        }
      }
    }
    return BCM_E_NONE;
}

/*
 * execute:
 *  This function does the following
 *  a) test setup
 *  b) actual configuration (Done in config_vxlan_ipv4_vtep())
 *  c) demonstrates the functionality(done in verify()).
 */
bcm_error_t
execute(void)
{
  bcm_error_t rv;
  int         unit = 0;
  print "attach; version \n";
  bshell(unit, "attach; version");

  print "dump sw config \n";
  bshell(unit, "dump sw config");

  print "bsh -c \"config\" \n";
  bshell(unit, "bsh -c 'config'");

  print "lt traverse -l DEVICE_CONFIG \n";
  bshell(unit, "bsh -c 'lt traverse -l DEVICE_CONFIG'");
  print "~~~ #1) test_setup(): ** start **";
  if (BCM_FAILURE((rv = test_setup(unit)))) {
    printf("test_setup() failed.\n");
    return -1;
  }
  print "~~~ #1) test_setup(): ** end **";

  print "~~~ #2) config_vxlan_ipv4_vtep(): ** start **";
  if (BCM_FAILURE((rv = config_vxlan_ipv4_vtep(unit)))) {
    printf("config_vxlan_ipv4_vtep() failed.\n");
    return -1;
  }
  print "~~~ #2) config_vxlan_ipv4_vtep(): ** end **";

  print "~~~ #3) verify(): ** start **";
  verify(unit);
  print "~~~ #3) verify(): ** end **";

  return BCM_E_NONE;
}

const char *auto_execute = (ARGC == 1) ? ARGV[0] : "YES";
if (!sal_strcmp(auto_execute, "YES")) {
  print "execute(): Start";
  print execute();
  print "execute(): End";
}
