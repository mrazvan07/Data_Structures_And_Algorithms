#pragma once

typedef int TElem;
class IteratorLI;
typedef bool(*Conditie)(TElem);
class LI {
private:
	friend class IteratorLI;

	TElem* elemente;
	int* urm;
	int prim = -1;
	int prim_liber = -1;
	int cp = 0;
	int n = 0;
	int ultim = -1;
	void resize();
	int aloca();
	void dealoca(int i);
	int creeaza_nod(TElem e);
	void resize_stergere();

public:
	// constructor implicit
	LI();

	// returnare dimensiune
	int dim() const;

	// verifica daca lista e vida
	bool vida() const;

	// afisare lista;
	void afisare();

	// returnare element
	//arunca exceptie daca i nu e valid
	TElem element(int i) const;

	// modifica element de pe pozitia i si returneaza vechea valoare
	//arunca exceptie daca i nu e valid
	TElem modifica(int i, TElem e);

	// adaugare element la sfarsit
	void adaugaSfarsit(TElem e);

	// adaugare element pe o pozitie i 
	//arunca exceptie daca i nu e valid
	void adauga(int i, TElem e);

	// sterge element de pe o pozitie i si returneaza elementul sters
	//arunca exceptie daca i nu e valid
	TElem sterge(int i);

	// cauta element si returneaza prima pozitie pe care apare (sau -1)
	int cauta(TElem e)  const;

	// returnare iterator
	IteratorLI iterator() const;

	void rearanjeaza(Conditie cond);

	//destructor
	~LI();

	//elimina toate elementele din lista.
	//void goleste();

};
