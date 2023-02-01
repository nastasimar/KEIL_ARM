#include <MDR32Fx.h>

void InitUART2(int freq, int BAUD) 	
{
	int I;
	double Frac;
	MDR_RST_CLK->UART_CLOCK |= RST_CLK_UART_CLOCK_UART2_CLK_EN; 
	//115200 ??????? 80 MHz
	MDR_PORTF -> OE |= (1 << 1); 
	MDR_PORTF -> FUNC |= (3 << PORT_FUNC_MODE0_Pos)|(3 << PORT_FUNC_MODE1_Pos);
	MDR_PORTF -> ANALOG |= 3;
	//MDR_PORTF -> PD &= ~ (1 << 10);
	MDR_PORTF -> PWR |= (0x3 << PORT_PWR1_Pos);
	
	I = freq/(16*BAUD);
	MDR_UART2->IBRD = I;
	Frac = (((double)freq)/((double)16*BAUD) - (double)I)*64 + 0.5;
	MDR_UART2->FBRD = (int)Frac;
	MDR_UART2->LCR_H |= (3 << UART_LCR_H_WLEN_Pos)|(1 << UART_LCR_H_FEN_Pos);
	MDR_UART2->IFLS |= (1 << UART_IFLS_TXIFLSEL_Pos);
	MDR_UART2->IFLS &= ~(UART_IFLS_RXIFLSEL_Msk);
  MDR_UART2->IMSC |= (1 << UART_IMSC_TXIM_Pos)|(1 << UART_IMSC_RXIM_Pos);	
	MDR_UART2->CR |= (1 << UART_CR_TXE_Pos)|(1 << UART_CR_RXE_Pos)|(1 << UART_CR_UARTEN_Pos);
	
}