#include "characterchuckwengam.h"
#include "player.h"
#include "gamecycle.h"
#include "gametable.h"


CharacterChuckWengam::CharacterChuckWengam(QObject* parent):
        CharacterBase(parent, CHARACTER_CHUCK_WENGAM)
{
}

void CharacterChuckWengam::useAbility()
{
 if (gameCycle().gamePlayState() == GAMEPLAYSTATE_TURN && gameCycle().currentPlayer() == mp_player && mp_player->lifePoints() > 0 ) {
  notifyAbilityUse();
  mp_player->modifyLifePoints(-1, mp_player);
  gameTable().playerDrawFromDeck(mp_player, 2, 0);
 }
}

