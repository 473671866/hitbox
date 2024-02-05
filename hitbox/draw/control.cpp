#include "control.h"

bool control::label(const char* checkbox, bool* box, const char* selector, bool* open, ImColor* color)
{
	ImGui::Checkbox(checkbox, box);
	ImGui::SameLine();

	if (ImGui::Button(selector)) {
		*open = !(*open);
	}

	if (*open) {
		ImGui::Begin("color", open);
		ImGui::ColorPicker3("color selector", (float*)color);
		ImGui::End();
	}
	return true;
}