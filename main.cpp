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
	string phoneNumber ="";
	double balance = 0;
	bool flage = false;
};
struct userINfo
{
	string user = "", pinCode = "";
	int access = 0;
	bool flag = false;
};

userINfo cor;

void gomainMenu()
{
	cout << "\n\nPress any key to go to the Main menu" << endl;
	system("pause>0");
}



/*THE MAIN FUNCTIONS*/
void showClientlist(string path);
void addNewclient(string path);
void deleteClient(string path, string accountNumber);
void updateClientinfo(string path, string accountNumber);
bool findClient(string path, string accountNumber, int flag);
//void exit();
void transactions();

/*THE MAIN FUNCTIONS*/


/*HELPPER FUNCTIONS*/
vector <string> fileTovectorString(string path);
info lineTorecord(string line);
vector<string> splitString(const string input);
vector <info> linesToInfos(vector <string> lines);
void printtheinforecord(info cl);
info readClientdata();
vector <info> vectorStringtovectorInfo(vector <string> data);
void vectorInfosTofile(vector <info> records);
void markToDelete(vector <info>& Records, string accountNumber);
info readTheupdate(string accountNum);
int numberOflines(string path);
void printUser(userINfo s);
/*HELPPER FUNCTIONS*/

bool findClient(string path, string accountNumber, int flag);

/*requarment2*/
void deposit(string path, string accountNumber);
void withDraw(string path, string accountNumber);
double totalBalance(string path);
void mainMe();
/*requarment2*/


/*requarment3*/
void logIn();
vector <userINfo> linesToUsers(vector <string> lines);
userINfo lineToUser(string line);
bool findUser(string path , string p , int flag);

void manageUeser(string path);
void headreListUser();
void printUserinfo(userINfo us);


void showUserList(string path);

void addNewUser(string path);
int giveAcces(userINfo& us);
void resutlbool(int& per, int& index, char an, int* arr);
userINfo readUserinfo();
void deleteUser(string path, string us);
userINfo readTHEup();
void upDateUser(string path, string usr);
bool findUser(string path, string usr, bool flag);
/*requarment3*/



bool checkPer(int userPer, int acc)
{
	if (userPer == -1)
		return true;
	if ((acc & userPer) == acc)
		return true;
	else
		return false;
}

void runMenu()
{
	system("cls");
	short op;
	cout << "==================================================" << endl;
	cout << "\t\t Main menu screen" << endl;
	cout << "==================================================" << endl;
	cout << "\t [1] Show Client List ." << endl;
	cout << "\t [2] Add New Client ." << endl;
	cout << "\t [3] Delete Client ." << endl;
	cout << "\t [4] Update Client Info ." << endl;
	cout << "\t [5] Find Client ." << endl;
	cout << "\t [6] Transaction Menu . " << endl;
	cout << "\t [7] Manage Users Menu ." << endl;
	cout << "\t [8] Logout ." << endl;
	cout << "==================================================" << endl;
	cout << "Choose What Do Want TO Do ? [1 TO 8] ? ";
	cin >> op;
	string data;
	switch (op)
	{
	case 1:
		showClientlist("file.txt");
		break;

	case 2:
		addNewclient("file.txt");
		break;
	case 3:
		system("cls");
		cout << "Enter the account number ";
		cin >> data;
		deleteClient("file.txt", data);
		break;
	case 4:
		system("cls");
		cout << "Enter the account number ";
		cin >> data;
		updateClientinfo("file.txt", data);
		break;
	case 5:
		system("cls");
		cout << "Enter the account number ";
		cin >> data;
		findClient("file.txt", data, 1);
		break;
	case 6 :
		transactions();
		break;
	case 7 :
		manageUeser("user.txt");
		break;
	case 8:
		logIn();
		break;

	}
}



int main()
{
	logIn();
	runMenu();
	return 0;
}


int numberOflines(string path)
{
	fstream f; 
	f.open(path, ios::in);
	int con = 0;
	string line;
	while (getline (f , line))
	{
		con++;
	}
	return con;
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
	//cout << lines[5] << endl;
	for (string& oneLine : lines)
	{
		record = lineTorecord(oneLine);
		records.push_back(record);
	}
	return records;
}
void printtheinforecord(info cl)
{
	//theHeader();
	cout << setw(0) << "| " << cl.accountNumber << setw(20) << "| " << cl.codePin << setw(15) << "| " << cl.userName << setw(12) << "| " << cl.phoneNumber << setw(19) << "| " << cl.balance << endl;

}

