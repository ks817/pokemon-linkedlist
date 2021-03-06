#include "Pokemon.h"
#include "PokemonList.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

// Name: Game Constructor
// Desc - Creates a new game and sets m_filename based on string passed
// Additionally, makes m_list and userPoken = new PokemonLists
// Preconditions - Input file passed and populated with Pokemon
// Postconditions - m_filename, m_list, and userPocket created
Game::Game(string file){
  m_filename = file;
  m_list = new PokemonList();
  m_userPocket = new PokemonList();
  m_enemyPocket = new PokemonList();
}

// Name: Game Destructor
// Desc - Calls destructor for all linked lists in game
// Preconditions - Linked lists populated
// Postconditions - m_list, userPocket, and enemyPocket are all destructed
Game::~Game(){
  delete m_list;
  delete m_userPocket;
  delete m_enemyPocket;
}

// Name: LoadFile
// Desc - Opens file and reads in each Pokemon. Each Pokemon dynamically
// allocated
// and put into m_list
// Preconditions - Input file passed and populated with Pokemon
// Postconditions - m_list populated with Pokemon
void Game::LoadFile(){

  int index;
  string name;
  string type;
  string strong;
  
  ifstream myFile;
  
  myFile.open(m_filename);
  while ( !myFile.eof()){
    myFile>>index;
    myFile.ignore(256, ',');
    getline(myFile, name,',');
    getline(myFile, type, ',');
    getline(myFile, strong, '\n');
    Pokemon *poke = new Pokemon(index,name,type,strong);
    poke->SetHealth(9);
    m_list->InsertEnd(poke);
  }
  myFile.close();
}

// Name: ChooseTeam
// Desc - Allows user to choose team and populates m_userPocket
// Preconditions - m_list populated with Pokemon
// Postconditions - m_userPocket populated with Pokemon to battle
void Game::ChooseTeam(){

  int userChoice;
  int count = NUM_TEAM;

  while (count > 0){
    cout << "Pick a Pokemon by entering the index (" << count <<" left): ";
    cin >> userChoice;
    count--;
    m_list->Transfer(userChoice,m_userPocket);
  }
  cout<<"------------------------------\nPrint player pocket"<<endl;
  m_userPocket->Display();
}

// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_list, m_userPocket, and m_enemyPocket all populated
// Postconditions - Returns choice
int Game::Menu(){
  int userChoice;
  cout<<"------------------------------\nMenu:\n1. Attack\n2. Swap\n3. Forfeit"<< endl;
  cin >> userChoice;
  return userChoice;
    
}

// Name: Battle
// Desc - Manages the battle between m_userPocket and m_enemyPocket.
// Displays both the m_userPocket and m_enemyPocket
// For each round, makes sure each team has Pokemon. Makes Pokemon in head
// fight.Indicates if the round yields user win, enemy win, and if a pokemon
// was switched.Fights continue until there are no remaining Pokemon in one
// of the lists
// Preconditions - m_userPocket and m_enemyPocket must all be > 0 and populated
// Postconditions - Returns result of battle back to Start (1=user win,
// 2=cpu win)
int Game::Battle(){
  int round = 1;
  int userChoice;
  int lowHealth;  

  Pokemon *poke = m_enemyPocket->GetHead();
  Pokemon *mon = m_userPocket->GetHead();


  //runs as long as both pockets are empty
  while (m_enemyPocket->GetSize() > 0 && m_userPocket->GetSize() > 0){
    cout << "------------------------------\nRound " << round << ":" << endl;
    cout << "CPU's Pokemon: "<< *m_enemyPocket->GetHead();;
    cout << "Your Pokemon: "<< *m_userPocket->GetHead();
    
    userChoice = Menu();
    switch(userChoice)
      {
      case 1:
	//get 2 or 0 from attack()
	lowHealth = m_userPocket->Attack(m_enemyPocket);
	round++;
	if (m_enemyPocket->GetSize() == 0){
              return 1;}
	if (m_userPocket->GetSize()==0){
              return 2;}
	//if cpu has low health
	if (lowHealth == 2){
	  if (poke->GetHealth() <= 0){// && mon->GetHealth() >=0){
	    cout << "CPU's pokemon has been defeated" << endl;
	    if (m_enemyPocket->GetSize()!=0){
	      m_enemyPocket->Remove(m_enemyPocket->GetHead()->GetIndex());
	      cout << "CPU changed it's pokemon to: " << *m_enemyPocket->GetHead() << endl;}}
	  //if (m_enemyPocket->GetSize() == 0){
	  //return 1;}}
	  //if user has low health
	  if (mon->GetHealth() <= 0 ){//&&
	    cout<<"Your Pokemon has been defeated"<< endl;
	    if (m_userPocket->GetSize()!=0){
	      m_userPocket->Remove(m_userPocket->GetHead()->GetIndex());
	      cout << "You changed your pokemon to: " << *m_userPocket->GetHead() << endl;}
	    else
	      return 2;}}
	break;
      case 2:
	m_userPocket->SwapPokemon();
	break;
      case 3:
	return 2;
	break;
      default:
	userChoice = Menu();}
  }  
  return 0;
}
// Name: Start
// Desc - Loads input file, allows user to choose their team, randomly
// populates the m_enemyPocket with remaining Pokemon and returns the result
// of the battle
// Preconditions - m_list, m_userPocket, and m_enemyPocket must all be
// PokemonLists
// Postconditions - Returns result of battle back to main
int Game::Start(){
  //int MIN = 0;
  //int MAX = 152;
  bool existence;
  int result;
  
  cout <<"Here is a list of Pokemon you can choose from:\n------------------------------"<< endl;
  //show pokemons
  LoadFile();
  m_list->Display();
  ChooseTeam();

  //populate enemy
  int count = NUM_TEAM;
  while (count>0){
    
    //get a random index
    int randNum = rand() % m_list->GetSize();

    //Check if the random index is already picked by user or not
    existence = m_list->Exist(randNum);
    
    if (existence){ 
      //Transfer(randNum);
      m_list->Transfer(randNum, m_enemyPocket);
      //rand() % m_list->GetSize(), m_enemyPocket);
      count--;
    }
  }
  
  cout<<"------------------------------\nPrint cpu pocket"<<endl;
  m_enemyPocket->Display();

  //Start battle
  result = Battle();

  
  return result;
  

}
