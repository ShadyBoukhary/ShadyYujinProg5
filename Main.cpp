/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*						Shady Boukhary; Yujin Yoshimura							*
*					 CMPS 2132 Object-Oriented Programming						*
*							   Dr. Stringfellow									*
*								HW5: TeamQueue									*
*								  12/06/2017									*
*																				*
*	This program reads from an input file team members of different teams.		*
*	Then, it reads commands to enqueue certain team members or dequeue from		*
*	a team queue. When the command is enqueue, the program checks whether a		*
*	member of the same team already is in the queue. If that is the case, the	*
*	the member is enqueue right behind his team in the queue, skipping all of	*
*	the members of other teams. If that is not the case, the member is then		*
*	enqueued at the very back of the queue, behind all other teams. As members	*
*	are dequeued from the queue, the program prints to the screen and a file	*
*	the members dequeued and their corresponding team number in a nice table	*
*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

#include "TeamQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Opens an input file.
ifstream openInputFile(string file_name);

// Opens an output file in truncate, then delete current content.
void initializeOutputFile();

// Opens an output file in append.
ofstream openOutputFile(string file_name);

// Displays string and exports string into output file.
void exportString(string s);

// Converts an input into number of teams.
// Failure in conversion returns - 1.
int getNumOfTeams(ifstream &myfile);

// Displays and outputs Scenario number.
void printScenario(int& scenario_no);

// Creates an array of teams. The index of the array is the team number.
void createTeams(ifstream &myfile, int** &teams, int num_of_teams);

// Add members into a team. The index of the array is the ID number.
void addMembers(ifstream &myfile, int** teams, int team_no);

// Process Team Queue commands.
void processCommand(ifstream &myfile, int** &teams, int num_of_teams);

// Gets Team Queue command from input file.
string getCommand(ifstream &myfile);

// Check if the input is enqueue.
bool isEnqueue(string line);

// Parse enqueue command and gets ID number of the person enqueued.
int getEnqueueID(string line);

// Searches ID number in the array of teams and tell its team number.
int getTeamNo(int** teams, int num_of_teams, int id_no);

// Check if the input is dequeue.
bool isDequeue(string line);

// Displays and outputs ID number of a member dequeued.
void printID(string);

// Check if the input is stop.
bool isStop(string line);

// Displays and outputs blank line between scenarios.
void printBlankLine();

// Deletes an array of teams and all of its content.
void deleteTeams(int** &teams, int num_of_teams);

// Displays Team number and all members of the team. Debug purpose.
void showTeam(int** teams, int team_no);

// Displays Member's ID and team number. Debug purpose.
void showMember(int id_no, int team_no);

// verifies input for an integer for menu purposes
int validInteger();

//prints header
void printHeader(int);



