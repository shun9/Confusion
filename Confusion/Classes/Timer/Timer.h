//************************************************/
//* @file  :Timer
//* @brief :時間を図るクラス
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

		//カウント
		void Update() { if (m_count < m_time) { m_count++; } }

		//時間が経過したかどうか
		bool IsEnded() { return m_count >= m_time; };

		//時間を設定
		void SetTime(int time) { m_time = time; }

		//カウントを初期化
		void ResetCount() { m_count = 0; }
	};
}
