#ifndef GREENDRAWCARDS_H
#define GREENDRAWCARDS_H


#include "playingcard.h"
class Player;

class GreenDrawCards : public PlayingCard
{
Q_OBJECT;
public:

    GreenDrawCards(Game *game, int id,  CardSuit, CardRank);
    ~GreenDrawCards();

    virtual void play();
    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);


};
#endif
