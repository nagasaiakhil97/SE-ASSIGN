// event.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

using namespace std;

class Machine
{
	class State* current;
public:
	Machine();
	void setCurrent(State* s)
	{
		current = s;
	}
	void Idle();
	void Sensing();
	void Processing();
};

class State
{
public:
	virtual void Idle(Machine* m)
	{
		cout << "Nodes are in Idle mode" << endl;
	}
	virtual void Sensing(Machine* m)
	{
		cout << "Nodes are in Sensing mode" << endl;
	}
	virtual void Processing(Machine* m)
	{
		cout << "Nodes are in Processing mode" << endl;
	}

};

void Machine::Idle()
{
	current->Idle(this);
}

void Machine::Sensing()
{
	current->Sensing(this);
}

void Machine::Processing()
{
	current->Processing(this);
}

class IDLE : public State
{
public:
	IDLE()
	{
		cout << "IDLE MODE CONSTRUCTOR" << endl;
	};
	~IDLE()
	{
		cout << "DESTRUCTOR IDLE MODE" << endl;
	};
	void Sensing(Machine* m);

};

class SENSING : public State
{
public:
	SENSING()
	{
		cout << "SENSING MODE CONSTRUCTOR" << endl;
	};
	~SENSING()
	{
		cout << "DESTRUCTOR SENSING MODE" << endl;
	};
	void Processing(Machine* m);

};

class PROCESSING : public State
{
public:
	PROCESSING()
	{
		cout << "PROCESSING MODE CONSTRUCTOR" << endl;
	};
	~PROCESSING()
	{
		cout << "DESTRUCTOR PROCESSING MODE" << endl;
	};

	void Idle(Machine* m);

};

void IDLE::Sensing(Machine* m)
{
	cout << "IDLE mode to SENSING mode" << endl;
	m->setCurrent(new SENSING());
	delete this;
	cout << "Reading Sensor Values" << endl;
	Sleep(3000);
	cout << "Getting data from the Humidity Sensor" << endl;
	int a = 1;
	while (a++ <= 7)
	{
		int Humidity = (rand() % (100 - 25 + 10)) + 5;
		cout << "The Humidity Sensor Value: " << Humidity << endl;
		Sleep(1500);
	}

	Sleep(3000);
	cout << "Getting data from the Temperature Sensor" << endl;
	int b = 1;
	while (b++ <= 7)
	{
		int temp = (rand() % (100 - 30 + 10)) + 15;
		cout << "The Temperature Sensor Value: " << temp << endl;
		Sleep(1500);
	}
	Sleep(3000);
	cout << "Values are ready for Processing" << endl;
	m->Processing();
}

void SENSING::Processing(Machine* m)
{
	cout << "SENSING mode to PROCESSING mode" << endl;
	m->setCurrent(new PROCESSING());
	delete this;
	cout << "PROCESSING the Sensor Data" << endl;
	Sleep(3000);
	cout << "PROCESSING the Humidity Data" << endl;
	Sleep(3000);
	cout << "PROCESSING the Temperature Data" << endl;
	Sleep(3000);
	cout << "Going back to IDLE mode" << endl;
	Sleep(3000);
	m->Idle();
}

void PROCESSING::Idle(Machine* m)
{
	cout << "PROCESSING mode to IDLE mode" << endl;
	m->setCurrent(new IDLE());
	delete this;
}

Machine::Machine()
{
	current = new IDLE();
	cout << '\n';
}

int main()
{
	Machine fstatem;
	char userPreference;
	for (int i = 1; i <= 7; i++)
	{
		cout << "System is in IDLE mode. Do you want to start SENSING mode??? (y/n): ";
		cin >> userPreference;
		if (char(toupper(userPreference)) == 'Y')
		{
			fstatem.Sensing();
			Sleep(3000);
		}
		else if (char(toupper(userPreference)) == 'N')
		{
			continue;
		}
		else
		{
			cout << "Invalid character is entered" << endl;
		}
	}
	return 0;
}