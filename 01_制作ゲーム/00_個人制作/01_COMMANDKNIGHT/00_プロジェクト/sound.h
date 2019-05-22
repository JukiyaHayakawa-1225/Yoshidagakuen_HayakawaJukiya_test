//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:	//�N������A�N�Z�X�\
	//*************************************
	// �T�E���h�t�@�C��
	//*************************************
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,		// BGM0 (OP)
		SOUND_LABEL_TUTORIAL,			// BGM1	(TUTORIAL)
		SOUND_LABEL_GAME,			// BGM2	(GAME)
		SOUND_LABEL_RESULT,			// BGM3	(CLEAR)
		SOUND_LABEL_RANKING,			// BGM4	(GAMEOVER)
		SOUND_LABEL_SE_PAUSE,		//�|�[�Y
		SOUND_LABEL_SE_DAMAGE,		//�|�[�Y
		SOUND_LABEL_SE_PRESS,		//�|�[�Y
		SOUND_LABEL_SE_SLASH,		//�|�[�Y
		SOUND_LABEL_SE_COUNT,		//�|�[�Y
		SOUND_LABEL_SE_SKILL0,
		SOUND_LABEL_SE_SKILL1,
		SOUND_LABEL_SE_SKILL2,
		SOUND_LABEL_SE_CURE,
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
private:	//�����������A�N�Z�X�\
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
		{ "data/BGM/title.wav", -1 },		// BGM0 (OP)
		{ "data/BGM/tutorial.wav", -1 },		// BGM1	(TUTORIAL)
		{ "data/BGM/game.wav", -1 },		// BGM2	(GAME)
		{ "data/BGM/result.wav", 0 },		// BGM3	(CLEAR)
		{ "data/BGM/ranking.wav", -1 },		// BGM5	(RANKING)
		{ "data/SE/pause.wav", 0 },			// ���S
		{ "data/SE/damage.wav", 0 },		// ���S
		{ "data/SE/press.wav", 0 },			// ���S
		{ "data/SE/slash.wav", 0 },			// ���S
		{ "data/SE/count.wav", 0 },			// ���S
		{ "data/SE/skill0.wav", 0 },			// ���S
		{ "data/SE/skill1.wav", 0 },			// ���S
		{ "data/SE/skill2.wav", 0 },			// ���S
		{ "data/SE/cure.wav", 0 },			// ���S

	};
};
#endif
