#include <exception>
#include <iostream>
#include "LI.h"
#include "IteratorLI.h"
#include <queue>

//Notam Theta cu Th.
//Complexitate: Th(1).
int LI::aloca() {
	int i = prim_liber;
	prim_liber = urm[prim_liber];
	return i;
}

//Complexitate: Th(1).
void LI::dealoca(int i) {
	urm[i] = prim_liber;
	prim_liber = i;
}

//Complexitate: Th(n).
void LI::resize() {
	TElem* new_vector = new TElem[cp * 2];
	int* new_urm = new int[cp * 2];
	for (int i = 0; i < cp; i++) {
		new_vector[i] = elemente[i];
		new_urm[i] = urm[i];
	}
	delete[] elemente;
	elemente = new_vector;
	delete[] urm;
	urm = new_urm;
	prim_liber = cp;
	for (int i = cp; i < cp * 2 - 1; i++)
		urm[i] = i + 1;
	urm[cp * 2 - 1] = -1;
	cp *= 2;
}

void LI::resize_stergere() {
	TElem* enou = new TElem[cp / 2];
	int* urmnou = new int[cp / 2];
	int nr = 0;
	//mutam din vectorii noi in cei vechi
	int nod = prim;
	for (int i = 0; i < cp / 2; i++) {
		urmnou[i] = i + 1;
	}
	urmnou[cp / 2 - 1] = -1;
	while (nod != -1) {
		enou[nr++] = elemente[nod];
		nod = urm[nod];
	}
	//refacem vectorii
	delete[] elemente;
	elemente = enou;
	delete[] urm;
	urm = urmnou;

	//initializam noul spatiu liber
	prim = 0;
	prim_liber = -1;
	cp /= 2;
}

//Complexitate: Th(n).
void LI::afisare() {
	int poz = prim;
	std::cout << "Lista elementelor:\n";
	while (poz != -1) {
		std::cout << elemente[poz] << " ";
		poz = urm[poz];
	}
	std::cout << std::endl;
}

//Complexitate: O(n).
//Caz favorabil, nu trebuie redimensionare a vectorului.
//Caz defavorabil, trebuie.
int LI::creeaza_nod(TElem e) {
	if (prim_liber == -1)
		resize();
	int i = aloca();
	this->elemente[i] = e;
	urm[i] = -1;
	return i;
}

//Complexitate: O(n) sau mai mare, depinde de complexitatea tipul TElementului, dar cum aici vorbim despre int-uri este O(n).
LI::LI() {
	cp = 10;
	elemente = new TElem[cp];
	urm = new int[cp];
	n = 0;
	prim = -1;
	prim_liber = 0;
	for (int i = 0; i < cp - 1; i++)
		urm[i] = i + 1;
	urm[cp - 1] = -1;
}

//Complexitate: Th(1).
int LI::dim() const {
	return n;
}

//Complexitate: Th(1).
bool LI::vida() const {
	return n == 0;
}

//Complexitate: O(n).
//Caz favorabil: O(1), indexul nu este unul din lista.
//Caz defavorabil: O(n), indexul este ultimul din lista.
TElem LI::element(int i) const {
	if (i >= n || i < 0)
		throw std::exception();
	int poz = prim, gasit = elemente[poz];
	while (i--)
		poz = urm[poz];
	return elemente[poz];
}

//Complexitate: O(n). 
//Caz favorabil: Elementul pe care vrem sa-l modificam nu este in lista.
//Caz defavorabil: Elementul pe care vrem sa-l modificam este la finalul listei.
TElem LI::modifica(int i, TElem e) {
	if (i >= n || i < 0)
		throw std::exception();
	int poz = prim;
	while (i-- > 0)
		poz = urm[poz];
	TElem temp = elemente[poz];
	elemente[poz] = e;
	return temp;
}

//Complexitate: O(1) amortizat.
void LI::adaugaSfarsit(TElem e) {
	int i = creeaza_nod(e);
	if (n == 0) {
		ultim = prim = i;
		n++;
		return;
	}
	urm[ultim] = i;
	ultim = i;
	n++;
}

//Complexitate: O(n).
//Caz favorabil, i nu este un indice valid pentru adaugarea elementului.
//Caz defavorabil: se adauga elementul pe penultima pozitie din lista.
void LI::adauga(int i, TElem e) {
	if (i > n)
		throw std::exception();
	if (i == n) {
		adaugaSfarsit(e);
		return;
	}
	int new_elem = creeaza_nod(e);
	if (i == 0) {
		urm[new_elem] = prim;
		prim = new_elem;
		n++;
		return;
	}
	int poz = prim, ant = prim;
	while (i--) {
		ant = poz;
		poz = urm[poz];
	}
	urm[ant] = new_elem;
	urm[new_elem] = poz;
	n++;
}
//Complexitate: O(n).
//Caz favorabil: Incercarea stergerii unui element care nu exista sau a primului element.
//Caz defavorabil: Stergera ultimului element. 
//resize la stergere cum ii place dnei dindelegan, nu e musai
TElem LI::sterge(int i) {
	if (dim() == cp / 2 && dim() > 1)
		resize_stergere();
	if (i >= n)
		throw std::exception();
	int poz = prim;
	if (0 == i) {
		TElem temp = elemente[poz];
		prim = urm[poz];
		dealoca(poz);
		n--;
		return temp;
	}
	int ant = prim;
	TElem temp = elemente[poz];
	while (i--) {
		ant = poz;
		poz = urm[poz];
		temp = elemente[poz];
	}
	if (urm[poz] == -1)
		ultim = ant;
	urm[ant] = urm[poz];
	dealoca(poz);
	n--;
	return temp;
}

