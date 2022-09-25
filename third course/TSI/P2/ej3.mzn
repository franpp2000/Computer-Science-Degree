set of int: n_casas = 1..5;
set of int: propiedades = 1..5;
array [propiedades, n_casas] of var 1..5: matriz;

%% restricciones

% El vasco vive en la casa roja.
constraint forall(j in 1..5)(if matriz[2, j] == 2 
                             then matriz[1, j] == 4 endif);
                             
% El catalán tiene un perro.
constraint forall(j in 1..5)(if matriz[2, j] == 5 
                             then matriz[3, j] == 1 endif);
                             
% El gallego es un pintor.
constraint forall(j in 1..5)(if matriz[2, j] == 4 
                             then matriz[5, j] == 1 endif);
                           
% El navarro bebe te.
constraint forall(j in 1..5)(if matriz[2, j] == 3
                             then matriz[4, j] == 1 endif);
                             
% El andaluz vive en la primera casa de la izquierda.
constraint matriz[2, 1] == 1;

% El de la casa verde bebe café.
constraint forall(j in 1..5)(if matriz[1, j] == 5
                             then matriz[4, j] == 2 endif);
                             
% La casa verde está al lado de la blanca y a su derecha.
constraint forall(j in 1..5)(if matriz[1, j] == 5
                             then matriz[1, j - 1] == 2 endif);
                             
% El escultor cría caracoles.
constraint forall(j in 1..5)(if matriz[5, j] == 2
                             then matriz[3, j] == 2 endif);
                             
% El diplomático vive en la casa amarilla.
constraint forall(j in 1..5)(if matriz[5, j] == 3
                             then matriz[1, j] == 3 endif);

% En la casa central se bebe leche.
constraint matriz[4, 3] == 3;

% La casa del andaluz está al lado de la azul.
constraint forall(j in 2..4)(if matriz[1, j] == 1
                             then matriz[2, j + 1] == 1 \/
                                   matriz[2, j - 1] == 1 endif);

constraint if matriz[1, 1] == 1 then matriz[2, 2] == 1 endif;
constraint if matriz[1, 5] == 1 then matriz[2, 4] == 1 endif;

% El violinista bebe zumo.
constraint forall(j in 1..5)(if matriz[5, j] == 4
                             then matriz[4, j] == 4 endif);
                             
% El zorro está en una casa al lado de la del médico.
constraint forall(j in 2..4)(if matriz[5, j] == 5
                             then matriz[3, j + 1] == 5 \/
                                   matriz[3, j - 1] == 5 endif);

constraint if matriz[5, 1] == 5 then matriz[3, 2] == 5 endif;
constraint if matriz[5, 5] == 5 then matriz[3, 4] == 5 endif;

% El caballo está en una casa al lado de la del diplomático.
constraint forall(j in 2..4)(if matriz[5, j] == 3
                             then matriz[3, j + 1] == 4 \/
                                  matriz[3, j - 1] == 4 endif);

constraint if matriz[5, 1] == 3 then matriz[3, 2] == 4 endif;
constraint if matriz[5, 5] == 3 then matriz[3, 4] == 4 endif;

% Restricción para que en cada fila todos los elementos sean distintos.
constraint forall(i in 1..5)(count(matriz[i, n_casas], 1) == 1);
constraint forall(i in 1..5)(count(matriz[i, n_casas], 2) == 1);
constraint forall(i in 1..5)(count(matriz[i, n_casas], 3) == 1);
constraint forall(i in 1..5)(count(matriz[i, n_casas], 4) == 1);
constraint forall(i in 1..5)(count(matriz[i, n_casas], 5) == 1);

%%
solve satisfy;
