#include "../Components/InputHandler/interface/InputHandler.h"
#include "../Components/Engine/interface/CoordinateFinder.h"
#include "../Components/OutputHandler/interface/OutputHandler.h"
#include "../../Common/CommonTypes.h"

#include <vector>
#include <experimental/filesystem>
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

class CoordinateGeneratorTest : public ::testing::Test{
    public:
       void SetUp() override {}
       void TearDown() override {}     
};

TEST_F(CoordinateGeneratorTest, openSourceImage){   
   std::string filename = "../../Resources/sourceImage.png";
   FILE* fp = fopen(filename.c_str(), "r");
   ASSERT_TRUE(fp != NULL);  // sucess  
   ASSERT_FALSE(fp == NULL); // fail 
}
 
TEST_F(CoordinateGeneratorTest, openTemplateImage){    
   std::string filename = "../../Resources/templates/";
   FILE* fp = fopen(filename.c_str(), "r");
   ASSERT_TRUE(fp != NULL);  // sucess
   ASSERT_FALSE(fp == NULL); // fail
} 

TEST_F(CoordinateGeneratorTest, InputHandlerSourceImage){
   int loadImageInColormode {1};
   TomTom::cd::CInputHandler inputHandler; 
   const std::string& filename = "../../Resources/sourceImage.png";
        
   auto image = cv::imread(filename, loadImageInColormode);
   cv::Mat sourceImage = inputHandler.readImage(filename);

   EXPECT_EQ(sourceImage.cols, image.cols);            // sucess
   EXPECT_EQ(sourceImage.rows, image.rows);            // sucess
   EXPECT_EQ(sourceImage.type(), image.type());        // sucess   
   EXPECT_EQ(sourceImage.channels(), image.channels());// sucess 
   EXPECT_NE(sourceImage.cols, image.rows);            // fail
   EXPECT_NE(sourceImage.rows, image.cols);            // fail
   EXPECT_NE(sourceImage.channels(), 0);               // fail, image channel is 3 
}   

TEST_F(CoordinateGeneratorTest, InputHandlerTemplateImage){
   int loadImageInColormode {1};
   TomTom::cd::CInputHandler inputHandler; 
   const auto templatePath = "../../Resources/templates/";
   for (auto entry: std::experimental::filesystem::v1::directory_iterator(templatePath)){

    auto image = cv::imread(entry.path(), loadImageInColormode);
    cv::Mat templateImage = inputHandler.readImage(entry.path());

    EXPECT_EQ(templateImage.cols, image.cols);             // sucess 
    EXPECT_EQ(templateImage.rows, image.rows);             // sucess
    EXPECT_EQ(templateImage.type(), image.type());         // sucess
    EXPECT_EQ(templateImage.channels(), image.channels()); // sucess
    EXPECT_NE(templateImage.channels(), 0);                // fail image channel is 3   
       
   } 
        
} 
TEST_F(CoordinateGeneratorTest, InputHandler){
   TomTom::cd::CInputHandler inputHandler; 
   EXPECT_NO_THROW(inputHandler.readImage("../../Resources/sourceImage.png")); // succefully pass 
} 
   
TEST_F(CoordinateGeneratorTest, findCoordinates){
   const TomTom::cd::SNormalizeParams normalizeParams{0.0, 1.0, 32, -1};
   const TomTom::cd::SRectangleParams rectangleparams{2, 8, 0};
   const int                          MatchMethod    {5};
   TomTom::cd::CCoordinateFinder coordinateFinder{normalizeParams, rectangleparams, MatchMethod};
   for (const auto& entry: std::experimental::filesystem::v1::directory_iterator("../../Resources/templates")){
    EXPECT_NO_THROW(coordinateFinder.findCoordinates(cv::imread("../../Resources/sourceImage.png", 1), cv::imread(entry.path(), 1)));   // sucessfully pass  
   }//end for 
   EXPECT_ANY_THROW(coordinateFinder.findCoordinates(cv::imread("../../Resources", 1), cv::imread( "../../Resources/library.png", 1))); // fail 
} 

TEST_F(CoordinateGeneratorTest, outputHandler){ 
   auto outputHandler = TomTom::cd::COutputHandler{};
   std::vector <std::string> templateImages; 
   std::vector <TomTom::cd::SCoordinates> coordinatesVector{{831, 426}, {1132, 431}, {526, 430}, {329, 412}, {176, 414}}; 
   for (const auto& entry: std::experimental::filesystem::v1::directory_iterator("../../Resources/templates")){
     templateImages.push_back(entry.path());
   }// end for
   EXPECT_NO_THROW(outputHandler.writeOutput(templateImages, coordinatesVector));  // sucessfully pass 
   templateImages.clear();
   EXPECT_ANY_THROW(outputHandler.writeOutput(templateImages, coordinatesVector)); // fail  
} 

int main(int argc, char** argv){     
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
} 