//************************************************/
//* @file  :Effect.cpp
//* @brief :Effekseer���g�p�����G�t�F�N�g�Đ��N���X
//* @date  :2017/05/04
//* @author:S.Katou
//************************************************/
#include "Effect.h"
#include <xaudio2.h>

// �f�o�C�X
ID3D11Device* ShunLib::Effect::m_device;

//�f�o�C�X�R���e�L�X�g
ID3D11DeviceContext* ShunLib::Effect::m_context;

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�o�C�X�̐ݒ�
//�b����  :�f�o�C�X
//�b����  :�f�o�C�X�R���e�L�X�g
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void ShunLib::Effect::SetDevice(ID3D11Device* device,
							    ID3D11DeviceContext* context)
{
	m_device = device;
	m_context = context;
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�t�@�C���w��R���X�g���N�^	
//�b����  :cmo�t�@�C���̖��O(wchar_t[])
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
ShunLib::Effect::Effect(const wchar_t efk[])
{
	// �`��Ǘ��C���X�^���X�̐���
	renderer = EffekseerRendererDX11::Renderer::Create(m_device, m_context, 32);
	
	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	manager = Effekseer::Manager::Create(32);

	// �`����@�̎w��A�Ǝ��Ɋg�����Ȃ������`���ł��B
	manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	manager->SetRingRenderer(renderer->CreateRingRenderer());
	
	// �e�N�X�`���摜�̓Ǎ����@�̎w��(�p�b�P�[�W������ǂݍ��ޏꍇ�g������K�v������܂��B)
	manager->SetTextureLoader(renderer->CreateTextureLoader());

	// ���W�n�̎w��(RH�ŉE��n�ALH�ō���n)
	manager->SetCoordinateSystem(Effekseer::CoordinateSystem::RH);

	// �G�t�F�N�g�̓Ǎ�
	effect = Effekseer::Effect::Create(manager, (EFK_CHAR*)L"Effect\\Gravity.efk");

	// �G�t�F�N�g�̍Đ�
	handle = manager->Play(effect, 0.0f, 0.0f, 0.0f);
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
ShunLib::Effect::~Effect()
{
	// �G�t�F�N�g��������܂��B�Đ����̏ꍇ�́A�Đ����I��������A�����I�ɉ������܂��B
	ES_SAFE_RELEASE(effect);
	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	manager->Destroy();
	// �`��p�C���X�^���X��j��
	renderer->Destory();
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :���f���̕`��
//�b����  :�ʒu�x�N�g��	(Vec3)
//�b����  :�r���[�s��	(Matrix)
//�b����  :�ˉe�s��		(Matrix)
//�b����  :�g�嗦		(Vec3)
//�b�߂�l:�Ȃ�(void)	
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void ShunLib::Effect::Draw(const ShunLib::Vec3 pos,
						   const ShunLib::Matrix& view,		
						   const ShunLib::Matrix & proj, 
						   const ShunLib::Vec3 scale)
{
	//�ʒu�x�N�g���R�s�[
	Effekseer::Vector3D e_pos = { pos.m_x,pos.m_y,pos.m_z };

	//�s����R�s�[
	Effekseer::Matrix44 e_view;
	Effekseer::Matrix44 e_proj;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			e_view.Values[i][j] = view.m_value[i][j];
			e_proj.Values[i][j] = proj.m_value[i][j];
		}
	}

	
	// �Đ����̃G�t�F�N�g�̈ړ�
	manager->SetLocation(handle, e_pos);

	//�g�嗦
	manager->SetScale(handle, scale.m_x,scale.m_y,scale.m_z);

	// ���e�s��̍X�V
	renderer->SetProjectionMatrix(e_proj);
	
	// �J�����s��̍X�V
	renderer->SetCameraMatrix(e_view);

	// �S�ẴG�t�F�N�g�̍X�V
	manager->Update();

	//�`��
	renderer->BeginRendering();
	manager->Draw();
	renderer->EndRendering();
}
