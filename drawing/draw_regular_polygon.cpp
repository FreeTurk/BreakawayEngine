#include <iostream>
#include <vector>

#include "../types.h"
#include "../window/window.h"

void Window::draw_regular_polygon(int x, int y, int z, int radius, int sides, RGBA color, bool filled = true) {
    double per_section_angle = (2 * M_PI) / sides;

    int center_x = x;
    int center_y = y;

    std::vector<std::tuple<int, int>> vertices;

    for (int i = 0; i < sides; i++) {
        int vertex_x = center_x + radius * cos(i * per_section_angle);
        int vertex_y = center_y - radius * sin(i * per_section_angle);

        vertices.push_back(std::make_tuple(vertex_x, vertex_y));
    }

    for (int i = 0; i < vertices.size(); ++i) {
        std::cout << "Vertex " << i << ": (" << std::get<0>(vertices[i]) << ", " << std::get<1>(vertices[i]) << ")\n";
    }

    for (int i = 0; i < sides; i++) {
        int x1 = std::get<0>(vertices[i]);
        int y1 = std::get<1>(vertices[i]);
        int x2 = std::get<0>(vertices[(i + 1) % sides]);
        int y2 = std::get<1>(vertices[(i + 1) % sides]);

        draw_line(x1, y1, x2, y2, z, color);
    }

    if (filled) {
        for (int i = 0; i < sides; i++) {
            int x1 = std::get<0>(vertices[0]);
            int y1 = std::get<1>(vertices[0]);
            int x2 = std::get<0>(vertices[i]);
            int y2 = std::get<1>(vertices[i]);
            int x3 = std::get<0>(vertices[(i + 1) % sides]);
            int y3 = std::get<1>(vertices[(i + 1) % sides]);

            draw_triangle(x1, y1, x2, y2, x3, y3, z, color, true);
        }
    }
}