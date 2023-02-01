//includes
#include <MDR32Fx.h>

uint8_t counter = 0;
uint8_t level = 0;
void light_upd(uint8_t cnt);
void setting (uint8_t level);

//main function
int main(void)
{

	//init perefirial 
	MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;	

	
	//pd10-pd14
	MDR_PORTD->OE |= (0x1F << 10);
	MDR_PORTD->ANALOG |= (0x1F<<10);
	MDR_PORTD->PD &= ~(0x1F<<10);
	MDR_PORTD->PWR |= (0x3<<PORT_PWR10_Pos | 0x3<<PORT_PWR11_Pos | 0x3<<PORT_PWR12_Pos | 0x3<<PORT_PWR13_Pos | 0x3<<PORT_PWR14_Pos);
	

	//pc10
	MDR_PORTC->OE &= ~(1 << 10);
	MDR_PORTC->FUNC |= (0x0 << PORT_FUNC_MODE10_Pos);
	MDR_PORTC->ANALOG |= 1 << 10;
	MDR_PORTC->PD &= ~(1 << 10);
	MDR_PORTC->PWR |= (0x3 << PORT_PWR10_Pos);
	
	//pc11
	MDR_PORTC->OE &= ~(1 << 11);
	MDR_PORTC->FUNC |= (0x0 << PORT_FUNC_MODE11_Pos);
	MDR_PORTC->ANALOG |= 1 << 11;
	MDR_PORTC->PD &= ~(1 << 11);
	MDR_PORTC->PWR |= (0x3 << PORT_PWR11_Pos);
	
	//pc12
	MDR_PORTC->OE &= ~(1 << 12);
	MDR_PORTC->FUNC |= (0x0 << PORT_FUNC_MODE12_Pos);
	MDR_PORTC->ANALOG |= 1 << 12;
	MDR_PORTC->PD &= ~(1 << 12);
	MDR_PORTC->PWR |= (0x3 << PORT_PWR12_Pos);
	
	//pc13
	MDR_PORTC->OE &= ~(1 << 13);
	MDR_PORTC->FUNC |= (0x0 << PORT_FUNC_MODE13_Pos);
	MDR_PORTC->ANALOG |= 1 << 13;
	MDR_PORTC->PD &= ~(1 << 13);
	MDR_PORTC->PWR |= (0x3 << PORT_PWR13_Pos);
	
	MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;
MDR_RST_CLK->TIM_CLOCK = RST_CLK_TIM_CLOCK_TIM1_CLK_EN;	
MDR_TIMER1 -> CNTRL |= (1 << TIMER_CNTRL_ARRB_EN_Pos)| TIMER_CNTRL_CNT_EN;	
MDR_TIMER1 -> CH2_CNTRL1|= (0x2 << TIMER_CH_CNTRL1_SELO_Pos);
MDR_TIMER1 -> CH2_CNTRL1|= (0x01 << TIMER_CH_CNTRL1_SELOE_Pos);	
MDR_TIMER1 -> CH2_CNTRL |= (0x6 << TIMER_CH_CNTRL_OCCM_Pos);
	
	
while(1)
	{
		
		if(!((MDR_PORTC->RXTX)&(1<<12))) 
		{//up button
			level  = 0; 
			setting (level);
		}
		if(!(MDR_PORTC->RXTX&(1<<11)))
		{
			level  = 1;
			setting (level);
		}
		
		if(!(MDR_PORTC->RXTX&(1<<12)))
		{
		level  = 2;
			setting (level);
		}
			if(!(MDR_PORTC->RXTX&(1<<13)))
			{
				level  = 3;		
				setting (level);
	   }
	
}
}


void setting (uint8_t level)
{
if (level == 0) 	
				{
				if(counter == 4){
								counter = 4;
							}
							else{
								counter++;
							}
							light_upd(counter);
							while(!(MDR_PORTC->RXTX&(1<<12)));
				}
if (level == 1) 	
{
					if(counter == 0){
									counter = 0;
								}
								else{
									counter--;
								}
								light_upd(counter);
								while(!(MDR_PORTC->RXTX&(1<<11)));

}
if (level == 2)
{
   while (((MDR_PORTC->RXTX&(1<<11) (MDR_PORTC->RXTX&(1<<10))& (MDR_PORTC->RXTX&(1<<13)));
	 {
	 if(counter == 4){
				counter = 0;
			}
			else{
				for (int i = 0 ; i <1000; i++ );				
				light_upd(counter);
				counter++; 
	 }
 }
if (level == 3)
{
while (!((!(MDR_PORTC->RXTX&(1<<11)))| (!(MDR_PORTC->RXTX&(1<<10)))| (!(MDR_PORTC->RXTX&(1<<12)))))
{
if(counter == 0)
				{
				counter = 4;
			  }
			else{
				for (int i = 0 ; i <1000; i++);
				light_upd(counter);
				counter--;
			}
}	

}

}
}



void light_upd(uint8_t cnt)
{
	MDR_PORTD->RXTX &= ~(1<<10);
	MDR_PORTD->RXTX &= ~(1<<11);
	MDR_PORTD->RXTX &= ~(1<<12);
	MDR_PORTD->RXTX &= ~(1<<13);
	MDR_PORTD->RXTX &= ~(1<<14);
	if(cnt == 0) { MDR_PORTD->RXTX |= (0x1<<10); }
	else if(cnt == 1) { MDR_PORTD->RXTX |= (1<<11); }
	else if(cnt == 2) { MDR_PORTD->RXTX |= (1<<12); }
	else if(cnt == 3) { MDR_PORTD->RXTX |= (1<<13); }
	else if(cnt == 4) { MDR_PORTD->RXTX |= (1<<14); }

}
