     #include <iostream>
    using namespace std;
     
    int main () {
    	
        char c;
        
		  cout << "Digite una letra en minuscula o mayuscula: ";
		  cin >> c;
        
		  if(c >= 'a' && c <= 'z') 
		  {
            c -= 'a' - 'A';
            
				cout << c;
        }
		  		
				  else if(c >= 'A' && c <= 'Z')
					{
            		c -= 'A' - 'a';
            		
						cout << c;
        		   }
        
		  
    }
