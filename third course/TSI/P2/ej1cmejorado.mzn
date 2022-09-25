% Definición de variables
int: euros_cantidad; %euros del importe
int: centimos_cantidad; %céntimos del importe

var 0..1000: moneda_200; % moneda de 2 euros -> 200 céntimos
var 0..1000: moneda_100; % moneda de 1 euro -> 100 céntimos
var 0..1000: moneda_50;
var 0..1000: moneda_20;
var 0..1000: moneda_10;
var 0..1000: moneda_5;
var 0..1000: moneda_2;
var 0..1000: moneda_1;

% Definición de restricciones:
% Parte euros
constraint 100*moneda_100 + 200*moneda_200 == euros_cantidad*100;
% Parte céntimos
constraint 50*moneda_50 + 20*moneda_20 + 10*moneda_10 + 5*moneda_5 + 2*moneda_2 + 1*moneda_1 == centimos_cantidad;

% Indica que es un CSP (podría ser COP)
solve minimize moneda_200 + moneda_100 + moneda_50 + moneda_20 + moneda_10 + moneda_5 + moneda_2 + moneda_1;
