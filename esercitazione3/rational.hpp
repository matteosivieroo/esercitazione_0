#pragma once
#include <iostream>
#include <concepts>
#include <numeric>

template<typename I> requires std::integral<I>
class rational {
private:
    I num_;
    I den_;

    void normalize() {
        //gestione di NaN (0/0)
        if (den_ == 0 && num_ == 0) return;

        //gestione di infinito (n/0)
        if (den_ == 0) {
            if (num_ > 0) {
                num_ = 1;
            } else {
                num_ = -1;
            }
            return;
        }

        //gestione dello zero (0/n)
        if (num_ == 0) {
            den_ = 1;
            return;
        }

        //semplificazione tramite massimo comune divisore
        I mcd = std::gcd(num_, den_); //funzione per il calcolo dell'MCD contenuta nell'header <numeric>
        num_ /= mcd;
        den_ /= mcd;

        //se il denominatore è negativo sposta il segno al numeratore
        if (den_ < 0) {
            num_ = -num_; 
            den_ = -den_;
        }
    }

public:
    //costruttore di default che inizializza la frazione a 0/1
    rational() : num_(I{0}), den_(I{1}) {}

    //costruttore user-defined
    rational(const I& n, const I& d) : num_(n), den_(d) {
        normalize();
    }

    //metodi per l'accesso in sola lettura
    I numeratore() const { return num_; } //restituisce il valore del numeratore
    I denominatore() const { return den_; } //restituisce il valore del denominatore

    bool is_nan() const { return num_ == 0 && den_ == 0; } //verifica se il numero è NaN
    bool is_inf() const { return num_ != 0 && den_ == 0; } //verifica se il numero è inf




    rational& operator+=(const rational& other) {
        if (is_nan() || other.is_nan()) { //qualsiasi operazione con NaN restituisce NaN
            num_ = 0; 
            den_ = 0; 
        } else if (is_inf() && other.is_inf()) { //operazioni tra infiniti
            if ((num_ > 0) == (other.num_ > 0)) { //stesso segno di infinito
            } else { //segno opposto -> NaN
                num_ = 0; 
                den_ = 0;
            }
        } else if (is_inf()) { // inf + numero = inf
        } else if (other.is_inf()) {
            num_ = other.num_; 
            den_ = other.den_;
        } else { //formula somma tra frazioni
            num_ = num_ * other.den_ + other.num_ * den_;
            den_ = den_ * other.den_;
            normalize();
        }
        return *this;
    }

    rational& operator-=(const rational& other) {
        if (is_nan() || other.is_nan()) {
            num_ = 0; 
            den_ = 0;
        } else if (is_inf() && other.is_inf()) {
            if ((num_ > 0) != (other.num_ > 0)) { //inf-(-inf) =inf
            } else { //inf-inf=NaN
                num_ = 0; 
                den_ = 0;
            }
        } else if (is_inf()) {
            // inalterato
        } else if (other.is_inf()) {
            num_ = -other.num_; 
            den_ = other.den_;
        } else {
            num_ = num_ * other.den_ - other.num_ * den_;
            den_ = den_ * other.den_;
            normalize();
        }
        return *this;
    }

    rational& operator*=(const rational& other) {
        if (is_nan() || other.is_nan()) {
            num_ = 0; 
            den_ = 0;
        } else if ((is_inf() && other.num_ == 0) || (other.is_inf() && num_ == 0)) { //inf * 0= NaN
            num_ = 0; 
            den_ = 0;
        } else if (is_inf() || other.is_inf()) {
            I sign; //regola dei segni per moltiplicazione tra infiniti
            if ((num_ > 0) == (other.num_ > 0)) {
                sign = 1;  //segni concordi -> +inf
            } else {
                sign = -1; // segni discordi -> -inf
            }
            num_ = sign; 
            den_ = 0;
        } else { //moltiplicazione tra frazioni finite
            num_ *= other.num_;
            den_ *= other.den_;
            normalize();
        }
        return *this;
    }

    rational& operator/=(const rational& other) {
        if (is_nan() || other.is_nan() || (is_inf() && other.is_inf()) || (num_ == 0 && other.num_ == 0)) { // NaN, inf/inf, 0/0 -> NaN
            num_ = 0; 
            den_ = 0;
        } else if (other.is_inf()) {
            // numero / inf = 0
            num_ = 0; 
            den_ = 1;
        } else if (other.num_ == 0) { // divisione per 0 -> +-inf
        I sign;
        if ((num_ > 0) == (other.den_ > 0)) {
            sign = 1;   //segni concordi -> +inf
        } else {
            sign = -1;  //segni discordi -> -inf
        }            
        num_ = sign; 
        den_ = 0;

        } else { //divisione tra frazioni
            num_ *= other.den_;
            den_ *= other.num_;
            normalize();
        }
        return *this;
    }



    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret; 
    }

    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }

    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other;
        return ret;
    }

    rational operator/(const rational& other) const {
        rational ret = *this;
        ret /= other;
        return ret;
    }
};



template<typename I>
std::ostream& operator<<(std::ostream& os, const rational<I>& r) {
    if (r.denominatore() == 0) { // se il denominatore è zero stampa NaN, +inf o -inf a seconda che il numeratore sia 0, >0 o <0
        if (r.numeratore() == 0) os << "NaN";
        else if (r.numeratore() > 0) os << "+inf";
        else os << "-inf";
    } else { //se il denominatore è diverso da 0
        os << r.numeratore(); // stampa il numeratore
        if (r.denominatore() != 1) { //se il denominatore è diverso da 1 aggiunge "/" e il denominatore
            os << "/" << r.denominatore();
        }
    }
    return os;
}