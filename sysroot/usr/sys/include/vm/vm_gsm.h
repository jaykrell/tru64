/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: vm_gsm.h,v $
 * Revision 1.1.11.1  2003/01/14  15:45:36  Renny_Shen
 * 	Fixed bitfield to remove build warnings when compiling at -std1
 *
 * Revision 1.1.4.3  2002/07/16  19:42:37  Renny_Shen
 * 	gsm_enabled now needs to be 2 to be enabled.
 *
 * Revision 1.1.4.2  2002/05/23  05:19:43  Renny_Shen
 * 	Added first allocated page and GSM user ID to alloc_rec, removed
 * 	partn_id and added n bad pages to GSM MAD, added seg_id to GSM hdr,
 * 	added dump macros
 *
 * Revision 1.1.4.1  2002/03/26  00:41:17  Renny_Shen
 * 	Added debug code
 *
 * Revision 1.1.2.8  2002/02/06  15:10:05  Renny_Shen
 * 	Initial file creation
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: vm_gsm.h,v $ $Revision: 1.1.11.1 $ (DEC) $Date: 2003/01/14 15:45:36 $
 */
#ifndef _VM_VM_GSM_H_
#define _VM_VM_GSM_H_

#include <sys/types.h>
#include <kern/lock.h>
#include <vm/vm_numa.h>
#include <vm/vm_page.h>
#include <vm/vm_tune.h>

/****************************************************************************
 * Debugging related definitions, variables, etc.
 ****************************************************************************/
/*#define TBD            0
#define GSM_SIM        0
#define GSM_DBG        1
#define GSM_DEBUG*/

extern int gsm_developer_debug;
#define GSMD_RTN       0x1
#define GSMD_ERR       0x2
#define GSMD_INFO      0x4
#define GSMD_INIT      0x8
#define GSMD_RUN       0x10
#define GSMD_ALLOC     0x20
#define GSMD_ALL       0xff

#ifdef GSM_DEBUG
#define GSM_MODULE(M)    static const char *module = M
#define GSM_DPRINTF(F,X) if( gsm_developer_debug & GSMD_##F ) dprintf X
#else
#define GSM_MODULE(M)
#define GSM_DPRINTF(F,X)
#endif

/****************************************************************************
 * GSM-related definitions, variables, etc.
 ****************************************************************************/
/*
 * GSM Allocation Record
 */
typedef struct gsm_alloc_rec {
  void                *gsm_addr;      /* Address of allocated memory        */
  struct vm_page      *gsm_pp;        /* First page to be allocated         */
  ulong               gsm_size;       /* Size of allocation                 */
  ulong               gsm_userid;     /* GSM User ID of owner               */
  struct gsm_alloc_rec *gsm_next;     /* Next record                        */
} *gsm_alloc_t;

/*
 * Per-GSM Region Information - the equivalent to the VM MAD structure.
 *
 * Calls to allocate GSM specify the shared memory region form which
 * to allocate. GSM assumes a maximum of one segment per CPU. Because 
 * there may be more than one CPU per RAD depending on the platform,
 * the GSM MAD is not associated with the RAD but with the physical 
 * memory segment.
 *
 * GSM MAD structures are grouped into a array of region info structures
 * and can be indexed by CPU number.
 */
typedef struct gsm_memory_affinity_domain {
  ulong 	      gsm_seg_id;     /* Seg ID for this region             */
  ulong               gsm_seg_pa_base;/* Starting avail PA for this region  */
  ulong               gsm_seg_size_b; /* Segment size for regions           */
  uint                gsm_nallocp;    /* Number of allocated pages          */
  uint                gsm_nbadp;      /* Number of bad pages                */
  uint                gsm_page_rdy:1, /* GSM pages set up                   */
                      gsm_alloc_rdy:1,/* GSM segment header set up          */
                      gsm_local:1,    /* Local segment                      */
                      gsm_unused:29;
  uint                gsm_unused2;    /* buffer for 64 bit alignment        */
  simple_lock_data_t  gsm_slock;      
  struct lockinfo     *gsm_slock_info;
  struct vm_page_array *gsm_vpa;      /* VM page array for this region      */
  gsm_alloc_t         gsm_alloc;      /* Allocations made f/this region     */
  struct vm_page      *gsm_last;      /* Last allocated page in this region */
  struct vm_page      *gsm_q_untested;/* untested pages                     */
} *gsm_mad_t;

