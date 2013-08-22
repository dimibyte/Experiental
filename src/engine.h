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

#include <system/SDL.h>

//foundation layer headers
#include "system/mmanager.h"
#include "system/CLog.h"
#include "system/functor.h"
#include "system/dator.h"
#include "system/singleton.h"
#include "system/kernel.h"
#include "system/ringBuffer.h"
#include "system/settingsManager.h"

#endif      //_ENGINE_H_
