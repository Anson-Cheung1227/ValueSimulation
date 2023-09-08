#include "CardType.h"


CardType::CardType(std::string ident)
{
    this->ident = ident;
    cards = CARDSPERTYPE;
}
