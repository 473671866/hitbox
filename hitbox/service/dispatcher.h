#ifndef DICPATCH_H
#define DICPATCH_H

#include "box.h"
#include "../mapper/mapper.h"
#include "../context/description.h"
#include "../context/configuration.h"

namespace hitboxes {
	struct context {
		action_types types;
		box* instance;
	};

	class dispatcher {
	public:
		bool dispatch();
	};
}

#endif // DICPATCH_H
