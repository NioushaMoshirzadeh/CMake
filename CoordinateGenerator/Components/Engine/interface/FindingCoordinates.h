#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

namespace TomTom{
namespace cd{
    
    class FindingCoordinates
    {
        public: //methods 
            void MatchingMethods(int, void*, cv::Mat imageSource, cv::Mat imageTemplate);

        public: //variables
            cv::Mat imageSource_display, result;
            int result_cols, result_rows;

        private://variables
            int TM_COEFF_NORMED_matchMethod {5};
            double alpha{0};
            double beta{1};
            int norm_type {32};
            int dtype {-1}; 
            //localizing the best match with minMaxLoc
            double minVal, maxVal;
            cv::Point minLoc,maxLoc,matchLoc;
            //rectangle variables 
            int thickness {2};
            int lineType{8};
            int shift{0};


    };


}//namespace cd 
}//namespace TomTom