/*
 * This macro, similar to the PA_TO_MID macro, takes a physical address and
 * returns the CPU with which the address is associated. The CPU number is 
 * the index into the shared region array from where we get the region's MAD.
 */
#define GSM_PA_TO_CPU(pa) ((((pa >> numa_shift) & numa_shift_mask) | (pa_to_mid_mask & (((pa >> 34) & (0x3 ^ ((pa >> 36) & 0x1))) | ((pa >> 7) & ((pa >> 36) & 0x1))))))

/*
 * The GSM header contains an array of offsets to user control structures
 * and user ID's. Every registered user of GSM will own on element in the 
 * array and use it to point to its control structures in this GSM segment.
 * Users can also use this array to locate peer control structures in 
 * remote segments.
 *
 * All currently defined GSM users must have a unique user ID declared below.
 *
 * GSM_USER_ID_NONE - no user; unused
 */
#define GSM_USER_ID_NONE 0
#define GSM_USER_ID_GSM  1
#define GSM_USER_ID_XPC  2
typedef struct gsm_user_control {
  /* 16 byte alignment */
  ulong               gsm_user_id;    /* ID of owner of user-specific hdr   */
  ulong               gsm_user_data;  /* Offset to user-specific hdr        */
} gsm_user_ctlr;

/*
 * The GSM header occupies the base address of every GSM region. 
 * It contains a "magic" field to verify that the GSM segment is
 * initialized, the current number of registered users of GSM, an
 * array of offsets to GSM user control structures or headers, 
 * and a simple lock to synchronize user access to this array.
 *
 * GSM_MAX_USERS is arbitrarily set to 8 to make the GSM header 128 byte
 * aligned. However, since the allocation of the header ties up the entire
 * first page, in actuality the user controller array can occupy the entire 
 * remainder of the first page. But because remote partitions must copy
 * over the entire GSM header in order to search for the user controller
 * structure, I wanted to limit the amount of data they had to pull to
 * a more reasonable number.
 */
#define GSM_MAGIC      0x47534d6d61676963 /* Hex equivalent to "GSMmagic"    */
#define GSM_MAX_USERS  8               /* Arbitrary numer allowing the GSM   */
                                       /*   GSM header to have 128 byte      */
                                       /*   alignment.                       */
typedef struct gsm_hdr {
  /* 128 byte alignment */
  ulong               gsm_magic;       /* Magic to indicate init'd state     */
  ulong               gsm_seg_id;      /* GSM Segment ID                     */
  int                 gsm_hdr_size;    /* Size of this header in bytes       */
  int                 gsm_num_users;   /* Current # users in this segment    */
  ulong               gsm_pad[13];

  /* 128 byte alignment */
  gsm_user_ctlr       gsm_user_ctlr[GSM_MAX_USERS];
                                       /* Array of user control structures   */
} *gsm_hdr_t;

/*
 * Users of GSM require knowledge of visible local and remote shared memory
 * regions. Upon request, GSM can build and return a hash table of regions,
 * where each element provides information about an individual segment.
 *
 * GSM_LOC_LOCAL and GSM_LOC_REMOTE must occupy the two LSB
 */
#define GSM_LOC_LOCAL  0x1
#define GSM_LOC_REMOTE 0x2
typedef struct gsm_segment {
  ulong               gsm_seg_id;     /* Segment ID                         */
  ulong               gsm_base_pa;    /* Segment base PA                    */
  uint                gsm_size_b;     /* Segment size in bytes              */
  uint                gsm_mid;        /* NUMA region index of GSM region    */
  uint                gsm_rel_loc;    /* Remote or local                    */
  void                *gsm_user_data; /* Ptr to user-specific structure     */
} gsm_seg_l, *gsm_seg_t;

/*
 * GSM check macros
 */
#define GSM_SPT_CHK(action) if(vm_tune_compare(2,vm_gsm_enabled,>)) {action;}
#define GSM_INIT_CHK(action) if(ngsm==0) {action;}
#define GSM_HDR_CHK(hdr, action) if(hdr->gsm_magic!=GSM_MAGIC) {action;}
#define GSM_SEG_CHK(mad, action) if(mad->gsm_seg_id==0) {action;}
#define GSM_INTR_CHK(action) if(AT_INTR_LVL()>0) {action;}
#define GSM_RANGE_CHK(num, hi, action) if(num>hi) {action;}