/*-----1------*/
void showClientlist(string path)
{
	if (checkPer(cor.access, 1) == false)
	{
		system("cls");
		cout << "You dont have permetion on this Contect the admin";
		return;
	}
	system("cls");
	//cout << "                                      client list ( ) client(s)                               " << endl;
	printf("                                      client list (%d) client(s)                               \n", numberOflines(path));
	cout << "______________________________________________________________________________________________" << endl;
	cout << setw(14) << "| Account Num " << setw(20) << "| pin code" << setw(20) << "| user name" << setw(20) << "| phone nums" << setw(20) << "| balance" << endl;
	cout << "______________________________________________________________________________________________" << endl;
	cout << endl;
	vector <string> dataClientsLines = fileTovectorString(path);
	vector <info> records = linesToInfos(dataClientsLines);
	for (info& oneRecored : records)
	{
		printtheinforecord(oneRecored);
	}
	gomainMenu();
	runMenu();
}
/*-----1------*/



info readClientdata()
{
	info cl;
	cout << "Enter number account ";
	getline(cin >> ws, cl.accountNumber);
	
	while (findClient ("file.txt" , cl.accountNumber , 0))
	{
		cout << "isExist Enter A new one : " ;
		getline(cin, cl.accountNumber);
	}

	cout << "enter the pin code ";
	getline(cin, cl.codePin);
	cout << "enter the useer name ";
	getline(cin, cl.userName);
	cout << "enter the phone number ";
	getline(cin, cl.phoneNumber);
	cout << "enter the balance ";
	cin >> cl.balance;
	return cl;
}
string recordToline(info clinte, string sp = "##")
{
	string str = "";
	str += clinte.accountNumber + sp + clinte.codePin + sp + clinte.userName + sp + clinte.phoneNumber + sp + to_string(clinte.balance);
	return str;
}
void lineTofile(string path, string line)
{
	fstream f;
	f.open(path, ios::out | ios::app);
	f << line << endl;
	f.close();
}

/*-----2------*/
void addNewclient(string path)
{
	if (checkPer(cor.access, 2) == false)
	{
		system("cls");
		cout << "You dont have permetion on this Contect the admin";
		return;
	}
	system("cls");
	char more;
	do
	{
		system("cls");
		info client = readClientdata();
		string line = recordToline(client);
		lineTofile(path, line);
		cout << "adding succefully" << endl;
		cout << "Do you want add more y/N ? ";
		cin >> more;
	} while (more == 'Y' || more == 'y');
	gomainMenu();
	runMenu();
}
/*-----2------*/


vector <info> vectorStringtovectorInfo(vector <string> dataClients)
{
	vector <info> records;
	for (string& line : dataClients)
	{
		records.push_back(lineTorecord(line));
	}
	return records;
}
void vectorInfosTofile(vector <info> records)
{
	fstream f;
	f.open("file.txt", ios::out);
	for (info& oneRecord : records)
	{
		if (oneRecord.flage == false)
			f << recordToline(oneRecord) << endl;
	}
	f.close();
}
void markToDelete(vector <info>& Records, string accountNumber)
{
	for (info& one : Records)
	{
		if (one.accountNumber == accountNumber)
		{
			one.flage = true;
			return;
		}
	}
	cout << "Doen not exist" << endl;
}

/*-----3------*/
void deleteClient(string path, string accountNumber)
{
	if (checkPer(cor.access, 4) == false)
	{
		system("cls");
		cout << "You dont have permetion on this Contect the admin";
		return;
	}
	//system("cls");
	vector <string> theLines = fileTovectorString(path);
	vector <info> records = linesToInfos(theLines);
	markToDelete(records, accountNumber);
	fstream f;
	f.open(path, ios::out);
	for (info& one : records)
	{
		if (one.flage == false)
		{
			f << recordToline(one) << endl;
		}
	}
	f.close();
	cout << "Done" << endl;
	gomainMenu();
	runMenu();
}
/*-----3------*/


info readTheupdate(string accountNum)
{
	info up;
	up.accountNumber = accountNum;
	cout << "enter the user name ";
	getline(cin >> ws, up.userName);
	cout << "enter the Phone Number ";
	getline(cin, up.phoneNumber);
	cout << "enter the code pine ";
	getline(cin, up.codePin);
	cout << "Enter the new balance ";
	cin >> up.balance;
	return up;
}

