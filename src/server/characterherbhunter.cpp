#include "characterherbhunter.h"
#include "game.h"
#include "gametable.h"


CharacterHerbHunter::CharacterHerbHunter(QObject* parent , Type type):
        CharacterBase(parent, CHARACTER_UNKNOWN),
     m_type(type)
     {
         if (type == HerbHunter)
             setCharacterType(CHARACTER_HERB_HUNTER);
         else if (type == GregDigger)
             setCharacterType(CHARACTER_GREG_DIGGER);
         else if (type == ApacheKid)
             setCharacterType(CHARACTER_APACHE_KID);
     }

int CharacterHerbHunter::maxLifePoints() const
{
    if (m_type == ApacheKid)
        return 3;
    else
        return 4;
}
// Ability - > game ->  burry player
// Apache kid // characterbase -> play card // multishoot
