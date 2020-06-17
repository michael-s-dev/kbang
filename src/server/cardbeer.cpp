#include "cardbeer.h"
#include "player.h"
#include "gametable.h"
#include "gamecycle.h"
#include "game.h"
#include "gameexceptions.h"

CardBeer::CardBeer(Game* game, int id, CardSuit cardSuit, CardRank cardRank, bool isSaloon , CardBeer::BeerType beerType ):
        PlayingCard(game, id, CARD_UNKNOWN, cardSuit, cardRank),
        m_isSaloon(isSaloon),
        m_beerType(beerType)
{
    if (beerType == whisky)
        setType(CARD_WHISKY);
    if (beerType == tequila)
        setType(CARD_TEQUILA);
    if (beerType == beer)
        setType(CARD_BEER);
    if (isSaloon)
        setType(CARD_SALOON);
}


CardBeer::~CardBeer()
{
}

void CardBeer::play()
{
    gameCycle()->assertTurn();
    assertInHand();
    Player* player = owner();
    gameTable()->playerPlayCard(this);
    if (!m_isSaloon) {
        if (game()->alivePlayersCount() > 2){
            if ( player->characterType() == CHARACTER_TEQUILA_JOE )
               player->modifyLifePoints(2, 0);
           else
               player->modifyLifePoints(1, 0);
            }
    }
    else {
        player->modifyLifePoints(1, 0);
        for (Player* p = game()->nextPlayer(player);
             p != player;
             p = game()->nextPlayer(p)) {
            p->modifyLifePoints(1, 0);
        }
    }
}

void CardBeer::play(PlayingCard* targetCard , PlayingCard* targetCard2)
{
    Player* targetPlayer = targetCard2->owner();
    play(targetCard , targetPlayer);
}

void CardBeer::play(PlayingCard* targetCard , Player* targetPlayer)
{

    gameCycle()->assertTurn();
    assertInHand();
    Player* player = owner();

    if ( m_beerType == tequila ) {
      if (targetCard->owner() != player || targetCard->pocket() != POCKET_HAND ){
          throw BadCardException();
      }
      gameTable()->playerDiscardCard(targetCard);
      gameTable()->playerPlayCard(this, targetPlayer);
      targetPlayer->modifyLifePoints(1, 0);
    }
    else{
       throw BadUsageException();
    }
}

void CardBeer::play(PlayingCard* targetCard)
{

    gameCycle()->assertTurn();
    assertInHand();
    Player* player = owner();

    if ( m_beerType == whisky ) {
      if (targetCard->owner() != player || targetCard->pocket() != POCKET_HAND ){
          throw BadCardException();
      }
      gameTable()->playerDiscardCard(targetCard);
      gameTable()->playerPlayCard(this);
      player->modifyLifePoints(2, 0);
    }
    else{
       throw BadUsageException();
    }
}

BeerRescue::BeerRescue(Game* game):
        QObject(game),
        mp_game(game)
{
}

void BeerRescue::respondPass()
{
    mp_game->gameCycle().unsetResponseMode();
    mp_target->lastSaveFailure(m_hitPoints, mp_attacker);
}

void BeerRescue::respondCard(PlayingCard* targetCard)
{
    targetCard->assertInHand();
    if (targetCard->type() == CARD_BEER && mp_game->alivePlayersCount() > 2) {
            mp_game->gameTable().playerPlayCard(targetCard);
            dismiss();
            return;
    }
    throw BadCardException();
}

void BeerRescue::dismiss()
{
    m_lifePointsToSave--;
    if (m_lifePointsToSave == 0) {
        mp_game->gameCycle().unsetResponseMode();
        mp_target->lastSaveSuccess(m_hitPoints, mp_attacker);
    }
}

void BeerRescue::allowSaveWithBeer(Player* attacker, Player* target, int lifePointsToSave, int hitPoints)
{
    mp_attacker = attacker;
    mp_target = target;
    m_lifePointsToSave = lifePointsToSave;
    m_hitPoints = hitPoints;
    mp_game->gameCycle().setResponseMode(this, mp_target);
}
