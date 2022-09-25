#include <iostream>
#include <list>
#include <map>
#include <set>

using namespace std;

struct piloto{
  string nombre, apellidos, escuderia;
  int puntos;
};

class piloto_ordenar{
  public: 
    bool operator()(const piloto &p1, const piloto &p2) const{
      return !(p1.puntos < p2.puntos);
    }
};

typedef map<string, set<piloto, piloto_ordenar>::const_iterator> DiccString;
typedef multimap<string, set<piloto, piloto_ordenar>::const_iterator> MultDiccString;

class pilotos{
  private:
    set<piloto, piloto_ordenar> pilotos;
    DiccString dicc_por_nombre;
    DiccString dicc_por_apellidos;
    MultDiccString dicc_por_escuderia;

  public:
    typedef set<piloto, piloto_ordenar>::const_iterator const_iterator;

    piloto buscar_apellidos(string) const;
    piloto buscar_nombre(string) const;
    list<piloto> buscar_escuderia(string) const;
    piloto posicion(int) const;
    void insertar_piloto(const piloto &);
    void cambiar_puntuacion(string , string , int);
    
    const_iterator cbegin() const{
      return pilotos.cbegin();
    }

    const_iterator cend() const{
      return pilotos.cend();
    }

};

piloto pilotos::buscar_apellidos(string apellidos) const{
  DiccString::const_iterator it = dicc_por_apellidos.find(apellidos);
  set<piloto, piloto_ordenar>::const_iterator p = it->second;

  return *p;
}

piloto pilotos::buscar_nombre(string nombre) const{
  DiccString::const_iterator it = dicc_por_nombre.find(nombre);
  set<piloto, piloto_ordenar>::const_iterator p = it->second;

  return *p;
}

list<piloto> pilotos::buscar_escuderia(string escuderia) const{
  list<piloto> l;
  pair<MultDiccString::const_iterator, MultDiccString::const_iterator> result = dicc_por_escuderia.equal_range(escuderia);
  set<piloto, piloto_ordenar>::const_iterator p;

  for(MultDiccString::const_iterator it = result.first; it != result.second; it++){
    p = it->second;
    l.push_back(*p);
  }

  return l;
}

piloto pilotos::posicion(int n) const{
  set<piloto, piloto_ordenar>::const_iterator p = pilotos.begin();

  for(int i = 2; i <= n; i++)
    p++;

  return *p;
}

void pilotos::insertar_piloto(const piloto &p){

    pair<set<piloto, piloto_ordenar>::const_iterator, bool> par = pilotos.insert(p);
    if(par.second){
      dicc_por_apellidos[p.apellidos] = par.first;
      dicc_por_nombre[p.nombre] = par.first;
      dicc_por_escuderia.insert(MultDiccString::value_type(p.escuderia, par.first));
    }
}

void pilotos::cambiar_puntuacion(string apellidos, string nombre, int puntos){

  set<piloto, piloto_ordenar>::iterator it = pilotos.begin();
  while(it->apellidos != apellidos)
    it++;

  piloto p = *it;

  pilotos.erase(p);
  dicc_por_apellidos.erase(p.apellidos);
  dicc_por_nombre.erase(p.nombre);

  MultDiccString::const_iterator q = dicc_por_escuderia.begin();
  while(q->first != p.escuderia && q->second->apellidos != apellidos)
    q++;

  dicc_por_escuderia.erase(q);  

  p.puntos = puntos;
  insertar_piloto(p);
 
}

int main(){
  pilotos participantes;
  
  piloto p1;
  p1.nombre = "Fernando";
  p1.apellidos = "Alonso";
  p1.escuderia = "Renault";
  p1.puntos = 100;

  piloto p2;
  p2.nombre = "Lewis";
  p2.apellidos = "Hamilton";
  p2.escuderia = "Mercedes";
  p2.puntos = 130;

  piloto p3;
  p3.nombre = "Michael";
  p3.apellidos = "Schumacher";
  p3.escuderia = "Ferrari";
  p3.puntos = 150;

  piloto p4;
  p4.nombre = "Sebastian";
  p4.apellidos = "Vettel";
  p4.escuderia = "Red Bull";
  p4.puntos = 110;

  piloto p5;
  p5.nombre = "Carlos";
  p5.apellidos = "Sainz";
  p5.escuderia = "Red Bull";
  p5.puntos = 80;


  participantes.insertar_piloto(p1);
  participantes.insertar_piloto(p3);
  participantes.insertar_piloto(p2);
  participantes.insertar_piloto(p4);
  participantes.insertar_piloto(p5);

  for(pilotos::const_iterator it = participantes.cbegin(); it != participantes.cend(); it++){
    cout << it->nombre << " " << it->apellidos << " " << it->puntos << endl;
  }

  cout << endl << "Busqueda por apellidos:" << endl;
  piloto p = participantes.buscar_apellidos("Sainz");
  cout << p.nombre << " " << p.apellidos << " " << p.puntos << endl;

  cout << endl << "Busqueda por nombre:" << endl;
  p = participantes.buscar_nombre("Fernando");
  cout << p.nombre << " " << p.apellidos << " " << p.puntos << endl;

  cout << endl << "Busqueda por escuderia:" << endl;
  list<piloto> escuderia = participantes.buscar_escuderia("Red Bull");
  for(list<piloto>::iterator it = escuderia.begin(); it != escuderia.end(); it++)
    cout << it->nombre << " " << it->apellidos << " " << it->puntos << endl;

  cout << endl << "Busqueda por posicion:" << endl;
  p = participantes.posicion(5);
  cout << p.nombre << " " << p.apellidos << " " << p.puntos << endl;

  cout << endl << "Fernando Alonso tiene ahora 200 puntos, es el lider del mundial" << endl;
  participantes.cambiar_puntuacion("Alonso", "Fernando", 200);

  for(pilotos::const_iterator it = participantes.cbegin(); it != participantes.cend(); it++){
    cout << it->nombre << " " << it->apellidos << " " << it->puntos << endl;
  }

}