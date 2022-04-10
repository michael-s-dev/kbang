#include "voidai.h"
#include "playerctrl.h"
#include "publicgameview.h"
#include "privateplayerview.h"
#include "cards.h"
#include "util.h"
#include "player.h"

#include <QDebug>
#include <QList>
#include <QTimer>
#include <QApplication>
#include <cstdlib>

int VoidAI::sm_playerCounter = 0;

int minActionDelay = 1550;
int maxActionDelay = 2500;
QList<QString> BotName ;



VoidAI::VoidAI(QObject* parent):
    QObject(parent),
    m_id(++sm_playerCounter)
{
    //moveToThread(QApplication::instance()->thread());
}

CreatePlayerData VoidAI::createPlayerData() const
{
    //BotName << "Mr.Nobody" << "Bot" << "Smart Bot" << "Bot John" << "Mr.Unknown" << "Dumb Bot" << "Bot Lerry";
    //Vianoce
    BotName << "Santa Claus" << "Rudolf" << "sobík" << "elf" << "pani Clausová";
    shuffleList(BotName);
    CreatePlayerData res;
    res.name = QString("%1 #%2").arg(BotName.first()).arg(m_id);
    res.password = "void";
    return res;
}

void VoidAI::onHandlerRegistered(  const PublicGameView* publicGameView , PlayerCtrl* playerCtrl)
{
    Q_UNUSED(publicGameView);
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
    case REQUEST_DRAW:{
        qDebug() << QString("(%1) REQUEST_DRAW").arg(mp_playerCtrl->publicPlayerView().name());

        // NORMAL DRAW
        bool specialdraw = false ;
        PublicPlayerView* target = 0 ;

        if  ( mp_playerCtrl->publicPlayerView().character() == CHARACTER_KIT_CARLSON ||
              (mp_playerCtrl->publicPlayerView().character() == CHARACTER_PEDRO_RAMIREZ && mp_playerCtrl->publicGameView().graveyardTop() != 0 ))
            specialdraw = true ;

        if ( mp_playerCtrl->publicPlayerView().character() == CHARACTER_JESSE_JONES ){
            QList<PublicPlayerView*> targets = getPlayersList();
            if ( targets.first()->handSize() > 0 ){
                specialdraw = true ;
                target = targets.first() ;
            }
        }

        try {

            if ( specialdraw  && mp_playerCtrl->publicPlayerView().character() == CHARACTER_JESSE_JONES  &&
                 target != 0)
               mp_playerCtrl->useAbility( target );
            else if ( specialdraw)
                mp_playerCtrl->useAbility();
            else
                mp_playerCtrl->draw();
        }
        catch (BadGameStateException& e){
            e.debug();
        }
        catch (BadPredrawException& e) {
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
        catch(...){}
        break;
    }
    case REQUEST_PLAY: {
        qDebug() << QString("VoidAI (%1): REQUEST_PLAY").arg(m_id);


        /* **********
               Use cards
              ************
            */
        foreach (PlayingCard* card , hand) {
            try {
                switch(card->type()) {
                case CARD_WHISKY:
                case CARD_RISSA:
                {
                    if ( card->type() == CARD_WHISKY &&
                         mp_playerCtrl->privatePlayerView().lifePoints() == mp_playerCtrl->privatePlayerView().maxLifePoints()){
                        break;
                    }
                    if ( mp_playerCtrl->privatePlayerView().hand().size() > 1 && rcard->id() != card->id()){
                        mp_playerCtrl->playCard(card , rcard);
                        return;
                    }
                }
                    break;
                    // weapons --fiska
                case CARD_VOLCANIC:
                case CARD_SCHOFIELD:
                case CARD_REMINGTON:
                case CARD_CARABINE:
                case CARD_WINCHESTER:
                case CARD_DEAGLE:
                {
                    WeaponCard* weaponCard = qobject_cast<WeaponCard*>(card);


                    if ( mp_playerCtrl->privatePlayerView().character() == CHARACTER_WILLY_THE_KID &&
                         card->type() == CARD_VOLCANIC ) {
                        continue;
                    }
                    if ( mp_playerCtrl->privatePlayerView().character() == CHARACTER_WILLY_THE_KID &&
                         mp_playerCtrl->publicPlayerView().weaponRange() < weaponCard->getRange() ) {
                        mp_playerCtrl->playCard(card);
                        return;
                    }
                    if ( mp_playerCtrl->publicPlayerView().unlimitedBangs()== 0 &&
                         mp_playerCtrl->publicPlayerView().weaponRange() < weaponCard->getRange() ){
                        mp_playerCtrl->playCard(card);
                        return;
                    }
                    if (mp_playerCtrl->publicPlayerView().unlimitedBangs()== 1 && card->type() == CARD_DEAGLE ){
                        mp_playerCtrl->playCard(card);
                        return;
                    }
                    break;
                }
                case CARD_INDIANS:
                case CARD_GATLING:
                case CARD_HOWITZER:
                {
                    // Only for ready howitzer
                    if( card->type() == CARD_HOWITZER && !card->greenready()){
                        mp_playerCtrl->playCard(card);
                        return;
                    }
                    // vice dont shoot sheriff
                    if (mp_playerCtrl->privatePlayerView().role() == ROLE_DEPUTY && getSheriffLifePoints() == 1 ) {
                        break;
                    }
                    // vice dont shoot sheriff
                    if (mp_playerCtrl->privatePlayerView().role() == ROLE_DEPUTY && getSheriffLifePoints() < 4  && getSheriff()->handSize() < 4 ) {
                        break;
                    }
                    // carefull sheriff
                    if (mp_playerCtrl->privatePlayerView().role() == ROLE_SHERIFF  && lowHpPlayersCount() > 0
                            && mp_playerCtrl->privatePlayerView().lifePoints() !=1 && aliveDeputyCount() >= 1){
                        break;
                    }
                    mp_playerCtrl->playCard(card);
                    return;
                }
                case CARD_APPALOSSA:
                case CARD_MUSTANG:
                case CARD_DILIGENZA:
                case CARD_WELLSFARGO:
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
            QList<PublicPlayerView*> players = getPlayersList();
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
                case CARD_SPRINGFIELD:
                {

                    // as a outlaw prefer to shoot on sheriff
                    if (mp_playerCtrl->privatePlayerView().role() == ROLE_OUTLAW  && (
                                card->type() != CARD_JAIL || card->type() != CARD_CONESTOGA) ){
                        players.prepend( getSheriff());
                    }
                    // as a goodguy prefer to shoot on outlaw
                    if ( mp_playerCtrl->publicPlayerView().role() == ROLE_SHERIFF ||
                         mp_playerCtrl->publicPlayerView().role() == ROLE_SHERIFF ){

                        foreach ( PublicPlayerView* player , players){
                            if ( player->attacksOnSheriff() == 0 )
                                continue;
                            players.removeOne( player );
                            players.prepend( player );
                        }
                    }


                    foreach(const PublicPlayerView* p, players) {

                        rcard = mp_playerCtrl->getRadnomCardFromHand();

                        // dont shoot self
                        if (mp_playerCtrl->privatePlayerView().id() == p->id()) {
                            continue;
                        }
                        // vice dont shoot sheriff
                        if (mp_playerCtrl->privatePlayerView().role() == ROLE_DEPUTY && p->isSheriff()) {
                            continue;
                        }
                        // renegade dont shoot sheriff until duel
                        if (mp_playerCtrl->privatePlayerView().role() == ROLE_RENEGADE && p->isSheriff() &&
                                alivePlayersCount() > 2 ){
                            continue;
                        }
                        // carefull sheriff
                        if (mp_playerCtrl->privatePlayerView().isSheriff() && alivePlayersCount() > 2
                                && card->isBangCard() && p->lifePoints() == 1 && aliveDeputyCount() >= 1 ){
                            continue;
                        }
                        // outlaw shoot only sherif if no deputy
                        if ( mp_playerCtrl->privatePlayerView().role() == ROLE_OUTLAW && aliveDeputyCount() == 0
                             && card->isBangCard() && !p->isSheriff())
                            continue;

                        if ( card->type() == CARD_SPRINGFIELD &&
                             (mp_playerCtrl->privatePlayerView().hand().size() < 2 || rcard->id() == card->id()) ){
                            continue;
                        }
                        try {
                            if ( card->type() == CARD_SPRINGFIELD ){
                                mp_playerCtrl->playCard(card, rcard , p);
                                return;
                            }
                            else{
                                mp_playerCtrl->playCard(card, p);
                                return;
                            }

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
                {
                    // vice prefer heal sheriff
                    if ( mp_playerCtrl->privatePlayerView().role() == ROLE_DEPUTY  &&
                         card->type() == CARD_TEQUILA && getSheriffLifePoints() <= 3 ){
                        players.prepend( getSheriff() );
                    }

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
                case CARD_GIFT:{
                    QList<PlayingCard*> gifts ;

                    foreach( PublicPlayerView* player , players ){
                         if ( !player->table().isEmpty()){
                            gifts = player->table();
                            break;
                        }
                    }
                    gifts = gifts + mp_playerCtrl->privatePlayerView().hand();
                    shuffleList(gifts);

                    if ( !gifts.isEmpty()) {
                        while ( players.first()->id() == mp_playerCtrl->publicPlayerView().id() ||
                                players.first()->id() == gifts.first()->owner()->id() ){
                            if ( players.size() >1 ) players.removeFirst();
                            else break;
                        }
                        try{
                            mp_playerCtrl->playCard( card , gifts.first() , players.first() );
                            mp_playerCtrl->sendChatMessage(QString("I'm sending a gift to (%1) ☺").arg(players.first()->name()) );
                            return;
                        }
                        catch(...){ }

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

        /* **********
               Use Ability
              ************
            */
        const PrivatePlayerView& bot = mp_playerCtrl->privatePlayerView();
        switch( bot.character() ){
        case CHARACTER_CHUCK_WENGAM:{
            if  (  bot.lifePoints() == bot.maxLifePoints() && bot.hand().size() < 5 ){
                mp_playerCtrl->useAbility();
                return;
            }
            break;
        }
        case CHARACTER_SID_KETCHUM:
        {
            if  (  bot.lifePoints() != bot.maxLifePoints() && bot.hand().size() > 2  ){
                QList<PlayingCard*> handList = bot.hand();
                shuffleList( handList );
                QList<PlayingCard*> list;
                list << bot.hand()[0] << bot.hand()[1];
                mp_playerCtrl->useAbility( list );
                return;
            }
            break;
        }
        case CHARACTER_JOSE_DELGADO:
        {
            foreach ( PlayingCard* card , bot.hand() ){
                if ( card->isBlue()) {
                    QList<PlayingCard*> list;
                    list.append(card);
                    try{
                        mp_playerCtrl->useAbility( list );

                    }
                    catch(BadUsageAbilityAlreadyUsed e){
                        e.debug(); break;
                    }
                    catch(...){
                        break;
                    }
                    return;
                }
                continue;
            }
            break;
        }

        default:break;
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
            cards = getSelectionCards( cards ); // return list of most value cards
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


// FUNCTIONS

int VoidAI::alivePlayersCount()
{
    QList<PublicPlayerView*> players = getPlayersList();
    return players.count();
}

int VoidAI::lowHpPlayersCount()
{
    int i = 0;
    QList<PublicPlayerView*> players = getPlayersList();
    foreach(const PublicPlayerView* p, players) {
        if ( p->isAlive() && p->lifePoints() < 2 ){
            i++;
        }
    }
    return i;
}

PublicPlayerView* VoidAI::getSheriff() {

    PublicPlayerView* sheriff;

    QList<PublicPlayerView*> players = getPlayersList();
    foreach( PublicPlayerView* p, players) {
        if ( p->isSheriff() ){
            sheriff = p;
        }
    }
    return sheriff;
}


int VoidAI::getSheriffLifePoints()
{
    return getSheriff()->lifePoints();
}


QList<PublicPlayerView*> VoidAI::getPlayersList( bool alive){
    // list of players
    QList<PublicPlayerView*> players = mp_playerCtrl->publicGameView().publicPlayerList();
    QList<PublicPlayerView*> tempPlayers;
    shuffleList(players);
    //for debug and testing
    foreach ( PublicPlayerView* player  , players ){
        if ( player->name() == "debug"  || ( alive && !player->isAlive() )){
            continue;
        }
        tempPlayers.append( player );
    }
    return tempPlayers;
}


int VoidAI::aliveDeputyCount() {

    QList<PublicPlayerView*> players = getPlayersList( false );
    int deputy = 0;

    if ( players.count() == 4) deputy = 0;
    else if ( players.count() > 4 && players.count() < 7) deputy = 1;
    else deputy = 2;

    foreach ( PublicPlayerView* player , players){
        if ( !player->isAlive() && player->role() == ROLE_DEPUTY )
            deputy--;
    }
    return deputy;
}

// return list of most value cards
QList<PlayingCard*> VoidAI::getSelectionCards(QList<PlayingCard*> cards){

    QList<PlayingCard*> toptiercards;
    QList<PlayingCard*> bettercards;
    foreach ( PlayingCard* card , cards) {
        switch(card->type()){
        case CARD_WELLSFARGO:case CARD_DEAGLE:case CARD_WHISKY:
            toptiercards.append( card );
            break;
        case CARD_PONY_EXPRESS:case CARD_BEER:case CARD_DILIGENZA:case CARD_SCHIVATA:
        case CARD_VOLCANIC:{
            if (card->type() == CARD_BEER &&
                    mp_playerCtrl->privatePlayerView().lifePoints() == mp_playerCtrl->privatePlayerView().maxLifePoints() )
                break;
            bettercards.append( card );
            break;
        }
        default: break;
        }
    }


    if (toptiercards.isEmpty() && bettercards.isEmpty() ) return cards;
    else if ( toptiercards.isEmpty() ) return bettercards;
    else return toptiercards;

}
