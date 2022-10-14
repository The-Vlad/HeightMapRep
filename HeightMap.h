#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


class HeightMap
{
	int piece_size;
	float zero_lattitude; // zero x pixel
	float zero_longitude; // zero y pixel
	float height_step;
	float pixel_x_step, pixel_y_step;
public:
	HeightMap( std::string filename );
	// filename is PNG or JPEG file
	// load this file via opencv
	// cut the file on pieces and save them
	// piece size is an optimization parameter

	void SetUAVPos( float latitude, float longitude );
	// set position of vehicle
	// load a correspondance map piece in thread

	float getHeight( float latitude, float longitude );
	// convert lattitude and longitude to pixel coordinate
	// check if pixel coordinates are within loaded piece and return height
	// if no return nan but this case is unusual and rare. our aim is to neglect one
};

