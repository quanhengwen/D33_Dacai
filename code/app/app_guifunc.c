/**
 **************************************************************************************************
 * @file        app_guifunc.c
 * @author
 * @app_guifunc
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "app_guifunc.h"
#include "app_vibration_exciter.h"
#include "dacai.h"
#include "bsp_adc.h"
#include "bsp_ad7682.h"
#include "app_dvalue.h"
#include "app_cvalue.h"
/**
 * @addtogroup    app_guifunc_Modules 
 * @{  
 */

/**
 * @defgroup      app_guifunc_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_guifunc_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       app_guifunc_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Private_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void app_gui_update(void);
static void app_gui_up_start(void);
static void app_gui_up_d(void);
static void app_gui_up_c(void);

static void app_gui_btn_d_pid(uint8_t status);
static void app_gui_btn_d_back(uint8_t status);


/**
 * @}
 */

/**
 * @defgroup      app_guifunc_Functions 
 * @brief         
 * @{  
 */
// --------- GUI Screen Define ---------- 

#define GUI_SCREEN_START	0
#define GUI_SCREEN_HOME		1
#define GUI_SCREEN_D		2
#define GUI_SCREEN_C		3
#define GUI_SCREEN_OPTION	4

#define GUI_SCREEN_TEST		5


// --------------------------------------
// --------- Button Define --------------
#define GUI_BUTTON_START_TIME	1
#define GUI_BUTTON_START_D		2
#define GUI_BUTTON_START_C		3
#define GUI_BUTTON_START_TEST	4
#define GUI_BUTTON_START_OPTION	5

#define GUI_BUTTON_D_PIDCONTROL	8
#define GUI_BUTTON_D_BACK		9

#define GUI_BUTTON_C_START		3
#define GUI_BUTTON_C_BACK		6

#define GUI_BUTTON_OPTION_BACK  1
#define GUI_BUTTON_OPTION_CALI	7


#define GUI_BUTTON_TEST1	16
#define GUI_BUTTON_TEST2 	17

// ---------- Text Define ---------------
#define GUI_TEXT_D_STANDARD	5
#define GUI_TEXT_D_TEST		6
#define GUI_TEXT_D_D		7
#define GUI_TEXT_D_PROGRASS	10

#define GUI_TEXT_C_VOL		5
#define GUI_TEXT_C_C		7

#define GUI_TEXT_OPTION_SN	6
#define GUI_TEXT_OPTION_VERSION	4

// --------------------------------------

// --------------------------------------

void APP_Gui_Init(void)
{
	Dacai_Button_CallbackRegister(APP_Gui_Button_CB);
	Dacai_HandShake_CallbackRegister(APP_Gui_HandShake_CB);
	Dacai_Rest_CallbackRegister(APP_Gui_Rest_CB);
	Dacai_Init();	
	Dacai_SetRest();
}

void APP_Gui_SetParam(void)
{
	Dacai_SetHandShake();
	//Dacai_SetPowerSaving(1 ,0x0f, 0xff, 30);
	Dacai_SetBuzzer(50);	
	Dacai_GetScreen();
}

void APP_Gui_Button_CB(uint16_t screen_id , uint16_t control_id  , uint8_t status)
{
	switch(screen_id)
	{
		case GUI_SCREEN_START:
			{
				
			}break;
		case GUI_SCREEN_HOME:
			{
				switch(control_id)
				{
					case GUI_BUTTON_START_TIME:
						{
							DEBUG("GUI_BUTTON_START_TIME :%d\r\n" , status);
						}break;
					case GUI_BUTTON_START_D:
						{
							APP_Dvalue_SW();
							DEBUG("GUI_BUTTON_START_D\r\n");
						}break;
					case GUI_BUTTON_START_C:
						{
							APP_Cvalue_SW();
							APP_Cvalue.calc_flag = 1;
							DEBUG("GUI_BUTTON_START_C\r\n");
						}break;
					case GUI_BUTTON_START_TEST:
						{
							DEBUG("GUI_BUTTON_START_TEST\r\n");
						}break;	
					case GUI_BUTTON_START_OPTION:
						{
							DEBUG("GUI_BUTTON_START_OPTION\r\n");
						}break;						
					default:break;
				}				
				
				
			}break;
		case GUI_SCREEN_D:
			{
				switch(control_id)
				{
					case GUI_BUTTON_D_PIDCONTROL:
						{
							app_gui_btn_d_pid(status);
							DEBUG("GUI_BUTTON_D_PIDCONTROL\r\n");
						}break;
					case GUI_BUTTON_D_BACK:
						{
							app_gui_btn_d_back(status);
							APP_Dvalue.calc_flag = 0;
							DEBUG("GUI_BUTTON_D_BACK\r\n");
						}break;					
					default:break;
				}					
			}break;		
		case GUI_SCREEN_C:
			{
				switch(control_id)
				{
					case GUI_BUTTON_C_START:
						{
							DEBUG("GUI_BUTTON_C_START\r\n");
						}break;
					case GUI_BUTTON_C_BACK:
						{
							APP_Cvalue.calc_flag = 0;
							DEBUG("GUI_BUTTON_C_BACK\r\n");
						}break;					
					default:break;
				}					
			}break;			
		case GUI_SCREEN_OPTION:
			{
				switch(control_id)
				{
					case GUI_BUTTON_OPTION_BACK:
						{
							DEBUG("GUI_BUTTON_OPTION_BACK\r\n");
						}break;	
					case GUI_BUTTON_OPTION_CALI:
						{
							
							DEBUG("GUI_BUTTON_OPTION_CALI\r\n");
						}break;
					default:break;
				}					
			}break;					
		case GUI_SCREEN_TEST:
			{
				switch(control_id)
				{
					case GUI_BUTTON_TEST1:
						{
							APP_VirExc_PID_1250();
							DEBUG("GUI_TEST1_BUTTON\r\n");
							
						}break;
					case GUI_BUTTON_TEST2:
						{
							APP_VirExc_PID_50();
							DEBUG("GUI_TEST2_BUTTON\r\n");
						}break;
					default:break;
				}
			}break;
		default:break;
	}
}
	


