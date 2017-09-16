#include "Screen.h"
#include <chrono>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "MAP EDITOR"


int main() {
	
	Screen screen(WIDTH, HEIGHT, TITLE);
	std::chrono::high_resolution_clock::time_point prev = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point current = std::chrono::high_resolution_clock::now();

    // run the program as long as the window is open
    while (screen.isOpen())
    {
		prev = current;
		current = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time_span = current - prev;

		screen.input();
		screen.update((float)time_span.count());
		screen.render();
    }

    return 0;
}