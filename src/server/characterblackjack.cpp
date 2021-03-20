#include "characterblackjack.h"
#include "gametable.h"
#include "playingcard.h"
#include "player.h"


CharacterBlackJack::CharacterBlackJack(QObject* parent, Type type):
    CharacterBase(parent, CHARACTER_UNKNOWN),
    m_type(type)
{
    if (type == BlackJack)
        setCharacterType(CHARACTER_BLACK_JACK);
    else if (type == KingSchultz)
        setCharacterType(CHARACTER_KING_SCHULTZ);
    else if (type == BillNoface)
        setCharacterType(CHARACTER_BILL_NOFACE);
    else if (type == SeanMallory)
        setCharacterType(CHARACTER_SEAN_MALLORY);
    else if (type == Tuco)
        setCharacterType(CHARACTER_TUCO);

}


int CharacterBlackJack::maxLifePoints() const
{
    if (m_type == Tuco)
        return 5;
    else if (m_type == BlackJack || m_type == BillNoface)
        return 4;
    else
        return 3;
}

void CharacterBlackJack::draw(bool)
{
   if (m_type == BlackJack){
    gameTable().playerDrawFromDeck(mp_player, 1, 0);
    QList<const PlayingCard*> cards = gameTable().playerDrawFromDeck(mp_player, 1, 1);
    const PlayingCard* card = cards[0];
    Q_ASSERT(card != 0);
    if (card->suit() == SUIT_HEARTS || card->suit() == SUIT_DIAMONDS) {
        notifyAbilityUse();
        gameTable().playerDrawFromDeck(mp_player, 1, 0);
    }
   }
   else if (m_type == KingSchultz){
      gameTable().playerDrawFromDeck(mp_player, 3, 0);
   }
   else if (m_type == BillNoface){
       int lp = mp_player->lifePoints();
       int maxhp = (mp_player->role() == ROLE_SHERIFF) ? 5 : 4;
       int missing_hp =  maxhp - lp;
       gameTable().playerDrawFromDeck(mp_player, 1 + missing_hp , 0);
   }
   else if (m_type == Tuco) {

       QList<PlayingCard*> cards = mp_player->table();

       bool bluecard = false ;
       foreach (PlayingCard* card, cards)
       {
       if (card->type() == CARD_APPALOSSA || card->type() == CARD_BARREL ||
               card->type() == CARD_DYNAMITE || card->type() == CARD_JAIL|| card->type() == CARD_MUSTANG || card->type() == CARD_VOLCANIC ||
               card->type() == CARD_REMINGTON || card->type() == CARD_CARABINE ||
               card->type() == CARD_WINCHESTER || card->type() == CARD_SCHOFIELD || card->type() == CARD_DEAGLE || card->type() == CARD_RIPARO)

           bluecard = true ;

      }
       if (bluecard == true)
         gameTable().playerDrawFromDeck(mp_player, 2, 0);
        else
         gameTable().playerDrawFromDeck(mp_player, 4, 0);
}
   else {
       gameTable().playerDrawFromDeck(mp_player, 2, 0); // Sean mallory normal draw
   }
}

// Sean mallory ability -> gamecycle::needdiscard
