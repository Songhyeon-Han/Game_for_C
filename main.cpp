#include <iostream>
#include <windows.h>
#include <conio.h>

const int WIDTH = 40;    // 게임 창 가로 한계 
const int HEIGHT = 20;   // 게임 창 세로 한계

void setCursor(int x, int y) {
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Ball{
private:
	int x;   // 위치
	int dx;  // 속도
	int y;
	int dy;  //세로 속도
	int frameCount = 0;

public:
	Ball(int startX, int startY, int startDx, int startDy) {
		x = startX;
		dx = startDx;
		y = startY;
		dy = startDy;
	}

	bool update(int paddleX) {
		frameCount = frameCount + 1;
		if (frameCount < 8) 
			return true; // 아직 움직이면은 안됨
		frameCount = 0;


		setCursor(x, y);
		std::cout << " ";
		x = x + dx;          // 움직이고
		y = y + dy;
		if (x <= 0 || x >= WIDTH - 1)dx = -dx;
		if (y <= 0) dy = -dy;  // 위쪽 벽. 튕기게

		if (y >= HEIGHT - 2) {                            // 패들 줄 바로 위에 도달했다면
			if (x >= paddleX - 1 && x <= paddleX + 1) {   // &&는 두 값이 참일때. paddleX가 가로로 ±1칸 안 (3칸 안)
				dy = -dy;
			}
			else {
				return false;
			}
		}
		return true;
	}

	void draw() {
		setCursor(x, y);
		std::cout << "O";
	}
};

class Paddle{
private:
	int x;
	int y;

public:
	Paddle(int startX) {
		x = startX;
		y = HEIGHT - 1;
	}

	void update() {
		if (_kbhit())
		{
			char key = _getch();
			setCursor(x, y);
			std::cout << " ";

			if (key == 'a') x = x - 1;
			if (key == 'd') x = x + 1;
			if (x < 0) x = 0;
			if (x >= WIDTH) x = WIDTH - 1;

		}
	}

	void draw() {
		setCursor(x, y);
		std::cout << "@";
	}

	int getX() const {                // 값을 읽기만 하는 창구
		return x;
	}

	
};

int main() {

	Paddle paddle  ( 10 );
	Ball ball ( 20, 5, 1, 1 );            // 기존에 {}을 넣어서 값을 넣었고, 생성자가 생기면서 ()로 바뀜. = 도 사라짐
	                                      // x,y는 서로 붙어 있어야 할 필요 없고, x는 가로 몇번째  y는 세로 몇번째로 서로 독립적

	while (true) {
		
		paddle.update();
		if (!ball.update(paddle.getX())) {
			setCursor(15, 10);
			std::cout << "GAME OVER";
			break;
		}
		paddle.draw();
		ball.draw();    // 그리기도 이 한줄

		Sleep(33);
		
	}

	return 0;
}