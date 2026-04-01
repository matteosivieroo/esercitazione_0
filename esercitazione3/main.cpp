#include <iostream>
#include "rational.hpp"

using namespace std;

int main() {
    cout << "\n--- semplificazione e operazioni base ---\n";
    rational<int> a(5, -15);
    rational<int> b(9, 12);
    
    cout << "a = 5/(-15) = " << a << ", b = 9/12 = " << b << "\n";
    cout << "a + b = " << a + b << "\n";
    cout << "a - b = " << a - b << "\n";
    cout << "a * b = " << a * b << "\n";
    cout << "a / b = " << a / b << "\n\n";

    cout << "--- casi speciali (inf e NaN) ---\n";
    rational<int> inf_pos(5, 0);
    rational<int> inf_neg(-2, 0);
    rational<int> nan(0, 0);
    rational<int> zero(0, 1);
    
    cout << "5/0 viene gestito come: " << inf_pos << "\n";
    cout << "-2/0 viene gestito come: " << inf_neg << "\n";
    cout << "0/0 viene gestito come: " << nan << "\n\n";
    
    cout << "+Inf + (+Inf) = " << inf_pos + inf_pos << "\n";
    cout << "+Inf - (+Inf) = " << inf_pos - inf_pos << "\n";
    cout << "a / 0 = " << a / zero << "\n";
    cout << "+Inf * 0 = " << inf_pos * zero << "\n";
    cout << "a + NaN = " << a + nan << "\n";

    return 0;
}