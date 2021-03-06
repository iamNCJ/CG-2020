#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include "ppm.h"

const int N = 2000;

struct Point {
    double x, y;
};

struct Pixel {
    unsigned char R, G, B;
};

int main(int argc, char **argv) {
    unsigned char data[400 * 300 * 3] = {0};
    Point points[N * 4];
    auto *pixel = (Pixel *) data;
    double x_c, y_c, a, b, theta;
    bool fill;
    if (argc != 7) {
        std::cout << "Usage: Xc Yc a b theta fill?(0 for no)" << std::endl;
        exit(0);
    }
    x_c = std::stod(argv[1]);
    y_c = std::stod(argv[2]);
    a = std::stod(argv[3]);
    b = std::stod(argv[4]);
    theta = std::stod(argv[5]);
    fill = std::strcmp(argv[6], "no");

    // Step 1 - Scan convert an ellipse at the origin point
    // initial points
    points[0] = {a, 0};
    points[N] = {0, b};
    points[2 * N] = {-a, 0};
    points[3 * N] = {0, -b};
    // prepare constants
    double sin_delta = std::sin(M_PI / 2 / N);
    double cos_delta = std::cos(M_PI / 2 / N);
    // iteration
    for (int i = 1; i < N; ++i) {
        double x = points[i - 1].x * cos_delta - a * points[i - 1].y * sin_delta / b;
        double y = points[i - 1].y * cos_delta + b * points[i - 1].x * sin_delta / a;
        points[i].x = points[3 * N + i].x = x;
        points[N + i].x = points[2 * N + i].x = -x;
        points[i].y = points[N + i].y = y;
        points[N * 2 + i].y = points[N * 3 + i].y = -y;
    }

    // Step 2 - Rotate the ellipse and move it to (Xc, Yc)
    double sin_beta = std::sin(M_PI / 180 * theta);
    double cos_beta = std::cos(M_PI / 180 * theta);
    int x_min = 400, x_max = 0, y_min = 300, y_max = 0;
    // map into new coordinate system
    for (auto &point : points) {
        int x = std::max(0, std::min(int(point.x * cos_beta - point.y * sin_beta + x_c), 399));
        int y = std::max(0, std::min(int(point.x * sin_beta + point.y * cos_beta + y_c), 299));
        pixel[y * 400 + x] = {255, 255, 255};
        x_min = std::min(x_min, x);
        x_max = std::max(x_max, x);
        y_min = std::min(y_min, y);
        y_max = std::max(y_max, y);
    }

    // Step 3 - Fill the ellipse
    if (fill)
        for (int y = y_min; y <= y_max; ++y) {
            int x_line_min = 400, x_line_max = 0;
            for (int x = x_min; x <= x_max; ++x) {
                if (pixel[y * 400 + x].R) {
                    x_line_min = std::min(x_line_min, x);
                    x_line_max = std::max(x_line_max, x);
                }
            }
            for (int x = x_line_min + 1; x < x_line_max; ++x) {
                pixel[y * 400 + x] = {255, 255, 255};
            }
        }

    ppmWrite("test.ppm", data, 400, 300);
    return 0;
}