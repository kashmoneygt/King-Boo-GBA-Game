// GBA Game
// Name: KASHYAP PATEL

#include "boo.h"
#include "ggwp.h"
#include "title.h"
#include "human.h"
#include "myLib.h"
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

int score = 0;
char scoreStr[100];

int main() {

	REG_DISPCNT = MODE_3 | BG2_ENABLE;

	//game isn't over
	int isGameOver = 0;

	int reset = 0;

	//distance b/w top humans and bot humans
	int dist = 70;


	//where boo starts
	//boo size = 25x25
	int boorow = 75;
	int boocol = 130;

	//how much to move boo per key prss
	int boomoverow = 2;
	int boomovecol = 2;


	//human size = 11x17
	//define top humans and bottom humans
	HUMAN humans1[NUMHUMANS];
	HUMAN humans2[NUMHUMANS];


	int colsize = 218;

	//define first human in top humans
	humans1[0].row = 30;
	humans1[0].col = 229;

	//define first human in bot humans
	humans2[0].row = humans1[0].row + dist;
	humans2[0].col = humans1[0].col;

	//define the rest of the humans
	for (int i = 1; i < NUMHUMANS; i++) {
		humans1[i].row = humans1[i - 1].row + rand() % 11 + (-5);
		humans1[i].col = colsize;

		colsize -= 11;

		humans2[i].row = humans1[i].row + dist;
		humans2[i].col = humans1[i].col;

	}
 
 	//start the game
 	int start = 1;

	//has the title been shown
	int showedTitle = 0;



	while (1) {

		if (start) {
			drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title);
			showedTitle = 1;
		}

		if ((KEY_DOWN_NOW(BUTTON_A) & showedTitle) || (reset)) {
			reset = 0;
			start = 0;
			showedTitle = 0;
			isGameOver = 0;
			clear();
			score = 0;
			boorow = 75;
			boocol = 130;
			drawImage3(boorow, boocol, BOO_WIDTH, BOO_HEIGHT, boo);
			drawString(5, 160, "Score: ", YELLOW);

		}

		if (!showedTitle && !isGameOver) {

				score++;

				clearScore();
				sprintf(scoreStr, "%d", score);
				drawString(5, 200, scoreStr, YELLOW);

				for (int i = 0; i < NUMHUMANS; i++) {
					drawImage3(humans1[i].row, humans1[i].col, HUMAN_WIDTH, HUMAN_HEIGHT, human);
					drawImage3(humans2[i].row, humans2[i].col, HUMAN_WIDTH, HUMAN_HEIGHT, human);
				}

				if (boocol <= 15) {
					boocol = 15;
					drawRect(0, 0, 15, 160, BLACK);
				}

				if (boocol + BOO_WIDTH >= 239) {
					boocol = 239 - BOO_WIDTH;
					drawRect(0, 234, 15, 160, BLACK);
				}


				waitForVblank();

				if (score % 10 == 0) {

					for (int i = 20; i > 0; i--) {
						clearHuman(humans1[i].row, humans1[i].col);
						humans1[i].row = humans1[i - 1].row;

						clearHuman(humans2[i].row, humans2[i].col);
						humans2[i].row = humans1[i].row + dist;
					}

					clearHuman(humans1[0].row, humans1[0].col);
					clearHuman(humans2[0].row, humans2[0].col);

					if (humans1[0].row >= 30) {
						humans1[0].row = humans1[0].row + rand() % 17 + (-8);
					} else {
						humans1[0].row = 30;
					}

					if (humans1[0].row <= 70) {
						humans1[0].row = humans1[0].row + rand() % 17 + (-8);
					} else {
						humans1[0].row = 70;
					}

					humans2[0].row = humans1[0].row + dist;
				}

				if (KEY_DOWN_NOW(BUTTON_UP)) {
					clearBoo(boorow, boocol);
					boorow -= boomoverow;
					drawImage3(boorow, boocol, BOO_WIDTH, BOO_HEIGHT, boo);
				}

				if (KEY_DOWN_NOW(BUTTON_DOWN)) {
					clearBoo(boorow, boocol);
					boorow += boomoverow;
					drawImage3(boorow, boocol, BOO_WIDTH, BOO_HEIGHT, boo);
				}

				if (KEY_DOWN_NOW(BUTTON_LEFT)) {
					clearBoo(boorow, boocol);
					boocol -= boomovecol;
					drawImage3(boorow, boocol, BOO_WIDTH, BOO_HEIGHT, boo);
				}

				if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
					clearBoo(boorow, boocol);
					boocol += boomovecol;
					drawImage3(boorow, boocol, BOO_WIDTH, BOO_HEIGHT, boo);
				}

				if (KEY_DOWN_NOW(BUTTON_SELECT)) {
					start = 1;
				}

				for (int i = 0; i < NUMHUMANS; i++) {

					if ((boocol > 228 - (13 * i)) && (boocol < 239 - (12 * i))) {

						if ((boorow - 1 <= humans1[i].row + HUMAN_HEIGHT) || (boorow + BOO_HEIGHT + 1 >= humans2[i].row)) {
							for (int i = 0; i < NUMHUMANS; i++) {
								clearHuman(humans1[i].row, humans1[i].col);
								clearHuman(humans2[i].row, humans2[i].col);
								humans1[i].row = 40;
								humans2[i].row = humans2[i].row + dist;
							}
							clear();
							gameOver(score);
							isGameOver = 1;

						}
					}

				}

		}

		if (KEY_DOWN_NOW(BUTTON_A) && isGameOver) {
			reset = 1;
			isGameOver = 0;

		}

	}

	return 0;

}

void clear() {
	drawRect(0, 0, 240, 160, BLACK);
}

void clearHuman(int row, int col) {
	drawRect(row, col, HUMAN_WIDTH, HUMAN_HEIGHT, BLACK);
}

void clearBoo(int row, int col) {
	drawRect(row, col, BOO_WIDTH, BOO_WIDTH, BLACK);
}

void clearScore() {
	drawRect(5, 200, 40, 10, BLACK);
}

void gameOver() {
	clear();
	drawImage3(0, 0, GGWP_WIDTH, GGWP_HEIGHT, ggwp);
	drawString(120, 70, "Final Score: ", YELLOW);
	sprintf(scoreStr, "%d", score);
	drawString(120, 145, scoreStr, YELLOW);
	drawString(130, 45, "(Press A to Start Over)", YELLOW);
}