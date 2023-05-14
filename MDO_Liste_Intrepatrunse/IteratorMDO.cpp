#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d) {
	/* de adaugat */
	curent = 0;
}

void IteratorMDO::prim() {
	/* de adaugat */
	curent = 0;
	while (dict.e[curent].first == -1) {
		curent++;
	}
}

void IteratorMDO::urmator() {
	/* de adaugat */
	do {
		curent++;
	} while (dict.e[curent].first == -1 && curent < dict.m);
}

bool IteratorMDO::valid() const {
	/* de adaugat */
	return (curent < dict.m && dict.e[curent].first != -1);
}

TElem IteratorMDO::element() const {
	/* de adaugat */
	return dict.e[curent];
}


