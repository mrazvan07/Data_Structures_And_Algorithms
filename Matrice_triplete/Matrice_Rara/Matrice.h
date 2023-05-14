#pragma once

typedef int TElem;


#define NULL_TELEMENT 0

class Matrice {

private:
	int numar_linii;
	int numar_coloane;
	int numar_elemente;
	int capacitate;
	TElem** matrice;

	//functie de redimensionare a matricii
	//complexitate: O(N)
	//pre: o matrice existenta
	//post: o matrice nou de capacitate dubla
	void redim();

	/*
	* functie care gaseste prima aparitie a unei linii sau locul unde ar trebui inserata tripleta corespunztoare liniei date in vectorul dinamic
	* worst case comlpexity: tetha(logN);
	* best case complexity: tetha(1);
	* pre: TElem** matrice- vector dinamic de triplete <linie,coloana,valoare>
			int linie: linia cautata
	* post: int index = indexul primei aparitii sau pozitia unde trebuie introdus
	*/
	int first_occurence(TElem** matrice, int linie) const;


	//functie care gaseste ultimao aparitie a unei linii sau locul unde ar trebui inserata tripleta corespunztoare liniei date in vectorul dinamic
	//worst case comlpexity: tetha(logN);
	//best case complexity: tetha(1);
	//pre: TElem** matrice- vector dinamic de triplete <linie,coloana,valoare>	
	//		int linie: linia cautata
	//post: int index = indexul ultimei aparitii sau pozitia unde trebuie introdus
	int last_occurence(TElem** matrice, int linie) const;

	//functie care gaseste prima aparitie a unei coloane sau locul unde trebuie inserata tripleta corespunzatoare in subsirul reprezentat de tripletele cu acelasi numar de linie
	//worst case comlpexity: tetha(logN);
	//best case complexity: tetha(1);
	//pre: TElem** matrice- vector dinamic de triplete <linie,coloana,valoare>	
	//		int left: indexul ce reprezinta limita inferioara de unde incepe cautarea
	//		int right : indexul ce reprezinta limita superioara de unde incepe cautarea
	//		TElem el: numarul coloanei
	//post: int index = indexul ultimei aparitii sau pozitia unde trebuie introdus
	int binary_search_columns(TElem** matrice, int left, int right, TElem el) const;

	//functie care insereaza o tripleta in vectorul dinamic
	//worst case comlpexity: tetha(logN);
	//best case complexity: tetha(1);
	//pre: TElem** matrice- vector dinamic de triplete <linie,coloana,valoare>	
	//		int left: indexul ce reprezinta limita inferioara de unde incpe cautarea
	//post: int index = indexul ultimei aparitii sau pozitia unde trebuie introdus
	void insert_element(TElem** matrice, int index, int linie, int coloana, TElem el);

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice() {};

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	//worst case comlpexity: tetha(logN);
	//best case complexity: tetha(1);
	//pre: matrice TElem** existent
	//		int i - numar de linie din tripleta
	//		int j - numar de coloana din tripleta
	//post: TElem e - valoarea corespunzatoare tripletei daca s-a gasit
	//		NULL_TELEMENT - in caz contrat
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	//worst case comlpexity: tetha(N);
	//best case complexity: tetha(1);
	//pre: matrice TElem** existent
	//		int i - numar de linie din tripleta
	//		int j - numar de coloana din tripleta
	//post: TElem e - valoarea veche corespunzatoare tripletei daca s-a gasit 
	//		daca nu s-a gasit o tripleta la fel, se va insera cea curenta
	TElem modifica(int i, int j, TElem);
};







