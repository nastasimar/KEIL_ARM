//includes
#include <MDR32Fx.h>
//init variable&contants

//init function prototype


//main function


int main (void)
{
MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;
MDR_RST_CLK->TIM_CLOCK = RST_CLK_TIM_CLOCK_TIM1_CLK_EN;	
//MDR_TIMER1 -> CNTRL |= (1 << TIMER_CNTRL_ARRB_EN_Pos)| TIMER_CNTRL_CNT_EN;	
MDR_TIMER1 -> CH2_CNTRL1|= (0x2 << TIMER_CH_CNTRL1_SELO_Pos);
MDR_TIMER1 -> CH2_CNTRL1|= (0x01 << TIMER_CH_CNTRL1_SELOE_Pos);	
MDR_TIMER1 -> CNTRL |= (0001 << 8)| (1 << 1 )| (1<<0);
//MDR_TIMER1 -> CH2_CNTRL |= (0x6 << TIMER_CH_CNTRL_OCCM_Pos);
//MDR_TIMER1 -> CH1_CNTRL &= ~ (1 << CCR_EN)	
MDR_PORTD -> OE |= (1 << 0x2);
MDR_PORTD -> FUNC |= (0x01 << PORT_FUNC_MODE10_Pos);
MDR_PORTD -> ANALOG |= (1 <<10);
MDR_PORTD -> PD &= ~ (1 << 10);
MDR_PORTD -> PWR |= (0x3 << PORT_PWR10_Pos);
MDR_TIMER1 -> ARR = 8000;
//MDR_TIMER1 -> CCR2 = 4000;
	
	
	while (1)
	{
//	MDR_PORTD -> RXTX &=~ (1 << 10);
		for (int i=0; i <8000; i++)
		{
			MDR_TIMER1 -> CCR2 = i;
			for (int j=0; j <1000; j++);
		
		}
		for (int i=8000; i > 0; i--)
		{
			MDR_TIMER1 -> CCR2 = i;
			for (int j=0; j <1000; j++);
		
		}
//	MDR_PORTD -> RXTX |= (1 << 10);
	
	}

}


//Subprograms


//Interrupt routines

