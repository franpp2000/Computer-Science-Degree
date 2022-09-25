#include <stack>
#include <iostream>

using namespace std;

stack<pair<int,int>> salida_laberinto(char **laberinto, int num_filas, int num_columnas){

  stack<pair<int, int>> pasos;
  pair<int, int> pos_act;
  bool fin = false;
  
  //Find E
  for(int i = 0; i < num_filas && !fin; i++)
    for(int j = 0; j < num_columnas && !fin; j++)
      if(laberinto[i][j] == 'E'){
				fin = true;
        pos_act.first = i;
        pos_act.second = j;
        pasos.push(pos_act);
      }
	
	fin = false;

  while(!fin){
    //Determine where to go

    //DOWN
    if(pos_act.first + 1 < num_filas && laberinto[pos_act.first + 1][pos_act.second] != '1' && laberinto[pos_act.first + 1][pos_act.second] != '.'){
      if(laberinto[pos_act.first + 1][pos_act.second] == 'S'){
        pos_act.first++;
        pasos.push(pos_act);
        fin = true;
      }
      else{
        laberinto[pos_act.first][pos_act.second] = '.';
        pos_act.first++;
        pasos.push(pos_act);
      }
    }

    //UP
    else if(pos_act.first - 1 >= 0 && laberinto[pos_act.first - 1][pos_act.second] != '1' && laberinto[pos_act.first - 1][pos_act.second] != '.'){
      if(laberinto[pos_act.first - 1][pos_act.second] == 'S'){
        pos_act.first--;
        pasos.push(pos_act);
        fin = true;
      }
      else{
        laberinto[pos_act.first][pos_act.second] = '.';
        pos_act.first--;
        pasos.push(pos_act);
      }
    }

    //LEFT
    else if(pos_act.second - 1 >= 0 && laberinto[pos_act.first][pos_act.second - 1] != '1' && laberinto[pos_act.first][pos_act.second - 1] != '.'){
      if(laberinto[pos_act.first][pos_act.second - 1] == 'S'){
        pos_act.second--;
        pasos.push(pos_act);
        fin = true;
      }
      else{
        laberinto[pos_act.first][pos_act.second] = '.';
        pos_act.second--;
        pasos.push(pos_act);
      }
    }

    //RIGHT
    else if(pos_act.second + 1 < num_columnas && laberinto[pos_act.first][pos_act.second + 1] != '1' && laberinto[pos_act.first][pos_act.second + 1] != '.'){
      if(laberinto[pos_act.first][pos_act.second + 1] == 'S'){
        pos_act.second++;
        pasos.push(pos_act);
        fin = true; 
      }
      else{
        laberinto[pos_act.first][pos_act.second] = '.';
        pos_act.second++;
        pasos.push(pos_act);
      }
    }

    //IF I CANT AVANCE, COME BACK
    else{
      laberinto[pos_act.first][pos_act.second] = '.';
			if(pasos.empty())
        fin = true;
      else{  
        pasos.pop();
        if(!pasos.empty())
          pos_act = pasos.top();
      }  

      if(pasos.empty())
        fin = true;
    }

  }

  return pasos;    
}

int main(){
	stack<pair<int,int>> pasos;
  const int fils = 8, cols = 10;
  char cadena[fils][cols] = 
      {'1','0','1','1','E','1','1','1','1','1',
       '1','1','1','1','0','1','1','1','1','1',
       '1','0','0','0','0','1','1','0','0','1',
       '1','1','0','1','1','1','1','0','1','1',
       '1','1','0','0','0','1','1','0','1','1',
       '1','1','1','1','0','1','0','0','0','0',
       '1','1','1','1','0','1','0','1','1','0',
       '1','1','0','0','0','0','0','0','1','S'};

  char **laberinto;
  laberinto = new char*[fils];    
  for(int i = 0; i < fils; i++)
    laberinto[i] = new char[cols];

  for(int i = 0; i < fils; i++)
    for(int j = 0; j < cols; j++)
      laberinto[i][j] = cadena[i][j];  

  for(int i = 0; i < fils; i++){
    for(int j = 0; j < cols; j++)
      cout << laberinto[i][j];
    cout << endl;  
  }    

  pasos = salida_laberinto(laberinto, fils, cols);
	
  if(pasos.empty())
    cout << "No tiene solucion el laberinto";
	
  while(!pasos.empty()){
		cout << "(" << pasos.top().first << "," << pasos.top().second << ")" << endl;
		pasos.pop();
  }

  for(int i = 0; i < fils; i++)
    delete[] laberinto[i];
  
  delete [] laberinto;  

}