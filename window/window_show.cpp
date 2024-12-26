#include <SDL2/SDL.h>

#include <iostream>
#include <thread>

#include "window.h"

void Window::show_callback() {
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    this->event = SDL_Event();

    this->gameplay_start();

    this->window_loop();
}

void Window::show() {
    window_loop_running = true;
    window_thread = std::thread(&Window::show_callback, this);

    window_thread.detach();
}

void Window::stop() {
    window_loop_running = false;
}