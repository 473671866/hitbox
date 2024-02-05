#include "context.h"

using namespace hitboxs;
context contexts[] = {
	{action_types::body,new body},
	{action_types::affected,new affected},
	{action_types::attack,new attack},
};