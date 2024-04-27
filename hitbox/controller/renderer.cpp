#include "renderer.h"

bool renderer::render() {
	hitboxes::dispatcher dispatch;
	dispatch.dispatch();
	return true;
}