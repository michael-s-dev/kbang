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

    bool bluecard = false ;
    foreach (PlayingCard* card, cards) {
    if (card->type() == CARD_APPALOSSA || card->type() == CARD_BARREL ||
            card->type() == CARD_DYNAMITE || card->type() == CARD_JAIL|| card->type() == CARD_MUSTANG || card->type() == CARD_VOLCANIC ||
            card->type() == CARD_REMINGTON || card->type() == CARD_CARABINE ||
            card->type() == CARD_WINCHESTER || card->type() == CARD_SCHOFIELD || card->type() == CARD_DEAGLE || card->type() == CARD_RIPARO)

        bluecard = true ;

   }

    foreach (PlayingCard* card, cards) {
        if (card->owner() != mp_player || card->pocket() != POCKET_HAND || bluecard == false  )
            throw BadCardException();
    }

    if (gameCycle().gamePlayState() == GAMEPLAYSTATE_TURN &&
        gameCycle().currentPlayer() == mp_player) {
        notifyAbilityUse();
        foreach (PlayingCard* card, cards) {
            gameTable().playerDiscardCard(card);
        }
        gameTable().playerDrawFromDeck(mp_player, 2, 0);
        return;
    }

    if (gameCycle().gamePlayState() == GAMEPLAYSTATE_RESPONSE &&
        gameCycle().requestedPlayer() == mp_player &&
        gameCycle().reactionHandler()->reactionType() == REACTION_LASTSAVE) {
        notifyAbilityUse();
        foreach (PlayingCard* card, cards) {
            gameTable().playerDiscardCard(card);
        }
        gameCycle().reactionHandler()->dismiss();
        return;
    }
    throw BadGameStateException();
}
