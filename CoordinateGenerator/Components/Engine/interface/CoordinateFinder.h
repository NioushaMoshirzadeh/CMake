#pragma once

#include "../../Common/CommonTypes.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <iostream>
#include <stdio.h>

namespace TomTom{
namespace cd{

    struct SNormalizeParams{
        double alpha;       // the lower range boundry in case of the range normalization
        double beta;        // upper range boundry in case of the range normalization  
        int    norm_type;   // normalization type which is NORM_L2 
        int    dtype;       // avoid distorting image intensities we assume the image use different dtype range.
                            // when negative,the output array has the same type as src
    };

    struct SRectangleParams{
        int       thickness; // thickness of lines that make yp the rectangle
        int       lineType;  // type of the line: 8-connected line/ 4 connected line/ antialiased line
        int       shift;     // number of fractional bits in the point of the coordinates
    }; 
    
    struct SMinMaxLocParams{
        double    minVal;    // returned minimum value
        double    maxVal;    // returned maximum value
        cv::Point minLoc;    // pointer to returned minimum location
        cv::Point maxLoc;    // pointer to returned maximum location
    };

    class CCoordinateFinder{
        
        public: 
            explicit CCoordinateFinder(const SNormalizeParams &aNormalzieParams, const SRectangleParams &aRectangleParams,const int aMatchMethod);                  
            SCoordinates findCoordinates(const cv::Mat aImageSource, const cv::Mat aImageTemplate);

        private:

            int                    TM_COEFF_NORMED_matchMethod; // one of the six different methods.To specify the way to compare the template with the image
            SMinMaxLocParams       mMinMaxLocParams;

            const SNormalizeParams mNormalizeParams;
            const SRectangleParams mRectangleParams;
  };


}//namespace cd 
}//namespace TomTom