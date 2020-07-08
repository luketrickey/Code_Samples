#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <iterator>
#include <math.h>
using namespace std;

#include "player.h"

void printTable(player &user, list <AI> &playerList);

int main(){
  ifstream infile("FinalProjName.txt");
  string names[6];
  int filecount = 0;
  while(!infile.eof()) {
        infile >> names[filecount];
        filecount++;
  }
  list <AI> playerList;

  int x = 0;
  string p;
  cout << "Welcome to blackjack!\n";
  cout << "What is your name? ";
  cin >> p;
  cout << "How many players would you like? (0-6) ";
  cin >> x;

  player user(p, 1000);

  for(int i = 0; i < x; i++)
  {
    int prsn = 0;
    if(i % 2 == 0){
      prsn = 0;
    } else {prsn = 1;}
    AI newPlayer(names[i], 1000, prsn);
    newPlayer.setPersn(prsn);
    playerList.push_back(newPlayer);
  }
  
  printTable(user, playerList);
}

void printTable(player &user, list <AI> &playerList) {
  string username = user.getName();
  int usercash = user.getCash();
  cout << user.getName() << "'s cash: " << usercash << endl;

  string AIname = "";
  int AIcash = 0;

  for(list <AI> :: iterator it = playerList.begin(); it != playerList.end(); it++) {
    AIname = it->getName();
    AIcash = it->getCash();
    cout << AIname << "'s cash: " << AIcash << endl;
  }
}
