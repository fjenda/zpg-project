/**
 * @file plain.h
 *
 * @brief Plain model 
 *
 * @details  Command for rendering
 *           glDrawArrays(GL_TRIANGLES, 0, 6);
 *
 * @author Martin Nemec
 *
 * @year 2023
 **/
#pragma once

const float plain[36] = {
    100.0f, 0.0f,  100.0f, 0.0f, 1.0f, 0.0f,
    100.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f,
   -100.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f,

   -100.0f, 0.0f,  100.0f, 0.0f, 1.0f, 0.0f,
    100.0f, 0.0f,  100.0f, 0.0f, 1.0f, 0.0f,
   -100.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f
};