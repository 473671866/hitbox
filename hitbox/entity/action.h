#pragma once
#include "body.h"
#include "attack.h"
#include "affected.h"

enum class action_types : int
{
	body = 0x3,									//��λ��0x3
	affected = 0x4,								//�ܻ���0x4
	attack = 0x5,								//������0x5
};

struct action_collections						//ACTָ�뼯
{
	unsigned int capacity;						//0x0 ��֡����ָ��ָ�������ܴ�С = TotalFrame * 0x2C
	action_types types;							//0x4 ACT���ͣ�����ָ��ָ�������
	union
	{
		attack_boxs* attack;
		body_boxs* body;
		affected_boxs* affected;
	};
};
static_assert(sizeof(action_collections) == 0x10, "Size check");

struct actions_entry							//����ʵ����
{
	void* _0x0;									//0x0
	int max;									//0x08���������֡��
	int reset;									//0x0C����������֡��
	void* _0x10;								//0x10
	void* _0x18;								//0x18
	int unknown4;								//0x20
	int capacity;								//0x24��ACTָ�뼯��ָ����
	action_collections* actcs;					//0x28��ACTָ�뼯
};
static_assert(sizeof(actions_entry) == 0x30, "Size check");

struct actions									//������
{
	char _0x0[0x20];							//0x0
	actions_entry* entry;						//0x20
	void* hold;									//0x28
};
static_assert(sizeof(actions) == 0x30, "Size check");
