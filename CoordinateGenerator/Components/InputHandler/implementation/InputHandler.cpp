#include "InputHandler.h"

namespace TomTom{
namespace cd {

    cv::Mat InputHandler::readImage(const std::string& filename) const
    {
        
        if(filename == "")
        {
            std::cout <<"your filename is empty!" <<std::endl;
        }

        (void)filename;
        
   

    return  cv::imread(filename,1);
    }

} // namespace cd  
} // namespace TomTom