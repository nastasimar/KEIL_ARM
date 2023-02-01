#include <MDR32Fx.h>


int main(void){
	MDR_RST_CLK->PER_CLOCK=0xFFFFFFFF;

	MDR_PORTD->OE |= 1<<10; // d10
	MDR_PORTD->FUNC |= (0x0<<(10*2));
	MDR_PORTD->ANALOG |= (1<<10);
	MDR_PORTD->PD &= ~(1<<10);
	MDR_PORTD->PWR |= 0x3<<PORT_PWR10_Pos;
	
	MDR_PORTD->OE |= 1<<11; // d11
	MDR_PORTD->FUNC |= (0x0<<(11*2));
	MDR_PORTD->ANALOG |= (1<<11);
	MDR_PORTD->PD &= ~(1<<11);
	MDR_PORTD->PWR |= 0x3<<PORT_PWR11_Pos;
	
	MDR_PORTD->OE |= 1<<12; // d12
	MDR_PORTD->FUNC |= (0x0<<(12*2));
	MDR_PORTD->ANALOG |= (1<<12);
	MDR_PORTD->PD &= ~(1<<12);
	MDR_PORTD->PWR |= 0x3<<PORT_PWR12_Pos;
	
	MDR_PORTD->OE |= 1<<13; // d13
	MDR_PORTD->FUNC |= (0x0<<(13*2));
	MDR_PORTD->ANALOG |= (1<<13);
	MDR_PORTD->PD &= ~(1<<13);
	MDR_PORTD->PWR |= 0x3<<PORT_PWR13_Pos;
	
	MDR_PORTD->OE |= 1<<14; // d14
	MDR_PORTD->FUNC |= (0x0<<(14*2));
	MDR_PORTD->ANALOG |= (1<<14);
	MDR_PORTD->PD &= ~(1<<14);
	MDR_PORTD->PWR |= 0x3<<PORT_PWR14_Pos;
	
	MDR_PORTC->OE &= ~(1<<10); // c10
	MDR_PORTC->FUNC |= (0x0<<(10*2));
	MDR_PORTC->ANALOG |= (1<<10);
	MDR_PORTC->PD &= ~(1<<10);
	MDR_PORTC->PWR |= 0x3<<PORT_PWR10_Pos;
	
	MDR_PORTC->OE &= ~(1<<11); // c11
	MDR_PORTC->FUNC |= (0x0<<(11*2));
	MDR_PORTC->ANALOG |= (1<<11);
	MDR_PORTC->PD &= ~(1<<11);
	MDR_PORTC->PWR |= 0x3<<PORT_PWR11_Pos;
	
	MDR_PORTC->OE &= ~(1<<12); // c12
	MDR_PORTC->FUNC |= (0x0<<(12*2));
	MDR_PORTC->ANALOG |= (1<<12);
	MDR_PORTC->PD &= ~(1<<12);
	MDR_PORTC->PWR |= 0x3<<PORT_PWR12_Pos;
	
int i=1;
int ink=1;	
	while(1){		
		if (!(MDR_PORTC->RXTX & (1<<12))) ink=-1;//c12
		if (!(MDR_PORTC->RXTX & (1<<10))) ink= 0;//c10
		if (!(MDR_PORTC->RXTX & (1<<11))) ink= 1;//c11

		switch(i){			
			case 1:
				{
					MDR_PORTD->RXTX |= (1<<10);
				  MDR_PORTD->RXTX &= ~((1<<11)|(1<<12)|(1<<13)|(1<<14));
				  i+=ink;
				  for(long k=0;k<100000;k++);
				  break;
				}
			case 2:
				{
					MDR_PORTD->RXTX |= (1<<11);
				  MDR_PORTD->RXTX &= ~((1<<10)|(1<<12)|(1<<13)|(1<<14));
				  i+=ink;
				  for(long k=0;k<100000;k++);
				  break;
				}
			case 3:
				{
					MDR_PORTD->RXTX |= (1<<12);
				  MDR_PORTD->RXTX &= ~((1<<10)|(1<<11)|(1<<13)|(1<<14));
				  i+=ink;
				  for(long k=0;k<100000;k++);
				  break;
				}
			case 4:
				{
					MDR_PORTD->RXTX |= (1<<13);
				  MDR_PORTD->RXTX &= ~((1<<11)|(1<<12)|(1<<10)|(1<<14));
				  i+=ink;
				  for(long k=0;k<100000;k++);
				  break;
				}
			case 5:
				{
					MDR_PORTD->RXTX |= (1<<14);
				  MDR_PORTD->RXTX &= ~((1<<11)|(1<<12)|(1<<13)|(1<<10));
				  i+=ink;
				  for(long k=0;k<100000;k++);
				  break;
				}
			case 0:
    {
			if (ink==-1) 
			  i=5;
		  if (ink==1) 
			  i=1;
		  break;
		}
			case 6:
   {
	 if (ink==-1) 
	   i=5;
	 if (ink==1)
	   i=1;
	 break;
	 }
		}					
	}
}
