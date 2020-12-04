/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

/*
 * Feature  : Vxlan Bridging , IPv4 access to network trunk ports Flow
 *
 * Usage    : BCM.0> cint TD4_HSDK_VXLAN_v4_acc_to_net_UC_trunk.c
 *
 * config   : bcm56880_a0-generic-32x400.config.yml 
 *
 * Log file : TD4_HSDK_VXLAN_v4_acc_to_net_UC_trunk_log.txt
 *
 * Test Topology :
 *
 *                                +----------------------+  VLAN=22   egress_port[0]
 *                                |                      |           +------------------+  Underlay+NextHop
 *                                |                      |Trunk=3    |egress_port[1]         +---+
 * SMAC 00::bb:bb                 |                      +------------------------------+    |   |
 *          +---+          VLAN=21|                      |00::22:22  |egress_port[2]         +---+
 * Host(acc)|   +-----------------+      Trident4        |           +------------------+    00::02
 *          +---+    ingress_port |                      |           |egress_port[3]
 *                                |                      |           +------------------+
 *                                |                      |           |egress_port[4]
 *                                |                      |           +------------------+
 *                                |                      |
 *                                |                      |
 *                                |                      |
 *                                +----------------------+
 * Summary:
 * ========
 * Cint example to demonstrate VxLAN Bridging configuration for tunnel Initiation -
 *             - access to network, with network port being a trunk (encap flow)
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
 *     Note: IFP rule is meant for a verification purpose and is not part of the feature configuration.
 *
 *   2) Step2 - Configuration (Done in config_vxlan()):
 *   =========================================================
 *     a) Configure a VxLAN Bridging configuration.
 *        This does the necessary configurations of vxlan global settings, vlan,
 *        access and network port setting, tunnel setup, interface and next hop.
 *
 *   3) Step3 - Verification (Done in verify()):
 *   ===========================================
 *     a) Check the configurations by 'vlan show', 'l2 show', 'trunk show'
 *
 *     b) Transmit 7 known unicast packets. The contents of the packets
 *        are printed on screen.
 *
 *     c) Expected Result:
 *     ===================
 *       We can see the tunnel packet on the egress port with the IPv4 encapsulation
 *       and 'show c' to check the Tx/Rx packet stats/counters.
 *       Also, 'show c s' shows the packet distribution among trunk member ports.
 */

/*
Packets:

ACCESS-TO-NETWORK:-
Encap-case: packets sent from ingress_port(access) to egress_port(network)

Ingress Packets: (No. of packets = 7)
======

Header Info

  ###[ Ethernet ]###
    dst= 00:00:00:00:aa:aa
    src= 00:00:00:00:bb:bb
    type= 0x8100
  ###[ 802.1Q ]###
     vlan= 21
     type= 0x800
  ###[ IP ]###
        version= 4
        proto= udp
        src= 1.1.1.1, 1.1.1.2, 1.1.1.3, 1.1.1.6, 1.1.1.7, 1.1.1.10 ,1.1.1.20  <== 7 packets' only changing contents
        dst= 2.2.2.2
  ###[ UDP ]###
          sport= 53
          dport= 54

Ingress Hex Packet:
tx port=1 data=0x00000000AAAA00000000BBBB8100001508004500002E00000000401174BA010101010202020200350036001AB0F8000102030405060708090A0B0C0D0E0F101133CF192C

tx port=1 data=0x00000000AAAA00000000BBBB8100001508004500002E00000000401174B9010101020202020200350036001AB0F7000102030405060708090A0B0C0D0E0F1011975E7DF7

tx port=1 data=0x00000000AAAA00000000BBBB8100001508004500002E00000000401174B8010101030202020200350036001AB0F6000102030405060708090A0B0C0D0E0F1011D621E6E1

tx port=1 data=0x00000000AAAA00000000BBBB8100001508004500002E00000000401174B5010101060202020200350036001AB0F3000102030405060708090A0B0C0D0E0F101196025567

tx port=1 data=0x00000000AAAA00000000BBBB8100001508004500002E00000000401174B4010101070202020200350036001AB0F2000102030405060708090A0B0C0D0E0F1011D77DCE71

tx port=1 data=0x00000000AAAA00000000BBBB8100001508004500002E00000000401174B40101010a0202020200350036001AB0F2000102030405060708090A0B0C0D0E0F1011D77DCE71
    
tx port=1 data=0x00000000AAAA00000000BBBB8100001508004500002E00000000401174B4010101140202020200350036001AB0F2000102030405060708090A0B0C0D0E0F1011D77DCE71



Egress Packet :
======

Header Info

  ###[ Ethernet ]###
    dst= 00:00:00:00:00:02
    src= 00:00:00:00:22:22
    type= 0x8100
  ###[ 802.1Q ]###
     vlan= 22
     type= 0x800
  ###[ IP ]###
     version= 4
     proto= udp
     src= 10.10.10.1
     dst= 192.168.1.1
  ###[ UDP ]###
     sport= 65535
     dport= 8472
  ###[ VXLAN ]###
     flags= Instance
     reserved1= 0
     vni= 0x12345
     reserved2= 0x0
  ###[ Ethernet ]###
                 dst= 00:00:00:00:aa:aa
                 src= 00:00:00:00:bb:bb
                 type= 0x800
  ###[ 802.1Q ]###
     vlan= 21
     type= 0x800
  ###[ IP ]###
        version= 4
        proto= udp
        src= 1.1.1.1, 1.1.1.2, 1.1.1.3, 1.1.1.6, 1.1.1.7 <== 5 packets' contents
        dst= 2.2.2.2
  ###[ UDP ]###

Packet Dump
Egress packet#1 -
data[0000]: {000000000002} {000000002222} 8100 0016
data[0010]: 0800 4500 0064 0000 0000 3f11 a5d5 0a0a
data[0020]: 0a01 c0a8 0101 ffff 2118 0050 0000 0000
data[0030]: 0000 0123 4500 0000 0000 aaaa 0000 0000
data[0040]: bbbb 0800 4500 002e 0000 0000 4011 74ba
data[0050]: 0101 0101 0202 0202 0035 0036 001a b0f8
data[0060]: 0001 0203 0405 0607 0809 0a0b 0c0d 0e0f
data[0070]: 1011 33cf 192c c36b b81f

Egress packet#2 -
data[0000]: {000000000002} {000000002222} 8100 0016
data[0010]: 0800 4500 0064 0001 0000 3f11 a5d4 0a0a
data[0020]: 0a01 c0a8 0101 ffff 2118 0050 0000 0000
data[0030]: 0000 0123 4500 0000 0000 aaaa 0000 0000
data[0040]: bbbb 0800 4500 002e 0000 0000 4011 74b9
data[0050]: 0101 0102 0202 0202 0035 0036 001a b0f7
data[0060]: 0001 0203 0405 0607 0809 0a0b 0c0d 0e0f
data[0070]: 1011 975e 7df7 e707 e61d

Egress packet#3 -
data[0000]: {000000000002} {000000002222} 8100 0016
data[0010]: 0800 4500 0064 0002 0000 3f11 a5d3 0a0a
data[0020]: 0a01 c0a8 0101 ffff 2118 0050 0000 0000
data[0030]: 0000 0123 4500 0000 0000 aaaa 0000 0000
data[0040]: bbbb 0800 4500 002e 0000 0000 4011 74b8
data[0050]: 0101 0103 0202 0202 0035 0036 001a b0f6
data[0060]: 0001 0203 0405 0607 0809 0a0b 0c0d 0e0f
data[0070]: 1011 d621 e6e1 ea03 8450

Egress packet#4 -
data[0000]: {000000000002} {000000002222} 8100 0016
data[0010]: 0800 4500 0064 0003 0000 3f11 a5d2 0a0a
data[0020]: 0a01 c0a8 0101 ffff 2118 0050 0000 0000
data[0030]: 0000 0123 4500 0000 0000 aaaa 0000 0000
data[0040]: bbbb 0800 4500 002e 0000 0000 4011 74b5
data[0050]: 0101 0106 0202 0202 0035 0036 001a b0f3
data[0060]: 0001 0203 0405 0607 0809 0a0b 0c0d 0e0f
data[0070]: 1011 9602 5567 ce6f da52

Egress packet#5 -
data[0000]: {000000000002} {000000002222} 8100 0016
data[0010]: 0800 4500 0064 0004 0000 3f11 a5d1 0a0a
data[0020]: 0a01 c0a8 0101 ffff 2118 0050 0000 0000
data[0030]: 0000 0123 4500 0000 0000 aaaa 0000 0000
data[0040]: bbbb 0800 4500 002e 0000 0000 4011 74b4
data[0050]: 0101 0107 0202 0202 0035 0036 001a b0f2
data[0060]: 0001 0203 0405 0607 0809 0a0b 0c0d 0e0f
data[0070]: 1011 d77d ce71 53db c116

Egress packet#6 -
data[0000]: {000000000002} {000000002222} 8100 0016
data[0010]: 0800 4500 0064 0000 0000 3f11 a5d5 0a0a 
data[0020]: 0a01 c0a8 0101 c000 12b5 0050 0000 0800 
data[0030]: 0000 0123 4500 0000 0000 aaaa 0000 0000 
data[0040]: bbbb 0800 4500 002e 0000 0000 4011 74b4 
data[0050]: 0101 010a 0202 0202 0035 0036 001a b0f2 
data[0060]: 0001 0203 0405 0607 0809 0a0b 0c0d 0e0f 
data[0070]: 1011 d77d ce71 

Egress packet#7 -
data[0000]: {000000000002} {000000002222} 8100 0016
data[0010]: 0800 4500 0064 0000 0000 3f11 a5d5 0a0a 
data[0020]: 0a01 c0a8 0101 c000 12b5 0050 0000 0800 
data[0030]: 0000 0123 4500 0000 0000 aaaa 0000 0000 
data[0040]: bbbb 0800 4500 002e 0000 0000 4011 74b4 
data[0050]: 0101 0114 0202 0202 0035 0036 001a b0f2 
data[0060]: 0001 0203 0405 0607 0809 0a0b 0c0d 0e0f 
data[0070]: 1011 d77d ce71 


*/

