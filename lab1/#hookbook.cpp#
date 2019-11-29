//Akwarandu Ugo Nwachuku
//September 11th, 2018
//Lab 1
//CS 15- Data Structures
#include <iostream>
#include <fstream>
#include "Pirate.h"
#include "ArrayList.h"
using namespace std; 

int main(){
    ifstream myfile;
    //Instantiating five pirates with parameterized constructors.
    Pirate p1("Jeff");
    Pirate p2("Adam");
    Pirate p3("Clara");
    Pirate p4("Caitlyin");
    Pirate p5("Ugo");

    //Instantiate Arraylist and add all pirates. 
    ArrayList a_list;
    a_list.insert_pirate(p1);
    a_list.insert_pirate(p2);
    a_list.insert_pirate(p3);
    a_list.insert_pirate(p4);
    a_list.insert_pirate(p5);
    //Print list.
    cout <<"These are the five new pirate recruits!" << endl;
    a_list.print(); 
    cout <<" "<<endl;

    //Generate ten new pirates. And catch a segmentation fault for 200 pirates.
    //Now generate names in order. 
    myfile.open("pirate_names.txt");
    if (myfile.is_open()){
      for(int i = 0; i<50; i++){ 
        Pirate pirate;
	//pirate.generate_pirate_name(myfile, 12);
	pirate.generate_next_pirate(myfile);
	pirate.assign_pirate_id();

        cout <<"Printed pirate name: " <<endl;
	pirate.print();
	cout <<" "<<endl;

	//Segmentation catch!
	if (!a_list.is_full()){
	  a_list.insert_pirate(pirate);
        }
	else{ 
          a_list.print();
	  cout << "The array list for pirates is full. You can't add anymore!" << endl;
          return 0;
	  }
        }
      }
  
  }
