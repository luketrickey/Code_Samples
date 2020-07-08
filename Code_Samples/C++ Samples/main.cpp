// cardplay-1/main.cpp -- Very simple program to deal cards.
// Fred Swartz 2004-11-22

// Summary:     Reads a number and then "deals" that many cards.
// Illustrates: Random methods (strand and rand).

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

#include "card.h"
#include "deck.h"

//================================================== main
int main() {
    int numOfCards; // Input number for how many cards to deal.
    srand(time(0)); // Initializes random "seed".
    Deck deck;
    
    while (cin >> numOfCards) {
        deck.shuffle();
        
        cout << "Your hand is: ";
        for (int cardNum=0; cardNum<numOfCards; cardNum++) {
            Card c = deck.dealOneCard();  
            string suit = c.getSuit();
            string face = c.getFace();
            cout << face << suit << " ";
        }
        cout << endl;
    }

    return 0;
}//end main