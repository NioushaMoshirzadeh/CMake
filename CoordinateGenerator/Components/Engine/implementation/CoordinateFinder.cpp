#include "CoordinateFinder.h"


namespace TomTom{
namespace cd {
    
    CCoordinateFinder::CCoordinateFinder(const SNormalizeParams &aNormalzieParams, const SRectangleParams &aRectangleParams, const int aMatchMethod):
    TM_COEFF_NORMED_matchMethod{aMatchMethod},
    mMinMaxLocParams{0, 0, {0,0}, {0,0}},
    mNormalizeParams{aNormalzieParams},
    mRectangleParams{aRectangleParams}
    {}
    
    SCoordinates CCoordinateFinder::findCoordinates(const cv::Mat aImageSource, const cv::Mat aImageTemplate){
        
        cv::Mat      result;

        result.cv::Mat::create((aImageSource.cv::Mat::cols - aImageTemplate.cv::Mat::cols + 1), (aImageSource.cv::Mat::rows - aImageTemplate.cv::Mat::rows + 1), CV_32FC1); //CV_32FC1 is a Data Type, means a 2-channel floating-point array 

        if (result.cv::Mat::cols < 0 || result.cv::Mat::rows < 0){
           
           throw std::runtime_error(std::string("failed to create the matching result for each template location!"));
        }
      
        //do the matching and normalize 
        cv::matchTemplate(aImageSource, aImageTemplate, result, TM_COEFF_NORMED_matchMethod);
        cv::normalize(result, result, mNormalizeParams.alpha, mNormalizeParams.beta, mNormalizeParams.norm_type, mNormalizeParams.dtype, cv::Mat());
       
        //localizing the best match with minMaxLoc
        cv::minMaxLoc(result, &mMinMaxLocParams.minVal, &mMinMaxLocParams.maxVal, &mMinMaxLocParams.minLoc, &mMinMaxLocParams.maxLoc, cv::Mat());
        
        SCoordinates templateCoordinates;
        templateCoordinates.x = mMinMaxLocParams.maxLoc.x + aImageTemplate.cv::Mat::cols / 2;
        templateCoordinates.y = mMinMaxLocParams.maxLoc.y + aImageTemplate.cv::Mat::rows / 2;

        //draw a rectangle around the template found 
        cv::rectangle(aImageSource, mMinMaxLocParams.maxLoc, cv::Point(mMinMaxLocParams.maxLoc.x + aImageTemplate.cv::Mat::cols / 2, mMinMaxLocParams.maxLoc.y + aImageTemplate.cv::Mat::rows / 2), cv::Scalar::all(0), mRectangleParams.thickness, mRectangleParams.lineType, mRectangleParams.shift);
        cv::rectangle(result, mMinMaxLocParams.maxLoc, cv::Point(mMinMaxLocParams.maxLoc.x + aImageTemplate.cv::Mat::cols / 2, mMinMaxLocParams.maxLoc.y + aImageTemplate.cv::Mat::rows / 2), cv::Scalar::all(0), mRectangleParams.thickness, mRectangleParams.lineType, mRectangleParams.shift);

        cv::imshow("Source Image", aImageSource);
        cv::imshow("Result Window", result);
        return templateCoordinates;
    }


}//namespace cd 
}//namespace TomTom