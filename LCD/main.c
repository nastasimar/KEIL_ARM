//includes
#include <MDR32Fx.h>
//init variable&contants
uint32_t flag = 0;
int Status = 0;
int data;
#define Reset_pin 10
#define CMD_E0 (int*)0x50200000
#define CMD_E1 (int*)0x50100000
#define LCDON 1
#define LCDOFF 0
#define Data_E0 (int*)0x58100000
#define Data_E1 (int*)0x58000000
#define E0 4
#define E1 5
#define A0 11
void Set_ADDR (int Address, int crystal);
void Clear_LCD(void);
//init function prototype
void EXT_INT2_IRQHandler(void);
void Init_LCD (void);
void LCD_ON (int Status);
void Send_Data(int Data, int crystal);
void SetPage (int Page, int crystal);
void  WRITECMD (int crystal, int CMD);
//main function
int main(void)
{

	MDR_RST_CLK -> PER_CLOCK = 0xFFFFFFFF;
	
	MDR_PORTD -> OE |= (1 << 10);
	MDR_PORTD -> FUNC |= (0x0 << PORT_FUNC_MODE10_Pos);
	MDR_PORTD -> ANALOG |= (1 << 10);
	MDR_PORTD -> PD &= ~(1 << 10);
	MDR_PORTD -> PWR |= (0x3 << PORT_PWR10_Pos);

	MDR_PORTC -> FUNC |= (0x2 << PORT_FUNC_MODE12_Pos);
	MDR_PORTC -> ANALOG |= (0x1 << 12);
	//MDR_PORTC -> PULL |= (0x1 << 28); -
	MDR_PORTC -> PD &= ~(1 << 12);
	MDR_PORTC -> PWR |= (0x3 << PORT_PWR12_Pos);
	MDR_PORTC -> GFEN |= (0x1 << 12);
	//init EBC
	MDR_EBC ->CONTROL |= EBC_CONTROL_WAIT_STATE_Msk | (1 << EBC_CONTROL_CPOL) | (1 << EBC_CONTROL_RAM);
	//PORTA - DATA
	MDR_PORTA -> FUNC |= (0x1 << PORT_FUNC_MODE0_Pos)|(0x1 << PORT_FUNC_MODE1_Pos) | (0x1 << PORT_FUNC_MODE2_Pos)| (0x1 << PORT_FUNC_MODE3_Pos)|(0x1 << PORT_FUNC_MODE4_Pos)|(0x1 << PORT_FUNC_MODE5_Pos)|(0x1 << PORT_FUNC_MODE6_Pos)|(0x1 << PORT_FUNC_MODE7_Pos);
	MDR_PORTA -> ANALOG |= 0XFF;
	MDR_PORTA -> PWR |= (0x3 << PORT_PWR0_Pos)| (0x3 << PORT_PWR1_Pos)| (0x3 << PORT_PWR2_Pos)|(0x3 << PORT_PWR3_Pos)| (0x3 << PORT_PWR4_Pos)|(0x3 << PORT_PWR5_Pos)| (0x3 << PORT_PWR6_Pos)|(0x3 << PORT_PWR7_Pos);
	//RC2- WE, PC7 - E, RESET - PE10
	MDR_PORTC -> FUNC |= (0x1 << PORT_FUNC_MODE2_Pos)| (0x1 << PORT_FUNC_MODE7_Pos);
	MDR_PORTC -> ANALOG |=(0x1 << 2)| (0x1 << 7);
	MDR_PORTC -> PWR |= (0x3 << PORT_PWR2_Pos)| (0x3 << PORT_PWR7_Pos);
  MDR_PORTC -> OE |= (0x1 << 2)| (0x1 << 7);
	NVIC -> ISER [0] = (0x1 << 29);
	//PORTE E4-E0, E5-E1, E11-A0
	MDR_PORTE -> FUNC |= (0x1 << PORT_FUNC_MODE4_Pos)| (0x1 << PORT_FUNC_MODE5_Pos)| (0x1 << PORT_FUNC_MODE11_Pos);
	MDR_PORTE -> ANALOG |=(0x1 << 4)| (0x1 << 5)| (0x1 << 11)| (0x1 << 10);
	MDR_PORTE -> PWR |= (0x3 << PORT_PWR4_Pos)| (0x3 << PORT_PWR5_Pos)| (0x3 << PORT_PWR11_Pos)| (0x3 << PORT_PWR10_Pos);
  MDR_PORTE -> OE |= (0x0 << 4)| (0x0 << 5)| (0x1 << 11)| (0x1 << 10);
	
	//__enable_irq();


/*		if (flag == 0) {
		MDR_PORTD->RXTX &= ~(1 << 10);
		for(int i = 0; i < 1000000; i++);
		MDR_PORTD->RXTX |= (1 << 10);
		for(int i = 0; i < 1000000; i++);
		} */
		Init_LCD ();
		SetPage (0,0);
		Set_ADDR (0,0);
		Clear_LCD();
		
		for (int page=0;  page<8; page++)
	{
	 for (int crystal=0; crystal<2; crystal++)
		{
		Set_ADDR (0, crystal);	
		SetPage(page,crystal);
		for (int i =0; i<64; i= i+2)
			{	
				if ( i< 16 * (page-1 * crystal))
			{
			Send_Data (0x00, crystal);
			Send_Data (0x00, crystal);	
			}	
			 else if (i < -2+16 * (page - 4* crystal)+1)
			 {
			 Send_Data (data |= 0x1 << ((1- 16 * (page-4* crystal ) )/2), crystal);
			 	Send_Data (data, crystal);
			 }
			else 
			{
			data = 0x1;
			Send_Data (0xFF, crystal);
      Send_Data (0xFF, crystal);				
			
			}
			for (int i = 1; i < 20000; i++);
		}
		}
	
	
	}
	
}
	