/* Reset C interpreter*/
cint_reset();

/**** global constants ****/
const int   IN_PORT_NUM = 1;   // fix
const int   OUT_PORT_NUM = 5;  // 
const int   NO_OF_TRUNK_MEMBERS = OUT_PORT_NUM;

bcm_port_t ingress_port;
bcm_port_t egress_port[OUT_PORT_NUM];


/*
 * This function is written so that hardcoding of port
 * numbers in Cint scripts is removed. This function gives
 * required number of ports
 */
bcm_error_t
portNumbersGet(int unit, int *port_list, int num_ports)
{
    int i = 0, port = 0, rv = 0;
    bcm_port_config_t configP;
    bcm_pbmp_t ports_pbmp;

    rv = bcm_port_config_get(unit, &configP);
    if (BCM_FAILURE(rv)) {
        printf("\nError in retrieving port configuration: %s.\n",bcm_errmsg(rv));
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
 * Creates a Field Group for copying/dropping packets 
 * on a certain ingress port.
 */
    bcm_error_t
field_group_setup(int unit, bcm_field_group_config_t *group_config)
{
    bcm_field_group_config_t_init(group_config);
    BCM_FIELD_QSET_INIT(group_config->qset);
    BCM_FIELD_QSET_ADD(&group_config->qset, bcmFieldQualifyInPort); 
    BCM_FIELD_ASET_ADD(group_config->aset, bcmFieldActionCopyToCpu);   
    BCM_FIELD_ASET_ADD(group_config->aset, bcmFieldActionDrop);
    group_config->mode = bcmFieldGroupModeAuto;

    BCM_IF_ERROR_RETURN(bcm_field_group_config_create(unit, group_config));

    return BCM_E_NONE;
}


/*
 * Configures the port in loopback mode and installs
 * an IFP rule. This IFP rule copies the packets ingressing
 * on the specified port to CPU.
 */
    bcm_error_t
ingress_port_setup(int unit, bcm_port_t port,
                    bcm_field_group_config_t group_config,
                    bcm_field_entry_t *entry)
{
    BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port, BCM_PORT_LOOPBACK_MAC));

    BCM_IF_ERROR_RETURN(bcm_field_entry_create(unit, group_config.group, entry));
    BCM_IF_ERROR_RETURN(bcm_field_qualify_InPort(unit, *entry, port, BCM_FIELD_EXACT_MATCH_MASK));
    BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, *entry, bcmFieldActionCopyToCpu, 0, 0));
    BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, *entry));

    return BCM_E_NONE;
}

/*
 * Configures the port in loopback mode and installs
 * an IFP rule. This IFP rule copies the packets ingressing
 * on the specified set of ports to CPU. Ports are also configured
 * to discard all packets. This is to avoid continuous
 * loopback of the packet.
 */
bcm_error_t
egress_port_setup(int unit, bcm_port_t port,
                    bcm_field_group_config_t group_config,
                    bcm_field_entry_t *entry)
{
    BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port, BCM_PORT_LOOPBACK_MAC));

    BCM_IF_ERROR_RETURN(bcm_field_entry_create(unit, group_config.group, entry));
    BCM_IF_ERROR_RETURN(bcm_field_qualify_InPort(unit, *entry, port, BCM_FIELD_EXACT_MATCH_MASK));
    BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, *entry, bcmFieldActionCopyToCpu, 0, 0));
    BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, *entry, bcmFieldActionDrop, 0, 0));
    BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, *entry));

    return BCM_E_NONE;
}

/*
 * Test Setup:
 * This functions gets the port numbers and sets up ingress and
 * egress ports. Check ingress_port_setup() and egress_port_setup().
 */
    bcm_error_t
test_setup(int unit)
{
    int i;
    int port_list[IN_PORT_NUM + OUT_PORT_NUM];
    bcm_field_group_config_t group_config;
    bcm_field_entry_t entry[IN_PORT_NUM + OUT_PORT_NUM];
    
    if (BCM_E_NONE != portNumbersGet(unit, port_list, IN_PORT_NUM + OUT_PORT_NUM)) {
        printf("portNumbersGet() failed\n");
        return -1;
    }

    if (BCM_E_NONE !=field_group_setup(unit, &group_config)){
        printf("field_group_setup() failed to create field group\n");
        return -1;
    }

    ingress_port = port_list[0];
    if (BCM_E_NONE != ingress_port_setup(unit, ingress_port, group_config, &entry[0])) {
        printf("ingress_port_setup() failed for port %d\n", ingress_port);
            return -1;
    }

    for (i = IN_PORT_NUM; i < (IN_PORT_NUM + OUT_PORT_NUM); i++){   
        egress_port[i - IN_PORT_NUM] = port_list[i];
        if (BCM_E_NONE != egress_port_setup(unit, egress_port[i - IN_PORT_NUM], group_config, &entry[i])) {
            printf("egress_port_setup(port2) failed for port %d\n", egress_port[i - IN_PORT_NUM]);
            return -1;
        }
    }

    bshell(unit, "pw start report +raw +decode");

    return BCM_E_NONE;
}


/************************** VXLAN Sub-Routines ****************************/

/**** global constants ****/
const int   max_vxlan_port_num_per_phy_port = 8;
const int   FLAGS_PROVIDER      = 0x1;
const int   FLAGS_CUSTOMER      = 0x2;
const int   FLAGS_REMOTE_CHIP   = 0x4;
const int   FLAGS_MC_ONLY       = 0x8;

