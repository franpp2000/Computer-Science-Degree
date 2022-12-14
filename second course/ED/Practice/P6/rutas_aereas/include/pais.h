#ifndef _PAIS_
#define _PAIS_

#include "punto.h"

class Pais{
  private:
    Punto p;
    string pais;
    string bandera;
    
  public:
    Pais(){}
    Punto GetPunto()const { return p;}
    string GetPais()const{ return pais;}
    string GetBandera()const{ return bandera;}
    
    bool operator<(const Pais &P)const{
	    return pais < P.pais;
    }

    bool operator==(const Pais &P)const{
	    return pais == P.pais;
    }
    
    bool operator==(const Punto &P)const{
	    return p == P;
    }

    friend istream & operator>>(istream & is, Pais & P){
      double lat,lng;
	
	  is >> lat >> lng >> P.pais >> P.bandera;
	
	  P.p=Punto(lat,lng);
	  
      return is;
    }

    friend ostream & operator<<(ostream & os, const Pais &P){
	  os << P.p << " " << P.pais << " " << P.bandera << endl;
	  
      return os;
    }
};
#endif