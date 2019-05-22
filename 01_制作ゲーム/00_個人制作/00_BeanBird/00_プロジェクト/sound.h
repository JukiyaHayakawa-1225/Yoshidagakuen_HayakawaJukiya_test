//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	//*************************************
	// �T�E���h�t�@�C��
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0 (OP)
		SOUND_LABEL_BGM001,			// BGM1	(TUTORIAL)
		SOUND_LABEL_BGM002,			// BGM2	(GAME)
		SOUND_LABEL_BGM003,			// BGM3	(CLEAR)
		SOUND_LABEL_BGM004,			// BGM4	(GAMEOVER)
		SOUND_LABEL_BGM005,			// BGM5	(RANKING)
		SOUND_LABEL_SE_BULLET,		// ���S
		SOUND_LABEL_SE_SHIT,		// ���S
		SOUND_LABEL_SE_DEATH,		// ���S
		SOUND_LABEL_SE_PAUSE,		//�|�[�Y
		SOUND_LABEL_SE_PAUSESELECT,	//�|�[�Y�Z���N�g
		SOUND_LABEL_SE_PAUSECURSOR,	//�|�[�Y�J�[�\��
		SOUND_LABEL_SE_PAUSECANCEL,	//�|�[�Y�L�����Z��
		SOUND_LABEL_SE_ALARM,		// ���S
		SOUND_LABEL_SE_GET,			// �A�C�e���l��
		SOUND_LABEL_SE_FEVER,		//�t�B�[�o�[
		SOUND_LABEL_SE_CANSEL,		//�L�����Z��
		SOUND_LABEL_SE_KETTEI,		//����
		SOUND_LABEL_SE_SLIDE,		//����
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/bgm000.wav", -1 },		// BGM0 (OP)
		{ "data/BGM/bgm001.wav", -1 },		// BGM1	(TUTORIAL)
		{ "data/BGM/bgm002.wav", -1 },		// BGM2	(GAME)
		{ "data/BGM/bgm003.wav", 0 },		// BGM3	(CLEAR)
		{ "data/BGM/bgm004.wav", 0 },		// BGM4	(GAMEOVER)
		{ "data/BGM/bgm005.wav", -1 },		// BGM5	(RANKING)
		{ "data/SE/bullet.wav", 0 },			// ���S
		{ "data/SE/fall.wav", 0 },			// ���S
		{ "data/SE/death.wav", 0 },			// ���S
		{ "data/SE/pause.wav", 0 },			// �|�[�Y
		{ "data/SE/pauseselect.wav", 0 },	// �|�[�Y
		{ "data/SE/cursor.wav", 0 },		// �|�[�Y
		{ "data/SE/cancel.wav", 0 },		// �|�[�Y
		{ "data/SE/alarm.wav", 0 },			// �x��
		{ "data/SE/get.wav", 0 },			// �A�C�e���l��
		{ "data/SE/fever.wav", 0 },			// �t�B�[�o�[
		{ "data/SE/back.wav", 0 },			// �L�����Z��
		{ "data/SE/kettei.wav", 0 },		// ����
		{ "data/SE/tutorial_advance.wav", 0 },		// ����
	};
};
#endif
