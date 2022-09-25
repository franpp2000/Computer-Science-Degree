% Definición de variables
set of int: horas_diarias = 1..6;
set of int: dias_semanales = 1..5;
array [dias_semanales, horas_diarias] of var 0..9: horario;


% Definición de restricciones:


% Máximo de horas a la semana de cada asignatura
constraint count(horario, 1) == 4;
constraint count(horario, 2) == 2;
constraint count(horario, 3) == 4;
constraint count(horario, 4) == 4;
constraint count(horario, 5) == 4;
constraint count(horario, 6) == 2;
constraint count(horario, 7) == 2;
constraint count(horario, 8) == 2;
constraint count(horario, 9) == 1;
% En cada día de la semana solo se puede impartir, como máximo, un bloque % % de cada asignatura.
constraint forall(i in 1..5)(count(horario[i, horas_diarias], 1) == 2 \/ count(horario[i, horas_diarias], 1) == 0);
constraint forall(i in 1..5)(count(horario[i, horas_diarias], 3) == 2 \/ count(horario[i, horas_diarias], 3) == 0);
constraint forall(i in 1..5)(count(horario[i, horas_diarias], 4) == 2 \/ count(horario[i, horas_diarias], 4) == 0);
constraint forall(i in 1..5)(count(horario[i, horas_diarias], 5) == 2 \/ count(horario[i, horas_diarias], 5) == 0);
constraint forall(i in 1..5)(count(horario[i, horas_diarias], 8) == 2 \/ count(horario[i, horas_diarias], 8) == 0);

constraint forall(i in 1..5)(count(horario[i, horas_diarias], 2) == 1 \/ count(horario[i, horas_diarias], 2) == 0);
constraint forall(i in 1..5)(count(horario[i, horas_diarias], 6) == 1 \/ count(horario[i, horas_diarias], 6) == 0);
constraint forall(i in 1..5)(count(horario[i, horas_diarias], 7) == 1 \/ count(horario[i, horas_diarias], 7) == 0);
constraint forall(i in 1..5)(count(horario[i, horas_diarias], 9) == 1 \/ count(horario[i, horas_diarias], 9) == 0);


% Cada profesor solo puede impartir un bloque de alguna de sus asignaturas cada día, 
% excepto Prof4 (que puede impartir más de una).
constraint forall(j in 1..6, j2 in 1..6, i in 1..5) (if j != j2 /\ horario[i, j] == 1 
                                                     then horario[i, j2] != 3 endif);
                 
constraint forall(j in 1..6, j2 in 1..6, i in 1..5)(if j != j2 /\ horario[i, j] == 4
                                                    then horario[i, j2] != 5 endif);
                 
constraint forall(j in 1..6, j2 in 1..6, i in 1..5)(if j != j2 /\ horario[i, j] == 6 
                                                    then horario[i, j2] != 9 endif);

% Recreo a 0
constraint forall(i in 1..5, j in 1..3)(horario[i, j] != 0);
constraint forall(i in 1..5, j in 5..6)(horario[i, j] != 0);
constraint forall(i in 1..5)(horario[i, 4] == 0);

% Restriccion horas de profesores
constraint forall(i in 1..5, j in 1..4)(horario[i, j] != 1);
constraint forall(i in 1..5, j in 1..4)(horario[i, j] != 3);

constraint forall(i in 1..5, j in 3..6)(horario[i, j] != 4);
constraint forall(i in 1..5, j in 3..6)(horario[i, j] != 5);

constraint forall(i in 1..5, j in 1..2)(horario[i, j] != 6);
constraint forall(i in 1..5, j in 5..6)(horario[i, j] != 6);

constraint forall(i in 1..5, j in 1..2)(horario[i, j] != 9);
constraint forall(i in 1..5, j in 5..6)(horario[i, j] != 9);

% Restriccion dias de asignaturas
constraint forall(i in 3..5, j in 1..6)(horario[i, j] != 1);
constraint forall(i in 3..5, j in 1..6)(horario[i, j] != 4);

constraint forall(j in 1..6)(horario[1, j] != 3);
constraint forall(j in 1..6)(horario[2, j] != 3);
constraint forall(j in 1..6)(horario[5, j] != 3);

constraint forall(i in 1..3, j in 1..6)(horario[i, j] != 5);

constraint forall(j in 1..6)(horario[1, j] != 6);
constraint forall(j in 1..6)(horario[2, j] != 6);
constraint forall(j in 1..6)(horario[4, j] != 6);

constraint forall(j in 1..6)(horario[1, j] != 7);
constraint forall(j in 1..6)(horario[3, j] != 7);
constraint forall(j in 1..6)(horario[4, j] != 7);

constraint forall(i in 1..2, j in 1..6)(horario[i, j] != 8);
constraint forall(i in 4..5, j in 1..6)(horario[i, j] != 8);

constraint forall(i in 2..5, j in 1..6)(horario[i, j] != 9);

% Indica que es un CSP (podría ser COP)
solve satisfy