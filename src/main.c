
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED ;
EXTI_InitTypeDef Ext_i;
NVIC_InitTypeDef Nvic;

void config(){

	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE);//led
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);//buton

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE); //interupt

    //led
    LED.GPIO_Mode=GPIO_Mode_OUT;
    LED.GPIO_OType= GPIO_OType_PP;
    LED.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    LED.GPIO_PuPd=GPIO_PuPd_NOPULL ;
    LED.GPIO_Speed=0x03;

   GPIO_Init(GPIOD, &LED);

   //buton
     LED.GPIO_Mode=GPIO_Mode_IN;
     LED.GPIO_OType= GPIO_OType_PP;
     LED.GPIO_Pin=GPIO_Pin_0;
     LED.GPIO_PuPd=GPIO_PuPd_DOWN ;
     LED.GPIO_Speed=0x03;

    GPIO_Init(GPIOA, &LED);

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//interupt yapacaðýmýz portu ve pinini tanýmladýk

    Ext_i.EXTI_Line=EXTI_Line0;
    Ext_i.EXTI_LineCmd=ENABLE;
    Ext_i.EXTI_Mode=EXTI_Mode_Interrupt;
    Ext_i.EXTI_Trigger= EXTI_Trigger_Rising;

    EXTI_Init(&Ext_i);

    Nvic.NVIC_IRQChannel=EXTI0_IRQn;
    Nvic.NVIC_IRQChannelCmd=ENABLE;
    Nvic.NVIC_IRQChannelPreemptionPriority=0xFF;
    Nvic.NVIC_IRQChannelSubPriority=0x00;

    NVIC_Init(&Nvic);
}

void delay(uint32_t time){
	while(time--){}
}

void ExtI0_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line0) != RESET ){


		GPIO_SetBits(GPIOD, GPIO_Pin_All);
		delay(168000000);

		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
int main(void)
{
	config();
	GPIO_ResetBits(GPIOD, GPIO_Pin_All);

  while (1)
  {
	  GPIO_ResetBits(GPIOD, GPIO_Pin_All);
  }
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
