
%%%%

%%%%%
constraint forall(j in 1..6, j2 in 1..6, i in 1..5)
                 (j != j2 /\
                 horario[i, j] == 1 /\
                 horario[i, j2] != 3);
                 
constraint forall(j in 1..6, j2 in 1..6, i in 1..5)(j != j2 /\ 
                                                    horario[i, j] == 4 /\ 
                                                    horario[i, j2] != 5);
                 
constraint forall(j in 1..6, j2 in 1..6, i in 1..5)(j != j2 /\
                                                    horario[i, j] == 6 /\ 
                                                    horario[i, j2] != 9);
                 
%%%%             
constraint forall(i in 1..5)(horario[i, 4] == 0);

%%%%
constraint forall(i in 1..5, j in 1..4)(horario[i, j] != 1);
constraint forall(i in 1..5, j in 1..4)(horario[i, j] != 3);

constraint forall(i in 1..5, j in 3..6)(horario[i, j] != 4);
constraint forall(i in 1..5, j in 3..6)(horario[i, j] != 5);

constraint forall(i in 1..5)(horario[i, 3] != 6);
constraint forall(i in 1..5)(horario[i, 3] != 9);

%%%%
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

constraint forall(j in 1..6)(horario[1, j] != 6);
constraint forall(j in 1..6)(horario[2, j] != 6);
constraint forall(j in 1..6)(horario[4, j] != 6);
constraint forall(j in 1..6)(horario[5, j] != 6);

constraint forall(i in 2..5, j in 1..6)(horario[i, j] != 3);
