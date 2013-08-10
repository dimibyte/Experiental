#ifndef _CLOG_H_
#define _CLOG_H_

#include <fstream>

const int LOG_APP = 1;
const int LOG_CLIENT = 2;
const int LOG_SERVER = 4;
//LOG_USER is used to display the log message to the user - i.e. in a dialog box
const int LOG_USER = 8;

#define MAX_LOG_STRINGS 256

class CLog
{
protected:
    CLog();

    std::ofstream appLog;
    std::ofstream clientLog;
    std::ofstream serverLog;

    std::string logStrings[MAX_LOG_STRINGS];
    bool loadStrings();

public:
    static CLog &get();

    bool init();

    void write(int target, const char *msg, ...);
    void write(int target, unsigned long msgID, ...);
};

#endif      //_CLOG_H_