//Subprograms

void Init_LCD (void)
{

MDR_PORTE -> RXTX &= ~(1 << Reset_pin);
for(int i=0; i < 50; i++);
MDR_PORTE -> RXTX |= (1 << Reset_pin);
for(int i=0; i < 500; i++);
Status = *(int*)(0x50200000);
while (*(int*)(0x50200000)&((1 <<4)| (1<<7)));	
while (*(int*)(0x50100000)&((1 <<4)| (1<<7)));	
LCD_ON(LCDON);	
}

void Clear_LCD(void)
{

for (int i=0; i<2; i++)
	{
	 for (int j=0; j<8; j++)
		{
		SetPage(j,i);
		for (int k =0; k<64; k++)
			{
			*Data_E0 = 0x00;
			*Data_E1 = 0x00;	
			}	
		}
	
	
	}
	
}
	
void LCD_ON (int Status)
{
if (Status)
{
	WRITECMD (0, 0x3F);
	WRITECMD (1, 0x3F);
//	*(CMD_E0) = 0x3F;
 // *(CMD_E1) = 0x3F;
}
else 
	{
//	*CMD_E0 = 0x3E;
//	*CMD_E1 = 0x3E;
	WRITECMD (0, 0x3E);
	WRITECMD (1, 0x3E);	
	}
}


void  WRITECMD (int crystal, int CMD)
{
	MDR_PORTE -> RXTX &= ~(1 <<  A0);
	if (crystal)
//		MDR_PORTE -> RXTX &= ~(1 <<  A0);
	{
	MDR_PORTE -> RXTX |= (1 <<  E1);
	MDR_PORTE -> RXTX &= ~(1 <<  E0);	
	}
else 
{
MDR_PORTE -> RXTX |= (1 <<  E0);
MDR_PORTE -> RXTX &= ~(1 <<  E1);	
}
}



void SetPage (int Page, int crystal)
{
	if (crystal) 
	{
		*CMD_E1 = 0x8 + Page & 0x7 ; 
	}
else 
{
	*CMD_E0 = 0x8 + Page & 0x7 ; 
}
}

void Set_ADDR (int Address, int crystal)
{
if (crystal) 
	{
		*CMD_E1 = 32 + Address & 63 ; 
	}
	else 
	{
		*CMD_E0 = 32 + Address & 63 ; 
	}

}


//Interrupt routines
void EXT_INT2_IRQHandler(void) 
{	
	if (flag == 0) {
		flag = 1;
	}
	else {
		flag = 0;
	}
	for (int i = 0; i < 100000; i++);
	NVIC -> ICPR [0] = 0x0;
}

void Send_Data(int Data, int crystal)
{
//	if(crystal)
//		*Data_E1 = Data;
//	else 
//		*Data_E0 = Data;
		MDR_PORTE->RXTX |= (1<<A0);

	if(crystal)
	{
		MDR_PORTE->RXTX |= 1<<E1;
		MDR_PORTE->RXTX &= ~(1<<E0);
	}
	else
	{
		MDR_PORTE->RXTX |= 1<<E0;
		MDR_PORTE->RXTX &= ~(1<<E1);
	}

  *Data_E0 = Data;
}





