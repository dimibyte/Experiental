/*
 *  This file is part of Experiental.
 *
 *  Experiental is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Experiental is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Experiental.  If not, see <http://www.gnu.org/licenses/>.
 */

///Logging system

#include "system/CLog.h"
#include "system/SDL.h"

#include <stdio.h>
#include <stdarg.h>

typedef unsigned char  BYTE; // 1byte
typedef unsigned short  WORD; // 2bytes
typedef unsigned long  DWORD; //4bytes

CLog::CLog()
{
}

CLog &CLog::get()
{
    static CLog log;
    return log;
}

bool CLog::init()
{
    appLog.open("applog.txt");
    clientLog.open("clientlog.txt");
    serverLog.open("serverlog.txt");
    //user errors get logged to client

    //load the strings file
    if(!loadStrings())
        return false;

    return true;
}

void CLog::write(int target, const char *msg, ...)
{
    va_list args; va_start(args, msg);
    char szBuf[1024];
    vsprintf(szBuf, msg, args);

    if(target&LOG_APP)
    {
        appLog<<szBuf<<"\n";
//#ifdef DEBUG
        appLog.flush();
//#endif
    }
    if(target&LOG_CLIENT)
    {
        clientLog<<szBuf<<"\n";
//#ifdef DEBUG
        clientLog.flush();
//#endif
    }
    if(target&LOG_SERVER)
    {
        serverLog<<szBuf<<"\n";
//#ifdef DEBUG
        serverLog.flush();
//#endif
    }
    if(target&LOG_USER)
    {
/*D #if defined _WIN32 || defined _WIN64
//        MessageBox(NULL, szBuf, "Message", MB_OK);        //can't use it, while there's no #include <windows.h>
#elif defined __linux__
//TODO: just need to make some X11 window with message, or write to console
#elif defined TARGET_OS_MAC
#error User-level logging is not yet implemented for this Macintosh platform.
#else
#error User-level logging is not yet implemented for this platform.
#endif */
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                         "Message",
                         szBuf,
                         NULL);

    }
}

void CLog::write(int target, unsigned long msgID, ...)
{
    va_list args; va_start(args, msgID);
    char szBuf[1024];
    vsprintf(szBuf, logStrings[msgID].c_str(), args);
    write(target, szBuf);
}

#if defined _WIN32 || defined _WIN64
//under WIN32, the strings get read in from a string table resource
bool CLog::loadStrings()
{
    for(unsigned long i = 0; i < MAX_LOG_STRINGS; i++)
    {
        char szBuf[1024];
//W?        if(!loadString(GetModuleHandle("engine"), i, szBuf, 1024))
//W?            break;  //returning 0 means no more strings
        logStrings[i] = szBuf;
    }
    return true;
}

#else
//other platforms load the strings in from strings.txt
bool CLog::loadStrings()
{
    std::ifstream in("strings.txt");
    if(!in.is_open())
        return false;

    DWORD index = 0;

    while(!in.eof())
    {
        char szBuf[1024];
        in.getline(szBuf, 1024);
        logStrings[index++] = szBuf;
    }

    return true;
}

#endif
