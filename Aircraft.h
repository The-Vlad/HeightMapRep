#pragma once
#include "HeightMap.h"
#include <chrono>	// for update time and calculating stats of vehicle


class Aircraft
{
	std::string name;
	bool is_gui;

	float latitude, longitude;
	float x_velocity, y_velocity;
	float altitude;				// height above sea level meters
	float distance_to_surface = NULL;
	float surface_height = NULL;

	//int delay_int = 1;				// delay in milliseconds
	std::chrono::milliseconds delay_ms = std::chrono::milliseconds( 1 );
	std::chrono::steady_clock::duration call_time, interval_time;

	// Панель управления нужна для cv::Trackbar, так как он принимает тип int, а не float
	struct ControlPanel {
		int x_velocity;
		int y_velocity;
		int altitude;
	} control_panel;
	
	std::string heightmap_path;
	HeightMap* hmap;
	std::mutex aircraft_mtx;

public:
	Aircraft(std::string name, float latitude=0.f, float longitude=0.f, float altitude=1000.f,
		float x_velocity=0.f, float y_velocity=0.f);

	void setPosition( float latitude, float longitude );

	void setVelocity( float x_velocity, float y_velocity );

	void setAltitude( float altitude );

	void startEngine();	// gui works

	void fly();

	void getInfo();

	//uint64_t current_timestamp();
};

