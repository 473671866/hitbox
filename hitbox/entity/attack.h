#pragma once

enum class attack_types : int			//����������
{
	normal = 0x0,					//��ͨ����
	projectile = 0x1,				//���е���
	grasp = 0x2,					//Ͷ��
	force = 0x3,					//ǿ������
	guard = 0x5,					//��������

	none = 0x9999
};

struct attack_boxs						//������ÿ֡ռ��0x2C�ֽ�
{
	unsigned int frame;					//0x00
	unsigned int number;				//0x04����ӦATK���
	unsigned int hit;					//0x08������Hit��
	float x;							//0x0C
	float y;							//0x10
	float w;							//0x14
	float h;							//0x18
	unsigned int flag;					//0x1C��bit 8����ȭ/�ؽŵĹ������б�ʾ��һ֡ΪCͶ/DͶ���ж���
	char unknown[0xc];
};
static_assert(sizeof(attack_boxs) == 0x2C, "Size check");

struct attack_collections
{
	attack_types types;
	int level;				//��ʽ�ȼ�
	int damage;				//�˺�
	int minimum;			//����˺�
	int penetrate;			//��͸�˺�
	int stun;				//��ֵ
	int loss;				//�Ʒ�
	int selfaddpower;		//
	int oppoaddpower;
	char fill[0x1A4];
};
static_assert(sizeof(attack_collections) == 0x1C8, "Size check");

struct attacks
{
	char unknown[0x20];
	attack_collections* atccs;
};
