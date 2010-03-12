#ifndef WIDGET_H
#define WIDGET_H

#include <QSettings>
#include <qutim/layerinterface.h>
#include <qutim/plugininterface.h>
using namespace qutim_sdk_0_2;
#include <QWidget>
#include <QDir>
#include "backend.h"
#include <QtDeclarative/QmlView>
namespace QmlPopups
{
	enum PopupWidgetFlag
	{
		None = 0x0,
		Preview = 0x1,
		AeroBackground = 0x2,
		Transparent = 0x4,
		AeroBlurBehind = 0x6,
	};
	Q_DECLARE_FLAGS(PopupWidgetFlags,PopupWidgetFlag)

	class PopupWidget : public QmlView
	{
		Q_OBJECT
	public:
		explicit PopupWidget();
		virtual QSize sizeHint() const;
		void setData(const QString& title,const QString& body,qutim_sdk_0_2::TreeModelItem item);
	public slots:
		void onTimeoutReached();
		void activate();
		void ignore();
	signals:
		void PopupResized(const QSize &size);
		void activated();
	private slots:
		void onSceneResized(QSize size);
	private:
		QSize m_size_hint;
                qutim_sdk_0_2::TreeModelItem m_item;
	};
}

#endif // WIDGET_H
