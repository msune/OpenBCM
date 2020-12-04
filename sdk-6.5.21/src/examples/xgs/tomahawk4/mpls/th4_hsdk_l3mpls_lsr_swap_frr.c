/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 */

/*
 * Feature  : L3 MPLS LSR label swap fast reroute scenario
 *
 * Usage    : BCM.0> cint th4_hsdk_l3mpls_lsr_swap_frr.c
 *
 * config   : bcm56990-generic-l3mpls.config.yml
 *
 * Log file : th4_hsdk_l3mpls_lsr_swap_frr_log.txt
 *
 * Test Topology :
 *
 *                   +------------------------------+
 *                   |                              |
 *                   |                              | primary_egress_port
 *                   |                              +--------------------+
 *  ingress_port     |                              |
 * +-----------------+          SWITCH              |
 *                   |                              |
 *                   |                              | failover_egress_port
 *                   |                              +--------------------+
 *                   |                              |
 *                   |                              |
 *                   +------------------------------+
 * Summary:
 * ========
 *   This Cint example to show configuration of the L3 MPLS LSR label swap with
 *   failover scenario using BCM APIs.
 *
 * Detailed steps done in the CINT script:
 * =======================================
 *   1) Step1 - Test Setup (Done in test_setup()):
 *   =============================================
 *     a) Selects three ports and configure them in Loopback mode. Out of these
 *        three ports, one port is used as ingress_port and the others as
 *        egress_ports (primary & failover).
 *
 *     b) Install an IFP rule to copy incoming packets to CPU and start
 *        packet watcher.
 *
 *     Note: IFP rule is meant for a testing purpose only (Internal) and it is
 *           nothing to do with an actual functional test.
 *
 *   2) Step2 - Configuration (Done in config_lsr_swap_frr()):
 *   =========================================================
 *     a) Configure a basic L3 MPLS Tunnel swap functional scenario with
 *        failover and does the necessary configurations of vlan, interface,
 *        next hop and swap labels.
 *
 *   3) Step3 - Verification (Done in test_verify()):
 *   ===========================================
 *     a) Register pktio call back funciton,
 *
 *     b) Transmit the MPLS Label packet. The contents of the packet
 *        are printed on screen.
 *
 *     c) Expected Result:
 *     ===================
 *       We can see that dmac, smac and vlan are all changed as the packet is
 *       routed through the egress port and also MPLS Labels are swapped
 *       as part of tunnel switching on egress port. Also use flexctr to check
 *       the packet stats/counters.
 *
 *       {000000aa2222} {000000aa1212} 8100 0016
 *       8847 0022 2001 000a a140 4500 003c 6762 // Swap the tunnel label to 0x222
 *       0000 fe01 be76 0a3a 4001 0a3a 4273 0000
 *       550a 0001 0051 6162 6364 6566 6768 696a
 *       6b6c 6d6e 6f70 7172 7374 7576 7761 6263
 *       6465 6667 6869
 *
 *       Now, switch to backup path with *_failover_egress_status_set and observe that
 *       packet is switched/routed to failover path/tunnel.
 *
 *       In Pktio call back function, checking the received pkt data, packet length, and
 *       the received port as expected port.
 *
 *       In function check_flexctr, checking the flexctr packet counter and bytes counter
 *       as expected values.
 *
 *       {000000003333} {000000aa1212} 8100 0021
 *       8847 0099 9040 0022 2001 000a a140 4500  // Extra failover tunnel label(0x999) added
 *       003c 6762 0000 fe01 be76 0a3a 4001 0a3a
 *       4273 0000 550a 0001 0051 6162 6364 6566
 *       6768 696a 6b6c 6d6e 6f70 7172 7374 7576
 *       7761 6263 6465 6667 6869
 */

/* Reset C interpreter */
cint_reset();

bcm_port_t ingress_port;
bcm_port_t egress_ports[2];
bcm_port_t primary_egress_port, failover_egress_port;
bcm_vlan_t in_vlan = 11;
bcm_vlan_t out_vlan = 22, failover_out_vlan = 33;
bcm_mac_t local_mac_in = {0x00, 0x00, 0x00, 0x00, 0x11, 0x11};
bcm_mac_t local_mac = {0x00, 0x00, 0x00, 0xAA, 0x12, 0x12};
bcm_mac_t nh_mac    = {0x00, 0x00, 0x00, 0xAA, 0x22, 0x22};
bcm_mpls_label_t in_tunnel_label = 0x111;  /* 273 */
bcm_mpls_label_t out_tunnel_label = 0x222;  /* 546 */
bcm_field_group_t ifp_group;
bcm_field_entry_t ifp_entry[2];
uint32_t stat_counter_id, stat_counter_id_1;
bcm_if_t primary_egr_obj;
int fixed_nh_offset = 0x3000;

