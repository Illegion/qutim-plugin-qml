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

#ifndef NOTIFICATIONCORE_H
#define NOTIFICATIONCORE_H
#include <qutim/layerscity.h>
#include "libnotifylayer.h"
#include "qmlsettingswidget.h"
#include <QIcon>
#include <QWidget>

using namespace qutim_sdk_0_2;

class NotificationCore : public QObject, public LayerPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(qutim_sdk_0_2::PluginInterface qutim_sdk_0_2::LayerPluginInterface)
public:
	virtual bool init(PluginSystemInterface* plugin_system);
	
	virtual void release();
	virtual void processEvent(PluginEvent &event);
	virtual void setProfileName(const QString &profileName);
	virtual QString name();
	virtual QString description();
	virtual QString type();
	virtual QIcon *icon();
private:
	QString m_profile_name;
	LibnotifyLayer *m_notification_layer;
};

#endif // NOTIFICATIONCORE_H
