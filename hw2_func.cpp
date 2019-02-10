//Aryeh Kempler-DeLugach, hw2 functions file
//CS202

#include "hw2.h"

//manager functions 
int manager::start() {
   build(); //functions that lets user add as many new nodes as they want
   
   cout << "\n\nHere are all your vehicles: \n";
   display_all(head); //displays all newly created nodes

   int choice = 0; //option menu for user to make choices
   while (choice != 6) {
      cout << "\n\n1 - Add a new vehicle"
           << "\n2 - Search for an ID #"
           << "\n3 - Remove a vehicle"
           << "\n4 - Add a new ride to a vehicle"
           << "\n5 - Display all vehicles"
           << "\n\n6 - Exit\n";
      cin >> choice; cin.ignore(100, '\n');
      if(choice == 1)
         add_new();
      if(choice == 2) {
         cout << "\n\nID # to retrieve?  ";
         int to_find;
         cin >> to_find; cin.ignore(100, '\n');
         vehicle * current = retrieve(head, to_find);
         if(!current) 
            cout << "\nID # not found in list\n";
         else {
            cout << "\nvehicle found, display? (y/n)  " ;
            char choice;
            cin >> choice; cin.ignore(100, '\n');
            if(toupper(choice) == 'Y') 
               current -> display();
         }
      }
      if(choice == 3) {
         cout << "\nEnter an ID # to remove: " ;
         int to_remove;
         int success = 1;
         cin >> to_remove; cin.ignore(100, '\n');
         success = remove(head, to_remove);
         if(success == 1) 
            cout << "\nVehicle has been removed\n";
         else 
            cout << "\nID # entered was not found in list\n";
      }
      if(choice == 4) { 
         cout << "\nwhich vehicle ID# is being used?  ";
         int to_find;
         cin >> to_find; cin.ignore(100, '\n');
         vehicle * current = retrieve(head, to_find);
         if(!current)
            cout << "\nID # not found in list\n)";
         else
            current -> new_use();
      }
      if(choice == 5)
         display_all(head);
   }
   return 0;
}
//remove all function, only called by destructor right now
int manager::clear_all(vehicle * & head) {
   if(!head)
      return 0;
   clear_all(head -> next);
   delete head -> ptr;
   delete head;
   return 0;
}
//lets user add as many new nodes as they want to fleet of vehicles
int manager::build() {
   int choice =0;
   int flag = 0;
   cout << "\nstart building your fleet\n\n";
   while (choice != 4) 
      choice = add_new(); //calls add function with information for node
   return 0;
}
//retrieve function that returns a node, nothing else
vehicle * manager::retrieve(vehicle * head, int to_find) const {
   if(!head) 
      return NULL;
   if(head -> ptr -> get_id() == to_find) {
      return head -> ptr;
   }
   return retrieve(head -> next, to_find);
}  
//reads in, creates node  and calls function add new vehicle to dll 
int manager::add_new() {
   int choice;
   cout << "\nadd a new vehicle to your fleet: \n" 
        << "new scooter: 1 \nnew bike: 2 \nnew car: 3\n"
        << "no more new: 4\n";
   cin >> choice; cin.ignore(3, '\n');
   if(choice != 4) {
      cout << "\nwhat is the intersection it is at?   ";
      char location[50];
      cin.get(location, 50, '\n'); cin.ignore(100, '\n');
      char * start_location = new char[strlen(location) +1];
      strcpy(start_location, location);
  
      cout << "\nwhat is the id number?   ";
      int id;
      cin >> id; cin.ignore(100, '\n');
      
      if(choice == 1) {
         vehicle * to_add = new vehicle; //creates vehicle node
         //uses upcating to make vehicle ptr in node a type of vehicle 
         to_add -> ptr = new scooter(start_location, id);
         add(head, to_add); //calls to_add function
         }      
      if(choice == 2) {
         vehicle * to_add = new vehicle;
         to_add -> ptr = new bike(start_location, id);
         add(head, to_add);
      }
      if(choice == 3) {
         vehicle * to_add = new vehicle;
         to_add -> ptr = new car(start_location, id);
         add(head, to_add);
      }  
      delete [] start_location; //deletes memmory that is passed to func
      return choice; //returns the next node to be added that user selected
   }
}
//function that adds nodes to end of the list
int manager::add(vehicle * &head, vehicle * &to_add) {
   if(!head) {
      head = to_add;
      head -> next = NULL;
   }
   else {
      if (head -> next)
         head -> next -> prev = head;  //sets next nodes prev
      add(head -> next, to_add);
   }
   return 0;
}
//removes nodes from the list that were selected by user (to_remove)
int manager::remove(vehicle * & head, int to_remove) {
   if(!head)
      return 0;
   if(head -> ptr -> get_id() == to_remove) {
      if(head -> prev) 
         head -> prev -> next = head -> next;
      if(head -> next)
         head -> next -> prev = head -> prev;   
      vehicle * temp = head;
      head = head -> next;
      delete temp -> ptr;
      delete temp;
     
      return 1;
   }
   return remove(head -> next, to_remove);
} 
//calls virtual function in head to display data from derived obj
int manager::display_all(vehicle * head) const {
   if(!head)
      return 0;
   head -> ptr -> display();
   display_all(head -> next);
   return 0;
}

