#include <mutex>

#include "window.h"

void Window::change_loop(Callback callback) {
    std::unique_lock<std::mutex> lock(this->window_loop_mutex);

    this->gameplay_loop = callback;
}