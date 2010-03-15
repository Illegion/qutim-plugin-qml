/*

    Copyright (c) 2010 by Stanislav (proDOOMman) Kosolapov <prodoomman@shell.tor.hu>

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************
*/

#include "qmlsettingswidget.h"

QMLSettingsWidget::QMLSettingsWidget(QWidget *parent) :
    QWidget(parent){
    this->blockSignals(true);
    counter = 666;
    emit setCurveTypes();
    settings_static = new QSettings(QSettings::defaultFormat(),
                                      QSettings::UserScope, "qutim/"+SystemsCity::PluginSystem()->getProfileDir().dirName(), "qml_popups");
    settings_temp = new QSettings(QSettings::defaultFormat(),
                                      QSettings::UserScope, "qutim/"+SystemsCity::PluginSystem()->getProfileDir().dirName(), "qml_popups_temp");
    settings = settings_static;
    setupUi(this);    
    QString nameFilter("main.qml");
    QStringList pathlist = SystemsCity::PluginSystem()->getSharePaths();
    foreach(QString dir_name, pathlist)
        foreach(QString name, QDir(dir_name+QDir::separator()+"qmlpopups").entryList(QDir::Dirs))
    {
        QDir d(QDir(dir_name+QDir::separator()+"qmlpopups").absoluteFilePath(name));
        if(d.exists(nameFilter))
        {
            themesList->addItem(name);
            themesList->setItemData(themesList->count()-1,d.absolutePath());
        }
    }
    QMapIterator<QEasingCurve::Type, QString> i(curve_types);
    while (i.hasNext()) {
        i.next();
        easingCurveComboBox->addItem(i.value(),i.key());
    }
    loadSettings();
    connect(previewButton,SIGNAL(released()),this,SLOT(preview()));
    connect(themesList,SIGNAL(currentIndexChanged(int)),this,SLOT(widgetStateChanged()));
    connect(themesList,SIGNAL(currentIndexChanged(int)),this,SLOT(preview()));
    connect(updatePositionBox,SIGNAL(toggled(bool)),this,SLOT(widgetStateChanged()));
    connect(appendModeCheckBox,SIGNAL(toggled(bool)),this,SLOT(widgetStateChanged()));
    connect(updateModeCheckBox,SIGNAL(toggled(bool)),this,SLOT(widgetStateChanged()));
    connect(easingCurveComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(widgetStateChanged()));
    connect(animationCheckBox,SIGNAL(currentIndexChanged(int)),this,SLOT(widgetStateChanged()));
    connect(animationDurationSpinBox,SIGNAL(valueChanged(int)),this,SLOT(widgetStateChanged()));
    connect(timeoutSpinBox,SIGNAL(valueChanged(int)),this,SLOT(widgetStateChanged()));
    connect(maxCountSpinBox,SIGNAL(valueChanged(int)),this,SLOT(widgetStateChanged()));
    connect(maxTextLengthSpinBox,SIGNAL(valueChanged(int)),this,SLOT(widgetStateChanged()));
    connect(contactChangedStatusCheckBox,SIGNAL(stateChanged(int)),this,SLOT(widgetStateChanged()));
    connect(contactIsTypingCheckBox,SIGNAL(stateChanged(int)),this,SLOT(widgetStateChanged()));;
    connect(contactOfflineCheckBox,SIGNAL(stateChanged(int)),this,SLOT(widgetStateChanged()));
    connect(contactOnlineCheckBox,SIGNAL(stateChanged(int)),this,SLOT(widgetStateChanged()));
    connect(messageRecivedCheckBox,SIGNAL(stateChanged(int)),this,SLOT(widgetStateChanged()));
    this->blockSignals(false);
}

void QMLSettingsWidget::setCurveTypes()
{
    curve_types[QEasingCurve::Linear] = tr("Linear");
    curve_types[QEasingCurve::InElastic] = tr("InElastic");
    curve_types[QEasingCurve::OutElastic] = tr("OutElastic");
    curve_types[QEasingCurve::InOutElastic] = tr("InOutElastic");
    curve_types[QEasingCurve::OutInElastic] = tr("OutInElastic");
    curve_types[QEasingCurve::InQuad] = tr("InQuad");
    curve_types[QEasingCurve::OutQuad] = tr("OutQuad");
    curve_types[QEasingCurve::InOutQuad] = tr("InOutQuad");
    curve_types[QEasingCurve::OutInQuad] = tr("OutInQuad");
    curve_types[QEasingCurve::OutSine] = tr("OutSine");
    curve_types[QEasingCurve::InCubic] = tr("InCubic");
    curve_types[QEasingCurve::OutCubic] = tr("OutCubic");
    curve_types[QEasingCurve::OutInCubic] = tr("OutInCubic");
    curve_types[QEasingCurve::InOutCubic] = tr("InOutCubic");
    curve_types[QEasingCurve::InQuart] = tr("InQuart");
    curve_types[QEasingCurve::OutQuart] = tr("OutQuart");
    curve_types[QEasingCurve::InOutQuart] = tr("InOutQuart");
    curve_types[QEasingCurve::OutInQuart] = tr("OutInQuart");
    curve_types[QEasingCurve::InQuint] = tr("InQuint");
    curve_types[QEasingCurve::OutQuint] = tr("OutQuint");
    curve_types[QEasingCurve::InOutQuint] = tr("InOutQuint");
    curve_types[QEasingCurve::OutInQuint] = tr("OutInQuint");
    curve_types[QEasingCurve::InSine] = tr("InSine");
    curve_types[QEasingCurve::OutSine] = tr("OutSine");
    curve_types[QEasingCurve::InOutSine] = tr("InOutSine");
    curve_types[QEasingCurve::OutInSine] = tr("OutInSine");
    curve_types[QEasingCurve::InExpo] = tr("InExpo");
    curve_types[QEasingCurve::OutExpo] = tr("OutExpo");
    curve_types[QEasingCurve::InOutExpo] = tr("InOutExpo");
    curve_types[QEasingCurve::OutInExpo] = tr("OutInExpo");
    curve_types[QEasingCurve::InCirc] = tr("InCirc");
    curve_types[QEasingCurve::OutCirc] = tr("OutCirc");
    curve_types[QEasingCurve::InOutCirc] = tr("InOutCirc");
    curve_types[QEasingCurve::OutInCirc] = tr("OutInCirc");
    curve_types[QEasingCurve::InBack] = tr("InBack");
    curve_types[QEasingCurve::OutBack] = tr("OutBack");
    curve_types[QEasingCurve::InOutBack] = tr("InOutBack");
    curve_types[QEasingCurve::OutInBack] = tr("OutInBack");
    curve_types[QEasingCurve::InBounce] = tr("InBounce");
    curve_types[QEasingCurve::OutBounce] = tr("OutBounce");
    curve_types[QEasingCurve::InOutBounce] = tr("InOutBounce");
    curve_types[QEasingCurve::OutInBounce] = tr("OutInBounce");
    curve_types[QEasingCurve::InCurve] = tr("InCurve");
    curve_types[QEasingCurve::OutCurve] = tr("OutCurve");
    curve_types[QEasingCurve::SineCurve] = tr("SineCurve");
    curve_types[QEasingCurve::CosineCurve] = tr("CosineCurve");
}

void QMLSettingsWidget::loadSettings()
{
    updatePositionBox->setChecked(settings_static->value("updatePosition",true).toBool());
    animationCheckBox->setCurrentIndex(settings_static->value("animationFlags",2).toInt());
    timeoutSpinBox->setValue(settings_static->value("timeout",5000).toInt());
    easingCurveComboBox->setCurrentIndex(easingCurveComboBox->findData(settings_static->value("easingCurve",QEasingCurve::OutSine).toInt()));
    maxCountSpinBox->setValue(settings_static->value("maxCount",10).toInt());
    maxTextLengthSpinBox->setValue(settings_static->value("maxTextLength",160).toInt());
    appendModeCheckBox->setChecked(settings_static->value("appendMode",true).toBool());
    updateModeCheckBox->setChecked(settings_static->value("updateMode",false).toBool());
    animationDurationSpinBox->setValue(settings_static->value("animationDuration",1000).toInt());
    contactChangedStatusCheckBox->setChecked(settings_static->value("contactChangedStatus",false).toBool());
    contactIsTypingCheckBox->setChecked(settings_static->value("contactIsTyping",false).toBool());
    contactOfflineCheckBox->setChecked(settings_static->value("contactOffline",false).toBool());
    contactOnlineCheckBox->setChecked(settings_static->value("contactOnline",false).toBool());
    messageRecivedCheckBox->setChecked(settings_static->value("messageRecived",true).toBool());
    marginSpinBox->setValue(settings_static->value("margin",20).toInt());
    themesList->setCurrentIndex(themesList->findData(settings_static->value("theme_path").toString()));
}

void QMLSettingsWidget::saveSettings()
{
    settings->setValue("theme_path",themesList->itemData(themesList->currentIndex()).toString());
    settings->setValue("updatePosition",updatePositionBox->isChecked());
    settings->setValue("animationFlags",animationCheckBox->currentIndex());
    settings->setValue("timeout",timeoutSpinBox->value());
    settings->setValue("maxCount",maxCountSpinBox->value());
    settings->setValue("maxTextLength",maxTextLengthSpinBox->value());
    settings->setValue("appendMode",appendModeCheckBox->isChecked());
    settings->setValue("updateMode",updateModeCheckBox->isChecked());
    settings->setValue("animationDuration",animationDurationSpinBox->value());
    settings->setValue("margin",marginSpinBox->value());
    settings->setValue("easingCurve",easingCurveComboBox->itemData(easingCurveComboBox->currentIndex()));
    settings->setValue("contactChangedStatus",contactChangedStatusCheckBox->isChecked());
    settings->setValue("contactIsTyping",contactIsTypingCheckBox->isChecked());
    settings->setValue("contactOffline",contactOfflineCheckBox->isChecked());
    settings->setValue("contactOnline",contactOnlineCheckBox->isChecked());
    settings->sync();
    QmlPopups::Manager::self()->loadSettings();
}

void QMLSettingsWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void QMLSettingsWidget::preview()
{
    settings = settings_temp;
    settings_static->setValue("use_temp",true);
    settings_static->sync();
    saveSettings();
    qutim_sdk_0_2::TreeModelItem item;
    item.m_account_name = tr("Test");
    for(int i = 0; i<4; i++)
    {
        QmlPopups::Popup *popup = new QmlPopups::Popup(QString::number(counter++));
        popup->setMessage(tr("Preview"),tr("This is a simple popup ")+QString::number(i));
        popup->send();
    }
    settings_static->setValue("use_temp",false);
    settings_static->sync();
    settings = settings_static;
}
