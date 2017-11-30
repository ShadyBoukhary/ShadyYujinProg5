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
int getNumTeams(string line);

// Displays Scenario number.
void printScenario(int& scenario);

// Creates an array of teams. The index of the array is the team number.
void createTeams(int** teams, int num_teams);

// Add members into a team.
void addMembers(int** teams, int team_no, string line);

int main() {
	string lines[65535];
	int length = 0;
	int index = 0;
	int scenario = 1;
	int num_teams = 1;
	int** teams;
	
	length = import(lines);
	while (index < length && num_teams > 0){
		if (isTeams(lines[index])) {
			num_teams = getNumTeams(lines[index]);
			
			// if num_teams is 0, skip all the process and end the loop
			if (num_teams) {
				printScenario(scenario);
				createTeams(teams, num_teams);
				index++;
				for (int team_no = 0; i < num_teams; i++) {
				}
			}
		}
		index++;
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
void printScenario(int& scenario) {
	cout << "Scenario #" + to_string(scenario) + \n;
	scenario++;
}

// Creates an array of teams. The index of the array is the team number.
// @param  pointer to an array of int (pass by pointer), int 
void createTeams(int** teams, int num_teams) { teams = new int* [num_teams]; }

// Add members into a team.
// @param  pointer to an array of int (pass by pointer), int, string
void addMembers(int** teams, int team_no, string line) {
	stringstream stream(line);
	int num_members;
	int* this_team;
	
	stream >> num_members;
	teams[team_no] = new int [num_members];
	this_team = teams[team_no];
	for (int i = 0; i < num_members; i++) {
		stream >> this_team[i];
	}
}