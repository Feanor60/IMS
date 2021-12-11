/*
 * @file: main.cpp
 * @author: Vojtěch Bůbela
 * @login: xbubel08
 * @brief: implementation of AR model for IMS project
 * @description: #TODO
 */

#include <math.h>
#include <stdio.h>

#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>

#define MIN_INFL 0.225

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
 * @brief: try to predict last 12 months of electric cars sales, based on sales
 * made previous to last 12 months
 * @description: in experiment one, we will determine what is the best level of
 * influence of autocorrelation that still should be valid. For example, if
 * there is a value 0.8 as a result of autocorrelation offsetet by 1 that means,
 * that a previous month had a significant influence on predicted value, if
 * its 0.2 that influence is much lower. This will be done by predicting last 20
 * months of sales and the shifting the mini  mal level of influence until best
 * result are achieved.
 */
void experiment_1(deque<double> vect);

/**
 * @name: experiment_2
 * @param vect: vector with values of time series (sales of electromobiles in
 * our case)
 * @brief: predict electric car sales for every year until 2030
 * @description: using the level of influence determined in experiment 1
 *               we will predict next 9 years, month by month
 */
void experiment_2(deque<double> vect);

void experiment_3(deque<double> vect);

int main(int argc, char **argv) {
  deque<double> vect;

  ifstream fin;
  fin.open("./src/input_data.txt", ifstream::in);

  while (true) {
    double x;
    fin >> x;

    if (fin.eof()) break;

    vect.push_front(x);
  }

  experiment_1(vect);
  experiment_2(vect);
  experiment_3(vect);

  return 0;
}

void experiment_1(deque<double> vect) {
  double minInfluence = MIN_INFL;
  double prediction = 0;
  int year_pred = 0;

  deque<string> months = {"Listopad", "Říjen",  "Září",   "Srpen",
                          "Červenec", "Červen", "Květen", "Duben",
                          "Březen",   "Únor",   "Leden",  "Prosinec"};
  deque<double> smallerVect = vect;

  cout << "################ EXPERIMENT 1 ################ \n";

  for (int i = 0; i <= 11; i++) {
    smallerVect.pop_front();
  }

  while (smallerVect.size() != (vect.size())) {
    prediction = calculate_prediction(smallerVect, minInfluence);

    prediction = floor(prediction);

    cout << "Predikce: " << prediction
         << "    reálně: " << vect[vect.size() - smallerVect.size() - 1] << "  "
         << months[vect.size() - smallerVect.size() - 1] << "\n";

    year_pred += prediction;
    smallerVect.push_front(prediction);
  }

  cout << "----------------------------------------------\n";

  cout << "Součet:   " << year_pred << "    "
       << "       3256\n";
  cout << "##############################################\n\n";

  return;
}

void experiment_2(deque<double> vect) {
  deque<double> future_predict;
  double min_infl = MIN_INFL;
  future_predict = vect;
  double next_pred = 0;
  double year_pred = 0;
  int year_count = 2021;
  double summ = 0;

  // add December of 2021
  next_pred = calculate_prediction(future_predict, min_infl);
  next_pred = floor(next_pred);
  future_predict.push_front(next_pred);

  for (unsigned int i = 0; i <= 11; i++) {
    year_pred += future_predict[i];
  }

  cout << "################ EXPERIMENT 2 ################\n";

  for (unsigned int i = 0; i < 108; i++) {
    if(i % 12 == 0) {
      cout << year_count << "   " << year_pred << "\n";
      summ += year_pred;
      year_pred = 0;
      year_count++;
    }

    next_pred = calculate_prediction(future_predict, min_infl);
    next_pred = floor(next_pred);
    future_predict.push_front(next_pred);

    year_pred += next_pred;
  }

  cout << year_count << "   " << year_pred << "\n";

  summ += year_pred;
  summ += 5200;
  cout << "Celkem elektro aut: " <<  summ << "\n";
  cout << "##############################################\n\n";

  return;
}

void experiment_3(deque<double> vect) {
  deque<double> future_predict;
  double min_infl = MIN_INFL;
  future_predict = vect;
  double next_pred = 0;
  double year_pred = 0;
  int year_count = 2021;
  double summ = 0;

  // add December of 2021
  next_pred = calculate_prediction(future_predict, min_infl);
  next_pred = floor(next_pred);
  future_predict.push_front(next_pred);

  for (unsigned int i = 0; i <= 11; i++) {
    year_pred += future_predict[i];
  }

  cout << "################ EXPERIMENT 3 ################\n";

  for (unsigned int i = 0; i < 108; i++) {
    if(i % 12 == 0) {
      cout << year_count << "   " << year_pred << "\n";
      summ += year_pred;
      year_pred = 0;
      year_count++;
    }

    next_pred = calculate_prediction(future_predict, min_infl);
    if(i <= 11) {
      next_pred = next_pred *1.2;
    }

    next_pred = floor(next_pred);
    future_predict.push_front(next_pred);

    year_pred += next_pred;
  }

  cout << year_count << "   " << year_pred << "\n";

  summ += year_pred;
  summ += 5200;
  cout << "Celkem elektro aut: " <<  summ << "\n";
  cout << "##############################################\n\n";

  return;

}

double calculate_prediction(deque<double> vect, double minInfluence) {
  long double mean = 0;

  for (unsigned int i = 0; i != vect.size(); i++) {
    mean += vect[i];
  }

  mean = mean / vect.size();

  // cout << "mean is: " << mean << '\n';

  deque<double> temp;

  for (unsigned int i = 0; i != vect.size(); i++) {
    temp.push_back(vect[i] - mean);
  }

  double sqr_dev = 0;
  for (unsigned int i = 0; i != vect.size(); i++) {
    sqr_dev += temp[i] * temp[i];
  }

  // cout << "sum of square deviations is: " << sqr_dev << '\n';

  deque<double> autoCorr;
  for (unsigned int i = 0; i != vect.size(); i++) {
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
      // cout << "autocorrelation for lag " << i << " is: " << autoCorr[i] <<
      // '\n';
    }
  }

  double prediction = 0;

  if (index.empty()) return prediction;

  for (unsigned int i = 0; i < index.size(); i++) {
    /* cout << "value at index " << i << " is: " << vect[index[i]] << '\n';
     cout << "value of autocor at index " << i << " is: " << autoCorr[index[i]]
          << '\n';
     cout << "goodsum cor is: " << goodCorSum << '\n';*/
    //if (index[i] == 0) {
      prediction += vect[index[i]] * (((autoCorr[index[i]]) / goodCorSum));
    //} else {
     // prediction += vect[index[i]] *
       //             (((autoCorr[index[i]]) / goodCorSum) * (1.0 / (index[i])));
    //}
    // cout << "prediction is: " << prediction << '\n';
  }

  return prediction;
}