/*
 * GSM data structure dump macros
 */
#ifdef GSM_DEBUG
#define GSM_PMR_DUMP(F)                                                       \
{                                                                             \
  pmr_t *t;                                                                   \
  int i, j;                                                                   \
                                                                              \
  if( gsm_developer_debug & GSMD_##F ) {                                      \
    for(i=0; i<4; i++) {                                                      \
      dprintf("pmr_rad_table[%d]:\n", i);                                     \
      dprintf("\tpmr_count=0x%x\n", pmr_data.pmr_rad_table[i].pmr_count);     \
      dprintf("\tpmr_sh_count=0x%x\n",                                        \
	      pmr_data.pmr_rad_table[i].pmr_sh_count);                        \
      dprintf("\tpmr_size=0x%lx\n", pmr_data.pmr_rad_table[i].pmr_size);      \
      dprintf("\tpmr_table=0x%p\n", pmr_data.pmr_rad_table[i].pmr_table);     \
      t = pmr_data.pmr_rad_table[i].pmr_table;                                \
      for(j=0; j<pmr_data.pmr_rad_table[i].pmr_count; j++) {                  \
	dprintf("\tpmr[%d]:\n", j);                                           \
	dprintf("\t\tpmr_avail=0x%lx\n", t[j].pmr_avail);                     \
	dprintf("\t\tpmr_pages=0x%lx\n", t[j].pmr_pages);                     \
	dprintf("\t\tpmr_type=0x%lx\n", t[j].pmr_type);                       \
	dprintf("\t\tpmr_vdone=0x%lx\n", t[j].pmr_vdone);                     \
	dprintf("\t\tpmr_base=0x%lx\n", t[j].pmr_base);                       \
	dprintf("\t\tpmr_size=0x%lx\n", t[j].pmr_size);                       \
      }                                                                       \
    }                                                                         \
  }                                                                           \
}

#define GSM_PI_DUMP(F, mod, pi, rid, i)                                       \
{                                                                             \
  if( gsm_developer_debug & GSMD_##F ) {                                      \
    dprintf("%s: rid %d region %d\n", mod, rid, i);                           \
    dprintf("\tbase=0x%lx\n", pi.pi_base);                                    \
    dprintf("\tsize=0x%lx\n", pi.pi_size);                                    \
    dprintf("\tavail=0x%lx\n", pi.pi_avail);                                  \
    dprintf("\tpages=0x%lx\n", pi.pi_pages);                                  \
    dprintf("\ttype=0x%lx\n", pi.pi_type);                                    \
  }                                                                           \
}

#define GSM_REC_DUMP(F, mod, gsmid)                                           \
{                                                                             \
  gsm_alloc_t tmp = gsm_mad_array[gsmid].gsm_alloc;                           \
                                                                              \
  if( gsm_developer_debug & GSMD_##F ) {                                      \
    while( tmp != (gsm_alloc_t)NULL ) {                                       \
      dprintf("%s: tmp_rec=0x%p\n", mod, tmp);                                \
      dprintf("\tgsm_addr=0x%p\n", tmp->gsm_addr);                            \
      dprintf("\tgsm_pp=0x%p\n", tmp->gsm_pp);                                \
      dprintf("\tgsm_size=0x%lx\n", tmp->gsm_size);                           \
      dprintf("\tgsm_userid=0x%lx\n", tmp->gsm_userid);                       \
      dprintf("\tgsm_next=0x%p\n", tmp->gsm_next);                            \
      tmp = tmp->gsm_next;                                                    \
    }                                                                         \
  }                                                                           \
}

