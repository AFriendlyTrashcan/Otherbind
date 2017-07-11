#include "mixedplatforms.h"
#include "mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

bool mixedPlatforms::isUIRunning(){
    string cmd = "pidof -s gameoverlayui";
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                pclose(stream);
    }
    if(data.length() > 0){
        return true;
    }
    return false;
}

void mixedPlatforms::setLayout(string layoutArgs){
    layoutArgs = "setxkbmap -layout " + layoutArgs;
    system(layoutArgs.c_str());
}

int mixedPlatforms::whatPlatform(){
    return 0;
}
