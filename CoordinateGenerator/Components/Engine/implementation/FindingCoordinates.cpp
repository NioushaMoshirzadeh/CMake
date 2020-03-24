#include "FindingCoordinates.h"

namespace TomTom{
namespace cd {

    void FindingCoordinates::MatchingMethods(int ,void*, cv::Mat imageSource, cv::Mat imageTemplate)
    {
        imageSource.cv::Mat::copyTo(imageSource_display);

        result_cols = imageSource.cv::Mat::cols - imageTemplate.cv::Mat::cols +1;
        result_rows = imageSource.cv::Mat::rows - imageTemplate.cv::Mat::rows +1;
        result.cv::Mat::create(result_rows,result_cols,CV_32FC1);
      
        //do the matching and normalize 
        cv::matchTemplate(imageSource,imageTemplate,result,TM_COEFF_NORMED_matchMethod);
        cv::normalize(result,result,alpha,beta,norm_type, dtype,cv::Mat());
       
        //localizing the best match with minMaxLoc
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
        matchLoc = maxLoc;
       
        //show me what you got 
        cv::rectangle(imageSource_display,matchLoc,cv::Point(maxLoc.x + imageTemplate.cv::Mat::cols, matchLoc.y + imageTemplate.cv::Mat::rows),cv::Scalar::all(0),thickness,lineType,shift);
        cv::rectangle(result,matchLoc,cv::Point(matchLoc.x +imageTemplate.cv::Mat::cols,matchLoc.y+imageTemplate.cv::Mat::rows),cv::Scalar::all(0), thickness,lineType,shift);

        cv::imshow("Source Image",imageSource_display);
        cv::imshow("Result Window",result);
        return;
    }


}//namespace cd 
}//namespace TomTom