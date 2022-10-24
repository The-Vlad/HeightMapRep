#pragma once
#include "HeightMap.h"
#include <chrono>

class Aircraft
{
	std::string name;

	float latitude, longitude;
	float x_velocity, y_velocity;
	float altitude;				// height above sea level meters
	float distance_to_surface = NULL;
	float surface_height = NULL;

	float delay_ms = 20;				// delay in milliseconds
	const float one_sec_delay = 1000;	// in milliseconds

	struct ControlPanel {	// in decimeters
		int x_velocity;
		int y_velocity;
		int altitude;
	} control_panel;
	
	std::string heightmap_path;
	HeightMap* hmap;
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

