# Project for Models and simulations class on BUT FIT Brno
This piece of code implements auto regressive model (AR for short).
The AR was edited to better suit our needs, that means we are using autocorrelation
instead of partial autocorrelation, we are ommiting error and we do not use beta0.

## Specification of our project
We had to make a model or simulation about Europes Union green deal so we decided to make
model for calculation how many electric cars there will be in 2030. We took data about
electric cars sold prior to November 2021 from czech website SDA. The result of our calculation
was compared with extimation of Czech goverment, published in Národní plán which addressed
demands of EU on reduction of polution.

## How to run project
You can clone our repo and then use `make run` in the root directory. The data of cars sold
is stored in `./src/input_data.txt` so new value (for example for December 2021) can be
added atthe end of this file. Our program contains some hardcoded values. They are described
at the start of `./src/main.cpp`. Program outputs result of 3 experiments. For further
information there is `dokumentace.pdf` which contains simulation protocol for this project.
It is written in czech.

## Evaluation
Our project scored 20/20 points
