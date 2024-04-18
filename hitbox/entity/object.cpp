#include "object.h"

warpper::warpper() {}

warpper::warpper(attack_types types) :attack(types) {
	affected = affected_types::none;
	body = body_types::none;
};

warpper::warpper(affected_types types) :affected(types) {
	attack = attack_types::none;
	body = body_types::none;
};

warpper::warpper(body_types types) :body(types) {
	attack = attack_types::none;
	affected = affected_types::none;
};

bool warpper::operator== (warpper b) {
	if (attack == b.attack)
		return true;
	else if (affected == b.affected)
		return true;
	else if (body == b.body)
		return true;
	else
		return false;
}

bool warpper::operator!= (warpper b) {
	if (attack != b.attack)
		return true;
	else if (affected != b.affected)
		return true;
	else if (body != b.body)
		return true;
	else
		return false;
}

range::range() {}

range::range(object* obj, attack_boxs box, bool l) {
	if (l) {
		this->left = obj->x * 10 + box.x * 10 + obj->xoff * 10;
		this->top = obj->y * 10 + box.y * 10 + obj->yoff * 10;
		this->right = left + box.w * 10;
		this->bottom = top - box.h * 10;
	}
	else {
		this->left = obj->x * 10 - box.x * 10 + obj->xoff * 10;
		this->top = obj->y * 10 + box.y * 10 + obj->yoff * 10;
		this->right = left - box.w * 10;
		this->bottom = top - box.h * 10;
	}
}

range::range(object* obj, body_boxs box, bool l) {
	if (l) {
		this->left = obj->x * 10 + box.x * 10 + obj->xoff * 10;
		this->top = obj->y * 10 + box.y * 10 + obj->yoff * 10;
		this->right = left + box.w * 10;
		this->bottom = top - box.h * 10;
	}
	else {
		this->left = obj->x * 10 - box.x * 10 + obj->xoff * 10;
		this->top = obj->y * 10 + box.y * 10 + obj->yoff * 10;
		this->right = left - box.w * 10;
		this->bottom = top - box.h * 10;
	}
}

range::range(object* obj, affected_boxs box, bool l) {
	if (box.path >= 0) {
		if (l) {
			this->left = obj->x * 10 + box.x * 10 + obj->xoff * 10;
			this->top = obj->y * 10 + box.y * 10 + obj->yoff * 10;
			this->right = left + box.w * 10;
			this->bottom = top - box.h * 10;
		}
		else {
			this->left = obj->x * 10 - box.x * 10 + obj->xoff * 10;
			this->top = obj->y * 10 + box.y * 10 + obj->yoff * 10;
			this->right = left - box.w * 10;
			this->bottom = top - box.h * 10;
		}
	}
	else {
		if (l) {
			this->left = obj->x * 10 + box.x * 10;
			this->top = obj->y * 10 + box.y * 10;
			this->right = left + box.w * 10;
			this->bottom = top - box.h * 10;
		}
		else {
			this->left = obj->x * 10 - box.x * 10;
			this->top = obj->y * 10 + box.y * 10;
			this->right = left - box.w * 10;
			this->bottom = top - box.h * 10;
		}
	}
}