#ifndef GREENBEER_H
#define GREENBEER_H


#include "tablecard.h"
class Player;

class GreenBeer : public TableCard
{
Q_OBJECT;
public:

    GreenBeer(Game *game, int id,  CardSuit, CardRank);
    ~GreenBeer();

    virtual void play();
    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);


};
#endif // CARDMUSTANG_H
