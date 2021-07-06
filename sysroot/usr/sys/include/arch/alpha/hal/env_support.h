/*
 * @DEC_COPYRIGHT@
 */
/*
 * HISTORY
 * $Log: env_support.h,v $
 * Revision 1.1.17.1  2002/11/08  21:17:36  Rajesh_R
 * 	Added defines for voltage sensors.
 *
 * Revision 1.1.13.3  2002/07/17  22:30:47  Rajesh_R
 * 	Added support for action strings. Removed the high_ prefix for high
 * 	warning and threshold strings for backward compatibility. Fix for
 * 	QAR#93739.
 *
 * Revision 1.1.13.2  2002/04/09  00:08:45  Rajesh_R
 * 	Added threshold support.
 *
 * Revision 1.1.13.1  2001/09/19  18:06:40  Joshua_Smith
 *     Merge from motoos.
 *
 * Revision 1.1.9.5  2001/09/13  20:29:47  Joshua_Smith
 *     Moved internal header information to env_support_internal.h
 *
 * Revision 1.1.9.4  2001/08/03  11:32:04  Joshua_Smith
 *     Added support for global unique IDs. QAR 89195
 *
 * Revision 1.1.9.3  2001/06/21  17:51:42  Joshua_Smith
 *     Added warning and fault thresholds.
 *
 * Revision 1.1.9.2  2001/06/18  17:56:32  Joshua_Smith
 *     Added state change events
 *
 * Revision 1.1.9.1  2001/06/01  13:51:56  Joshua_Smith
 *     Updated functionality to new design specification.
 *
 * Revision 1.1.3.3  2000/10/23  15:10:28  Joshua_Smith
 * 	Changed sensor types
 *
 * Revision 1.1.3.2  2000/10/04  15:00:56  Joshua_Smith
 *     Added simple locking macros
 *
 * Revision 1.1.4.1  2000/09/27  19:38:34  Joshua_Smith
 *     Added defines for additional sensor states. Changed
 *     sensor structure to return ulongs instead of void when
 *     getting sensor info.
 *
 * Revision 1.1.1.1  2000/07/12  15:31:06  Matthew_Waxman
 * *** Initial Branch Revision ***
 *
 * $EndLog$
 */
/*
 * @(#)$RCSfile: env_support.h,v $ $Revision: 1.1.17.1 $ (DEC) $Date: 2002/11/08 21:17:36 $
 */

#ifndef ___ENV_SUPPORT_H__
#define ___ENV_SUPPORT_H__

#if defined (__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Attribute name strings
 */
#define   ENV_SUPPORT_ATTR_NAME         "name"
#define   ENV_SUPPORT_ATTR_CAT          "category"
#define   ENV_SUPPORT_ATTR_SUBCAT       "sub_category"
#define   ENV_SUPPORT_ATTR_PHYSLOC      "phys_location"
#define   ENV_SUPPORT_ATTR_STATUS       "sensor_status"
#define   ENV_SUPPORT_ATTR_DATA         "sensor_data"
#define   ENV_SUPPORT_ATTR_DATA_TYPE    "sensor_data_type"
#define   ENV_SUPPORT_ATTR_LOW_WARN_THRESH  "low_warning_threshold"
#define   ENV_SUPPORT_ATTR_HIGH_WARN_THRESH  "warning_threshold"
#define   ENV_SUPPORT_ATTR_LOW_FAULT_THRESH "low_fault_threshold"
#define   ENV_SUPPORT_ATTR_HIGH_FAULT_THRESH "fault_threshold"
#define   ENV_SUPPORT_ATTR_WARN_ACTION	 "warning_action"
#define   ENV_SUPPORT_ATTR_FAULT_ACTION  "fault_action"


/*
 * Strings used for the attribute 'category'.
 * Definitions are to be used as an index into the
 * 'env_type_list' array.
 */
static char *env_type_list[] ={
  "unknown_type",
  "thermal",
  "power", 
  "current", 
  "fan",
  "voltage"
};

#define ENV_SENSOR_TYPE_UNKNOWN  0
#define ENV_SENSOR_TYPE_THERMAL  1
#define ENV_SENSOR_TYPE_POWER    2
#define ENV_SENSOR_TYPE_CURRENT  3
#define ENV_SENSOR_TYPE_FAN      4
#define ENV_SENSOR_TYPE_VOLTAGE  5 


/*
 * Strings used for attribute 'sensor_status'.
 * Definitions are to be used as an index into the
 * 'env_status_list' array.
 */
static char *env_status_list[] ={
  "unknown_status", 
  "ok", 
  "warning", 
  "fault", 
  "override",
  "standby",
  "disabled", 
  "not_present", 
  "device_broken",
  "unavailable"
};

#define ENV_SENSOR_UNKNOWN      0
#define ENV_SENSOR_OK           1
#define ENV_SENSOR_WARNING      2
#define ENV_SENSOR_FAULT        3
#define ENV_SENSOR_OVERRIDE     4
#define ENV_SENSOR_STANDBY      5
#define ENV_SENSOR_DISABLED     6
#define ENV_SENSOR_NOT_PRESENT  7
#define ENV_SENSOR_BROKEN       8
#define ENV_SENSOR_UNAVAILABLE  9


/*
 * Strings used for the attribute 'sensor_data_type'.
 * Definitions are to be used as an index into the
 * 'env_data_type_list' array.
 */
static char *env_data_type_list[]={
  "unknown_data", 
  "Celsius", 
  "Farenheit", 
  "Kelvin", 
  "rpm", 
  "volts",
  "amps", 
  "cfm", 
  "watts"
};

#define ENV_SENSOR_DATA_UNKNOWN   0
#define ENV_SENSOR_DATA_CELCIUS   1
#define ENV_SENSOR_DATA_FARENHEIT 2
#define ENV_SENSOR_DATA_KELVIN    3
#define ENV_SENSOR_DATA_RPM       4
#define ENV_SENSOR_DATA_VOLTS     5
#define ENV_SENSOR_DATA_AMPS      6
#define ENV_SENSOR_DATA_CFM       7
#define ENV_SENSOR_DATA_WATTS     8


#if defined (__cplusplus)
}
#endif /* __cplusplus */

#endif	/* __ENV_SUPPORT_H__ */