//virtual functions for scooter
void scooter::new_use() {
   cout << "\nSomeone used scooter " << id_num 
        << "\n\nHow many minutes did they use it for?  ";
   int time;
   cin >> time; cin.ignore(100, '\n');
   battery = battery - time;      
   money_made = money_made + (time * PRICE);
   cout << "\nWhere is the scooter now?  ";
   char temp_location[50];
   cin.get(temp_location, 50, '\n'); cin.ignore(100, '\n');
   delete [] location;
   location = new char[strlen(temp_location) +1];
   strcpy(location, temp_location);

   display();
}

void scooter::display() {
   cout << "\nScooter"
        << "\nID #: " << id_num
        << "\nLocation: " << location
        << "\nBattery level: " << battery 
        << "\nMoney made: " << money_made << " dollars\n";
}

int scooter::get_id() {
   
   return id_num;
}

//virtual functions for bike
void bike::new_use() {
   cout << "\nSomeone used bike " << id_num 
        << "\n\nHow many minutes did they use it for?  ";
   int time;
   cin >> time; cin.ignore(100, '\n');
   money_made = money_made + PRICE;
   cout << "\nWhere is the bike now?  ";
   char temp_location[50];
   cin.get(temp_location, 50, '\n'); cin.ignore(100, '\n');
   delete [] location;
   location = new char[strlen(temp_location) +1];
   strcpy(location, temp_location);

   display();
}

void bike::display() {
   cout << "\nBike"
        << "\nID #: " << id_num
        << "\nLocation: " << location
        << "\nMoney made: " << money_made << " dollars\n";
}

int bike::get_id() {
   return id_num;
}

//virtual functions for car
void car::new_use() {
   cout << "\nSomeone used car " << id_num 
        << "\n\nHow many hours did they use it for(min 1)?  ";
   int time;
   gas = gas - GALLON_PER_HOUR; 
   cin >> time; cin.ignore(100, '\n');
   money_made = money_made + (PRICE * time);
   cout << "\nWhere is the car now?  ";
   char temp_location[50];
   cin.get(temp_location, 50, '\n'); cin.ignore(100, '\n');
   delete [] location;
   location = new char[strlen(temp_location) +1];
   strcpy(location, temp_location);

   display();
}

void car::display() {
   cout << "\nCar"
        << "\nID #: " << id_num
        << "\nLocation: " << location
        << "\nGas: " << gas
        << "\nMoney made: " << money_made << " dollars\n";
}

int car::get_id() {
   return id_num;
}