/*-----4------*/
void updateClientinfo(string path, string accountNumber)
{
	if (checkPer(cor.access, 8) == false)
	{
		system("cls");
		cout << "You dont have permetion on this Contect the admin";
		return;
	}
	//system("cls");
	vector <string> theLines = fileTovectorString(path);
	vector <info> Records;
	for (string& line : theLines)
	{
		Records.push_back(lineTorecord(line));
	}
	for (info& one : Records)
	{
		if (one.accountNumber == accountNumber)
		{
			one = readTheupdate(one.accountNumber);
		}
	}
	fstream f;
	f.open(path, ios::out);
	for (info& one : Records)
	{
		f << recordToline(one) << endl;
	}
	cout << "Done" << endl;
	f.close();
	gomainMenu();
	runMenu();
}
/*-----4------*/

/*-----5------*/
bool findClient(string path, string accountNumber, int flag)
{
	if (checkPer(cor.access, 16) == false)
	{
		system("cls");
		cout << "You dont have permetion on this Contect the admin";
		return true;
	}
	if (flag == 1)
		system("cls");
	vector <string> theLines = fileTovectorString(path);
	vector <info> Records = linesToInfos(theLines);
	for (info& one : Records)
	{
		if (one.accountNumber == accountNumber)
		{
			if (flag == 1)
			{
				//cout << "                                      client list ( ) client(s)                               " << endl;
				cout << "______________________________________________________________________________________________" << endl;
				cout << setw(14) << "| Account Num " << setw(20) << "| pin code" << setw(20) << "| user name" << setw(20) << "| phone nums" << setw(20) << "| balance" << endl;
				cout << "______________________________________________________________________________________________" << endl;
				cout << endl;
				printtheinforecord(one);
			}
			return true;
		}
	}
	if (flag == 1)
	{
		cout << "not exist" << endl;
	}
	return false;
}
/*-----5------*/

void deposit(string path, string accountNumber)
{
	if (findClient(path, accountNumber, 0) == false)
		cout << "Does Not Exist" << endl;
	vector <string> lines = fileTovectorString(path);
	vector <info> records = linesToInfos(lines);
	for (info& one : records)
	{
		if (one.accountNumber == accountNumber)
		{
			printtheinforecord(one);
			cout << "Do You Want Deposit y/n ? ";
			char c;
			cin >> c;
			if (c == 'y')
			{
				cout << "Enter the amount : ";
				double am;
				cin >> am;
				one.balance += am;
				cout << "done\n" << "the new balace is : " << one.balance << endl;
			}
			
		}
	}
	gomainMenu();
	transactions();
}
void withDraw(string path, string accountNumber)
{
	vector <string> lines = fileTovectorString(path);
	vector <info> records = linesToInfos(lines);
	for (info& one : records)
	{
		if (one.accountNumber == accountNumber)
		{
			printtheinforecord(one);
			char c;
			cout << "Do you want to take your money : n/Y ? "; 
			cin >> c;
			if (c == 'y')
			{
				double amount;
				cout << "Enter the amount : ";
				cin >> amount;
				while (amount > one.balance)
				{
					cout << "You do not have this Enter another amount : ";
					cin >> amount;
				}
				one.balance -= amount;
				cout << "withdrawing done the new balance is : " << one.balance;
			}
			else
			{
				transactions();
			}
		}
	}
	gomainMenu();
	transactions();
}
double totalBalance(string path)
{
	vector <string> lines = fileTovectorString(path);
	vector <info> records = linesToInfos(lines);
	double s = 0;
	for (info& one : records)
	{
		s = s + one.balance;
	}
	return s;
}
void mainMe()
{
	runMenu();
}

/*-----6------*/
void transactions()
{
	if (checkPer(cor.access, 32) == false)
	{
		system("cls");
		cout << "You dont have permetion on this Contect the admin";
		return;
	}
	system("cls");
	cout << "==================================================" << endl;
	cout << "\t\tTransaction Menu screen" << endl;
	cout << "==================================================" << endl;
	cout << "\t [1] Deposit ." << endl;
	cout << "\t [2] Withdraw ." << endl;
	cout << "\t [3] Total Balance ." << endl;
	cout << "\t [4] Main menu ." << endl;
	cout << "==================================================" << endl;
	short ch;
	string accNum;
	cin >> ch;
	switch (ch)
	{
	case 1 :
		cout << "Enter The accout number" << endl ;
		cin >> accNum;
		while (findClient ("file.txt" , accNum , 0) == false)
		{
			cout << "Enter Another one : ";
			cin >> accNum;
		}
		deposit("file.txt", accNum);
		break;
	case 2 :
		cout << "Enter The accout number" << endl;
		cin >> accNum;
		while (findClient("file.txt", accNum, 0) == false)
		{
			cout << "Enter Another one : ";
			cin >> accNum;
		}
		withDraw("file.txt", accNum);
		break;
	case 3 :
		cout << "The TOTAL Balance in the Bank is : " << totalBalance("file.txt");
		gomainMenu();
		transactions();
		break;
	case 4:
		mainMe();
		break;
	}
}
/*-----6------*/