const int   VXLAN_UDP_DST_PORT  = 4789;      // IANA (RFC 7348)

const int   FLAGS_FLOW_IPV6     = 0x1;
const int   FLAGS_FLOW_CLASSIC  = 0x2;

const int   FLAGS_TUNNEL_MC     = 0x1;
const int   FLAGS_TUNNEL_MC_BUD = 0x2;

/* flow API */
bcm_flow_handle_t   flow_handle;
int                 flow_flag;         

/**** Data Structures ****/
struct vxlan_port_s {
    bcm_vpn_t       vpn;    
    bcm_flow_port_t flow_port;    
    int             vid;
    bcm_mac_t       local_mac;
    bcm_mac_t       remote_mac;  
    bcm_if_t        intf_id;    // Required For Tunnel 
    bcm_if_t        egr_id;      
    uint32          vnid; 

    /* Specific for Network port */
    bcm_flow_encap_criteria_t criteria;    
    bcm_ip_t        remote_ip;
    bcm_ip_t        local_ip;    
    bcm_ip6_t       remote_ip6;
    bcm_ip6_t       local_ip6;
    int             ttl;
    uint32          vnid;
    int             dvp_group;
    bcm_ip_t        mcast_ip;
    bcm_ip6_t       mcast_ip6;
    bcm_mac_t       mcast_mac;
    int             mc_tnl_flag;
};


struct vxlan_phy_port_s {
    int             modid;
    int             port_id;
    bcm_gport_t     gport_id;    
    vxlan_port_s    vxlan_port[max_vxlan_port_num_per_phy_port];    
    int             vxlan_port_num;    
    int             flags;
};


/**** Internal Sub-functions ****/

/* Create vlan and add port to vlan */
bcm_error_t
vlan_create_add_port(int unit, int vid, int port)
{
    bcm_pbmp_t pbmp, upbmp;
    bcm_error_t rv = BCM_E_NONE;

    rv = bcm_vlan_create(unit, vid);
    if((rv != BCM_E_NONE) && (rv != BCM_E_EXISTS)) {
        return rv;
    }

    BCM_PBMP_CLEAR(pbmp);
    BCM_PBMP_CLEAR(upbmp);
    BCM_PBMP_PORT_ADD(pbmp, port);  
    return bcm_vlan_port_add(unit, vid, pbmp, upbmp);
}

