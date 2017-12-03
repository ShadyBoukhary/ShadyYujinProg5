/**
* This program demonstrates team queue.
* @version 1.0 2017-12-02
* @course CMPS2143 Dr. Stringfellow
* @author Yujin Yoshimura, Shady Boukhary
*/

#include "TeamQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Opens an input file.
ifstream openInputFile(string file_name);

// Imports team data and queues from an input file into an array of string.
// The index of the array is the line number.
int importString(string lines[]);

// Opens an output file in truncate, then delete current content.
void initializeOutputFile();

// Opens an output file in append.
ofstream openOutputFile(string file_name);

// Displays string and exports string into output file.
void exportString(string s);

// Checks whether an input is about creating a team or about queueing.
bool isTeams(string line);

// Converts an input into number of teams.
int getNumOfTeams(string line);

// Displays Scenario number.
void printScenario(int& scenario_no);

// Creates an array of teams. The index of the array is the team number.
void createTeams(int** &teams, int num_of_teams);

// Add members into a team. The index of the array is the ID number.
void addMembers(int** teams, int team_no, string line);

// Check if the input is enqueue.
bool isEnqueue(string line);

// Parse enqueue command and gets ID number of the person enqueued.
int getEnqueueID(string line);

// Searches ID number in the array of teams and tell its team number.
int getTeamNo(int** teams, int num_of_teams, int id_no);

// Check if the input is dequeue.
bool isDequeue(string line);

// Check if the input is stop.
bool isStop(string line);

// Displays Scenario number.
void printBlankLine();

// Deletes an array of teams and all of its content.
void deleteTeams(int** &teams, int num_of_teams);

// Displays Team number and all members of the team. Debug purpose.
void printTeam(int** teams, int team_no);

// Displays Member's ID and team number. Debug purpose.
void printMember(int id_no, int team_no);

int main() {
	TeamQueue<int> q;
	string lines[255];
	int length = 0;
	int line_no = 0;
	int scenario_no = 1;
	int num_of_teams = 1;
	int team_no;
	int id_no;
	int** teams;
	bool stop;

	initializeOutputFile();
	length = importString(lines);
	while (line_no < length && num_of_teams > 0) {
		if (isTeams(lines[line_no])) {
			num_of_teams = getNumOfTeams(lines[line_no]);

			// if num_of_teams is 0, skip all the process and end the loop
			if (num_of_teams) {
				printScenario(scenario_no);
				createTeams(teams, num_of_teams);
				line_no++;

				// store team information
				for (team_no = 0; team_no < num_of_teams; team_no++) {
					addMembers(teams, team_no, lines[line_no]);
					line_no++;
				}

				// process commands
				stop = false;
				while (!stop) {
					if (isEnqueue(lines[line_no])) {
						id_no = getEnqueueID(lines[line_no]);
						team_no = getTeamNo(teams, num_of_teams, id_no);
						q.enqueue(id_no, team_no);
					}
					else if (isDequeue(lines[line_no])) {
						q.dequeue();
					}
					else if (isStop(lines[line_no])) {
						printBlankLine();
						deleteTeams(teams, num_of_teams);
						stop = true;
					}
					line_no++;
				}
			}
		}
	}

	system("pause");
	return 0;
}

// Opens an input file.
// @param: string
// @return: ifstream
ifstream openInputFile(string file_name) {
	ifstream myfile(file_name);
	return myfile;
}

// Imports team data and queues from an input file into an array of string.
// The index of the array is the line number.
// @param: array of string (pass by pointer)
// @return: int
int importString(string lines[]) {
	string file_name = "prog5data.txt";
	string line;
	int length = 0;

	ifstream myfile = openInputFile(file_name);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			lines[length] = line;
			length++;
		}
		myfile.close();
	}
	else { cout << "Unable to open file." << endl; }

	return length;
}

// Opens an output file in truncate, then delete current content.
// @param: string
void initializeOutputFile() {
	string file_name = "prog5output.txt";
	ofstream myfile(file_name, ios_base::trunc);
	if (myfile.is_open()) { myfile.close(); }
	else { cout << "Unable to open file." << endl; }
}

// Opens an output file in append.
// @param: string
// @return: ofstream
ofstream openOutputFile(string file_name) {
	ofstream myfile(file_name, ios_base::app);
	return myfile;
}

// Displays string and exports string into output file.
// @param: string
void exportString(string s) {
	string file_name = "prog5output.txt";
	ofstream myfile = openOutputFile(file_name);

	if (myfile.is_open()) {
		cout << s;
		myfile << s;
		myfile.close();
	}
	else { cout << "Unable to open file." << endl; }
}

// Checks whether an input is about creating a team or about queueing.
// @param: string
// @return: bool
bool isTeams(string line) { return isdigit(line[0]); }

// Converts an input into number of teams.
// @param: string
// @return: int
int getNumOfTeams(string line) { 
	int num_of_teams;
	(isTeams(line)) ? num_of_teams = stoi(line) : num_of_teams = -1;
	return num_of_teams;
}

// Displays Scenario number.
// @param: int (pass by reference)
void printScenario(int& scenario_no) {
	exportString("Scenario #" + to_string(scenario_no) + "\n");
	scenario_no++;
}

// Creates an array of teams. The index of the array is the team number.
// @param: pointer to an array of int (pass by reference), int 
void createTeams(int** &teams, int num_of_teams) {
	teams = new int*[num_of_teams];
}

// Add members into a team.
// @param: pointer to an array of int (pass by pointer), int, string
void addMembers(int** teams, int team_no, string line) {
	stringstream stream(line);
	int num_of_members, id_no;
	int* this_team;

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

// Check if the input is enqueue.
// @param: string
// @return: bool
bool isEnqueue(string line) {
	stringstream stream(line);
	string command;
	bool enqueue = false;

	stream >> command;
	if (command == "ENQUEUE")
		enqueue = true;
	return enqueue;
}

// Parse enqueue command and gets ID number of the person enqueued.
// @param: string
// @return: int
int getEnqueueID(string line) {
	stringstream stream(line);
	string command;
	int id_no = -1;

	stream >> command >> id_no;
	return id_no;
}

// Searches ID number in the array of teams and tell its team number.
// @param: pointer to an array of int (pass by pointer), int, int
// @return: int
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

// Check if the input is dequeue.
// @param: string
// @return: bool
bool isDequeue(string line) {
	stringstream stream(line);
	string command;
	bool dequeue = false;

	stream >> command;
	if (command == "DEQUEUE")
		dequeue = true;
	return dequeue;
}

// Check if the input is stop.
// @param: string
// @return: bool
bool isStop(string line) {
	stringstream stream(line);
	string command;
	bool stop = false;

	stream >> command;
	if (command == "STOP")
		stop = true;
	return stop;
}

// Displays Scenario number.
// @param: int (pass by reference)
void printBlankLine() {
	exportString("\n");
}

// Deletes an array of teams and all of its content.
void deleteTeams(int** &teams, int num_of_teams) {
	for (int team_no = 0; team_no < num_of_teams; team_no++) {
		delete[] teams[team_no];
		teams[team_no] = nullptr;
	}
	delete[] teams;
	teams = nullptr;
}

// Displays Team number and all members of the team. Debug purpose.
// @param: pointer to an array of int (pass by pointer), int
void printTeam(int** teams, int team_no) {
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

// Displays Member's ID and team number. Debug purpose.
// @param: int, int
void printMember(int id_no, int team_no) {
	cout << "Team No.: " << team_no << "\n";
	cout << " | ID: " << id_no << "\n";
}