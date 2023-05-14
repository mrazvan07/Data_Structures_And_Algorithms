#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) :rel{r} {
	/* de adaugat */
	m = MAX;
	//initializam vectorii
	for (int i = 0; i < m; i++) {
		e[i].first = -1;
		e[i].second = -1;
		urm[i] = -1;
	}
	//initializare primLiber
	primLiber = 0;
}

void MDO::actPrimLiber() {
	primLiber++;
	while (primLiber < m && e[primLiber].first != -1)
		primLiber++;

}

void MDO::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	int rez;
	TElem elem{ c,v };
	//locatia de dispersie a cheii
	int i = d(c);
	if (e[i].first == -1)	// pozitia este libera
	{
		e[i] = elem;	// adaugam elementul
		if (i == primLiber)
			actPrimLiber();	// actualizam primLiber, daca este nevoie
		return;
	}

	int j = -1;	// j va retine pozitia precedenta lui i, pentru a putea reface inlantuirea
	// daca pozitia nu este libera
	while (i != -1)	// iteram pana gasim capatul inlantuirii
	{
		j = i;
		i = urm[i];
	}

	if (primLiber >= m)
		throw std::exception{ "Nu mai exista spatiu pentru adaugarea elementului!" }; //nu tratam depasirea tabelei

	// adaugam elementul
	e[primLiber] = elem;
	urm[j] = primLiber;
	actPrimLiber();

}

vector<TValoare> MDO::cauta(TCheie c) const {
	/* de adaugat */
	vector<TValoare> rez;
	int aux;
	aux = this->d(c);
	while (aux != -1 && (this->e[aux].first != c)) {
		aux = this->urm[aux];
	}
	while (aux!=-1 && e[aux].first == c) {
		rez.push_back(e[aux].second);
		aux = this->urm[aux];
	}

	return rez;
}

bool MDO::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	int i = this->d(c);
	int j = -1;
	while (i != -1 && (this->e[i].first != c || this->e[i].second != v)) {
		j = i;
		i = this->urm[i];
	}
	if (i == -1) {
		return false;
	}
	else {
		bool gata = false;
		int prec;
		int p;
		do {
			prec = i;
			p = this->urm[i];
			while (p != -1 && this->d(this->e[p].first) != i) {
				prec = p;
				p = this->urm[p];
			}
			if (p == -1)
				gata = true;
			else {
				this->e[i].first = this->e[p].first;
				this->e[i].second = this->e[p].second;
				j = prec;
				i = p;
			}
		} while (gata != true);
		if (j != -1) {
			this->urm[j] = this->urm[i];
		}
		this->e[i].first = -1;
		this->e[i].second = -1;
		this->urm[i] = -1;
		if (i < this->primLiber)
			this->primLiber = i;
		return true;
	}
}

int MDO::dim() const {
	/* de adaugat */
	int nr = 0;
	for (int i = 0; i < m; i++) {
		if (this->e[i].first != -1)
			nr++;
	}
	return nr;
}

bool MDO::vid() const {
	/* de adaugat */
	return dim()==0;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	/* de adaugat */
	
}
