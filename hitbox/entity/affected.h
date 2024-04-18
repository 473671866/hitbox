#pragma once

enum class affected_types :int
{
	normal = 0x1,							//�ܻ���
	capture = 0x2,							//��Ͷ��
	guard = 0x3,							//������
	ground = 0x4,							//�����ܻ���
	negative = 0x5,							//�������е��߿�
	reflects = 0x6,							//�������е��߿�
	invulnerability = 0x7,					//�����
	parries = 0x8,							//�����
	nothing = 0x9,							//���е��ߵ����
	parriesex = 0xA,						//Ͷ�������
	none = 0x9999
};

struct affected_boxs						//�ܻ���ṹ��ÿ֡ռ��0x2C�ֽ�
{
	unsigned int frame;						//0x00��֡��
	unsigned int _0x04;						//0x04
	affected_types types;					//0x08���ܻ�������
	unsigned int flag;						//0x0C��Flag�ڲ�ͬ���͵��ܻ����ж�Ӧ�Ĺ��ܲ�һ��
	unsigned int _0x10;						//0x10
	unsigned int path;						//0x14
	unsigned int _0x18;						//0x18
	float x;								//0x1C
	float y;								//0x20
	float w;								//0x24
	float h;								//0x28
};
static_assert(sizeof(affected_boxs) == 0x2C, "Size check");
