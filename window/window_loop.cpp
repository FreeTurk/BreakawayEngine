#include <SDL2/SDL.h>

#include <iostream>

#include "../types.h"
#include "window.h"

void Window::window_loop() {
    while (window_loop_running) {
        std::unique_lock<std::mutex> lock(this->window_loop_mutex);

        if (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) {
                window_loop_running = false;
                break;
            }

        int current_width, current_height;
        SDL_GetWindowSize(window, &current_width, &current_height);

        if (matrix_copy != matrix || current_width != width || current_height != height)
            for (Matrix layer : matrix)
                for (int i = 0; i < layer.size(); i++)
                    for (int j = 0; j < layer[i].size(); j++) {
                        RGBA color = layer[i][j];
                        SDL_SetRenderDrawColor(renderer, std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color));
                        SDL_RenderDrawPointF(renderer, j, i);
                    }

        matrix_copy = matrix;
        width = current_width;
        height = current_height;

        SDL_RenderPresent(renderer);

        gameplay_loop();

        SDL_Delay(10);
    }

    std::cout << "Window loop stopped." << std::endl;
}