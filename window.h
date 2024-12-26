#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <string>

class Window {
   public:
    int width;
    int height;
    std::string title;

    Window();
    void show();

   private:
    void window_loop(SDL_Renderer* renderer);
};

#endif  // WINDOW_H