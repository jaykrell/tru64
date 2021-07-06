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
 * @(#)$RCSfile: comet.h,v $ $Revision: 1.1.15.1 $ (DEC) $Date: 1999/11/12 17:38:33 $
 */

/* /usr/sys/include/io/hw/dec/ws/comet.h */

#ifndef _COMET_H_
#define _COMET_H_

/* graphics header files */
#include <sys/workstation.h>
#include <sys/inputdevice.h>
#include <sys/wsdevice.h>
#include <io/common/devdriver.h>

#define	COMET_INFO_VARIANT_UNKNOWN		0
#define	COMET_INFO_VARIANT_4D10T		1
#define	COMET_INFO_VARIANT_ELSA_GLORIA		2
#define	COMET_INFO_VARIANT_P2V			3
#define	COMET_INFO_VARIANT_COUNT		4

#define COMET_IOC_GET_VIDEO_MODES 1
#define COMET_IOC_SET_VIDEO_MODE  2
#define	COMET_IOC_GET_VARIANT	  3
#define	COMET_IOC_GET_MEM_SIZE	  4

typedef struct
  {
    unsigned char  pixel_depth; /* 8, 15, 32 */
    unsigned char  visual;      /* TRUECOLOR or PSEUDO COLOR */
    unsigned char  freq;        /* hz */
    unsigned short x_res;
    unsigned short y_res;
  } comet_video_mode_t;

typedef struct
  {
    int			req_mode_count;
    comet_video_mode_t	*vid_modes;
    int 		ret_mode_count;
  } comet_ioc_get_modes_t;

typedef struct
  {
    comet_video_mode_t	*vid_mode;
  } comet_ioc_set_mode_t;

typedef struct 
  {
    short         screen;
    short         cmd;
    union 
      {
	comet_ioc_get_modes_t  get_mode;
        comet_ioc_set_mode_t  set_mode;
	unsigned int		get_variant;
	unsigned int		get_mem_size;
      } info;
  } comet_ioc_t;

/* Server/driver shared data */

typedef struct 
  {
    unsigned int          text_mem_size;
    bus_addr_t            module_dma_addr;
    unsigned short        dma_limited;
  } comet_server_info_t;


#define COMET_IOC_PRIVATE	_IOWR('w', (0|IOC_S), comet_ioc_t)

#define COMET_IOC_FLASH         0
#define COMET_IOC_DMA_REQ       1
#define COMET_IOC_LOCK_BUFFER   2
#define COMET_IOC_UNLOCK_BUFFER 3
#define COMET_IOC_LOAD_WAT      4
#define COMET_IOC_SET_OVL_CMAP  5
#define COMET_IOC_OVL_ONOFF     6

#define COMET_OVL_OFF 0
#define COMET_OVL_ON 1

#define TRUECOLOR 1
#define PSEUDO_COLOR 0 

#endif /* _COMET_H_ */

/*
 * HISTORY
 */
