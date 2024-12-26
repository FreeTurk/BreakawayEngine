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

    Window(int width, int height, std::string title, Callback gameplay_start, Callback gameplay_loop = []() {});
    void show();
    void stop();
    void change_loop(Callback callback);
    void change_start(Callback callback);
    void draw_png(std::string filename, int x, int y, int scale = 1);
    void draw_line(int x1, int y1, int x2, int y2, RGBA color, int thickness = 1);
    void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA color, bool filled = true);
    void draw_rectangle(int x, int y, int width, int height, RGBA color, bool filled = true);
    void draw_regular_polygon(int x, int y, int radius, int sides, RGBA color, bool filled = true);

   private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    std::thread window_thread;
    std::mutex window_loop_mutex;
    std::atomic<bool> window_loop_running = false;
    Callback gameplay_loop = []() {};
    Callback gameplay_start = []() {};
    void window_loop();
    void show_callback();
};

#endif  // WINDOW_H