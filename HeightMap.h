#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <mutex>

class HeightMap
{
	int piece_size;
	float zero_latitude;	// corresponds to zero x pixel
	float zero_longitude;	// corresponds to zero y pixel
	float height_step;		// meters per pixel brightness
	float pixel_x_step, pixel_y_step;	// how many latitude and longitude per one pixel

	int piece_index_i, piece_index_j;

	std::string filename;
	std::string piece_filename = "";
	std::string window_name = "Current Map";
	cv::Mat current_map;
	std::mutex mtx;

public:
	HeightMap(
		std::string filename, bool is_new_map=true,
		float zero_latitude=0.f, float zero_longitude=0.f,
		int piece_size=800, float height_step=34.7f,
		float pixel_x_step=10.f, float pixel_y_step=10.f);
	// filename is PNG or JPEG file
	// load this file via opencv
	// cut the file on pieces and save them
	// piece size is an optimization parameter

	void SetUAVPos( float latitude, float longitude );
	// set position of vehicle
	// load a correspondance map piece in thread

	float getHeight( float latitude, float longitude );
	// convert latitude and longitude to pixel coordinate
	// check if pixel coordinates are within loaded piece and return height
	// if no return nan but this case is unusual and rare. our aim is to neglect one

	void showMap(float latitude, float longitude );

	void getImageDepth();

	std::string getPieceName();

private:
	void old_cropImage(int cols_num, int cols_res, int rows_num, int rows_res);
	void cropImage( int x_pieces_num, int y_pieces_num, int piece_x_res, int piece_y_res );
};

