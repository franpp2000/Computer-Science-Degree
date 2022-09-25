#include <iostream>
#include <queue>

using namespace std;

struct Persona{
  string nombre;
  string apellidos;
  int prioridad;

  Persona(string n, string ap, int pr)
  :nombre(n), apellidos(ap), prioridad(pr)
  {}
};

struct compPersonas{
  bool operator()(const Persona &p1, const Persona &p2){
    return p1.prioridad < p2.prioridad;
  }
};

int main(){

  priority_queue<Persona, vector<Persona>, compPersonas> personas;

  Persona p1("Pepe", "Gonzalez", 5);
  personas.push(p1);
  Persona p2("Tomas", "Garcia", 4);
  personas.push(p2);
  Persona p3("Juan", "Perez", 1);
  personas.push(p3);
  Persona p4("Clara", "Perea", 7);
  personas.push(p4);
  Persona p5("Antonio", "Perez", 2);
  personas.push(p5);
  Persona p6("Jose", "Zaragoza", 9);
  personas.push(p6);

  while(!personas.empty()){
    cout << personas.top().nombre << " (" << personas.top().prioridad << ")" << endl;
    personas.pop();
  }
}