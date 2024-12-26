#include <chrono>
#include <iostream>
#include <thread>

#include "window/window.h"

int main() {
    Window window;
    window.show();

    window.change_color(255);

    // Keep the main thread alive until the user quits
    std::cout << "Press 'q' to quit the program." << std::endl;
    char input;
    do {
        std::cin >> input;  // Wait for user input to quit
    } while (input != 'q');

    // Stop the rendering loop and exit
    window.stop();

    return 0;
}