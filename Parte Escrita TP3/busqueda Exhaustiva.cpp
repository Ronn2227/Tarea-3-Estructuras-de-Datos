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