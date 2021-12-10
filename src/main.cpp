/*
 * @file: main.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: implementation of AR model for IMS project
 * @description: #TODO
 */

#include <stdio.h>

#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @name: calculate_prediction
 * @param vect: vector with values of time series (sales of electromobiles in
 * our case)
 * @param minInfluence: minimal level of influence that autocorrelation must
 * have to be used in the prediction
 * @brief: predict how many electromobiles will be sold in the next month
 * @description: this function uses AR model - autoregression - to predict the
 * next value of time series recieved in param vect. The influence of previous
 * months on the next month is predicted using autocorrelation. Autocorrelation
 * returns a value in interval <-1;1>, the bigger the value, the bigger the
 * impact. #TODO finish this
 * @retval: predicted value
 */
double calculate_prediction(deque<double> vect, double minInfulence);

/**
 * @name: experiment_1
 * @param vect: vector with values of time series (sales of electromobiles in
 * our case)
 * @brief: try to predict last 20 months of electric cars sales, based on sales
 * made previous to last 20 months
 * @description: in experiment one, we will determine what is the best level of
 * influence of autocorrelation that still should be valid. For example, if
 * there is a value 0.8 as a result of autocorrelation offsetet by 1 that means,
 * that a previous moth was has a significant influence on predicted value, if
 * its 0.2 that influence is much lower. This will be done by predicting last 20
 * months of sales and the shifting the minimal level of influence until best
 * result are achieved.
 */
void experiment_1(deque<double> vect);

int main(int argc, char **argv) {
  deque<double> vect;

  ifstream fin;
  fin.open("./src/input_data.txt", ifstream::in);

  // int count = 1;

  while (true) {
    double x;
    fin >> x;

    if (fin.eof()) break;

    vect.push_front(x);
  }

  experiment_1(vect);

  return 0;
}

void experiment_1(deque<double> vect) {
  unsigned int count = vect.size() - 20;
  double minInfluence = 0.01;
  // int predictNum = 0;
  double prediction = 0;

  deque<double> smallerVect = vect;

  for (int i = 0; i <= 19; i++) {
    smallerVect.pop_front();
  }

  // smallerVect.erase(smallerVect.begin(), smallerVect.begin() + 9);

  for (unsigned long int i = 0; i <= smallerVect.size(); i++) {
    cout << smallerVect[i] << ", ";
  }

  cout << '\n';

  // while (predictNum <= 20) {
  while (minInfluence <= 1) {
    prediction = calculate_prediction(smallerVect, minInfluence);
    cout << "Prediction for level of influnce " << minInfluence
         << " is: " << prediction << "\n";
    minInfluence += 0.01;
    cout << "---------------------------------------------\n\n";
  }
  count++;
  //}

  return;
}

double calculate_prediction(deque<double> vect, double minInfluence) {
  long double mean = 0;

  for (unsigned int i = 0; i != vect.size(); i++) {
    mean += vect[i];
  }

  mean = mean / vect.size();

  cout << "mean is: " << mean << '\n';

  deque<double> temp;

  for (unsigned int i = 0; i != vect.size(); i++) {
    temp.push_back(vect[i] - mean);
  }

  double sqr_dev = 0;
  for (unsigned int i = 0; i != vect.size(); i++) {
    sqr_dev += temp[i] * temp[i];
  }

  cout << "sum of square deviations is: " << sqr_dev << '\n';

  deque<double> autoCorr;
  // should there really be 1 here? not 0?
  for (unsigned int i = 1; i != vect.size(); i++) {
    double result = 0;
    int count = 0;
    for (unsigned int j = i; j != temp.size(); j++) {
      result += temp[count] * temp[j];
      count++;
    }
    autoCorr.push_back(result);
  }

  double goodCorSum = 0;
  deque<int> index;

  for (unsigned int i = 0; i != vect.size(); i++) {
    autoCorr[i] = autoCorr[i] / sqr_dev;
    if (abs(autoCorr[i]) > minInfluence) {
      goodCorSum += autoCorr[i];
      index.push_back(i);
      //cout << "autocorrelation for lag " << i << " is: " << autoCorr[i] << '\n';
    }
  }

  double prediction = 0;

  
  if(index.empty()) return prediction;

  for (unsigned int i = 0; i <= index.size(); i++) {
   /* cout << "value at index " << i << " is: " << vect[index[i]] << '\n';
    cout << "value of autocor at index " << i << " is: " << autoCorr[index[i]]
         << '\n';
    cout << "goodsum cor is: " << goodCorSum << '\n';*/
    prediction += vect[index[i]] * ((autoCorr[index[i]]) / goodCorSum);
    cout << "prediction is: " << prediction << '\n';
  }

  return prediction;
}
