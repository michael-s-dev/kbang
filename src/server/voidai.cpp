#include "voidai.h"
#include "playerctrl.h"
#include "publicgameview.h"
#include "privateplayerview.h"
#include "cards.h"
#include "util.h"
#include "player.h"

#include <QDebug>
#include <QTimer>
#include <QApplication>
#include <cstdlib>

int VoidAI::sm_playerCounter = 0;

int minActionDelay = 800;
int maxActionDelay = 2500;
QString BotName = "Mr.Nobody";


VoidAI::VoidAI(QObject* parent):
        QObject(parent),
        m_id(++sm_playerCounter)
{
    //moveToThread(QApplication::instance()->thread());
}

CreatePlayerData VoidAI::createPlayerData() const
{
    CreatePlayerData res;
    res.name = QString("%1 #%2").arg(BotName).arg(m_id);
    res.password = "void";
    return res;
}

void VoidAI::onHandlerRegistered(const PublicGameView* publicGameView, PlayerCtrl* playerCtrl)
{
    mp_playerCtrl = playerCtrl;
}

void VoidAI::onActionRequest(ActionRequestType requestType)
{
    m_requestType = requestType;
    // Simulate a real player
    int randomDelay = (rand() % (maxActionDelay - minActionDelay)) + minActionDelay;
    QTimer::singleShot(randomDelay, this, SLOT(requestWithAction()));
}

