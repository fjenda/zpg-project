//
// Created by Honza Fojtík on 28.10.2023.
//

#include "../Include/ArrayConverter.h"

std::vector<float> ArrayConverter::convert(const float* array, int size) {
    std::vector<float> result;
    int actualSize = size / sizeof(float);
    for (int i = 0; i < actualSize; i++) {
        result.push_back(array[i]);
    }
    return result;
}

std::vector<int> ArrayConverter::convert(const int* array, int size) {
    std::vector<int> result;
    int actualSize = size / sizeof(int);
    for (int i = 0; i < actualSize; i++) {
        result.push_back(array[i]);
    }
    return result;
}