#ifndef PARQUE
#define PARQUE
#include <vector>

class Parque{
public:
	Parque(){};
	~Parque(){}

	std::vector<int> busquedaExhaustiva(int** espera, int m, int n, int* disfrute, int** traslado){
		maximo = 0;
		std::vector<int> respuesta(m);
		std::vector<int> borrador(m);
		busquedaRecursiva(0, 0, 0, espera, traslado, disfrute, m, n, respuesta, borrador);
		int i = 1;
		while (respuesta[i] != 0){
			++i;
		}
		respuesta.resize(i);
		return respuesta;
	}

	std::vector<int> programacionDinamica(int** espera, int m, int n, int* disfrute, int** traslado){
		int ** oraculo = new int*[m];
		int ** camino = new int*[m];
		std::vector<int> respuesta(m);
		oraculo[m - 1] = new int[n];
		camino[m - 1] = new int[n];
		for (int i = 0; i < n; ++i){
			oraculo[m - 1][i] = 0;
			camino[m - 1][i] = 0;
		}

		for (int i = m - 2; i >= 0; --i){
			oraculo[i] = new int[n];
			camino[i] = new int[n];
			for (int j = 0; j < n; ++j){
				oraculo[i][j] = -1;
				for (int k = 1; k < n; ++k){
					if (k != j && i + traslado[j][k-1] < m){
						int duracion = traslado[j][k-1] + espera[i + traslado[j][k-1]][k] + disfrute[k-1];
						if (i + duracion + traslado[k][n - 1] <= m && oraculo[i + duracion][k] + 1 > oraculo[i][j]){
							oraculo[i][j] = oraculo[i + duracion][k] + 1;
							camino[i][j] = k;
						}
					}
				}
			}
		}
		respuesta.resize(oraculo[0][0]);
		int j = 0;
		int k = 0;
		for (int i = 0; i < oraculo[0][0]; ++i){
			respuesta[i] = camino[j][k];
			int duracion = traslado[k][respuesta[i] - 1] + espera[j + traslado[k][respuesta[i] - 1]][respuesta[i]] + disfrute[respuesta[i] - 1];
			j += duracion;
			k = respuesta[i];
		}
		return respuesta;
	}

	std::vector<int> algoritmoAvido(int** espera, int m, int n, int* disfrute, int** traslado){
		std::vector<int> respuesta(m);
		int tiempoGastado = 0;
		int anterior = 0;
		for (int i = 0; i < m && tiempoGastado <= m; ++i){
			int menor = m;
			for (int j = 1; j < n; ++j){
				if (j != anterior && tiempoGastado + traslado[anterior][j - 1] < m){
					int duracion = traslado[anterior][j - 1] + espera[tiempoGastado + traslado[anterior][j - 1]][j] + disfrute[j - 1];
					if (tiempoGastado + duracion + traslado[j][n - 1] <= m){
						if (duracion < menor){
							menor = duracion;
							respuesta[i] = j;
						}
						else if (duracion == menor){
							int duracion1 = -1;
							int duracion2 = -1;
							int siguiente = mejorSiguiente(tiempoGastado + menor, respuesta[i], espera, m, n, disfrute, traslado);
							if (siguiente > -1){
								duracion1 = traslado[respuesta[i]][siguiente - 1] + espera[tiempoGastado + menor + traslado[respuesta[i]][siguiente - 1]][siguiente] + disfrute[siguiente - 1];
							}
							siguiente = mejorSiguiente(tiempoGastado + menor, j, espera, m, n, disfrute, traslado);
							if (siguiente > -1){
								duracion2 = traslado[j][siguiente - 1] + espera[tiempoGastado + menor + traslado[j][siguiente - 1]][siguiente] + disfrute[siguiente - 1];
							}
							if (duracion1 > duracion2){
								respuesta[i] = j;
							}
						}
					}
				}
			}
			tiempoGastado += menor;
			anterior = respuesta[i];
		}

		int i = 1;
		while (respuesta[i] != 0){
			++i;
		}
		respuesta.resize(i);

		return respuesta;
	}

private:
	int maximo = 0;

	int busquedaRecursiva(int i, int tiempoAcumulado , int atraccionesVisitadas, int ** espera, int** traslado,
						  int* disfrute, int m, int n, std::vector<int> & respuesta, std::vector<int>& borrador){
		int maxAtracciones = 0;
		if (tiempoAcumulado == m || i == m){
			maxAtracciones = atraccionesVisitadas;
		}
		else{
			for (int j = 1; j < n; ++j){ // Prueba eligiendo cada posible atraccion
				int duracion;
				if (i > 0 && tiempoAcumulado + traslado[borrador[i - 1]][j - 1] < m){
					duracion = traslado[borrador[i - 1]][j - 1] + espera[tiempoAcumulado + traslado[borrador[i - 1]][j - 1]][j] + disfrute[j - 1];
				}

				if (i == 0 && espera[tiempoAcumulado + traslado[0][j-1]][j] != -1){
					duracion = traslado[0][j - 1] + espera[tiempoAcumulado + traslado[0][j - 1]][j] + disfrute[j - 1];
					borrador[i] = j;
					maxAtracciones = busquedaRecursiva(i + 1, tiempoAcumulado + duracion, atraccionesVisitadas + 1, espera, traslado, disfrute, m, n, respuesta, borrador);
					if (maxAtracciones > maximo){
						maximo = maxAtracciones;
						respuesta = borrador;
					}
				}
				else if (i > 0 && j != borrador[i - 1] && tiempoAcumulado + traslado[borrador[i - 1]][j - 1] < m && duracion + traslado[j][n - 1] <= m - tiempoAcumulado && espera[tiempoAcumulado + traslado[borrador[i - 1]][j - 1]][j] != -1){
					borrador[i] = j;
					maxAtracciones = busquedaRecursiva(i + 1, tiempoAcumulado + duracion, atraccionesVisitadas + 1, espera, traslado, disfrute, m, n, respuesta, borrador);
					if (maxAtracciones > maximo){
						maximo = maxAtracciones;
						respuesta = borrador;
					}
				}
			}
		}
		if (maxAtracciones == 0){
			maxAtracciones = atraccionesVisitadas;
		}
		return maxAtracciones;
	}

	int mejorSiguiente(int momento, int atraccion, int** espera, int m, int n, int* disfrute, int** traslado){
		int mejor = m;
		int respuesta = -1;
		for (int i = 1; i < n; ++i){
			if (i != atraccion && momento + traslado[atraccion][i - 1] < m){
				int duracion = traslado[atraccion][i - 1] + espera[momento + traslado[atraccion][i - 1]][i] + disfrute[i - 1];
				if (duracion < mejor){
					mejor = duracion;
					respuesta = i;
				}
			}
		}
		return respuesta;
	}

	int mejorAnterior(int momento, int atraccion, int** espera, int m, int n, int* disfrute, int** traslado){
		int mejor = m;
		int respuesta = -1;
		for (int i = 1; i < n; ++i){
			if (i != atraccion && momento - traslado[atraccion][0] > 0){
				int duracion = traslado[atraccion][i - 1] + espera[momento - traslado[atraccion][i - 1]-disfrute [i-1]][i] + disfrute[i - 1];
				if (duracion > mejor){
					mejor = duracion;
					respuesta = i;
				}
			}
		}
		return respuesta;
	}
};

#endif
