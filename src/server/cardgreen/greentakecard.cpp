#include "greentakecard.h"
#include "gameexceptions.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"
#include "cardtaker.h"


GreenTakeCard::GreenTakeCard(Game *game, int id, CardSuit suit, CardRank rank , GreenTakeCard::Type type):
       PlayingCard(game, id, CARD_UNKNOWN, suit, rank),
        m_type(type)
{
    if (m_type == conestoga)
        setType(CARD_CONESTOGA);
    else
        setType(CARD_CAN_CAN);
}

GreenTakeCard::~GreenTakeCard()
{
}

void GreenTakeCard::play()
{

    gameCycle()->assertTurn();

    if ( this->pocket() == POCKET_HAND) {
        if (owner()->hasIdenticalCardOnTable(this)) {
            throw TwoSameOnTableException();
        }
        gameTable()->playerPlayCardOnTable(this);
        this->setGreenReady(false);
    }

     throw BadUsageException(); // prevent voidai from infinite circle
}


void GreenTakeCard::registerPlayer(Player*)
{
}

void GreenTakeCard::unregisterPlayer(Player*)
{
}






