#include <iostream>

using namespace std;

int main() {
    int numero, cocahina, divisor = 1;
    
    cout << "Ingrese un numero: ";
    cin >> numero;
    
    cocahina = numero;
    
                 
    while(cocahina / 10 > 0){               
        
		  cocahina = cocahina / 10;          
        divisor = divisor * 10;            
    
	 }
    
    while(divisor > 0){
        
		  cout << numero / divisor;
        
		  if(divisor / 10 > 0){
            
			cout << " ";
        }
        
		  numero = numero % divisor;
        divisor = divisor / 10;
    }
    
    
}

        


