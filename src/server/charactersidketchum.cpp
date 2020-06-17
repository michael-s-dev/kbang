#include "charactersidketchum.h"
#include "gamecycle.h"
#include "gametable.h"
#include "gameexceptions.h"
#include "player.h"
#include "playingcard.h"
#include "reactionhandler.h"
#include "cardbang.h"


CharacterSidKetchum::CharacterSidKetchum(QObject *parent , Type type):
        CharacterBase(parent, CHARACTER_UNKNOWN),
        m_type(type),
        m_virtualbang(0),
        mp_bang(0)
{
        if (type == DocHoliday )
            setCharacterType(CHARACTER_DOC_HOLYDAY);
        else
            setCharacterType(CHARACTER_SID_KETCHUM);

}

void CharacterSidKetchum::useAbility(QList<PlayingCard*> cards)
{
    if (cards.size() != 2)
        throw BadCardException();

    foreach (PlayingCard* card, cards) {
        if (card->owner() != mp_player ||
            card->pocket() != POCKET_HAND)
            swapCards()->play( card->owner());
             throw BadCardException();
    }

    if (gameCycle().gamePlayState() == GAMEPLAYSTATE_TURN &&
        gameCycle().currentPlayer() == mp_player) {
        notifyAbilityUse();
        foreach (PlayingCard* card, cards) {
            gameTable().playerDiscardCard(card);
        }

        mp_player->modifyLifePoints(1, 0);
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

void CharacterSidKetchum::useAbility(Player* targetPlayer){

        swapCards()->play(targetPlayer);

}
PlayingCard* CharacterSidKetchum::swapCards()
{
        if (!mp_bang)
            mp_bang = new CardBang(mp_player->game(), 0, SUIT_CLUBS, 2 , CardBang::pepperbox);
        mp_bang->setVirtual(mp_bang);
        return mp_bang;

}

