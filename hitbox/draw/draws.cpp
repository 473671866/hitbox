#include "draws.h"

bool draws::initialize(services* service, mappers* mapper)
{
	this->serivce = service;
	this->mapper = mapper;
	return this->serivce != nullptr and mapper != nullptr ? true : false;
}

void draws::menus()
{
	static bool display_p1 = false;
	ImGui::Checkbox("p1", &display_p1); ImGui::SameLine();

	static bool display_p2 = false;
	ImGui::Checkbox("p2", &display_p2); ImGui::SameLine();

	static float alpha = 0.2f;
	ImGui::SetNextItemWidth(50);
	ImGui::InputFloat(u8"Í¸Ã÷¶È", &alpha, 0.0f, 0.0f, "%.2f");

	for (int i = 0; i < (sizeof(switches) / sizeof(switcher)); i++) {
		switcher* swch = &switches[i];
		control::label(swch->name, &swch->display, swch->title, &swch->control, &swch->color);
	}

	this->dp1 = display_p1;
	this->dp2 = display_p2;
	this->alpha = alpha;
	return;
}

bool draws::draw()
{
	auto objects = *mapper->objs;

	if (objects == nullptr)
		return false;

	if (objects->complete != 2)
		return false;

	if (objects->ready <= 2)
		return false;

	auto p1 = objects->p1;
	if (p1 == nullptr)
		return false;

	auto p2 = objects->p2;
	if (p2 == nullptr)
		return false;

	for (switcher& swch : switches) {
		if (!swch.display)
			continue;

		actions_entry entry = p1->acts->entry[p1->number];
		for (int i = 0; i < entry.capacity && entry.actcs != nullptr && IsBadReadPtr(&entry.actcs[i], sizeof(actions_entry)) == 0; i++) {
			action_collections actcs = entry.actcs[i];
			if (actcs.types != swch.action)
				continue;

			int index = (int)actcs.types - 3;
			if (index < 0 or index > 3)
				continue;

			if (dp1) {
				hitboxes::boxs* b = contexts[index].instance;
				b->alpha = alpha;
				b->service = serivce;
				b->box(p1, actcs, swch);
			}

			if (dp2) {
				hitboxes::boxs* b = contexts[index].instance;
				b->alpha = alpha;
				b->service = serivce;
				b->box(p2, actcs, swch);
			}
		}
	}

	for (switcher& swch : switches) {
		if (swch.types != attack_types::projectile)
			continue;

		if (!swch.display)
			continue;

		auto list = objects->props_list->list;
		for (; list != nullptr; list = list->next) {
			auto props = list->props;
			auto props_entry = props->acts->entry[props->number];
			for (int i = 0; i < props_entry.capacity; i++) {
				action_collections actcs = props_entry.actcs[i];
				if (actcs.types != swch.action)
					continue;

				int index = (int)actcs.types - 3;
				if (index < 0 or index > 3)
					continue;

				if (dp1) {
					hitboxes::boxs* b = contexts[index].instance;
					b->alpha = alpha;
					b->service = serivce;
					b->box((object*)props, actcs, swch);
				}

				if (dp2) {
					hitboxes::boxs* b = contexts[index].instance;
					b->alpha = alpha;
					b->service = serivce;
					b->box((object*)props, actcs, swch);
				}
			}
		}
	}

	return true;
}