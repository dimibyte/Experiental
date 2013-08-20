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

    void registerVariable(std::string &name, CMMPointer<BaseDator> &var);
    void setVariable(std::string &name, std::string &value, int bias = 0);

    void createStandardSettings();
    void destroyStandardSettings();

    void parseSetting(std::string str);
    void parseFile(std::string filename);

protected:
    std::map<std::string, CMMPointer<BaseDator> > settingMap;
};

#endif      //_SYSTEM_SETTINGSMANAGER_H_
