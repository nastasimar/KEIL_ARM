//includes
#include <MDR32Fx.h>
//init variable&contants
uint32_t Flag = 0;
//init function prototype

//main function
int main ()
{

MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;
//MDR_PORTC -> OE |= (1 << 0x2);
MDR_PORTD -> OE |= (1 << 10);
MDR_PORTD -> FUNC |= (0x0 << PORT_FUNC_MODE10_Pos);
MDR_PORTD -> ANALOG |= (1 <<10);
MDR_PORTD -> PD &= ~ (1 << 10);
MDR_PORTD -> PWR |= (0x3 << PORT_PWR10_Pos);
	
MDR_PORTC -> FUNC |= (0x2 << PORT_FUNC_MODE12_Pos);
MDR_PORTC -> ANALOG |= (1 << 12);
MDR_PORTC -> PD &= ~ (1 << 12);
MDR_PORTC -> GFEN |= (1 << 12);	
//MDR_PORTC -> PWR |= (0x3 << PORT_PWR12_Pos);
NVIC -> ISER[0] |= ( 1 << EXT_INT2_IRQn );
__enable_irq();
	while (1)
	{
		if (Flag == 1)
		{
		
	MDR_PORTD -> RXTX &=~ (1 << 10);
			for (int j=0; j <1000000; j++);
		
		
			MDR_PORTD -> RXTX |= (1 << 10);
			for (int j=0; j <1000000; j++);	
		
		
		
		}

}
}

void EXT_INT2_IRQHandler (void)

//	while (1)
{
	if (Flag == 0)
 Flag = 1;
  else 
 Flag = 0;
		for (int j=0; j <1000000; j++);
	NVIC -> ICPR[0] = 0xFFFFFFFF;
		
}
