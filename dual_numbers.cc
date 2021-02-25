#include <iostream>
#include <cmath>

using namespace std;

struct dual{
    double real;
    double e;
    dual(const double real_, const double e_){
        real = real_;
        e = e_;
    }
    dual(const double real_){
        real = real_;
        e = 1;
    }

    ~dual(){
        free(&real);
        free(&e);
    }

    dual operator+(const dual &b){
        return dual(real + b.real, e + b.e);
    }

    dual operator+(const double &b){
         return dual(b + real,e);
    }

    dual operator-(const dual &b){
        return dual(real - b.real, e - b.e);
    }

    dual operator-(const double &b){
         return dual(real - b,e);
    }

    dual operator*(const double &b){
        return dual(real * b , e * b);
    }

    dual operator*(const dual &b){
        return dual(real * b.real , real * b.e + e*b.real);
    }

    dual operator/(const dual &b){
        return dual(real / b.real, (e * b.real - real * b.e)/(b.real*b.real));
    }

    dual operator/(const double &b){
        return dual(real * (1/b) , e * (1/b));
    }

    dual operator^(const double &b){
        double temp = pow(real, b);
        return dual(temp, temp * ((e * b)/real));
        }

    dual operator^(const dual &b){
        double temp = pow(real, b.real);
        return dual(temp , temp * ( b.e * (log(real)) + ((e * b.real)/real) )  );
        }

};


ostream& operator<<(ostream& os, const dual& a)
    {
    return os << a.real << " + " << a.e << "e~";
    }

dual operator/(const double &a,const dual &b){
    return dual(a,0) / b;
    }

dual operator^(const double &a, const dual &b){
    double temp = pow(a, b.real);
    return dual(temp , temp * ( b.e * (log(a)) )  );
    }

    

dual exp(const dual &a){
    double temp = pow(2.7182818284, a.real);
    return dual(temp,temp * a.e);
}

dual log(const dual &a){
    return dual(log(a.real), (a.e/a.real));
}

dual sin(const dual &a){
    return dual(sin(a.real), cos(a.real) * a.e);
}

dual cos(const dual &a){
    return dual(cos(a.real), -sin(a.real) * a.e);
}

dual tan(const dual &a){
    return sin(a)/cos(a);
}

int main() {
    dual x(3);
    dual test = (sin(cos(x) - x))^2;
    cout << "f(x): " << test.real << " - f'(x): " << test.e;
}