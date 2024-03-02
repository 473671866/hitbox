#pragma once
#include "boxs.h"

struct context {
	action_types types;
	hitboxes::boxs* instance;
};

extern context contexts[3];
