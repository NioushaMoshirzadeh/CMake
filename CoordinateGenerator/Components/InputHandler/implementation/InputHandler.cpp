#include "InputHandler.h"

namespace{ 
    constexpr int KLoadColorImage {1};

}//namespace

namespace TomTom{
namespace cd{

    cv::Mat CInputHandler::readImage(const std::string& aFilename){
        
    return  cv::imread(aFilename, KLoadColorImage);
    }

}//namespace cd  
}//namespace TomTom