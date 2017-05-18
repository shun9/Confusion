//************************************************/
//* @file  :Timer
//* @brief :���Ԃ�}��N���X
//* @date  :2017/05/17
//* @author:S.Katou
//************************************************/
#pragma once

namespace ShunLib
{
	class Timer
	{
	private:
		int m_count;
		int m_time;

	public:
		Timer():m_count(0),m_time(0) {};
		~Timer() {};

		//�J�E���g
		void Update() { if (m_count < m_time) { m_count++; } }

		//���Ԃ��o�߂������ǂ���
		bool IsEnded() { return m_count >= m_time; };

		//���Ԃ�ݒ�
		void SetTime(int time) { m_time = time; }

		//�J�E���g��������
		void ResetCount() { m_count = 0; }
	};
}
