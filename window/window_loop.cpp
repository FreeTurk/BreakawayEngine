#include <SDL2/SDL.h>

#include <iostream>

#include "../types.h"
#include "window.h"

void Window::window_loop() {
    Callback callback = []() {
        std::cout << "Hello, World!" << std::endl;
    };

    int i = 0;

    while (window_loop_running) {
        std::unique_lock<std::mutex> lock(this->window_loop_mutex);
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window_loop_running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(this->renderer, this->red, 0, 255, 255);
        SDL_RenderDrawPoint(this->renderer, i, i);
        SDL_RenderPresent(this->renderer);

        callback();

        i++;

        SDL_Delay(10);
    }

    std::cout << "Window loop stopped." << std::endl;
    exit(0);
}