void VoidAI::requestWithAction()
{
    qDebug() << QString("VoidAI (%1): onActionRequest(%2)").arg(m_id).arg(m_requestType);
    if (mp_playerCtrl->publicGameView().gameContextData().requestedPlayerId != mp_playerCtrl->privatePlayerView().id()) {
        QString("VoidAI (%1): Not requested!").arg(m_id);
        return;
    }
    QList<PlayingCard*> hand = mp_playerCtrl->privatePlayerView().table();
    hand += mp_playerCtrl->privatePlayerView().hand();
    PlayingCard* rcard = mp_playerCtrl->getRadnomCardFromHand();
    switch(m_requestType) {
        case REQUEST_DRAW:
        qDebug() << QString("VoidAI (%1): REQUEST_DRAW").arg(m_id);
            // Drawing two cards
            try {
                mp_playerCtrl->draw();
            } catch (BadPredrawException& e) {
                e.debug();
                QList<PlayingCard*> table = mp_playerCtrl->privatePlayerView().table();
                foreach(PlayingCard* c, table) {
                    try {
                        qDebug() << "Trying to play some card to bypass predraw exception";
                        mp_playerCtrl->playCard(c);
                        return;
                    } catch (GameException& e) {
                        qDebug() << "Predraw exception test exception:";
                        e.debug();
                    }
                }
            }
            break;
        case REQUEST_PLAY: {
            qDebug() << QString("VoidAI (%1): REQUEST_PLAY").arg(m_id);

            // Try to use blue cards:
            foreach (PlayingCard* card , hand) {
                try {
                    switch(card->type()) {
                        case CARD_WHISKY:
                        case CARD_RISSA:
                        if ( mp_playerCtrl->privatePlayerView().hand().size() > 1 && rcard->id() != card->id()){
                                mp_playerCtrl->playCard(card , rcard);
                                return;
                             }
                            else{ break; }
                        case CARD_APPALOSSA:
                        case CARD_MUSTANG:
                        case CARD_VOLCANIC:
                        case CARD_SCHOFIELD:
                        case CARD_REMINGTON:
                        case CARD_CARABINE:
                        case CARD_WINCHESTER:
                        case CARD_DILIGENZA:
                        case CARD_WELLSFARGO:
                        case CARD_INDIANS:
                        case CARD_GATLING:
                        case CARD_GENERALSTORE:
                        case CARD_DYNAMITE:
                        case CARD_BARREL:
                        case CARD_RIPARO:
                        case CARD_SOMBRERO:
                        case CARD_BIBBIA:
                        case CARD_PONY_EXPRESS:
                        case CARD_BORRACCIA:
                        case CARD_PLACCA_DI_FERRO:
                        case CARD_CAN_CAN:
                        case CARD_CONESTOGA:
                        case CARD_FUCILE_DA_CACCIA:
                        case CARD_DERRINGER:
                        case CARD_PUGNALE:
                        case CARD_PEPPERBOX:
                        case CARD_HOWITZER:
                        case CARD_DEAGLE:
                            mp_playerCtrl->playCard(card);
                            return;
                        case CARD_BEER:
                        case CARD_SALOON:
                            if (mp_playerCtrl->privatePlayerView().lifePoints() !=
                                    mp_playerCtrl->privatePlayerView().maxLifePoints()) {
                                mp_playerCtrl->playCard(card);
                                return;
                            }
                        default:
                            break;
                    }
                } catch (GameException& e)  {
                    qDebug() << "VoidAI: (checkpoint #1)";
                    e.debug();
                }
            }
            foreach (PlayingCard* card, hand) {
                try {
                    switch(card->type()) {

                        case CARD_CAN_CAN:
                        case CARD_CONESTOGA:
                        case CARD_FUCILE_DA_CACCIA:
                        case CARD_DERRINGER:
                        case CARD_PUGNALE:
                        case CARD_PEPPERBOX:
                        case CARD_BANG:
                        case CARD_DUEL:
                        case CARD_JAIL:
                        case CARD_PUGNO:
                        case CARD_PANIC:
                        case CARD_CATBALOU:
                        {
                            QList<PublicPlayerView*> players = mp_playerCtrl->publicGameView().publicPlayerList();
                            shuffleList(players);
                            foreach(const PublicPlayerView* p, players) {
                                if (mp_playerCtrl->privatePlayerView().id() == p->id()) {
                                    continue;
                                 }
                                // vice dont shoot sheriff
                                if (mp_playerCtrl->privatePlayerView().role() == ROLE_DEPUTY && p->isSheriff()) {
                                        continue;
                                }
                                try {
                                    mp_playerCtrl->playCard(card, p);
                                    return;
                                } catch (BadTargetPlayerException e) {
                                    qDebug() << "VoidAI: BadTargetPlayerException!";
                                } catch (OneBangPerTurnException e) {
                                    qDebug() << "VoidAI: One bang per turn!";
                                } catch(GameException& e) {
                                    qDebug() << "VoidAI: GameException";
                                }
                            }
                            break;
                        }
                          case CARD_RAG_TIME:
                          case CARD_TEQUILA:
                          case CARD_SPRINGFIELD:
                        {
                            QList<PublicPlayerView*> players = mp_playerCtrl->publicGameView().publicPlayerList();
                            shuffleList(players);
                            foreach(const PublicPlayerView* p, players) {

                                rcard = mp_playerCtrl->getRadnomCardFromHand();

                                if (mp_playerCtrl->privatePlayerView().id() == p->id() || p->isAlive() == false ) {
                                    continue;
                                }
                                if ( mp_playerCtrl->privatePlayerView().hand().size() < 2 || rcard->id() == card->id() ){
                                    continue;
                                }
                                if ( card->type() == CARD_TEQUILA && p->lifePoints() == p->maxLifePoints() ){
                                    continue;
                                }
                                try {
                                    mp_playerCtrl->playCard(card, rcard , p);
                                    return;
                                } catch (BadTargetPlayerException e) {
                                    qDebug() << "VoidAI: BadTargetPlayerException!";
                                } catch (OneBangPerTurnException e) {
                                    qDebug() << "VoidAI: One bang per turn!";
                                } catch(GameException& e) {
                                    qDebug() << "VoidAI: GameException";
                                }
                            }
                            break;
                        }
                        default:
                            break;
                    }
                } catch (GameException& e) {
                    qDebug() << "VoidAI: (checkpoint #2)";
                    e.debug();
                }
            }

            // Finish turn or discard random card
            try {
                mp_playerCtrl->finishTurn();
                return;
            } catch (TooManyCardsInHandException e) {
                qDebug() << QString("VoidAI (%1): discarding card").arg(m_id);
                PlayingCard* card = mp_playerCtrl->privatePlayerView().hand().first();
                mp_playerCtrl->discardCard(card);
                return;
            }
            break;
        }
        case REQUEST_RESPOND: {
            if (mp_playerCtrl->publicGameView().selection().size() > 0) {
                QList<PlayingCard*> cards = mp_playerCtrl->publicGameView().selection();
                int index = rand() % cards.size();
                try {
                    mp_playerCtrl->playCard(cards[index]);
                    return;
                } catch(GameException& e) {
                    qDebug() << QString("VoidAI (%1): Respond - selection: GameException").arg(m_id);
                    e.debug();
                }
            }
            qDebug() << QString("VoidAI (%1): REQUEST_RESPOND").arg(m_id);;
            QList<PlayingCard*> cards = mp_playerCtrl->privatePlayerView().hand();
            foreach (PlayingCard* c, hand) {
                try {
                    qDebug() << "Trying to play: " << playingCardTypeToString(c->type());
                    mp_playerCtrl->playCard(c);
                    return;
                } catch (BadCardException e) {
                    qDebug() << QString("VoidAI (%1): Respond: BadCardException").arg(m_id);
                } catch (BadPlayerException e) {
                    qDebug() << QString("VoidAI (%1): Respond: BadPlayerException").arg(m_id);
                } catch (GameException& e) {
                    qDebug("VoidAI");
                    e.debug();
                }
            }
            qDebug() << QString("VoidAI (%1): Trying to pass").arg(m_id);
            try {
                mp_playerCtrl->pass();
            } catch (GameException& e) {
                qDebug("Pass exception:");
                e.debug();
            }


            return;
        }
        case REQUEST_DISCARD:
            try {
                qDebug() << QString("VoidAI (%1): discarding card").arg(m_id);
                PlayingCard* card = mp_playerCtrl->privatePlayerView().hand().first();
                qDebug() << QString("VoidAI (%1): cards in hand: %2").arg(m_id).arg(
                        mp_playerCtrl->privatePlayerView().hand().size());
                mp_playerCtrl->discardCard(card);
            } catch (BadGameStateException e) {
                qDebug() << QString("VoidAI (%1): BadGameStateException").arg(m_id);
            }
            break;
    }
}
