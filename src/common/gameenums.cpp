/***************************************************************************
 *   Copyright (C) 2009 by MacJariel                                       *
 *   MacJariel (at) gmail.com                                              *
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

#include "gameenums.h"
#include "util.h"


CardSuit stringToCardSuit(const QString& s)
{
    if (s == "spades")      return SUIT_SPADES;
    if (s == "hearts")      return SUIT_HEARTS;
    if (s == "diamonds")    return SUIT_DIAMONDS;
    if (s == "clubs")       return SUIT_CLUBS;
    return SUIT_SPADES;
}

QString cardSuitToString(const CardSuit& suit)
{
    switch(suit) {
        case SUIT_SPADES:   return "spades";
        case SUIT_HEARTS:   return "hearts";
        case SUIT_DIAMONDS: return "diamonds";
        case SUIT_CLUBS:    return "clubs";
    }
    return "";
}

CharacterType stringToCharacterType(const QString& s)
{
    if (s == "slab the killer") return CHARACTER_SLAB_THE_KILLER;
    if (s == "lucky duke")      return CHARACTER_LUCKY_DUKE;
    if (s == "suzy lafayette")  return CHARACTER_SUZY_LAFAYETTE;
    if (s == "vulture sam")     return CHARACTER_VULTURE_SAM;
    if (s == "black jack")      return CHARACTER_BLACK_JACK;
    if (s == "sid ketchum")     return CHARACTER_SID_KETCHUM;
    if (s == "jourdonnais")     return CHARACTER_JOURDONNAIS;
    if (s == "el gringo")       return CHARACTER_EL_GRINGO;
    if (s == "kit carlson")     return CHARACTER_KIT_CARLSON;
    if (s == "jesse jones")     return CHARACTER_JESSE_JONES;
    if (s == "pedro ramirez")   return CHARACTER_PEDRO_RAMIREZ;
    if (s == "calamity janet")  return CHARACTER_CALAMITY_JANET;
    if (s == "rose doolan")     return CHARACTER_ROSE_DOOLAN;
    if (s == "bart cassidy")    return CHARACTER_BART_CASSIDY;
    if (s == "paul regret")     return CHARACTER_PAUL_REGRET;
    if (s == "willy the kid")   return CHARACTER_WILLY_THE_KID;
    if (s == "jose delgado")    return CHARACTER_JOSE_DELGADO;
    if (s == "dr. king schultz") return CHARACTER_KING_SCHULTZ;
    if (s == "chuck wengam")    return CHARACTER_CHUCK_WENGAM;
    if (s == "pat brennan")     return CHARACTER_PAT_BRENNAN;
    if (s == "tequila joe")     return CHARACTER_TEQUILA_JOE;
    if (s == "bill noface")     return CHARACTER_BILL_NOFACE;
    if (s == "sean mallory")    return CHARACTER_SEAN_MALLORY;
    if (s == "herb hunter")     return CHARACTER_HERB_HUNTER;
    if (s == "greg digger")     return CHARACTER_GREG_DIGGER;
    if (s == "elena fuente")    return CHARACTER_ELENA_FUENTE;
    if (s == "molly stark")     return CHARACTER_MOLLY_STARK;
    if (s == "doc holyday")     return CHARACTER_DOC_HOLYDAY;
    if (s == "apache kid")      return CHARACTER_APACHE_KID;
    if (s == "belle star")      return CHARACTER_BELLE_STAR;
    if (s == "tuco")            return CHARACTER_TUCO;
    return CHARACTER_UNKNOWN;
}

QString characterTypeToString(const CharacterType& t)
{
    switch(t) {
    case CHARACTER_UNKNOWN:         return "unknown";
    case CHARACTER_SLAB_THE_KILLER: return "slab the killer";
    case CHARACTER_LUCKY_DUKE:      return "lucky duke";
    case CHARACTER_SUZY_LAFAYETTE:  return "suzy lafayette";
    case CHARACTER_VULTURE_SAM:     return "vulture sam";
    case CHARACTER_BLACK_JACK:      return "black jack";
    case CHARACTER_SID_KETCHUM:     return "sid ketchum";
    case CHARACTER_JOURDONNAIS:     return "jourdonnais";
    case CHARACTER_EL_GRINGO:       return "el gringo";
    case CHARACTER_KIT_CARLSON:     return "kit carlson";
    case CHARACTER_JESSE_JONES:     return "jesse jones";
    case CHARACTER_PEDRO_RAMIREZ:   return "pedro ramirez";
    case CHARACTER_CALAMITY_JANET:  return "calamity janet";
    case CHARACTER_ROSE_DOOLAN:     return "rose doolan";
    case CHARACTER_BART_CASSIDY:    return "bart cassidy";
    case CHARACTER_PAUL_REGRET:     return "paul regret";
    case CHARACTER_WILLY_THE_KID:   return "willy the kid";
    case CHARACTER_JOSE_DELGADO:    return "jose delgado";
    case CHARACTER_KING_SCHULTZ:    return "dr. king schultz";
    case CHARACTER_CHUCK_WENGAM:    return "chuck wengam";
    case CHARACTER_PAT_BRENNAN:     return "pat brennan";
    case CHARACTER_TEQUILA_JOE:     return "tequila joe";
    case CHARACTER_BILL_NOFACE:     return "bill noface";
    case CHARACTER_SEAN_MALLORY:    return "sean mallory";
    case CHARACTER_HERB_HUNTER:     return "herb hunter";
    case CHARACTER_GREG_DIGGER:     return "greg digger";
    case CHARACTER_ELENA_FUENTE:    return "elena fuente";
    case CHARACTER_MOLLY_STARK:     return "molly stark";
    case CHARACTER_DOC_HOLYDAY:     return "doc holyday";
    case CHARACTER_BELLE_STAR:      return "belle star";
    case CHARACTER_APACHE_KID:      return "apache kid";
    case CHARACTER_TUCO:            return "tuco";
    }
    return "unknown";
}

PlayingCardType stringToPlayingCardType(const QString& s)
{
    if (s == "bang")             return CARD_BANG;
    if (s == "missed")           return CARD_MISSED;
    if (s == "beer")             return CARD_BEER;
    if (s == "saloon")           return CARD_SALOON;
    if (s == "wellsfargo")       return CARD_WELLSFARGO;
    if (s == "diligenza")        return CARD_DILIGENZA;
    if (s == "generalstore")     return CARD_GENERALSTORE;
    if (s == "panic")            return CARD_PANIC;
    if (s == "catbalou")         return CARD_CATBALOU;
    if (s == "indians")          return CARD_INDIANS;
    if (s == "duel")             return CARD_DUEL;
    if (s == "gatling")          return CARD_GATLING;
    if (s == "mustang")          return CARD_MUSTANG;
    if (s == "appalossa")        return CARD_APPALOSSA;
    if (s == "riparo")           return CARD_RIPARO;
    if (s == "barrel")           return CARD_BARREL;
    if (s == "dynamite")         return CARD_DYNAMITE;
    if (s == "jail")             return CARD_JAIL;
    if (s == "volcanic")         return CARD_VOLCANIC;
    if (s == "schofield")        return CARD_SCHOFIELD;
    if (s == "remington")        return CARD_REMINGTON;
    if (s == "carabine")         return CARD_CARABINE;
    if (s == "winchester")       return CARD_WINCHESTER;
    if (s == "deagle")           return CARD_DEAGLE;
    if (s == "schivata")         return CARD_SCHIVATA;
    if (s == "pugno")            return CARD_PUGNO;
    if (s == "cappello")         return CARD_SOMBRERO;
    if (s == "placca di ferro")  return CARD_PLACCA_DI_FERRO;
    if (s == "bibbia")           return CARD_BIBBIA;
    if (s == "pony express")     return CARD_PONY_EXPRESS;
    if (s == "borraccia")        return CARD_BORRACCIA;
    if (s == "conestoga")        return CARD_CONESTOGA;
    if (s == "can can")          return CARD_CAN_CAN;
    if (s == "fucile da caccia") return CARD_FUCILE_DA_CACCIA;
    if (s == "derringer")        return CARD_DERRINGER;
    if (s == "pugnale")          return CARD_PUGNALE;
    if (s == "pepperbox")        return CARD_PEPPERBOX;
    if (s == "howitzer")         return CARD_HOWITZER;
    if (s == "rag time")         return CARD_RAG_TIME;
    if (s == "tequila")          return CARD_TEQUILA;
    if (s == "rissa")            return CARD_RISSA;
    if (s == "springfield")      return CARD_SPRINGFIELD;
    if (s == "whisky")           return CARD_WHISKY;
    if (s == "gift")             return CARD_GIFT;
    return CARD_UNKNOWN;
}

QString playingCardTypeToString(const PlayingCardType& c)
{
    switch(c) {
        case CARD_BANG:           return "bang";
        case CARD_MISSED:         return "missed";
        case CARD_BEER:           return "beer";
        case CARD_SALOON:         return "saloon";
        case CARD_WELLSFARGO:     return "wellsfargo";
        case CARD_DILIGENZA:      return "diligenza";
        case CARD_GENERALSTORE:   return "generalstore";
        case CARD_PANIC:          return "panic";
        case CARD_CATBALOU:       return "catbalou";
        case CARD_INDIANS:        return "indians";
        case CARD_DUEL:           return "duel";
        case CARD_GATLING:        return "gatling";
        case CARD_MUSTANG:        return "mustang";
        case CARD_RIPARO:         return "riparo";
        case CARD_APPALOSSA:      return "appalossa";
        case CARD_BARREL:         return "barrel";
        case CARD_DYNAMITE:       return "dynamite";
        case CARD_JAIL:           return "jail";
        case CARD_VOLCANIC:       return "volcanic";
        case CARD_SCHOFIELD:      return "schofield";
        case CARD_REMINGTON:      return "remington";
        case CARD_CARABINE:       return "carabine";
        case CARD_WINCHESTER:     return "winchester";
        case CARD_DEAGLE:         return "deagle";
        case CARD_PUGNO:          return "pugno";
        case CARD_SCHIVATA:       return "schivata";
        case CARD_SOMBRERO:       return "cappello";
        case CARD_PLACCA_DI_FERRO:return "placca di ferro";
        case CARD_BIBBIA:         return "bibbia";
        case CARD_PONY_EXPRESS:   return "pony express";
        case CARD_BORRACCIA:      return "borraccia";
        case CARD_CONESTOGA:      return "conestoga";
        case CARD_CAN_CAN:        return "can can";
        case CARD_FUCILE_DA_CACCIA:return "fucile da caccia";
        case CARD_DERRINGER:      return "derringer";
        case CARD_PUGNALE:        return "pugnale";
        case CARD_PEPPERBOX:      return "pepperbox";
        case CARD_HOWITZER:       return "howitzer";
        case CARD_RAG_TIME:       return "rag time";
        case CARD_TEQUILA:        return "tequila";
        case CARD_RISSA:          return "rissa";
        case CARD_SPRINGFIELD:    return "springfield";
        case CARD_WHISKY:         return "whisky";
        case CARD_GIFT:           return "gift";
        case CARD_UNKNOWN:        return "";
    }
    return "";
}

PlayerRole stringToPlayerRole(const QString& s)
{
    if (s == "unknown")  return ROLE_UNKNOWN;
    if (s == "outlaw")   return ROLE_OUTLAW;
    if (s == "deputy")   return ROLE_DEPUTY;
    if (s == "sheriff")  return ROLE_SHERIFF;
    if (s == "renegade") return ROLE_RENEGADE;
    return ROLE_INVALID;
}

QString playerRoleToString(const PlayerRole& r)
{
    if (r == ROLE_UNKNOWN)  return "unknown";
    if (r == ROLE_OUTLAW)   return "outlaw";
    if (r == ROLE_DEPUTY)   return "deputy";
    if (r == ROLE_SHERIFF)  return "sheriff";
    if (r == ROLE_RENEGADE) return "renegade";
    if (r == ROLE_INVALID)  return "invalid";
    NOT_REACHED();
    return "invalid";
}


GamePlayState stringToGamePlayState(const QString& s)
{
    if (s == "draw")     return GAMEPLAYSTATE_DRAW;
    if (s == "turn")     return GAMEPLAYSTATE_TURN;
    if (s == "response") return GAMEPLAYSTATE_RESPONSE;
    if (s == "discard")  return GAMEPLAYSTATE_DISCARD;
    return GAMEPLAYSTATE_INVALID;
}

QString gamePlayStateToString(const GamePlayState& s)
{
    if (s == GAMEPLAYSTATE_DRAW)     return "draw";
    if (s == GAMEPLAYSTATE_TURN)     return "turn";
    if (s == GAMEPLAYSTATE_RESPONSE) return "response";
    if (s == GAMEPLAYSTATE_DISCARD)  return "discard";
    if (s == GAMEPLAYSTATE_INVALID)  return "invalid";
    NOT_REACHED();
    return "invalid";
}

ReactionType stringToReactionType(const QString& s)
{
    if (s == "bang")            return REACTION_BANG;
    if (s == "gatling")         return REACTION_GATLING;
    if (s == "indians")         return REACTION_INDIANS;
    if (s == "duel")            return REACTION_DUEL;
    if (s == "general-store")   return REACTION_GENERALSTORE;
    if (s == "last-save")       return REACTION_LASTSAVE;
    if (s == "lucky-duke")      return REACTION_LUCKYDUKE;
    if (s == "kit-carlson")     return REACTION_KITCARLSON;
    if (s == "howitzer")        return REACTION_HOWITZER;
    if (s == "pugno")           return REACTION_PUGNO;
    if (s == "pugnale")         return REACTION_PUGNALE;

    return REACTION_NONE;
}

QString reactionTypeToString(const ReactionType& r)
{
    switch(r) {
    case REACTION_BANG:         return "bang";
    case REACTION_GATLING:      return "gatling";
    case REACTION_INDIANS:      return "indians";
    case REACTION_DUEL:         return "duel";
    case REACTION_GENERALSTORE: return "general-store";
    case REACTION_LASTSAVE:     return "last-save";
    case REACTION_LUCKYDUKE:    return "lucky-duke";
    case REACTION_KITCARLSON:   return "kit-carlson";
    case REACTION_HOWITZER:     return "howitzer";
    case REACTION_PUGNALE:      return "pugnale";
    case REACTION_PUGNO:        return "pugno";
    case REACTION_NONE:         return "";
    }
    return "";
}

PocketType stringToPocketType(const QString& s)
{
    if (s == "deck")      return POCKET_DECK;
    if (s == "graveyard") return POCKET_GRAVEYARD;
    if (s == "hand")      return POCKET_HAND;
    if (s == "table")     return POCKET_TABLE;
    if (s == "selection") return POCKET_SELECTION;
    return POCKET_INVALID;
}

QString pocketTypeToString(const PocketType& p)
{
    if (p == POCKET_DECK)       return "deck";
    if (p == POCKET_GRAVEYARD)  return "graveyard";
    if (p == POCKET_HAND)       return "hand";
    if (p == POCKET_TABLE)      return "table";
    if (p == POCKET_SELECTION)  return "selection";
    return "";
}


GameState stringToGameState(const QString& s)
{
    if (s == "WaitingForPlayers")   return GAMESTATE_WAITINGFORPLAYERS;
    if (s == "Playing")             return GAMESTATE_PLAYING;
    if (s == "Finished")            return GAMESTATE_FINISHED;
    return GAMESTATE_INVALID;
}

QString gameStateToString(const GameState& s)
{
    switch(s) {
    case GAMESTATE_WAITINGFORPLAYERS:   return "WaitingForPlayers";
    case GAMESTATE_PLAYING:             return "Playing";
    case GAMESTATE_FINISHED:            return "Finished";
    default:                            break;
    }
    return "Invalid";
}

ClientType stringToClientType(const QString& s) {
    if (s == "player") return CLIENT_PLAYER;
    else return CLIENT_SPECTATOR;
}

QString clientTypeToString(const ClientType& t) {
    switch(t) {
    case CLIENT_PLAYER:     return "player";
    case CLIENT_SPECTATOR:  return "spectator";
    }
    return "";
}

GameMessageType stringToGameMessageType(const QString& s) {
    if (s == "game-started")                return GAMEMESSAGE_GAMESTARTED;
    if (s == "game-finished")               return GAMEMESSAGE_GAMEFINISHED;
    if (s == "player-draw-from-deck")       return GAMEMESSAGE_PLAYERDRAWFROMDECK;
    if (s == "player-draw-from-graveyard")  return GAMEMESSAGE_PLAYERDRAWFROMGRAVEYARD;
    if (s == "player-discard-card")         return GAMEMESSAGE_PLAYERDISCARDCARD;
    if (s == "player-play-card")            return GAMEMESSAGE_PLAYERPLAYCARD;
    if (s == "player-respond-with-card")    return GAMEMESSAGE_PLAYERRESPONDWITHCARD;
    if (s == "player-pass")                 return GAMEMESSAGE_PLAYERPASS;
    if (s == "player-pick-from-selection")  return GAMEMESSAGE_PLAYERPICKFROMSELECTION;
    if (s == "player-check-deck")           return GAMEMESSAGE_PLAYERCHECKDECK;
    if (s == "player-steal-card")           return GAMEMESSAGE_PLAYERSTEALCARD;
    if (s == "player-cancel-card")          return GAMEMESSAGE_PLAYERCANCELCARD;
    if (s == "deck-regenerate")             return GAMEMESSAGE_DECKREGENERATE;
    if (s == "player-died")                 return GAMEMESSAGE_PLAYERDIED;
    if (s == "pass-table-card")             return GAMEMESSAGE_PASSTABLECARD;
    return GAMEMESSAGE_INVALID;
}

QString gameMessageTypeToString(const GameMessageType& g) {
    switch(g) {
    case GAMEMESSAGE_GAMESTARTED:               return "game-started";
    case GAMEMESSAGE_GAMEFINISHED:              return "game-finished";
    case GAMEMESSAGE_PLAYERDRAWFROMDECK:        return "player-draw-from-deck";
    case GAMEMESSAGE_PLAYERDRAWFROMGRAVEYARD:   return "player-draw-from-graveyard";
    case GAMEMESSAGE_PLAYERDISCARDCARD:         return "player-discard-card";
    case GAMEMESSAGE_PLAYERPLAYCARD:            return "player-play-card";
    case GAMEMESSAGE_PLAYERRESPONDWITHCARD:     return "player-respond-with-card";
    case GAMEMESSAGE_PLAYERPASS:                return "player-pass";
    case GAMEMESSAGE_PLAYERPICKFROMSELECTION:   return "player-pick-from-selection";
    case GAMEMESSAGE_PLAYERCHECKDECK:           return "player-check-deck";
    case GAMEMESSAGE_PLAYERSTEALCARD:           return "player-steal-card";
    case GAMEMESSAGE_PLAYERCANCELCARD:          return "player-cancel-card";
    case GAMEMESSAGE_DECKREGENERATE:            return "deck-regenerate";
    case GAMEMESSAGE_PLAYERDIED:                return "player-died";
    case GAMEMESSAGE_PASSTABLECARD:             return "pass-table-card";
    case GAMEMESSAGE_INVALID:                   return "";
    }
    return "";
}

