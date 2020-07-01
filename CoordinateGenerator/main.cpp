#include "Components/InputHandler/interface/InputHandler.h"
#include "Components/Engine/interface/CoordinateFinder.h"
#include "Components/OutputHandler/interface/OutputHandler.h"
#include "Components/Common/CommonTypes.h"

#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  
    (void)argc;
    const auto sourceImage   = std::string{argv[1]};
    const auto templatePath = std::string{argv[2]};
    std::vector <std::string> templateImages; 
    std::vector <TomTom::cd::SCoordinates> coordinatesVector;

    for (const auto& entry: std::experimental::filesystem::v1::directory_iterator(templatePath)){
        
        templateImages.push_back(entry.path());
    } 

    for (const auto templateImage: templateImages){
        auto inputHandler = TomTom::cd::CInputHandler{};

        cv::Mat imageSource, imageTemplate;
        
        imageSource   = inputHandler.readImage(sourceImage);
        imageTemplate = inputHandler.readImage(templateImage);

        /**********struct SNormalizeParams{alpha, beta, norm_type, dtype}**********
         * chose mean 0.0 as alpha value and norm of 1.0 to give the image consistent 
         * intensity and reduce the effect of different illumination consitions.
         * norm_type is 32, cv::NORM_MINMAX = 32.
         * dtype is negative value to have an array as the same type as the src.
         *************************************************************************/ 
        const TomTom::cd::SNormalizeParams normalizeParams{0.0, 1.0, 32, -1};    

        /**********struct SRectangleParams{thickness, lineType, shift}*************
         * chose positive value to indicate the thickness of lines make up the rectangle. 
         * linetype is 8 to draw 8-connected line for non-antialiased lines with int coordinates.
         * shift indicates number of fractional bits in the point coordinates.
         *************************************************************************/   
        const TomTom::cd::SRectangleParams rectangleparams{2, 8, 0};               
        
        /**the TM_CCOEFF_NORMED (type of the template matching operation)**/
        const int                          MatchMethod    {5};
    
        auto coordinateFinder = TomTom::cd::CCoordinateFinder{normalizeParams, rectangleparams, MatchMethod};
        auto coordinates = coordinateFinder.findCoordinates(imageSource, imageTemplate);

        coordinatesVector.push_back(coordinates);
        
    } //end for

    TomTom::cd::COutputHandler::writeOutput(templateImages, coordinatesVector);
    cv::waitKey(0);
    return 0;    
}
