#pragma once

#include <opencv2/opencv.hpp> 

namespace TomTom {
namespace cd{

	class CInputHandler{

		public:
		    static cv::Mat readImage(const std::string& aFilename); 
	};

}//namespace cd	
}//namespace TomTom
