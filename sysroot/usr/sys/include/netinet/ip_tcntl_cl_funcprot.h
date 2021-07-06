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
#if !defined(__INCLUDE_IP_TCNTL_CL_FUNCPROT)
#define __INCLUDE_IP_TCNTL_CL_FUNCPROT

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL


/*
 * The following function prototypes are part of the callback
 * interface from generic traffic control
 */
tcntl_error_code_t cl_admit_flow(struct ifnet *ifp,
				 struct tcntl *tcntl,
				 struct flowreq *flowreq,
				 unsigned int flowreq_len,
				 unsigned int flow_table,
				 void *nhops,
				 IS_specbody_t *i_spec,
				 IS_tspbody_t *i_tsp,
				 IS_adsbody_t *i_ads,
				 struct tcntl_genflow *gflow);

tcntl_error_code_t cl_modify_flow(struct ifnet *ifp,
				  struct tcntl *tcntl,
				  struct flowreq *flowreq,
				  unsigned int flowreq_len,
				  unsigned int flow_table,
				  void *nhops,
				  IS_specbody_t *i_spec,
				  IS_tspbody_t *i_tsp,
				  IS_adsbody_t *i_ads,
				  struct tcntl_genflow *gflow);

tcntl_error_code_t cl_remove_flow(struct ifnet *ifp,
				  struct tcntl *tcntl,
				  unsigned int flow_table,
				  struct tcntl_genflow *gflow);

tcntl_error_code_t cl_examine_flow(struct ifnet *ifq,
				   struct tcntl *tctl,
				   unsigned int flow_table,
				   struct tcntl_genflow *gflow,
				   unsigned int flow_params_maxsize,
				   void *flow_params,
				   unsigned int *actual_flow_params);

tcntl_error_code_t cl_get_adspec(struct ifnet *ifp,
				 struct tcntl *tcntl,
				 unsigned int flow_table,
				 struct adspecreq *adspecreq,
				 unsigned int adspec_input_len);

tcntl_error_code_t cl_device_initialize(struct ifnet *ifp,
					struct tcntl *tcntl);

tcntl_error_code_t cl_device_rundown(struct ifnet *ifp,
				     struct tcntl *tcntl);

tcntl_error_code_t cl_config_req(struct ifnet *ifp,
				 struct tcntl *tcntl,
				 struct tcntlconfreq *confreq,
				 int index,
				 tcntl_conf_value_t value);

/*
 * This is the routine that polices traffic during IP output 
 * for devices with traffic control enabled.
 */
int cl_if_enqueue (
    struct ifnet *ifp,
    struct mbuf *m,
    int drop_best_effort,
    struct tcntl_genflow *gflow,
    int packet_len);



#endif /* _KERNEL */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !defined(__INCLUDE_IP_TCNTL_CL_FUNCPROT) */