/* Add L2 Entry */
bcm_error_t
vxlan_l2_add(int unit, bcm_mac_t mac, bcm_vpn_t vpn_id, int port)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_l2_addr_t l2_addr;

    bcm_l2_addr_t_init(&l2_addr, mac, vpn_id);
    l2_addr.flags   = BCM_L2_STATIC;
    l2_addr.port    = port;
    rv = bcm_l2_addr_add(unit, &l2_addr);
    if (BCM_FAILURE(rv)) {
        printf("\nError in adding static L2 entry: %s.\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}

/* Add L2 Station MAC for VXLAN Termination */
bcm_error_t
vxlan_l2_station_add(int unit, bcm_mac_t mac)
{
    bcm_error_t rv = BCM_E_NONE;
    int station_id;
    bcm_l2_station_t l2_station;

    bcm_l2_station_t_init(&l2_station);
    sal_memcpy(l2_station.dst_mac, mac, sizeof(mac));
    l2_station.dst_mac_mask = "ff:ff:ff:ff:ff:ff";
    rv = bcm_l2_station_add(unit, &station_id, &l2_station);
    if (BCM_FAILURE(rv)) {
        printf("\nError in adding L2 station: %s.\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;    
}

/* Create L3 ingress interface */
bcm_error_t
create_l3_ingress_interface(int unit, bcm_vlan_t vid, bcm_if_t *l3_iif)
{
    bcm_error_t             rv = BCM_E_NONE; 
    bcm_l3_ingress_t        l3_ingress; 
    bcm_vlan_control_vlan_t vlan_ctrl;  

    printf("Create network L3 ingress interface\n");
    bcm_l3_ingress_t_init(&l3_ingress);
    l3_ingress.vrf = 0;
    rv = bcm_l3_ingress_create(unit, &l3_ingress, l3_iif);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring L3 ingress interface: %s.\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Config vpn(0x%x) to l3_iif(0x%x) mapping.\n", vid, *l3_iif);
    bcm_vlan_control_vlan_t_init(&vlan_ctrl);
    vlan_ctrl.ingress_if = *l3_iif;
    rv = bcm_vlan_control_vlan_selective_set(unit, vid, BCM_VLAN_CONTROL_VLAN_INGRESS_IF_MASK, &vlan_ctrl);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring vid to l3_iif: %s.\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}


/* Create L3 Egress Interface */
bcm_error_t 
vxlan_l3_intf_create(int unit, bcm_vlan_t vlan, bcm_mac_t mac_addr, int is_net_intf, 
                        bcm_flow_handle_t flow_handle, bcm_if_t * l3_intf_id)
{
    bcm_l3_intf_t l3_interface;

    /* Create L3 Interface */
    bcm_l3_intf_t_init(&l3_interface);
    if (is_net_intf)  {  
        l3_interface.l3a_flags = BCM_L3_ADD_TO_ARL;   
            if (flow_handle)  {  
                l3_interface.flow_handle = flow_handle;         
                l3_interface.l3a_intf_flags  = BCM_L3_INTF_UNDERLAY; 
            }
    }
    sal_memcpy(l3_interface.l3a_mac_addr, mac_addr, sizeof(mac_addr));
    l3_interface.l3a_vid = vlan;
    BCM_IF_ERROR_RETURN(bcm_l3_intf_create(unit, &l3_interface));
    *l3_intf_id = l3_interface.l3a_intf_id;
    
    return BCM_E_NONE;
}

/* Create L3 Egress Object */
bcm_error_t 
vxlan_l3_egress_create(int unit, uint32 flags, uint32 flags2, bcm_if_t l3_if, bcm_mac_t mac_addr, bcm_vlan_t vlan, 
                           bcm_gport_t gport, bcm_flow_handle_t flow_handle, bcm_gport_t flow_port_id, bcm_if_t *egr_obj)
{
    bcm_l3_egress_t             l3_egress;

    bcm_l3_egress_t_init(&l3_egress);
    l3_egress.flags2        = flags2;
    l3_egress.intf          = l3_if;
    l3_egress.flow_handle   = flow_handle;
    sal_memcpy(l3_egress.mac_addr,  mac_addr, sizeof(mac_addr));
    l3_egress.vlan          = vlan;
    l3_egress.port          = gport;
    l3_egress.encap_id      = BCM_GPORT_FLOW_PORT_ID_GET(flow_port_id);   
     
    BCM_IF_ERROR_RETURN(bcm_l3_egress_create(unit, flags , &l3_egress, egr_obj));
    
    return BCM_E_NONE;
}

bcm_error_t 
vxlan_vpn_create(int unit, bcm_multicast_t bc_group, bcm_vpn_t vpn)
{
    bcm_error_t           rv;    
    bcm_flow_vpn_config_t vpn_info;

    bcm_flow_vpn_config_t_init (&vpn_info);
    vpn_info.flags = BCM_FLOW_VPN_ELAN | BCM_FLOW_VPN_WITH_ID;
    vpn_info.broadcast_group         = bc_group;
    vpn_info.unknown_unicast_group   = bc_group;
    vpn_info.unknown_multicast_group = bc_group;
    rv = bcm_flow_vpn_create(unit, &vpn, &vpn_info);
    if (BCM_FAILURE(rv)) { 
        printf("\r\n bcm_vxlan_vpn_create = %s, vpn = %d\n", bcm_errmsg(rv), vpn);  
    } else {
        printf("Creating VXLAN VPN (0x%x)... done!\n", vpn);
    } 
        
    return BCM_E_NONE;
}

bcm_error_t
vxlan_access_port_create(int unit, bcm_vpn_t vpn, vxlan_phy_port_s *vxlan_access_port)
{
    vxlan_port_s            * v_port = &vxlan_access_port->vxlan_port[vxlan_access_port->vxlan_port_num];
    bcm_error_t             rv = BCM_E_NONE;   
    bcm_flow_port_t         flow_port;
    bcm_flow_match_config_t match_info;
    bcm_flow_port_encap_t   peinfo;

    if(BCM_GPORT_IS_TRUNK(vxlan_access_port->gport_id)) {
        bcm_trunk_t tid = BCM_GPORT_TRUNK_GET(vxlan_access_port->gport_id);;
        int member_array_szie = 16;
        int member_count = 0, i;
        bcm_trunk_member_t member_array[member_array_szie]; 

        BCM_IF_ERROR_RETURN(bcm_trunk_get(unit, tid, NULL, member_array_szie, member_array,
                              &member_count));
      
        for (i = 0; i < member_count; i++){
            bcm_port_t port_id = BCM_GPORT_MODPORT_PORT_GET(member_array[i].gport);
            rv = vlan_create_add_port(unit, v_port->vid, port_id);
            if (BCM_FAILURE(rv)) {
                printf("\nError in configuring vlan(port %d): %s.\n", port_id, bcm_errmsg(rv));
                return rv;
            }

            /* Add ports to VPN to pass membership check */
            rv = bcm_vlan_gport_add(unit, vpn, member_array[i].gport, 0);
            if (BCM_FAILURE(rv)) {
                printf("Error in configuring VPN membership check: %s.\n", bcm_errmsg(rv));
                return rv;
            }            
        }   
    } else {
        rv = vlan_create_add_port(unit, v_port->vid, vxlan_access_port->port_id);
        if (BCM_FAILURE(rv)) {
            printf("Error in configuring vlan: %s.\n", bcm_errmsg(rv));
            return rv;
        }

        /* Add ports to VPN to pass membership check */
        rv = bcm_vlan_gport_add(unit, vpn, vxlan_access_port->gport_id, 0);
        if (BCM_FAILURE(rv)) {
            printf("Error in configuring VPN membership check: %s.\n", bcm_errmsg(rv));
            return rv;
        }
    }

    // Create  Access Flow Port (VP).
    bcm_flow_port_t_init(&flow_port);
    rv = bcm_flow_port_create(unit, vpn, &flow_port);
    if (BCM_FAILURE(rv)) {
        printf("\nbcm_flow_port_create() failed: %s\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Creating Access Flow Port (0x%x)... done!\n", flow_port.flow_port_id);
    }

    // Access: VPN assignment, port + outer_VID -> VPN.
    bcm_flow_match_config_t_init(&match_info);
    match_info.criteria       = BCM_FLOW_MATCH_CRITERIA_PORT_GROUP_VLAN;
    match_info.valid_elements = BCM_FLOW_MATCH_PORT_VALID |
                                BCM_FLOW_MATCH_VLAN_VALID | 
                                BCM_FLOW_MATCH_VPN_VALID;
    match_info.port           = (vxlan_access_port->gport_id & 0xff);  // use port id as port group
    match_info.vlan           = v_port->vid;
    match_info.vpn            = vpn;
    rv = bcm_flow_match_add(unit, &match_info, 0, NULL);   
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring access flow match(VPN): %s.\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Creating Access Flow Match for VPN... done!\n");
    }

    // Access: Add flow match (match: port criteria) -> SVP.
    bcm_flow_match_config_t_init(&match_info);
    match_info.criteria         = BCM_FLOW_MATCH_CRITERIA_PORT;
    match_info.port             = vxlan_access_port->gport_id;
    match_info.flow_port        = flow_port.flow_port_id;
    match_info.valid_elements   = BCM_FLOW_MATCH_PORT_VALID |
                                  BCM_FLOW_MATCH_FLOW_PORT_VALID;
    rv = bcm_flow_match_add(unit, &match_info, 0, NULL);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring access flow match(SVP): %s.\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Creating Access Flow Match for SVP... done!\n");
    }
                                     
    v_port->flow_port       = flow_port;
    v_port->vpn             = vpn;   
    vxlan_access_port->vxlan_port_num++;
    
    return BCM_E_NONE;
}    

bcm_error_t
vxlan_network_port_create(int unit, bcm_vpn_t vpn, vxlan_phy_port_s *vxlan_network_port)
{   
    vxlan_port_s            * v_port = &vxlan_network_port->vxlan_port[vxlan_network_port->vxlan_port_num];    
    bcm_error_t             rv = BCM_E_NONE;
    bcm_flow_port_t         flow_port;
    bcm_flow_encap_config_t einfo;
    bcm_flow_match_config_t match_info;
    bcm_flow_port_encap_t   peinfo;
    int  is_ipmc_only = (FLAGS_MC_ONLY == (vxlan_network_port->flags & FLAGS_MC_ONLY));

    if(BCM_GPORT_IS_TRUNK(vxlan_network_port->gport_id)) {
        bcm_trunk_t tid = BCM_GPORT_TRUNK_GET(vxlan_network_port->gport_id);;
        int member_array_szie = 16;
        int member_count = 0, i;
        bcm_trunk_member_t member_array[member_array_szie]; 

        BCM_IF_ERROR_RETURN(bcm_trunk_get(unit, tid, NULL, member_array_szie, member_array,
                              &member_count));
      
        for (i = 0; i < member_count; i++){
            bcm_port_t port_id = BCM_GPORT_MODPORT_PORT_GET(member_array[i].gport);
            rv = vlan_create_add_port(unit, v_port->vid, port_id);
            if (BCM_FAILURE(rv)) {
                printf("\nError in configuring vlan(port %d): %s.\n", port_id, bcm_errmsg(rv));
                return rv;
            }

            /* Add ports to VPN to pass membership check */
            rv = bcm_vlan_gport_add(unit, vpn, member_array[i].gport, 0);
            if (BCM_FAILURE(rv)) {
                printf("Error in configuring VPN membership check: %s.\n", bcm_errmsg(rv));
                return rv;
            }            
        }   
    } else {
        rv = vlan_create_add_port(unit, v_port->vid, vxlan_network_port->port_id);
        if (BCM_FAILURE(rv)) {
            printf("\nError in configuring vlan: %s.\n", bcm_errmsg(rv));
            return rv;
        }

        /* Add ports to VPN to pass membership check */
        rv = bcm_vlan_gport_add(unit, vpn, vxlan_network_port->gport_id, 0);
        if (BCM_FAILURE(rv)) {
            printf("Error in configuring VPN membership check: %s.\n", bcm_errmsg(rv));
            return rv;
        }
    }

    // Create network L3 interface
    rv = vxlan_l3_intf_create(unit, v_port->vid, v_port->local_mac, 1,
                                        ((is_ipmc_only) ? 0 : flow_handle), &v_port->intf_id);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring l3 interface: %s.\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Creating Network Interface (0x%x)... done!\n", v_port->intf_id);
    }

    if (is_ipmc_only) {
        printf("Create Network port for IPMC domain... done!\n");
        return BCM_E_NONE;
    }

    // Create  Network Flow Port.
    bcm_flow_port_t_init(&flow_port);
    flow_port.flags = BCM_FLOW_PORT_NETWORK;
    rv = bcm_flow_port_create(unit, vpn, &flow_port);
    if (BCM_FAILURE(rv)) {
        printf("\nbcm_flow_port_create() failed: %s\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Create Network Flow Port (0x%x)... done!\n", flow_port.flow_port_id);
    }

    // Create network L3 Egress object
    rv = vxlan_l3_egress_create(unit, 0, BCM_L3_FLAGS2_UNDERLAY, v_port->intf_id, 
                                    v_port->remote_mac, v_port->vid,
                                    vxlan_network_port->gport_id, flow_handle,
                                    flow_port.flow_port_id, &v_port->egr_id);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring egress obj: %s.\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Create Network Egress Object (0x%x)... done!\n", v_port->egr_id);
    }

    // Network: encap add, (VFI,DVP) or (VFI)-->VNID
    bcm_flow_encap_config_t_init(&einfo);
    einfo.flow_handle       = flow_handle;
    einfo.criteria          = v_port->criteria;
    einfo.vnid              = v_port->vnid;
    einfo.vpn               = vpn;
    einfo.dvp_group         = v_port->dvp_group;
    einfo.valid_elements    = BCM_FLOW_ENCAP_VNID_VALID |
                              BCM_FLOW_ENCAP_VPN_VALID;
    if (BCM_FLOW_ENCAP_CRITERIA_VFI_DVP_GROUP == 
               (einfo.criteria & BCM_FLOW_ENCAP_CRITERIA_VFI_DVP_GROUP)) {
        einfo.valid_elements |= BCM_FLOW_ENCAP_DVP_GROUP_VALID;      
    } 
    rv = bcm_flow_encap_add(unit, &einfo, 0, NULL);
    if (BCM_FAILURE(rv)) {
        printf("\nNetwork: bcm_flow_encap_add() failed: %s\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Creating Flow Encap... done!\n");
    }

    // Network: Configure match condition to derive VPN (Match: {VN_ID}, Derive: VFI (VPN))
    bcm_flow_match_config_t_init(&match_info);
    match_info.flow_handle    = flow_handle;
    match_info.criteria       = BCM_FLOW_MATCH_CRITERIA_VN_ID;
    match_info.vpn            = vpn;
    match_info.vnid           = v_port->vnid;
    match_info.valid_elements = BCM_FLOW_MATCH_VPN_VALID |
                                BCM_FLOW_MATCH_VNID_VALID;
    rv = bcm_flow_match_add(unit, &match_info, 0, NULL);
    if (BCM_FAILURE(rv)) {
        if (rv != BCM_E_EXISTS) {
            printf("\nError in configuring network flow match: %s.\n", bcm_errmsg(rv));
            return rv;
        } else {
            printf("Warning: Flow Match (VNID 0x%x -> VFI 0x%x) Entry exists!\n", v_port->vnid, vpn);
        }
    } else {
        printf("Adding Flow Match (VNID -> VFI)... done!\n");
    }

    // Network; Set  Encapsulation. VP=>egress-obj{Device,Port}
    bcm_flow_port_encap_t_init(&peinfo);
    peinfo.flow_handle      = flow_handle;
    peinfo.dvp_group        = v_port->dvp_group;;
    peinfo.flow_port        = flow_port.flow_port_id;
    peinfo.egress_if        = v_port->egr_id;
    peinfo.valid_elements   = BCM_FLOW_PORT_ENCAP_DVP_GROUP_VALID |
                              BCM_FLOW_PORT_ENCAP_EGRESS_IF_VALID;
    rv = bcm_flow_port_encap_set(unit, &peinfo, 0, NULL);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring network encap: %s.\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Setting Port Encap... done!\n");
    }

    // Network: Add  flow match (match: SIP => network SVP)
    bcm_flow_match_config_t_init(&match_info);
    match_info.flow_handle      = flow_handle;
    match_info.criteria         = BCM_FLOW_MATCH_CRITERIA_SIP;     
    match_info.flow_port        = flow_port.flow_port_id;
    match_info.valid_elements   = BCM_FLOW_MATCH_FLOW_PORT_VALID;
    if (flow_flag == FLAGS_FLOW_CLASSIC) {
        match_info.sip          = v_port->remote_ip;
        match_info.valid_elements |= BCM_FLOW_MATCH_SIP_VALID;
    } else {      
        match_info.sip6         = v_port->remote_ip6;
        match_info.valid_elements |= BCM_FLOW_MATCH_SIP_V6_VALID;
    }
    rv = bcm_flow_match_add(unit, &match_info, 0, NULL);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring network flow match: %s.\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Adding Flow Match (SIP -> SVP)... done!\n");
    }

    v_port->flow_port           = flow_port;
    v_port->vpn                 = vpn;   
    vxlan_network_port->vxlan_port_num++;
    
    return rv;
}

