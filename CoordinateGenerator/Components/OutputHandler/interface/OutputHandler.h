#pragma once 

#include "../../Common/CommonTypes.h"

#include <fstream>
#include <iostream>

namespace TomTom {
namespace cd {

	class COutputHandler{

		public:
			static void writeOutput(const std::vector<std::string> &templateImages, const std::vector<SCoordinates> &coordinates); 
		

	};

}//namespace cd 
}//namespace TomTom