/*
 * This function is written so that hardcoding of port
 * numbers in Cint scripts is removed. This function gives
 * required number of ports
*/
bcm_error_t
portNumbersGet(int unit, int *port_list, int num_ports)
{
	bcm_error_t rv = BCM_E_NONE;
    int i = 0, port = 0;
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
        return BCM_E_PORT;
    }

    return BCM_E_NONE;
}

/*
 * Configures the port in loopback mode
 */
bcm_error_t
ingress_port_setup(int unit, bcm_port_t port)
{
    BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, port, BCM_PORT_LOOPBACK_MAC));
    BCM_IF_ERROR_RETURN(bcm_port_discard_set(unit, port, BCM_PORT_DISCARD_NONE));

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
egress_ports_setup(int unit, int port_count, int *port)
{
	int i=0;
    bcm_field_entry_t entry;
    bcm_field_group_config_t group_config;

    bcm_field_group_config_t_init(&group_config);
    BCM_FIELD_QSET_INIT(group_config.qset);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyInPort);
    BCM_FIELD_QSET_ADD(group_config.qset, bcmFieldQualifyStageIngress);
    BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionCopyToCpu);
    BCM_FIELD_ASET_ADD(group_config.aset, bcmFieldActionDrop);
    BCM_IF_ERROR_RETURN(bcm_field_group_config_create(unit, &group_config));
	ifp_group = group_config.group;
	print ifp_group;

    for(i=0;i<port_count; i++){
    BCM_IF_ERROR_RETURN(bcm_field_entry_create(unit, group_config.group, &entry));
	ifp_entry[i] = entry;
	print ifp_entry[i];
    BCM_IF_ERROR_RETURN(bcm_field_qualify_InPort(unit, entry, *port, BCM_FIELD_EXACT_MATCH_MASK));
    BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry, bcmFieldActionCopyToCpu, 0, 0));
    BCM_IF_ERROR_RETURN(bcm_field_action_add(unit, entry, bcmFieldActionDrop, 0, 0));
    BCM_IF_ERROR_RETURN(bcm_field_entry_install(unit, entry));

    BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, *port, BCM_PORT_LOOPBACK_MAC));
    BCM_IF_ERROR_RETURN(bcm_port_discard_set(unit, *port, BCM_PORT_DISCARD_ALL));
	port++;
	}

    return BCM_E_NONE;
}

