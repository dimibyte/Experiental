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

#ifndef _SYSTEM_SETTINGSMANAGER_H_
#define _SYSTEM_SETTINGSMANAGER_H_

#include <string>
#include <map>

#include "system/singleton.h"
#include "system/mmanager.h"
#include "system/dator.h"

class CSettingsManager : public Singleton<CSettingsManager>
{
public:
    CSettingsManager();
    virtual ~CSettingsManager();

    void registerVariable(std::string name, CMMPointer<BaseDator> var);
    void setVariable(std::string &name, std::string &value, int bias = 0);

    void createStandardSettings();
    void destroyStandardSettings();

    void parseSetting(std::string str);
    void parseFile(std::string filename);

protected:
    std::map<std::string, CMMPointer<BaseDator> > settingMap;
};

#endif      //_SYSTEM_SETTINGSMANAGER_H_
