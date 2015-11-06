// Tarea 3 estructuras.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parque.h"
//#include <fstream>
//#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[]){

	int i = 0;
	int j = 0;
	int * disfrute[13];
	int ** espera = new int*[14];
	int ** traslado = new int*[14];
	int ** tiempo = new int*[14];
	string linea;
	string data;
	ifstream fileDisfrute;
	ifstream fileEspera;
	ifstream fileTraslado;
	fileDisfrute.open("disfrute.csv");
	fileEspera.open("espera.csv");
	fileTraslado.open("traslado.csv");

	if (fileDisfrute.is_open()){ // Lee el archivo y crea la lista de operaciones.
		while (getline(fileDisfrute, linea)){
			while (linea.find(",")!= string::npos){
				int a = linea.find(",");
				int b;
				data = linea.substr(0, a);
				linea = linea.substr(a + 1);
				try{
					if (linea.length() == 0){
						b = -1;
					}
					else{
						b = stoi(linea);
					}
				}
				catch (invalid_argument exception){
					b = -2;
				}
				if (b > -2){
					
					*disfrute[i] = b;
					++i;
				}
			}	
		}
		fileDisfrute.close();
	}

	for (j = 0; j <= i; ++j){
		cout << *disfrute[j] << endl;
	}
	/*
	if (fileEspera.is_open()){ // Lee el archivo y crea la lista de operaciones.
		while (getline(fileEspera, linea)){

		}
		fileEspera.close();
	}

	if (fileTraslado.is_open()){ // Lee el archivo y crea la lista de operaciones.
		while (getline(fileTraslado, linea)){

		}
		fileTraslado.close();
	}
	*/

	return 0;
}

