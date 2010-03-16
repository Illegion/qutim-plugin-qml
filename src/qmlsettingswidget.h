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

#ifndef QMLSETTINGSWIDGET_H
#define QMLSETTINGSWIDGET_H

#include "ui_qmlsettingswidget.h"
#include "popup.h"
#include "manager.h"
#include <qutim/settings.h>
#include <QDir>
#include <QDebug>
#include "settingsmanager.h"
#include "manager.h"
using namespace qutim_sdk_0_2;

class QMLSettingsWidget : public QWidget, private Ui::QMLSettingsWidget {
    Q_OBJECT
public:
    QMLSettingsWidget(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
    qint16 counter;
    QMap<QEasingCurve::Type,QString> curve_types;
    SettingsManager *settings_manager;
    SettingsManager::SettingsType stype;
public slots:
    void preview();
    void loadSettings();
    void saveSettings();
    void saveSettingsStatic(){ stype = SettingsManager::Static; saveSettings();}
    void widgetStateChanged(){ emit settingsChanged(); }

private slots:
    void setCurveTypes();
signals:
    void settingsChanged();
};

#endif // QMLSETTINGSWIDGET_H
