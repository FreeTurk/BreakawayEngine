#include <chrono>
#include <iostream>
#include <thread>

#include "window/window.h"

int main() {
    Window window = Window(800, 600, "Hello, World!", []() { std::cout << "Gameplay started." << std::endl; });

    window.show();

    window.draw_png("VirtualBox_logo_64px.png", 0, 0, 2);
    window.draw_png("VirtualBox_logo_64px.png", 64, 0, 2, 2);

    window.draw_rectangle(100, 100, 1, 100, 100, RGBA(255, 0, 0, 255));
    window.draw_rectangle(200, 200, 1, 100, 100, RGBA(0, 255, 0, 255), false);

    window.draw_regular_polygon(400, 300, 1, 100, 6, RGBA(0, 0, 255, 255), true);
    window.draw_regular_polygon(600, 300, 1, 100, 6, RGBA(255, 255, 0, 255), false);

    // Keep the main thread alive until the user quits
    std::cout
        << "Press 'q' to quit the program." << std::endl;
    char input;
    do {
        std::cin >> input;  // Wait for user input to quit
    } while (input != 'q');

    // Stop the rendering loop and exit
    window.stop();

    return 0;
}