/*

6. Realizar un programa que lea dos vectores de caracteres (sin repetición) y construya un vector
	intersección y un vector unión.

*/

#include<iostream>

using namespace std;

int main()
{
	
	// DECLARACION DE VARIABLES:
	
	const int MAX = 1000;                                            //<----- Tamaño maximo de los vectores
	
	char v1[MAX], v2[MAX], v_union[MAX], v_interseccion[MAX];        //<----- Definicion de los vectores a utilizar
	
	int tam_v1, tam_v2, tam_v_union = 0, tam_v_interseccion = 0;     //<----- tamaño de los distintos vectores
	
	bool coincidencia = false;                                       //<----- booleano que indica si hay coincidencias o no
	
	int indice_v_union = 0, indice_v_interseccion = 0;               //<----- indicador de una posicion de v_union y v_interseccionuh
	
	
	// NUMERO DE ELEMENTOS DEL VECTOR V1:
	
	cout << "Numero de elementos del vector 1: ";
	cin >> tam_v1;
	
	
	// INTRODUCIMOS LOS ELEMENTOS DEL VECTOR V1:
	
	for(int i = 0; i < tam_v1; i++)
	{
		cout << "\nPosicion " << i << ": ";
		cin >> v1[i];
	} 
	
	
	// NUMERO DE ELEMENTOS DEL VECTOR V2:
	
	cout << "\n\nNumero de elementos del vector 2: ";
	cin >> tam_v2;
	
	
	// INTRODUCIMOS LOS ELEMENTOS DEL VECTOR V2:
	
	for(int i = 0; i < tam_v2; i++)
	{
		cout << "\nPosicion " << i << ": ";
		cin >> v2[i];
	} 
	
	
	// PARA CREAR EL VECTOR INTERSECCION BUSCAREMOS LOS CARACTERES COINCIDENTES ENTRE LOS VECTORES, DE MANERA 
	// QUE ESTOS SERAN INTRODUCIDOS EN EL VECTOR INTERSECCION.

	for(int i = 0; i < tam_v1; i++)
	{
		
		for(int j = 0; j < tam_v2 && coincidencia == false; j++)   
		{                                                           
			if(v1[i] == v2[j])                                      
			{                                                       
				coincidencia = true;                                 
			}                                                       
		}                                                          
		
		
		if(coincidencia == true)   
		{                           
			tam_v_interseccion++;                
			                          
			v_interseccion[indice_v_interseccion] = v1[i];   
			                         
			indice_v_interseccion++;	          
		}  
		
		coincidencia = false;	//<----- asignacion necesaria para que haga la comprobacion con todas las posiciones.
	}

	
	// PARA CREAR EL VECTOR UNION, PRIMERO INTRODUCIMOS TODOS LOS CARACTERES DE UNO DE LOS VECTORES EN EL VECTOR UNION Y FINALMENTE
	// A ESTOS SE LES AÑADEN LOS CARACTERES QUE NO COINCIDAN ENTRE EL VECTOR RESTANTE Y LOS QUE SE HAN INTRODUCIDO EN EL VECTOR UNION 
	
	for(int i = 0; i < tam_v1; i++)       //
	{                                     //
		tam_v_union++;                     // 
		                                   // Ciclo que introduce los elementos de v1 en v_union
		v_union[indice_v_union] = v1[i];   //
		                                   //
		indice_v_union++;                  //
	}
	
	
	for(int i = 0; i < tam_v2; i++)                                     
	{                                                                   
		
		for(int j = 0; j < tam_v_union && coincidencia == false; j++)    
		{                                                                
			if(v_union[j] == v2[i])                                        
			{                                                             
				coincidencia = true;                                       
			}                  	                                         
		}                                                                
		
		
		if(coincidencia == false)   
		{                           
			tam_v_union++;                
			                          
			v_union[indice_v_union] = v2[i];   
			                         
			indice_v_union++;	          
		}  
		
		coincidencia = false;   //<----- asignacion necesaria para que haga la comprobacion con todas las posiciones.
	}
	
	
	//MOSTRAMOS VECTOR UNION Y VECTOR INTERSECCION:
	
	cout << "\n\nEl vector interseccion es:" << endl;
	
	for(int i = 0; i < tam_v_interseccion; i++)
	{
		cout << v_interseccion[i] << endl;
	}

	cout << "\n\nEl vector union es:" << endl;
	
	for(int i = 0; i < tam_v_union; i++)
	{
		cout << v_union[i] << endl;
	}
	
}
