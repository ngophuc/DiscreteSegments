#include <iostream>
#include "fraction.h"

std::ostream& DGtal::operator<<(std::ostream& out, const Fraction& f){
   return out << f.num() << "/" << f.den() ;
}

bool DGtal::operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num() == rhs.num() && lhs.den() == rhs.den();
}
bool DGtal::operator!=(const Fraction& lhs, const Fraction& rhs) {
    //return !(lhs == rhs);
    return lhs.num() != rhs.num() || lhs.den() != rhs.den();
}
Fraction DGtal::operator*(Fraction lhs, const Fraction& rhs)
{
    return lhs *= rhs;
}
