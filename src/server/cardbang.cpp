/***************************************************************************
 *   Copyright (C) 2008 by MacJariel                                       *
 *   echo "badmailet@gbalt.dob" | tr "edibmlt" "ecrmjil"                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "cardbang.h"
#include "player.h"
#include "gamecycle.h"
#include "gameexceptions.h"
#include "gametable.h"
#include "game.h"
#include "cardbarrel.h"
#include "characterbase.h"

CardBang::CardBang(Game* game, int id, CardSuit cardSuit, CardRank cardRank , CardBang::BangType bangType ):
        ReactionCard(game, id, CARD_UNKNOWN, cardSuit, cardRank),
        mp_attackedPlayer(0) ,  m_bangType(bangType)
{

    switch(m_bangType) {
    case pugno:
        setType(CARD_PUGNO);
        break;
    case bang:      
        setType(CARD_BANG);
        break;
    case fuciledacaccia:
        setType(CARD_FUCILE_DA_CACCIA);
        break;
    case derringer:
        setType(CARD_DERRINGER);
        break;
    case pugnale:
        setType(CARD_PUGNALE);
        break;
    case pepperbox:
        setType(CARD_PEPPERBOX);
        break;
    case springfield:
        setType(CARD_SPRINGFIELD);
        break;
    }
}


CardBang::~CardBang()
{
}

ReactionType CardBang::reactionType() const
{
   if (m_bangType == pugno) return REACTION_PUGNO;
   else if (m_bangType == pugnale) return REACTION_PUGNALE;
   else return REACTION_BANG;
}


// Trigger this fucntion when clicked card in hand
void CardBang::play()
    {

        gameCycle()->assertTurn();
        assertInHand();

            if (owner()->hasIdenticalCardOnTable(this)) {
                throw TwoSameOnTableException();
            }
            gameTable()->playerPlayCardOnTable(this);
            this->setGreenReady(false);
}


void CardBang::play(Player *targetPlayer)
{
    gameCycle()->assertTurn();
    if (m_bangType == fuciledacaccia || m_bangType == pepperbox || m_bangType == pugnale || m_bangType == derringer) {
        assertOnTable();
            if ( this->greenready() == 0)
                throw BadCardException();
     }
    else {assertInHand();}

    /* don't allow shoot yourself */
    if (owner() == targetPlayer)
        throw BadTargetPlayerException();

    /* distance check */
    if (game()->getDistance(owner(), targetPlayer) > owner()->weaponRange()){
        if (m_bangType == bang || m_bangType == pepperbox)
            throw PlayerOutOfRangeException();
    }

    /* one-bang-per-turn check */
    if ((!owner()->canPlayBang()) && (m_bangType == bang) && (!this->isVirtual()))
        throw OneBangPerTurnException();

    /*pugno range check*/
    if ( (m_bangType == pugno || m_bangType == pugnale || m_bangType == derringer)  && (game()->getDistance(owner(), targetPlayer) > 1))
        throw PlayerOutOfRangeException();

    if ( (m_bangType == bang) && (!this->isVirtual()) )
        owner()->onBangPlayed();


    mp_attackingPlayer = owner();
    gameTable()->playerPlayCard(this, targetPlayer);
    if (m_bangType == derringer)
        gameTable()->playerDrawFromDeck( mp_attackingPlayer , 1);
    m_usedBarrels.clear();
    mp_attackedPlayer = targetPlayer;
    m_missedLeft = mp_attackingPlayer->bangPower();
    game()->gameCycle().setResponseMode(this, targetPlayer);

}


void CardBang::play(PlayingCard* targetCard , PlayingCard* targetCard2)
{
    Player* targetPlayer = targetCard2->owner();
    play(targetCard , targetPlayer);
}

void CardBang::play(PlayingCard* targetCard , Player *targetPlayer)
{

    gameCycle()->assertTurn();
    assertInHand();
    Player* player = owner();

    if (owner() == targetPlayer)
        throw BadTargetPlayerException();
    if ( m_bangType  == springfield ) {
      if (targetCard->owner() != player || targetCard->pocket() != POCKET_HAND ){
          throw BadCardException();
      }
      mp_attackingPlayer = owner();
      gameTable()->playerDiscardCard(targetCard);
      gameTable()->playerPlayCard(this, targetPlayer);
      m_usedBarrels.clear();
      mp_attackedPlayer = targetPlayer;
      m_missedLeft = 1;
      game()->gameCycle().setResponseMode(this, targetPlayer);
    }
    else{
       throw BadUsageException();
    }
}
void CardBang::respondPass()
{
    Q_ASSERT(mp_attackedPlayer != 0);
    gameCycle()->unsetResponseMode();
    gameTable()->playerPass(mp_attackedPlayer);
    mp_attackedPlayer->modifyLifePoints(-1, mp_attackingPlayer);

}

void CardBang::respondCard(PlayingCard* targetCard)
{
    switch(targetCard->type()) {
    case CARD_MISSED:
    case CARD_SCHIVATA:
        targetCard->assertInHand();
        game()->gameCycle().unsetResponseMode();
        gameTable()->playerRespondWithCard(targetCard);
        missed();
        if (targetCard->type() == CARD_SCHIVATA)
        gameTable()->playerDrawFromDeck(mp_attackedPlayer, 1);
        return;
    case CARD_SOMBRERO:
    case CARD_PLACCA_DI_FERRO:
    case CARD_BIBBIA:{
        if (targetCard->greenready() == 1){
            targetCard->assertOnTable(); // Continue only if on table
            if(mp_attackingPlayer->ignoreTableCards()){ // Belle Star
                 gameTable()->playerDiscardCard(targetCard);
                 return;
            }
            game()->gameCycle().unsetResponseMode();
            gameTable()->playerRespondWithGreenCard(targetCard);
            missed();
        if (targetCard->type() == CARD_BIBBIA)
        gameTable()->playerDrawFromDeck(mp_attackedPlayer, 1);
        return;
        }
        else {
            throw BadCardException();
            return;
        }
    }
    case CARD_BARREL: {
        if (m_usedBarrels.contains(targetCard))
            break;
        if (mp_attackingPlayer->ignoreTableCards()) // belle star
            break;
        targetCard->assertOnTable();
        m_usedBarrels.append(targetCard);
        CardBarrel* barrel = qobject_cast<CardBarrel*>(targetCard);
        barrel->check(this);
        return;
        }
    default:
        break;
    }
    throw BadCardException();
}

void CardBang::checkResult(bool result)
{
    if (result) {
        game()->gameCycle().unsetResponseMode();
        missed();
    }
}

void CardBang::missed()
{
    m_missedLeft--;
    if (m_missedLeft > 0) {
        game()->gameCycle().setResponseMode(this, mp_attackedPlayer);
    }

}


