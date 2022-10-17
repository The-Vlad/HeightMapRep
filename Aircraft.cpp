#include "Aircraft.h"

Aircraft::Aircraft( std::string name, float latitude, float longitude, float altitude,
	float x_velocity, float y_velocity )
	: name(name),
	latitude(latitude),
	longitude(longitude),
	altitude(altitude),
	x_velocity(x_velocity),
	y_velocity(y_velocity) { }

void Aircraft::setPosition( float latitude, float longitude ) {
	this->latitude = latitude;
	this->longitude = longitude;
}

void Aircraft::setAltitude( float altitude ) {
	this->altitude = altitude;
}

void Aircraft::startEngine() {
	heightmap_path = "Resources/8k_map/Heightmap.png";
	hmap = new HeightMap( heightmap_path, false, -16, 250, 800, 15.f, 10.f, 10.f );
	hmap->SetUAVPos( 912, 2451 );
	float heights[3] = {
		hmap->getHeight( 958, 2743 ),
		hmap->getHeight( 912, 2451 ),
		hmap->getHeight( 1000, 3000 ),
	};
	hmap->showMap();
	std::cout << "\n\n=========================\n";
	std::cout << "Height on (958, 2743) is: " << heights[0] << " meters" << std::endl;
	std::cout << "Height on (912, 2451) is: " << heights[1] << " meters" << std::endl;
	std::cout << "Height on (1000, 3000) is: " << heights[2] << " meters" << std::endl;
	delete hmap;
}