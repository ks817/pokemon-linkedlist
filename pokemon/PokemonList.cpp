#include <iostream>
#include <string>
#include "Pokemon.h"
#include "PokemonList.h"

using namespace std;

// Name: PokemonList
// Desc - Default constructor for the PokemonList (linked list)
// Preconditions - None
// Postconditions - Creates an empty PokemonList (linked list)
PokemonList::PokemonList(){
  m_head = nullptr;
  m_size = 0;
}

// Name: ~PokemonList
// Desc - Destructor for the PokemonList (linked list)
// Preconditions - None
// Postconditions - Clears out a PokemonList (linked list)
PokemonList::~PokemonList(){
  Pokemon *curr = m_head;
  while (curr != nullptr){
    m_head = curr;
    curr = curr->GetNext();
    delete m_head;}
  m_head = nullptr;
  m_size = 0;
}

// Name: InsertEnd
// Desc - Inserts an already dynamically allocated Pokemon to end of linked
// list
// Preconditions - PokemonList already created
// Postconditions - The passed Pokemon appears at the end of the list
void PokemonList::InsertEnd(Pokemon* node){

  if (m_head == nullptr){
    m_head = node;
  }
  else{
    Pokemon *temp = m_head;
    while (temp->GetNext() != nullptr){
      temp=temp->GetNext(); //moves to the next node
    }
    temp->SetNext(node);
  }
  m_size++;
  
}

// Name: Display
// Desc - Iterates over PokemonList and displays each Pokemon formatted as in output
// Preconditions - PokemonList already created and has Pokemon
// Postconditions - Displayed Pokemon information
void PokemonList::Display(){
  
  if(m_head == nullptr)
    cout<<"List is empty"<< endl;
  else{
    Pokemon *poke = m_head;
    for(int i = 0; i < m_size; i++){
      
      cout <<"Index: "<< poke->GetIndex();
      cout <<"\tName: "<< poke->GetName();
      cout <<"\tType: "<< poke->GetType();
      cout <<"\tHealth: "<< poke->GetHealth();
      cout << endl;
      poke = poke->GetNext();}}
}

// Name: Transfer
// Desc - Searches for a Pokemon with a specific index. If found,
// creates a new Pokemon and copies it into the PokemonList passed in
// Preconditions - int is the index of the desired Pokemon and
// PokemonList is the destination
// Postconditions - Adds new Pokemon to the destination list and removes it
// from the source
void PokemonList::Transfer(int index, PokemonList* pList){
  //set node equal to m_head
  Pokemon *poke = m_head;
  for(int i=0; i<m_size; i++){ //or while (poke!=nullptr){
    if (index == poke->GetIndex()){
      Pokemon *temp = new Pokemon(poke->GetIndex(),poke->GetName(),poke->GetType(),poke->GetStrong());
      //Insert new pokemon to the destination list
      pList->InsertEnd(temp);
      //remove the data from given index
      Remove(index);}
    //move onto the next node
    poke=poke->GetNext();
  }
}

// Name: Remove (int)
// Desc - Searches for a Pokemon with a specific index. If found,
// removes it from the linked list
// Preconditions - int is the index of the desired Pokemon
// Postconditions - Removes Pokemon from linked list
void PokemonList::Remove(int choice){

  //create two pointer
  Pokemon *poke, *mon;

  //set the first pointer equal to m_head
  poke = m_head;
  //set the second pointer equal to the pointer after^
  mon = m_head->GetNext();

  //if the data is at choice then m_head = second pointer
  if (poke->GetIndex()==choice){
    m_head=mon;
    delete poke;
    poke = nullptr;}

  //otherwise keep moving both pointers
  else{
    while (mon->GetIndex()!=choice && mon!= nullptr){
      mon=mon->GetNext();
      poke=poke->GetNext();}
    //if the second ptr is at the end then set first ptr to the end
    if (mon->GetNext()==nullptr){
      poke->SetNext(nullptr);
      //delete the second ptr
      delete mon;}

    //otherwise set the first pointer next  to the second pointer's next
    else{
      poke->SetNext(mon->GetNext());
      //then delete second pointer
      delete mon;}}
  
  //subtract the size of the list
  m_size--;
}