bcm_error_t 
vxlan_tunnel_create(int unit, vxlan_port_s * v_port)
{      
    bcm_error_t                     rv = BCM_E_NONE;
    bcm_flow_tunnel_initiator_t     tiinfo;
    bcm_flow_tunnel_terminator_t    ttinfo;

    // Tunnel_init: Create  Flow Tunnel Initiator
    bcm_flow_tunnel_initiator_t_init(&tiinfo);
    tiinfo.flow_handle      = flow_handle;
    tiinfo.valid_elements   = BCM_FLOW_TUNNEL_INIT_TTL_VALID;                           
    tiinfo.ttl              = v_port->ttl;
    tiinfo.flow_port        = v_port->flow_port.flow_port_id;
    if (flow_flag == FLAGS_FLOW_CLASSIC) {
        tiinfo.type     = bcmTunnelTypeVxlan;
        tiinfo.sip      = v_port->local_ip;
        if (v_port->mc_tnl_flag) {
            tiinfo.dip  = v_port->mcast_ip;
        } else {
            tiinfo.dip  = v_port->remote_ip;
        }
        tiinfo.valid_elements |= BCM_FLOW_TUNNEL_INIT_DIP_VALID |
                                 BCM_FLOW_TUNNEL_INIT_SIP_VALID;        
    } else {
        tiinfo.type     = bcmTunnelTypeVxlan6;
        tiinfo.sip6     = v_port->local_ip6;
        if (v_port->mc_tnl_flag) {
            tiinfo.dip6 = v_port->mcast_ip6;
        } else {        
            tiinfo.dip6 = v_port->remote_ip6;
        }
        tiinfo.valid_elements |= BCM_FLOW_TUNNEL_INIT_DIP6_VALID |
                                 BCM_FLOW_TUNNEL_INIT_SIP6_VALID;
    }

    rv = bcm_flow_tunnel_initiator_create(unit, &tiinfo, 0, NULL);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuring init-tunnel: %s.\n", bcm_errmsg(rv));
        return rv;
    } else {
        printf("Creating VXLAN init-tunnel... done!\n");
    } 

    // Tunnel_term: Create  Flow Tunnel Terminator
    bcm_flow_tunnel_terminator_t_init(&ttinfo);
    ttinfo.flow_handle = flow_handle;
    if (flow_flag == FLAGS_FLOW_CLASSIC) {
        ttinfo.type = bcmTunnelTypeVxlan;
        ttinfo.valid_elements = BCM_FLOW_TUNNEL_TERM_DIP_VALID;
        if (v_port->mc_tnl_flag) {
            ttinfo.dip = v_port->mcast_ip;
        } else { 
            ttinfo.dip = v_port->local_ip;   
        }     
    } else {
        ttinfo.type = bcmTunnelTypeVxlan6;
        ttinfo.valid_elements = BCM_FLOW_TUNNEL_TERM_DIP6_VALID;
        if (v_port->mc_tnl_flag) {
            ttinfo.dip6 = v_port->mcast_ip6;        
        } else {
            ttinfo.dip6 = v_port->local_ip6;
        }
    }
    if (v_port->mc_tnl_flag == FLAGS_TUNNEL_MC_BUD) {
        ttinfo.multicast_flag = BCM_FLOW_MULTICAST_TUNNEL_STATE_BUD_ENABLE;
    }   
    rv = bcm_flow_tunnel_terminator_create(unit, &ttinfo, 0, NULL);
    if (BCM_FAILURE(rv)) {
        if (rv != BCM_E_EXISTS) {
            printf("\nError in configuring term-tunnel: %s.\n", bcm_errmsg(rv));
            return rv;
        } else {
            printf("Warning: The VxLAN DIP already created!\n");
        }        
    } else {
        printf("Creating VXLAN term-tunnel... done!\n");
    } 

    return BCM_E_NONE;
}


