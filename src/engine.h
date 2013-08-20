//ENGINE.H - this file includes all the headers from the engine so far, so that projects using the engine
//	     can just include this file rather than worry about the 30-40 #includes we will eventually have

#ifndef _ENGINE_H_
#define _ENGINE_H_

//disable the warning about symbol names being too long for the debug information (happens a lot with STL)
#pragma warning ( disable : 4786 )

#ifdef WIN32
#include <windows.h>
//#include "resource.h"
#endif

//foundation layer headers
#include "mmanager.h"
#include "CLog.h"
#include "functor.h"
#include "singleton.h"

#endif      //_ENGINE_H_
