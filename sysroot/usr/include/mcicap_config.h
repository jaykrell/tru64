/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: mcicap_config.h,v $
 * Revision 1.1.7.1  2003/06/10  13:32:36  Jason_Miller
 * 	Ported file from /sbin/mcutil/include/. QAR 96001.
 *
 * Revision 1.1.2.1  1999/12/08  16:23:59  Jan_Reimers
 * 	Integration into Base OS
 *
 * Revision 1.1.2.3  1993/08/20  16:39:50  Mike_Cattolico
 * 	make safe for C file include
 * 	[1993/08/20  16:39:14  Mike_Cattolico]
 *
 * Revision 1.1.2.2  1993/08/09  21:43:51  Edit_Marcinkech
 * 	Initial revision
 * 	[1993/08/09  20:32:43  Edit_Marcinkech]
 * 
 * $EndLog$
 */

#ifndef MCI_H
#define MCI_H

/* MCI configurator
 *	MCI provides access to a configured media changer.
 *
 *	The open/close interface allows clients to mention
 *	the media changer by name only.  An environment variable
 *	may contain a media capiblities entry or name a file which
 *	will contain an entry describing the named media changer.
 *	If the environment variable is not set, /etc/mcicap is
 *	the default "media cap" file.
 *
 *	MCI also allows clients to register new interfaces.
 *	For an explaination of this feature, please see the manual.
*/


#if defined(__cplusplus)
extern "C" {
#endif

extern MC_ERROR_CODE mci_open(const char *name, media_changer_t **mc);
extern MC_ERROR_CODE mci_close(media_changer_t *mc);
extern MC_ERROR_CODE mci_register(const char *if_name,
				const media_changer_t *(newobject)());

#if defined(__cplusplus)
}
#endif

#endif //MCI_H
