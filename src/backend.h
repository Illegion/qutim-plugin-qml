/****************************************************************************
 *  backend.h
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

#ifndef BACKEND_H
#define BACKEND_H

#include <qutim/layerscity.h>

namespace QmlPopups
{
	class Popup;
	class Backend : public QObject
	{
		Q_OBJECT
	public:
            virtual void show(qutim_sdk_0_2::NotificationType type, qutim_sdk_0_2::TreeModelItem item,
						  const QString& body, const QString& customTitle);
		Backend ();
	};

}

#endif //BACKEND_H