// Name: GetSize
// Desc - Returns the size of the linked list
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns the size of the linked list
int PokemonList::GetSize(){
  return m_size;
}

// Name: GetHead
// Desc - Returns the Pokemon at the head of the linked list
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns the Pokemon at the head of the linked list
Pokemon* PokemonList::GetHead(){
  return m_head;
}

// Name: Attack(PokemonList)
// Desc - Passes an enemy pocket to the user's pocket to attack
// User always attacks the enemy Pokemon in this game
// Preconditions - This list is populated and enemy list is populated
// Postconditions - Does damage to the user Pokemon and enemy Pokemon
// and updates their health. Returns 2 if enemy Pokemon is less than 0
// Returns 2 if user's health is less than 0 else returns 0.
int PokemonList::Attack(PokemonList* enemy){

  //set both ptr equal tp head ptr
  Pokemon *user = GetHead();
  Pokemon *cpu = enemy->GetHead();

  if (user != nullptr && cpu != nullptr){
    //user attacks first
    //if deals with strong types else deals w normal
    if (user->GetStrong() == cpu->GetType()){
      cpu->SetHealth(cpu->GetHealth() - STRONG_DAMAGE);
      cout << "CPU's Pokemon took " << STRONG_DAMAGE <<" damage."<<endl;}
    if (user->GetStrong() != cpu->GetType()){
      cpu->SetHealth(cpu->GetHealth() - DAMAGE2ENEMY);
      cout << "CPU's Pokemon took " << DAMAGE2ENEMY <<" damage."<<endl;}

    if (cpu->GetStrong() == user->GetType()){
      user->SetHealth(user->GetHealth() - STRONG_DAMAGE);
      cout << "Your Pokemon took "<< STRONG_DAMAGE << " damage."<<endl;}

    if (cpu->GetStrong() != user->GetType()){
      user->SetHealth(user->GetHealth() - DAMAGE2USER);
      cout << "Your Pokemon took "<< DAMAGE2USER<<" damage."<<endl;}

    //if user's health is 0 or less, return 2
    if (user->GetHealth() <= 0 or cpu->GetHealth() <= 0){
      return 2;
    }
  }
  return 0;
}

// Name: SwapPokemon
// Desc - Allows user to move a Pokemon from any position into the first
// position
// Special cases: Empty list, Pokemon chosen at m_head or choice doesn't exist
// Preconditions - Linked list is populated
// Postconditions - User selects a Pokemon and it is moved into the first
// position
void PokemonList::SwapPokemon(){
  int userChoice;
  Pokemon *poke, *mon;
  
  //set the pointer equal to m_head and another equal to nullptr
  poke = m_head;
  mon = nullptr;
  
  cout << "Which Pokemon would you like to choose? (Enter the index#)"<<endl;

  //display options
  Display();

  cin >> userChoice;

  //if the userchoice is already m_head keep it that way
  if (poke != nullptr && userChoice == poke->GetIndex()){
    mon = poke;
    m_head = poke;}
  
  //search the node that the user wants to swap
  while (poke != nullptr && poke->GetIndex()!= userChoice){
    mon = poke;
    poke = poke->GetNext();}
  
  //connecting previous ptr  to current pointer
  mon->SetNext(poke->GetNext());
  poke->SetNext(m_head);

  m_head = poke;

}

// Name: Exist(int)
// Desc - Iterates through linked list looking for a specific index of a
// Pokemon
// Preconditions - PokemonList is populated with Pokemon
// Postconditions - Returns true if found else false
bool PokemonList::Exist(int index){
  
  //set node equal to m_head
  Pokemon *poke = m_head;


  for(int i=0; i<m_size; i++){ //or while (poke!=nullptr){
    
    if (index-1 == poke->GetIndex()){
      return true;
    }
    poke=poke->GetNext();
  }

  return false;
}
