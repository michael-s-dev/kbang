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
#include "playingcard.h"
#include "gametable.h"
#include "game.h"
#include "gameexceptions.h"
#include "cards.h"

PlayingCard::PlayingCard(Game *game, int id, PlayingCardType type, CardSuit suit, CardRank rank ):
        QObject(game),
        m_id(id),
        m_type(type),
        m_suit(suit),
        m_rank(rank),
        mp_owner(0),
        m_pocket(POCKET_DECK),
        mp_game(game),
        m_isVirtual(0),
        m_greenready(0)
{
}

PlayingCard::~PlayingCard()
{
}

CardData PlayingCard::cardData() const
{
    CardData result;
    if (this != 0) {
        result.id = id();
        result.type = type();
        result.suit = suit();
        result.rank = rank();
    }
    return result;
}


void PlayingCard::play()
{
   throw BadUsageException();
}

void PlayingCard::play(Player* targetPlayer)
{
    Q_UNUSED(targetPlayer);
    throw BadUsageException();
}

void PlayingCard::play(PlayingCard* targetCard)
{
    Q_UNUSED(targetCard);
    throw BadUsageException();
}

void PlayingCard::play(PlayingCard* targetCard , PlayingCard* targetCard2)
{
    Q_UNUSED(targetCard ; targetCard2);
    throw BadUsageException();
}

void PlayingCard::play(PlayingCard* targetCard , Player* targetPlayer)
{
    Q_UNUSED(targetCard ; targetPlayer);
    throw BadUsageException();
}


GameTable* PlayingCard::gameTable() const
{
    return &mp_game->gameTable();
}

GameCycle* PlayingCard::gameCycle() const
{
    return &mp_game->gameCycle();
}

void PlayingCard::assertInHand() const
{
    if (pocket() != POCKET_HAND)
        throw BadCardException();
}

void PlayingCard::assertOnTable() const
{
    if (pocket() != POCKET_TABLE)
        throw BadCardException();
}

void PlayingCard::greenReady() const
{
    if ( m_greenready == 0)
        throw BadCardException();
}

void PlayingCard::setGreenReady( bool greenready)
{
    m_greenready = greenready;
}


void PlayingCard::setVirtual(PlayingCard* master)
{
    mp_master   = master;
    m_isVirtual = 1;
    m_id        = 0;
    m_suit      = master->suit();
    m_rank      = master->rank();
    mp_owner    = master->owner();
    m_pocket    = master->pocket();
    mp_game     = master->game();
}

void PlayingCard::setVirtual(Player* owner, PocketType pocket)
{
    mp_master = 0;
    m_isVirtual = 1;
    m_id = 0;
    mp_owner = owner;
    m_pocket = pocket;
}


void PlayingCard::setType(PlayingCardType type)
{
    m_type = type;
}

bool PlayingCard::isBlue()
{
    switch( this->type()){
    case CARD_VOLCANIC:case CARD_SCHOFIELD:case CARD_REMINGTON:case CARD_CARABINE:
    case CARD_WINCHESTER:case CARD_DEAGLE:case CARD_APPALOSSA: case CARD_BARREL: case CARD_DYNAMITE:
    case CARD_JAIL:case CARD_MUSTANG:case CARD_RIPARO:
        return true;
    default:
        return false;

    }
}

bool PlayingCard::isBangCard() {

    CardBang* bang = qobject_cast<CardBang*>(this);

    if( bang != 0 || this->type() == CARD_DUEL )
        return true;
    else
        return false;

}

