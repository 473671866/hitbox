#ifndef OVERVIEW_H
#define OVERVIEW_H

#include "../entity/objects.h"

class overview {
public:
	int startup(object* obj);
	int active(object* obj);
	int recovery(object* obj);
};

#endif // OVERVIEW_H
