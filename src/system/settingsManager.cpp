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

#include "system/settingsManager.h"
#include <fstream>

CSettingsManager::CSettingsManager()
{
    settingMap.clear();
    createStandardSettings();
}

CSettingsManager::~CSettingsManager()
{
    destroyStandardSettings();
}

void CSettingsManager::registerVariable(std::string &name, CMMPointer<BaseDator> &var)
{
    settingMap[name] = var;
}

void CSettingsManager::parseFile(std::string filename)
{
    std::ifstream in(filename.c_str());
    if(!in.is_open())
        return;     //couldn't open
    while(!in.eof())
    {
        char szBuf[1024];
        in.getline(szBuf, 1024);
        parseSetting(szBuf);
    }
}

//set up a couple of macros for the StandardSettings mechanism - just convenience
//jobs each macro takes the type of dator, the CMMPointer<> to store it in,
//the variable it's bound to, and the name the manager should use to refer to it.
#define SETTING(type, target, var, name) target = new Dator<type>(var); registerVariable(std::string(name), CMMPointer<BaseDator>(target));
#define LIST(type, target, var, name) target = new ListDator<type>(var); registerVariable(std::string(name), CMMPointer<BaseDator>(target));

void CSettingsManager::createStandardSettings()
{
    //empty for the time being
}

void CSettingsManager::destroyStandardSettings()
{
    //also empty
}

void CSettingsManager::setVariable(std::string &name, std::string &value, int bias)
{
    if(!settingMap[name])
        return;     //setting doesn't exist
    if(settingMap[name]->hasMultipleValues())
    {
        std::list<std::string> valueList;
        valueList.clear();

        //check for semicolon-seperated values
        if(value.find(';'))
        {
            //split the string into semicolon-seperated chunks
            int first = 0, last;
            while((last = value.find(';', first)) != -1)
            {
                valueList.push_back(value.substr(first, last - first));
                first = last + 1;
            }
            valueList.push_back(value.substr(first));
        }
        else
        {
            valueList.push_back(value);
        }

        for(std::list<std::string>::iterator it = valueList.begin(); it != valueList.end(); it++)
        {
            if(bias > 0)
            {
                (*settingMap[name]) += (*it);
            }
            else if(bias < 0)
            {
                (*settingMap[name]) -= (*it);
            }
            else
            {
                (*settingMap[name]) = (*it);
            }
        }
    }
    else
    {
        //just assign the value
        (*settingMap[name]) = value;
    }
}

void CSettingsManager::parseSetting(std::string str)
{
    int bias = 0; std::string name, value;
    //test for bias
    if((str[0] == '+') || (str[0] == '-'))
    {
        bias = ((str[0] == '+') * 2) - 1;   //+ maps to 1*2-1=1, - maps to 0*2-1=-1
        str = str.substr(1);    //remove the first character from the string
    }
    //test for '='
    int eqPos = str.find('=');
    if(eqPos != -1)
    {
        //there's an = sign in there
        //so split either side of it
        name = str.substr(0, eqPos);
        value = str.substr(eqPos + 1);
    }
    else
    {
        //there's no equal sign
        //we use the bias to construct a boolean value
        //so that flags can be +flag (mapping to flag = 1) or -flag (mapping to flag = 0)
        name = str;
        char szBuf[5];
        sprintf(szBuf, "%i", (bias + 1) / 2);
        value = szBuf;
    }
    //set the variable
    setVariable(name, value, bias);
}
