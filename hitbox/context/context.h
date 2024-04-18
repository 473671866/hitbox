#ifndef CONTEXT_H
#define CONTEXT_H

#include "../service/box.h"

struct context {
	action_types types;
	hitboxes::box* instance;
};

extern context contexts[3];

#endif	//CONTEXT_H
