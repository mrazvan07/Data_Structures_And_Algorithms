#include "TestScurt.h"
#include <assert.h>
#include "Matrice.h"
#include <iostream>

using namespace std;

void testAll() { //apelam fiecare functie sa vedem daca exista
	cout << "gsd";
	Matrice m(100, 100);
	//assert(m.nrLinii() == 4);
	//assert(m.nrColoane() == 4);
	assert(m.nrLinii() == 100);
	assert(m.nrColoane() == 100);
	for (int i = 0; i < m.nrLinii(); i++)
		for (int j = 0; j < m.nrColoane(); j++)
			assert(m.element(i, j) == NULL_TELEMENT);


	//adaug niste elemente
	m.modifica(1, 1, 5);
	m.modifica(1, 1, 6);
	m.modifica(2, 3, 4);
	m.modifica(2, 2, 1);
	m.modifica(3, 3, 1);
	m.modifica(3, 1, 1);
	cout << m.element(1, 1);
	assert(m.element(1, 1) == 6);
	cout << m.element(2, 3);
	assert(m.element(2, 3) == 4);
	assert(m.element(2, 2) == 1);
	assert(m.element(3, 3) == 1);
	assert(m.element(3, 1) == 1);

	m.modifica(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEMENT);

}
