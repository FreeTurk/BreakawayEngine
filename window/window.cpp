#include "window.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <thread>

#include "../types.h"

Window::Window(int width, int height, std::string title, Callback gameplay_start, Callback gameplay_loop = []() {}) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->gameplay_loop = gameplay_loop;
    this->gameplay_start = gameplay_start;
}