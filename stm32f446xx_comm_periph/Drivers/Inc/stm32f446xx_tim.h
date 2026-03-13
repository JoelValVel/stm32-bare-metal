#ifndef INC_STM32F446XX_TIM_H_
#define INC_STM32F446XX_TIM_H_

#include "stm32f446xx.h"
#include "stm32f446xx_rcc.h"
#include "stm32f446xx_nvic.h"


#define TIM_IS_BASIC_TIMER(x)	(((x) == TIM6) || ((x) == TIM7))

#define TIM_IS_GP_TIMER(x)		(((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5)  || \
								 ((x) == TIM9) || ((x) == TIM10) || ((x) == TIM11) || ((x) == TIM12) || \
								 ((x) == TIM13)|| ((x) == TIM14) \
								)

#define TIM_IS_ADV_TIMER(x)		(((x) == TIM1) || ((x) == TIM8))

#define TIM_HAS_MS_FUNCTIONALITY(x)		(((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5)  || \
										 ((x) == TIM1) || ((x) == TIM8) \
										)

/*
 * No channels:
 *  - Basic Timers: TIM6 y TIM7
 *
 * CH1:
 * 	- GP Timers (16bits): TIM10/11/13/14
 *
 * CH1/2:
 * 	- GP Timers (16bits): TIM9 y TIM12 / TIM 3 y TIM4
 * 	- GP Timers (32bits): TIM2 y TIM5
 * 	- ADV Timers (16bits): TIM1 y TIM8
 *
 * CH1/2/3:
 * 	- GP Timers (16bits): TIM3 y TIM4
 * 	- GP Timers (32bits): TIM2 y TIM5
 * 	- ADV Timers (16bits): TIM1 y TIM8
 *
 * CH1/2/3/4:
 * 	- GP Timers (16bits): TIM  y TIM4
 * 	- GP Timers (32bits): TIM2 y TIM5
 * 	- ADV Timers (16bits): TIM1 y TIM8
 */
#define TIM_HAS_CH1(x)			(((x) != TIM6) && ((x) != TIM7))
#define TIM_HAS_CH2(x)			(((x) == TIM1) || ((x) == TIM8) || \
								((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5)  || \
								((x) == TIM9) || ((x) == TIM12) \
								)

#define TIM_HAS_CH3(x)			(((x) == TIM1) || ((x) == TIM8) || \
								((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5) \
								)

#define TIM_HAS_CH4(x)			(((x) == TIM1) || ((x) == TIM8) || \
								((x) == TIM2) || ((x) == TIM3)  || ((x) == TIM4)  || ((x) == TIM5) \
								)




typedef enum{
		TIM_EVENT_UI   = 0,    // Update event
	    TIM_EVENT_CC1I = 1,    // Capture/Compare 1 event
	    TIM_EVENT_CC2I = 2,    // Capture/Compare 2 event
	    TIM_EVENT_CC3I = 3,    // Capture/Compare 3 event
	    TIM_EVENT_CC4I = 4,    // Capture/Compare 4 event
	    TIM_EVENT_COMI = 5,    // COM event (solo TIM1 y TIM8)
	    TIM_EVENT_TI   = 6,    // Trigger event
	    TIM_EVENT_BI   = 7,    // Break event (solo TIM1 y TIM8)
	    TIM_EVENT_CC1O = 9,   // Capture/Compare 1 overcapture
	    TIM_EVENT_CC2O = 10,  // Capture/Compare 2 overcapture
	    TIM_EVENT_CC3O = 11,  // Capture/Compare 3 overcapture
	    TIM_EVENT_CC4O = 12,  // Capture/Compare 4 overcapture
}TIM_Event_t;

/*
 * @TIM_CouterMode
 */
typedef enum{
	TIM_CouterMode_CenterAlign1 = 1,
	TIM_CouterMode_CenterAlign2,
	TIM_CouterMode_CenterAlign3,
	TIM_CouterMode_UP,
	TIM_CouterMode_DOWN

}TIM_CouterMode_t;

/*
 * @TIM_CHANNELS
 */

typedef enum{
	TIM_CH1,
	TIM_CH2,
	TIM_CH3,
	TIM_CH4,
}TIM_Channels_t;

/*
 * @TIM_ICPolarity
 */
typedef enum{
	TIM_ICPolarity_RE,
	TIM_ICPolarity_FE,
	TIM_ICPolarity_RFE
}TIM_ICPolarity_t;

/*
 * @TIM_ICSelection
 */
typedef enum{
	TIM_ICSelection_Direct = 1,
	TIM_ICSelection_Indirect,
	TIM_ICSelection_TRC
}TIM_ICSelection_t;

/*
 * @TIM_ICPrescaler
 */
typedef enum{
	TIM_ICPrescaler_NONE,
	TIM_ICPrescaler_2,
	TIM_ICPrescaler_4,
	TIM_ICPrescaler_8
}TIM_ICPrescaler_t;

/*
 * @TIM_ICFilter
 */
typedef enum{
	TIM_ICFilter_NONE,
	TIM_ICFilter_Fck_int_2,
	TIM_ICFilter_Fck_int_4,
	TIM_ICFilter_Fck_int_8,
	TIM_ICFilter_Fdts_div2_6,
	TIM_ICFilter_Fdts_div2_8,
	TIM_ICFilter_Fdts_div4_6,
	TIM_ICFilter_Fdts_div4_8,
	TIM_ICFilter_Fdts_div8_6,
	TIM_ICFilter_Fdts_div8_8,
	TIM_ICFilter_Fdts_div16_5,
	TIM_ICFilter_Fdts_div16_6,
	TIM_ICFilter_Fdts_div16_8,
	TIM_ICFilter_Fdts_div32_5,
	TIM_ICFilter_Fdts_div32_6,
	TIM_ICFilter_Fdts_div32_8
}TIM_ICFilter_t;


