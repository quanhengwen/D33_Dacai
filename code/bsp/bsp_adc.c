/**
 **************************************************************************************************
 * @file        bsp_adc.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */

#include "bsp_conf.h"
#include "bsp_adc.h"
#include "clog.h"

/**
 * @addtogroup    XXX 
 * @{  
 */

/**
 * @addtogroup    bsp_adc_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_adc_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_adc_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup       bsp_adc_Private_Types
 * @brief         
 * @{  
 */


/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Private_Variables 
 * @brief         
 * @{  
 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;


bsp_adc_data_t BSP_ADC_Value[BSP_ADC_CHANNEL_COUNT];
uint16_t bsp_adcspace[512];

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static void bsp_adc_calc(void);
/**
 * @}
 */

/**
 * @defgroup      bsp_adc_Functions 
 * @brief         
 * @{  
 */
void BSP_ADC_Init(void)
{
	// ---------- DMA Init -----
	/* DMA controller clock enable */
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA2_Stream0_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);	
	// --------------------------
	ADC_ChannelConfTypeDef sConfig = {0};

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 2;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = DISABLE;
	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_10;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}	
	
	sConfig.Channel = ADC_CHANNEL_11;
	sConfig.Rank = 2;
	sConfig.SamplingTime = ADC_SAMPLETIME_84CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	
	HAL_ADC_Start_DMA(&hadc1, (uint32_t * )bsp_adcspace, 512);
}



void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if(adcHandle->Instance==ADC1)
	{
		/* USER CODE BEGIN ADC1_MspInit 0 */
   
		/* USER CODE END ADC1_MspInit 0 */
		/* ADC1 clock enable */
		__HAL_RCC_ADC1_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**ADC1 GPIO Configuration
		PC0     ------> ADC1_IN10
		PC1     ------> ADC1_IN11
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		/* ADC1 DMA Init */
		/* ADC1 Init */
		hdma_adc1.Instance = DMA2_Stream0;
		hdma_adc1.Init.Channel = DMA_CHANNEL_0;
		hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
		hdma_adc1.Init.Mode = DMA_CIRCULAR;
		hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
		hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
		if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

		/* USER CODE BEGIN ADC1_MspInit 1 */

		/* USER CODE END ADC1_MspInit 1 */
	}
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{
	if(adcHandle->Instance==ADC1)
	{
		/* USER CODE BEGIN ADC1_MspDeInit 0 */

		/* USER CODE END ADC1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_ADC1_CLK_DISABLE();

		/**ADC1 GPIO Configuration
		PC0     ------> ADC1_IN10
		PC1     ------> ADC1_IN11
		*/
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_1);

		/* ADC1 DMA DeInit */
		HAL_DMA_DeInit(adcHandle->DMA_Handle);
		/* USER CODE BEGIN ADC1_MspDeInit 1 */

		/* USER CODE END ADC1_MspDeInit 1 */
	}
}


void BSP_ADC_DeInit(void)
{

	// ---------GPIO Init ----------------------

	// -----------------------------------------	

}


void BSP_ADC_DisableIRQ(void)
{
	
}

void BSP_ADC_EnableIRQ(void)
{
	
}

static void bsp_adc_calc(void)
{
	uint32_t sum[2] = {0 , 0};
	for(uint16_t i = 0 ; i < 256 ; i ++)
	{
		sum[0] += bsp_adcspace[i* 2];
		sum[1] += bsp_adcspace[i * 2 + 1];
	}
	
	
	BSP_ADC_Value[BSP_ADC_CHANNEL_0].average = (uint16_t )(sum[0] / 256);
	BSP_ADC_Value[BSP_ADC_CHANNEL_1].average = (uint16_t )(sum[1] / 256);
	
	BSP_ADC_Value[BSP_ADC_CHANNEL_0].real_mv = (float)(0.805664f * BSP_ADC_Value[BSP_ADC_CHANNEL_0].average);
	BSP_ADC_Value[BSP_ADC_CHANNEL_1].real_mv = (float)(0.805664f * BSP_ADC_Value[BSP_ADC_CHANNEL_1].average);
}



// -------IRQ ----------------
void ADC_IRQHandler(void)
{
	DEBUG("ADC_IRQHandler\r\n" );
	HAL_ADC_IRQHandler(&hadc1);
	//bsp_adc_addvalue(0);
}

/*
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc->Instance == ADC1)
	{
		
		//DEBUG("HAL_ADC_ConvCpltCallback\r\n");
	}
}
*/

void DMA2_Stream0_IRQHandler(void)
{
	//DEBUG("DMA2_Stream0_IRQHandler\r\n");
	HAL_DMA_IRQHandler(&hdma_adc1);
	
	bsp_adc_calc();
}

// ---------------------------

// --------------Test -----
void BSP_ADC_ShowValue(void)
{
	DEBUG("sig avr:%d\r\n" , BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].average);
	Clog_Float("sig real:" , BSP_ADC_Value[BSP_ADC_SIG_CHANNEL].real_mv);
	DEBUG("cal avr:%d\r\n" , BSP_ADC_Value[BSP_ADC_CAL_CHANNEL].average);
	Clog_Float("cal real:" , BSP_ADC_Value[BSP_ADC_CAL_CHANNEL].real_mv);
}

// ------------------------



/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

