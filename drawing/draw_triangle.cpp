#include <mutex>

#include "../types.h"
#include "../window/window.h"

void Window::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, RGBA color, bool filled) {
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x3, y3, color);
    draw_line(x3, y3, x1, y1, color);

    if (filled) {
        std::unique_lock<std::mutex> lock(this->window_loop_mutex);

        // Calculate the bounding box of the triangle
        int x_min = std::min({x1, x2, x3});
        int x_max = std::max({x1, x2, x3});
        int y_min = std::min({y1, y2, y3});
        int y_max = std::max({y1, y2, y3});

        // Fill the triangle
        for (int i = y_min; i <= y_max; i++) {
            for (int j = x_min; j <= x_max; j++) {
                // Calculate the barycentric coordinates of the pixel
                float alpha = ((y2 - y3) * (j - x3) + (x3 - x2) * (i - y3)) / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
                float beta = ((y3 - y1) * (j - x3) + (x1 - x3) * (i - y3)) / (float)((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
                float gamma = 1.0f - alpha - beta;

                // If the pixel is inside the triangle, color it
                if (alpha >= 0 && beta >= 0 && gamma >= 0) {
                    matrix[i][j] = color;
                }
            }
        }
    }
}