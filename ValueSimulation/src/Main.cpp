#include <iomanip>
#include <iostream>
#include "CardType.h"

#define CARDTYPES 13

long count = 0;
long maxCount = 10;
CardType* current, *last;
long nonConsecutive = 0, longestCard = 0;

CardType Cards[CARDTYPES] =
    {
    CardType("2"),
    CardType("3"),
    CardType("4"),
    CardType("5"),
    CardType("6"),
    CardType("7"),
    CardType("8"),
    CardType("9"),
    CardType("10"),
    CardType("J"),
    CardType("Q"),
    CardType("K"),
    CardType("A"),
    };

void Init()
{
    std::cout << "Please enter iterations:";
    std::cin >> maxCount;
}
void SetChanceNum()
{
    int currentCount = 0;
    for (CardType& card : Cards)
    {
        card.chanceNum = currentCount;
        currentCount += card.cards;
    }
}
void DrawCard(int cardsLeft)
{
    int random = rand() % cardsLeft;
    CardType* lastIter = nullptr;
    for (CardType& card : Cards)
    {
        if (card.chanceNum > random && card.cards > 0)
        {
            current = lastIter;
            --current->cards;
            std::cout << current->ident << " ";
            return;
        }
        if (card.cards > 0)lastIter = &card;
    }
    for (int i = 12; i >= 0; --i)
    {
        if (Cards[i].cards > 0)
        {
            current = &Cards[i];
            --Cards[i].cards;
            std::cout << current->ident << " ";
            return;
        }
    }
}
void Reset()
{
    for (CardType& card : Cards)
    {
        card.cards = CARDSPERTYPE;
    }
}
int main(int argc, char* argv[])
{
    Init();
    while (count < maxCount)
    {
        //LOOP
        last = nullptr;
        current = nullptr;
        std::cout << "Iteration " << count << ":" << std::endl;
        long found = false;
        int currentCardCount = 0;
        Reset();
        for (int i = CARDSPERTYPE * CARDTYPES; i > 0; --i)
        {
            SetChanceNum();
            DrawCard(i);
            ++currentCardCount;
            if (last == nullptr)
            {
                last = current;
                continue;
            }
            if (last == current)
            {
                std::cout << std::endl << "Consecutive Value!" << std::endl;
                found = true;
                break;
            }
            last = current;
        }
        if (found == false)
        {
            std::cout << std::endl << "No Consecutive Value!" << std::endl;
            ++nonConsecutive;
        }
        if (currentCardCount > longestCard)
        {
            longestCard = currentCardCount;
        }
        std::cout << "Cards drawn in this iteration:" << currentCardCount << std::endl;
        std::cout << "Cards left: ";
        for (CardType& card : Cards)
        {
            if (card.cards > 0)
            {
                for (int i = 0; i < card.cards; ++i)
                {
                    std::cout << card.ident << " ";
                }
            }
        }
        ++count;
        std::cout << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Stats" << std::endl << "Consecutive Sets: " << count - nonConsecutive << std::endl <<
            "Non Consecutive Sets: " << nonConsecutive << std::endl << "Non Consecutive Chance: ";
        if (nonConsecutive == 0)
        {
            std::cout << "0%" << std::endl;
        }
        else
        {
            float chance = (float)nonConsecutive/(float)count* (float)100;
            std::cout << std::setprecision(10) <<chance << "%" << std::endl;
        }
        std::cout << "Most cards drawn:" << longestCard  << std::endl;
        std::cout << "==============================" << std::endl;
    }
    return 0;
}
