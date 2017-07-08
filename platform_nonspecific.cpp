#include "mixedplatforms.h"
#include <string>
#include <fstream>

using namespace std;

string mixedPlatforms::getAppID(){
  ifstream contentLogStream;
  string contentLogRead;
  bool checkNextInput = false;
  bool checkFurtherInput = false;
  string currentID;
  string tempCurrentID;
  contentLogStream.open("../.steam/steam/logs/content_log.txt");
  while(contentLogStream >> contentLogRead){
    if(checkFurtherInput){
      if(contentLogRead == "state"){
        currentID = tempCurrentID;
        checkFurtherInput = false;
      }
    }
    if(checkNextInput){
      tempCurrentID = contentLogRead;
      checkNextInput = false;
      checkFurtherInput = true;
    }
    if(contentLogRead == "App" || contentLogRead == "AppID"){
      checkNextInput = true;
    }
  }
  return currentID;
}
