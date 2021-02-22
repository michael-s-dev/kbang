#include "cardmultishoot.h"
#include "gametable.h"
#include "gamecycle.h"
#include "game.h"
#include "player.h"
#include "gameexceptions.h"
#include "cardbarrel.h"

CardMultiShoot::CardMultiShoot(Game* game, int id, CardMultiShoot::Type type, CardSuit cardSuit, CardRank cardRank):
        ReactionCard(game, id, CARD_UNKNOWN, cardSuit, cardRank),
        m_type(type),
        mp_requestedPlayer(0)
{
    switch(m_type) {
    case Indians:
        setType(CARD_INDIANS);
        break;
    case Gatling:
        setType(CARD_GATLING);
        break;
    case Howitzer:
        setType(CARD_HOWITZER);
        break;
    case Rissa:
        setType(CARD_RISSA);
        break;
    }
}

CardMultiShoot::~CardMultiShoot()
{
}

// Rissa
void CardMultiShoot::play(PlayingCard* targetCard){

    gameCycle()->assertTurn();
    assertInHand();
    gameTable()->playerDiscardCard(targetCard);
    Player* cardowner = this->owner();
    gameTable()->playerPlayCard(this);

    Player* player;
    PlayingCard* card;


    foreach (player, game()->playerList()){
        if ( player == cardowner ){
            continue;
        }
        card = player->getRandomCardFromTable();
        if ( card != 0){
          gameTable()->playerDiscardCard(card);
        }
        else{
         card = player->getRandomCardFromHand();
         if ( card != 0)
          gameTable()->playerDiscardCard(card);
        }
    }
}

void CardMultiShoot::play()
{

 gameCycle()->assertTurn();

     if  (m_type == Howitzer  && this->pocket() == POCKET_HAND) {
                 assertInHand();
                 if (owner()->hasIdenticalCardOnTable(this)) {
                     throw TwoSameOnTableException();
                 }
                 gameTable()->playerPlayCardOnTable(this);
                 this->setGreenReady(false);
     }
     else {
            if (m_type == Howitzer) {
                 assertOnTable();
                 if ( this->greenready() == 0)
                   throw BadCardException();
            }
            else {assertInHand();}
            mp_shootingPlayer = owner();
            mp_requestedPlayer = owner();
            m_usedBarrels.clear();
            gameTable()->playerPlayCard(this);
            requestNext();
        }
    }

void CardMultiShoot::respondPass()
{
    gameCycle()->unsetResponseMode();
    gameTable()->playerPass(mp_requestedPlayer);
    mp_requestedPlayer->modifyLifePoints(-1, mp_shootingPlayer);
    requestNext();
}

void CardMultiShoot::respondCard(PlayingCard* targetCard)
{
    switch(targetCard->type()) {
    case CARD_BANG:
        if (m_type != Indians)
            break;
        targetCard->assertInHand();
        gameTable()->playerRespondWithCard(targetCard);
        game()->gameCycle().unsetResponseMode();
        requestNext();
        return;

    case CARD_MISSED:
    case CARD_SCHIVATA:
        if (m_type == Indians)
            break;
        targetCard->assertInHand();
        gameTable()->playerRespondWithCard(targetCard);
        game()->gameCycle().unsetResponseMode();
        if (targetCard->type() == CARD_SCHIVATA){
        gameTable()->playerDrawFromDeck(mp_requestedPlayer, 1);}
        requestNext();
        return;
    case CARD_SOMBRERO:
    case CARD_PLACCA_DI_FERRO:
    case CARD_BIBBIA:{
        if (m_type == Indians)
            break;
        if (targetCard->greenready() == 1){
        targetCard->assertOnTable(); // Continue only if on table
        game()->gameCycle().unsetResponseMode();
        gameTable()->playerRespondWithGreenCard(targetCard);
        if (targetCard->type() == CARD_BIBBIA)
            gameTable()->playerDrawFromDeck(mp_requestedPlayer, 1);
        requestNext();
        return;
        }
        else {
            throw BadCardException();
            return;
        }
    }
    case CARD_BARREL: {
        if (m_type == Indians)
            break;
        if (m_usedBarrels.contains(targetCard))
            break;
        targetCard->assertOnTable();
        m_usedBarrels.append(targetCard);
        CardBarrel* barrel = qobject_cast<CardBarrel*>(targetCard);
        barrel->check(this);
        return;
    }
    default:
        break;
    }
    throw BadCardException();
}

void CardMultiShoot::checkResult(bool result)
{
    Q_ASSERT(m_type == Gatling);
    if (result) {
        game()->gameCycle().unsetResponseMode();
        requestNext();
    }
}


ReactionType CardMultiShoot::reactionType() const
{
   if (m_type == Indians) return REACTION_INDIANS;
   else if (m_type == Howitzer) return REACTION_HOWITZER;
   else return REACTION_GATLING;
}

void CardMultiShoot::requestNext()
{
    mp_requestedPlayer = game()->nextPlayer(mp_requestedPlayer);
    if (mp_requestedPlayer->characterType() == CHARACTER_APACHE_KID && m_type == Indians && mp_requestedPlayer != mp_shootingPlayer)
       mp_requestedPlayer = game()->nextPlayer(mp_requestedPlayer) ;
    if (mp_requestedPlayer == mp_shootingPlayer) return;

    game()->gameCycle().setResponseMode(this, mp_requestedPlayer);
}
