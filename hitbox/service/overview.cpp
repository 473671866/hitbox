#include "overview.h"

int overview::startup(object* obj) {
	actions_entry entry = obj->acts->entry[obj->number];
	for (int i = 0; i < entry.capacity; i++) {
		action_collections actcs = entry.actcs[i];
		if (actcs.types != action_types::attack)
			continue;

		for (unsigned int j = 0; j < actcs.capacity; j++) {
			auto box = actcs.attack[j];
			if (obj->atcs->atccs[box.number].types != attack_types::normal)
				continue;

			return actcs.attack[0].frame;
		}
	}
	return -1;
}

int overview::active(object* obj) {
	actions_entry entry = obj->acts->entry[obj->number];
	for (int i = 0; i < entry.capacity; i++) {
		action_collections actcs = entry.actcs[i];
		if (actcs.types != action_types::attack)
			continue;

		for (unsigned int j = 0; j < actcs.capacity; j++) {
			auto box = actcs.attack[j];
			if (obj->atcs->atccs[box.number].types != attack_types::normal)
				continue;

			if (obj->now != actcs.attack[actcs.capacity - 1].frame)
				continue;

			return entry.max - actcs.attack[actcs.capacity - 1].frame;
		}
	}
	return -1;
}

int overview::recovery(object* obj) {
	actions_entry entry = obj->acts->entry[obj->number];
	for (int i = 0; i < entry.capacity; i++) {
		action_collections actcs = entry.actcs[i];
		if (actcs.types == action_types::attack) {
			return actcs.capacity;
		}
	}
	return -1;
}