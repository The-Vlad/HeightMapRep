#pragma once
#include "HeightMap.h"

class Aircraft
{
	std::string name;

	float latitude, longitude;
	float x_velocity, y_velocity;
	float altitude;		// height above sea level
	float distance_to_ground;
	
	std::string heightmap_path;
	HeightMap* hmap;
public:
	Aircraft(std::string name, float latitude=0.f, float longitude=0.f, float altitude=1000.f,
		float x_velocity=0.f, float y_velocity=0.f);

	void setPosition( float latitude, float longitude );

	void setVelocity( float x_velocity, float y_velocity );

	void setAltitude( float altitude );

	void startEngine();
};

