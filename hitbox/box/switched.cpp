#include "switched.h"

switcher switches[] = {
	{u8"普通攻击框",		u8"普通攻击框颜色",		{ 200, 100, 100 },	action_types::attack,	attack_types::normal,		false,	false},
	{u8"投技框",			u8"投技框颜色",			{ 127, 191, 191 },	action_types::attack,	attack_types::grasp,		false,	false},
	{u8"飞行道具攻击框",	u8"飞行道具攻击框颜色",	{ 127, 255, 127 },	action_types::attack,	attack_types::projectile,	false,	false},
	{u8"引发防御框",		u8"引发防御框颜色",		{ 127, 255, 127 },	action_types::attack,	attack_types::guard,		false,	false},
	{u8"身位框",			u8"身位框颜色",			{ 255, 165, 0  },	action_types::body,		body_types::none,			false,	false},
	{u8"受击框",			u8"受击框颜色",			{ 255, 255, 0 },	action_types::affected, affected_types::normal,		false,	false},
	{u8"被投框",			u8"被投框颜色",			{ 127, 255, 255 },	action_types::affected, affected_types::capture,	false,	false},
	{u8"防御框",			u8"防御框颜色",			{ 0, 255, 0 },		action_types::affected, affected_types::guard,		false,	false},
	{u8"追加框",			u8"追加框颜色",			{ 0, 255, 0 },		action_types::affected, affected_types::ground,		false,	false},
	{u8"抵消飞行道具框",	u8"抵消飞行道具框颜色", { 128, 128, 255 },	action_types::affected, affected_types::negative,	false,	false},
	{u8"反弹飞行道具框",	u8"反弹飞行道具框颜色", { 255, 127, 255 },	action_types::affected, affected_types::reflects,	false,	false},
	{u8"霸体框",			u8"霸体框颜色",			{ 64, 127, 127 },	action_types::affected, affected_types::invulnerability, false, false},
	{u8"当身框",			u8"当身框颜色",			{ 0, 0, 255 },		action_types::affected, affected_types::parries,	false, false},
	{u8"对投当身框",		u8"对投当身框颜色",		{ 139, 0, 255 },	action_types::affected, affected_types::parriesex,	false, false},
};