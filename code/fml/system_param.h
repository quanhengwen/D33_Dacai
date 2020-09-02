/**
 **************************************************************************************************
 * @file        system_param.h
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#ifndef _SYSTEM_PARAM_H_
#define _SYSTEM_PARAM_H_

/**
 * @addtogroup    XXX 
 * @{ 
 */
#include "self_def.h"
/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_Exported_Macros 
 * @{  
 */
												
#define SYS_PARAM_SAVE_FLASH_FIRSTHEAD   		0x080C0000
#define SYS_PARAM_SAVE_FLASH_SECONDHEAD			0x080E0000

#define SYSTEMPARAM_CONFIG     0



/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Constants
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Types 
 * @{  
 */
 

 
#pragma pack(1)

typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
}sys_time_t;

typedef struct
{
	uint8_t SNcode[8];
	sys_time_t D_cali_time;
	uint16_t D_caliunit_value;
	uint16_t D_cali_result ; 
	
    uint16_t crc;           /*!< 所有的参数结构体必须按字节对其。且最后一个必须包
                                 含一个uint16_t类型的数据，该数据用于内部存储时的
                                 crc校验和存储，用户在保存参数时不用关心该值数值。*/
}SystemParam_Config_t;
#pragma pack()
/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Variables 
 * @{  
 */
extern SystemParam_Config_t g_SystemParam_Config;
/**
 * @}
 */

/**
 * @defgroup      system_param_Exported_Functions 
 * @{  
 */
void SystemParam_Init(void);

int16_t SystemParam_Read(uint8_t handle);

void SystemParam_Save(void);

void SystemParam_Reset(void);

void SystemParam_Apply(uint8_t handle);
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
