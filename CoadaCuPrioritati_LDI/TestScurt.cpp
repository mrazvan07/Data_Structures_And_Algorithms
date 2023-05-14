#include "CP.h"
#include "TestScurt.h"
#include <assert.h>

bool rel(TPrioritate p1, TPrioritate p2) {
	if (p1 <= p2) {
		return true;
	}
	else {
		return false;
	}
}




void testAll() { //apelam fiecare functie sa vedem daca exista
	CP c(rel);

	assert(c.vida() == true);

	//adaugam 5, 3, 10, 2, 12 -> rezultat: 2, 3, 5, 10, 12
	c.adauga(5, 5);
	assert(c.element().first == 5);
	assert(c.element().second == 5);
	c.adauga(3, 3);
	assert(c.element().first == 3);
	assert(c.element().second == 3);
	c.adauga(10, 10);
	assert(c.element().first == 3);
	assert(c.element().second == 3);
	c.adauga(2, 2);
	assert(c.element().first == 2);
	assert(c.element().second == 2);
	c.adauga(12, 12);
	assert(c.element().first == 2);
	assert(c.element().second == 2);
	assert(c.vida() == false);
	assert(c.sterge().second == 2);
	assert(c.element().second == 3);
	assert(c.sterge().second == 3);
	assert(c.element().second == 5);
	assert(c.sterge().second == 5);
	assert(c.element().second == 10);
	assert(c.sterge().second == 10);
	assert(c.element().second == 12);
	assert(c.sterge().second == 12);
	assert(c.vida() == true);

	//testarea functionalitatii noi
	c.adauga(5, 1);
	c.adauga(6, 2);
	c.adauga(7, 3);
	c.adauga(23, 5);
	c.adauga(86, 7);
	c.adauga(510, 10);
	c.adauga(100, 11);
	c.adauga(100, 12);
	c.adauga(100, 13);
	c.adauga(-5, 90);
	c.adauga(-10, 91);
	c.adauga(80, 17);
	int prioritate = c.prioritateaElementului(23);
	assert(prioritate == 5);
	prioritate = c.prioritateaElementului(7);
	assert(prioritate == 3);
	prioritate = c.prioritateaElementului(86);
	assert(prioritate == 7);
	//elementul e in spate
	prioritate = c.prioritateaElementului(-10);
	assert(prioritate == 91);
	//elementul e in fata
	prioritate = c.prioritateaElementului(5);
	assert(prioritate == 1);

	//aparitia de mai multe ori a unui element, va gasi prioritatea cea mai mica;
	prioritate = c.prioritateaElementului(100);

	assert(prioritate == 13);

	//element inexistent
	prioritate = c.prioritateaElementului(200);
	assert(prioritate == -1);
}



