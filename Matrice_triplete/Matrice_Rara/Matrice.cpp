#include "Matrice.h"
#include <exception>
#include <cstdlib>
using namespace std;



void Matrice::insert_element(TElem** matrice, int index, int linie, int coloana, TElem el) {
	for (int i = this->numar_elemente; i > index; i--) {
		matrice[i][0] = matrice[i - 1][0];
		matrice[i][1] = matrice[i - 1][1];
		matrice[i][2] = matrice[i - 1][2];
	}
	matrice[index][0] = linie;
	matrice[index][1] = coloana;
	matrice[index][2] = el;

	this->numar_elemente += 1;
}


int Matrice::first_occurence(TElem** matrice, int numar_linie) const {
	int low = 0;
	int high = this->numar_elemente - 1;
	int index = -1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (matrice[mid][0] > numar_linie) {
			high = mid - 1;
		}
		else if (matrice[mid][0] < numar_linie) {
			low = mid + 1;
		}
		else {
			index = mid;
			high = mid - 1;
		}
	}
	if (index != -1) {
		return index;
	}
	else {
		return low;
	}
}

int Matrice::last_occurence(TElem** matrice, int numar_linie) const {
	int low = 0;
	int high = this->numar_elemente - 1;
	int index = -1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (matrice[mid][0] > numar_linie) {
			high = mid - 1;
		}
		else if (matrice[mid][0] < numar_linie) {
			low = mid + 1;
		}
		else {
			index = mid;
			low = mid + 1;
		}
	}
	if (index != -1) {
		return index;
	}
	else {
		return low;
	}
}

int Matrice::binary_search_columns(TElem** matrice, int left, int right, TElem el) const {
	if (this->numar_elemente == 0) {
		return 0;
	}
	if (el <= matrice[left][1]) {
		return left;
	}
	if (el > matrice[right - 1][1]) {
		return right;
	}
	while (right - left > 1) {
		int mid = (left + right) / 2;
		if (el <= matrice[mid][1]) {
			right = mid;
		}
		else {
			left = mid;
		}
	}
	return right;
}


void Matrice::redim() {
	TElem** matrice_noua = new TElem * [2 * capacitate];
	for (int i = 0; i < 2 * capacitate; i++) {
		matrice_noua[i] = new TElem[3];
	}
	for (int i = 0; i < numar_elemente; i++) {
		matrice_noua[i][0] = matrice[i][0];
		matrice_noua[i][1] = matrice[i][1];
		matrice_noua[i][2] = matrice[i][2];
	}
	for (int i = 0; i < capacitate; i++) {
		delete[] matrice[i];
	}
	delete[] matrice;
	capacitate = 2 * capacitate;
	this->matrice = matrice_noua;
}


Matrice::Matrice(int m, int n) {
	if (m <= 0 || n <= 0) {
		throw exception();
	}
	this->numar_linii = m;
	this->numar_coloane = n;
	this->numar_elemente = 0;
	this->capacitate = m;
	this->matrice = new TElem * [capacitate];
	for (int i = 0; i < capacitate; i++) {
		this->matrice[i] = new TElem[3];
	}
}



int Matrice::nrLinii() const {
	return numar_linii;
}


int Matrice::nrColoane() const {
	return numar_coloane;
}


TElem Matrice::element(int i, int j) const {
	if (i < 0 || j < 0 || i >= numar_linii || j >= numar_coloane) {
		throw exception();
	}
	int left = Matrice::first_occurence(matrice, i);
	if (left >= numar_elemente) {
		return NULL_TELEMENT;
	}
	if (matrice[left][0] != i) {
		return NULL_TELEMENT;
	}
	int right = Matrice::last_occurence(matrice, i);
	int index = Matrice::binary_search_columns(matrice, left, right + 1, j);
	if (matrice[index][1] == j) {
		return matrice[index][2];
	}
	else {
		return NULL_TELEMENT;
	}
}



TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= numar_linii || j >= numar_coloane) {
		throw exception();
	}
	int left = Matrice::first_occurence(matrice, i);
	if (left >= numar_elemente || matrice[left][0] != i) {
		if (this->capacitate == this->numar_elemente) {
			Matrice::redim();
		}
		Matrice::insert_element(matrice, left, i, j, e);
		return 0;
	}
	int right = Matrice::last_occurence(matrice, i);
	int index = Matrice::binary_search_columns(matrice, left, right + 1, j);
	if (index >= numar_elemente || matrice[index][1] != j) {
		if (this->capacitate == this->numar_elemente) {
			Matrice::redim();
		}
		Matrice::insert_element(matrice, index, i, j, e);
		return 0;
	}
	else if (matrice[index][1] == j) {
		TElem val_veche = matrice[index][2];
		matrice[index][2] = e;
		return val_veche;
	}
}


