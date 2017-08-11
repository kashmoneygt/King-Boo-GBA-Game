#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

/* Draws an arbitrary sized image onto the screen with DMA
 * @param r row to draw the image
 * @param c column to draw the image
 * @param width width of the imagef
 * @param height height of hte image
 * @param image Pointer to the first element of the image
 */
void drawImage3(int r, int c, int width, int height, const u16* image) {

	for (int row = 0; row < height; row++) {
		REG_DMA3SAD = (u32)(image + OFFSET(row, 0, width));
		REG_DMA3DAD = (u32)(videoBuffer + OFFSET(row + r, c, 240));
		REG_DMA3CNT = width | DMA_ON;
	}
}

void setPixel(int row, int col, unsigned short color) {
	videoBuffer[OFFSET(row,col, 240)] = color;
}

void drawRect(int r, int c, int width, int height, const u16* color) {

	for (int row = 0; row < height; row++) {
		REG_DMA3SAD = (u32)&color;
		REG_DMA3DAD = (u32)(&videoBuffer[OFFSET(row + r, c, 240)]);
		REG_DMA3CNT = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

void waitForVblank() {
	while (SCANLINECOUNTER > 160);
	while (SCANLINECOUNTER < 160);
}