//--------------------------------------------------------------------------------------
// File: ADX2Le.cpp
//
// ADX2Le�Ɋւ���֐��Q
//
// Date: 2015.10.1
// Author: Hideyasu Imase
//
// �ȒP�Ȏg����
//--------------------------------------------------------------------------------------
// ADX2Le�̑g�ݍ��ݕ�
//
// �P�Ecri_ware_pcx86_LE.dll��exe�t�@�C���̂���t�H���_�ɃR�s�[����
// �Q�Ecri\pc\include�փp�X��ʂ�
// �R�Ecri\pc\libs\x86�փp�X��ʂ�
// �S�Ecri_ware_pcx86_LE_import.lib�������N����
//     �� #pragma comment(lib, "cri_ware_pcx86_LE_import.lib")�Ŏw�肵�Ă�OK
//--------------------------------------------------------------------------------------
// �������F�ŏ��P��Ăяo���Ă�������
//          ADX2Le::Initialize("ACF�t�@�C����");
//
// �X�V�F���t���[���Ăяo���Ă�������
//          ADX2Le::Update();
//
// �I�������F�v���O�����I�����ɌĂяo���Ă�������
//          ADX2Le::Finalize();
//--------------------------------------------------------------------------------------
// ���f�[�^�̃��[�h�FAWB�t�@�C���͏ȗ���
//          ADX2Le::LoadAcb("ACB�t�@�C����", "AWB�t�@�C����");
//
// �Đ�
//          ADX2Le::Play(�L���[�C���f�b�N�X);
//
// ��~
//          ADX2Le::Stop();
//
// �|�[�Y���|�[�Y����
//          ADX2Le::Pause();
//
// ���ʐݒ�
//          ADX2Le::SetVolume(����[1.0f���ʏ�]);
//
// ���Đ������Ƃ̉��ʕω���|�[�Y�Ȃǎw��ł��܂��������ł̐����͊������܂�
//--------------------------------------------------------------------------------------
// �ڂ������Ƃ�m�肽������CRI ADX2�̃w���v�t�@�C�����Q�Ƃ��Ă�������
// �w���v�t�@�C���Fcri\documentation\CRI_ADX2LE_PC_Manual_j.chm
//--------------------------------------------------------------------------------------
#pragma once

#include <cri_adx2le.h>

// ADX2Le�̍Đ��v���C���[�N���X
class ADX2Le_Player
{
	// ACB�n���h��
	CriAtomExAcbHn m_acb_hn;

	// �v���C���[�n���h��
	CriAtomExPlayerHn m_player;

public:

	// �R���X�g���N�^
	ADX2Le_Player();

	// �v���C���[�̍쐬
	void Create();

	// Acb�t�@�C���̃��[�h
	void LoadAcb(const char *acb, const char *awb = NULL);

	// �v���C���[�̉���֐�
	void Release();

	// �v���C���[�n���h���̎擾
	CriAtomExPlayerHn GetPlayerHandle();

	//----- �Đ� -----//

	// �w��L���[�̍Đ� 
	CriAtomExPlaybackId Play(CriAtomExCueId cue_id, float volume = 1.0f);

	//----- ���� -----//

	// �v���C���[�̉��ʂ̐ݒ�
	void SetVolume(float volume);

	// �Đ�ID�w��̉��ʂ̐ݒ�
	void SetVolumeByID(CriAtomExPlaybackId playback_id, float volume);

	//----- �|�[�Y -----//

	// �v���C���[�̃|�[�Y
	void Pause();

	// �Đ�ID�w��̃|�[�Y
	void PauseByID(CriAtomExPlaybackId playback_id);

	// �v���C���[�̃|�[�Y��Ԃ̎擾
	bool IsPause();

	// �Đ�ID�w��̃|�[�Y��Ԃ̎擾
	bool IsPauseByID(CriAtomExPlaybackId playback_id);

	//----- ��~ -----//

	// �v���C���[�̒�~
	void Stop();

	// ����̍Đ����̒�~
	void StopByID(CriAtomExPlaybackId playback_id);

};

// ADX2Le�N���X
class ADX2Le
{
	// �ő�{�C�X���𑝂₷���߂̊֘A�p�����[�^
	static const int MAX_VOICE = 24;
	static const int MAX_VIRTUAL_VOICE = 64;	// �������葽��(�ʏ�{�C�X�{HCA-MX�{�C�X�{��)
	static const int MAX_CRIFS_LOADER = 64;		// �������葽��(�ʏ�{�C�X�{HCA-MX�{�C�X�{��)

	// �ő�T���v�����O���[�g�i�s�b�`�ύX�܂ށj
	static const int MAX_SAMPLING_RATE = (48000 * 2);

	// HCA-MX�R�[�f�b�N�̃T���v�����O���[�g
	static const int SAMPLINGRATE_HCAMX = 32000;

	static CriAtomExVoicePoolHn	m_standard_voice_pool;	// �{�C�X�v�[��(ADX/HCA�R�[�f�b�N�p)
	static CriAtomExVoicePoolHn	m_hcamx_voice_pool;		// �{�C�X�v�[��(HCA-MX�p)
	static CriAtomDbasId		m_dbas_id;				// D-BAS�n���h��

	static ADX2Le_Player m_player; // �v���C���[

private:
	static void user_error_callback_func(const CriChar8 *errid, CriUint32 p1, CriUint32 p2, CriUint32 *parray);
	static void *user_alloc_func(void *obj, CriUint32 size);
	static void user_free_func(void *obj, void *ptr);

public:

	// ����������
	static void Initialize(const char *acf);

	// �X�V����
	static void Update();

	// �I������
	static void Finalize();

	// �v���C���[�̎擾�֐�
	static ADX2Le_Player* GetPlayer();

	// Acb�t�@�C���̃��[�h
	static void LoadAcb(const char *acb, const char *awb = NULL);

	//----- �Đ� -----//

	// �w��L���[�̍Đ� 
	static CriAtomExPlaybackId Play(CriAtomExCueId cue_id, float volume = 1.0f);

	//----- ���� -----//

	// �v���C���[�̉��ʂ̐ݒ�
	static void SetVolume(float volume);

	//----- �|�[�Y -----//

	// �v���C���[�̃|�[�Y
	static void Pause();

	// �v���C���[�̃|�[�Y��Ԃ̎擾
	static bool IsPause();

	//----- ��~ -----//

	// �v���C���[�̒�~
	static void Stop();

};