int main() {
	ifstream infile;
	string infile_name = "prog5data.txt";
	int scenario_no = 1;
	int num_of_teams;
	int** teams;

	infile = openInputFile(infile_name);
	initializeOutputFile();
	printHeader(1);
	// one loop per scenario
	do {
		num_of_teams = getNumOfTeams(infile);
		// if num_of_teams is 0, skip all the process and end the loop
		if (num_of_teams) {
			printScenario(scenario_no);
			createTeams(infile, teams, num_of_teams);
			processCommand(infile, teams, num_of_teams);
			scenario_no++;
		}
	} while (num_of_teams > 0);

	printHeader(2);
	system("pause");
	return 0;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Opens an input file.
* @usage: myfile = openInputFile("input.txt");
* @param: string
* @return: ifstream
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
ifstream openInputFile(string file_name) {
	int choice = 0;
	cout << "Would you like to Enter input filename? DEFAULT: prog5data.txt\n";
	cout << "1. YES\n2. Use Default\n";
	choice = validInteger();
	system("cls");

	if (choice == 1)
	{
		cout << "Enter input file name: ";
		cin.ignore();
		getline(cin, file_name);
	}

	system("cls");
	ifstream myfile;

	// try to open input file

	try
	{
		myfile.open(file_name.c_str());
		if (!myfile.is_open())
			throw string("Unable to open file. Terminating\n");
	}
	catch (string message)
	{
		cout << message;
		system("pause");
		exit(1);
	}
	return myfile;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Opens an output file in truncate, then delete current content.
* @usage: initializeOutputFile();
* @param: string
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void initializeOutputFile() {
	string file_name = "prog5output.txt";
	ofstream myfile;
	try
	{
		myfile.open(file_name, ios_base::trunc);
		if (!myfile)
			throw string("Unable to open output file.Terminating\n");
		else
			myfile.close();
	}
	catch (string error)
	{
		cout << error;
		system("pause");
		exit(1);
	}
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Opens an output file in append.
* @usage: myfile = openOutputFile("output.txt");
* @param: string
* @return: ofstream
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
ofstream openOutputFile(string file_name) {
	ofstream myfile;
	try
	{
		myfile.open(file_name, ios_base::app);
		if (!myfile)
			throw string("Unable to open output file. Terminating\n");
	}
	catch (string error)
	{
		cout << error;
		system("pause");
		exit(1);
	}
	return myfile;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Displays string and exports string into output file.
* @usage: exportString("Hello World!");
* @param: string
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void exportString(string s) {
	string file_name = "prog5output.txt";
	ofstream myfile = openOutputFile(file_name);

	cout << s;
	myfile << s;
	myfile.close();

}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Converts an input into number of teams.
* Failure in conversion returns -1.
* @usage: num_of_teams = getNumOfTeams(infile);
* @param: ifstream (pass by reference)
* @return: int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
int getNumOfTeams(ifstream &myfile) {
	string line;
	int num_of_teams;

	getline(myfile, line);
	(isdigit(line[0])) ? num_of_teams = stoi(line) : num_of_teams = -1;
	return num_of_teams;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Displays and outputs Scenario number.
* @usage: printScenario(scenario_no);
* @param: int (pass by reference)
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void printScenario(int& scenario_no) {
	exportString("Scenario #" + to_string(scenario_no) + "\n");
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Creates an array of teams. The index of the array is the team number.
* @usage: createTeams(teams, 2)
* @param: pointer to an array of int (pass by reference), int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void createTeams(ifstream &myfile, int** &teams, int num_of_teams) {
	teams = new int*[num_of_teams];
	for (int team_no = 0; team_no < num_of_teams; team_no++) {
		addMembers(myfile, teams, team_no);
	}
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Add members into a team.
* @usage: addMembers(infile, teams, 0)
* @param: ifstream (pass by reference), pointer to an array of int, int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void addMembers(ifstream &myfile, int** teams, int team_no) {
	string line;
	int num_of_members, id_no;
	int* this_team;

	getline(myfile, line);
	stringstream stream(line);
	stream >> num_of_members;
	this_team = new int[num_of_members + 1];
	teams[team_no] = this_team;

	// Since dynamic array cannot tell its length, I store the
	// Number of members of that team in the index 0 of that array.
	this_team[0] = num_of_members;
	for (int member = 1; member <= num_of_members; member++) {
		stream >> id_no;
		this_team[member] = id_no;
	}
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\
* Process Team Queue commands.
* @usage: processCommand(infile, teams, 2);
* @param: ifstream (pass by reference), pointer to an array of int, int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void processCommand(ifstream &myfile, int** &teams, int num_of_teams) {
	string command;
	int id_no;
	string output;
	int team_no;
	bool stop = false;
	TeamQueue<int> q;
	exportString(q.to_string());
	do {
		command = getCommand(myfile);
		if (isEnqueue(command)) {
			id_no = getEnqueueID(command);
			team_no = getTeamNo(teams, num_of_teams, id_no);
			q.enqueue(id_no, team_no);
		}
		else if (isDequeue(command)) {
			output = q.dequeue();
			printID(output);
		}
		else if (isStop(command)) {
			printBlankLine();
			deleteTeams(teams, num_of_teams);
			stop = true;
		}
	} while (!stop);
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\
* Gets Team Queue command from input file.
* @usage: command = getCommand(infile);
* @param: ifstream (pass by reference)
* @return: string
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
string getCommand(ifstream &myfile) {
	string line;
	getline(myfile, line);
	return line;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Check if the input is enqueue.
* @usage: if(isEnqueue("ENQUEUE 101"))
* @param: string
* @return: bool
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
bool isEnqueue(string line) {
	stringstream stream(line);
	string command;
	bool enqueue = false;

	stream >> command;
	if (command == "ENQUEUE")
		enqueue = true;
	return enqueue;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Parse enqueue command and gets ID number of the person enqueued.
* @usage: id_no = getEnqueueID("ENQUEUE 101");
* @param: string
* @return: int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
int getEnqueueID(string line) {
	stringstream stream(line);
	string command;
	int id_no = -1;

	stream >> command >> id_no;
	return id_no;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Searches ID number in the array of teams and tell its team number.
* @usage: team_no = getTeamNo(teams, 2, 101);
* @param: pointer to an array of int (pass by pointer), int, int
* @return: int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
int getTeamNo(int** teams, int num_of_teams, int id_no) {
	int team_no = -1;
	int index = 0;
	int num_of_members = 0;
	int member;
	int* this_team;
	bool found = false;

	// Search algorithm is linear search, as ID numbers are not sorted.
	while (!found && index < num_of_teams) {
		this_team = teams[index];
		num_of_members = this_team[0];
		member = 1;
		while (!found && member <= num_of_members) {
			if (id_no == this_team[member]) {
				team_no = index;
				found = true;
			}
			member++;
		}
		index++;
	}

	return team_no;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Check if the input is dequeue.
* @usage: if(isDequeue("DEQUEUE"))
* @param: string
* @return: bool
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
bool isDequeue(string line) {
	stringstream stream(line);
	string command;
	bool dequeue = false;

	stream >> command;
	if (command == "DEQUEUE")
		dequeue = true;
	return dequeue;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Displays and outputs ID number of a member dequeued.
* @usage: printID(101);
* @param: int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void printID(string output) {
	exportString(output);
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Check if the input is stop.
* @usage: if(isStop("STOP"))
* @param: string
* @return: bool
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
bool isStop(string line) {
	stringstream stream(line);
	string command;
	bool stop = false;

	stream >> command;
	if (command == "STOP")
		stop = true;
	return stop;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Displays and outputs blank line between scenarios.
* @usage: printBlankLine();
* @param: int (pass by reference)
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void printBlankLine() {
	exportString("\n");
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Deletes an array of teams and all of its content.
* @usage: deleteTeams(teams, 2);
* @param: pointer to an array of int (pass by pointer), int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void deleteTeams(int** &teams, int num_of_teams) {
	for (int team_no = 0; team_no < num_of_teams; team_no++) {
		delete[] teams[team_no];
		teams[team_no] = nullptr;
	}
	delete[] teams;
	teams = nullptr;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Displays Team number and all members of the team. Debug purpose.
* @usage: showTeam(teams, 0);
* @param: pointer to an array of int (pass by pointer), int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void showTeam(int** teams, int team_no) {
	int* this_team;
	int num_of_members;

	this_team = teams[team_no];
	num_of_members = this_team[0];
	cout << "Team No.: " << team_no << "\n";
	cout << " | Number of members: " << num_of_members << "\n";
	for (int member = 1; member <= num_of_members; member++) {
		cout << " | ID: " << this_team[member] << "\n";
	}
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
* Displays Member's ID and team number. Debug purpose.
* @usage: showMember(101, 0);
* @param: int, int
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void showMember(int id_no, int team_no) {
	cout << "Team No.: " << team_no << " | ID: " << id_no << "\n";
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*									validInteger()							  +
* @param: none																  +
* @return integer															  +
* reads a verified integer from the keyboard								  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
int validInteger()
{
	int x;
	cin >> x;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(120, '\n');
		cout << "Invalid input. Try again: ";
		cin >> x;
	}
	return x;
}


/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*									printHeader()							  +
* @param: integer															  +
* @return none																  +
* prints header or goodbye message depending on parameter					  +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void printHeader(int x)
{
	if (x == 1)
	{
		string s = "Shady Boukary, Yujin Yoshimura\n";
		s += "TeamQueue HW5\n";
		s += "------------------------------\n\n";
		exportString(s);
	}
	else
	{
		string s = "\n\n**********THANK YOU**********\n\n";
		exportString(s);
	}
}
