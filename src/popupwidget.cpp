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

#include <QSettings>

using namespace qutim_sdk_0_2;

namespace QmlPopups {

	PopupWidget::PopupWidget()
	{
            QString themePath;
            QSettings test_settings(QSettings::defaultFormat(),
                                              QSettings::UserScope, "qutim/"+SystemsCity::PluginSystem()->getProfileDir().dirName(), "qml_popups");
            if(!test_settings.value("use_temp",false).toBool())
            {
                QSettings settings(QSettings::defaultFormat(),
                                              QSettings::UserScope, "qutim/"+SystemsCity::PluginSystem()->getProfileDir().dirName(), "qml_popups");
                themePath = settings.value("theme_path","/usr/share/qutim/qmlpopups/default").toString();
            }
            else
            {
                QSettings settings(QSettings::defaultFormat(),
                                     QSettings::UserScope, "qutim/"+SystemsCity::PluginSystem()->getProfileDir().dirName(), "qml_popups_temp");
                themePath = settings.value("theme_path","/usr/share/qutim/qmlpopups/default").toString();
            }
            //ConfigGroup appearance = Config(themePath + "/settings.json").group("appearance");//хз вообще зачем это...
            setWindowFlags(static_cast<Qt::WindowFlags>(Qt::ToolTip));
            PopupWidgetFlags popupFlags = static_cast<PopupWidgetFlags>(Transparent);

		connect(this,SIGNAL(sceneResized(QSize)),this,SLOT(onSceneResized(QSize)));
		//view->setContentResizable(true);
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

		QString filename =themePath % QLatin1Literal("/main.qml");//м.б. QDir::separator?
		setSource(QUrl::fromLocalFile(filename));//url - main.qml

		show();
		rootContext()->setContextProperty("popupWidget",this);

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
