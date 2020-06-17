#include "greenbeer.h"
#include "gameexceptions.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"


GreenBeer::GreenBeer(Game *game, int id, CardSuit suit, CardRank rank):
        TableCard(game, id, CARD_BORRACCIA, suit, rank)
{
}

GreenBeer::~GreenBeer()
{
}

void GreenBeer::play()
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
    gameTable()->playerPlayCard(this);
    player->modifyLifePoints(1, 0);
    }
     throw BadUsageException(); // prevent voidai from infinite circle
}



void GreenBeer::registerPlayer(Player*)
{
}

void GreenBeer::unregisterPlayer(Player*)
{
}






