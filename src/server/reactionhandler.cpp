#include "reactionhandler.h"
#include "gameexceptions.h"
#include <QDebug>

void ReactionHandler::respondPass()
{
    throw BadUsageException();
}

void ReactionHandler::respondCard(PlayingCard* targetCard)
{
    Q_UNUSED(targetCard);
    throw BadUsageException();
}

void ReactionHandler::dismiss()
{
    throw BadUsageException();
}
