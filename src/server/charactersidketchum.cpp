#include "charactersidketchum.h"
#include "gamecycle.h"
#include "gametable.h"
#include "gameexceptions.h"
#include "player.h"
#include "playingcard.h"
#include "reactioncard.h"
#include "reactionhandler.h"
#include "cardbang.h"


CharacterSidKetchum::CharacterSidKetchum(QObject *parent , Type type):
        CharacterBase(parent, CHARACTER_UNKNOWN),
        m_type(type),
        mp_bang(0)
{
        if (type == DocHoliday )
            setCharacterType(CHARACTER_DOC_HOLYDAY);
        else
            setCharacterType(CHARACTER_SID_KETCHUM);

}


void CharacterSidKetchum::useAbility(QList<PlayingCard*> cards , Player* targetPlayer){

    if (cards.size() != 2)
        throw BadCardException();

    foreach (PlayingCard* card, cards) {
        card->assertInHand();
    }


    if (gameCycle().gamePlayState() == GAMEPLAYSTATE_TURN &&
        gameCycle().currentPlayer() == mp_player &&
        mp_player->canUseAbility()) {
            notifyAbilityUse();

            if (!mp_bang) {
                mp_bang = new CardBang(mp_player->game(), 0 , SUIT_SPADES,  9 , CardBang::bang);
            }
            mp_bang->setVirtual(cards[1]);

            try {
               gameCycle().playCard(mp_player, mp_bang , targetPlayer);
            } catch (...) {
                return;
            }
            gameTable().playerDiscardCard(cards[0]);
            mp_player->onAbilityUsed();

        }
}



void CharacterSidKetchum::useAbility(QList<PlayingCard*> cards)
{
    if (cards.size() != 2)
        throw BadCardException();


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




