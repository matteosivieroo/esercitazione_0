#include <iostream>
#include <cmath>     

int main() {
    static const int N = 10; 
    double arr[N] = {1.2, 3.4, 0.5, 7.8, 4.2, 2.1, 9.0, 5.5, 3.3, 6.1};

    double massimo = arr[0];
	double minimo = arr[0];

    double somma = 0.0;
    for(int i = 0; i < N; ++i) {
        somma += arr[i];
        massimo = std::max(massimo, arr[i]);
		minimo = std::min(minimo, arr[i]);
    }
    double media = somma / N;

    double var = 0.0;
    for(int i = 0; i < N; ++i) {
        var += (arr[i] - media)*(arr[i] - media);
    }
    double dev_std = std::sqrt(var / N);

    std::cout << "Minimo: " << minimo << "\n";
    std::cout << "Massimo: " << massimo << "\n";
    std::cout << "Media: " << media << "\n";
    std::cout << "Deviazione standard: " << dev_std << "\n";

    return 0;
}