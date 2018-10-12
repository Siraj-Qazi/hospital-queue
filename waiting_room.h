#include <iostream>
#include <string>
#include <cctype>
#include <Windows.h>
#include <conio.h>

class Patient
{
public:

	std::string _name;
	int _patientID;

	Patient() : _name(""), _patientID(0) {}
};


class WaitingQueue
{
public:

	int _size;
	int _frontIndex;
	int _rearIndex;
	int _patientCount;
	Patient* _waitingQueue;

	WaitingQueue() :  // Member Initializer List Syntax
		_size(0), 
		_frontIndex(0), 
		_rearIndex(-1), 
		_patientCount(0), 
		_waitingQueue(NULL)
	{
		Patient();    // Call Patient's constructor to initialize data members
		std::cout << "\n Enter ward capacity (or Queue size): ";
		std::cin >> _size;
		std::cin.clear();
		std::cin.ignore();
	}

	void enterWardX()
	{
		system("cls");
		system("color 0b");
		std::cout
			<< "\n ******************************************************"
			<< "\n                  WARD-X : STARTUP INTERFACE"
			<< "\n ******************************************************"
			<< "\n\n Welcome to Ward-X."
			<< "\n Press 1-6: \n"
			<< "\n 1 - Register new patient into Ward-X"
			<< "\n 2 - Allow the first patient into the Doctor's Clinic"
			<< "\n 3 - Display current waiting list of patients"
			<< "\n 4 - Cancel all appointments"
			<< "\n 5 - Check if no patients are remaining and the Doc's free now"
			<< "\n 6 - Exit"
			<< "\n ";

		char choice = _getch();
		switch (choice)
		{
		case '1':
			registerPatient();
			break;

		case '2':
			servePatient();
			break;

		case '3':
			displayCurrentQueue();
			break;

		case '4':
			cancelAllAppointments();
			break;

		case '5':
			checkIfDocsFree();
			break;

		case '6':
			exit(0);

		default:
			std::cout << "\n Please press 1-6 ONLY. ";
			_getch();
			enterWardX();
		}
		enterWardX();
	}


	void registerPatient()
	{
		if (_rearIndex == -1)
			_waitingQueue = new Patient[_size];

		if (isFull())
		{
			std::cout << "\n Cannot register new patients. Ward-X is out of capacity. ";
			_getch();
		}

		else
		{
			system("cls");
			std::cout << "\n\n ^^^^^^^^^^  REGISTER NEW PATIENT MENU  ^^^^^^^^^^"
				<< "\n\n Please enter new patient's name: ";
			std::string name;
		

		getName:
			std::getline(std::cin, name);

			for (int i = 0; i < name.size(); ++i)
			{
				if (!(isalpha(name[i]) || isspace(name[i])))
				{
					std::cout << "\n INVALID NAME. Name cannot contain digits or special characters.\n";
					Sleep(2000);
					std::cout << "\n Please enter new patient's name: ";
					goto getName;
				}
			}

			//random + (random > 999 ? 0 : 1000);

			_waitingQueue[++_rearIndex]._name = name;
			_waitingQueue[_rearIndex]._patientID = ++_patientCount + 999;

			std::cout << "\n Test Subject '" << name << "'" << std::endl << " PatientID " << _patientCount + 999 << std::endl << " has been successfully added to Ward-X Records.\n";
			_getch();
		}
	}

	void servePatient()
	{
		if (!(isEmpty() || (_frontIndex > _rearIndex)))
		{
				std::cout << "\n Patient '" << _waitingQueue[_frontIndex]._name << "' has been sent into the clinic. \n";
				
				/*Patient* servedPatient = &_waitingQueue[_frontIndex];
				delete servedPatient;*/
				
				if (!(_frontIndex == _size - 1))
					_frontIndex++;

				_patientCount--;
		}

		else
			std::cout << "\n No patient is waiting. ";
		
		_getch();
	}

	void displayCurrentQueue()
	{
		if (isEmpty() || (_frontIndex > _rearIndex))
		{
			std::cout << "\n The queue is currently empty. ";
			_getch();
		}

		else
		{
			system("cls");
			std::cout << "\n Total Patient(s): "<<_patientCount<<"\tCurrent waiting queue (sorted by ID): \n"
				<< "\n --------------------------------------------------------------"
				<< "\n PATIENT ID\t\tPATIENT NAME\n";
			for (int i = _frontIndex; i <= _rearIndex; ++i)
				std::cout << "\n " << _waitingQueue[i]._patientID << "\t\t\t" << _waitingQueue[i]._name;
			std::cout << "\n --------------------------------------------------------------\n";
			_getch();
		}
	}

	void cancelAllAppointments()
	{
		if (isEmpty() || (_frontIndex > _rearIndex))
		{
			std::cout << "\n No appointments have been made. ";
			_getch();
			return;
		}

		else
		{
			std::cout << "\n\n ###### Sure you wanna ditch all patients (y/n)?  ###### ";
			char c = _getch();
			if (c == 'n' || c == 'N')
				return;

			else if (c != 'y' && c != 'Y')
			{
				std::cout << "\n Invalid input. ";
				Sleep(700);
				return;
			}

			//delete _waitingQueue;
			_waitingQueue = NULL;
			_rearIndex = -1;
			_patientCount = 0;

			std::cout << "\n Tearing up the waiting list";
			Sleep(500);
			std::cout << ".";
			Sleep(500);
			std::cout << ".";
			Sleep(500);
			std::cout << ".";
			std::cout << "\n Ditching all patients";
			Sleep(500);
			std::cout << ".";
			Sleep(600);
			std::cout << ".";
			Sleep(800);
			std::cout << ".";
			std::cout << "\n\n All patients successfully sent home or killed.\n";

			_getch();
		}
	}

	void checkIfDocsFree()
	{
		if (isEmpty() || (_frontIndex > _rearIndex))
			std::cout << "\n No one's waiting. Yeah he free ";

		else
			std::cout << "\n No. '" << _patientCount << "' patient(s) are still waiting in the queue. ";
	
		_getch();
	}

	bool isEmpty()
	{
		return _waitingQueue == NULL;
	}

	bool isFull()
	{
		return _rearIndex == _size - 1;
	}
};


