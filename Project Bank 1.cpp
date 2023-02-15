#include <bits/stdc++.h>

using namespace std;


const string FILENAME = "myFile.txt";


void ShowMenu();


enum enListChoices
{
	enShowClientList = 1, enAddNewClient = 2, enDeleteClient = 3, enUpdateClientInfo = 4, enFindClient = 5, enExit = 6
};


struct stClientData
{

	string AccountNumber;
	string PIN;
	string Name;
	string Phone;
	double Balance = 0;
	bool MarkToDelete = false;
	
};


vector <string> Split(string s, string delim)
{

	int pos = 0;
	string word = "";

	vector <string> vstring;

	while ((pos = s.find(delim)) != string::npos)
	{

		word = s.substr(0, pos);

		if (word != "")
		{
			vstring.push_back(word);
		}

		s.erase(0, pos + delim.length());

	}

	if (s != "")
	{
		vstring.push_back(s);
	}

	return vstring;

}


stClientData ConvertLinetoRecordInStructure(string line)
{

	vector <string> vstring = Split(line, "/##/");
	stClientData client;

	client.AccountNumber = vstring[0];
	client.PIN = vstring[1];
	client.Name = vstring[2];
	client.Phone = vstring[3];
	client.Balance = stod(vstring[4]);

	return client;

}


vector <stClientData> LoadClientDataFromFile(string filename)
{

	vector <stClientData> vstclient;

	fstream myfile;
	myfile.open(filename, ios::in);

	if (myfile.is_open())
	{

		string line;
		stClientData client;

		while (getline(myfile, line))
		{

			client = ConvertLinetoRecordInStructure(line);
			vstclient.push_back(client);

		}

		myfile.close();

	}

	return vstclient;

}


void PrintCLientsData_ShowList(stClientData client)
{

	cout << "| " << left << setw(15) << client.AccountNumber;
	cout << "| " << left << setw(15) << client.PIN;
	cout << "| " << left << setw(40) << client.Name;
	cout << "| " << left << setw(25) << client.Phone;
	cout << "| " << left << setw(8) << client.Balance;

}


void ShowClientLIst(vector <stClientData> vstclients)
{

	system("cls");

	cout << "\t\t\t\t\t Clients List (" << vstclients.size() << ") Clients(s)." << endl << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------\n\n";
	cout << "| " << left << setw(15) << "Account Number" << "| " << left << setw(15) << "PIN Code" << "| " << left << setw(40) << "Client Name" << "| " << left << setw(25) << "Phone" << "| " << left << setw(8) << "Balance\n";
	cout << "------------------------------------------------------------------------------------------------------------------------\n\n";

	for (stClientData& c : vstclients)
	{
		PrintCLientsData_ShowList(c);
		cout << endl;
	}


	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

}


bool CheckAccountNumber(stClientData client, string accountNumber)
{

	if (client.AccountNumber == accountNumber)
	{
		return true;
	}

}


bool SearchForAccountNumber(vector <stClientData> vstclient, string accountNumber)
{

	for (stClientData c : vstclient)
	{
		if (CheckAccountNumber(c, accountNumber) == true)
		{
			return true;
		}
	}

	return false;

}


stClientData ReadClientData(vector <stClientData> vstclient)
{

	stClientData c;

	cout << "Please enter the Information of the client you want to add below..\n\n";

	cout << "Enter Account Number? ";
	getline(cin >> ws, c.AccountNumber);


	while (SearchForAccountNumber(vstclient, c.AccountNumber))
	{
		cout << "Client With Account Number [" << c.AccountNumber << "] already Exists, Enter another account Number?  ";
		getline(cin >> ws, c.AccountNumber);
	}

	cout << "Enter PIN? ";
	getline(cin, c.PIN);
	cout << "Enter Name? ";
	getline(cin, c.Name);
	cout << "Enter Phone? ";
	getline(cin, c.Phone);
	cout << "Enter Balance? ";
	cin >> c.Balance;

	return c;

}


string ConvertStructreRecordToLine(stClientData c, string delim)
{

	string line = "";

	line += c.AccountNumber + delim;
	line += c.PIN + delim;
	line += c.Name + delim;
	line += c.Phone + delim;
	line += to_string(c.Balance) + delim;

	return line;

}


void SaveVectorToFile(string filename, vector <stClientData> vstclient)
{

	fstream myfile;
	myfile.open(filename, ios::out);
	if (myfile.is_open())
	{

		string dataline;

		for (stClientData c : vstclient)
		{
			if (c.MarkToDelete == false)
			{
				dataline = ConvertStructreRecordToLine(c, "/##/");
				myfile << dataline << endl;
			}
		}

		myfile.close();

	}

}


void AppendDataToFile(string filename, string NewDataline)
{

	fstream myfile;
	myfile.open(filename, ios::out | ios::app);
	if (myfile.is_open())
	{

		myfile << NewDataline << endl;
		myfile.close();

	}

}


void AddNewClient(vector <stClientData>& vstclient)
{

	char choice = 'n';

	do
	{
		system("cls");

		stClientData client = ReadClientData(vstclient);
		AppendDataToFile(FILENAME, ConvertStructreRecordToLine(client, "/##/"));

		cout << "Do you want add more Clients?  Y/N?  ";
		cin >> choice;

	} while (toupper(choice) == 'Y');

}


string ReadAccountNumber()
{
	string accnum;
	
	cout << "Please enter account Number? ";
	getline(cin >> ws, accnum);

	return accnum;

}


