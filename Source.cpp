#include "Aircraft.h"
#include <thread>

void f();

int main() {
	std::setlocale( LC_ALL, "rus" );
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


	Aircraft aircraft( "Il-86" );
	/*aircraft.startEngine();
	aircraft.fly();
	aircraft.getInfo();*/
	//std::thread gui_thr( &Aircraft::startEngine, aircraft);	//gui thread
	//std::thread fly_thr( &Aircraft::fly, aircraft);			//fly thread
	//std::thread info_thr( &Aircraft::getInfo, aircraft);	//info thread

	std::thread gui_thr( [&]() {aircraft.startEngine(); } );	//gui thread
	std::thread fly_thr( [&]() {aircraft.fly(); } );			//fly thread
	std::thread info_thr( [&]() {aircraft.getInfo(); } );	//info thread

	gui_thr.join();
	fly_thr.join();
	info_thr.join();

	return 0;
}