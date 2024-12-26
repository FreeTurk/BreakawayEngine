#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <atomic>
#include <mutex>
#include <string>
#include <thread>

#include "../types.h"

class Window {
   public:
    int width;
    int height;
    std::string title;
    int red = 0;
    Matrix matrix;

    Window();
    void show();
    void stop();
    void change_loop(Callback callback);
    void change_start(Callback callback);


   private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    std::thread window_thread;
    std::mutex window_loop_mutex;
    std::atomic<bool> window_loop_running = false;
    Callback gameplay_loop;
    Callback gameplay_start;
    void window_loop();
    void show_callback();
};

#endif  // WINDOW_H