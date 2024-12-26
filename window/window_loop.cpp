#include <SDL2/SDL.h>

#include <iostream>

#include "../types.h"
#include "window.h"

void Window::window_loop() {
    while (window_loop_running) {
        std::unique_lock<std::mutex> lock(this->window_loop_mutex);

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window_loop_running = false;
                break;
            }
        }

        SDL_GetWindowSize(window, &width, &height);

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                RGBA color = matrix[i][j];
                SDL_SetRenderDrawColor(renderer, std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color));
                SDL_RenderDrawPoint(renderer, j, i);
            }
        }

        SDL_RenderPresent(renderer);

        gameplay_loop();

        SDL_Delay(10);
    }

    std::cout << "Window loop stopped." << std::endl;
}