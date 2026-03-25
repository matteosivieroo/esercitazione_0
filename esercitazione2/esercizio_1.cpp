#include <iostream>

int main() {
    double ad[4] = {0.0, 1.1, 2.2, 3.3};
    float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    int ai[3] = {0, 1, 2};

    int x = 1;
    float y = 1.1; 

    std::cout << "\nindirizzo di x: " << &x << "\n";
    std::cout << "indirizzo di y: " << &y << "\n";

    std::cout << "\n--- indirizzi array double (ad) ---" << "\n";
    for(int i = 0; i < 4; ++i) 
        std::cout << "&ad[" << i << "]: " << &ad[i] << "\n";

    std::cout << "\n--- indirizzi array float (af) ---" << "\n";
    for(int i = 0; i < 8; ++i) 
        std::cout << "&af[" << i << "]: " << &af[i] << "\n";

    std::cout << "\n--- indirizzi array int (ai) ---" << "\n";
    for(int i = 0; i < 3; ++i) 
        std::cout << "&ai[" << i << "]: " << &ai[i] << "\n";


    (&y)[1] = 0; 

    std::cout << "\nvalore finale di x: " << x << "\n"; 

    return 0;
}