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
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {

	vector<double> vect;

	ifstream fin;
	fin.open("./src/input_data.txt", ifstream::in);

	int count = 1;

	while(!fin.eof()) {
		double x;
		fin >> x;
		cout << "number " << count++ << " is: " << x << '\n';
		vect.push_back(x);
	}

	long double mean = 0;

	for(unsigned int i = 0; i != vect.size(); i++) {
		mean += vect[i];
	}

	mean = mean / vect.size();

	cout << "mean is: " << mean << '\n';

	vector<double> temp;

	for(unsigned int i = 0; i != vect.size(); i++) {
		temp.push_back(vect[i] - mean);
	}

	double sqr_dev = 0;
	for(unsigned int i = 0; i != vect.size(); i++) {
		sqr_dev += temp[i] * temp[i];
	}

	cout << "sum of square deviations is: " << sqr_dev << '\n';

	
	vector<double> autoCorr;
	// should there really be 1 here? not 0?
	for(unsigned int i = 1; i != vect.size(); i++) {
		double result = 0;
		int count = 0;
		for(unsigned int j = i; j != temp.size(); j++) {
			result += temp[count]*temp[j];
			count++;
		}
			autoCorr.push_back(result);
	}

	double goodCorSum = 0;
	vector<int> index;

	for(unsigned int i = 0; i != vect.size(); i++) {
		autoCorr[i] = autoCorr[i]/sqr_dev;
		if(abs(autoCorr[i]) > 0.2) {	// 0.2 is a value we've decided, perhaps experiment w/ it a bit
			goodCorSum += autoCorr[i];
			index.push_back(i);
			cout << "autocorrelation for lag " << i << " is: " << autoCorr[i] << '\n';
		}
	}

	double prediction = 0;

	for(unsigned int i = 0; i != index.size(); i++) {
		prediction += vect[index[i]] * ((autoCorr[index[i]] * 100) / goodCorSum);
		cout << "prediction is: " << prediction << '\n';
	}

	return 0;
}
