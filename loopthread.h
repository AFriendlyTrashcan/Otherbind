#ifndef LOOPTHREAD_H
#define LOOPTHREAD_H

#include <QtCore>

class loopThread : public QThread
{
public:
    explicit loopThread(bool gW, int gLI);
    void run();
    void exec();
};

#endif // LOOPTHREAD_H
