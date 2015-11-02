#ifndef PARQUE
#define PARQUE

class Parque{
public:
	Parque(){};
	~Parque(){}
	std::vector<int> busquedaExhaustiva(const int** espera, int m, int n, const int* disfrute, const int** traslado){};
	std::vector<int> programacionDinamica(const int** espera, int m, int n, const int* disfrute, const int** traslado){};
	std::vector<int> algoritmoAvido(const int** espera, int m, int n, const int* disfrute, const int** traslado){};
};

#endif
