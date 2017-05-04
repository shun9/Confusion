//************************************************/
//* @file  :Effect.h
//* @brief :Effekseer���g�p�����G�t�F�N�g�Đ��N���X
//* @date  :2017/05/04
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
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
		static ID3D11Device* m_device;

		//�f�o�C�X�R���e�L�X�g
		static ID3D11DeviceContext* m_context;


		/*--�ÓI�֐�--*/
	public:
		//�f�o�C�X�̐ݒ�
		static void SetDevice(ID3D11Device* device,
							  ID3D11DeviceContext* context);

		/*--�����o�ϐ�--*/
	private:
		EffekseerRenderer::Renderer* renderer;
		Effekseer::Manager* manager;
		Effekseer::Effect* effect;
		Effekseer::Handle handle;


		/*--�����o�֐�--*/
	public:

		//�t�@�C���w��R���X�g���N�^
		Effect(const wchar_t efk[]);

		//�f�X�g���N�^
		~Effect();

		void Draw(const ShunLib::Vec3 pos, 
				  const ShunLib::Matrix& view,
				  const ShunLib::Matrix& proj, 
				  const ShunLib::Vec3 scale = (1.0f,1.0f,1.0f));
	};
}