void PrintClientData(stClientData Client)
{

	cout << "The following are the client Data:\n\n";

	cout << left << setw(20) << "Account Number" << right << setw(5) << ": " << Client.AccountNumber << endl;
	cout << left << setw(20) << "Pin Code" << right << setw(5) << ": " << Client.PIN << endl;
	cout << left << setw(20) << "Name" << right << setw(5) << ": " << Client.Name << endl;
	cout << left << setw(20) << "Phone" << right << setw(5) << ": " << Client.Phone << endl;
	cout << left << setw(20) << "Account Balance" << right << setw(5) << ": " << Client.Balance << endl << endl;

}


stClientData FindClientByAccountNumber(string AccountNumber, vector <stClientData> vstclient)
{

	stClientData client;
	
	for (stClientData c : vstclient)
	{
		if (c.AccountNumber == AccountNumber)
		{
			client = c;
			return client;
		}
	}

}


void MarkClientForDelete(vector <stClientData>& vstclient, string accountnumber)
{

	for (stClientData& c : vstclient)
	{
		if (c.AccountNumber == accountnumber)
		{
			c.MarkToDelete = true;
		}
	}

}


void DeleteClient(vector <stClientData> vstclient)
{

	string acc = ReadAccountNumber();

	if (SearchForAccountNumber(vstclient, acc) == false)
	{
		cout << "CLient With Account number (" << acc << ") is not found!\n\n";
	}
	
	else
	{
		
		PrintClientData(FindClientByAccountNumber(acc, vstclient));

		char choice = 'n';

		cout << "Are you sure you want to delete this Client?  Y/N?  ";
		cin >> choice;

		if (toupper(choice) == 'Y')
		{

			MarkClientForDelete(vstclient, acc);
			SaveVectorToFile(FILENAME, vstclient);

			//refresh
			vstclient = LoadClientDataFromFile(FILENAME);

			cout << "Client Deleted Succesfully.\n\n";

		}

	}


}


stClientData AskForNewClientDataToUpdate(stClientData& client)
{

	cout << "Please enter New PIN?  ";
	getline(cin >> ws, client.PIN);
	cout << "Please enter new Name?  ";
	getline(cin, client.Name);
	cout << "PLease enter New Phone Number?  ";
	getline(cin, client.Phone);
	cout << "Please enter New Account Balance?  ";
	cin >> client.Balance;

	return client;

}


void UpdateClientData(vector <stClientData>& vstclient, string filename)
{

	string acc = ReadAccountNumber();

	if (SearchForAccountNumber(vstclient, acc) == false)
	{
		cout << "Client with Account Number (" << acc << ") is not found!\n\n";
	}

	else
	{

		PrintClientData(FindClientByAccountNumber(acc, vstclient));

		char choice = 'n';

		cout << "Are you sure you want to update this client?  Y/N?  ";
		cin >> choice;

		if (toupper(choice) == 'Y')
		{
			for (stClientData& c : vstclient)
			{
				if (c.AccountNumber == acc)
				{
					c = AskForNewClientDataToUpdate(c);
					break;
				}
			}

			SaveVectorToFile(filename, vstclient);

			vstclient = LoadClientDataFromFile(filename);

			cout << "Client Updated Successfully.\n\n";

		}

	}

}


void FindClient(vector <stClientData> vstclient)
{

	string acc = ReadAccountNumber();

	if (SearchForAccountNumber(vstclient, acc) == false)
	{
		cout << "Client with Account Number (" << acc << ") is not found!\n\n";
	}

	else
	{
		PrintClientData(FindClientByAccountNumber(acc, vstclient));
	}

}


enListChoices ReadMenuChoice()
{

	short choice = 0;

	do
	{
		cout << "Choose what do you want to do [1 to 6]?   ";
		cin >> choice;

	} while (choice < 1 || choice > 6);

	return enListChoices(choice);

}


void GoBackToMainMenu()
{

	cout << "Press any key to back the main menu..";
	system("pause>0");
	ShowMenu();

}


void StartBankProgram(enListChoices choice)
{

	vector <stClientData> vstclient = LoadClientDataFromFile(FILENAME);


	switch (choice)
	{
	case enShowClientList:
		system("cls");
		ShowClientLIst(vstclient);
		GoBackToMainMenu();
		break;

	case enAddNewClient:
		system("cls");
		AddNewClient(vstclient);
		GoBackToMainMenu();
		break;

	case enDeleteClient:
		system("cls");
		DeleteClient(vstclient);
		GoBackToMainMenu();
		break;

	case enUpdateClientInfo:
		system("cls");
		UpdateClientData(vstclient, FILENAME);
		GoBackToMainMenu();
		break;

	case enFindClient:
		system("cls");
		FindClient(vstclient);
		GoBackToMainMenu();
		break;

	case enExit:
		return;
		break;


	}

}


void ShowMenu()
{

	system("cls");

	cout << "=================================================\n";
	cout << "\t\t Main Menu Screen \n";
	cout << "=================================================\n";
	cout << "\t [1] Show Client List.\n";
	cout << "\t [2] Add new client.\n";
	cout << "\t [3] Delete Client.\n";
	cout << "\t [4] Update Client Info.\n";
	cout << "\t [5] Find CLient.\n";
	cout << "\t [6] Exit.\n";
	cout << "=================================================\n\n";
	
	StartBankProgram(ReadMenuChoice());

}



int main()
{

	ShowMenu();

}