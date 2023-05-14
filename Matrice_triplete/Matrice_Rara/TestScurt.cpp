#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	Matrice m(4, 4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);
	//adaug niste elemente
	m.modifica(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modifica(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEMENT);

}

void test2() {

	Matrice m(10, 10);
	int val = 1;
	for (int i = 0; i < m.nrLinii(); i++) {
		for (int j = 0; j < m.nrColoane(); j++) {
			m.modifica(i, j, val);
		}
		val++;
	}

	for (int k = 0; k < m.nrLinii(); k++) {
		assert(m.element(0, k) == 1);
		assert(m.element(1, k) == 2);
		assert(m.element(2, k) == 3);
		assert(m.element(3, k) == 4);
		assert(m.element(4, k) == 5);
		assert(m.element(5, k) == 6);

	}



}
