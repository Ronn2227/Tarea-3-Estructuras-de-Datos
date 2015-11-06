#ifndef PARQUE
#define PARQUE
#include <vector>

class Parque{
public:
	Parque(){};
	~Parque(){}
	std::vector<int> busquedaExhaustiva(const int** espera, int m, int n, const int* disfrute, const int** traslado){
		maximo = 0;
		std::vector<int> respuesta(m);
		std::vector<int> borrador(m);
		busquedaRecursiva(0, 0 , 0, espera, traslado, disfrute, m, n, respuesta, borrador);
		respuesta.shrink_to_fit();

		return respuesta;
	}
	std::vector<int> programacionDinamica(const int** espera, int m, int n, const int* disfrute, const int** traslado){};
	std::vector<int> algoritmoAvido(const int** espera, int m, int n, const int* disfrute, const int** traslado){};

private:
	int maximo = 0;

	int busquedaRecursiva(int i, int tiempoAcumulado , int disfruteAcumulado, const int ** espera, const int** traslado,
						  const int* disfrute, int m, int n, std::vector<int> respuesta, std::vector<int> borrador){
		int maxDisfrute = 0;
		if (tiempoAcumulado == m || i == m){
			maxDisfrute = disfruteAcumulado;
		}
		else{
			for (int j = 1; j <= n; ++j){
				int duracion;
				if (i > 0){
					duracion = espera[j][tiempoAcumulado] + traslado[borrador[i - 1]][j] + disfrute[j];
				}

				if (i = 0){
					duracion = espera[j][tiempoAcumulado] + traslado[borrador[i]][j] + disfrute[j];
					borrador[i] = j;
					maxDisfrute = busquedaRecursiva(i + 1, tiempoAcumulado + duracion, disfruteAcumulado + disfrute[j], espera, traslado, disfrute, m, n, respuesta, borrador);
					if (maxDisfrute > maximo){
						maximo = maxDisfrute;
						respuesta = borrador;
					}
				}
				else if (j != borrador[i - 1] && duracion + traslado[j][n] <= m - tiempoAcumulado){
					maxDisfrute = busquedaRecursiva(i + 1, tiempoAcumulado + duracion, disfruteAcumulado + disfrute[j], espera, traslado, disfrute, m, n, respuesta, borrador);
					if (maxDisfrute > maximo){
						maximo = maxDisfrute;
						respuesta = borrador;
					}
				}
			}
		}
		if (maxDisfrute == 0){
			maxDisfrute = disfruteAcumulado;
		}
		return maxDisfrute;
	}
};

#endif
