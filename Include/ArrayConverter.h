/**
 * @file ArrayConverter.h
 *
 * @brief ArrayConverter class
 *
 * @details ArrayConverter class is used to convert const float arrays into vectors
 *
 * @author Jan Fojtik
 *
 * @year 2023
 **/

#ifndef ZPGPROJEKT_ARRAYCONVERTER_H
#define ZPGPROJEKT_ARRAYCONVERTER_H

#include <vector>

class ArrayConverter {
public:
    static std::vector<float> convert(const float* array, int size);
};


#endif //ZPGPROJEKT_ARRAYCONVERTER_H
