#include "OutputHandler.h"

namespace{
    const std::string  KOutputFile {"outputFile.json"};
        
}//namespace



namespace TomTom{
namespace cd{
    
    void COutputHandler::writeOutput(const std::vector<std::string> &templateImages, const std::vector<SCoordinates> &coordinates){
           
      std::fstream fileStream;
      fileStream.open(KOutputFile, std::ios::out | std::ios::ate | std::ios::trunc);

      if (templateImages.size() == 0 || coordinates.size() == 0){
        throw std::runtime_error(std::string("failed to cllect template images or coordinates!"));
      }

      for (unsigned int i = 0; i < templateImages.size(); i++){

        if ( i == 0 ){
           fileStream << " { " ; 
           fileStream << "\t" << " \"" << templateImages[i] << "\": " << " \"" << coordinates[i].x << " , " << coordinates[i].y << "\" " << ", " << "\n";
        }
        else if ( i == templateImages.size() - 1 ){
           fileStream << "\t" << " \"" << templateImages[i] << "\": " << " \"" << coordinates[i].x << " , " << coordinates[i].y << "\" " << "\n";
           fileStream << " } "; 
        }
        else{
           fileStream << "\t" << " \"" << templateImages[i] << "\": " << " \"" << coordinates[i].x << " , " << coordinates[i].y  << "\" " << ", " << "\n";
        }
      } // end for
      
      fileStream.close();
    }


}//namespace cd 
}//namespace TomTom