/*----------------------------------------------------------*/




void printUser(userINfo s)
{
	cout << endl;
	cout << "--------------------------------" << endl;
	cout << "the user is  :  " << s.user << endl ;
	cout << "the pin code is  :  " << s.pinCode << endl;
	cout << "the accss is  :  " << s.access << endl;
	cout << "---------------------------------" << endl;
}

userINfo lineToUser(string line)
{
	userINfo u;
	vector <string> t = splitString(line);
	u.user = t[0];
	u.pinCode = t[1];
	u.access = (int)stod(t[2]);
	return u;
}
vector <userINfo> linesToUsers(vector <string> lines)
{
	vector <userINfo> records;
	userINfo record;
	//cout << lines[5] << endl;
	for (string& oneLine : lines)
	{
		record = lineToUser(oneLine);
		records.push_back(record);
	}
	return records;
}
bool findUser(string path , string p , int flag)
{
	vector <string> lines = fileTovectorString(path);
	vector <userINfo> records = linesToUsers(lines);
	//cout << records[0].pinCode;
	for (userINfo& one : records)
	{
		if (flag == 1)
		{
			if (one.user == p)
				return true;
		}
		else
		{
			if (one.pinCode == p)
				return true;
		}
	}
	return false;
}

void getper(string path, string usr)
{
	vector <string> lines = fileTovectorString("user.txt");
	vector <userINfo> records = linesToUsers(lines);
	for (userINfo& one : records)
	{
		if (one.user == usr)
		{
			cor = one;
			return;
		}
	}
}

void logIn()
{
	system("cls");
	cout << "-----------------------------------------" << endl;
	cout << "\t  Log in Screen" << endl;
	cout << "-----------------------------------------" << endl;
	vector <string> lines = fileTovectorString("user.txt");
	vector <userINfo> records = linesToUsers(lines);

	string us = "", pin = "";
	cout << endl;
	cout << "enter the user name : ";
	cin >> us;
	cout << "enter the code pine : ";
	cin >> pin;
	while ((findUser ("user.txt" , us , 1) && findUser("user.txt" , pin , 0)) == false)
	{
		cout << "USER/PASSEWORD IS UNCORECT" << endl;
		cout << "enter the user name : ";
		cin >> us;
		cout << "enter the code pine : ";
		cin >> pin;
		
		system("cls");

	}
	getper("user.txt", us);
	system("cls");
}


void headreListUser()
{
	cout << "--------------------------------------" << endl;
	cout << endl;
	cout << setw(0) << "user" << setw(17) << "pass" << setw(17) << "acces" << endl;
	cout << endl;
	cout << "--------------------------------------" << endl;
	cout << endl;
	
}
void printUserinfo(userINfo us)
{
	cout << setw(0) << us.user << setw(16) << us.pinCode << setw(16) << us.access << endl;
	cout << endl;
}


void showUserList(string path)
{
	system("cls");
	vector <string> lines = fileTovectorString(path);
	vector <userINfo> records = linesToUsers(lines);
	headreListUser();
	for (userINfo& one : records)
	{
		printUserinfo(one);
	}
	gomainMenu();
	manageUeser(path);
}


void resutlbool(int& per, int& index, char an ,int* arr)
{
	cin >> an;
	if (an == 'y' || an == 'Y')
	{
		per += arr[index];
		index++;
	}
	else
	{
		index++;
	}
}

int giveAcces(userINfo& us)
{
	int arr[] = { 1,2,4,8,16,32,64 };
	int per = 0;
	char ch = ' ';
	int i = 0; 
	cout << "Do you want to give to show Client list y/N ? : ";
	resutlbool(per, i, ch, arr);
	cout << "Do you want to give to Add new client y/N ? : ";
	resutlbool(per, i, ch, arr);
	cout << "Do you want to give to Delete client y/N ? : ";
	resutlbool(per, i, ch, arr);
	cout << "Do you want to give to Update client y/N ? : ";
	resutlbool(per, i, ch, arr);
	cout << "Do you want to give to Find client y/N ? : ";
	resutlbool(per, i, ch, arr);
	cout << "Do you want to give to Transaction y/N ? : ";
	resutlbool(per, i, ch, arr);
	cout << "Do you want to give to Manage user y/N ? : ";
	resutlbool(per, i, ch, arr);

	return per;
}
userINfo readUserinfo()
{
	userINfo us;
	cout << "Enter the user name" << endl;
	getline(cin >> ws, us.user);
	cout << "Enter the pin code" << endl;
	getline(cin , us.pinCode);
	cout << "The acces : " << endl;
	us.access = giveAcces(us);
	return us;
}

