/****************************************************************************
 *  backend.cpp
 *
 *  Copyright (c) 2010 by Sidorov Aleksey <sauron@citadelspb.com>
 *
 ***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*****************************************************************************/

#include "backend.h"
#include "popup.h"
#include "manager.h"
#include <QVariant>
#include <QTime>

namespace QmlPopups
{

	Backend::Backend ()
	{
	}

	void Backend::show(qutim_sdk_0_2::NotificationType type, qutim_sdk_0_2::TreeModelItem item, const QString& body,
					   const QString& customTitle)
	{
		Manager *manager =  Manager::self();
                //чтой-то я не въехал в QFlags. В общем сделаем лучше так:
                int typemask = 0;
                switch(type)
                {
                case qutim_sdk_0_2::NotifyMessageGet:
                    typemask = QmlPopups::NotifyMessageGet;
                    break;
                case qutim_sdk_0_2::NotifyOffline:
                    typemask = QmlPopups::NotifyOffline;
                    break;
                case qutim_sdk_0_2::NotifyOnline:
                    typemask = QmlPopups::NotifyOnline;
                    break;
                case qutim_sdk_0_2::NotifyTyping:
                    typemask = QmlPopups::NotifyTyping;
                    break;
                case qutim_sdk_0_2::NotifyStatusChange:
                    typemask = QmlPopups::NotifyStatusChange;
                    break;
                default:
                    typemask = 0xfffffff;
                    break;
                }

 		if (!(manager->showFlags & typemask) || (manager->count() >= manager->maxCount)) {
			return;
		}
		static int id_counter = 0;
		QString text = body;
		QString sender_id = item.m_item_name;//хз что тут писать...
		QString sender_name = item.m_item_name;
		if(sender_name.isEmpty())
			sender_name = sender_id;
		QString title = customTitle;
		QString popup_id = title;

		bool updateMode = manager->updateMode;
		bool appendMode = manager->appendMode;

		Popup *popup = manager->getById(popup_id);
		if (popup)
		{
			if (appendMode) {
				updateMode ? popup->updateMessage(text) : popup->appendMessage(text);
				return;
			}
			else if (!item.m_item_name.isEmpty()) {
				popup_id.append("." + QString::number(id_counter++));
			}
		}
		popup  = new Popup (popup_id);
		popup->setMessage(title,text,item);
		popup->send();
	}

}
