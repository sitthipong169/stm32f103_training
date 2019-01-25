/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/* Private variables ---------------------------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 360;
uint16_t CCR2_Val = 270;
uint16_t CCR3_Val = 180;
uint16_t CCR4_Val = 90;

uint16_t PrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void GPIO_Timer2_Configuration(void);
static inline void Delay_1us(uint32_t nCnt_1us);
static inline void Delay(uint32_t nCnt_1us);

void Triangle_pulse(void);

/* Private functions ---------------------------------------------------------*/
int main()
{
	/* System Clocks Configuration */
	RCC_Configuration();

	/* GPIO Configuration */
	GPIO_Configuration();

	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;

	/*
	The TIM3 is running at 36 KHz: TIM3 Frequency = TIM3 counter clock/(ARR + 1)
                                                  = 24 MHz / 666 = 36 KHz
	*/

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 720-1;
	// TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_Prescaler = 1-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

      /* PWM2 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	/* TIM2 Chanel 1*/
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* TIM2 Chanel 2*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);


	/* TIM2 Chanel 3*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);


	/* TIM2 Chanel 4*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);

	while(1)
	{
		Triangle_pulse();
	}

}

void RCC_Configuration(void)
{
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* GPIOA and GPIOB clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
						   RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10X_MD
	/*GPIOA Configuration: TIM2 channel1, 2, 3 and 4 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); 

#else
  /* GPIOA Configuration:TIM2 Channel1, 2, 3 and 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
}

void GPIO_Timer1_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10X_MD
	/*GPIOA Configuration: TIM2 channel1, 2, 3 and 4 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); 

#else
	;
#endif
}
void GPIO_Timer2_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10X_MD
	/*GPIOA Configuration: TIM2 channel1, 2, 3 and 4 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); 

#else
	;
#endif
}
void GPIO_Timer3_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10X_MD
	/*GPIOA Configuration: TIM2 channel1, 2, 3 and 4 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); 

#else
	;
#endif
}



static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

static inline void Delay(uint32_t nCnt_1us)
{

      while(nCnt_1us--);
}

void Triangle_pulse(void)
{
	int count = 0;
	while(1)
	{
		TIM2 -> CCR1 = count;
		if(count>=216+1)
		{
			while(count>=36+1)
			{
				count-=18;
				TIM2 -> CCR1 = count;
				Delay_1us(50000);
			}
		}
		count+=18;
		Delay_1us(50000);
	}
}