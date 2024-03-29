#include "cardtaker.h"
#include "player.h"
#include "gamecycle.h"
#include "gametable.h"
#include "gameexceptions.h"
#include "game.h"

#include "weaponcard.h"



CardTaker::CardTaker(Game* game, int id, CardTaker::Type type, CardSuit cardSuit, CardRank cardRank):
       PlayingCard(game, id, CARD_UNKNOWN, cardSuit, cardRank),
        m_type(type),
        m_targetCard(0)
{
    if (m_type == Panic)
        setType(CARD_PANIC);
    else if  (m_type == CatBalou)
        setType(CARD_CATBALOU);
    else if (m_type == cancan)
        setType(CARD_CAN_CAN);
    else if (m_type == RagTime)
        setType(CARD_RAG_TIME);
    else if (m_type == Gift)
        setType(CARD_GIFT);
    else
        setType(CARD_CONESTOGA);
}

CardTaker::~CardTaker()
{
}

// Trigger this fucntion when clicked card in hand and its not panic or catbalou
void CardTaker::play()
    {

        gameCycle()->assertTurn();
        assertInHand();

            if (owner()->hasIdenticalCardOnTable(this)) {
                throw TwoSameOnTableException();
            }
            gameTable()->playerPlayCardOnTable(this);
            this->setGreenReady(false);
}


void CardTaker::play( PlayingCard* targetCard , Player* targetPlayer ){
    if (m_type == Gift){
      // State check
      gameCycle()->assertTurn();
      assertInHand();
      if (owner() == targetPlayer || targetPlayer->isAlive() == false )
          throw BadTargetPlayerException();
      if (targetPlayer->hasIdenticalCardOnTable(targetCard)) {
          throw TwoSameOnTableException();
      }
//      Vianoce
//      if (targetCard->pocket() != POCKET_TABLE) {
//          throw BadCardException();
//      }

      // Play the card
      gameTable()->playerPlayCard(this, targetCard);

      // Double weapon check
      WeaponCard* weaponCard = qobject_cast<WeaponCard*>(targetCard);
      if ( weaponCard != 0 ) {
          qDebug() <<  "hello there";
        foreach(PlayingCard* card, targetPlayer->table()) {
          WeaponCard* weaponCard = qobject_cast<WeaponCard*>(card);
          if (weaponCard == 0)
              continue;
          gameTable()->playerDiscardCard(card);
        }
      }
      // Move target card to the player
      //Vianoce
      if (targetCard->pocket() == POCKET_TABLE)
      gameTable()->passTableCard(targetCard , targetPlayer);
      else if (targetCard->pocket() == POCKET_HAND)
      gameTable()->playerStealCard(targetPlayer , targetCard);
      else throw BadCardException();

    }
    else{
    m_targetCard = targetCard;
    play(targetPlayer);
    }
}

void CardTaker::play( PlayingCard* targetCard , PlayingCard* targetCard2 ){
    if (m_type == Gift){ play( targetCard , targetCard2->owner()); }
    else{
    m_targetCard = targetCard;
    play(targetCard2);
    }
}


void CardTaker::play(Player* targetPlayer )
{
    gameCycle()->assertTurn();
    if (m_type == cancan || m_type == conestoga) {
        assertOnTable();
            if ( this->greenready() == 0)
                throw BadCardException();
     }
    else {assertInHand();}

    /* allow steel from himself only if has more than one card in hand */
    if (owner() == targetPlayer && owner()->handSize() < 2)
        throw BadTargetPlayerException();

    
    PlayingCard* targetCard;

    do {
        targetCard = targetPlayer->getRandomCardFromHand();
    } while (targetCard == this); // pick other than this card

    if (targetCard == 0)
        throw BadTargetPlayerException();

     play(targetCard);
}

void CardTaker::play(PlayingCard* targetCard )
{

    gameCycle()->assertTurn();
    if (m_type == cancan || m_type == conestoga) {
        assertOnTable();
            if ( this->greenready() == 0)
                throw BadCardException();
     }
    else {assertInHand();}


    Player* o = owner();

    if (m_type == Panic || m_type == conestoga || m_type == RagTime) {
        /* distance check */
        if (game()->getDistance(owner(), targetCard->owner()) > 1 && m_type == Panic)
            throw PlayerOutOfRangeException();
        gameCycle()->setCardEffect(1);
        if (m_targetCard != 0)
         gameTable()->playerDiscardCard(m_targetCard);
        gameTable()->playerPlayCard(this, targetCard);
        gameTable()->playerStealCard(o, targetCard);
        gameCycle()->setCardEffect(0);
    } else {
        gameCycle()->setCardEffect(1);
        if (m_targetCard != 0)
         gameTable()->playerDiscardCard(m_targetCard);
        gameTable()->playerPlayCard(this, targetCard);
        gameTable()->cancelCard(targetCard, o);
        gameCycle()->setCardEffect(0);
    }
}

