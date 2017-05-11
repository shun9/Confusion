//************************************************/
//* @file  :SummonMagic.h
//* @brief :�G���������閂�@�w�N���X
//* @date  :2017/05/10
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "../Wrapper/Texture/Texture.h"

class SummonMagic
{
private:
	ShunLib::Texture* m_texture;
	ShunLib::Effect* m_summonEffect;

	//�ʒu
	ShunLib::Vec3* m_pos;

	//�g�嗦,�ő�g�嗦�i�p���[�j
	float m_scale;
	float m_maxScale;


	bool m_isStart;

	//��]�p�p�x
	float m_angle;

	//�����Ԋu 
	const int m_interval;
	int m_intervaCnt;

	//�J�n�܂ł̑҂�����
	const int m_firstInterval;
	int m_firstIntervaCnt;

public:
	SummonMagic(ShunLib::Vec3 pos = ShunLib::Vec3(0.0f, 0.0f, 0.0f), int interval = 60, int firstInterval=0,float scale = 5.0f);
	~SummonMagic();
	
	std::shared_ptr<Enemy> Create();
	void Update();

	void Draw(const ShunLib::Matrix& view,
			  const ShunLib::Matrix& proj);

	//�����\���ǂ����Ԃ�
	bool CanSummon()
	{
		if (m_scale <= 0.0f) { return false; }
		return (m_intervaCnt > m_interval);
	}

	//�g�嗦�i�p���[�j
	void Scale(float scale) { m_scale = scale; }
	float Scale() { return m_scale; }

	//�����J�n���Ă��邩�ǂ���
	bool IsStarted() { return m_isStart; }
};
