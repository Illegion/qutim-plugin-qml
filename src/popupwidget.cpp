#include "popupwidget.h"
#include <QGridLayout>
#include <QUrl>
#include <QtDeclarative/qdeclarativecontext.h>
#include <QVariant>
#include <QLatin1Literal>
#include <qutim/layerscity.h>
#include <qutim/settings.h>
#include <QMouseEvent>
#include "qtdwm/qtdwm.h"
#include "manager.h"

#include <QSettings>

using namespace qutim_sdk_0_2;

namespace QmlPopups {

	PopupWidget::PopupWidget()
	{
	    QSettings *settings = QmlPopups::Manager::getSettingsPtr();
            Qt::WindowFlags widgetFlags = Qt::ToolTip;
            PopupWidgetFlags popupFlags = Transparent;
#ifdef Q_WS_WIN
	    QString themePath = settings->value("theme_path","%APPDATA%\\qutim\\qmlpopups\\default\\").toString();
            if(!settings->value("ignore_settings_json",false).toBool())
#else
	    QString themePath = settings->value("theme_path","~/.config/qutim/qmlpopups/default/").toString();
	    if(!settings->value("ignore_settings_json",true).toBool())
#endif
                    loadJsonSettings(themePath + "/settings.json",widgetFlags,popupFlags);
            setWindowFlags(widgetFlags);

	    connect(this,SIGNAL(sceneResized(QSize)),this,SLOT(onSceneResized(QSize)));
	    //view->setContentResizable(true);
	    setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
	    setAttribute(Qt::WA_DeleteOnClose);

		if (popupFlags & Transparent) {
			setAttribute(Qt::WA_NoSystemBackground);
			setAttribute(Qt::WA_TranslucentBackground);
			viewport()->setAutoFillBackground(false);
		}

		if (popupFlags & AeroBackground) {
                if (QtDWM::isCompositionEnabled()) {
                    QtDWM::extendFrameIntoClientArea(this);
				setContentsMargins(0, 0, 0, 0);
			}
		}

		if (popupFlags & AeroBlurBehind) {
                if (QtDWM::isCompositionEnabled())
                    QtDWM::enableBlurBehindWindow(this,true);
		}

		QString filename =themePath % QLatin1Literal("/main.qml");
		setSource(QUrl::fromLocalFile(filename));

		show();
		rootContext()->setContextProperty("popupWidget",this);

	}
	
	void PopupWidget::loadJsonSettings(QString filename, Qt::WindowFlags &wf, PopupWidgetFlags &pf)
	{
	    wf = Qt::ToolTip;
	    pf = Transparent;
	    QFile f;
	    f.setFileName(filename);
	    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	    int len = f.size();
	    QByteArray array;
	    const uchar *fmap = f.map(0, f.size());
	    if(!fmap)
	    {
		array = f.readAll();
		fmap = (uchar *)array.constData();
	    }
	    const uchar *s = K8JSON::skipBlanks(fmap, &len);
	    QVariant variant;
	    K8JSON::parseValue(variant, s, &len);
	    if(variant.toMap().keys().contains("appearance"))
	    {
		pf = static_cast<PopupWidgetFlags>(variant.toMap().value("appearance").toMap().value("popupFlags",Transparent).toInt());
		wf = static_cast<Qt::WindowFlags>(variant.toMap().value("appearance").toMap().value("widgetFlags",Qt::ToolTip).toInt());
	    }
	    f.close();
	}

	void PopupWidget::onSceneResized(QSize size)
	{
		//debug() << "resized:" << size;
		m_size_hint = size;
		emit PopupResized(m_size_hint);
	}


	QSize PopupWidget::sizeHint() const
	{
		return m_size_hint;
	}

	void PopupWidget::setData ( const QString& title, const QString& body, qutim_sdk_0_2::TreeModelItem item )
	{
		m_item = item;
		QDeclarativeContext *context = rootContext();
		context->setContextProperty("popupTitle",title);
		context->setContextProperty("popupBody",body);
                
                PluginSystemInterface *ps = SystemsCity::PluginSystem();
                QStringList contact_info;
                QStringList account_info;
                TreeModelItem account_item = item;
                account_item.m_item_name = item.m_account_name;
                QString contact_avatar;
                QString account_avatar;
                //if( type != NotifySystem )
                {
                    contact_info = ps->getAdditionalInfoAboutContact(item);
                    account_info = ps->getAdditionalInfoAboutContact(account_item);
                    if ( contact_info.count() > 1 )
                    {
                        contact_avatar = contact_info.at(1);
                    }
                    if ( account_info.count() > 1 )
                    {
                        account_avatar = account_info.at(1);
                    }
                }
                
                
		QString image_path = contact_avatar;
		context->setContextProperty("popupImage",image_path);
	}
	
	void PopupWidget::onTimeoutReached()
	{
		emit activated();
	}

	void PopupWidget::activate()
	{
            if(!m_item.m_item_name.isEmpty())
                SystemsCity::PluginSystem()->createChat(m_item);
            emit activated();
	}
	
	void PopupWidget::ignore()
	{
		emit activated();
	}


}
