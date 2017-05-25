//************************************************/
//* @file  :SummonMagic.h
//* @brief :�G���������閂�@�w�N���X
//* @date  :2017/05/18
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "../Wrapper/Texture/Texture.h"
#include "../Wrapper/Model/Model.h"
#include "../Timer/Timer.h"

class SummonMagic
{
protected:
	static std::unique_ptr<ShunLib::Texture> m_texture;
	static std::unique_ptr<ShunLib::Effect> m_summonEffect;

	//�ʒu
	ShunLib::Vec3* m_pos;

	//�g�嗦,�ő�g�嗦�i�p���[�j
	float m_scale;
	float m_maxScale;

	//�����J�n������true
	bool m_isStart;

	//��]�p�p�x
	float m_angle;

	//�����Ԋu
	ShunLib::Timer* m_summonIntervalTimer;


	//�����J�n�܂ł̑҂�����
	ShunLib::Timer* m_firstIntervalTimer;

	//�����ɕK�v�ȃp���[
	float m_summonPower;

public:
	SummonMagic(ShunLib::Vec3 pos = ShunLib::Vec3(0.0f, 0.0f, 0.0f), int interval = 60, int firstInterval = 0, float scale = 5.0f, float summonPower = 1.0f);
	~SummonMagic();

	//�G�̐���
	virtual std::shared_ptr<Enemy> SummonEnemy();

	//�X�V����
	void Update();

	//�`��
	virtual void Draw(const ShunLib::Matrix& view,
					  const ShunLib::Matrix& proj);

	//�����\���ǂ����Ԃ�
	bool CanSummon()
	{
		if (m_scale <= 0.0f){
			return false;
		}

		return (m_summonIntervalTimer->IsEnded());
	}

	//�g�嗦�i�p���[�j
	void Scale(float scale) { m_scale = scale; }
	float Scale() { return m_scale; }

	//�����J�n���Ă��邩�ǂ���
	bool IsStarted() { return m_isStart; }

protected:
	void DrawSummonEffect(const ShunLib::Vec3& pos);
};
