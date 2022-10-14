#include "HeightMap.h"

int main() {
	std::string path = "Resources/test.png";
	cv::Mat img = cv::imread( path );
	cv::imshow( "HeightMap", img );
	cv::waitKey( 0 );

	return 0;
}