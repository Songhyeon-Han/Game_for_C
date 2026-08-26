#include <iostream>
#include <windows.h>
#include <conio.h>

void setCursor(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
	int x = 10;
	const int WIDTH = 40;
	int ballX = 20;   // 가운데 위치
	int ballDx = 1; // 1칸씩 이동이고 공의 속도

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

		setCursor(ballX, 2); // 가운데 공백을 그림
		std::cout << " ";
		ballX = ballX + ballDx; // 처음 21
		if (ballX <= 0 || ballX >= WIDTH - 1)
			ballDx = -ballDx;  // 공의 경계선 계산

		setCursor(x, 0);
		std::cout << "@";
		setCursor(ballX, 2);
		std::cout << "0"; // 매 프레임 공을 찍는다. 경계선 닿기 전에는 if문이 돌지 않는다.

		Sleep(33);
	}
	return 0;
}