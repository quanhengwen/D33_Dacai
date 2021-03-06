/**
 **************************************************************************************************
 * @file        clog.h
 * @author
 * @version    v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _CLOG_H_
#define _CLOG_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "SEGGER_RTT.h"
/**
 * @addtogroup    clog_Modules 
 * @{  
 */

/**
 * @defgroup      clog_Exported_Macros 
 * @{  
 */
 
#ifdef RTT_DEBUG  

#define  DEBUG(arg...) 			SEGGER_RTT_printf(0, arg)

#else

#define  DEBUG(arg...)			((void)0U)

#endif 

/**
 * @}
 */

/**
 * @defgroup      clog_Exported_Constants
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      clog_Exported_Types 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      clog_Exported_Variables 
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      clog_Exported_Functions 
 * @{  
 */
void Clog_Float(const char * buf ,float  value);
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif



