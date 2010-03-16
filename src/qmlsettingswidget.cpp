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
    stype = SettingsManager::Auto;
    settings_manager = SettingsManager::getPtr();
    counter = 666;
    emit setCurveTypes();
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
    connect(ignoreSettingsJsonCheckBox,SIGNAL(toggled(bool)),this,SLOT(widgetStateChanged()));
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
    updatePositionBox->setChecked(settings_manager->getValue("updatePosition",true,SettingsManager::Static).toBool());
    animationCheckBox->setCurrentIndex(settings_manager->getValue("animationFlags",2,SettingsManager::Static).toInt());
    timeoutSpinBox->setValue(settings_manager->getValue("timeout",5000,SettingsManager::Static).toInt());
    easingCurveComboBox->setCurrentIndex(easingCurveComboBox->findData(settings_manager->getValue("easingCurve",QEasingCurve::OutSine,SettingsManager::Static).toInt()));
    maxCountSpinBox->setValue(settings_manager->getValue("maxCount",10,SettingsManager::Static).toInt());
    maxTextLengthSpinBox->setValue(settings_manager->getValue("maxTextLength",160,SettingsManager::Static).toInt());
    appendModeCheckBox->setChecked(settings_manager->getValue("appendMode",true,SettingsManager::Static).toBool());
    updateModeCheckBox->setChecked(settings_manager->getValue("updateMode",false,SettingsManager::Static).toBool());
    animationDurationSpinBox->setValue(settings_manager->getValue("animationDuration",1000,SettingsManager::Static).toInt());
    contactChangedStatusCheckBox->setChecked(settings_manager->getValue("contactChangedStatus",false,SettingsManager::Static).toBool());
    contactIsTypingCheckBox->setChecked(settings_manager->getValue("contactIsTyping",false,SettingsManager::Static).toBool());
    contactOfflineCheckBox->setChecked(settings_manager->getValue("contactOffline",false,SettingsManager::Static).toBool());
    contactOnlineCheckBox->setChecked(settings_manager->getValue("contactOnline",false,SettingsManager::Static).toBool());
    messageRecivedCheckBox->setChecked(settings_manager->getValue("messageRecived",true,SettingsManager::Static).toBool());
    marginSpinBox->setValue(settings_manager->getValue("margin",20,SettingsManager::Static).toInt());
    themesList->setCurrentIndex(themesList->findData(settings_manager->getValue("theme_path",QString(),SettingsManager::Static).toString()));
#ifdef Q_WS_WIN
    ignoreSettingsJsonCheckBox->setChecked(settings_manager->getValue("ignore_settings_json",false,SettingsManager::Static).toBool());
#else
    ignoreSettingsJsonCheckBox->setChecked(settings_manager->getValue("ignore_settings_json",true,SettingsManager::Static).toBool());
#endif
}

void QMLSettingsWidget::saveSettings()
{
    settings_manager->setValue("theme_path",themesList->itemData(themesList->currentIndex()).toString(),stype);
    settings_manager->setValue("updatePosition",updatePositionBox->isChecked(),stype);
    settings_manager->setValue("animationFlags",animationCheckBox->currentIndex(),stype);
    settings_manager->setValue("timeout",timeoutSpinBox->value(),stype);
    settings_manager->setValue("maxCount",maxCountSpinBox->value(),stype);
    settings_manager->setValue("maxTextLength",maxTextLengthSpinBox->value(),stype);
    settings_manager->setValue("appendMode",appendModeCheckBox->isChecked(),stype);
    settings_manager->setValue("updateMode",updateModeCheckBox->isChecked(),stype);
    settings_manager->setValue("animationDuration",animationDurationSpinBox->value(),stype);
    settings_manager->setValue("margin",marginSpinBox->value(),stype);
    settings_manager->setValue("easingCurve",easingCurveComboBox->itemData(easingCurveComboBox->currentIndex()),stype);
    settings_manager->setValue("contactChangedStatus",contactChangedStatusCheckBox->isChecked(),stype);
    settings_manager->setValue("contactIsTyping",contactIsTypingCheckBox->isChecked(),stype);
    settings_manager->setValue("contactOffline",contactOfflineCheckBox->isChecked(),stype);
    settings_manager->setValue("contactOnline",contactOnlineCheckBox->isChecked(),stype);
    settings_manager->setValue("ignore_settings_json",ignoreSettingsJsonCheckBox->isChecked(),stype);
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
    settings_manager->setValue("use_temp",true,SettingsManager::Static);
    saveSettings();
    qutim_sdk_0_2::TreeModelItem item;
    item.m_account_name = tr("Test");
    for(int i = 0; i<3; i++)
    {
        QmlPopups::Popup *popup = new QmlPopups::Popup(QString::number(counter++));
        popup->setMessage(tr("Preview"),tr("This is a simple popup ")+QString::number(i));
        popup->send();
    }
    settings_manager->setValue("use_temp",false,SettingsManager::Static);
}
