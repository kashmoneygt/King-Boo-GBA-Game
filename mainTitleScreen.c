// GBA Game
// Name: KASHYAP PATEL

#include "boo.h"
#include "ggwp.h"
#include "title.h"
#include "myLib.h"
#include "text.h"

int main() {

	REG_DISPCNT = MODE_3 | BG2_ENABLE;

	drawImage3(55, 95, BOO_WIDTH, BOO_HEIGHT, boo);

	drawString(38, 20, "King Boo is terrified of humans!", YELLOW);

	drawString(115, 25, "Protect him at all costs using", YELLOW);
	drawString(140, 40, "the arrows keys!", YELLOW);
	drawString(135, 50, "(Press A to continue)", YELLOW);

	while (1) {
	}

	return 0;

}