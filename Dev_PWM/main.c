
#include "stm32f10x.h"

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

uint16_t CCR1_Val = 333;
uint16_t PrescalerValue = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);


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
int main(void)
{
  /* System Clocks Configuration */
  RCC_Configuration();

  /* GPIO Configuration */
  GPIO_Configuration();

  /* -----------------------------------------------------------------------
    The TIM3 is running at 36 KHz: TIM3 Frequency = TIM3 counter clock/(ARR + 1)
                                                  = 24 MHz / 2400 = 10 KHz
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100
  ----------------------------------------------------------------------- */
  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 2399;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);

  // int i = 333;
  	uint16_t cnt = 0;

  while (1)
  {
  			TIM3 -> CCR1 = cnt;

		cnt ++;

		if(cnt > 600){
			while(cnt>300)
			{
				cnt--;
				TIM3 -> CCR1 = cnt;
				Delay_1us(20);
			}	
		Delay_1us(20);
}
  }
}

void RCC_Configuration(void)
{
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}



void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10X_CL
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);	

#else

#endif
}

#ifdef  USE_FULL_ASSERT


void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  while (1)
  {}
}

#endif
