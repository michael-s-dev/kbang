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
    mp_targetCard = targetPlayer->getRandomCardFromHand();
    if (mp_targetCard == 0)
        throw BadTargetPlayerException();
    gameCycle().draw(mp_player, 1);
}

void CharacterJesseJones::useAbility(QList<PlayingCard*> cards)
{
    mp_targetCard = cards[0];
    // Avoid server crash if invalid card selected
    if (cards.size() != 1)
        throw BadCardException();
    // Check pocket
    if ( mp_targetCard->pocket() != POCKET_TABLE)
        throw BadTargetCardException();

    gameCycle().draw(mp_player, 1);
}

void CharacterJesseJones::draw(bool specialDraw)
{
    if (specialDraw) {
        if (m_type == JesseJones) {
            notifyAbilityUse();
            gameTable().playerStealCard(mp_player, mp_targetCard);
            gameTable().playerDrawFromDeck(mp_player, 1, 0);
        }
        else if (m_type == PatBrennan){
            notifyAbilityUse();
            gameTable().playerStealCard(mp_player, mp_targetCard);
        }
    } else {
        CharacterBase::draw(0);
    }
}
