#include <iostream>
#include <windows.h>
#include <conio.h>

const int WIDTH = 40;

void setCursor(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

struct Ball
{
	int x;   // 위치
	int dx;  // 속도

	void update() {
		setCursor(x, 2);
		std::cout << " ";
		x = x + dx;          // 움직이고
		if (x <= 0 || x >= WIDTH - 1)
			dx = -dx;
	}

	void draw() {
		setCursor(x, 2);
		std::cout << "O";
	}
};

int main() {
	int x = 10;
	Ball ball = { 20, 1 };
	

	while (true) {
		if (_kbhit()) {              // 눌린 키 있을 때만
			char key = _getch();     // 읽는다
			setCursor(x, 0);
			std::cout << " ";

			if (key == 'a') x = x - 1;
			if (key == 'd') x = x + 1;
			if (x < 0) x = 0;
			if (x >= WIDTH) x = WIDTH -1;
		}

		ball.update();   // 공은 이 한 줄
		setCursor(x, 0);
		std::cout << "@";
		ball.draw();    // 그리기도 이 한줄

		Sleep(33);
	}

	return 0;
}