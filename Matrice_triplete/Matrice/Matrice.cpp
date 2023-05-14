#include "Matrice.h"

#include <exception>

using namespace std;


void Matrice::redim() {

	TElem** newElements = new int* [2 * capacitate];
	for (int i = 0; i < numar_coloane; i++) {
		newElements[i] = new int[3];
	}
	for (int i = 0; i < numar_triplete; i++) {
		for (int j = 0; j < 3; j++) {
			newElements[i][j] = elements[i][j];
		}
	}
	for (int i = 0; i < capacitate; i++) {
		delete[] elements[i];
	}
	capacitate = 2 * capacitate;
	delete[] elements;
	elements = newElements;
}

Matrice::Matrice(int m, int n) {
	this->numar_linii = m;
	this->numar_coloane = n;
	this->numar_triplete = 0;
	this->capacitate = m;
	elements = new int* [this->numar_linii];
	for (int i = 0; i < this->numar_linii; i++) {
		elements[i] = new int[3];
	}
}



int Matrice::nrLinii() const {

	return this->numar_linii;
	//return 0;
}


int Matrice::nrColoane() const {
	/* de adaugat */
	return this->numar_coloane;
	//return 0;
}


TElem Matrice::element(int i, int j) const {
	if (i < 0 || j < 0 || i > this->numar_linii || j > this->numar_coloane) {
		throw exception();
	}
	if (this->numar_triplete == 0) {
		return NULL_TELEMENT;
	}

	if (i < this->elements[0][0] && j < this->elements[0][1]) {
		return NULL_TELEMENT;
	}
	if (i > this->elements[numar_triplete - 1][0] && j > this->elements[numar_triplete - 1][1]) {
		return NULL_TELEMENT;
	}

	//first occurence of the 'i' line number in the matrix
	int low = 0;
	int high = this->numar_triplete - 1;
	int low_index = -1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (this->elements[mid][0] > i) {
			high = mid - 1;
		}
		else if (this->elements[mid][0] < i) {
			low = mid + 1;
		}
		else {
			low_index = mid;
			high = mid - 1;
		}
	}


	if (low_index == -1 || elements[low_index][1] > j) {
		return NULL_TELEMENT;
	}

	//last occurence of the 'i' line number in the matrix
	int last_index = -1;
	low = 0;
	high = numar_triplete - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (this->elements[mid][0] > i) {
			high = mid - 1;
		}
		else if (this->elements[mid][0] < i) {
			low = mid + 1;
		}
		else {
			last_index = mid;
			low = mid + 1;
		}
	}

	if (last_index == -1 || elements[last_index][1] < j) {
		return NULL_TELEMENT;
	}

	if (low_index == last_index) {
		if (elements[low_index][1] == elements[last_index][1]) {
			return elements[last_index][2];
		}
		else {
			return NULL_TELEMENT;
		}
	}
	else {

		int right = last_index;
		int left = low_index;
		while (right >= left) {
			int mij = left + (right - left) / 2;
			if (j <= elements[mij][1]) {
				right = mij;
			}
			else {
				left = mij;
			}
		}
		//if (low_index == 0 && right == 1) { return elements[0][2]; }
		if (elements[right][1] == j) {
			return elements[right][2];
		}
		else {
			return NULL_TELEMENT;
		}
	}

	return -2;
}



TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i > this->numar_linii || j > this->numar_coloane) {
		throw exception();
	}

	int low = 0;
	int high = this->numar_triplete - 1;
	int low_index = -1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (this->elements[mid][0] > i) {
			high = mid - 1;
		}
		else if (this->elements[mid][0] < i) {
			low = mid + 1;
		}
		else {
			low_index = mid;
			high = mid - 1;
		}
	}
	//low
	if (low_index == -1) {
		if (capacitate == numar_triplete) {
			redim();
		}
		for (int index = numar_triplete - 1; index >= low; index--) {
			elements[index + 1][0] = elements[index][0];
			elements[index + 1][1] = elements[index][1];
			elements[index + 1][2] = elements[index][2];
		}
		elements[low][0] = i;
		elements[low][1] = j;
		elements[low][2] = e;
		numar_triplete++;
		return 0;
	}

	int last_index = -1;
	low = 0;
	high = numar_triplete - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (this->elements[mid][0] > i) {
			high = mid - 1;
		}
		else if (this->elements[mid][0] < i) {
			low = mid + 1;
		}
		else {
			last_index = mid;
			low = mid + 1;
		}
	}

	if (elements[low_index][1] > j) {
		if (capacitate == numar_triplete) {
			redim();
		}
		for (int index = numar_triplete - 1; index >= low_index; index--) {
			elements[index + 1][0] = elements[index][0];
			elements[index + 1][1] = elements[index][1];
			elements[index + 1][2] = elements[index][2];
		}
		elements[low_index][0] = i;
		elements[low_index][1] = j;
		elements[low_index][2] = e;
		numar_triplete++;
		return 0;
	}
	if (elements[last_index][1] > j) {
		if (capacitate == numar_triplete) {
			redim();
		}
		for (int index = numar_triplete - 1; index >= last_index + 1; index--) {
			elements[index + 1][0] = elements[index][0];
			elements[index + 1][1] = elements[index][1];
			elements[index + 1][2] = elements[index][2];
		}
		elements[last_index + 1][0] = i;
		elements[last_index + 1][1] = j;
		elements[last_index + 1][2] = e;
		numar_triplete++;
		return 0;
	}


	int right = last_index;
	int left = low_index;
	while (right >= left) {
		int mij = (right + left) / 2;
		if (j <= elements[mij][1]) {
			right = mij;
		}
		else {
			left = mij;
		}
	}
	//if (low_index == 0 && right == 1) { return elements[0][2]; }
	if (elements[right][1] == j) {
		elements[right][2] = e;
		return 0;
	}

	if (capacitate == numar_triplete) {
		redim();
	}
	for (int index = numar_triplete - 1; index >= right; index--) {
		elements[index + 1][0] = elements[index][0];
		elements[index + 1][1] = elements[index][1];
		elements[index + 1][2] = elements[index][2];
	}
	elements[right][0] = i;
	elements[right][1] = j;
	elements[right][2] = e;
	numar_triplete++;
	return 0;


	return -1;
}


