#include "characterlist.h"

#include "characterbase.h"
#include "characterblackjack.h"
#include "charactercalamityjanet.h"
#include "charactercassidygringo.h"
#include "characterjessejones.h"
#include "characterjourdonnais.h"
#include "characterkitcarlson.h"
#include "characterluckyduke.h"
#include "characterpedroramirez.h"
#include "characterpropertychange.h"
#include "charactersidketchum.h"
#include "charactersuzylafayette.h"
#include "charactervulturesam.h"
#include "characterjosedelgado.h"
#include "characterchuckwengam.h"
#include "characterherbhunter.h"
#include "character_stark_fuente.h"
#include "util.h"

QList<CharacterType> CharacterList::sm_characterTypes;

CharacterList::CharacterList(QObject* parent, int size):
        QList<CharacterBase*>()
{
    if (sm_characterTypes.size() == 0)
        initCharacterTypes();
    Q_ASSERT(sm_characterTypes.size() != 0);
    shuffleList(sm_characterTypes);
    for (int i = 0; i < size; ++i) {

        append(createCharacter(parent, sm_characterTypes[i % sm_characterTypes.size()]));

    }
}
CharacterBase* CharacterList::createCharacter(QObject* parent, CharacterType type)
{
    switch(type) {
    case CHARACTER_BART_CASSIDY:
        return new CharacterCassidyGringo(parent, CharacterCassidyGringo::BartCassidy);
    case CHARACTER_BLACK_JACK:
        return new CharacterBlackJack(parent , CharacterBlackJack::BlackJack);
    case CHARACTER_CALAMITY_JANET:
        return new CharacterCalamityJanet(parent);
    case CHARACTER_EL_GRINGO:
        return new CharacterCassidyGringo(parent, CharacterCassidyGringo::ElGringo);
    case CHARACTER_JESSE_JONES:
         return new CharacterJesseJones(parent , CharacterJesseJones::JesseJones);
    case CHARACTER_JOURDONNAIS:
        return new CharacterJourdonnais(parent);
    case CHARACTER_KIT_CARLSON:
        return new CharacterKitCarlson(parent);
    case CHARACTER_LUCKY_DUKE:
        return new CharacterLuckyDuke(parent);
    case CHARACTER_PAUL_REGRET:
        return new CharacterPropertyChange(parent, CharacterPropertyChange::PaulRegret);
    case CHARACTER_PEDRO_RAMIREZ:
        return new CharacterPedroRamirez(parent);
    case CHARACTER_ROSE_DOOLAN:
        return new CharacterPropertyChange(parent, CharacterPropertyChange::RoseDoolan);
    case CHARACTER_SID_KETCHUM:
        return new CharacterSidKetchum(parent);
    case CHARACTER_SLAB_THE_KILLER:
        return new CharacterPropertyChange(parent, CharacterPropertyChange::SlabTheKiller);
    case CHARACTER_SUZY_LAFAYETTE:
        return new CharacterSuzyLafayette(parent);
    case CHARACTER_VULTURE_SAM:
        return new CharacterVultureSam(parent);
    case CHARACTER_WILLY_THE_KID:
        return new CharacterPropertyChange(parent, CharacterPropertyChange::WillyTheKid);
    case CHARACTER_BELLE_STAR:
        return new CharacterPropertyChange(parent, CharacterPropertyChange::BelleStar);
    case CHARACTER_JOSE_DELGADO:
        return new CharacterJoseDelgado(parent);
    case CHARACTER_KING_SCHULTZ:
        return new CharacterBlackJack(parent , CharacterBlackJack::KingSchultz);
    case CHARACTER_CHUCK_WENGAM:
         return new CharacterChuckWengam(parent);
    case CHARACTER_PAT_BRENNAN:
        return new CharacterJesseJones(parent , CharacterJesseJones::PatBrennan);
    case CHARACTER_TEQUILA_JOE:
         return new  CharacterBase(parent, CHARACTER_TEQUILA_JOE);
    case CHARACTER_BILL_NOFACE:
        return new CharacterBlackJack(parent , CharacterBlackJack::BillNoface);
    case CHARACTER_SEAN_MALLORY:
        return new CharacterBlackJack(parent , CharacterBlackJack::SeanMallory);
    case CHARACTER_HERB_HUNTER:
        return new CharacterHerbHunter(parent , CharacterHerbHunter::HerbHunter);
    case CHARACTER_GREG_DIGGER:
        return new CharacterHerbHunter(parent , CharacterHerbHunter::GregDigger);
    case CHARACTER_APACHE_KID:
        return new CharacterHerbHunter(parent , CharacterHerbHunter::ApacheKid);
    case CHARACTER_ELENA_FUENTE:
        return new CharacterStarkFuente(parent , CharacterStarkFuente::ElenaFuente);
    case CHARACTER_MOLLY_STARK:
        return new CharacterStarkFuente(parent , CharacterStarkFuente::MollyStark);
    case CHARACTER_DOC_HOLYDAY:
        return new CharacterSidKetchum(parent , CharacterSidKetchum::DocHoliday);
    case CHARACTER_TUCO:
        return new CharacterBlackJack(parent , CharacterBlackJack::Tuco);
    case CHARACTER_UNKNOWN:
        NOT_REACHED();
    }
    return new CharacterBase(parent, CHARACTER_UNKNOWN);
}

