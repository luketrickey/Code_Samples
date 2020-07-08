#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.h"
using namespace std;

player::player() {}

player::player(string n, int c) {
        cout << "Player: " << n << " joined the game!\n";
        setName(n);
        setCash(c);
}

player::~player() {}

void player::setName(string name) {
        this->name = name;
}

string player::getName() {
        return name;
}

void player::setCash(int cash) {
        this->cash = cash;
}

int player::getCash() {
        return cash;
}

AI::AI() {
        cout << "Blank AI created.\n";
}

AI::AI(string n, int c, int p) {
        cout << "Player: " << n << " has joined the game!\n";
        setName(n);
        setCash(c);
}

AI::~AI() {}

void AI::setPersn(int p) {
        personality = p;
}

int AI::getPersn() {
        return personality;
}
