#include "description.h"

description descriptions[] = {
	{1,		u8"��ͨ������",		false, false, { 200, 100, 100 },	action_types::attack,	attack_types::normal,			},
	{2,		u8"Ͷ����",			false, false, { 127, 191, 191 },	action_types::attack,	attack_types::grasp,			},
	{3,		u8"���е��߹�����",	false, false, { 127, 255, 127 },	action_types::attack,	attack_types::projectile,		},
	{4,		u8"����������",		false, false, { 127, 255, 127 },	action_types::attack,	attack_types::guard,			},
	{5,		u8"��λ��",			false, false, { 255, 165, 0  },	action_types::body,		body_types::none,				},
	{6,		u8"�ܻ���",			false, false, { 255, 255, 0 },	action_types::affected, affected_types::normal,			},
	{7,		u8"��Ͷ��",			false, false, { 127, 255, 255 },	action_types::affected, affected_types::capture,		},
	{8,		u8"������",			false, false, { 0, 255, 0 },		action_types::affected, affected_types::guard,			},
	{9,		u8"׷�ӿ�",			false, false, { 0, 255, 0 },		action_types::affected, affected_types::ground,			},
	{10,	u8"�������е��߿�",	false, false, { 128, 128, 255 },	action_types::affected, affected_types::negative,		},
	{11,	u8"�������е��߿�",	false, false, { 255, 127, 255 },	action_types::affected, affected_types::reflects,		},
	{12,	u8"�����",			false, false, { 64, 127, 127 },	action_types::affected, affected_types::invulnerability,},
	{13,	u8"�����",			false, false, { 0, 0, 255 },		action_types::affected, affected_types::parries,		},
	{14,	u8"��Ͷ�����",		false, false, { 139, 0, 255 },	action_types::affected, affected_types::parriesex,		},
};