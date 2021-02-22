/*
 * Copyright (c) 2014-2016 Alex Spataru <alex_spataru@outlook.com>
 *
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file for more details.
 */

#include "Window.h"
#include "ui_Window.h"

#include <QSimpleUpdater.h>

//==============================================================================
// Define the URL of the Update Definitions file
//==============================================================================

static const QString DEFS_URL = "http://gameplanes.6f.sk/updates.json";

//==============================================================================
// Window::Window
//==============================================================================

Window::Window (QWidget* parent) : QMainWindow (parent) {
    m_ui = new Ui::Window;
    m_ui->setupUi (this);

    m_updater = QSimpleUpdater::getInstance();

    /* Check for updates when the "Check For Updates" button is clicked */
    connect (m_updater, SIGNAL (checkingFinished (QString)),
             this,        SLOT (updateChangelog  (QString)));

    /* React to button clicks */
    connect (m_ui->resetButton, SIGNAL (clicked()),
             this,                SLOT (resetFields()));
    connect (m_ui->closeButton, SIGNAL (clicked()),
             this,                SLOT (close()));
    connect (m_ui->checkButton, SIGNAL (clicked()),
             this,                SLOT (checkForUpdates()));

    /* Resize the dialog to fit */
    setFixedSize (minimumSizeHint());

    /* Reset the UI state */
    resetFields();
}

//==============================================================================
// Window::~Window
//==============================================================================

Window::~Window() {
    delete m_ui;
}

//==============================================================================
// Window::checkForUpdates
//==============================================================================

void Window::resetFields() {
    m_ui->installedVersion->setText ("0.1");
    m_ui->enableDownloader->setChecked (true);
    m_ui->showAllNotifcations->setChecked (false);
    m_ui->showUpdateNotifications->setChecked (true);
}

//==============================================================================
// Window::checkForUpdates
//==============================================================================

void Window::checkForUpdates() {
    /* Get settings from the UI */
    QString version = m_ui->installedVersion->text();
    bool downloaderEnabled = m_ui->enableDownloader->isChecked();
    bool notifyOnFinish = m_ui->showAllNotifcations->isChecked();
    bool notifyOnUpdate = m_ui->showUpdateNotifications->isChecked();

    /* Apply the settings */
    m_updater->setModuleVersion (DEFS_URL, version);
    m_updater->setNotifyOnFinish (DEFS_URL, notifyOnFinish);
    m_updater->setNotifyOnUpdate (DEFS_URL, notifyOnUpdate);
    m_updater->setDownloaderEnabled (DEFS_URL, downloaderEnabled);

    /* Check for updates */
    m_updater->checkForUpdates (DEFS_URL);
}

//==============================================================================
// Window::updateChangelog
//==============================================================================

void Window::updateChangelog (QString url) {
    if (url == DEFS_URL)
        m_ui->changelogText->setText (m_updater->getChangelog (url));
}
