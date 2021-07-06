/*
 * *****************************************************************
 * *                                                               *
 * *   Copyright 2002 Compaq Information Technologies Group, L.P.  *
 * *                                                               *
 * *   The software contained on this media  is  proprietary  to   *
 * *   and  embodies  the  confidential  technology  of  Compaq    *
 * *   Computer Corporation.  Possession, use,  duplication  or    *
 * *   dissemination of the software and media is authorized only  *
 * *   pursuant to a valid written license from Compaq Computer    *
 * *   Corporation.                                                *
 * *                                                               *
 * *   RESTRICTED RIGHTS LEGEND   Use, duplication, or disclosure  *
 * *   by the U.S. Government is subject to restrictions  as  set  *
 * *   forth in Subparagraph (c)(1)(ii)  of  DFARS  252.227-7013,  *
 * *   or  in  FAR 52.227-19, as applicable.                       *
 * *                                                               *
 * *****************************************************************
 */
/*
 * HISTORY
 */

/*
 * Avoid recursive and double includes
 */
#if !defined(__INCLUDE_IP_TCNTL_FUNCPROT)
#define __INCLUDE_IP_TCNTL_FUNCPROT

#ifdef __cplusplus
extern "C" {
#endif
  
#ifdef _KERNEL



/*
 * ioctl() processing routines
 */
int tcntl_flow_req(struct socket *so,
		   struct ifnet *ifp,
		   struct flowreq *flowreq,
		   int length);
int tcntl_filt_req (struct ifnet *ifp,
		    struct filtreq *filtreq,
		    int length);
int tcntl_adspec_req (struct ifnet *ifp,
		      struct adspecreq *adspecreq,
		      int length);
int tcntl_hash_req (struct ifnet *ifp,
		    struct hashreq *hashreq,
		    int length);
int tcntl_listflow_req (struct ifnet *ifp,
			struct listflowreq *listflowreq,
			int length);
int tcntl_listfilt_req (struct ifnet *ifp,
			struct listfiltreq *listfiltreq,
			int length);
int tcntl_config_req (struct ifnet *ifp,
		      struct tcntlconfreq *confreq);
int tcntl_generic_config(struct ifnet *ifp,
			 struct tcntl *tcntl,
			 struct tcntlconfreq *confreq,
			 int index,
			 tcntl_conf_value_t value);

/*
 * Routines for filtering (packet classification)
 */
TCNTL_INLINED_RTN struct tcntl_genflow *TCNTL_HASH_IP4_WF (
    struct tcntl_filt_bucket **fb,
    union ip4_wf_filter_entry *e,
    int *index);
TCNTL_INLINED_RTN struct tcntl_genflow *TCNTL_HASH_IP4_PORT (
    struct tcntl_filt_bucket **fb,
    union ip4_port_filter_entry *e,
    int *index);
TCNTL_INLINED_RTN struct tcntl_genflow *TCNTL_HASH_IP6_FLOW (
    struct tcntl_filt_bucket **fb,
    struct ip6_flow_filter_entry *e,
    int *index);
struct tcntl_genflow *tcntl_classify_tx_ip(
				    struct ifnet *ifq,
				    struct ip *ip_hdr);
struct tcntl_genflow *tcntl_classify_tx_ip6 (
				       struct ifnet *ifq,
				       const struct ip6_hdr *ip6_hdr);

/*
 * General under the hood management routines 
 */
tcntl_error_code_t tcntl_remove_flow(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      struct tcntl_genflow *gflow);
tcntl_error_code_t tcntl_orphan_flow(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int final_cleanup,
		      struct tcntl_genflow *flow);
tcntl_error_code_t tcntl_blast_flow(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      struct tcntl_genflow *gflow);
tcntl_error_code_t tcntl_extincr_flow_refc(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int flow_bucket,
		      tcntl_rhandle_t ext_handle,
		      int tag_scope,
		      struct tcntl_genflow **gflow);
tcntl_error_code_t tcntl_list_flows(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int tag_scope,
		      unsigned int flow_bucket,
		      tcntl_rhandle_t last_handle,
		      unsigned int max_out_handles,
		      void *lookup_ctx,
		      unsigned int *actual_handles,
		      tcntl_rhandle_t *out_handles);
tcntl_error_code_t tcntl_list_flow_hth(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int flow_bucket,
		      void **lookup_ctx,
		      unsigned int *table_slots,
		      unsigned int *max_entries,
                      unsigned int *curr_entries,
		      unsigned int *flags);
tcntl_error_code_t tcntl_examine_flow_slot(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int flow_bucket,
		      unsigned int flow_slot,
		      void *lookup_ctx,
		      unsigned int *flow_count,
		      unsigned long *hit_count,
		      unsigned long *miss_count,
		      unsigned long *collision_count,
		      unsigned int *bucket_flags);
tcntl_error_code_t tcntl_examine_specific_flow(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int flow_bucket,
		      tcntl_rhandle_t rhandle,
                      unsigned int *flow_class,
		      void **tag,
                      unsigned int *tag_scope,
                      unsigned long *refc,
		      void *device_data,
		      unsigned int max_output_data,
		      unsigned int *actual_data_len);
tcntl_error_code_t tcntl_examine_specific_filters(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int flow_bucket,
		      tcntl_rhandle_t rhandle,
                      tcntl_fhandle_t *last_filter,
		      unsigned int max_output,
		      unsigned int *actual_output_filtlen,
		      tcntl_filtspec_t *filtvec);
tcntl_error_code_t tcntl_list_filter_hth(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int filter_bucket,
		      void **lookup_ctx,
		      unsigned int *table_slots,
		      unsigned int *max_entries,
                      unsigned int *curr_entries,
		      unsigned int *flags);
tcntl_error_code_t tcntl_examine_filter_slot(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int filter_bucket,
		      unsigned int filter_slot,
		      void *lookup_ctx,
		      unsigned int *filter_count,
		      unsigned long *hit_count,
		      unsigned long *miss_count,
		      unsigned long *collision_count,
		      unsigned int *bucket_flags);
tcntl_error_code_t tcntl_init_flow_hash(
		      struct tcntl *tctl,
		      unsigned short flow_table_index,
		      unsigned int table_slots,
		      unsigned int max_entries,
		      unsigned int flags,
		      struct tcntl_flow_bucket **flow_table);
tcntl_error_code_t tcntl_delete_flow_hash(
   		      struct tcntl *tctl,
		      struct tcntl_flow_bucket *fb);
tcntl_error_code_t tcntl_init_filt_hash(
		      struct tcntl *tctl,
		      unsigned int table_type,
		      unsigned int table_slots,
		      unsigned int max_entries,
		      unsigned int flags,
		      struct tcntl_filt_bucket **filt_table);
tcntl_error_code_t tcntl_delete_filt_hash(
   		      struct tcntl *tctl,
		      struct tcntl_filt_bucket *fib);
tcntl_error_code_t tcntl_move_flow_hash(
		      struct tcntl *tcntl,
		      unsigned int flow_table,
		      struct tcntl_flow_bucket *dest_table);
tcntl_error_code_t tcntl_move_filter_hash(
		      struct ifnet *ifp,
		      unsigned int filter_table,
		      struct tcntl_filt_bucket *dest_table);
unsigned long tcntl_allocate_filter_ids(
		      struct tcntl *tcntl,
		      unsigned long block_size,
                      unsigned int *laps_count);
unsigned long tcntl_allocate_flow_ids(
		      struct tcntl *tcntl,
		      unsigned long block_size);
tcntl_error_code_t tcntl_admit_flow(
		     struct ifnet *ifp,
		     struct tcntl *tcntl,
		     unsigned int table_index,
		     struct tcntl_genflow *gflow);
tcntl_error_code_t tcntl_admit_filter(
		      struct tcntl *tcntl,
		      unsigned int filter_table,
		      struct tcntl_filter_entry *filter);
tcntl_error_code_t tcntl_zap_filter(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      struct tcntl_genflow *gflow,
		      tcntl_fhandle_t fhandle);
tcntl_error_code_t tcntl_install_filter(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      unsigned int filter_table,
		      struct tcntl_genflow *flow,
		      struct tcntl_filter_entry *filt,
		      tcntl_fhandle_t *filt_handle);
tcntl_error_code_t tcntl_remove_filter(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      struct tcntl_filter_entry *filt);
tcntl_error_code_t tcntl_purge_flowtable(
		      struct ifnet *ifp,
		      struct tcntl *tcntl,
		      struct tcntl_flow_bucket *flow_table,
		      void *tag,
                      unsigned char tag_scope);
tcntl_error_code_t tcntl_initialize_device(
		      struct ifnet *ifp,
		      tcntl_device_initialize_rtn_t dev_init);
tcntl_error_code_t tcntl_delete_tcntl(struct ifnet *ifp,
				      struct tcntl *tcntl);
tcntl_error_code_t tcntl_deactivate_device(struct ifnet *ifp);
tcntl_error_code_t tcntl_setup(void);
tcntl_error_code_t tcntl_rundown(void);


 
#endif /* _KERNEL */             

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !defined(__INCLUDE_IP_TCNTL_FUNCPROT) */
