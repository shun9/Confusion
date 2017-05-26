//************************************************/
//* @file  :Effect.h
//* @brief :Effekseer���g�p�����G�t�F�N�g�Đ��N���X
//* @date  :2017/05/16
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <memory>
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include "../Matrix/Matrix.h"

namespace ShunLib
{
	class Effect
	{
		/*--�ÓI�ϐ�--*/
	private:
		// �f�o�C�X
		static Microsoft::WRL::ComPtr<ID3D11Device>m_device;

		//�f�o�C�X�R���e�L�X�g
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_context;


		/*--�ÓI�֐�--*/
	public:
		//�f�o�C�X�̐ݒ�
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);
		static void ResetDevice();

		/*--�����o�ϐ�--*/
	private:
		EffekseerRenderer::Renderer* renderer;
		Effekseer::Manager* manager;
		Effekseer::Effect* effect;
		Effekseer::Handle handle;

		//�G�t�F�N�g�̃t���[�����i���ԁj
		int m_flame;

		//�t���[���̃J�E���g
		int m_flameCnt;

		//�Đ����I��������true
		bool m_isEnded;

		//�Đ����x�{��
		float m_spd;

		/*--�����o�֐�--*/
	public:

		//�t�@�C���w��R���X�g���N�^
		Effect(const wchar_t efk[], int flame, int spriteNum = 32, bool isDrawFirst = false);

		//�f�X�g���N�^
		~Effect();

		void Draw(const ShunLib::Matrix& view,
				  const ShunLib::Matrix& proj);

		void DrawLoop(const ShunLib::Matrix& view,
					  const ShunLib::Matrix& proj);

		//�`��̏�Ԃ����Z�b�g����
		void SetDraw(const ShunLib::Vec3 pos = ShunLib::Vec3::Zero)
		{
			handle = manager->Play(effect, pos.m_x,pos.m_y,pos.m_z);
			m_isEnded = false;
			m_flameCnt = 0;
		}

		//�ʒu��ݒ�
		void SetPos(const ShunLib::Vec3 pos)
		{
			//�ʒu�x�N�g���R�s�[
			Effekseer::Vector3D e_pos = { pos.m_x,pos.m_y,pos.m_z };
			manager->SetLocation(handle, e_pos);
		}

		//�g�嗦��ݒ�
		void SetScale(const ShunLib::Vec3 scale)
		{
			manager->SetScale(handle, scale.m_x, scale.m_y, scale.m_z);
		}

		//�Đ����x��ݒ�
		void SetSpd(float spd)
		{
			m_spd = spd;
			manager->SetSpeed(handle, m_spd);
		}

		//�X����ݒ�
		void SetRotate(const ShunLib::Vec3 axis,float angle)
		{
			Effekseer::Vector3D e_axis = { axis.m_x,axis.m_y,axis.m_z };
			manager->SetRotation(handle, e_axis, angle);
		}

		//�Đ����I���������ǂ���
		bool IsEnded() { return m_isEnded; }
	};
}