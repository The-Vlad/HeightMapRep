#include "Aircraft.h"

Aircraft::Aircraft( std::string name, float latitude, float longitude, float altitude,
	float x_velocity, float y_velocity )
	: name( name ),
	latitude( latitude ),
	longitude( longitude ),
	altitude( altitude ),
	x_velocity( x_velocity ),
	y_velocity( y_velocity )
{
	char answer;
	while (true) {
		std::cout << "Загрузить файл \"Resources/8k_map/Heightmap.png\"? (y/n): ";
		std::cin >> answer;
		if (answer == 'y') {
			heightmap_path = "Resources/8k_map/Heightmap.png";
			break;
		}
		else if (answer == 'n') {
			std::cout << "Введите путь до файла: ";
			std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
			std::getline( std::cin, heightmap_path );
			break;
		}
		else {
			std::cout << "Ошибка ввода.\n";
		}
	}

	bool is_new;
	while (true) {
		std::cout << "Разбить изображение на фрагменты если это не сделано? (y/n): ";
		std::cin >> answer;
		if (answer == 'y') {
			is_new = true;
			break;
		}
		else if (answer == 'n') {
			is_new = false;
			break;
		}
		else {
			std::cout << "Ошибка ввода.\n";
		}
	}
	
	hmap = new HeightMap( heightmap_path, is_new, -40645, 40645 );
	hmap->SetUAVPos( latitude, longitude );

	control_panel.altitude = altitude;
	control_panel.x_velocity = x_velocity;
	control_panel.y_velocity = y_velocity;
}

void Aircraft::setPosition( float latitude, float longitude ) {
	this->latitude = latitude;
	this->longitude = longitude;
	hmap->SetUAVPos( latitude, longitude );
}

void Aircraft::setVelocity( float x_velocity, float y_velocity ) {
	this->x_velocity = x_velocity;
	this->y_velocity = y_velocity;
}

void Aircraft::setAltitude( float altitude ) {
	this->altitude = altitude;
}

void Aircraft::startEngine() {
	cv::namedWindow( "Trackbars", cv::WINDOW_NORMAL);
	cv::createTrackbar( "X Velocity (m/s)", "Trackbars", &control_panel.x_velocity, x_velocity);
	cv::createTrackbar( "Y Velocity (m/s)", "Trackbars", &control_panel.y_velocity, y_velocity);
	cv::createTrackbar( "Altitude (m)", "Trackbars", &control_panel.altitude, altitude);

	cv::setTrackbarMax( "X Velocity (m/s)", "Trackbars", 900 );
	cv::setTrackbarMin( "X Velocity (m/s)", "Trackbars", -900 );
	cv::setTrackbarMax( "Y Velocity (m/s)", "Trackbars", 900 );
	cv::setTrackbarMin( "Y Velocity (m/s)", "Trackbars", -900 );
	cv::setTrackbarMax( "Altitude (m)", "Trackbars", 12000 );
	cv::setTrackbarMin( "Altitude (m)", "Trackbars", 0 );

	while (true) {
		hmap->showMap( latitude, longitude );

		cv::Mat bg( 1000, 1000, CV_8UC3, cv::Scalar( 125, 125, 125 ) );
		cv::putText( bg, "Latitude: " + std::to_string( latitude ), cv::Point( 10, 50 ), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar( 0, 0, 0 ) );
		cv::putText( bg, "Longitude: " + std::to_string( longitude ), cv::Point( 10, 80 ), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar( 0, 0, 0 ) );
		cv::putText( bg, "Altitude: " + std::to_string( altitude ) + " meters", cv::Point( 10, 110 ), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar( 0, 0, 0 ) );
		cv::putText( bg, "Height map: " + std::to_string( surface_height ) + " meters", cv::Point( 10, 140 ), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar( 0, 0, 0 ) );
		cv::putText( bg, "Distance to surface: " + std::to_string( distance_to_surface ) + " meters", cv::Point( 10, 170 ), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar( 0, 0, 0 ) );
		cv::putText( bg, "Piece file name: " + hmap->getPieceName(), cv::Point( 10, 200 ), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar( 0, 0, 0 ) );
		cv::imshow( "Trackbars", bg );
	}
}

void Aircraft::fly() {		
	auto t1 = std::chrono::steady_clock::now();
	auto t2 = std::chrono::steady_clock::now();
	std::chrono::duration<float> time_diff;
		
	while(true) {
		//std::this_thread::sleep_for( std::chrono::milliseconds( delay_ms ) );

		//aircraft_mtx.lock();
		altitude = (float) control_panel.altitude;
		x_velocity = (float) control_panel.x_velocity;
		y_velocity = (float) control_panel.y_velocity;

		t2 = std::chrono::steady_clock::now();
		time_diff = t2 - t1;
		latitude += x_velocity * time_diff.count();
		longitude += y_velocity * time_diff.count();
		t1 = std::chrono::steady_clock::now();
		distance_to_surface = altitude - surface_height;
		//aircraft_mtx.unlock();

		hmap->SetUAVPos( latitude, longitude );

		//std::cout << "\n####################" << std::endl;
		//std::cout << "Latitude: " << latitude << std::endl;
		//std::cout << "Longitude: " << longitude << std::endl;
		//std::cout << "Altitude: " << altitude << " meters" << std::endl;
		//std::cout << "Heigh of map at current coordinates: " << surface_height << " meters" << std::endl;
		//std::cout << "Distance to surface: " << distance_to_surface << " meters" << std::endl;
	}
}

void Aircraft::getInfo() {
	while (true) {
		//std::this_thread::sleep_for( std::chrono::milliseconds( delay_ms ) );
		//aircraft_mtx.lock();
		surface_height = hmap->getHeight( latitude, longitude );
		//aircraft_mtx.unlock();
	}
}

//uint64_t Aircraft::current_timestamp() {
//	/*
//	auto t1 = std::chrono::steady_clock::now();
//	auto t2 = std::chrono::steady_clock::now();
//	std::chrono::duration<float, std::milli> time_diff = t2 - t1;
//	*/
// 
//	return std::chrono::duration_cast<std::chrono::milliseconds>(
//		std::chrono::steady_clock::now().time_since_epoch()
//	).count();
//}