void APP_Gui_HandShake_CB(void)
{
	
}
void APP_Gui_Rest_CB(void)
{
	
}


typedef enum
{
	APP_Gui_HandShake_Req = 1,
	APP_Gui_HandShake_Resp ,
	APP_Gui_Updata , 
}app_gui_loop_e;


void APP_Gui_Loop(void)   // loop in 20ms
{
	static uint8_t cmd = 0;
	
	
	switch(cmd)
	{
		case APP_Gui_HandShake_Req:
			{
				Dacai_SetHandShake();
				cmd = APP_Gui_HandShake_Resp;
			}break;
		case APP_Gui_HandShake_Resp:
			{
				static uint8_t time_count = 0;
				time_count ++;
				
				if(dacai_gui_info.handshake_flag == 1)
				{
					dacai_gui_info.handshake_flag = 0;
					cmd = APP_Gui_Updata;
					time_count = 0;
				}
				else
				{
					if(time_count > 30)
					{
						cmd = APP_Gui_HandShake_Req;
					}
				}
				
			}break;
		case APP_Gui_Updata:
			{
				app_gui_update();
			}break;
		default:
			{
				cmd = APP_Gui_HandShake_Req;
			}break;
	}
	
}


// ------------- Update -------------
static void app_gui_update(void)
{
	switch(dacai_gui_info.cur_s)
	{
		case GUI_SCREEN_START:app_gui_up_start();break;
		case GUI_SCREEN_HOME:break;
		case GUI_SCREEN_D: app_gui_up_d();break;
		case GUI_SCREEN_C: app_gui_up_c();break;
		case GUI_SCREEN_OPTION:break;
		default:break;
	}
}

static void app_gui_up_start(void)
{
	Dacai_SetScreen(GUI_SCREEN_HOME);
}

static void app_gui_up_d(void)
{
	Dacai_Disable_Updata();
	
	char strbuf[40];

	snprintf(strbuf , 40 , "%.2fmV" , BSP_ADC_Value[BSP_ADC_CAL_CHANNEL].real_mv);
	Dacai_SetTextValue(GUI_SCREEN_D,GUI_TEXT_D_STANDARD,(uint8_t *)strbuf , strlen(strbuf));
	
	snprintf(strbuf , 40 , "%.2fmV" , BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv);
	Dacai_SetTextValue(GUI_SCREEN_D,GUI_TEXT_D_TEST,(uint8_t *)strbuf , strlen(strbuf));
	
	
	
	if(abs((int)(BSP_ADC_Value[BSP_ADC_CAL_CHANNEL].real_mv - 1250.0f)) < 5)
	{
		snprintf(strbuf , 40 , "%.2fpc/N" , APP_Dvalue.D_value);
		Dacai_SetTextValue(GUI_SCREEN_D,GUI_TEXT_D_D,(uint8_t *)strbuf , strlen(strbuf));			
	}
	else
	{
		char temp_str[] = "--.--pc/N";
		Dacai_SetTextValue(GUI_SCREEN_D,GUI_TEXT_D_D,(uint8_t *)temp_str , strlen(temp_str));		
	}
	

	
	Dacai_SetProgressBar(GUI_SCREEN_D , GUI_TEXT_D_PROGRASS,(uint32_t )APP_Dvalue.schedule);
	
	Dacai_Enable_Updata();
}


static void app_gui_up_c(void)
{
	Dacai_Disable_Updata();
	
	char strbuf[40];
	snprintf(strbuf , 40 , "%.2f" , BSP_AD7682_Get_CurValue(BSP_AD7682_C_OUT_CHANNEL));
	Dacai_SetTextValue(GUI_SCREEN_C,GUI_TEXT_C_VOL,(uint8_t *)strbuf , strlen(strbuf));	

	Dacai_Enable_Updata();

}


// -----------------------------------

// ----------Button Func -------------
//GUI_BUTTON_D_PIDCONTROL
static void app_gui_btn_d_pid(uint8_t status)
{
	if(status == 0x01)
	{	
		DEBUG("APP_VirExc_PID_1250\r\n");
		APP_VirExc_PID_1250();
		APP_Dvalue.calc_flag = 1;
	}
	else
	{
		DEBUG("APP_VirExc_PID_50\r\n");
		APP_VirExc_PID_50();
	}
}
//GUI_BUTTON_D_BACK

static void app_gui_btn_d_back(uint8_t status)
{
	APP_VirExc_PID_50();
	
}

	


// -----------------------------------

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