void CharacterList::initCharacterTypes()
{
    Q_ASSERT(sm_characterTypes.size() == 0);
        sm_characterTypes.append(CHARACTER_BART_CASSIDY);
        sm_characterTypes.append(CHARACTER_BLACK_JACK);
        sm_characterTypes.append(CHARACTER_CALAMITY_JANET);
        sm_characterTypes.append(CHARACTER_EL_GRINGO);
        sm_characterTypes.append(CHARACTER_JESSE_JONES);
        sm_characterTypes.append(CHARACTER_JOURDONNAIS);
        sm_characterTypes.append(CHARACTER_KIT_CARLSON);
        sm_characterTypes.append(CHARACTER_LUCKY_DUKE);
        sm_characterTypes.append(CHARACTER_PAUL_REGRET);
        sm_characterTypes.append(CHARACTER_PEDRO_RAMIREZ);
        sm_characterTypes.append(CHARACTER_ROSE_DOOLAN);
        sm_characterTypes.append(CHARACTER_SID_KETCHUM);
        sm_characterTypes.append(CHARACTER_SLAB_THE_KILLER);
        sm_characterTypes.append(CHARACTER_SUZY_LAFAYETTE);
        sm_characterTypes.append(CHARACTER_VULTURE_SAM);
        sm_characterTypes.append(CHARACTER_WILLY_THE_KID);
        sm_characterTypes.append(CHARACTER_JOSE_DELGADO);
        sm_characterTypes.append(CHARACTER_CHUCK_WENGAM);
        sm_characterTypes.append(CHARACTER_PAT_BRENNAN);
        sm_characterTypes.append(CHARACTER_TEQUILA_JOE);
        sm_characterTypes.append(CHARACTER_KING_SCHULTZ);
        sm_characterTypes.append(CHARACTER_BILL_NOFACE);
        sm_characterTypes.append(CHARACTER_SEAN_MALLORY);
        sm_characterTypes.append(CHARACTER_HERB_HUNTER);
        sm_characterTypes.append(CHARACTER_GREG_DIGGER);
        sm_characterTypes.append(CHARACTER_ELENA_FUENTE);
        sm_characterTypes.append(CHARACTER_MOLLY_STARK);
        sm_characterTypes.append(CHARACTER_APACHE_KID);
        sm_characterTypes.append(CHARACTER_DOC_HOLYDAY);
        sm_characterTypes.append(CHARACTER_BELLE_STAR);
        sm_characterTypes.append(CHARACTER_TUCO);
}
