#pragma once

const std::vector<float> triangle_rgb = {
     0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};

const std::vector<float> triangle_cmyk = {
    0.0f, 0.5f, 0.0f, 0.f, 1.f, 1.f,
    0.5f, -0.5f, 0.0f, 1.f, 0.f, 1.f,
    -0.5f, -0.5f, 0.0f, 1.f, 1.f, 0.f
};

const std::vector<float> triangle_rectangular_rgb = {
        0.5f, 0.5f, 0.0f, 1.f, 0.f, 0.f,
        -0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f,
        -0.5f, 0.5f, 0.0f, 0.f, 0.f, 1.f,
};

const std::vector<float> triangle_rectangular_cmyk = {
    0.5f, 0.5f, 0.0f, 1.f, 0.f, 1.f,
    -0.5f, -0.5f, 0.0f, 1.f, 1.f, 0.f,
    -0.5f, 0.5f, 0.0f, 0.f, 1.f, 1.f,
};