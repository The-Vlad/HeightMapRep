#include "HeightMap.h"

HeightMap::HeightMap( std::string filename, bool is_new_map,
	float zero_latitude, float zero_longitude,
	int piece_size, float height_step,
	float pixel_x_step, float pixel_y_step )
	: filename( filename ),
	zero_latitude( zero_latitude ),
	zero_longitude( zero_longitude ),
	piece_size( piece_size ),
	height_step( height_step ),
	pixel_x_step( pixel_x_step ),
	pixel_y_step( pixel_y_step )
{
	current_map = cv::imread( filename );
	cv::cvtColor( current_map, current_map, cv::COLOR_BGR2GRAY );

	if (is_new_map) {

		int piece_x_num = 1, piece_y_num = 1;
		int piece_x_res = 0, piece_y_res = 0;
		int cols = current_map.cols, rows = current_map.rows;
		bool crop = false;

		if (cols > piece_size) {
			piece_x_num = cols / piece_size;
			piece_x_res = cols % piece_size;
			crop = true;
		}

		if (rows > piece_size) {
			piece_y_num = cols / piece_size;
			piece_y_res = cols % piece_size;
			crop = true;
		}

		if (crop) cropImage( piece_x_num, piece_x_res, piece_y_num, piece_y_res );
	}
}

void HeightMap::SetUAVPos( float latitude, float longitude ) {
	// loading corresponding map piece
	int pixel_x = round( (latitude - zero_latitude) / pixel_x_step);
	int pixel_y = round( (longitude - zero_longitude) / pixel_y_step );

	piece_index_i = pixel_x / piece_size;
	piece_index_j = pixel_y / piece_size;
	std::string piece_filename =
		filename.substr( 0, filename.find_last_of( "." ) )			// Original filename without extension
		+ "_" + std::to_string(piece_index_i) + "_" + std::to_string(piece_index_j) +		// indexes of pieces
		filename.substr( filename.find_last_of( "." ) );			// extension of original file
	current_map = cv::imread( piece_filename );
}

float HeightMap::getHeight( float latitude, float longitude ) {
	if (!current_map.empty()) {
		// converting to global pixel coordinates
		int pixel_x = round( (latitude - zero_latitude) / pixel_x_step );
		int pixel_y = round( (longitude - zero_longitude) / pixel_y_step );

		// calculating piece indexes
		int i = pixel_x / piece_size;
		int j = pixel_y / piece_size;

		// check if global pixel coordinates are within loaded piece
		if (i == piece_index_i && j == piece_index_j) {
			// calculating height with local pixel coordinates
			uchar& pixel = current_map.at<uchar>( pixel_x % piece_size , pixel_y % piece_size );
			return height_step * pixel;
		}
		else {
			SetUAVPos( latitude, longitude );
			// calculating height
			uchar& pixel = current_map.at<uchar>( pixel_x % piece_size, pixel_y % piece_size );
			return height_step * pixel;
		}
	}
	else return -1;
}

void HeightMap::cropImage( int cols_num, int cols_res, int rows_num, int rows_res ) {
	cv::Rect rect(0, 0, piece_size, piece_size );
	cv::Rect residual_x(piece_size * cols_num, 0, cols_res, piece_size * rows_num);
	cv::Rect residual_y( 0, piece_size * rows_num, current_map.cols, rows_res );
	
	cv::Mat cropped_map = current_map( rect );
	std::string path_to_save = filename.substr( 0, filename.find_last_of( "." ) );
	std::string extension = filename.substr( filename.find_last_of( "." ) );

	for (int i = 0; i < cols_num; i++) {
		for (int j = 0; j < rows_num; j++) {
			rect.x = i * piece_size;
			rect.y = j * piece_size;

			cropped_map = current_map( rect );

			//save image to disk:
			if (!cropped_map.empty()) {
				cv::imwrite( path_to_save + "_" + std::to_string(i) + "_" + std::to_string(j) + extension, cropped_map);
			}
		}
	}

	cropped_map = current_map( residual_x );
	// save image to disk
	if (!cropped_map.empty()) {
		cv::imwrite( path_to_save + "_" + std::to_string( cols_num ) + "_" + std::to_string( 0 ) + extension, cropped_map );
	}
	cropped_map = current_map( residual_y );
	// save image to disk
	if (!cropped_map.empty()) {
		cv::imwrite( path_to_save + "_" + std::to_string( 0 ) + "_" + std::to_string( rows_num ) + extension, cropped_map );
	}
}

void HeightMap::showMap()
{
	if (!current_map.empty()) {
		cv::imshow( "Current Map", current_map );
		cv::moveWindow( "Current Map", 100, 100 );
		cv::waitKey( 0 );
	}
}

void HeightMap::getImageDepth() {
	if (!current_map.empty()) {
		switch (current_map.depth()) {
			case CV_8U: // 8 bit unsigned
				std::cout << "Depth: 8" << std::endl;
				break;
			case CV_16U: // 16 bit unsigned
				std::cout << "Depth: 16" << std::endl;
				break;
			case CV_32F: // float
				std::cout << "Depth: 32" << std::endl;
				break;
			case CV_64F: // double
				std::cout << "Depth: 64" << std::endl;
				break;
			default:
				break;
		}
	}
}

/*class HeightMap
{
	int piece_size;
	float zero_latitude; // zero x pixel
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
	// convert latitude and longitude to pixel coordinate
	// check if pixel coordinates are within loaded piece and return height
	// if no return nan but this case is unusual and rare. our aim is to neglect one
};
*/