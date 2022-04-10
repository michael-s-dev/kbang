/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "serverconnection.h"
#include "helpcarddialog.h"
#include "settingsdialog.h"

#include <QList>


#define KBANG_CLIENT_VERSION_MAJOR 1
#define KBANG_CLIENT_VERSION_MINOR 1
#define KBANG_CLIENT_VERSION_REVISION 0


class QSimpleUpdater;

namespace client {

class ConnectToServerDialog;
class CreateGameDialog;
class JoinGameDialog;
class AboutDialog;
class OpponentWidget;
class Game;
class CardWidgetSizeManager;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();
    virtual void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent *ev);

public slots:
    void showConnectToServerDialog();
    void disconnectFromServer();
    void showCreateGameDialog();
    void showJoinGameDialog();
    void leaveGame();
    void showAboutDialog();
    void showHelpCardDialog();
    void showSettingsDialog();

    void enterGameMode(int gameId, const QString& gameName, ClientType);
    void exitGameMode();

    void serverConnectionStatusChanged();
     //Update Patch
    void checkForUpdates();
    void updateChangelog (QString url);


signals:
    void connectToServer(QString serverHost, int serverPort);

private:
    void createMenu();
    void createActions();
    void createWidgets();
    void updateActions();
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    ConnectToServerDialog* mp_connectToServerDialog;
    CreateGameDialog*      mp_createGameDialog;
    JoinGameDialog*        mp_joinGameDialog;
    AboutDialog*           mp_aboutDialog;
    HelpCardDialog*        mp_HelpCardDialog;
    SettingsDialog*        mp_settingsDialog;
    ServerConnection       m_serverConnection;
    Game*                  mp_game;
    QList<OpponentWidget*> m_opponentWidgets;
    CardWidgetSizeManager* mp_cardWidgetSizeManager;
    QImage*                mp_background;
    //Update Patch
    QSimpleUpdater*        m_updater;

};
}
#endif



