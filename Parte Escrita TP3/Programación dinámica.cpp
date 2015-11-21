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