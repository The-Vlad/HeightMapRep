#include "Aircraft.h"


int main() {
	//std::string path = "Resources/Heightmap.png";
	//cv::Rect rect( 0, 0, 512, 512 );
	//cv::Mat* img = new cv::Mat(cv::imread( path ));
	//cv::Mat cropped_img = (*img)(rect);

	//std::cout << img->size << std::endl;
	//delete img;
	////img->deallocate();

	//std::cout << cropped_img.size << std::endl;
	////cv::resize(img, resized_img, cv::Size(512, 512) );
	//cv::imshow( "HeightMap", cropped_img);

	//cv::waitKey( 0 );

	/*std::string heightmap_path = "Resources/8k_map/Heightmap.png";
	HeightMap hmap( heightmap_path, false, -16, 250, 800, 15.f, 10.f, 10.f );
	hmap.SetUAVPos( 912, 2451 );
	hmap.getHeight(958, 2743);
	hmap.showMap();*/

	/*std::string test_path = "Resources/test.png";
	HeightMap map( test_path, false);
	map.showMap();*/

	Aircraft aircraft("Il-86");
	aircraft.startEngine();

	return 0;
}