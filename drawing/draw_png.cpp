#include <iostream>
#include <mutex>

#include "../types.h"
#include "../window/window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

void Window::draw_png(std::string filename, int x, int y, int scale = 1) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    std::unique_lock<std::mutex> lock(this->window_loop_mutex);

    // Creating buffer for the image if the matrix vertices are yet to be initialized (to that size)
    if (matrix.size() < height * scale + y) {
        matrix.resize(height * scale + y, Line());
    }

    for (Line& l : matrix) {
        if (l.size() < width * scale + x) {
            l.resize(width * scale + x, RGBA(0, 0, 0, 0));
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = (i * width + j) * 4;

            for (int k = 0; k < scale; k++) {
                for (int l = 0; l < scale; l++) {
                    matrix[y + i * scale + k][x + j * scale + l] = RGBA(data[index], data[index + 1], data[index + 2], data[index + 3]);
                }
            }
        }
    }
}