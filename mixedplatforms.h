#ifndef MIXEDPLATFORMS_H
#define MIXEDPLATFORMS_H

#include <string>

class mixedPlatforms
{
public:
    std::string getAppID();
    bool isUIRunning();
    void setLayout(std::string layoutArgs);
    int whatPlatform();
};

#endif // MIXEDPLATFORMS_H
