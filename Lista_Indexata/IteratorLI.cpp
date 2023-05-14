#include "IteratorLI.h"
#include "LI.h"
#include <exception>

//Complexitate: Th(1).
IteratorLI::IteratorLI(const LI& li) : lista(li) {
    curent = li.prim;
}

//Complexitate: Th(1).
void IteratorLI::prim() {
    curent = lista.prim;
}

//Complexitate: Th(1).
void IteratorLI::urmator() {
    if (curent == -1)
        throw std::exception();
    curent = lista.urm[curent];
}

//Complexitate: Th(1).
bool IteratorLI::valid() const {
    return curent != -1;
}

//Complexitate: Th(1).
TElem IteratorLI::element() const {
    if (curent == -1)
        throw std::exception();
    return lista.elemente[curent];
}
