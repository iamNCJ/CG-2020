#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <algorithm>
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
    double x_c, y_c, a, b, theta = 0;
    if (argc < 5 || argc > 6) {
        std::cout << "Usage: Xc Yc a b [theta]" << std::endl;
        exit(0);
    }
    x_c = std::stod(argv[1]);
    y_c = std::stod(argv[2]);
    a = std::stod(argv[3]);
    b = std::stod(argv[4]);
    if (argc == 6) {
        theta = std::stod(argv[5]);
    }

    // Step 1 - Scan convert an ellipse at the origin point
    // initial points
    points[0] = {a, 0};
    points[N] = {0, b};
    points[2 * N] = {-a, 0};
    points[3 * N] = {0, -b};
    // prepare constants
    double sin_delta = std::sin(M_PI / 2 / N);
    double cos_delta = std::cos(M_PI / 2 / N);
    // Iteration
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
    // map into new coordinate system
    for (auto &point : points) {
        int x = std::max(0, std::min(int(point.x * cos_beta - point.y * sin_beta + x_c), 399));
        int y = std::max(0, std::min(int(point.x * sin_beta + point.y * cos_beta + y_c), 299));
        pixel[y * 400 + x] = {255, 255, 255};
    }

    ppmWrite("test.ppm", data, 400, 300);
    return 0;
}