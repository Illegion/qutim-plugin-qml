/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef LIBNOTIFYLAYER_H
#define LIBNOTIFYLAYER_H
#include <qutim/layerinterface.h>
#include <qutim/plugininterface.h>
#include <QVector>
// #include "activenotification.h"
#include "backend.h"
#include "manager.h"
#include "qmlsettingswidget.h"

using namespace qutim_sdk_0_2;

class LibnotifyLayer : public QObject, public NotificationLayerInterface
{
    Q_OBJECT
public:
        LibnotifyLayer ();
        virtual ~LibnotifyLayer ();
	virtual bool init(PluginSystemInterface *plugin_system);	
	virtual void release() {}
	virtual void removeGuiLayerSettings() {}
	virtual void removeLayerSettings() {delete settings_widget;}
        QList<SettingsStructure> getLayerSettingsList();
	virtual void saveGuiSettingsPressed() {}
	virtual void saveLayerSettings();
	virtual void setLayerInterface(LayerType type, LayerInterface* interface);
	virtual void setProfileName(const QString& profile_name);
	virtual void showPopup(const TreeModelItem &item, const QString &message, NotificationType type);
	virtual void playSound(const TreeModelItem &item, NotificationType type);
	virtual void notify(const TreeModelItem &item, const QString &message, NotificationType type);
private:
// 	ActiveNotifications m_activenotifications;
	int cutCount;
	QVector<QString> m_sound_path;
	bool m_enable_sound;
        QmlPopups::Backend *qml_backend;
        QMLSettingsWidget *settings_widget;
};

#endif // LIBNOTIFYLAYER_H
