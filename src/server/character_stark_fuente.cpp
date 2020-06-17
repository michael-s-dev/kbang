#include "character_stark_fuente.h"
#include "player.h"
#include "playingcard.h"
#include "gameexceptions.h"
#include "cardbang.h"
#include "cardmissed.h"
#include "gametable.h"



CharacterStarkFuente::CharacterStarkFuente(QObject *parent , Type type):
        CharacterBase(parent, CHARACTER_UNKNOWN),
        mp_missed(0),
        m_type(type)
    {
        if (type == ElenaFuente)
            setCharacterType(CHARACTER_ELENA_FUENTE);
        else if (type == MollyStark)
            setCharacterType(CHARACTER_MOLLY_STARK);

    }


int CharacterStarkFuente::maxLifePoints() const
{
    if (m_type == MollyStark)
        return 4;
    else
        return 3;

}


void CharacterStarkFuente::respondCard(ReactionHandler* reactionHandler, PlayingCard* targetCard)
{
   if ( m_type == ElenaFuente ) {
    try {
        reactionHandler->respondCard(targetCard);
    } catch (BadCardException& e) {
        PlayingCard* swapped = swapCards(targetCard);
        if (swapped) {
            reactionHandler->respondCard(swapped);
            notifyAbilityUse();
        } else {
            throw e;
        }
     }
   }
   else if ( m_type == MollyStark){

       try {
           reactionHandler->respondCard(targetCard);
           if ( targetCard->type() != CARD_BARREL && targetCard->owner() != mp_player)
            gameTable().playerDrawFromDeck(mp_player, 1, 0);
           notifyAbilityUse();
       }
       catch (BadCardException& e)
       {
         throw e;
       }



  }
 }


PlayingCard* CharacterStarkFuente::swapCards(PlayingCard* card)
{

        if (!mp_missed)
            mp_missed = new CardMissed(mp_player->game(), 0, SUIT_CLUBS, 2 , CardMissed::miss);
        mp_missed->setVirtual(card);
        return mp_missed;

}
