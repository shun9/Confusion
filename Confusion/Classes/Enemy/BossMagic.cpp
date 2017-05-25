//************************************************/
//* @file  :BossMagic.cpp
//* @brief :�G����������{�X���@�w�N���X
//* @date  :2017/05/17
//* @author:S.Katou
//************************************************/
#include "BossMagic.h"
#include "../RandomNumber/RandomNumber.h"


BossMagic::BossMagic(ShunLib::Vec3 pos, int interval, int firstInterval, float scale,int hp)
	:SummonMagic(pos,interval,firstInterval,scale)
	,m_hp(hp)
	, m_isDead(false)
{
}

BossMagic::~BossMagic()
{
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�G�𐶐�����
//�b����  :�Ȃ�(void)
//�b�߂�l:�G(shared_ptr<Enemy>)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
std::shared_ptr<Enemy> BossMagic::SummonEnemy()
{
	using namespace ShunLib;

	RandomNumber randNum;
	Vec3 randPos(randNum(-m_scale, m_scale), 0.0f, 1.0f);
	Vec3 randSpd(0.0f, 0.0f, randNum(0.1f, 100.0f));

	//�G����
	std::shared_ptr<Enemy>enemy = std::make_shared<Enemy>(L"CModel\\Enemy.cmo",
		*m_pos + randPos,randSpd);

	//�G�t�F�N�g�ݒ�
	DrawSummonEffect(enemy->Pos());

	//�J�E���g���Z�b�g
	m_summonIntervalTimer->ResetCount();

	//�p���[�_�E��
	m_hp--;

	return enemy;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :�r���[�s��		   (ShunLib::Matrix)
//�b����  :�v���W�F�N�V�����s��(ShunLib::Matrix)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void BossMagic::Draw(const ShunLib::Matrix & view, const ShunLib::Matrix & proj)
{
	if (m_isDead)
	{
		return;
	}

	using namespace ShunLib;

	Matrix world;
	world = Matrix::CreateScale(m_scale * 2)
		  * Matrix::CreateRotationY(m_angle)
		  * Matrix::CreateRotationX(90.0f)
		  * Matrix::CreateTranslation(*m_pos);

	m_texture->Draw(world, view, proj);

	m_summonEffect->Draw(view, proj);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�_���[�W���󂯂�
//�b����  :�_���[�W(int)
//�b�߂�l:�Ȃ��@�@(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void BossMagic::TakeDamage(int damage) {
	m_hp -= damage;
	if (m_hp < 0) { m_hp = 0; }
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���@�w�̐���
//�b����  :�X�e�[�W�̍��[(float)
//�b����  :�X�e�[�W�̏�[(float)
//�b����  :�X�e�[�W�̕��@(float)
//�b����  :�X�e�[�W�̍���(float)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
std::shared_ptr<SummonMagic> BossMagic::CreateMagic(float stageX, float stageW, float stageY, float stageH)
{
	using namespace ShunLib;

	//��������
	RandomNumber randNum;

	//�傫��
	float scale = randNum(0.1f, 5.0f);

	//�ʒu ���@�w�����܂�ʒu�ɐ���
	float posX = stageX > stageW ? randNum(stageW + scale, stageX - scale) : randNum(stageX + scale, stageW - scale);
	float posZ = stageY > stageH ? randNum(stageH + scale, stageY - scale) : randNum(stageY + scale, stageH - scale);
	Vec3 pos(posX,0.0f, posZ);

	//�����Ԋu
	int summonInterval = randNum(60,500);

	//�����n�߂�܂ł̎���
	int firstInterval = randNum(100,200);


	std::shared_ptr<SummonMagic> magic;
	magic = std::make_shared<SummonMagic>(pos, summonInterval, firstInterval, scale);

	return magic;
}