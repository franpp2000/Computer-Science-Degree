% Definición de variables
int: euros_cantidad;
int: centimos_cantidad;

var 0..1000: moneda_200;
var 0..1000: moneda_100;
var 0..1000: moneda_50;
var 0..1000: moneda_20;
var 0..1000: moneda_10;
var 0..1000: moneda_5;
var 0..1000: moneda_2;
var 0..1000: moneda_1;

% Definición de restricciones:
constraint 100*moneda_100 + 200*moneda_200 == euros_cantidad*100;

constraint 50*moneda_50 + 20*moneda_20 + 10*moneda_10 + 5*moneda_5 + 2*moneda_2 + 1*moneda_1 == centimos_cantidad;

% Indica que es un CSP (podría ser COP)
solve satisfy;
