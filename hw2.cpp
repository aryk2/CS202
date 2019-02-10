//Aryeh Kempler-DeLugach, hw2 main file
//CS202

#include "hw2.h"

//The class structure for this program is a little funny
//I have a manager class that hold the head ptr for a list
//each head ptr points to the base class vehicle
//each node is a vehicle object with a vehicle ptr to a derived class obj
//therefore my vehicle class is not abstract because there are objects 
//Otherwise, is makes nodes and uses upcasting with is standard 

int main() {

   manager list; //creates manager object, hold head ptr
   list.start();  //manager function that starts program

   return 0;
}

//constructors

manager::manager() {
   head = NULL;
};

vehicle::vehicle() {
   prev = NULL;
   next = NULL;
}
//constructors initialize data members and manage dynamic memory for 
// the location of each vehicle 
scooter::scooter(char *start_location, int id):vehicle(), id_num(id), battery(100) {    
   location = new char[strlen(start_location) +1];
   strcpy(location, start_location);
   money_made = 0;
   type = 1;
}

bike::bike(char *start_location, int id): vehicle(), id_num(id){
   location = new char[strlen(start_location) +1];
   strcpy(location, start_location);
   money_made = 0;
   type = 2;
}
 
car::car(char *start_location, int id): vehicle(), id_num(id), gas(40) {
   location = new char[strlen(start_location) +1];
   strcpy(location, start_location);
   money_made = 0;
   type = 3;
}

manager::~manager() {
   clear_all(head); //recursive function that deletes all nodes
}
//virtual destructor
vehicle::~vehicle() {

}
//destructors for each derived class, each only manage location memory
scooter::~scooter() {
   delete [] location; 
}

bike::~bike() {
   delete [] location;
}

car::~car() {
   delete [] location;
}


