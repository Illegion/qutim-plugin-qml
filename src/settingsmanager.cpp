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

#include "settingsmanager.h"

SettingsManager *SettingsManager::m_self = 0;

SettingsManager::SettingsManager()
{
    init();
}

void SettingsManager::init()
{
    m_settings_static = new QSettings(QSettings::defaultFormat(),
                            QSettings::UserScope,
                            "qutim/"+SystemsCity::PluginSystem()->getProfileDir().dirName(),
                            "qml_popups");
    m_settings_temp = new QSettings(QSettings::defaultFormat(),
                                    QSettings::UserScope,
                                    "qutim/"+SystemsCity::PluginSystem()->getProfileDir().dirName(),
                                    "qml_popups_temp");
    m_settings = (m_settings_static->value("use_temp").toBool())?m_settings_temp:m_settings_static;
}

SettingsManager* SettingsManager::getPtr()
{
    if(!m_self)
        m_self = new SettingsManager();
    return m_self;
}

QVariant SettingsManager::getValue(QString key, QVariant default_value, SettingsType type)
{
   switch(type)
   {
   case Auto:
       m_settings = (m_settings_static->value("use_temp").toBool())?m_settings_temp:m_settings_static;
   case Static:
       m_settings = m_settings_static;
   case Temp:
       m_settings = m_settings_temp;
   }
   return m_settings->value(key,default_value);
}

void SettingsManager::changeProfile()
{
    if(m_settings_static)
        delete m_settings_static;
    if(m_settings_temp)
        delete m_settings_temp;
}

void SettingsManager::setValue(QString key, QVariant value, SettingsType type)
{
    switch(type)
    {
    case Auto:
        m_settings = (m_settings_static->value("use_temp").toBool())?m_settings_temp:m_settings_static;
    case Static:
        m_settings = m_settings_static;
    case Temp:
        m_settings = m_settings_temp;
    }
    m_settings->setValue(key,value);
}