bcm_error_t
vxlan_multicast_port_add(int unit, int create_group, int flags, bcm_multicast_t *mc_group, 
                                 vxlan_phy_port_s *vxlan_port, int vxlan_port_idx)
{
    vxlan_port_s            * v_port = &vxlan_port->vxlan_port[vxlan_port_idx];        
    bcm_error_t             rv = BCM_E_NONE;
    bcm_if_t                encap_id = BCM_IF_INVALID;
    bcm_multicast_encap_t   mc_encap;

    if(create_group) {
        rv = bcm_multicast_create(unit, flags, mc_group);
        if (BCM_FAILURE(rv)) {
            printf("\nError in creating Mcast Group: %s.\n", bcm_errmsg(rv));
            return rv;
        }
        printf("Creating Mcast Group (0x%x)... done!\n", *mc_group);
    }

    if (vxlan_port->flags == FLAGS_CUSTOMER) { // Access

    } else { // Network
        bcm_multicast_encap_t_init(&mc_encap);
        if (flags == BCM_MULTICAST_TYPE_FLOW) { // Tunnel
            mc_encap.encap_type = bcmMulticastEncapTypeL2Tunnel;
            mc_encap.ul_egress_if   = v_port->egr_id;        
            mc_encap.l3_intf        = 0;  
            mc_encap.port_id        = v_port->flow_port.flow_port_id;              
        } else {  // Transit      
            mc_encap.encap_type = bcmMulticastEncapTypeL3;
            mc_encap.ul_egress_if   = 0;
            mc_encap.l3_intf        = v_port->intf_id;
        }
        rv = bcm_multicast_encap_create(unit, &mc_encap, &encap_id);
        if (BCM_FAILURE(rv) && rv != BCM_E_EXISTS) {
            printf("\nError in creating Mcast Encap ID: %s.\n", bcm_errmsg(rv));
            return rv;
        }
    }

    rv = bcm_multicast_egress_add(unit, *mc_group, vxlan_port->gport_id, encap_id);
    if (BCM_FAILURE(rv)) {
        printf("\nError in egress add: %s.\n", bcm_errmsg(rv));
        return rv;
    }
    printf("Adding port (0x%x) to Mcast Group (0x%x)... done.\n", vxlan_port->gport_id, *mc_group);

    return rv;
}

                                   
bcm_error_t
vxlan_init(int unit, int flags)
{
    BCM_IF_ERROR_RETURN( bcm_vlan_control_set(unit, bcmVlanTranslate, 1));
    if (flags == FLAGS_FLOW_CLASSIC) {
        BCM_IF_ERROR_RETURN( bcm_flow_handle_get(unit, "CLASSIC_VXLAN", &flow_handle));
    } else {
        BCM_IF_ERROR_RETURN( bcm_flow_handle_get(unit, "VXLAN", &flow_handle));
    }
    flow_flag = flags;

    return BCM_E_NONE;
}

bcm_error_t
vxlan_port_create(int unit, int modid, bcm_port_t port_id, int flags, vxlan_phy_port_s * port)
{
    int my_modid;

    BCM_IF_ERROR_RETURN(bcm_stk_modid_get(unit, &my_modid));
    if (my_modid == modid) {  
        BCM_IF_ERROR_RETURN(bcm_port_gport_get(unit, port_id, &port->gport_id));  
        BCM_IF_ERROR_RETURN( bcm_port_control_set(unit, port_id, bcmPortControlVxlanTunnelbasedVnId, 0));
        if (FLAGS_PROVIDER == flags) {    
            BCM_IF_ERROR_RETURN( bcm_port_control_set(unit, port_id, bcmPortControlVxlanEnable, 1));
        } else {
            BCM_IF_ERROR_RETURN( bcm_port_control_set(unit, port_id, bcmPortControlVxlanEnable, 0));
            BCM_IF_ERROR_RETURN( bcm_vlan_control_port_set(unit, port_id, bcmVlanTranslateIngressEnable, 1));

            /* Configure ING_L2_IIF_TABLE.PORT_GROUP_ID - use port id as the port group */
            BCM_IF_ERROR_RETURN(bcm_port_class_set(unit, port->gport_id, bcmPortClassIngress, (port->gport_id & 0xff)));

        }
    } else {
        BCM_GPORT_MODPORT_SET(port->gport_id, modid, port_id);
        flags |= FLAGS_REMOTE_CHIP;
    }   
    port->modid             = modid;      
    port->port_id           = port_id;
    port->flags             = flags;
    port->vxlan_port_num    = 0;

    return BCM_E_NONE;
}


/************************** Trunk Sub-Routines ****************************/

/* FlexDigest configuration*/

