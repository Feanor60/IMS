/*
 * @file: main.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: implementation of AR model for IMS project
 * @description: #TODO
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

	vector<vector<int>> vect {
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0}
	};

	ifstream fin;
	fin.open("./src/input_data.txt", ifstream::in);
	
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 12; j++) {
			int x;
			fin >> x;
			if( fin.eof()) break;
			vect[i][j] = x;
		}
	}

	cout << vect[5][5];

	return 0;
}
