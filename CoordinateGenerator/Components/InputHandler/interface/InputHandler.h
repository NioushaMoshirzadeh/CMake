#pragma once


#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function

namespace TomTom {
namespace cd {

	class InputHandler
	{

	public:
		cv::Mat readImage( const std::string& filename)const; // a read_only function
		
	};

} // namespace cd	
} // namespace TomTom
