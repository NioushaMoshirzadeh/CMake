#include "Components/InputHandler/interface/InputHandler.h"
#include "Components/Engine/interface/FindingCoordinates.h"

#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv)
{  
    (void)argc;
    const auto sourceImage = std::string{argv[1]};
    const auto templateImage = std::string{argv[2]};

    auto inputHandler = TomTom::cd::InputHandler{};

    cv::Mat imageSource, imageTemplate;

    imageSource   = inputHandler.readImage(sourceImage);
    imageTemplate = inputHandler.readImage(templateImage);

    
    auto matching = TomTom::cd::FindingCoordinates{};
    matching.MatchingMethods(0,0,imageSource,imageTemplate);

    cv::waitKey(0);
    return 0;    
}
