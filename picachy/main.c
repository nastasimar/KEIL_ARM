//?????? ????????? 64 ?? 128. ????
//????????? ???? ?????? ????? ?? ???????? ?????????
//includes
#include <MDR32Fx.h>
//init variable&contants
#define resetLCD 10
#define CMD_E0 (int*)0x50100000 //??? ?????? //???????? ?????????? ?? ???????
#define CMD_E1 (int*)0x50200000
#define DATA_E0 (int*)0x58100000 //??? ??????????
#define DATA_E1 (int*)0x58200000
#define LCD_ON 1
#define LCD_OFF 0
#define E0 4
#define E1 5
#define A0 11
uint32_t data = 0x1;
uint8_t array[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x5A, 0x4C, 0x4B, 0x00, 0x8C, 0x3F, 0x00, 0x00, 0x07, 0x41, 0x4B, 0x00, 0x01, 0x00, 0x00,
0x00, 0x70, 0x2F, 0x32, 0x02, 0x0C, 0x01, 0x00, 0x00, 0x70, 0x2F, 0x32, 0x02, 0xA5, 0x0D, 0x00
};
//128 * 8
//init function prototype
void initExternalBusController(void);
void initPortA(void); //??? ?????? ?????? DB0...DB7
void initPortC(void); //??? ???????? WE(W/R(?????? ??? ??????)), CLOCK
void initPortE(void); //??? ?????? ???????? reset, E0, E1 ? ??????? ??? ?????????? A0
void initLCD(void);
void LCDON(int Status);
void SetPage(int Page, int crystal);
void SetAddr(int Addr, int crystal);
void SendData(int data, int crystal);
void clear_LCD();
void StartLine (int StLine);
int ReadCMD(int crystal);
void WriteCMD(int crystal, int CMD);
void WriteData(int crystal, int Data);
//main function
int main(void)
{
MDR_RST_CLK -> PER_CLOCK = 0xFFFFFFFF;
initExternalBusController();
initPortA();
initPortC();
initPortE();
initLCD();
SetPage(0, 0);
SetAddr(0, 0);
clear_LCD();
for (int page = 0; page < 8; page++) {
for (int crystal = 0; crystal < 2; crystal++) {
SetAddr(0, crystal);
SetPage(page, crystal);
for (int i = 0; i < 64; i = i + 1) {
if (crystal == 0)
SendData(array[(page * 128) + i], crystal);
else
SendData(array[(page * 128) + i + 64], crystal);
for (int i = 1; i < 2000; i++);
}
}
}
while(1) {
for (int i = 63; i >= 0; i--) {
StartLine(i);
for (int i = 1; i < 75000; i++);
}
}
}

//Subprograms

void initExternalBusController(void) {
MDR_EBC -> CONTROL = EBC_CONTROL_WAIT_STATE_Msk | EBC_CONTROL_CPOL | EBC_CONTROL_RAM;
}

void initPortA(void) {
MDR_PORTA -> FUNC = 0x5555;
MDR_PORTA -> ANALOG = 0xFF;
MDR_PORTA -> PWR = 0xFFFF;
}

void initPortC(void) {
MDR_PORTC ->
FUNC = (0x1 << PORT_FUNC_MODE2_Pos) | 0x1 << PORT_FUNC_MODE7_Pos;
MDR_PORTC -> OE = (0x1 << 2) | (0x1 << 7);
MDR_PORTC -> ANALOG = (0x1 << 2) | (0x1 << 7);
MDR_PORTC -> PWR = (0x3 << PORT_PWR2_Pos) | (0x3 << PORT_PWR7_Pos);
}

void initPortE(void) {
MDR_PORTE -> FUNC = (0x0 << PORT_FUNC_MODE4_Pos) | (0x0 << PORT_FUNC_MODE5_Pos) | (0x0 << PORT_FUNC_MODE10_Pos) | (0x1 << PORT_FUNC_MODE11_Pos);
MDR_PORTE -> OE = (0x1 << 4) | (0x1 << 5) | (0x1 << resetLCD) | (0x1 << 11);
MDR_PORTE -> ANALOG = (0x1 << 4) | (0x1 << 5) | (0x1 << resetLCD) | (0x1 << 11);
MDR_PORTE -> PWR = (0x3 << PORT_PWR4_Pos) | (0x3 << PORT_PWR5_Pos) | (0x3 << PORT_PWR10_Pos) | (0x3 << PORT_PWR11_Pos);
}

void initLCD(void) {
MDR_PORTE -> RXTX &= ~(1 << resetLCD);
for (int i = 0; i < 50; i++);
MDR_PORTE -> RXTX |= (1 << resetLCD);
for (int i = 0; i < 500; i++);
while((ReadCMD(0))&((1<< 7)|(1<< 4)));
while((ReadCMD(1))&((1<<7)|(1<< 4)));
LCDON(LCD_ON);
}

int ReadCMD(int crystal)
{

if(crystal)
{
MDR_PORTE -> RXTX |= 1 << E1;
MDR_PORTE -> RXTX &= ~(1 << E0);
}
else
{
MDR_PORTE -> RXTX |= 1 << E0;
MDR_PORTE -> RXTX &= ~(1 << E1);
}

return *CMD_E0;
}

void WriteCMD(int crystal, int CMD)
{

if(crystal)
{
MDR_PORTE -> RXTX |= 1 <<E1;
MDR_PORTE -> RXTX &= ~(1<<E0);
}
else
{
MDR_PORTE -> RXTX |= 1<<E0;
MDR_PORTE -> RXTX &= ~(1<<E1);
}

*CMD_E0 = CMD;
}

void WriteData(int crystal, int Data)
{
if(crystal)
{
MDR_PORTE -> RXTX |= 1<<E1;
MDR_PORTE -> RXTX &= ~(1<<E0);
}
else
{
MDR_PORTE -> RXTX |= 1<<E0;
MDR_PORTE -> RXTX &= ~(1<<E1);
}

*DATA_E0 = Data;
}

void StartLine (int StLine) {
int CMD;
CMD = ((StLine & 0x3F) + 0xC0);
WriteCMD(0, CMD);
WriteCMD(1, CMD);
}

void clear_LCD() {
for (int j = 0; j < 2; j++) {
for (int i = 0; i < 8; i++) {
SetPage(i, j);
for (int k = 0; k < 64; k++) {
SendData(0x00, j);
}
}
}
}

void SetPage(int Page, int crystal) {
int CMD;
CMD =((Page&0x7) + 0xB8);

if(crystal)
WriteCMD(1, CMD);
else
WriteCMD(0, CMD);
}

void SetAddr(int Addr, int crystal) {
if(crystal)
WriteCMD(1, 0x40 + (Addr&0x3F));
else
WriteCMD(0, 0x40 + (Addr&0x3F));
}

void SendData(int Data, int crystal) {
MDR_PORTE->RXTX |= (1<<A0);
if(crystal) {
MDR_PORTE->RXTX |= 1<<E1;
MDR_PORTE->RXTX &= ~(1<<E0);
}
else {
MDR_PORTE->RXTX |= 1<<E0;
MDR_PORTE->RXTX &= ~(1<<E1);
}
*DATA_E0 = Data;
}

void LCDON(int ON_or_OFF) {
if (ON_or_OFF) {
WriteCMD(0, 0x3F);
WriteCMD(1, 0x3F);
} else {
WriteCMD(0, 0x3E);
WriteCMD(1, 0x3E);
}
}
//Interrupt routines