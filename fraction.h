#ifndef FRACTION
#define FRACTION

#include "DGtal/helpers/StdDefs.h"

using namespace DGtal;
using namespace Z2i;
using namespace std;

namespace DGtal
{
    class Fraction
    {
        int gcd(int a, int b) {return b==0 ? a : gcd(b,a%b); }
        int n, d;
     public:
        Fraction(int n, int d = 1) : n(n/gcd(n,d)), d(d/gcd(n,d)) {}
        int num() const { return n; }
        int den() const { return d; }
        Fraction& operator*=(const Fraction& rhs) {
            int new_n = n*rhs.n / gcd(n*rhs.n, d*rhs.d);
            d = d*rhs.d / gcd(n*rhs.n, d*rhs.d);
            n = new_n;
            return *this;
        }
        /*
        friend std::ostream& operator<<(std::ostream& out, const Fraction& f)
        {
            return out << f.num() << "/" << f.den() ;
        }
        */
        friend std::ostream& operator<<(std::ostream& out, const Fraction& f);
        friend bool operator==(const Fraction& lhs, const Fraction& rhs);
        friend bool operator!=(const Fraction& lhs, const Fraction& rhs);
        friend Fraction operator*(Fraction lhs, const Fraction& rhs);
    };
}


#endif // FRACTION