#define GSM_MAD_DUMP(F, mod, gsmid, mad, npages)                              \
{                                                                             \
  if( gsm_developer_debug & GSMD_##F ) {                                      \
    dprintf("%s: gsmid=%d mad=0x%p\n", mod, gsmid, mad);                      \
    dprintf("\tgsm_seg_id=0x%lx\n", mad->gsm_seg_id);                         \
    dprintf("\tgsm_seg_pa_base=0x%lx\n", mad->gsm_seg_pa_base);               \
    dprintf("\tgsm_seg_size_b=0x%lx\n", mad->gsm_seg_size_b);                 \
    dprintf("\tgsm_nallocp=0x%x\n", mad->gsm_nallocp);                        \
    dprintf("\tgsm_nbadp=0x%x\n", mad->gsm_nbadp);                            \
    dprintf("\tgsm_page_rdy=0x%x\n", mad->gsm_page_rdy);                      \
    dprintf("\tgsm_alloc_rdy=0x%x\n", mad->gsm_alloc_rdy);                    \
    dprintf("\tgsm_local=0x%x\n", mad->gsm_local);                            \
    if( mad->gsm_local ) {                                                    \
      dprintf("\tgsm_vpa=0x%p\n", mad->gsm_vpa);                              \
      dprintf("\t\t%d pages\n", npages);                                      \
      dprintf("\t\tva_vmp=0x%p\n", gsm_mad->gsm_vpa->va_vmp);                 \
      dprintf("\tgsm_alloc=0x%lx\n", mad->gsm_alloc);                         \
      dprintf("\tgsm_last=0x%p\n", mad->gsm_last);                            \
      dprintf("\tgsm_q_untested=0x%p\n", mad->gsm_q_untested);                \
    }                                                                         \
  }                                                                           \
}

#define GSM_HDR_DUMP(F, mod, hdr)                                             \
{                                                                             \
  int i;                                                                      \
                                                                              \
  if( gsm_developer_debug & GSMD_##F ) {                                      \
    dprintf("%s: gsm_hdr=0x%p\n", mod, hdr);                                  \
    dprintf("\tgsm_magic=0x%lx\n", hdr->gsm_magic);                           \
    dprintf("\tgsm_seg_id=0x%lx\n", hdr->gsm_seg_id);                         \
    dprintf("\tgsm_hdr_size=0x%lx\n", hdr->gsm_hdr_size);                     \
    dprintf("\tgsm_num_users=0x%lx\n", hdr->gsm_num_users);                   \
    dprintf("\tgsm_user_ctlr=0x%p\n", hdr->gsm_user_ctlr);                    \
    for( i=0; i<GSM_MAX_USERS; i++ )                                          \
      if( hdr->gsm_user_ctlr[i].gsm_user_id ) {                               \
        dprintf("\t\tgsm_user_id=0x%lx\n", hdr->gsm_user_ctlr[i].gsm_user_id);\
        dprintf("\t\tgsm_user_data=0x%lx\n", hdr->gsm_user_ctlr[i].gsm_user_data);\
      }                                                                       \
  }                                                                           \
}

#define GSM_SEG_DUMP(F, mod, seg)                                             \
{                                                                             \
  if( gsm_developer_debug & GSMD_##F ) {                                      \
    dprintf("%s: gsm_seg=0x%p\n", mod, seg);                                  \
    dprintf("\tgsm_seg_id=0x%lx\n", seg->gsm_seg_id);                         \
    dprintf("\tgsm_base_pa=0x%lx\n", seg->gsm_base_pa);                       \
    dprintf("\tgsm_size_b=0x%lx\n", seg->gsm_size_b);                         \
    dprintf("\tgsm_mid=0x%lx\n", seg->gsm_mid);                               \
    dprintf("\tgsm_rel_loc=0x%x\n", seg->gsm_rel_loc);                        \
  }                                                                           \
}

#else
#define GSM_PMR_DUMP(F)
#define GSM_PI_DUMP(F, mod, pi, rid, i)
#define GSM_REC_DUMP(F, mod, gsmid)
#define GSM_MAD_DUMP(F, mod, rid, mad, npages)
#define GSM_HDR_DUMP(F, mod, hdr)
#define GSM_SEG_DUMP(F, mod, seg)
#endif

/****************************************************************************
 * Function Prototypes
 ****************************************************************************/
#define       pmap_sh_regions(mid) (pmr_data.pmr_rad_table[mid].pmr_sh_count)
void          gsm_init();
void          gsm_mad_init(int);
void          gsm_post_init(int rid);
int           gsm_get_seg(gsm_seg_t *);
void          gsm_free_seg(gsm_seg_t);
int           gsm_reg_user(gsm_seg_t, void *, ulong);
ulong         gsm_locate_user(ulong, gsm_hdr_t, int);
void          *gsm_contig_malloc(ulong, ulong, ulong, ulong, int);
int           gsm_contig_free(void *, ulong);
void          gsm_shutdown();
gsm_alloc_t   gsm_locate_rec(void *);
void          gsm_print_page_stats();

#endif
