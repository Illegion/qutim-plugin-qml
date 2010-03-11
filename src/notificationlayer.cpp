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

#include "notificationlayer.h"
#include <QDebug>
//#include <libnotifymm.h>

//#include "notifyhelper.h"


LibnotifyLayer::LibnotifyLayer()
{
	cutCount = 200;
}

LibnotifyLayer::~LibnotifyLayer()
{
}

bool LibnotifyLayer::init(PluginSystemInterface*)
{
	return true;
}

void LibnotifyLayer::showPopup(const TreeModelItem &item, const QString &message, NotificationType type)
{
	notify(item, message, type);
}

void LibnotifyLayer::playSound(const TreeModelItem &item, NotificationType type)
{
	notify(item, QString(), type);
}

void LibnotifyLayer::notify(const TreeModelItem &item, const QString &message, NotificationType type)
{
	QString msg;
	//read contact and account info
	PluginSystemInterface *ps = SystemsCity::PluginSystem();
	QStringList contact_info;
	QStringList account_info;
	TreeModelItem account_item = item;
	account_item.m_item_name = item.m_account_name;
	QString contact_nick = item.m_item_name;
	QString contact_avatar;
	QString account_nick = item.m_account_name;
	QString account_avatar;
	QString n_type;
	if( type != NotifySystem )
	{
		contact_info = ps->getAdditionalInfoAboutContact(item);
		account_info = ps->getAdditionalInfoAboutContact(account_item);
		if ( contact_info.count() > 0)
		{
			contact_nick = contact_info.at(0);
		}
		if ( contact_info.count() > 1 )
		{
			contact_avatar = contact_info.at(1);
		}

		if ( account_info.count() > 0)
		{
			account_nick = account_info.at(0);
		}
		if ( account_info.count() > 1 )
		{
			account_avatar = account_info.at(1);
		}
	}
	switch ( type )
	{
	case NotifySystem:
		msg = QObject::tr("System message from %1: <br />").arg(item.m_account_name) + message;
		n_type = "systemMessage";
		break;
	case NotifyStatusChange:
		msg = contact_nick + "<br />" + message;
		n_type = "NotifyStatusChange";
		break;
	case NotifyMessageGet:
		msg = QObject::tr("Message from %1:<br />%2").arg(contact_nick).arg(message);
		n_type = "NotifyMessageGet";
		break;
	case NotifyTyping:
		msg = QObject::tr("%1</b><br /> is typing").arg(contact_nick);
		n_type = "NotifyTyping";
		break;
	case NotifyBlockedMessage:
		msg = QObject::tr("Blocked message from<br /> %1:\n%2").arg(contact_nick).arg(message);
		n_type = "NotifyBlockedMessage";
		break;
	case NotifyBirthday:
		msg = QObject::tr("%1 has birthday today!!").arg(contact_nick);
		n_type = "NotifyBirthday";
		break;
	case NotifyCustom:
		msg = contact_nick + "(" + item.m_item_name + ") " + message;
		n_type = "NotifyCustom";
		break;
	case NotifyOnline:
		msg = contact_nick + "<br />" + message;
		n_type = "NotifyOnline";
		break;
	case NotifyOffline:
		msg = contact_nick + "<br />" + message;
		n_type = "NotifyOffline";
		break;
	case NotifyStartup:
		n_type = "NotifyStartup";
		break;
	case NotifyCount:
		n_type = "NotifyCount";
		break;
	default:
		return;
	}

// 	bool displayNewNotification = true;
// 	ActiveNotifications::iterator notifyIt = m_activenotifications.find(account_nick);
// 	if (notifyIt != m_activenotifications.end())
// 	{
// 		(*notifyIt)->incrementMessages();
// 		displayNewNotification = false;
// 	}
	

}

void LibnotifyLayer::setLayerInterface(LayerType type, LayerInterface *layer_interface)
{
	LayersCity::instance().setLayerInterface( type, layer_interface );
}


