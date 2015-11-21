// Tarea 3 estructuras.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Parque.h"
#include "windows.h"

using namespace std;

double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b){
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

int _tmain(int argc, _TCHAR* argv[]){
	LARGE_INTEGER t_ini, t_fin;
	double secs;
	int i;
	int j;
	int * disfrute = new int[13];
	int ** espera = new int*[120];
	int ** traslado = new int*[14];
	int ** tiempo;
	string linea;
	string data;
	vector<int> orden;
	Parque diversiones;
	ifstream fileDisfrute;
	ifstream fileEspera;
	ifstream fileTraslado;
	fileDisfrute.open("disfrute.csv");
	fileEspera.open("espera.csv");
	fileTraslado.open("traslado.csv");

	if (fileDisfrute.is_open()){ // Lee el archivo y crea la lista de operaciones.
		i = 0;
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
					
					disfrute[i] = b;
					++i;
				}
			}	
		}
		fileDisfrute.close();
	}

	/*
	for (j = 0; j < i; ++j){
		cout << disfrute[j] << endl;
	}
	cout << endl;
	*/
	
	if (fileEspera.is_open()){ // Lee el archivo y crea la lista de operaciones.
		i = 0;
		getline(fileEspera, linea);
		while (getline(fileEspera, linea)){
			espera[i] = new int[14];
			j = 0;
			while (linea.find(",") != string::npos){
				int a = linea.find(",");
				int b;
				data = linea.substr(0, a);
				linea = linea.substr(a + 1);
				try{
					if (data.length() == 0){
						b = -1;
					}
					else{
						b = stoi(data);
					}
				}
				catch (invalid_argument exception){
					b = -2;
				}
				if (b > -2){
					espera[i][j] = b;
					++j;
				}
				if (linea.length() == 1){
					b = stoi(linea);
					espera[i][j] = b;
					++j;
				}
			}
			++i;
		}
		fileEspera.close();
	}

	for (int h = 0; h < j; ++h){
		int cuantos = 0;
		for (int k = i-1; k >= 0; --k){
			if (espera[k][h] == -1){
				cuantos++;
				espera[k][h] = cuantos;
			}
			else {
				cuantos = 0;
			}
		}
	}

	/*
	for (int k = 0; k < i; ++k){
		for (int h = 0; h < j; ++h){
			cout << espera[k][h] << " ";
		}
		cout << endl;
	}
	*/
	
	
	if (fileTraslado.is_open()){ // Lee el archivo y crea la lista de operaciones.
		i = 0;
		getline(fileTraslado, linea);
		while (getline(fileTraslado, linea)){
			traslado[i] = new int[14];
			j = 0;
			while (linea.find(",") != string::npos){
				int a = linea.find(",");
				int b;
				data = linea.substr(0, a);
				linea = linea.substr(a + 1);
				try{
					if (data.length() == 0){
						b = -1;
					}
					else{
						b = stoi(data);
					}
				}
				catch (invalid_argument exception){
					b = -2;
				}
				if (b > -2){
					traslado[i][j] = b;
					++j;
				}
				if (linea.length() == 1){
					b = stoi(linea);
					traslado[i][j] = b;
					++j;
				}
			}
			++i;
		}
		fileTraslado.close();
	}
	/*
	cout << endl;

	for (int k = 0; k < i; ++k){
		for (int h = 0; h < j; ++h){
			cout << traslado[k][h] << " ";
		}
		cout << endl;
	}
	*/
	
	int inicio = 0;
	int final = 48;
	int tamano = 48;
	tiempo = new int*[tamano];
	int ini;
	for (i = 0, ini = inicio; i < tamano; ++i, ++ini){
		tiempo[i] = new int[14];
		for (j = 0; j < 14; ++j){
			tiempo[i][j] = espera[ini][j];
		}
	}
	for (i = 0; i < tamano; ++i){
		for (j = 0; j < 14; ++j){
			cout << tiempo[i][j] << " ";
		}
		cout << endl;
	}

	QueryPerformanceCounter(&t_ini);
	orden = diversiones.algoritmoAvido(tiempo,tamano,14,disfrute,traslado);
	QueryPerformanceCounter(&t_fin);
	secs = performancecounter_diff(&t_fin, &t_ini);
	printf("%.16g milliseconds\n", secs * 1000);

	int tiempoDisfrute = 0;
	for (unsigned int h = 0; h < orden.size(); ++h){
		tiempoDisfrute += disfrute[orden[h]-1];
		cout << orden[h] << " ";
	}
	cout << endl << tiempoDisfrute << endl;
	


	return 0;
}

