#include <mutex>

#include "../types.h"
#include "../window/window.h"

void Window::draw_line(int x1, int y1, int x2, int y2, RGBA color, int thickness = 1) {
    std::unique_lock<std::mutex> lock(this->window_loop_mutex);

    // Ensure that the matrix vector is big enough

    if (matrix.size() < std::max(y1, y2) + thickness) {
        matrix.resize(std::max(y1, y2) + thickness, Line());
    }

    for (Line& l : matrix) {
        if (l.size() < std::max(x1, x2) + thickness) {
            l.resize(std::max(x1, x2) + thickness, RGBA(0, 0, 0, 0));
        }
    }

    // Draw a line considering that the second point might be smaller than the first
    if (x1 > x2) {
        std::swap(x1, x2);
    }

    if (y1 > y2) {
        std::swap(y1, y2);
    }

    // Calculate the slope and the direction of the line
    float m = (y2 - y1) / (float)(x2 - x1);
    int dx = x2 - x1;
    int dy = y2 - y1;

    // Draw a vertical line
    if (dx == 0) {
        for (int i = 0; i < thickness; i++) {
            for (int j = 0; j < dy; j++) {
                matrix[y1 + j][x1 + i] = color;
            }
        }
    }
    // Draw a horizontal line
    else if (dy == 0) {
        for (int i = 0; i < thickness; i++) {
            for (int j = 0; j < dx; j++) {
                matrix[y1 + i][x1 + j] = color;
            }
        }
    }
    // Draw a line with a slope
    else {
        // Draw a line with a slope that is less than 1
        if (std::abs(m) <= 1) {
            for (int i = 0; i < thickness; i++) {
                for (int j = 0; j < dx; j++) {
                    int y = y1 + (int)(m * j);
                    matrix[y + i][x1 + j] = color;
                }
            }
        }
        // Draw a line with a slope that is greater than 1
        else {
            m = 1 / m;

            for (int i = 0; i < thickness; i++) {
                for (int j = 0; j < dy; j++) {
                    int x = x1 + (int)(m * j);
                    matrix[y1 + j][x + i] = color;
                }
            }
        }
    }
}