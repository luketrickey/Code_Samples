#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

class player {
  protected:
        string name;
        int cash;
  public:
        player();
        player(string n, int c);
        ~player();

        void setName(string n);
        string getName();
        void setCash(int c);
        int getCash();
};

class AI : public player {
  protected:
        int personality;
  public:
        AI();
        AI(string n, int c, int p);
        ~AI();

        void setPersn(int p);
        int getPersn();
};
#endif