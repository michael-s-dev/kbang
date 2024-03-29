#include "gamemessageevent.h"
#include "game.h"
#include "card.h"
#include "config.h"
#include "common.h"

#include <QSound>
#include <QMediaPlaylist>
#include <QMediaPlayer>

using namespace client;

GameMessageEvent::GameMessageEvent(Game* game, const GameMessage& gameMessage):
        GameEvent(game), m_gameMessage(gameMessage)
{
}

GameMessageEvent::~GameMessageEvent()
{
}

void GameMessageEvent::run()
{
    GameEvent::run();
    QString msg;
    // ID of client ( never change)
    int client_id = mp_game->playerId();
    // Name,ID of player which play a card
    QString playerName       = m_gameMessage.player ? mp_game->playerWidget(m_gameMessage.player)->name() : "";
    int     playerId      = m_gameMessage.player ? mp_game->playerWidget(m_gameMessage.player)->id() : 0;
    QString targetPlayerName = m_gameMessage.targetPlayer ? mp_game->playerWidget(m_gameMessage.targetPlayer)->name() : "";
    QString causedByName     = m_gameMessage.causedBy ? mp_game->playerWidget(m_gameMessage.causedBy)->name() : "";

    //Get music name from config
    Config& cfg = Config::instance();
    cfg.refresh();
    //Vianoce
    QList<QString>  songs ;
    songs << "jingle_bells"<<"let_it_snow_cut"<< "wish_you _xmas_cut"<<"hippo_cut"<< "kevin_cut"<<"navidad_cut" ;
    int month =  QDate::currentDate().month();
    QString song = cfg.readString("game" , "music") + ".wav";
    if( month == 12 ) song = songs[qrand() % 6] + ".mp3";

    QMediaPlayer* mediaPlayer = new QMediaPlayer;

    switch(m_gameMessage.type) {
    case GAMEMESSAGE_GAMESTARTED:
        mp_game->setGameState(GAMESTATE_PLAYING);
        mediaPlayer->setMedia(QUrl::fromLocalFile(Config::dataPathString() + "sounds/" + song ));
        mediaPlayer->setVolume(60);
        mediaPlayer->play();
        msg = tr("The game has just started.");
        break;
    case GAMEMESSAGE_GAMEFINISHED:
        mp_game->setGameState(GAMESTATE_FINISHED);

        msg = tr("The game has finished.");
        break;
    case GAMEMESSAGE_PLAYERDRAWFROMDECK:
        if ( client_id == playerId  )
        QSound::play(Config::dataPathString() + "sounds/drawacard.wav");

        msg = tr("%1 drew %2 from the deck.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardListWidgetToString(m_gameMessage.cards));
        break;
    case GAMEMESSAGE_PLAYERDRAWFROMGRAVEYARD:
        msg = tr("%1 drew %2 from the discard pile.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERDISCARDCARD:
        msg = tr("%1 discarded %2.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERPLAYCARD:
        if (m_gameMessage.card.type == CARD_BEER || m_gameMessage.card.type == CARD_SALOON || m_gameMessage.card.type == CARD_TEQUILA ||
                m_gameMessage.card.type == CARD_WHISKY )
            QSound::play(Config::dataPathString() + "sounds/beer.wav");
        if (m_gameMessage.card.type == CARD_APPALOSSA || m_gameMessage.card.type == CARD_MUSTANG )
            QSound::play(Config::dataPathString() + "sounds/horseplayed.wav");
        if (m_gameMessage.card.type == CARD_VOLCANIC||
            m_gameMessage.card.type == CARD_DEAGLE  ||
            m_gameMessage.card.type == CARD_SCHOFIELD||
            m_gameMessage.card.type == CARD_REMINGTON||
            m_gameMessage.card.type == CARD_CARABINE||
            m_gameMessage.card.type == CARD_WINCHESTER)
             QSound::play(Config::dataPathString() + "sounds/weaponplayed.wav");
        if (m_gameMessage.card.type == CARD_JAIL )
            QSound::play(Config::dataPathString() + "sounds/jail.wav");
        if (m_gameMessage.card.type == CARD_DYNAMITE )
            QSound::play(Config::dataPathString() + "sounds/bomb.wav");
        if (m_gameMessage.card.type == CARD_RAG_TIME )
            QSound::play(Config::dataPathString() + "sounds/regtime.wav");

        if (m_gameMessage.targetCard.id) {
            msg = tr("%1 played %2 on %3%4.").
                        arg(decoratePlayerName(playerName)).
                        arg(cardToString(m_gameMessage.card)).
                        arg("card").
                        arg(m_gameMessage.targetPlayer ?
                                tr(" owned by %1").arg(decoratePlayerName(targetPlayerName, 1)) : "");
        } else if (m_gameMessage.targetPlayer && m_gameMessage.targetPlayer != m_gameMessage.player) {
            msg = tr("%1 played %2 on %3.").
                        arg(decoratePlayerName(playerName)).
                        arg(cardToString(m_gameMessage.card)).
                        arg(decoratePlayerName(targetPlayerName, 1));
        } else {
            msg = tr("%1 played %2.").
                        arg(decoratePlayerName(playerName)).
                        arg(cardToString(m_gameMessage.card));
        }
        break;
    case GAMEMESSAGE_PLAYERRESPONDWITHCARD:
        if(m_gameMessage.card.type == CARD_MISSED || m_gameMessage.card.type == CARD_SCHIVATA){
           if ( client_id == playerId )
               QSound::play(Config::dataPathString() + "sounds/miss.wav");
        }

        msg = tr("%1 responded with %2.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERPASS:
        msg = tr("%1 did not react.").
                    arg(decoratePlayerName(playerName));
        QSound::play(Config::dataPathString() + "sounds/noreact.wav");
        break;
    case GAMEMESSAGE_PLAYERPICKFROMSELECTION:
        msg = tr("%1 took %2 from selection.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card));
        break;
    case GAMEMESSAGE_PLAYERCHECKDECK:
        msg = tr("%1 \"drew!\" %2 (because of %3) and ").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.targetCard, 1)).
                    arg(cardToString(m_gameMessage.card));
        if (m_gameMessage.checkResult)
            msg += tr("was lucky.");
        else {
            msg += tr("failed.");
            if(QString(cardToString(m_gameMessage.card)).contains("Dinamite"))
               // QSound::play(Config::dataPathString() + "sounds/dynamite.wav");
               // Vianoce
               QSound::play(Config::dataPathString() + "sounds/merry_christmas.wav");
        }
        break;
    case GAMEMESSAGE_PLAYERSTEALCARD:
        msg = tr("%1 drew %2 from %3.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card)).
                    arg(decoratePlayerName(targetPlayerName, 1));
        break;
    case GAMEMESSAGE_PASSTABLECARD:
        msg = tr("%1 move %2 to %3.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card)).
                    arg(decoratePlayerName(targetPlayerName, 1));
        break;
    case GAMEMESSAGE_PLAYERCANCELCARD:
        msg = tr("%1 forced %3 to discard %2.").
                    arg(decoratePlayerName(playerName)).
                    arg(cardToString(m_gameMessage.card)).
                    arg(decoratePlayerName(targetPlayerName, 1));
        break;
    case GAMEMESSAGE_DECKREGENERATE:
        QSound::play(Config::dataPathString() + "sounds/shuffle.wav");
        msg = tr("The deck ran out of cards. Cards from the discard pile were shuffled and are now used as new deck.");
        break;
    case GAMEMESSAGE_PLAYERDIED:
        QSound::play(Config::dataPathString() + "sounds/death.wav");
        msg = tr("%1 passed away. R.I.P.").arg(decoratePlayerName(playerName));
        break;
    case GAMEMESSAGE_INVALID:
        break;
    }
    if (!msg.isEmpty())
        mp_game->sendLogMessage(msg);
    //qDebug() << msg;
    GameEvent::finish();
}

QString GameMessageEvent::cardToString(const CardData& cardData, bool withRankAndSuit)
{
    if (cardData.id == 0) {
        return tr("<i>unknown card</i>");
    }
    const Card* card = Card::findPlayingCard(cardData.type);
    if (card == 0)
        return "";

    QString res = "<b><i>" + card->name() + "</i></b>";
    if (withRankAndSuit)
        res += " (" + Card::rankToString(cardData.rank) +
               Card::suitToColorString(cardData.suit) + ")";
    return res;
}

QString GameMessageEvent::cardListWidgetToString(QList<CardData> cardListWidget)
{
    if (cardListWidget.size() == 0)
        return "";
    QStringList cardStrings;
    foreach(const CardData& cardData, cardListWidget) {
        cardStrings.append(cardToString(cardData));
    }
    QString result;
    QStringListIterator it(cardStrings);
    result = it.next();
    while(it.hasNext()) {
        QString next = it.next();
        if (it.hasNext()) {
            result = tr("%1, %2").arg(result).arg(next);
        } else {
            result = tr("%1 and %2").arg(result).arg(next);
        }
    }
    return result;
}

QString GameMessageEvent::decoratePlayerName(const QString& playerName, bool isTarget)
{
    return QString("<font color=\"%2\"><b>%1</b></font>").
                  arg(removeHTMLtags(playerName)).arg(isTarget ? "navy" : "lightblue");
}
