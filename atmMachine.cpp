#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
struct info
{
	string accountNumber = "";
	string codePin = "";
	string userName = "";
	string phoneNumber = "";
	double balance = 0;
	int indexOfTheClient = 0;
};

/*global variabl*/
info correntClient;
/*global variabl*/
void mainMenu();
enum choses {qWithdraw = 1 , norWithraw = 2 , deposit = 3 , check = 4 , logOut = 5};
vector <string> fileTovectorString(string path);
vector<string> splitString(const string input);
info lineTorecord(string line);
vector <info> linesToInfos(vector <string> lines);
string recordToline(info clinte, string sp);
vector <info> vectorStringtovectorInfo(vector <string> dataClients);
void vectorInfosTofile(vector <info> records);
void returnMainMenu();
bool findClient(string path, string accountNumber , bool flag);
void changeFileData(info afterChange);
void logIn();
void logOUT();
void balance();
void deposite();
void withdraw();
void quickWithraw();
int main()
{
	logIn();
	mainMenu();
}

vector <string> fileTovectorString(string path)
{
	vector <string> dataClients;
	string line;
	fstream f;
	f.open(path, ios::in);
	while (getline(f, line))
	{
		dataClients.push_back(line);
	}
	f.close();
	return dataClients;
}
vector<string> splitString(const string input) {
	vector<string> result;
	string::size_type start = 0;
	string::size_type end = 0;
	const string separator = "##";
	while ((end = input.find(separator, start)) != string::npos) {
		if (end != start) { // Only add non-empty substrings to the result
			result.push_back(input.substr(start, end - start));
		}
		start = end + separator.length();
	}

	// Add the last substring after the last separator
	if (start < input.length()) {
		result.push_back(input.substr(start));
	}

	return result;
}
info lineTorecord(string line)
{
	vector<string> data = splitString(line);
	info clientData;
	clientData.accountNumber = data[0];
	clientData.codePin = data[1];
	clientData.userName = data[2];
	clientData.phoneNumber = data[3];
	clientData.balance = stod(data[4]);
	return clientData;
} 
vector <info> linesToInfos(vector <string> lines)
{
	vector <info> records;
	info record;
	for (string& oneLine : lines)
	{
		record = lineTorecord(oneLine);
		records.push_back(record);
	}
	return records;
}
vector <info> vectorStringtovectorInfo(vector <string> dataClients)
{
	vector <info> records;
	for (string& line : dataClients)
	{
		records.push_back(lineTorecord(line));
	}
	return records;
}
string recordToline(info clinte, string sp = "##")
{
	string str = "";
	str += clinte.accountNumber + sp + clinte.codePin + sp + clinte.userName + sp + clinte.phoneNumber + sp + to_string(clinte.balance);
	return str;
}
void vectorInfosTofile(vector <info> records);
void vectorInfosTofile(vector <info> records)
{
	fstream f;
	f.open("file.txt", ios::out);
	for (info& oneRecord : records)
	{
		f << recordToline(oneRecord) << endl;
	}
	f.close();
}
bool findClient(string path, string accountNumber , bool flag = true)
{
	vector <string> theLines = fileTovectorString(path);
	vector <info> Records = linesToInfos(theLines);
	int i = 0;
	for (info& one : Records)
	{
		if (flag == true)
		{
			if (one.accountNumber == accountNumber)
			{
				//correntClient = one;
				return true;
			}
		}
		if (flag == false)
		{
			if (one.codePin == accountNumber)
			{
				correntClient = one;
				correntClient.indexOfTheClient = i;
				return true;
			}
			i++;
		}
	}
	return false;
}
void returnMainMenu()
{
	cout << "\n\n\t press any key to return to the main menu";
	system("pause>0");
	mainMenu();
}
void logIn()
{
	cout << "======================================" << endl;
	cout << "======================================" << endl;
	cout << "\n\t    LOG IN SCREEN\n" << endl;
	cout << "======================================" << endl;
	cout << "======================================" << endl;
	cout << endl;
	cout << "Enter the account number" << endl;
	string accountNumber , pinCode ;
	cin >> accountNumber;
	cout << "Enter the pin code" << endl;
	cin >> pinCode;
	while ((findClient ("file.txt" , accountNumber) && findClient ("file.txt" , pinCode , false)) == false)
	{
		system("cls");
		cout << "======================================" << endl;
		cout << "======================================" << endl;
		cout << "\n\t    LOG IN SCREEN\n" << endl;
		cout << "======================================" << endl;
		cout << "======================================" << endl;
		cout << "\nUser name and pin code are wrong try again" << endl;
		cout << "Enter the account number" << endl;
		cin >> accountNumber;
		cout << "Enter the pin code" << endl;
		cin >> pinCode;
	}
}
void mainMenu()
{
	system("cls");
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "\n\t ATM MACHINE" << endl;
	cout << "\t WELLCOME MR/MS : " << correntClient.userName << endl;
	cout << "\n===========================================\n" << endl;
	cout << "  MACHINE SERVECIES : " << endl;
	cout << "\t[1] Quik withdraw ." << endl;
	cout << "\t[2] Normal withdraw ." << endl;
	cout << "\t[3] Deposit" << endl;
	cout << "\t[4] Check balance ." << endl;
	cout << "\t[5] Log out .\t" << endl;
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "  Enter number of the service : ";
	short ch;
	cin >> ch;
	switch (ch)
	{
	case choses::qWithdraw :
		quickWithraw();
		break;

	case choses::norWithraw:
		withdraw();
		break;

	case choses::deposit :
		deposite();
		break;

	case choses::check :
		balance();
		break;

	case choses::logOut :
		logOUT();
		break;
	}
}
void logOUT()
{
	system("cls");
	logIn();
	mainMenu();
}
void balance()
{
	system("cls");
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "\nYour balance is : " << correntClient.balance << "\n" << endl;
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	returnMainMenu();
}
void changeFileData(info afterChange)
{
	vector <string> lines = fileTovectorString("file.txt");
	vector <info> records = linesToInfos(lines);
	records[afterChange.indexOfTheClient] = afterChange;
	fstream f;
	f.open("file.txt", ios::out);
	for (info& one : records)
	{
		f << recordToline(one) << endl;
	}
	f.close();
}
void deposite()
{
	system("cls");
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "\nDEPOSTE SCREEN you have : " << correntClient.balance << "\n" << endl;
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "Enter how many you want to deposite : ";
	double amount;
	cin >> amount;
	correntClient.balance += amount;
	cout << "Your New balance is : " << correntClient.balance;
	changeFileData(correntClient);
	returnMainMenu();
}
void withdraw()
{
	system("cls");
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "\nWITHDRAW SCREEN you have : " << correntClient.balance << "\n" << endl;
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "Enter how many you want to withraw : ";
	double amount;
	cin >> amount;
	if (amount > correntClient.balance)
	{
		cout << "your dont have enough money";
	}
	else
	{
		correntClient.balance -= amount;
		changeFileData(correntClient);
		cout << "your new balanace is : " << correntClient.balance;
	}
	returnMainMenu();
}
void quickWithraw()
{
	system("cls");
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "\nQUICK WITHDRAW SCREEN you have : " << correntClient.balance << "\n" << endl;
	cout << "===========================================" << endl;
	cout << "===========================================" << endl;
	cout << "  The options : " << endl;
	cout << "    [1] - 100    [2] - 500" << endl;
	cout << "    [3] - 1000   [4] - 10000" << endl;
	cout << "   enter your option : ";
	short op;
	cin >> op;
	switch (op)
	{
	case 1 :
		if (100 > correntClient.balance)
		{
			cout << "Sorry your cant do this oprerator " << endl;
			break;
		}
		else
		{
			correntClient.balance -= 100;
			cout << "Your new balance is : " << correntClient.balance << endl;
		}
		break;
	case 2:
		if (500 > correntClient.balance)
		{
			cout << "Sorry your cant do this oprerator " << endl;
			break;
		}
		else
		{
			correntClient.balance -= 500;
			cout << "Your new balance is : " << correntClient.balance;
		}
		break;
	case 3:
		if (1000 > correntClient.balance)
		{
			cout << "Sorry your cant do this oprerator " << endl;
			break;
		}
		else
		{
			correntClient.balance -= 1000;
			cout << "Your new balance is : " << correntClient.balance;
		}
		break;
	case 4:
		if (10000 > correntClient.balance)
		{
			cout << "Sorry your cant do this oprerator " << endl;
			break;
		}
		else
		{
			correntClient.balance -= 10000;
			cout << "Your new balance is : " << correntClient.balance;
		}
		break;
	}
	changeFileData(correntClient);
	returnMainMenu();
}