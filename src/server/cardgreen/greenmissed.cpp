#include "greenmissed.h"
#include "gameexceptions.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"


GreenMissed::GreenMissed(Game *game, int id, GreenMissed::MissType missType, CardSuit suit, CardRank rank):
       PlayingCard(game, id, CARD_UNKNOWN, suit, rank),
        m_missType(missType)
{
    switch(m_missType) {
    case sombrero:
        setType(CARD_SOMBRERO);
        break;
    case placcadiferro:
        setType(CARD_PLACCA_DI_FERRO);
        break;
    case bibbia:
        setType(CARD_BIBBIA);
        break;
}
}

GreenMissed::~GreenMissed()
{
}

void GreenMissed::play()
{
    gameCycle()->assertTurn();
    assertInHand();
    if (owner()->hasIdenticalCardOnTable(this)) {
        throw TwoSameOnTableException();
    }
    gameTable()->playerPlayCardOnTable(this);
    this->setGreenReady(false);
}


void GreenMissed::registerPlayer(Player*)
{
}

void GreenMissed::unregisterPlayer(Player*)
{
}