bcm_error_t clear_field_resource(int unit, bcm_field_group_t group, bcm_field_entry_t *entry, int entry_num)
{
	bcm_error_t rv = BCM_E_NONE;
	int i;

	for(i=0; i<entry_num; i++){
    /* Remove field entry from hardware table */
    rv = bcm_field_entry_remove(unit, entry[i]);
    if (BCM_FAILURE(rv)) {
        printf("bcm_field_entry_remove() FAILED: %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* Destroy the field entry */
    rv = bcm_field_entry_destroy(unit, entry[i]);
    if (BCM_FAILURE(rv)) {
        printf("bcm_field_entry_destroy() FAILED: %s\n", bcm_errmsg(rv));
        return rv;
    }
	}

    /* Destroy the field group */
    rv = bcm_field_group_destroy(unit, group);
    if (BCM_FAILURE(rv)) {
        printf("bcm_field_group_destroy() FAILED: %s\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}

/*
 * Test Setup:
 * This functions gets the port numbers and sets up ingress and
 * egress ports. Check ingress_port_setup() and egress_ports_setup().
 */
bcm_error_t test_setup(int unit)
{
	bcm_error_t rv = BCM_E_NONE;
    int port_list[3];

    rv = portNumbersGet(unit, port_list, 3);
    if (BCM_FAILURE(rv)) {
        printf("portNumbersGet() failed\n");
        return rv;
    }

    ingress_port = port_list[0];
	print ingress_port;
    egress_ports[0] = primary_egress_port = port_list[1];
    egress_ports[1] = failover_egress_port = port_list[2];
    print primary_egress_port;
	print failover_egress_port;

    printf("setting ingress port:%d MAC loopback\n", ingress_port);
    rv = ingress_port_setup(unit, ingress_port);
    if (BCM_FAILURE(rv)) {
        printf("ingress_port_setup() failed for port %d\n", ingress_port);
        return rv;
    }

    printf("setting egress port:%d %d MAC loopback\n", egress_ports[0], egress_ports[1]);
    rv = egress_ports_setup(unit, 2, egress_ports);
    if (BCM_FAILURE(rv)) {
        printf("egress_ports_setup() failed for ports %d %d\n", egress_port[0], egress_port[1]);
        return rv;
    }

    /*bshell(unit, "pw start report +raw +decode");*/

	return BCM_E_NONE;
}

/*Expected Egress packets */
unsigned char expected_egress_packet1[86] = {
0x00, 0x00, 0x00, 0xaa, 0x22, 0x22, 0x00, 0x00, 0x00, 0xaa, 0x12, 0x12, 0x81, 0x00, 0x00, 0x16,
0x88, 0x47, 0x00, 0x22, 0x20, 0x01, 0x00, 0x0a, 0xa1, 0x40, 0x45, 0x00, 0x00, 0x3c, 0x67, 0x62,
0x00, 0x00, 0xfe, 0x01, 0xbe, 0x76, 0x0a, 0x3a, 0x40, 0x01, 0x0a, 0x3a, 0x42, 0x73, 0x00, 0x00,
0x55, 0x0a, 0x00, 0x01, 0x00, 0x51, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x61, 0x62, 0x63,
0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
};

unsigned char expected_egress_packet2[90] = {
0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x00, 0xaa, 0x12, 0x12, 0x81, 0x00, 0x00, 0x21,
0x88, 0x47, 0x00, 0x99, 0x90, 0x40, 0x00, 0x22, 0x20, 0x01, 0x00, 0x0a, 0xa1, 0x40, 0x45, 0x00,
0x00, 0x3c, 0x67, 0x62, 0x00, 0x00, 0xfe, 0x01, 0xbe, 0x76, 0x0a, 0x3a, 0x40, 0x01, 0x0a, 0x3a,
0x42, 0x73, 0x00, 0x00, 0x55, 0x0a, 0x00, 0x01, 0x00, 0x51, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
0x77, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
};

int test_failed = 0; /*Final result will be stored here */
int rx_count;   /* Global received packet count */
uint32 test_pkt_num = 2;
unsigned char *expected_packets[test_pkt_num];
const uint8 priority = 100;


/* Rx callback function for applications using the HSDK PKTIO */
bcm_pktio_rx_t
pktioRxCallback(int unit, bcm_pktio_pkt_t * packet, void *cookie)
{
    int                *count = (auto) cookie;
    void               *buffer;
    uint32              length;
    uint32              port;

	(*count)++; /* Bump received packet count */

    /* Get basic packet info */
    if (BCM_FAILURE(bcm_pktio_pkt_data_get(unit, packet, (void *) &buffer, &length))) {
        return BCM_PKTIO_RX_NOT_HANDLED;
    }
    /* Get source port metadata */
    BCM_IF_ERROR_RETURN(bcm_pktio_pmd_field_get
                        (unit, packet, bcmPktioPmdTypeRx,
                         BCM_PKTIO_RXPMD_SRC_PORT_NUM, &port));

    printf("pktioRxCallback: packet received #%d from port %d, length %d\n", *count, port, length);

	if ((egress_ports[0] == port) && (sal_memcmp(buffer, expected_packets[0], length) != 0)){
   	    test_failed = 1;
        printf("pktioRxCallback: packet received from wrong port %d, expected from port %d, or packet data not match\n", port, egress_ports[0]);
    }else if ((egress_ports[1] == port) && (sal_memcmp(buffer, expected_packets[1], length) != 0)){
   	    test_failed = 1;
        printf("pktioRxCallback: packet received from wrong port %d, expected from port %d, or packet data not match\n", port, egress_ports[1]);
	} else {
        printf("pktioRxCallback: packet received from correct expected port %d\n", port);
        printf("pktioRxCallback: packet received data comparision pass\n");
	}

    return BCM_PKTIO_RX_NOT_HANDLED;
}

/* Register callback function for received packets */
bcm_error_t
registerPktioRxCallback(int unit)
{
    const uint32        flags = 0;      /* Flags only used on match (for now) */

    return bcm_pktio_rx_register
      (unit, "rx_cb", pktioRxCallback, priority, &rx_count, flags);
}

bcm_error_t
unregisterPktioRxCallback(int unit)
{
    return bcm_pktio_rx_unregister(unit, pktioRxCallback, priority);
}

/* Create vlan and add port to vlan */
bcm_error_t
vlan_create_add_port(int unit, int vid, int port)
{
    bcm_pbmp_t pbmp, upbmp;

    BCM_IF_ERROR_RETURN(bcm_vlan_create(unit, vid));
    BCM_PBMP_CLEAR(pbmp);
    BCM_PBMP_CLEAR(upbmp);
    BCM_PBMP_PORT_ADD(pbmp, port);
    return bcm_vlan_port_add(unit, vid, pbmp, upbmp);
}

/* Destroy vlan and remove port from vlan */
bcm_error_t
vlan_destroy_remove_port(int unit, int vid, int port)
{
    bcm_pbmp_t pbmp;

    BCM_PBMP_CLEAR(pbmp);
    BCM_PBMP_PORT_ADD(pbmp, port);
    BCM_IF_ERROR_RETURN(bcm_vlan_port_remove(unit, vid, pbmp));
    return bcm_vlan_destroy(unit, vid);
}

/* Create vlan and add array of ports to vlan */
bcm_error_t
vlan_create_add_ports(int unit, int vid, int count, bcm_port_t *ports)
{
    bcm_pbmp_t pbmp, upbmp;
    int i;

    BCM_IF_ERROR_RETURN(bcm_vlan_create(unit, vid));
    BCM_PBMP_CLEAR(pbmp);
    BCM_PBMP_CLEAR(upbmp);

    for (i = 0; i < count; i++) {
        BCM_PBMP_PORT_ADD(pbmp, ports[i]);
    }

    return bcm_vlan_port_add(unit, vid, pbmp, upbmp);
}

bcm_error_t
create_l3_interface(int unit, int flags, bcm_mac_t local_mac, int vid, bcm_if_t *intf_id)
{
    bcm_l3_intf_t l3_intf;
    bcm_error_t rv = BCM_E_NONE;

    /* L3 interface and egress object for access */
    bcm_l3_intf_t_init(&l3_intf);
    l3_intf.l3a_flags |= flags;
    sal_memcpy(l3_intf.l3a_mac_addr, local_mac, sizeof(local_mac));
    l3_intf.l3a_vid = vid;
    l3_intf.l3a_intf_id = *intf_id;
    rv = bcm_l3_intf_create(unit, &l3_intf);
    if (BCM_FAILURE(rv)) {
        printf("bcm_l3_intf_create()%s\n", bcm_errmsg(rv));
        return rv;
    }
    *intf_id = l3_intf.l3a_intf_id;

    return rv;
}

bcm_error_t
clear_l3_interface(int unit, bcm_if_t intf_id)
{
    bcm_l3_intf_t l3_intf;
    bcm_error_t rv = BCM_E_NONE;

    bcm_l3_intf_t_init(&l3_intf);
	l3_intf.l3a_intf_id = intf_id;
	rv = bcm_l3_intf_get(unit, &l3_intf);
    if (BCM_FAILURE(rv)) {
        printf("bcm_l3_intf_get %s\n", bcm_errmsg(rv));
        return rv;
    }

    rv = bcm_l3_intf_delete(unit, &l3_intf);
    if (BCM_FAILURE(rv)) {
        printf("bcm_l3_intf_delete %s\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}

/* Create L3 egress object with outgoing label */
bcm_error_t
create_egr_obj_with_route_label(int unit, int l3_if, bcm_mac_t nh_mac, bcm_port_t port,
               bcm_mpls_label_t route_label, bcm_if_t *egr_obj_id)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_l3_egress_t l3_egress;

    bcm_l3_egress_t_init(&l3_egress);
    sal_memcpy(l3_egress.mac_addr,  nh_mac, sizeof(nh_mac));
    l3_egress.intf  = l3_if;
    l3_egress.port = port;
    l3_egress.flags = BCM_L3_ROUTE_LABEL;
    l3_egress.mpls_label = route_label;
    rv = bcm_l3_egress_create(unit, 0, &l3_egress, egr_obj_id);
    if (BCM_FAILURE(rv)) {
        printf("bcm_l3_egress_create() %s\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}

/* Clear L3 egress object */
bcm_error_t
clear_egr_obj(int unit, bcm_if_t egr_obj_id)
{
    bcm_error_t rv = BCM_E_NONE;

    rv = bcm_l3_egress_destroy(unit, egr_obj_id);
    if (BCM_FAILURE(rv)) {
        printf("bcm_l3_egress_destroy() %s\n", bcm_errmsg(rv));
        return rv;
    }

    return rv;
}

int config_l3_egress_flexctr(int unit, bcm_if_t egr_obj, uint32 *stat_counter_id)
{
    bcm_error_t rv = BCM_E_NONE;
    bcm_flexctr_action_t action = {0};
    bcm_flexctr_index_operation_t *index_op = NULL;
    bcm_flexctr_value_operation_t *value_a_op = NULL;
    bcm_flexctr_value_operation_t *value_b_op = NULL;
    int options = 0;

    action.index_num = 1;
    action.source = bcmFlexctrSourceL3Egress;
    action.hint = 0;
    action.mode = bcmFlexctrCounterModeNormal;

    /* Counter index is always zero. */
    index_op = &action.index_operation;
    index_op->object[0] = bcmFlexctrObjectConstZero;
    index_op->mask_size[0] = 16;
    index_op->shift[0] = 0;
    index_op->object[1] = bcmFlexctrObjectConstZero;
    index_op->mask_size[1] = 1;
    index_op->shift[1] = 0;

    /* Increase counter per packet. */
    value_a_op = &action.operation_a;
    value_a_op->select = bcmFlexctrValueSelectCounterValue;
    value_a_op->object[0] = bcmFlexctrObjectConstOne;
    value_a_op->mask_size[0] = 16;
    value_a_op->shift[0] = 0;
    value_a_op->object[1] = bcmFlexctrObjectConstZero;
    value_a_op->mask_size[1] = 1;
    value_a_op->shift[1] = 0;
    value_a_op->type = bcmFlexctrValueOperationTypeInc;

    /* Increase counter per packet bytes. */
    value_b_op = &action.operation_b;
    value_b_op->select = bcmFlexctrValueSelectPacketLength;
    value_b_op->type = bcmFlexctrValueOperationTypeInc;

    rv = bcm_flexctr_action_create(unit, options, &action, stat_counter_id);
    if (BCM_FAILURE(rv)) {
        printf("bcm_flexctr_action_create %s\n", bcm_errmsg(rv));
        return rv;
    }
    printf("Created flexctr stat_counter_id = 0x%x.\n", *stat_counter_id);

    rv = bcm_l3_egress_stat_attach(unit, egr_obj, *stat_counter_id);
    if (BCM_FAILURE(rv)) {
        printf("ERROR: bcm_l3_egress_stat_attach() -  %s.\n", bcm_errmsg(rv));
        return rv;
    }
    printf("Flexctr stat_counter_id:0x%x attached to l3 egress obj %d\n", *stat_counter_id, egr_obj);

    return rv;
}

bcm_error_t
check_flexctr(int unit, uint32 stat_counter_id, int expected_packet_length, int *flexctr_check_failed)
{
    bcm_error_t rv = BCM_E_NONE;
    uint32 num_entries = 1;
    uint32 counter_index = 0;
    bcm_flexctr_counter_value_t counter_value;

    /* Get counter value. */
    sal_memset(&counter_value, 0, sizeof(counter_value));
    rv = bcm_flexctr_stat_get(unit,
                              stat_counter_id,
                              num_entries,
                              &counter_index,
                              &counter_value);
    if (BCM_FAILURE(rv)) {
        printf("bcm_flexctr_stat_get %s\n", bcm_errmsg(rv));
        return rv;
    }

    printf("Flexctr Get : %d packets / %d bytes\n",
           COMPILER_64_LO(counter_value.value[0]),
           COMPILER_64_LO(counter_value.value[1]));

    if (COMPILER_64_LO(counter_value.value[0]) != 1) {
        printf("Flexctr packet verify failed. Expected packet %d but get %d\n", rx_count, COMPILER_64_LO(counter_value.value[0]));
        *flexctr_check_failed = 1;
        return BCM_E_FAIL;
    };

    if (COMPILER_64_LO(counter_value.value[1]) != expected_packet_length) {
        printf("Flexctr byte verify failed. Expected bytes %d but get %d\n", expected_packet_length, COMPILER_64_LO(counter_value.value[1]));
        *flexctr_check_failed = 1;
        return BCM_E_FAIL;
    };

    return BCM_E_NONE;
}

bcm_error_t
clear_l3_egress_flexctr(int unit,  bcm_if_t intf_id, uint32 stat_counter_id)
{
    bcm_error_t rv = BCM_E_NONE;

    /* Detach flexctr from l3 egress */
    rv = bcm_l3_egress_stat_detach(unit, intf_id);
    if (BCM_FAILURE(rv)) {
        printf("bcm_l3_egress_stat_detach: %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* Destroy flexctr action */
    rv = bcm_flexctr_action_destroy(unit, stat_counter_id);
    if (BCM_FAILURE(rv)) {
        printf("bcm_flexctr_action_destroy %s\n", bcm_errmsg(rv));
        return rv;
    }

    return BCM_E_NONE;
}

bcm_error_t
config_lsr_swap_frr(int unit)
{
    bcm_error_t rv = BCM_E_NONE;
	int flags = 0;
    bcm_if_t intf_id;
    bcm_if_t egr_obj_id;
    bcm_mpls_tunnel_switch_t tunnel_switch;

    /************************************
     * Create failover label switch path
 */
    /*
     * The packet going out of the failover path will have an additional tunnel label
     * failover_tunnel_label, the old swapped label "out_tunnel_label"
     * now becomes the second/inner label
     * So this is similar to initiation case, e.g. we use
     * bcm_l3_egress_create() and bcm_mpls_tunnel_initiator_set() to add 2 labels
     */

    bcm_if_t failover_tunnel_intf_id;
    bcm_mac_t failover_sa = {0x00, 0x00, 0x00, 0x00, 0x00, 0x33};
    bcm_mac_t failover_da = {0x00, 0x00, 0x00, 0x00, 0x33, 0x33};
    bcm_vlan_t failover_vid = failover_out_vlan;
    bcm_port_t failover_port = failover_egress_port;
    bcm_l3_egress_t failover_l3_egress;
    bcm_mpls_egress_label_t tunnel_label;
    uint32 failover_tunnel_label = 0x999;

    /* Create and add failover egress port into failover VLAN */
    rv = vlan_create_add_port(unit, failover_vid, failover_port);
    if (BCM_FAILURE(rv)) {
        printf("\nError in configuration: %s.\n",bcm_errmsg(rv));
        return rv;
    }

    /* Create egress L3 interface for failover LSP */
    rv = create_l3_interface(unit, flags, local_mac, failover_vid, &failover_tunnel_intf_id);
    if (BCM_FAILURE(rv)) {
        printf("\nError in create_l3_interface(): %s.\n",bcm_errmsg(rv));
        return rv;
    }
    printf("failover egr l3 intf = %d\n", failover_tunnel_intf_id);

    /* Create egr object for failover LSP */
    bcm_l3_egress_t_init(&failover_l3_egress);
    sal_memcpy(failover_l3_egress.mac_addr, failover_da, 6);
    failover_l3_egress.port = failover_port;
    failover_l3_egress.intf = failover_tunnel_intf_id;
    failover_l3_egress.mpls_label = out_tunnel_label;

    /* Push failover tunnel label*/
    bcm_mpls_egress_label_t_init(&tunnel_label);
    tunnel_label.flags = BCM_MPLS_EGRESS_LABEL_TTL_SET;
    tunnel_label.label = failover_tunnel_label;
    tunnel_label.ttl   = 64;
    rv = bcm_mpls_tunnel_initiator_set(unit, failover_tunnel_intf_id, 1, &tunnel_label);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_mpls_tunnel_initiator_set(): %s.\n",bcm_errmsg(rv));
        return rv;
    }

    /************************************
     * Create primary label swap path
 */
    /* Create and add ingress port to ingress VLAN */
    rv = vlan_create_add_port(unit, in_vlan, ingress_port);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vlan_create_add_port(): %s.\n",bcm_errmsg(rv));
        return rv;
    }

	/* Enable MPLS Lookup for incoming packet */
    BCM_IF_ERROR_RETURN(bcm_l2_tunnel_add(unit, local_mac_in, in_vlan));

    /* Create and add egress port to egress VLAN */
    rv = vlan_create_add_port(unit, out_vlan, primary_egress_port);
    if (BCM_FAILURE(rv)) {
        printf("\nError in vlan_create_add_port(): %s.\n",bcm_errmsg(rv));
        return rv;
    }

    /* Create egress L3 interface */
    rv = create_l3_interface(unit, BCM_L3_ADD_TO_ARL, local_mac, out_vlan, &intf_id);
    if (BCM_FAILURE(rv)) {
        printf("\nError in create_l3_interface: %s.\n",bcm_errmsg(rv));
        return rv;
    }
    printf("primary l3 egr intf = %d\n", intf_id);

    /* Create Egress object with outgoing label */
    rv = create_egr_obj_with_route_label(unit, intf_id, nh_mac, primary_egress_port, out_tunnel_label, &egr_obj_id);
    if (BCM_FAILURE(rv)) {
        printf("\nError in create_egr_obj_with_route_label: %s.\n",bcm_errmsg(rv));
        return rv;
    }
	primary_egr_obj = egr_obj_id;
    printf("primary l3 egr obj = %d\n", primary_egr_obj);

    rv = bcm_failover_egress_set(unit, primary_egr_obj, &failover_l3_egress);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_failover_egress_set(): %s.\n",bcm_errmsg(rv));
        return rv;
    }

    /* MPLS label lookup and SWAP operation */
    bcm_mpls_tunnel_switch_t_init (&tunnel_switch);
    tunnel_switch.label   = in_tunnel_label;  /* Incoming MPLS label */
    tunnel_switch.port    = BCM_GPORT_INVALID;
    tunnel_switch.action  = BCM_MPLS_SWITCH_ACTION_SWAP;
    tunnel_switch.egress_if = primary_egr_obj;  /* egress object contains the out label info */
    rv = bcm_mpls_tunnel_switch_add(unit, &tunnel_switch);
    if (BCM_FAILURE(rv)) {
        printf("\nError in bcm_mpls_tunnel_switch_add(): %s.\n",bcm_errmsg(rv));
        return rv;
    }

    return BCM_E_NONE;
}

bcm_error_t
clear_lsr_swap_frr(int unit)
{
    bcm_error_t rv = BCM_E_NONE;
	bcm_l3_egress_t egr;
    bcm_mpls_tunnel_switch_t tunnel_switch;

    bcm_mpls_tunnel_switch_t_init (&tunnel_switch);
    tunnel_switch.label   = in_tunnel_label;  /* Incoming MPLS label */
    BCM_IF_ERROR_RETURN(bcm_mpls_tunnel_switch_get(unit, &tunnel_switch));
	BCM_IF_ERROR_RETURN(bcm_mpls_tunnel_switch_delete(unit, &tunnel_switch));
	BCM_IF_ERROR_RETURN(bcm_l3_egress_get(unit, tunnel_switch.egress_if, &egr));
	BCM_IF_ERROR_RETURN(bcm_failover_egress_status_set(unit, tunnel_switch.egress_if, FALSE));
	BCM_IF_ERROR_RETURN(bcm_failover_egress_clear(unit, tunnel_switch.egress_if));
	BCM_IF_ERROR_RETURN(clear_egr_obj(unit, tunnel_switch.egress_if));
	BCM_IF_ERROR_RETURN(clear_l3_interface(unit, egr.intf));
	BCM_IF_ERROR_RETURN(vlan_destroy_remove_port(unit, out_vlan, primary_egress_port));
	BCM_IF_ERROR_RETURN(vlan_destroy_remove_port(unit, failover_out_vlan, failover_egress_port));
	BCM_IF_ERROR_RETURN(vlan_destroy_remove_port(unit, in_vlan, ingress_port));
    BCM_IF_ERROR_RETURN(bcm_l2_tunnel_delete(unit, local_mac_in, in_vlan));

    return rv;
}

void test_verify(int unit)
{
	bcm_error_t rv = BCM_E_NONE;
    char   str[512];
	int expected_packet_length;
    expected_packets[0] = expected_egress_packet1;
    expected_packets[1] = expected_egress_packet2;

    rv = registerPktioRxCallback(unit);
    if (BCM_FAILURE(rv)) {
        printf("registerPktioRxCallback() FAILED: %s\n", bcm_errmsg(rv));
        return rv;
    }

	/* create flex ctr and attach to primary l3 egress nexthop */
	rv = config_l3_egress_flexctr(unit, primary_egr_obj, &stat_counter_id);
    if (BCM_FAILURE(rv)) {
        printf("ERROR: config_l3_egress_flexctr() : %s.\n", bcm_errmsg(rv));
    }

    /* Disable Protection Switching, choose primary nexthop */
    printf("Disable Protection Switching, choose primary-path\n");
    rv = bcm_failover_egress_status_set(unit, primary_egr_obj, FALSE);
    if (BCM_FAILURE(rv)) {
        printf("ERROR: bcm_failover_egress_status_set() : %s.\n", bcm_errmsg(rv));
        return rv;
    }

    printf("\na) Sending MPLS packet with TWO labels to ingress_port:%d\n", ingress_port);
    snprintf(str, 512, "tx 1 pbm=%d data=0x0000000011110000000002028100000B884700111002000AA1404500003C67620000FE01BE760A3A40010A3A42730000550A000100516162636465666768696A6B6C6D6E6F7071727374757677616263646566676869; sleep quiet 1", ingress_port);
    bshell(unit, str);
    bshell(unit, "sleep quiet 1");

	expected_packet_length = 90;
    rv = check_flexctr(unit, stat_counter_id, expected_packet_length, &test_failed);
    if (BCM_FAILURE(rv)) {
        printf("check_flexctr() FAILED: %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* Remove the flex counter from primary l3 egress object */
    rv = clear_l3_egress_flexctr(unit, primary_egr_obj, stat_counter_id);
    if (BCM_FAILURE(rv)) {
        printf("clear_l3_egress_flexctr() failed.\n");
        return rv;
    }

    /* Switch From Primary to Protection */
    printf("Switch-over from primary-path to failover/protection-path\n");
    rv = bcm_failover_egress_status_set(unit, primary_egr_obj, TRUE);
    if (BCM_FAILURE(rv)) {
        printf("ERROR: bcm_failover_egress_status_set() : %s.\n", bcm_errmsg(rv));
        return rv;
    }

	/* create flex counter and attach to failover l3 egress object */
	rv = config_l3_egress_flexctr(unit, primary_egr_obj+fixed_nh_offset, &stat_counter_id_1);
    if (BCM_FAILURE(rv)) {
        printf("ERROR: config_l3_egress_flexctr() : %s.\n", bcm_errmsg(rv));
        return rv;
    }

    printf("\na) ReSending MPLS packet with TWO labels to ingress_port:%d\n", ingress_port);
    snprintf(str, 512, "tx 1 pbm=%d data=0x0000000011110000000002028100000B884700111002000AA1404500003C67620000FE01BE760A3A40010A3A42730000550A000100516162636465666768696A6B6C6D6E6F7071727374757677616263646566676869; sleep quiet 1", ingress_port);
    bshell(unit, str);
    bshell(unit, "sleep quiet 1");

	expected_packet_length = 94;
    rv = check_flexctr(unit, stat_counter_id_1, expected_packet_length, &test_failed);
    if (BCM_FAILURE(rv)) {
        printf("check_flexctr() FAILED: %s\n", bcm_errmsg(rv));
        return rv;
    }

    /* Remove the flex counter from failover l3 egress object */
    rv = clear_l3_egress_flexctr(unit, primary_egr_obj+fixed_nh_offset, stat_counter_id_1);
    if (BCM_FAILURE(rv)) {
        printf("clear_l3_egress_flexctr() failed.\n");
        return rv;
    }
    printf("\n------------------------------------------------------------- \n");
    printf("    RESULT OF L3MPLS LSR FAST REROUTE VERIFICATION  ");
    printf("\n------------------------------------------------------------- \n");
    printf("Test = [%s]", !test_failed? "PASS":"FAIL");
    printf("\n------------------------------------- \n");

    if (!test_failed)
        return BCM_E_NONE;
    else
        return BCM_E_FAIL;
}

/*
 * Clean up pre-test setup.
 */
bcm_error_t test_cleanup(int unit)
{
    bcm_error_t rv = BCM_E_NONE;

	/* unregister Pktio callback */
    unregisterPktioRxCallback(unit);

    /* Remove the l3 mpls label swap related configuration */
	if (BCM_FAILURE(rv = clear_lsr_swap_frr(unit))){
        printf("clear_lsr_swap_frr() failed.\n");
        return rv;
	}

    /* Remove the field configiuration */
	BCM_IF_ERROR_RETURN(clear_field_resource(unit, ifp_group, ifp_entry, 2));

    /* Remove the port loopback configiuration */
    BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, ingress_port, BCM_PORT_LOOPBACK_NONE));
    BCM_IF_ERROR_RETURN(bcm_port_discard_set(unit, ingress_port, BCM_PORT_DISCARD_NONE));
    BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, egress_ports[0], BCM_PORT_LOOPBACK_NONE));
    BCM_IF_ERROR_RETURN(bcm_port_loopback_set(unit, egress_ports[1], BCM_PORT_LOOPBACK_NONE));

    return BCM_E_NONE;
}
/*
 * execute:
 *  This function does the following
 *  a) test setup
 *  b) l3 mpls lsr fast reroute configuration (Done in config_lsr_swap_frr())
 *  c) demonstrates the functionality(done in test_verify()).
 *  d) demonstrates the teardown l3 mpls lsr fast reroute configure sequence(Done in test_cleanup())
 */
bcm_error_t
execute(void)
{
    int unit = 0;
    bcm_error_t rv = BCM_E_NONE;

    print "~~~ #1) test_setup(): ** start **";
    if (BCM_FAILURE((rv = test_setup(unit)))) {
        printf("test_setup() failed.\n");
        return rv;
    }
    print "~~~ #1) test_setup(): ** end **";

    print "~~~ #2) config_lsr_swap_frr(): ** start **";
    if (BCM_FAILURE((rv = config_lsr_swap_frr(unit)))) {
        printf("config_lsr_swap_frr() failed.\n");
        return rv;
    }
    print "~~~ #2) config_lsr_swap_frr(): ** end **";

    print "~~~ #3) test_verify(): ** start **";
    test_verify(unit);
    print "~~~ #3) test_verify(): ** end **";

    print "~~~ #4) test_cleanup(): ** start **";
    if (BCM_FAILURE(rv = test_cleanup(unit))) {
         printf("test_cleanup() failed.\n");
         return rv;
    }
    print "~~~ #4) test_cleanup(): ** end **";

    return BCM_E_NONE;
}

const char *auto_execute = (ARGC == 1) ? ARGV[0] : "YES";
if (!sal_strcmp(auto_execute, "YES")) {
  print "execute(): Start";
  print execute();
  print "execute(): End";
}

