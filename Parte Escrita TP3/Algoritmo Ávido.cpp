std::vector<int> algoritmoAvido(int** espera, int m, int n, int* disfrute, int** traslado){
maximo = 0;
	std::vector<int> respuesta(m);
	std::vector<int> borrador(m);
	avidoRecursivo(0, 0, 0, espera, traslado, disfrute, m, n, respuesta, borrador);

	int i = 1;
	while (respuesta[i] != 0){
		++i;
	}
	respuesta.resize(i);

	return respuesta;
}

int avidoRecursivo(int i, int tiempoAcumulado, int atraccionesVisitadas, int ** espera, int** traslado,
				       int* disfrute, int m, int n, std::vector<int> & respuesta, std::vector<int>& borrador){
	int maxAtracciones = 0;
	if (tiempoAcumulado == m || i == m){
		maxAtracciones = atraccionesVisitadas;
	}
	else{
		int anterior = 0;
		if (i > 0){
			anterior = borrador[i-1];
		}
		int menor = m;
		std::vector<int> mejores;
		for (int j = 1; j < n; ++j){ //Escoge todos los que tengan menor duracion
			if (j != anterior && tiempoAcumulado + traslado[anterior][j - 1] < m){
				int duracion = traslado[anterior][j - 1] + espera[tiempoAcumulado + traslado[anterior][j - 1]][j] + disfrute[j - 1];
				if (tiempoAcumulado + duracion + traslado[j][n - 1] <= m){
					if (duracion < menor){
						menor = duracion;
						mejores.resize(0);
						mejores.push_back(j);
					}
					else if (duracion == menor){
						mejores.push_back(j);
					}
				}
			}
		}
		for (int j = 0; j < mejores.size(); ++j){
			borrador[i] = mejores[j];
			maxAtracciones = avidoRecursivo(i + 1, tiempoAcumulado + menor, atraccionesVisitadas + 1, espera, traslado, disfrute, m, n, respuesta, borrador);
			if (maxAtracciones > maximo){
				maximo = maxAtracciones;
				respuesta = borrador;
			}
		}
	}
	if (maxAtracciones == 0){
		maxAtracciones = atraccionesVisitadas;
	}
	return maxAtracciones;
}