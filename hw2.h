//Aryeh Kempler-DeLugach, hw2 header file
//CS202

#include "iostream"
#include "cctype"
#include "cstring"
using namespace std;

class manager;
class vehicle;
class scooter;
class bike;
class car;
//manager class holds head ptr for dll
class manager {
   public:
      manager();
      ~manager();
       
      int start();
      int build();

      int add_new();   
      int add(vehicle * &head, vehicle * &to_add);
      vehicle * retrieve(vehicle * head, int to_find) const;
      int display_all(vehicle * head) const;
      int remove(vehicle * & head, int to_remove);
      vehicle * &getnext();      
      int clear_all(vehicle * & head);
   private: 
      vehicle * head;
};
//vehicle is base class and node class combined 
class vehicle {
   public:
      vehicle();
      virtual ~vehicle();

      virtual void new_use() {};
      virtual void display() {};
      virtual int get_id() {};

      vehicle * ptr;      
      vehicle * prev;
      vehicle * next;
};
//derived classes 
class scooter: public vehicle {
   public:
      scooter(char * start_location, int id);
      scooter(const scooter &);
      ~scooter();
      
      void new_use();
      void manage();
      void display();
      int get_id();
   private:
      int id_num;
      int type;
      char * location;
      int battery;
      int money_made;
      const int PRICE = 1; //per min
};

class bike: public vehicle {
   public:
      bike(char * start_location, int id);
      bike(const bike &);
      ~bike();

      void new_use();
      void manage();
      void display();
      int get_id();
   private:
      int id_num;
      int type;
      char * location;
      int money_made;
      const int PRICE = 3; //per use
};

class car: public vehicle {
   public:
      car(char * start_location, int id);
      car(const car &);
      ~car();
  
      void new_use();
      void manage();
      void display();
      int get_id();
   private:
      int id_num;
      int type;
      char * location;
      int money_made;
      int gas;
      const int PRICE = 10; //per hour
      const int GALLON_PER_HOUR = 2;
};
