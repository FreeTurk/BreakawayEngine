#include "window.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <thread>

#include "types.h"

Window::Window() {
    width = 800;
    height = 600;
    title = "Hello, World!";
}

void Window::show() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_Event event;

    std::thread window_thread(&Window::window_loop, this, renderer);

    window_thread.join();

    // SDL_DestroyWindow(window);
    // SDL_Quit();
}

void Window::window_loop(SDL_Renderer* renderer) {
    Callback callback = []() {
        std::cout << "Hello, World!" << std::endl;
    };

    SDL_Event event;
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        callback();
    }
}