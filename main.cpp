﻿// Jan Fojtík
// FOJ0127

#include <cstdio>

// Include chrono for time measurement
#include <chrono>

#include "Include/Application.h"
#include "Scenes/SolarSystemScene.h"
#include "Scenes/BallScene.h"
#include "Scenes/MultipleShadersScene.h"

int main()
{
	// get start time
	auto start = std::chrono::high_resolution_clock::now();

    Application& app = Application::get();
    app.initialization(1280, 720);

//    app.addScene(new SolarSystemScene(2));
//    app.addScene(new BallScene(3));
//    app.addScene(new MultipleShadersScene(4));

    app.run();

    // get end time
	auto finish = std::chrono::high_resolution_clock::now();

	fprintf(stdout, "[DEBUG] Application stats\n");
	fprintf(stdout, "   Time elapsed: %f seconds\n", std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1000000000.0);

	return 0;
}