/*
 * @TIM_OCModes
 */
typedef enum
{
	TIM_OCMode_Frozen,
	TIM_OCMode_Active,
	TIM_OCMode_Inactive,
	TIM_OCMode_Toggle,
	TIM_OCMode_Force_Inactive,
	TIM_OCMode_Force_Active,
	TIM_OCMode_PWM1,
	TIM_OCMode_PWM2
}TIM_OCModes_t;

/*
 * @TIM_OCPolarity
 */
typedef enum
{
	TIM_OCPolarity_Active_HIGH,
	TIM_OCPolarity_Active_LOW
}TIM_OCPolarity_t;

/*
 * @TIM_Trigger
 */
typedef enum
{
	TIM_Trigger_Internal_0,
	TIM_Trigger_Internal_1,
	TIM_Trigger_Internal_2,
	TIM_Trigger_Internal_3,
	TIM_Trigger_Edge_Detector_TI1,
	TIM_Trigger_Filtered_Timer_Input_1,
	TIM_Trigger_Filtered_Timer_Input_2,
	TIM_Trigger_External
}TIM_Trigger_t;

/*
 * @TIM_Slave
 */
typedef enum
{
	TIM_Slave_Mode_Disabled,
	TIM_Slave_Encoder_Mode_1,
	TIM_Slave_Encoder_Mode_2,
	TIM_Slave_Encoder_Mode_3,
	TIM_Slave_Reset_Mode,
	TIM_Slave_Gated_Mode,
	TIM_Slave_Trigger_Mode,
	TIM_Slave_External_Mode1
}TIM_Slave_t;

/*
 * @TIM_MasterOutput
 */
typedef enum
{
	TIM_MasterOutput_Reset,
	TIM_MasterOutput_Enable,
	TIM_MasterOutput_Update,
	TIM_MasterOutput_Compare_Pulse,
	TIM_MasterOutput_OC1REF,
	TIM_MasterOutput_OC2REF,
	TIM_MasterOutput_OC3REF,
	TIM_MasterOutput_OC4REF
}TIM_MasterOutput_t;


/*
 * @TIM_IC struct (Input Capture)
 */

typedef struct
{
	TIM_Channels_t TIM_Channel;        	/*!< Channel. @TIM_CHANNELS */
	TIM_ICPolarity_t TIM_ICPolarity;   	/*!< Polaridad de la deteccion. @TIM_ICPolarity */
	TIM_ICSelection_t TIM_ICSelection;  /*!< Tipo de entrada. @TIM_ICSelection */
	TIM_ICPrescaler_t TIM_ICPrescaler;  /*!< Prescaler. @TIM_ICPrescaler */
	TIM_ICFilter_t TIM_ICFilter;     	/*!< Filtrado. @TIM_ICFilter_t */
}TIM_IC_t;


typedef struct{
	uint16_t TIM_Prescaler;
	uint32_t TIM_Period;
	TIM_CouterMode_t TIM_CounterMode;
}TIM_TimeBase_t;

typedef struct
{
	TIM_Channels_t TIM_Channel;        	/*!< Channel. @TIM_CHANNELS */
	TIM_OCModes_t TIM_OCMode;        	/*!< Modo de salida. @TIM_OCModes */
	TIM_OCPolarity_t TIM_OCPolarity;	/*!< Polaridad. @TIM_OCPolarity */
	uint32_t TIM_Pulse;					/*!< Ancho de pulso en CCRx (0x0000-0xFFFF) */
}TIM_OC_t;


typedef struct{
	TIM_RegDef_t *pTIMx;
	TIM_TimeBase_t TIM_TimeBase;
	TIM_IC_t TIM_InputCapture;
	TIM_OC_t TIM_OutputCompare;
}TIM_Handle_t;


/*			Time base			*/
void TIM_ClkCtrl(TIM_RegDef_t *p_tim_reg, uint8_t status);
void TIM_ITConfig(TIM_RegDef_t *p_tim_reg, uint16_t it_type, uint8_t status);

void TIM_TimeBaseInit(TIM_Handle_t *p_tim_handle);
void TIM_DeInit(TIM_RegDef_t *p_tim_reg);
void TIM_Cmd(TIM_RegDef_t *p_tim_reg, uint8_t status);

void TIM_IRQHandler(TIM_Handle_t *p_tim_handle);
uint8_t TIM_GetITStatus(TIM_RegDef_t *p_reg_def, uint16_t tim_it);
void TIM_ClearITPendingBit(TIM_RegDef_t *p_reg_def, uint16_t tim_it);
void TIM_EventCallback(TIM_Handle_t *p_tim_handle, TIM_Event_t event);


uint32_t TIM_GetCounter(TIM_RegDef_t *p_TIMx);
void TIM_SetCounter(TIM_RegDef_t *p_TIMx, uint32_t counter);
uint32_t TIM_GetCapture(TIM_RegDef_t *p_TIMx, TIM_Channels_t TIM_channel);
void TIM_SetCompare(TIM_RegDef_t *p_TIMx, TIM_Channels_t TIM_channel, uint32_t value);
/*Input capture*/
void TIM_ICInit(TIM_Handle_t *p_tim_handle);
void TIM_OC_Init(TIM_Handle_t *p_tim_handle);

/* Configurar esclavo */
void TIM_InputTrigger(TIM_RegDef_t *pTIMx, TIM_Trigger_t trigger);
void TIM_SlaveMode(TIM_RegDef_t *pTIMx, TIM_Slave_t mode);

/* Configurar maestro */
void TIM_MasterTriggerOutput(TIM_RegDef_t *pTIMx, TIM_MasterOutput_t output);


#endif /* INC_STM32F446XX_TIM_H_ */
