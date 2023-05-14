
#include "CP.h"
#include <exception>
#include <stdio.h>

using namespace std;


Nod::Nod(TElem e, TPrioritate p, PNod urm, PNod prec) {
	this->p = p;
	this->e = e;
	this->urm = urm;
	this->prec = prec;
}

Element Nod::element() {
	return pair <TElem, TPrioritate>(e, p);
}

PNod Nod::urmator() {
	return urm;
}

PNod Nod::precedent() {
	return prec;
}

TPrioritate Nod::prioritate() {
	return p;
}


CP::CP(Relatie r) {
	rel = r;
	this->fata = nullptr;
	this->spate = nullptr;
}


void CP::adauga(TElem e, TPrioritate p) {
	PNod nou = new Nod(e, p, nullptr, nullptr);
	//daca coada este vida se adauga primul element
	if (CP::vida()) {
		fata = nou;
		spate = nou;
	}
	else {
		//daca e este cu prioritate mai mica decat elementul din  spate, acesta devine spatele
		if (rel(spate->prioritate(), p)) {
			nou->prec = spate;
			spate->urm = nou;
			spate = nou;

		}
		//daca e cu prioritate mai mare decat fata, acesta devine fata
		else if (rel(p, fata->prioritate())) {
			nou->urm = fata;
			fata->prec = nou;
			fata = nou;

		}
		//trebuie inserat intre doua noduri din coada: plecam din spate pana gasim nodul q al carui nod precedent e mai prioritar decat
		//elementul nostru si atunci il vom insera intre q->precedent si q.
		else {
			PNod q = spate;
			while (q->prec != nullptr && rel(p, q->prec->prioritate())) {
				q = q->prec;
			}
			nou->urm = q;
			q->prec->urm = nou;
			nou->prec = q->prec;
			q->prec = nou;
		}
	}
}

//arunca exceptie daca coada e vida
Element CP::element() const {
	if (CP::vida()) {
		throw exception();
	}
	return pair <TElem, TPrioritate>(fata->e, fata->prioritate());
}

Element CP::sterge() {
	if (CP::vida()) {
		throw exception();
	}

	TElem e = fata->e;
	TPrioritate prioritate = fata->p;


	PNod ptr = fata;
	fata = fata->urm;
	//cazul in care coada contine un singur element
	if (fata == nullptr) {
		spate == nullptr;
		delete ptr;
		return pair <TElem, TPrioritate>(e, prioritate);
	}
	fata->prec = nullptr;
	delete ptr;
	return pair <TElem, TPrioritate>(e, prioritate);
}


bool CP::vida() const {
	if (fata == nullptr || spate == nullptr) {
		return true;
	}
	return false;
}

TPrioritate CP::prioritateaElementului(TElem elem) const {

	//verificam daca elementul este fata
	if (fata->e == elem) {
		return fata->p;
	}

	//verificam daca elementul este spatele
	if (spate->e == elem) {
		return spate->p;
	}

	//cautam elementul incepand din spatele cozii,  in cazul in care nu e nici elementul din fata, nici elementul din spate
	PNod q = spate;
	while (q->prec != nullptr) {
		q = q->prec;
		if (q->e == elem) {
			return q->p;
		}
	}

	//daca nu am gasit elementul, returneaza -1;
	return -1;
}

CP::~CP() {
	while (fata != nullptr) {
		PNod p = fata;
		fata = fata->urm;
		delete p;
	}
}