int 
flex_degest_setup(int unit, uint8 l2_iif_opaque_ctrl_id)
{
    int seed_profile_id, norm_profile_id, hash_profile_id;
    int value;
    uint16 salt_a[16] = {
        0xabcd,
        0xbbcb,
        0xbabe,
        0x0123,
        0x7654,
        0xabcd,
        0xaaaa,
        0x5555,
        0xffff,
        0x0000,
        0xa5a5,
        0xface,
        0xbbbb,
        0xcccc,
        0xdddd,
        0xeeee
    };
    bcm_flexdigest_qset_t qset;
    bcm_flexdigest_group_t group;
    bcm_flexdigest_entry_t entry;
    bcm_flexdigest_match_id_t match_id;
    int pri = 0;

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_init(unit));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_norm_seed_profile_create(unit, 0, &seed_profile_id));
    value = 0xbabaface;
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_norm_seed_profile_set(unit, seed_profile_id,
                                              bcmFlexDigestNormSeedControlBinASeed,
                                              value));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_norm_profile_create(unit, 0, &norm_profile_id));

    value = 1;
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_norm_profile_set(unit, norm_profile_id,
                                         bcmFlexDigestNormProfileControlNorm, value));
    value = 0;
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_norm_profile_set(unit, norm_profile_id,
                                         bcmFlexDigestNormProfileControlSeedId, value));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_hash_profile_create(unit, 0, &hash_profile_id));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_hash_profile_set(unit, hash_profile_id,
                                         bcmFlexDigestHashProfileControlPreProcessBinA,
                                         1));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_hash_profile_set(unit, hash_profile_id,
                                         bcmFlexDigestHashProfileControlXorSaltBinA,
                                         1));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_hash_profile_set(unit, hash_profile_id,
                                         bcmFlexDigestHashProfileControlBinA0FunctionSelection,
                                         BCM_FLEXDIGEST_HASH_FUNCTION_CRC32LO));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_hash_profile_set(unit, hash_profile_id,
                                         bcmFlexDigestHashProfileControlBinA1FunctionSelection,
                                         BCM_FLEXDIGEST_HASH_FUNCTION_CRC32HI));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_hash_salt_set(unit, bcmFlexDigestHashBinA, 16, salt_a));


    /* Flex Digest Group */
    BCM_FLEXDIGEST_QSET_INIT(qset);
    BCM_FLEXDIGEST_QSET_ADD(qset, bcmFlexDigestQualifyMatchId);

    BCM_FLEXDIGEST_QSET_ADD(qset, bcmFlexDigestQualifyL2IifOpaqueCtrlId);
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_group_create(unit, qset, pri, &group));

    printf("Create FlexDigest Group 0x%x for Match ID and L2_IIF_OPCAQUE_CTRL_ID... done!\n", group);

    /* Flex Digest Entry for L2 packets with IP UDP header */
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_entry_create(unit, group, &entry));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_entry_priority_set(unit, entry, 2));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_match_id_create(unit, &match_id));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_match_add(unit, match_id, bcmFlexDigestMatchOuterL2HdrL2));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_match_add(unit, match_id, bcmFlexDigestMatchOuterL2HdrOtag));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_match_add(unit, match_id, bcmFlexDigestMatchOuterL3L4HdrUdp));
        BCM_IF_ERROR_RETURN
        (bcm_flexdigest_qualify_MatchId(unit, entry, match_id));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_qualify_L2IifOpaqueCtrlId(unit, entry, l2_iif_opaque_ctrl_id, 0xf));

    // Based on DA, SA, VID, Ethertype, IP addresses
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds0,  BCM_FLEXDIGEST_FIELD_OUTER_MACSA_0_15, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds1,  BCM_FLEXDIGEST_FIELD_OUTER_MACSA_16_31, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds2,  BCM_FLEXDIGEST_FIELD_OUTER_MACSA_32_47, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds3,  BCM_FLEXDIGEST_FIELD_OUTER_MACDA_0_15, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds4,  BCM_FLEXDIGEST_FIELD_OUTER_MACDA_16_31, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds5,  BCM_FLEXDIGEST_FIELD_OUTER_MACDA_32_47, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds6,  BCM_FLEXDIGEST_FIELD_OUTER_OTAG_0_15, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds7,  BCM_FLEXDIGEST_FIELD_OUTER_OTAG_16_31, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds8,  BCM_FLEXDIGEST_FIELD_OUTER_ETHERTYPE, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds9,  BCM_FLEXDIGEST_FIELD_OUTER_IP_HDR_SIP_0_15, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds10, BCM_FLEXDIGEST_FIELD_OUTER_IP_HDR_SIP_16_31, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds11, BCM_FLEXDIGEST_FIELD_OUTER_IP_HDR_DIP_0_15, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds12, BCM_FLEXDIGEST_FIELD_OUTER_IP_HDR_DIP_16_31, 0xffff));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_entry_install(unit, entry));

    printf("Create FlexDigest Entry 0x%x for L2 packets based on DA, SA, VID, Ethertype, IP addresses... done!\n", entry);

    /* Flex Digest Entry for VXLAN packets */
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_entry_create(unit, group, &entry));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_entry_priority_set(unit, entry, 2));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_match_id_create(unit, &match_id));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_match_add(unit, match_id, bcmFlexDigestMatchOuterL3L4HdrVxlan));
    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_qualify_MatchId(unit, entry, match_id));

    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_qualify_L2IifOpaqueCtrlId(unit, entry, l2_iif_opaque_ctrl_id, 0xf));

    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds0,  BCM_FLEXDIGEST_FIELD_OUTER_IP_HDR_SIP_0_15, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds1,  BCM_FLEXDIGEST_FIELD_OUTER_IP_HDR_SIP_16_31, 0xffff));    
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds3,  BCM_FLEXDIGEST_FIELD_OUTER_IP_HDR_DIP_0_15, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds4,  BCM_FLEXDIGEST_FIELD_OUTER_IP_HDR_DIP_16_31, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds5,  BCM_FLEXDIGEST_FIELD_OUTER_VXLAN_VN_ID_RESERVED_2_0_15, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds6,  BCM_FLEXDIGEST_FIELD_OUTER_VXLAN_VN_ID_RESERVED_2_16_31, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds7,  BCM_FLEXDIGEST_FIELD_OUTER_L4_DST_PORT, 0xffff));
    BCM_IF_ERROR_RETURN(bcm_flexdigest_action_add(unit, entry, bcmFlexDigestActionExtractBinSetACmds8,  BCM_FLEXDIGEST_FIELD_OUTER_L4_SRC_PORT, 0xffff));


    BCM_IF_ERROR_RETURN
        (bcm_flexdigest_entry_install(unit, entry));

    printf("Create FlexDigest Entry 0x%x for VxLAN packets based on Tunnel IP addresses, L4 ports, VNID... done!\n", group, entry);

    return BCM_E_NONE;
}



int 
flex_digest_port_setup(int unit, bcm_port_t port, uint8 l2_iif_opaque_ctrl_id)
{

    BCM_IF_ERROR_RETURN(bcm_port_class_set(unit, port, bcmPortClassOpaqueCtrlId, l2_iif_opaque_ctrl_id));

    BCM_IF_ERROR_RETURN(flex_degest_setup(unit, l2_iif_opaque_ctrl_id));

    /* Hash Selection */
    BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit, bcmSwitchHashUseFlowSelTrunkUc, 0));
    BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit, bcmSwitchHashUseFlowSelTrunkNonUnicast, 0));
    BCM_IF_ERROR_RETURN(bcm_switch_control_set(unit, bcmSwitchHashUseFlowSelTrunkDynamic, 0));
    // 0 -> Concatenation = 0, block A, offset = 0 (A0: 0~15, A1: 16~31, B0/B1: 32~63, C0/C1: 64~95,)
    BCM_IF_ERROR_RETURN(bcm_switch_control_port_set(unit, port, bcmSwitchTrunkUnicastHashOffset, 0));
    BCM_IF_ERROR_RETURN(bcm_switch_control_port_set(unit, port, bcmSwitchTrunkNonUnicastHashOffset, 0));
    BCM_IF_ERROR_RETURN(bcm_switch_control_port_set(unit, port, bcmSwitchTrunkDynamicHashOffset, 0));
    
    return BCM_E_NONE;
}

/*Trunk configuration*/
int
config_trunk(int unit, int tid)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_trunk_info_t trunk_info;
    bcm_trunk_member_t member_array[NO_OF_TRUNK_MEMBERS];
    int i=0;

    bcm_trunk_info_t_init(&trunk_info);
    trunk_info.flags      = BCM_TRUNK_FLAG_FAILOVER_ALL_LOCAL;
    trunk_info.psc        = BCM_TRUNK_PSC_PORTFLOW;
    trunk_info.dlf_index  = BCM_TRUNK_UNSPEC_INDEX;
    trunk_info.mc_index   = BCM_TRUNK_UNSPEC_INDEX;
    trunk_info.ipmc_index = BCM_TRUNK_UNSPEC_INDEX;

    for(i = 0; i < NO_OF_TRUNK_MEMBERS; i++)
    {
        bcm_trunk_member_t_init(&member_array[i]);
        BCM_GPORT_LOCAL_SET(member_array[i].gport, egress_port[i]);
    }

    BCM_IF_ERROR_RETURN(bcm_trunk_create(unit, BCM_TRUNK_FLAG_WITH_ID,
                                                &tid));
    BCM_IF_ERROR_RETURN(bcm_trunk_set(unit, tid,
                                &trunk_info, NO_OF_TRUNK_MEMBERS, member_array));

    return BCM_E_NONE;
}

/************************** Main Routine ****************************/
bcm_vpn_t           vxlan_vpn = 0x8064;
vxlan_phy_port_s    customer_port, provider_port1, provider_port2,
                    provider_port3,provider_port4,provider_port5;
vxlan_phy_port_s    net_trunk_port;

/* Access Port Coinfigurations */
bcm_vlan_t      acc_vid = 21;
bcm_mac_t       acc_local_mac = "00:00:00:00:11:11";
bcm_mac_t       acc_remote_mac = "00:00:00:00:00:01";

/* Network Port Coinfigurations */
bcm_vlan_t      net_vid = 22;
bcm_mac_t       net_local_mac = "00:00:00:00:22:22";
bcm_mac_t       net_remote_mac = "00:00:00:00:00:02";
bcm_ip_t        net_remote_ip  = 0xC0A80101;  /* 192.168.1.1 */
bcm_ip_t        net_local_ip   = 0x0a0a0a01;  /* 10.10.10.1 */
uint32          vnid = 0x12345; 
int             dvp_group = 10 + 2048;
bcm_flow_encap_criteria_t criteria = BCM_FLOW_ENCAP_CRITERIA_VFI_DVP_GROUP;

