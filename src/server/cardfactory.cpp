#include "cardfactory.h"
#include "cards.h"

#include <QSet>
#include <cstdlib>

struct CardFactory::CardFactoryImp
{

    void generateCards(Game* game, QMap<int, PlayingCard*>& res)
    {
        QList<PlayingCard*> list;
        //////////
       // BANG //
      //////////
        for (int i = 2; i <= 14; ++i) {
            list.append(new CardBang(game, id(), SUIT_DIAMONDS, i ,CardBang::bang));
        }
        for (int i = 2; i <= 9; ++i) {
            list.append(new CardBang(game, id(), SUIT_CLUBS, i , CardBang::bang));
        }
        for (int i = 12; i <= 14; ++i) {
            list.append(new CardBang(game, id(), SUIT_HEARTS, i , CardBang::bang));
        }
        list.append(new CardBang(game, id(), SUIT_SPADES, 14 , CardBang::bang));
        //Pugno + ext bangs
        list.append(new CardBang(game, id(), SUIT_SPADES, 10 , CardBang::pugno));
        list.append(new CardBang(game, id(), SUIT_CLUBS, 13 , CardBang::bang));
        list.append(new CardBang(game, id(), SUIT_CLUBS, 6 , CardBang::bang));
        list.append(new CardBang(game, id(), SUIT_CLUBS, 5 , CardBang::bang));
        list.append(new CardBang(game, id(), SUIT_SPADES, 8 , CardBang::bang));
        // Green "bangs like card"
        list.append(new CardBang(game, id(), SUIT_CLUBS, 13 , CardBang::fuciledacaccia));
        list.append(new CardBang(game, id(), SUIT_SPADES, 7 , CardBang::derringer));
        list.append(new CardBang(game, id(), SUIT_HEARTS, 8 , CardBang::pugnale));
        list.append(new CardBang(game, id(), SUIT_CLUBS, 10 , CardBang::pepperbox));

        list.append(new CardBang(game, id(), SUIT_SPADES, 13 ,CardBang::springfield));



        ////////////
       // MISSED //
      ////////////
        for (int i = 2; i <= 8; ++i) {
            list.append(new CardMissed(game, id(), SUIT_SPADES, i , CardMissed::miss));
        }
        for (int i = 10; i <= 14; ++i) {
            list.append(new CardMissed(game, id(), SUIT_CLUBS, i , CardMissed::miss));
        }
        list.append(new CardMissed(game, id(), SUIT_DIAMONDS, 8 , CardMissed::miss));

        // Schivata
        list.append(new CardMissed(game, id(), SUIT_HEARTS, 13 , CardMissed::schivata));
        list.append(new CardMissed(game, id(), SUIT_DIAMONDS, 7 , CardMissed::schivata));


        list.append(new GreenMissed(game, id(), GreenMissed::placcadiferro ,SUIT_DIAMONDS, 11 ));
        list.append(new GreenMissed(game, id(), GreenMissed::placcadiferro ,SUIT_SPADES, 13 ));
        list.append(new GreenMissed(game, id(), GreenMissed::sombrero ,SUIT_DIAMONDS, 12 ));
        list.append(new GreenMissed(game, id(), GreenMissed::sombrero ,SUIT_CLUBS, 7 ));
        list.append(new GreenMissed(game, id(), GreenMissed::bibbia ,SUIT_HEARTS, 10 ));



        ///////////////////
       // BEER + SALOON //
      ///////////////////
        for (int i = 6; i <= 11; ++i) {
            list.append(new CardBeer(game, id(), SUIT_HEARTS, i, 0));
        }
        list.append(new CardBeer(game, id(), SUIT_HEARTS, 6, 0));
        list.append(new CardBeer(game, id(), SUIT_SPADES, 6, 0));
        list.append(new CardBeer(game, id(), SUIT_HEARTS, 5, 1));
        list.append(new GreenBeer(game, id(), SUIT_HEARTS, 7));

        // Whisky && Tequila

        list.append(new CardBeer(game, id(), SUIT_CLUBS, 9, 0 , CardBeer::tequila));
        list.append(new CardBeer(game, id(), SUIT_HEARTS, 12, 0 , CardBeer::whisky));


        ////////////
       // HORSES //
      ////////////
        list.append(new CardHorse(game, id(), CardHorse::Appaloosa, SUIT_SPADES, 14));
        list.append(new CardHorse(game, id(), CardHorse::Mustang,   SUIT_HEARTS, 8));
        list.append(new CardHorse(game, id(), CardHorse::Mustang,   SUIT_HEARTS, 9));
        list.append(new CardHorse(game, id(), CardHorse::Mustang,   SUIT_HEARTS, 5));
        list.append(new CardHorse(game, id(), CardHorse::Riparo,    SUIT_DIAMONDS, 13));
        // change to binocolo
        list.append(new CardHorse(game, id(), CardHorse::Appaloosa, SUIT_DIAMONDS, 10));

        /////////////
       // WEAPONS //
      /////////////
        list.append(new WeaponCard(game, id(), 1, SUIT_SPADES, 10));
        list.append(new WeaponCard(game, id(), 1, SUIT_CLUBS,  10));
        list.append(new WeaponCard(game, id(), 2, SUIT_CLUBS,  11));
        list.append(new WeaponCard(game, id(), 2, SUIT_CLUBS,  12));
        list.append(new WeaponCard(game, id(), 2, SUIT_SPADES, 13));
        list.append(new WeaponCard(game, id(), 3, SUIT_CLUBS,  13));
        list.append(new WeaponCard(game, id(), 3, SUIT_DIAMONDS, 6));
        list.append(new WeaponCard(game, id(), 4, SUIT_CLUBS,  14));
        list.append(new WeaponCard(game, id(), 4, SUIT_SPADES, 5));
        list.append(new WeaponCard(game, id(), 5, SUIT_SPADES, 8));
        list.append(new WeaponCard(game, id(), 6, SUIT_SPADES, 7));

        ////////////////
       // DRAW CARDS //
      ////////////////
        list.append(new CardDrawCards(game, id(), CardDrawCards::Diligenza,  SUIT_SPADES,  9));
        list.append(new CardDrawCards(game, id(), CardDrawCards::Diligenza,  SUIT_SPADES,  9));
        list.append(new CardDrawCards(game, id(), CardDrawCards::WellsFargo, SUIT_HEARTS,  3));
        list.append(new GreenDrawCards(game, id(), SUIT_DIAMONDS, 13));



        ////////////////
       // MULTISHOOT //
      ////////////////
        list.append(new CardMultiShoot(game, id(), CardMultiShoot::Indians, SUIT_DIAMONDS,  13));
        list.append(new CardMultiShoot(game, id(), CardMultiShoot::Indians, SUIT_DIAMONDS,  14));
        list.append(new CardMultiShoot(game, id(), CardMultiShoot::Indians, SUIT_DIAMONDS,  5));
        list.append(new CardMultiShoot(game, id(), CardMultiShoot::Gatling, SUIT_HEARTS,    10));
        // Green howitzer

        list.append(new CardMultiShoot(game, id(), CardMultiShoot::Howitzer, SUIT_SPADES,  9));


        //////////
       // DUEL //
      //////////
        list.append(new CardDuel(game, id(), SUIT_CLUBS,    8 ));
        list.append(new CardDuel(game, id(), SUIT_SPADES,   11));
        list.append(new CardDuel(game, id(), SUIT_DIAMONDS, 12));


        list.append(new CardGeneralStore(game, id(), SUIT_SPADES, 12));
        list.append(new CardGeneralStore(game, id(), SUIT_CLUBS, 9));
        list.append(new CardGeneralStore(game, id(), SUIT_SPADES, 14));

        list.append(new CardJail(game, id(), SUIT_SPADES, 10));
        list.append(new CardJail(game, id(), SUIT_SPADES, 11));
        list.append(new CardJail(game, id(), SUIT_HEARTS, 4));

        list.append(new CardDynamite(game, id(), SUIT_HEARTS, 2));
        list.append(new CardDynamite(game, id(), SUIT_CLUBS, 10));

        list.append(new CardTaker(game, id(), CardTaker::Panic, SUIT_DIAMONDS, 8 ));
        list.append(new CardTaker(game, id(), CardTaker::Panic, SUIT_HEARTS,   11));
        list.append(new CardTaker(game, id(), CardTaker::Panic, SUIT_HEARTS,   12));
        list.append(new CardTaker(game, id(), CardTaker::Panic, SUIT_HEARTS,   14));
        list.append(new CardTaker(game, id(), CardTaker::Panic, SUIT_HEARTS,   11));

        list.append(new CardTaker(game, id(), CardTaker::RagTime, SUIT_HEARTS,   9));
        list.append(new CardTaker(game, id(), CardTaker::Gift, SUIT_SPADES,   14));
        list.append(new CardTaker(game, id(), CardTaker::Gift, SUIT_SPADES,   13));


        list.append(new CardTaker(game, id(), CardTaker::CatBalou, SUIT_DIAMONDS, 9 ));
        list.append(new CardTaker(game, id(), CardTaker::CatBalou, SUIT_DIAMONDS, 10));
        list.append(new CardTaker(game, id(), CardTaker::CatBalou, SUIT_DIAMONDS, 11));
        list.append(new CardTaker(game, id(), CardTaker::CatBalou, SUIT_HEARTS,   13));
        list.append(new CardTaker(game, id(), CardTaker::CatBalou, SUIT_CLUBS,   8));

        list.append(new CardMultiShoot(game, id(), CardMultiShoot::Rissa, SUIT_SPADES,   11));

        // Can can && conestoga
        list.append(new CardTaker(game, id(), CardTaker::cancan, SUIT_CLUBS, 11));
        list.append(new CardTaker(game, id(), CardTaker::conestoga, SUIT_DIAMONDS, 9));


        list.append(new CardBarrel(game, id(), SUIT_SPADES, 12));
        list.append(new CardBarrel(game, id(), SUIT_SPADES, 13));
        list.append(new CardBarrel(game, id(), SUIT_CLUBS, 14));

        foreach(PlayingCard* card, list) {
            res[card->id()] = card;
        }
    }


    int id()
    {
        int cardId;
        do {
            cardId = (int)qrand();
        } while(m_ids.contains(cardId));
        m_ids.insert(cardId);
        return cardId;
    }

    QSet<int>   m_ids;
};

CardFactory::CardFactory()
{
    mp_imp = new CardFactoryImp();
}

CardFactory::~CardFactory()
{
    delete mp_imp;
}

QMap<int, PlayingCard*> CardFactory::generateCards(Game* game)
{
    QMap<int, PlayingCard*> res;
    mp_imp->generateCards(game, res);
    return res;

}
