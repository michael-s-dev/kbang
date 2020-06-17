#include "greendrawcards.h"
#include "gameexceptions.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"


GreenDrawCards::GreenDrawCards(Game *game, int id, CardSuit suit, CardRank rank):
        TableCard(game, id, CARD_PONY_EXPRESS, suit, rank)
{
}


GreenDrawCards::~GreenDrawCards()
{
}

void GreenDrawCards::play()
{

    gameCycle()->assertTurn();

    if ( this->pocket() == POCKET_HAND) {
        if (owner()->hasIdenticalCardOnTable(this)) {
            throw TwoSameOnTableException();
        }
        gameTable()->playerPlayCardOnTable(this);
        this->setGreenReady(false);
    }
    else if ( this->greenready() == 1){
        assertOnTable();
        Player* player = owner();
        gameCycle()->setCardEffect(1);
        gameTable()->playerPlayCard(this);
        gameTable()->playerDrawFromDeck(player, 3);
        gameCycle()->setCardEffect(0);
    }
     throw BadUsageException(); // prevent voidai from infinite circle
}



void GreenDrawCards::registerPlayer(Player*)
{
}

void GreenDrawCards::unregisterPlayer(Player*)
{
}