void userInfoToFile(userINfo us , string path)
{
	fstream f;
	f.open(path, ios::app | ios::out);
	f << us.user << "##" << us.pinCode << "##" << us.access << endl;
	f.close();
}


void addNewUser(string path)
{
	char ch = 'y';
	do
	{
		system("cls");
		cout << "--------------------------------------" << endl;
		cout << endl;
		cout << "\t Add new user screen" << endl;
		cout << endl;
		cout << "--------------------------------------" << endl;
		cout << endl;
		userINfo us = readUserinfo();
		userInfoToFile(us, path);
		cout << endl;
		cout << "Do you want add more user n/Y ? : ";
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	cout << endl;
	gomainMenu ();
	manageUeser(path);
}

void toDelete(vector <userINfo>& all, string usr)
{
	for (userINfo& one : all)
	{
		if (one.user == usr)
			one.flag = true;
	}
}

void deleteUser(string path, string us)
{
	//system("cls");
	vector <string> lines = fileTovectorString(path);
	vector <userINfo> records = linesToUsers(lines);
	cout << "Do you want Delet the user y/N ? ";
	char c;
	cin >> c;
	if (c == 'y')
	{
		toDelete(records, us);
		fstream f;
		f.open(path, ios::out);
		for (userINfo& one : records)
		{
			if (one.flag == false)
			{
				f << one.user << "##" << one.pinCode<< "##" << one.access << endl;
			}
		}
		f.close();
	}
	gomainMenu();
	manageUeser(path);
}


userINfo readTHEup()
{
	userINfo us;
	cout << "Enter the pin code" << endl;
	getline(cin >> ws, us.pinCode);
	cout << "The acces : " << endl;
	us.access = giveAcces(us);
	return us;

}

void upDateUser(string path, string usr)
{
	vector <string> lines = fileTovectorString(path);
	vector <userINfo> records = linesToUsers(lines);
	for (userINfo& one : records)
	{
		if (one.user == usr)
		{
			cout << "Do you want to Update this account n/y : ";
			char c;
			cin >> c;
			if (c == 'y')
			{
				one = readTHEup();
				one.user = usr;
			}
			else
			{
				gomainMenu();
				manageUeser(path);
			}
		}
	}
	fstream f;
	f.open(path, ios::out);
	for (userINfo& one : records)
	{
		f << one.user << "##" << one.pinCode << "##" << one.access << endl;
	}
	cout << "\nDone" << endl;
	gomainMenu();
	manageUeser(path);
}


bool findUser(string path, string usr, bool flag = 1)
{
	vector <string> lines = fileTovectorString(path);
	vector <userINfo> records = linesToUsers(lines);
	for (userINfo& one : records)
	{
		if (one.user == usr)
		{
			if (flag == 1)
			{
				printUser(one);
				gomainMenu();
				manageUeser(path);
			}
			return true;
		}
	}
	if (flag == 1)
	{
		cout << "Does not exist " << endl;
		gomainMenu();
		manageUeser(path);
	}
	return false;
}




void manageUeser(string path)
{
	if (checkPer(cor.access, 64) == false)
	{
		system("cls");
		cout << "You dont have permetion on this Contect the admin";
		return;
	}
	system("cls");
	cout << "==================================================" << endl;
	cout << "\t\t Manage Users screen" << endl;
	cout << "==================================================" << endl;
	cout << "\t [1] Show user List ." << endl;
	cout << "\t [2] Add New user ." << endl;
	cout << "\t [3] Delete user ." << endl;
	cout << "\t [4] Update user Info ." << endl;
	cout << "\t [5] Find user ." << endl;
	cout << "\t [6] Main menu . " << endl;
	cout << "==================================================" << endl;
	cout << "Choose What Do Want TO Do ? [1 TO 6] ? ";
	short ch = 0;
	cin >> ch;
	string data = "";
	switch (ch)
	{
	case 1 :
		showUserList(path);
		break;
	case 2: 
		addNewUser(path);
		break;
	case 3 :
		system("cls");
		cout << "Enter the User : ";
		cin >> data;
		deleteUser(path, data);
		break;
	case 4:
		system("cls");
		cout << "Enter the User : ";
		cin >> data;
		upDateUser(path, data);
		break;
	case 5:
		system("cls");
		cout << "Enter the User : ";
		cin >> data;
		findUser(path, data);
		break;
	case 6:
		runMenu();
	}
}