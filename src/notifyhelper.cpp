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

#include "notifyhelper.h"
#include <QDebug>

NotifyHelper::NotifyHelper(const TreeModelItem& tree_model_item) {
	m_contact_item = tree_model_item;
}

void NotifyHelper::registerNotification(KNotification* notification) {
	m_notification = notification;
}


void NotifyHelper::actionFilter(unsigned int index)
{
	switch (index)
	{
		case 1:
			startChatSlot();
			break;
		case 2:
			closeSlot();
			break;
		default:
			return;
			break;
	}
}

void NotifyHelper::startChatSlot()
{
	SystemsCity::PluginSystem()->createChat(m_contact_item);
}
void NotifyHelper::closeSlot() {
	m_notification->close();
	m_notification = 0;
}

