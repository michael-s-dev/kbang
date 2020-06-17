#ifndef GREENMISSED_H
#define GREENMISSED_H


#include "tablecard.h"

class GreenMissed : public TableCard
{
Q_OBJECT;
public:
    enum MissType {
      sombrero,
      placcadiferro,
      bibbia
    };

    GreenMissed(Game *game, int id, MissType, CardSuit, CardRank);
    ~GreenMissed();

    virtual void play();
    virtual void registerPlayer(Player* player);
    virtual void unregisterPlayer(Player* player);



private:
    MissType m_missType;
};

#endif // CARDMUSTANG_H
