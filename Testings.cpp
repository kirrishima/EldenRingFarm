#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>

#define VK_CLOSE_BRACE 0xDD  // "}" (Shift + ])
#define VK_RUSSIAN_HARD_SIGN 0xDE  // "ъ" (в русской раскладке)
#define VK_KEY_A 0x65  // 'A'
#define VK_KEY_S 0x83  // 'S'
#define VK_KEY_W 0x87  // 'W'
#define VK_KEY_D 0x65  // 'D'
#define VK_KEY_Q 0x81  // 'Q'
#define VK_KEY_SHIFT 0x16  // Shift
#define VK_KEY_C 0x67  // 'C'
#define VK_LBUTTON 0x01  // Left Mouse Button (ЛКМ)
#define VK_RBUTTON 0x02  // Right Mouse Button (ПКМ)
#define VK_ESC 0x27  // Right Mouse Button (ПКМ)

std::atomic<bool> running(true);

// Функция для плавного перемещения мыши
void MoveMouseSmoothly(int dx, int dy, int duration_ms) {
	const int steps = duration_ms;
	int step_dx = dx / steps;
	int step_dy = dy / steps;
	int delay_per_step = duration_ms / steps;

	for (int i = 0; i < steps; ++i) {
		INPUT input = { 0 };
		input.type = INPUT_MOUSE;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		input.mi.dx = step_dx;
		input.mi.dy = step_dy;
		SendInput(1, &input, sizeof(INPUT));
		Sleep(1);
	}
}

void keyListener() {
	while (running) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			std::cout << "Escape key pressed!\n";
			running = false;
			exit(EXIT_SUCCESS);
		}
		Sleep(100);
	}
}

void CheckForExit() {
	while (running) {
		if (false) {
			running = false;
		}
		Sleep(10);
	}
}

void boulderFarm()
{
	MoveMouseSmoothly(3000, 0, 15);
	Sleep(10000);
	MoveMouseSmoothly(400, 0, 45);
	Sleep(2000);
	MoveMouseSmoothly(-600, 0, 25);
	Sleep(1000);
	MoveMouseSmoothly(3600, 0, 75);

}

void birdFarm()
{

	MoveMouseSmoothly(-1300, 0, 15);
	Sleep(1300);
	MoveMouseSmoothly(0, 450, 15);
	Sleep(200);
	MoveMouseSmoothly(-910, 0, 15);

}

void albinorsFarm()
{
	MoveMouseSmoothly(-900, 0, 15);
}

int main() {
	std::thread listenerThread(keyListener);

	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
		if (GetAsyncKeyState(VK_CLOSE_BRACE) & 0x8000) {
			albinorsFarm();
		}
	}

	listenerThread.join();
	return 0;
}
