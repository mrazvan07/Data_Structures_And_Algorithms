#pragma once
#include <vector>
#include <utility>

using namespace std;

typedef int TElem;
typedef int TPrioritate;

typedef std::pair<TElem, TPrioritate> Element;

typedef bool (*Relatie)(TPrioritate p1, TPrioritate p2);

class Nod;
typedef Nod* PNod;

class Nod {
public:
	friend class CP;

	//constructor
	Nod(TElem e, TPrioritate p, PNod urm, PNod prec);

	//functie de accesare a nodului
	Element element();

	//functie care returneaza adresa urmatorului nod de la nodul curent
	PNod urmator();

	//functie care returneaza adresa  nodului precedent de la nodul curent
	PNod precedent();

	//functie care returneaza prioritatea nodului curent
	TPrioritate prioritate();

private:
	TElem e;
	TPrioritate p;
	PNod urm, prec;
};



class CP {
private:
	friend class Nod;
	PNod fata, spate;
	Relatie rel;

public:
	//constructorul implicit
	CP(Relatie r);

	//functie ce insereaza un element in CP, in functie de prioritate
	//worst case comlpexity: tetha(N);
	//best case complexity: tetha(1);
	//pre: CP c - o coada existenta
	//		TElem e - valoarea perechii de tip Element
	//		TPrioritate - prioritatea perechii de tip Element
	//post: noua pereche adaugata in coada
	void adauga(TElem e, TPrioritate p);

	//acceseaza elementul cel mai prioritar in raport cu relatia de ordine
	//arunca exceptie daca CP e vida
	//pre: CP c - o coada existenta
	//post: Element e - fata cozii 
	//complexitate: tetha(1) - mereu se acceseaza fata cozii
	Element element()  const;

	//sterge elementul cel mai prioritar si il returneaza
	//arunca exceptie daca CP e vida
	//pre: CP c - o coada existenta, nevida
	//post: coada fara elementul ce a reprezentat fata;
	//complexitate: tetha(1) - mereu se acceseaza fata cozii
	Element sterge();

	//verifica daca CP e vida;
	bool vida() const;

	// returnează prioritatea elementului elem. În cazul în care elem apare de mai multe ori, se va returna prioritatea uneia dintre apariții
	//daca elem nu este în coadă, se returnează -1
	//best case complexity: tetha(1) - cand elementul este fata sau spatele
	//worst case complexity: tetha(N) - cand elementul nu este fata sau spatele si trebuie cautat in coada
	//average case complexity: O(N)
	TPrioritate prioritateaElementului(TElem elem) const;


	// destructorul cozii
	~CP();

};
