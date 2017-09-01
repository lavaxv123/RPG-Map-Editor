#include "Screen.h"
#include <iostream>
#include <string>


#define WIDTH 800
#define HEIGHT 600
#define TITLE "MAP EDITOR"




int main() {
	
	Screen screen(WIDTH, HEIGHT, TITLE);
	
    // run the program as long as the window is open
    while (screen.isOpen())
    {
		screen.input();
		screen.render();
    }

    return 0;
}