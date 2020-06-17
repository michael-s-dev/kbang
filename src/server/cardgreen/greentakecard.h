#ifndef GREENTAKECARD_H
#define GREENTAKECARD_H


#include "tablecard.h"
class Player;

class GreenTakeCard : public TableCard
{
Q_OBJECT;
public:
    enum Type{
        conestoga,
        cancan
    };

    GreenTakeCard(Game *game, int id,  CardSuit, CardRank , Type type);
    ~GreenTakeCard();

    virtual void play();
    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);

private:
    Type m_type;
};

#endif
