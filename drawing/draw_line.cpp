#include <mutex>

#include "../types.h"
#include "../window/window.h"

void Window::draw_line(int x1, int y1, int x2, int y2, int z, RGBA color, int thickness = 1) {
    std::unique_lock<std::mutex> lock(this->window_loop_mutex);

    // Ensure that the matrix vector is big enough
    if (this->matrix.size() < z + 1) {
        this->matrix.resize(z + 1, Matrix());
    }

    Matrix& matrix = this->matrix[z];

    if (matrix.size() < std::max(y1, y2) + thickness) {
        matrix.resize(std::max(y1, y2) + thickness, Line());
    }

    for (Line& l : matrix) {
        if (l.size() < std::max(x1, x2) + thickness) {
            l.resize(std::max(x1, x2) + thickness, RGBA(0, 0, 0, 0));
        }
    }

    // Bresenham's Line Algorithm
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        // Draw the pixel
        for (int i = 0; i < thickness; ++i) {
            for (int j = 0; j < thickness; ++j) {
                int px = x1 + i;
                int py = y1 + j;
                if (px >= 0 && py >= 0 && px < matrix[0].size() && py < matrix.size()) {
                    matrix[py][px] = color;
                }
            }
        }

        // Check if the line is complete
        if (x1 == x2 && y1 == y2) break;

        // Update error term and coordinates
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}