/* Multicast Groups*/
bcm_multicast_t vxlan_bcast_group = 0;

const int   CREATE      = 1;
const int   NOT_CREATE  = 0;

bcm_error_t
config_vxlan(int unit)
{
    bcm_error_t rv = BCM_E_NONE;
    int my_modid;
    int tid = 3;
    uint8 l2_iif_opaque_ctrl_id = 1;
    bcm_gport_t trunk_gport;
        
    rv = flex_digest_port_setup(unit, ingress_port, l2_iif_opaque_ctrl_id);
    if (BCM_FAILURE(rv)) {
        printf("\nError in setup flex digest config: %s.\n", bcm_errmsg(rv));
        return rv;
    }
        
    rv = config_trunk(unit, tid);
    if (BCM_FAILURE(rv)) {
        printf("\nError in trunk config: %s.\n", bcm_errmsg(rv));
        return rv;
    }
    BCM_GPORT_TRUNK_SET(trunk_gport, tid);
    
    BCM_IF_ERROR_RETURN(vxlan_init(unit, FLAGS_FLOW_CLASSIC));
    BCM_IF_ERROR_RETURN(bcm_stk_modid_get(unit, &my_modid));
    BCM_IF_ERROR_RETURN(vxlan_port_create(unit, my_modid, ingress_port,   FLAGS_CUSTOMER, &customer_port));    
    BCM_IF_ERROR_RETURN(vxlan_port_create(unit, my_modid, egress_port[0], FLAGS_PROVIDER, &provider_port1));
    BCM_IF_ERROR_RETURN(vxlan_port_create(unit, my_modid, egress_port[1], FLAGS_PROVIDER, &provider_port2));
    BCM_IF_ERROR_RETURN(vxlan_port_create(unit, my_modid, egress_port[2], FLAGS_PROVIDER, &provider_port3));
    BCM_IF_ERROR_RETURN(vxlan_port_create(unit, my_modid, egress_port[3], FLAGS_PROVIDER, &provider_port4));
    BCM_IF_ERROR_RETURN(vxlan_port_create(unit, my_modid, egress_port[4], FLAGS_PROVIDER, &provider_port5));

    /* Multicast group for non-UC */
    BCM_IF_ERROR_RETURN( bcm_multicast_create(unit, BCM_MULTICAST_TYPE_FLOW, &vxlan_bcast_group));

    /* Create VXLAN VPN */
    BCM_IF_ERROR_RETURN( vxlan_vpn_create(unit, vxlan_bcast_group, vxlan_vpn));

    /* Create VXLAN VP for access ports */
    customer_port.vxlan_port[0].vid = acc_vid;
    BCM_IF_ERROR_RETURN(vxlan_access_port_create(unit, vxlan_vpn, &customer_port));

    /* Create VXLAN VP for network ports */
    net_trunk_port.gport_id                 = trunk_gport;
    net_trunk_port.flags                    = FLAGS_PROVIDER;
    net_trunk_port.vxlan_port[0].vid        = net_vid;
    net_trunk_port.vxlan_port[0].local_mac  = net_local_mac;
    net_trunk_port.vxlan_port[0].remote_mac = net_remote_mac;
    net_trunk_port.vxlan_port[0].criteria   = criteria;
    net_trunk_port.vxlan_port[0].vnid       = vnid;
    net_trunk_port.vxlan_port[0].dvp_group  = dvp_group;
    net_trunk_port.vxlan_port[0].remote_ip  = net_remote_ip;
    BCM_IF_ERROR_RETURN(vxlan_network_port_create(unit, vxlan_vpn, &net_trunk_port));

    /* Create init & term tunnel */
    net_trunk_port.vxlan_port[0].ttl        = 0x3f;
    net_trunk_port.vxlan_port[0].local_ip   = net_local_ip;
    net_trunk_port.vxlan_port[0].remote_ip  = net_remote_ip;
    net_trunk_port.vxlan_port[0].mc_tnl_flag = 0;
    BCM_IF_ERROR_RETURN(vxlan_tunnel_create(unit, &net_trunk_port.vxlan_port[0]));



    /* Access-to-Network: Add payload-dest-mac Address => Network-flow-port (VP). */
    BCM_IF_ERROR_RETURN(vxlan_l2_add(unit, "00:00:00:00:aa:aa", vxlan_vpn, 
                           net_trunk_port.vxlan_port[0].flow_port.flow_port_id));

    return BCM_E_NONE;

}

    void
verify(int unit)
{
    char str[512];
    char pkt_data[7][512];
    int i=0;
    /*Initalize the pkt_data with the actual ingress packets to be used for testing*/
    snprintf(pkt_data[0],512,"%s","00000000AAAA00000000BBBB8100001508004500002E00000000401174BA010101010202020200350036001AB0F8000102030405060708090A0B0C0D0E0F101133CF192C");

    snprintf(pkt_data[1],512,"%s","00000000AAAA00000000BBBB8100001508004500002E00000000401174B9010101020202020200350036001AB0F7000102030405060708090A0B0C0D0E0F1011975E7DF7");

    snprintf(pkt_data[2],512,"%s","00000000AAAA00000000BBBB8100001508004500002E00000000401174B8010101030202020200350036001AB0F6000102030405060708090A0B0C0D0E0F1011D621E6E1");

    snprintf(pkt_data[3],512,"%s","00000000AAAA00000000BBBB8100001508004500002E00000000401174B5010101060202020200350036001AB0F3000102030405060708090A0B0C0D0E0F101196025567");

    snprintf(pkt_data[4],512,"%s","00000000AAAA00000000BBBB8100001508004500002E00000000401174B4010101070202020200350036001AB0F2000102030405060708090A0B0C0D0E0F1011D77DCE71");

    snprintf(pkt_data[5],512,"%s","00000000AAAA00000000BBBB8100001508004500002E00000000401174B40101010a0202020200350036001AB0F2000102030405060708090A0B0C0D0E0F1011D77DCE71");
    
    snprintf(pkt_data[6],512,"%s","00000000AAAA00000000BBBB8100001508004500002E00000000401174B4010101140202020200350036001AB0F2000102030405060708090A0B0C0D0E0F1011D77DCE71");

    bshell(unit, "e; vlan show");
    bshell(unit, "e; l2 show");
    bshell(unit, "e; trunk show");
    bshell(unit, "e; clear c");

    for(i=0; i<sizeof(pkt_data)/512; i++)
    {
        printf("\nSending known unicast packet No.[%d] to ingress_port access side:%d\n", i+1,ingress_port);
        snprintf(str, 512, "tx 1 pbm=%d data=0x%s; sleep quiet 1", ingress_port, pkt_data[i]);
        bshell(unit, str);
    }

    printf("\n-----------------------------------------\n");
    printf("Distribution of %d Packets on trunk ports:",sizeof(pkt_data)/512);
    printf("\n-----------------------------------------\n");
    bshell(unit, "sleep quiet 1;show c s;show c s");
    return;
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
    int unit = 0;

    print "config show; attach; version";
    bshell(unit, "config show; a ; version");

    print "~~~ #1) test_setup(): ** start **";
    if (BCM_FAILURE((rv = test_setup(unit)))) {
        printf("test_setup() failed.\n");
        return -1;
    }
    print "~~~ #1) test_setup(): ** end **";

    print "~~~ #2) config_vxlan(): ** start **";
    if (BCM_FAILURE((rv = config_vxlan(unit)))) {
        printf("config_vxlan() failed.\n");
        return -1;
    }
    print "~~~ #2) config_vxlan(): ** end **";

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
