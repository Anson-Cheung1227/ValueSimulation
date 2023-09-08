#pragma once
#include <string>

#define CARDSPERTYPE 4

class CardType
{
public:
    CardType(std::string ident);
    std::string ident;
    int cards;
    long chanceNum;
};
