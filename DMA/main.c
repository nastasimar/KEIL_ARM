//includes
#include <MDR32Fx.h>
#include "uart.h"
//init variable&contants
uint32_t flag = 0;
uint32_t N = 16;
int PRI_TBL[256] __attribute__ ((aligned (0x400)));
uint8_t buf[16] = "Hello WORLD!!!!\n";

//init function prototype


//main function
int main(void)
{
	//init rst_clk
	
/*	MDR_RST_CLK->HS_CONTROL = RST_CLK_HS_CONTROL_HSE_ON;// turn on hse
	while (!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY));// wait for hse stability
	MDR_RST_CLK->CPU_CLOCK |= 2<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos;//select hse c1
	MDR_RST_CLK->PLL_CONTROL = (9<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos);//select multiplier 10
	MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_ON;//turn on pll
	MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_PLD;//
	MDR_RST_CLK->PLL_CONTROL &= ~(RST_CLK_PLL_CONTROL_PLL_CPU_PLD);//reloading pll
	while (!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY));//wait for pll stability
	MDR_RST_CLK->CPU_CLOCK |= 1<<RST_CLK_CPU_CLOCK_HCLK_SEL_Pos;//select cpu_c3 hclk	
	MDR_RST_CLK->CPU_CLOCK |= 1<<RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos;//select pll c2
*/	

	//init perefirial 
	MDR_RST_CLK->PER_CLOCK = 0xFFFFFFFF;	
	
	//MDR_PORTD->OE &= ~(1<<10);
//	MDR_PORTD->OE |=(1<<10);
//	MDR_PORTD->FUNC |= (1<<PORT_FUNC_MODE10_Pos);
//	MDR_PORTD->ANALOG |= (1<<10);
//	MDR_PORTD->PD &= ~(1<<10);
//	MDR_PORTD->PWR |= (0x3<<PORT_PWR10_Pos);

//	MDR_PORTC->FUNC |= (0x2<<PORT_FUNC_MODE12_Pos);
//	MDR_PORTC->ANALOG |= (1<<12);
//	MDR_PORTC->PD &= ~(1<<12);
//	MDR_PORTC->GFEN |= (1<<12);
//	
//	MDR_PORTF -> OE |= (1 << 1); 
//	MDR_PORTF -> FUNC |= (3 << PORT_FUNC_MODE0_Pos)|(3 << PORT_FUNC_MODE1_Pos);
//	MDR_PORTF -> ANALOG |= 3;
//	//MDR_PORTF -> PD &= ~ (1 << 10);
//	MDR_PORTF -> PWR |= (0x3 << PORT_PWR1_Pos);


	//init perefirial 
		
	InitUART2(8000000, 115200);
	
	#define DMA_CH_UART2_TX 2

	#define dst_inc 30
	#define dst_size 28
	#define src_inc 26
	#define src_size 24
	#define dst_prot 21
	#define src_prot 18
	#define R_power 14
	#define n_minus_1 4
	#define nextuburst 3
	#define cycle_ctrl 0
	
	
	
	
	//src end pointer
	PRI_TBL[4*DMA_CH_UART2_TX] = (int)(&buf[0] + N - 1);
	//dst end pointer
	PRI_TBL[4*DMA_CH_UART2_TX + 1] = (int) 0x40038000;
	//control
	PRI_TBL[4*DMA_CH_UART2_TX + 2] = (0x3<<dst_inc)|(0<<dst_size)|(0x0<<src_inc)|(0<<src_size)|(0<<dst_prot)|(0<<src_prot)|(0xF<<R_power)|((N-1)<<n_minus_1)|(0<<nextuburst)|(0x1<<cycle_ctrl);	

	MDR_DMA->CTRL_BASE_PTR = (int)PRI_TBL;
	MDR_DMA->ALT_CTRL_BASE_PTR  = (int)PRI_TBL + 0x200;
	MDR_DMA->CFG = DMA_CFG_MASTER_ENABLE;
	MDR_DMA->CHNL_REQ_MASK_CLR = 1<<DMA_CH_UART2_TX;
	MDR_DMA->CHNL_ENABLE_SET = 1<<DMA_CH_UART2_TX;
	MDR_DMA->CHNL_PRI_ALT_CLR = 1<<DMA_CH_UART2_TX;
	
	MDR_DMA->CHNL_SW_REQUEST = 1<<DMA_CH_UART2_TX;
	
	NVIC->ISER[0] |= 1<<EXT_INT2_IRQn;
	
	__enable_irq();

 	while(1)
	{
	//main loop
 		if(flag == 1)
		{	
			MDR_PORTD->RXTX &= ~(1<<10);
			for(int i = 0; i<1000000; i++);
			MDR_PORTD->RXTX |= (1<<10);
			for(int i = 0; i<1000000; i++);
		}
	}


}


//Subprograms


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

