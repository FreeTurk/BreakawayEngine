#include "window.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <thread>

#include "../types.h"

Window::Window() {
    width = 800;
    height = 600;
    title = "Hello, World!";
}