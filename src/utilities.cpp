/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}
vector<process_stats> stats;
int rows=0;
int loadData(const char *filename, bool ignoreFirstRow) {
	stats.clear();
	ifstream MyFile;
	MyFile.open(filename, ios::in);
	if (MyFile.is_open()) {
		string line;
		while (!MyFile.eof()) {
			getline(MyFile, line);
			stringstream ss(line);
			string tempToken;
			vector<string> tempVect;
			while (getline(ss, tempToken, ',')) {
				tempVect.push_back(tempToken);
			}
			if (tempVect.size() == 4) {
				process_stats tempStat;
				tempStat.process_number = stoi(tempVect[0]);
				tempStat.start_time = stoi(tempVect[1]);
				tempStat.cpu_time = stoi(tempVect[2]);
				tempStat.io_time = stoi(tempVect[3]);
				stats.push_back(tempStat);
			}
		}
		rows = stats.size();
		MyFile.close();
	} else {
		return COULD_NOT_OPEN_FILE;
	}

	return SUCCESS;
}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder){
	case 1:
		for(int i=stats.size()-1;i>=0;i--){
			int max=stats[0].process_number;
			int index=0;
			for(int j=0;j<=i;j++){
				if(stats[j].process_number>max){
					max=stats[j].process_number;
					index=j;
				}
			}
			process_stats temp = stats[i];
			stats[i]=stats[index];
			stats[index]=temp;
		}
		break;
	case 2:
		for(int i=stats.size()-1;i>=0;i--){
			int max=stats[0].start_time;
			int index=0;
			for(int j=0;j<=i;j++){
				if(stats[j].start_time>max){
					max=stats[j].start_time;
					index=j;
				}
			}
			process_stats temp = stats[i];
			stats[i]=stats[index];
			stats[index]=temp;
		}
		break;
	case 3:
		for(int i=stats.size()-1;i>=0;i--){
			int max=stats[0].cpu_time;
			int index=0;
			for(int j=0;j<=i;j++){
				if(stats[j].cpu_time>max){
					max=stats[j].cpu_time;
					index=j;
				}
			}
			process_stats temp = stats[i];
			stats[i]=stats[index];
			stats[index]=temp;
		}
		break;
	case 4:
		for(int i=stats.size()-1;i>=0;i--){
			int max=stats[0].io_time;
			int index=0;
			for(int j=0;j<=i;j++){
				if(stats[j].io_time>max){
					max=stats[j].io_time;
					index=j;
				}
			}
			process_stats temp = stats[i];
			stats[i]=stats[index];
			stats[index]=temp;
		}
		break;
	default:
		break;

	}


}

process_stats getNext() {
	process_stats myFirst;
	myFirst = stats[0];
	stats.erase(stats.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows() {
	return rows;
}

