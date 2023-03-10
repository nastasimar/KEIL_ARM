//includes
#include <MDR32Fx.h>
//init variable&contants
uint32_t flag = 0;
int x=0;
int y=0;
int data=0;
int inc=1;
//define
#define RESET_LCD 10
#define CMD_E0 (int*)0x50100000
#define CMD_E1 (int*)0x50200000
#define Data_E0 (int*)0x58100000
#define Data_E1 (int*)0x58200000
#define LCD_ON 1
#define LCD_OFF 0
#define E0 4
#define E1 5
#define A0 11

//init function prototype
void LCDON(int Status);
void InitLcd(void);
void SetPage(int Page, int crystal);
void SetAddr(int Addr, int crystal);
void Send_Data(int Data, int crystal);
void clear_lcd(void);
int ReadCMD(int crystal);
//main function
int main(void)
{
	//init rst_clk
	
	//init perefirial 
	MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;	
	//init external bus contoller
	MDR_EBC->CONTROL |= (EBC_CONTROL_WAIT_STATE_Msk)|(EBC_CONTROL_CPOL)|(EBC_CONTROL_RAM);
	//portA - DATA
	MDR_PORTA->FUNC |= (1<<PORT_FUNC_MODE0_Pos)|(1<<PORT_FUNC_MODE1_Pos)|(1<<PORT_FUNC_MODE2_Pos)|(1<<PORT_FUNC_MODE3_Pos)|(1<<PORT_FUNC_MODE3_Pos)|(1<<PORT_FUNC_MODE4_Pos)|(1<<PORT_FUNC_MODE5_Pos)|(1<<PORT_FUNC_MODE6_Pos)|(1<<PORT_FUNC_MODE7_Pos);
	MDR_PORTA->ANALOG |= 0XFF;
	MDR_PORTA->PWR |= (0x3<<PORT_PWR0_Pos)|(0x3<<PORT_PWR1_Pos)|(0x3<<PORT_PWR2_Pos)|(0x3<<PORT_PWR3_Pos)|(0x3<<PORT_PWR4_Pos)|(0x3<<PORT_PWR5_Pos)|(0x3<<PORT_PWR6_Pos)|(0x3<<PORT_PWR7_Pos);
	//pc2-WE,PC7 - E,
	MDR_PORTC->FUNC |= (1<<PORT_FUNC_MODE2_Pos)|(1<<PORT_FUNC_MODE7_Pos);
	MDR_PORTC->ANALOG |= (1<<2)|(1<<7);
	MDR_PORTC->PWR |= (0x3<<PORT_PWR2_Pos)|(0x3<<PORT_PWR7_Pos);
	MDR_PORTC->OE |=(1<<2)|(1<<7);
	//PE4-E0,PE5,PE11, PE10 - RESET
	MDR_PORTE->FUNC |= (0<<PORT_FUNC_MODE4_Pos)|(0<<PORT_FUNC_MODE5_Pos)|(1<<PORT_FUNC_MODE11_Pos)|(0<<PORT_FUNC_MODE10_Pos);
	MDR_PORTE->ANALOG |= (1<<4)|(1<<5)|(1<<11)|(1<<10);
	MDR_PORTE->PWR |= (0x3<<PORT_PWR4_Pos)|(0x3<<PORT_PWR5_Pos)|(0x3<<PORT_PWR11_Pos)|(0x3<<PORT_PWR10_Pos);
	MDR_PORTE->OE |=(1<<4)|(1<<5)|(1<<11)|(1<<10);
	//MDR_PORTD->OE &= ~(1<<10);
	MDR_PORTD->OE |=(1<<10);
	MDR_PORTD->FUNC |= (1<<PORT_FUNC_MODE10_Pos);
	MDR_PORTD->ANALOG |= (1<<10);
	MDR_PORTD->PD &= ~(1<<10);
	MDR_PORTD->PWR |= (0x3<<PORT_PWR10_Pos);

	MDR_PORTC->FUNC |= (0x2<<PORT_FUNC_MODE12_Pos);
	MDR_PORTC->ANALOG |= (1<<12);
	MDR_PORTC->PD &= ~(1<<12);
	MDR_PORTC->GFEN |= (1<<12);
	
//	NVIC->ISER[0] |= 1<<EXT_INT2_IRQn;
	
//	__enable_irq();

		
		InitLcd();
		SetPage(0, 0);
		SetAddr(0, 0);
		clear_lcd();
	
		for (int crystal=0;crystal<2;crystal++)
		{
			for (int page=0;page<8;page++)
			{
				SetPage(page,crystal);
				SetAddr(0, crystal);
				for (int pos=0;pos<64; pos++)
				{
					for (int bit=0;bit<8;bit++)
					{
						x=pos+crystal*64;
						y=8*page+bit;
						if (y <(x/2)) data+=inc;
						if (inc == 128) inc=1;
						else inc*=2;
					}
					Send_Data(data,crystal);
					data=0;
				}
			}
		}
while(1)
	{ 	
	
	}


}


//Subprograms
void InitLcd(void)
{
	int Status = 0;
	MDR_PORTE-> RXTX &= ~(1<<RESET_LCD);
	 for(int i=0;i<50;i++);
	MDR_PORTE-> RXTX |= (1<<RESET_LCD);
		for(int i=0;i<500;i++);
	Status = *((int*)0x50200000);
	
//	while((*CMD_E0)&((1<<7)|(1<<4)));
//	while((*CMD_E1)&((1<<7)|(1<<4)));
	while((ReadCMD(0))&((1<<7)|(1<<4)));
	while((ReadCMD(1))&((1<<7)|(1<<4)));
	LCDON(LCD_ON);
	
	
}

int ReadCMD(int crystal)
{

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

	return *CMD_E0;
}

void WriteCMD(int crystal, int CMD)
{

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

  *CMD_E0 = CMD;
}

void WriteData(int crystal, int Data)
{
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

void clear_lcd(void)
{	for (int j=0; j<2;j++){
		for(int i =0; i<8;i++){
			SetPage(i,j);
			for(int k=0;k<64;k++){
				Send_Data(0x00,j);
			}
		}
	}
}

void LCDON(int Status)
{
	if(Status)
	{	
		WriteCMD(0, 0x3F);
		WriteCMD(1, 0x3F);
//		*CMD_E0 = 0x3F;
//		*CMD_E1 = 0x3F;
	}else{
		WriteCMD(0, 0x3E);
		WriteCMD(1, 0x3E);
	
//		*CMD_E0 = 0x3E;
//		*CMD_E1 = 0x3E;
	}
		
}

void SetPage(int Page, int crystal)
{
	int CMD;
	CMD =((Page&0x7) + 0xB8);
	
	if(crystal)
			WriteCMD(1, CMD);
	//*CMD_E1 = 0xB8 + Page&0x7;
	else
			WriteCMD(0, CMD);
		//*CMD_E0 = 0xB8 + Page&0x7;
}

void SetAddr(int Addr, int crystal)
{
	if(crystal)
		WriteCMD(1, 0x40 + (Addr&0x3F));
	//	*CMD_E1 = 0x40 + Addr&0x3f;
	else
		WriteCMD(0, 0x40 + (Addr&0x3F));
	//	*CMD_E0 = 0x40 + Addr&0x3f;
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

//Interrupt routines
void EXT_INT2_IRQHandler(void)
{
		if (flag == 0)
			flag = 1;
		else
			flag = 0;	
		for(int i = 0; i<10000000; i++);
		NVIC->ICPR[0] = 0x0;

}

