#ifndef PARQUE
#define PARQUE
#include <vector>

class Parque{
public:
	Parque(){};
	~Parque(){}
	std::vector<int> busquedaExhaustiva(const int** espera, int m, int n, const int* disfrute, const int** traslado){
		return respuesta;
	}
	std::vector<int> programacionDinamica(const int** espera, int m, int n, const int* disfrute, const int** traslado){};
	std::vector<int> algoritmoAvido(const int** espera, int m, int n, const int* disfrute, const int** traslado){};

private:
	std::vector<int> respuesta;
	std::vector<int> borrador (4);

	int busquedaRecursiva(int i, int tiempoRestante, int DisfruteAcumulado, const int ** espera, const int** traslado, const int* disfrute, int m, int n){
		int maxDisfrute = 0;
		if (tiempoRestante == 0){
			maxDisfrute = DisfruteAcumulado;
		}
		else{
			for (int j = 0; j < n; ++j){
				borador[j] = j;
			}
		}
		return maxDisfrute;
	}
};

#endif
