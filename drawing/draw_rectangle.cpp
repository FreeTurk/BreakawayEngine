#include <mutex>

#include "../types.h"
#include "../window/window.h"

void Window::draw_rectangle(int x, int y, int z, int width, int height, RGBA color, bool filled = true) {
    if (filled) {
        draw_triangle(x, y, x + width, y, x, y + height, z, color, true);
        draw_triangle(x + width, y, x + width, y + height, x, y + height, z, color, true);
    } else {
        draw_line(x, y, x + width, y, z, color);
        draw_line(x + width, y, x + width, y + height, z, color);
        draw_line(x + width, y + height, x, y + height, z, color);
        draw_line(x, y + height, x, y, z, color);
    }
}