#include "characterjosedelgado.h"
#include "gamecycle.h"
#include "gametable.h"
#include "gameexceptions.h"
#include "player.h"
#include "playingcard.h"
#include "reactionhandler.h"


CharacterJoseDelgado::CharacterJoseDelgado(QObject *parent):
        CharacterBase(parent, CHARACTER_JOSE_DELGADO)
{
}


int CharacterJoseDelgado::maxLifePoints() const
{
        return 4;
}
void CharacterJoseDelgado::useAbility(QList<PlayingCard*> cards)
{
    if (cards.size() != 1)
        throw BadCardException();


    foreach (PlayingCard* card, cards) {
        if (card->owner() != mp_player || card->pocket() != POCKET_HAND || card->isBlue() == false  )
            throw BadCardException();
    }

    if (gameCycle().gamePlayState() == GAMEPLAYSTATE_TURN &&
        gameCycle().currentPlayer() == mp_player &&  mp_player->canUseAbility()) {
        notifyAbilityUse();
        foreach (PlayingCard* card, cards) {
            gameTable().playerDiscardCard(card);
        }
        gameTable().playerDrawFromDeck(mp_player, 2, 0);
        mp_player->onAbilityUsed();
        return;
    }

    throw BadGameStateException();
}
