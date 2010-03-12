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
#include "libnotifylayer.h"
#include <QSettings>
#include "notificationcore.h"

LibnotifyLayer::LibnotifyLayer()
{
    cutCount = 200;
    settings_widget = 0;
}

LibnotifyLayer::~LibnotifyLayer()
{
}

QList<SettingsStructure> LibnotifyLayer::getLayerSettingsList()
{
    m_settings.clear();
    SettingsStructure settings;
    settings.settings_item = new QTreeWidgetItem();
    settings.settings_item->setText(0, QObject::tr("Notifications"));
    //settings.settings_item->setIcon(0, Icon("events"));
    settings_widget = new QMLSettingsWidget();
    settings.settings_widget = settings_widget;
    m_settings.append(settings);
    return m_settings;
}

bool LibnotifyLayer::init(PluginSystemInterface*)
{
    qml_backend = new QmlPopups::Backend();
    return true;
}

void LibnotifyLayer::setProfileName(const QString& profile_name) {
    QmlPopups::Manager::self()->loadSettings();
    QSettings settings(QSettings::defaultFormat(), QSettings::UserScope, "qutim/qutim."+profile_name, "profilesettings");
    settings.beginGroup("sounds");
    m_enable_sound = settings.value("enable",true).toBool();
    for(int i=0;i<qutim_sdk_0_2::NotifyCount;i++)
    {
        QString file_name = settings.value("event"+QString::number(i), "-").toString();
        m_sound_path.insert(i, (file_name.at(0) == '+') ? file_name.mid(1) : "");
    }
    settings.endGroup();
}

void LibnotifyLayer::saveLayerSettings()
{
    if(settings_widget)
        emit settings_widget->saveSettingsStatic();
}


void LibnotifyLayer::showPopup(const TreeModelItem &item, const QString &message, NotificationType type)
{
    notify(item, message, type);
}

void LibnotifyLayer::playSound(const TreeModelItem &item, NotificationType type)
{
    Q_UNUSED(item);
    QString file_name = m_sound_path.value(type, QString());

    if(!file_name.isEmpty() && m_enable_sound)
        LayersCity::SoundEngine()->playSound(file_name);
}

void LibnotifyLayer::notify(const TreeModelItem &item, const QString &message, NotificationType type)
{
    playSound(item, type); //FIXME temprorary

    QString msg = message;
    QString ttl;
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
    if( type != NotifySystem )
    {
        contact_info = ps->getAdditionalInfoAboutContact(item);
        account_info = ps->getAdditionalInfoAboutContact(account_item);
        if ( contact_info.count() > 0)
        {
            contact_nick = contact_info.at(0);
            if(contact_nick.isEmpty())
                contact_nick = item.m_item_name;
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
        ttl = tr("System message \n");
        break;
    case NotifyMessageGet:
        ttl = tr("%1").arg(contact_nick);
        break;
    case NotifyBlockedMessage:
        msg = tr("Blocked message from\n%1").arg(contact_nick);
        break;
    case NotifyBirthday:
        ttl = contact_nick;
        msg = tr("Contact has birthday today!");
        break;
    case NotifyCustom:
        ttl = contact_nick + "(" + item.m_item_name + ") ";
        break;
    case NotifyTyping:
        ttl = contact_nick;
        msg = tr("is typing...");
        break;
    case NotifyStatusChange:
        ttl = contact_nick;
        msg = tr("Contact changed his status");
        break;
    case NotifyOnline:
        ttl = contact_nick;
        msg = tr("Contact is online");
        break;
    case NotifyOffline:
        ttl = contact_nick;
        msg = tr("Contact is offline");
        break;
    case NotifyStartup:
        ttl = "qutIM";
        msg = tr("Starting up...");
        break;
    //case NotifyCount:
        //break;
    default:
        return;
    }

    qml_backend->show(type,item,msg,ttl);
}

void LibnotifyLayer::setLayerInterface(LayerType type, LayerInterface *layer_interface)
{
    LayersCity::instance().setLayerInterface( type, layer_interface );
}


