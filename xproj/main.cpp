#include <iostream>
#include "Bridges.h"
#include "Island.h"
using namespace std; 

int main()
{
	Bridges b1;
	cout << endl;
	cout << endl;
	cout << endl;

	cout << "******WELCOME TO EULER'S KONISBERG CHALLENGE******" << endl;

	cout << "Cross all bridges to explore Konigsberg, but only ";
	cout << "cross a bridge once or else your out of town!" <<endl;

	b1.populate_graph("Bridges.txt");
	b1.print();
	cout << "To Play, " << endl;
	cout << "Enter your starting island: [PRESS_ENTER] " << endl;
	cout << "Enter your starting bridge: [PRESS ENTER]  " << endl;
	int count = 7;
	b1.run(cin, cout);
	while (count > 0)
	{
		string ans;
		b1.run(cin, cout);
		cout << "Looks like you crossed a bridge twice, no worries. Try again!"
		<< endl;
		count--;
		cout << "Play again? Y or N:" << endl;
		cin >> ans; 
		if (ans == "N")
			break;
		b1.print();
		cout << "You have " << count << " chances left. So think hard ;)" << endl;
		cout << endl; 
		cout << "Enter your starting island: [PRESS_ENTER] " << endl;
		cout << "Enter your starting bridge: [PRESS ENTER]  " << endl;
	}
	
	return 0;
}