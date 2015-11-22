#include "main.h"
//#include "head.h"
int main() {

	unsigned int i, j = 0;

	volatile unsigned int *pLcdDestReg =
			(volatile unsigned int*) (LCD_DEST_REG_ADDR);
	volatile unsigned int *pLcdWidthReg =
			(volatile unsigned int*) (LCD_WIDTH_REG_ADDR);
	volatile unsigned int *pLcdHeightReg =
			(volatile unsigned int*) (LCD_HEIGHT_REG_ADDR);
	volatile unsigned int *pLcdCmdReg =
			(volatile unsigned int*) (LCD_CMD_REG_ADDR);

	volatile unsigned int *pCam = (volatile unsigned int*) (OV7670_0_BASE
			| 0x80000000);
	volatile unsigned char pid[2] = { 0, 0 };

	*pLcdCmdReg = 0; // make sure that the DMA is stopped before calling the LCD init functions
	*pCam = 0;
	LCD_Init();
	LCD_Clear(0X00ff);
	//init_lcd_frame();

	printf("%x\n", lcd_frame);

	*pCam = 1; // turns the camera ON. Camera turns on with the next new frame
	Delay_Ms(2000); // add delay to be sure that frames are already in the memory

	*pLcdDestReg = LT24_CONTROLLER_0_BASE + 4;
	*pLcdWidthReg = 240; // LCD width
	*pLcdHeightReg = 320; // LCD height

	volatile unsigned char *pCamAddress = (volatile unsigned char*) (0x1f00000
			| 0x80000000); // by default camera throws images starting from here

	//*pLcdCmdReg = 0x1f00000;

	//printf ("%x\n",*pLcdCmdReg) ;

	int iter =0;
	while (1) {
		int count = 0;
		for (i = 0; i < 320; i++) {
			for (j = 0; j < 240; j++) {

			if (pCamAddress[640 * j + i] < 128) {
			//	if(i < 160){
					//LCD_WR_DATA(0Xffff);
			     	LCD_WR_DATA(0X0000);
					//printf("here");

				} else {
					LCD_WR_DATA(0Xffff);

				}

				count++;
			}

		}

		//Delay_Ms(2000);
		//sprintf("iter : %d", iter++);
	}


}