//Complexitate: O(n).
//Caz favorabil: Elementul este pe prima pozitie din lista.
//Caz defavorabil: Elementul nu se afla in lista.
int LI::cauta(TElem e) const {
	int i = 0;
	for (int poz = prim; poz != -1; poz = urm[poz]) {
		if (elemente[poz] == e)
			return i;
		i++;
	}
	return -1;
}

//Complexitate: Th(1).
IteratorLI LI::iterator() const {
	return  IteratorLI(*this);
}
//Complexitate: nu exista caz favorabil sau defavorabil, complexitatea depinde de dimensiunea datelor de intrare
//==>caz favorabil=caz defavorabil=caz mediu=Theta(2*n)~=Theta(n), unde n este dimensiunea listei
//parcurg prima data toate elementele din lista pentru a le pune in cele doua cozi-->n pasi
//ok[] va contine atatea elemente cate respecta conditia, iar not_ok[] le va contine pe restul, n- dim(ok), deci impreuna dim(ok)+dim(not_ok)=n
//cum mai parcurg o data atat ok, cat si not_ok, se vor mai face inca n pasi, deci rezulta in final 2*n pasi, deci complexitatea finala este liniara,
//Theta(n)

/*pseudocod
* subalgoritm rearanjeaza(lista LI, cond Conditie)
//preconditii :lista - de clasa LI
						cond-de tip Conditie
						caz favorabil, se fac 2*n pasi==>complexitate liniara Theta(n)
						caz defavorabil, se fac 2*n pasi==>complexitate liniara Theta(n)
//postconditii:lista' - de tip LI, va fi o lista cu aceleasi elemente ca si li, dar rearanjate
subalgortim rearanjeaza(cond)
	queue<TElem> ok
	queue<TElem> not_ok
	temp<-prim
	cat timp temp!=-1 executa
		daca cond(elemente[temp]) ==false atunci
			not_ok.push(elemente[temp])
		altfel ok.push(elemente[temp])
		sfarsit daca
		temp<-urm[temp]
	sfarsit cat timp
	
	temp<-prim
	cat timp ok.empty()==false executa
		elemente[temp]<-ok.front()
		ok.pop()
		temp<-urm[temp]
	sfarsit cattimp

	cat timp not_ok.empty() == false executa
		elemente[temp]<-not_ok.front()
		not_ok.pop()
		temp<-urm[temp]
	sfarsit cat timp
sfarsit subalgoritm
*/
void LI::rearanjeaza(Conditie cond) {
	std::queue<TElem> ok;
	std::queue<TElem> not_ok;
	int temp = prim;
	while (temp != -1) {
		if (cond(elemente[temp]) == false) {
			not_ok.push(elemente[temp]);
		}
		else {
			ok.push(elemente[temp]);

		}
		temp = urm[temp];
	}
	temp = prim;
	while (ok.empty() == false) {
		elemente[temp] = ok.front();
		ok.pop();
		temp = urm[temp];
	}
	while (not_ok.empty() == false) {
		elemente[temp] = not_ok.front();
		not_ok.pop();
		temp = urm[temp];
	}
}

//Complexitate: O(n) sau O(1), depinde de TElem, pentru ca acum vorbim de INT-uri am putea spune ca este O(1).
LI::~LI() {
	delete[] elemente;
	delete[] urm;
}

//Complexitate: Th(cp).
//Nu exista caz favorabil sau defavorabil pentru aceasta functie depinzand doar de lungimea listei.
/*
Pre: lista (lista de pozitii ale elementelor), cp - capacitatea listei, prim (indexul primului element) si ultim (indexul ulrimului element).
Post: lista' - lista pozitilor in noua ordine;
	  primul_liber - arata catre inceputul listei.
	  prim, ulrim sunt acum initializati cu -1.

subalgoritm goleste(lista, cp):
	pentru i <-0, cp:
		urm[i] <- i + 1
	urm[cp - 1] <- -1
	n <- 0
	prim <- -1.
	ultim <- 0.
	prim_liber <- 0
*/
/*
void LI::goleste()
{
	for (int i = 0; i < cp - 1; i++)
		urm[i] = i + 1;
	urm[cp - 1] = -1;
	n = 0;
	prim = ultim = -1;
	prim_liber = 0;
}
*/