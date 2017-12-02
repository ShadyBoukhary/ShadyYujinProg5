#include "TeamQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Opens an input file.
ifstream openFile(string filename);

// Imports team data and queues from an input file into an array of string.
// The index of the array is the line number.
int import(string lines[]);

// Checks whether an input is about creating a team or about queueing.
bool isTeams(string line);

// Converts an input into number of teams.
int getNumOfTeams(string line);

// Displays Scenario number.
void printScenario(int& scenario_no);

// Creates an array of teams. The index of the array is the team number.
void createTeams(int** teams, int num_of_teams);

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

// Deletes an array of teams and all of its content.
void deleteTeams(int** teams, int num_of_teams);

int main() {
	string lines[65535];
	int length = 0;
	int line_no = 0;
	int scenario_no = 1;
	int num_of_teams = 1;
	int team_no;
	int id_no;
	int** teams;
	bool stop;
	
	length = import(lines);
	while (line_no < length && num_of_teams > 0){
		if (isTeams(lines[line_no])) {
			num_of_teams = getNumTeams(lines[line_no]);
			
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
						// ENQUEUE
						// Search Team Number in Team Queue
						// If found, then insert a node
						// If not found, then add a node at the tail
						// Node includes both team_no and id_no
					}
					else if (isDequeue(lines[line_no])) {
						// DEQUEUE
						// just like ordinary Queue
					}
					else if (isStop(lines[line_no])) {
						deleteTeams(teams, num_of_teams);
						stop = true;
					}
					line_no++;
				}
			}
		}
		line_no++;
	}
	
	system("pause");	
	return 0;
}

// Opens an input file.
// @param: none
// @return: ifstream
ifstream openFile(string filename) {
	string file_name = filename;
	ifstream myfile(file_name);
	return myfile;
}

// Imports team data and queues from an input file into an array of string.
// The index of the array is the line number.
// @param: array of string (pass by pointer)
// @return: int
int import(string lines[]) {
	int length = 0;
	string line;

	ifstream myfile = openFile("prog5data.txt");
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

// Checks whether an input is about creating a team or about queueing.
// @param: string
// @return: bool
bool isTeams(string line) { return isdigit(line[0]); }

// Converts an input into number of teams.
// @param: string
// @return: int
int getNumTeams(string line) { return stoi(line); }

// Displays Scenario number.
// @param: int (pass by reference)
void printScenario(int& scenario_no) {
	cout << "Scenario #" + to_string(scenario_no) + \n;
	scenario_no++;
}

// Creates an array of teams. The index of the array is the team number.
// @param: pointer to an array of int (pass by pointer), int 
void createTeams(int** teams, int num_of_teams) {
	teams = new int* [num_of_teams];
}

// Add members into a team.
// @param: pointer to an array of int (pass by pointer), int, string
void addMembers(int** teams, int team_no, string line) {
	stringstream stream(line);
	int num_of_members, id_no;
	int* this_team;
	
	stream >> num_of_members;
	teams[team_no] = new int [num_of_members + 1];
	this_team = teams[team_no];
	
	// Since dynamic array cannot tell its length, I store the
	// Number of members of that team in the index 0 of that array.
	this_team[0] = num_of_members;
	for (int member = 1; member < num_of_members + 1; member++) {
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
			if (id_no == this_team[member]){
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

// Deletes an array of teams and all of its content.
void deleteTeams(int** teams, int num_of_teams) {
	for (int team_no = 0; team_no < num_of_teams; team_no++) {
		delete[] teams[team_no];
		teams[team_no] = nullptr;
	}
	delete[][] teams;
	teams = nullptr;
}
