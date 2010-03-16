/*

    Copyright (c) 2010 by Stanislav (proDOOMman) Kosolapov <prodoomman@shell.tor.hu>

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*/

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <qutim/layerscity.h>
#include <QSettings>
#include <QDir>
using namespace qutim_sdk_0_2;

class SettingsManager
{
public:
    enum SettingsType{
        Auto,
        Static,
        Temp
    };
    SettingsManager();
    void init();
    QVariant getValue(QString key, QVariant default_value, SettingsType type = Auto);
    void setValue(QString key, QVariant value, SettingsType = Auto);
    void changeProfile();
    static SettingsManager* getPtr();
private:
    QSettings *m_settings_static;
    QSettings *m_settings_temp;
    QSettings *m_settings;
    static SettingsManager* m_self;
};

#endif // SETTINGSMANAGER_H
