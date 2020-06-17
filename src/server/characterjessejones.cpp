#include "characterjessejones.h"
#include "gametable.h"
#include "gamecycle.h"
#include "player.h"
#include "gameexceptions.h"
#include "playingcard.h"

CharacterJesseJones::CharacterJesseJones(QObject *parent , Type type):
        CharacterBase(parent, CHARACTER_UNKNOWN),
   m_type(type)
  {
      if (type == JesseJones)
          setCharacterType(CHARACTER_JESSE_JONES);
      else if (type == PatBrennan)
          setCharacterType(CHARACTER_PAT_BRENNAN);
  }


void CharacterJesseJones::useAbility(Player* targetPlayer )
{
    mp_targetPlayer = targetPlayer;
    gameCycle().draw(mp_player, 1);
}

void CharacterJesseJones::useAbility(QList<PlayingCard*> cards)
{
    if (cards.size() != 1)  // Avoid server crash if invalid card selected
        throw BadCardException();

    mp_targetCard = cards[0];
    gameCycle().draw(mp_player, 1);
}

void CharacterJesseJones::draw(bool specialDraw)
{
    if (specialDraw) {
        if (m_type == JesseJones) {
            PlayingCard* targetCard = mp_targetPlayer->getRandomCardFromHand();
            if (targetCard == 0)
                throw BadTargetPlayerException();
            notifyAbilityUse();
            gameTable().playerStealCard(mp_player, targetCard);
            gameTable().playerDrawFromDeck(mp_player, 1, 0);
        }
        else if (m_type == PatBrennan){
            if ( mp_targetCard->pocket() != POCKET_TABLE)
                throw BadTargetCardException();
            notifyAbilityUse();
            gameTable().playerStealCard(mp_player, mp_targetCard);
        }
    } else {
        CharacterBase::draw(0);
    }
}
