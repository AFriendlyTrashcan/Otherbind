#include "loopthread.h"
#include "mainwindow.h"
#include "mixedplatforms.h"
#include <QDebug>
#include <QtCore>
#include <QThread>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool globalGameWorkaround;
int globalGameLangIndex;
string langComms[100];
bool gameRunning = false;
bool layoutSet = false;
bool gameWorkaround;
int langIndex;
string gameOpenChat[20] = "";
string gameCloseChat[20] = "";
string gameAppID;
loopThread::loopThread(bool gGW, int gGLI){
    globalGameWorkaround = gGW;
    globalGameLangIndex = gGLI;
}

void populateKeys(string commaSeparated, bool inOrOut){
    char keyTemp[100];
    int keyTempIncrement = 0;
    int charIncrement = 0;
    if(commaSeparated.length() == 0){
        for(int i = 0; i < 20; i++){
            gameOpenChat[i] = "";
        }
    }
    for(int i = 0; i < commaSeparated.length(); i++){
        if(commaSeparated[i] != ',' && keyTempIncrement < 100 && commaSeparated[i+1]){
            keyTemp[keyTempIncrement] = commaSeparated[i];
            keyTempIncrement++;
        }else if(charIncrement < 20){
            if(!commaSeparated[i+1]){
                keyTemp[keyTempIncrement] = commaSeparated[i];
                keyTempIncrement++;
            }
            keyTempIncrement = 0;
            if(!inOrOut){
                gameOpenChat[charIncrement] = keyTemp;
            }else{
                gameCloseChat[charIncrement] = keyTemp;
            }
            charIncrement++;
        }
    }
}

void loopThread::run(){
    mixedPlatforms mp;
    int prefLangCount = 0;
    int arrayLangCounts = 0;
    ifstream langStream;
    string langLine;
    langStream.open("../otherbind/languages");
    while(getline(langStream, langLine)){
        if(prefLangCount % 4 == 1){
            langComms[arrayLangCounts] = langLine;
            qDebug() << QString::fromStdString(langComms[arrayLangCounts]);
            arrayLangCounts++;

        }
        prefLangCount++;
    }
    bool configsRead = false;
    while(true){
        sleep(1);
        if(mp.isUIRunning()){
            gameRunning = true;
            gameAppID = mp.getAppID();
            ifstream gameConfigs;
            gameConfigs.open("../otherbind/gameConfigs");
            string readLine;
            bool readingGame = false;
            bool finishLooping = false;
            int postGameLine = 0;
            while(getline(gameConfigs, readLine) && !finishLooping){
                if(postGameLine < 4 && readingGame){
                    switch(postGameLine){
                        case 0:
                            if(readLine != ""){
                                globalGameWorkaround = stoi(readLine);
                            }
                            break;
                        case 1:
                            if(readLine != ""){
                                                                qDebug() << QString::fromStdString(readLine);
                                globalGameLangIndex = stoi(readLine);
                            }
                            break;
                        //Case 2 and 3 deal with an unimplemented function
                        case 2:
                            populateKeys(readLine, false);
                            break;
                        case 3:
                            populateKeys(readLine, true);
                            break;
                        default:
                            //Redundant, just good practice
                            break;
                    }
                    postGameLine++;
                }else if(readingGame){
                    finishLooping = true;
                    readingGame = false;
                }
                if(readLine == gameAppID && !configsRead){
                    readingGame = true;
                    postGameLine = 0;
                }
            }
            finishLooping = false;
            configsRead = true;
        if(gameWorkaround && !layoutSet){
            qDebug() << "us";
            mp.setLayout("us");
            layoutSet = true;
        }
        }else{
            if(layoutSet){
                layoutSet = false;
                qDebug() << QString::fromStdString(langComms[globalGameLangIndex]);
                mp.setLayout(langComms[globalGameLangIndex]);
            }
            /*
        if(gameRunning){
            gameRunning = false;
            configsRead = false;
        }
        if(gameWorkaround && layoutSet){
            layoutSet = false;
            ifstream langRead;
            string langLine;
            bool langSection = false;
            int langCount = 0;
            langRead.open("../otherbind/languages");
            while(getline(langRead, langLine)){
                langCount++;
                if(langCount / 4 == langIndex && langIndex == false){
                        langSection = true;
                        langCount = 0;
                }
                if(langSection == true && langCount == mp.whatPlatform() + 1){
                    mp.setLayout(langLine);
                }
            }
            */

        }
    }
}
