#pragma once
#include "boxs.h"

struct context {
	action_types types;
	hitboxs::boxs* instance;
};

extern context contexts[3];
