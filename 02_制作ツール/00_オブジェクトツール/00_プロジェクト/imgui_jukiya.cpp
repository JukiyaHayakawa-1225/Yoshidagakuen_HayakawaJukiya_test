//=============================================================================
//
// ImGui�̏��� [imgui_jukiya.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "imgui_jukiya.h"
#include "imconfig.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"

#include "object.h"
#include "editor.h"
#include "objectplayer.h"
#include "map.h"
#include "modelcreate.h"
#include "manager.h"
#include "camera.h"

//=============================================================================
// ImGui�̃R���X�g���N�^
//=============================================================================
CImGui_Jukiya::CImGui_Jukiya()
{

}

//=============================================================================
// ImGui�̃f�X�g���N�^
//=============================================================================
CImGui_Jukiya::~CImGui_Jukiya()
{
}

//=============================================================================
// ImGui�̏���������
//=============================================================================
void CImGui_Jukiya::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
	// ImGui�p�̃e�L�X�g�f�[�^�𐶐�����
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImFontConfig config;
	//config.MergeMode = true;
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/meiryo.ttc", 18.0f, &config, io.Fonts->GetGlyphRangesJapanese());

	// AddFontFromFileTTF�֐�
	// ��P���� : �t�H���g�f�[�^�̃t�@�C���p�X��
	// ��Q���� : �t�H���g�̃T�C�Y
	// ��R���� : NULL��OK
	// ��S���� : ���{��ɂ��������io.Fonts->GetGlyphRangesJapanese�Ŋ�{�I��OK
	io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/meiryo.ttc", 20.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	// ImGui�𐶐�����
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);
	ImGui::StyleColorsClassic();
}

//=============================================================================
// ImGui�̏I������
//=============================================================================
void CImGui_Jukiya::Uninit(void)
{
	// ImGui���I��������
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//=============================================================================
// ImGui�̍X�V����
//=============================================================================
void CImGui_Jukiya::Update(void)
{
	//�J�����̎擾
	CCamera *pCamera = CManager::GetCamera();

	//�I�u�W�F�N�g�v���C���[�̃|�C���^�擾����
	CObjectPlayer *pObjectPlayer;
	pObjectPlayer = CEditor::GetObjectPlayer();

	//�I�u�W�F�N�g�̃|�C���^���擾
	CObject *pObject;
	pObject = pObjectPlayer->GetObjectPointer();

	//�}�b�v�̃|�C���^���擾
	CMap *pMap = CEditor::GetMap();

	// �V�����t���[����p�ӂ���
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// �E�B���h�E�����J�n
	ImGui::Begin(u8"�I�u�W�F�N�g�c�[�� Ver1.1", false);

	// FPS�`��
	ImGui::Text("FPS : %.1f", ImGui::GetIO().Framerate);

	if (pCamera != NULL)
	{
		//�J�����̎��_�̎擾���
		float aCameraPosV[3] = {pCamera->GetPosV().x,pCamera->GetPosV().y,pCamera->GetPosV().z};

		//�J�����̒����_�̎擾���
		float aCameraPosR[3] = { pCamera->GetPosR().x,pCamera->GetPosR().y,pCamera->GetPosR().z };

		// �J�����̎��_�̕\��
		ImGui::InputFloat3(u8"�J�����̎��_", &aCameraPosV[0]);

		// �J�����̒����_�̕\��
		ImGui::InputFloat3(u8"�J�����̒����_", &aCameraPosR[0]);

		////���_�̐ݒu����
		//pCamera->SetPosV(D3DXVECTOR3(aCameraPosV[0], aCameraPosV[1], aCameraPosV[2]));

		////�����_�̐ݒu����
		//pCamera->SetPosR(D3DXVECTOR3(aCameraPosR[0], aCameraPosR[1], aCameraPosR[2]));

	}
	//���݂̏���ۑ�����
	if (ImGui::Button(u8"�ۑ�����"))
	{
		ImGui::SameLine();
		if (pMap != NULL)
		{//��񂪂���ꍇ
			pMap->SaveObject();
			ImGui::Text(u8"�ۑ����������܂����B");
		}
		else
		{//��񂪂Ȃ��ꍇ
			ImGui::Text(u8"�ۑ����o���܂���ł����B");
		}
	}

	// ������@�̕\��
	ImGui::CollapsingHeader(u8"������@");

	ImGui::Text(u8"W,A,S,D [�I�u�W�F�N�g�̈ړ�]");
	ImGui::Text(u8"��,��,��,�E [�J�����̈ړ�]");
	ImGui::Text(u8"T,B,Q,E [�J���������_�̈ړ�]");
	ImGui::Text(u8"Y,N,Z,C [�J�������_�̈ړ�]");
	ImGui::Text(u8"1,2 [��ނ̕ύX]");
	ImGui::Text(u8"Enter [���f���̐���]");
	ImGui::Text(u8"�ۑ������ꍇ�A����data/TEXT/MAP/OBJECT/save_object.txt�ɂ���܂��B");

	// �E�B���h�E�����I��
	ImGui::End();

	// �E�B���h�E�����J�n
	ImGui::Begin(u8"�I�u�W�F�N�g", false);

	if (pObjectPlayer != NULL)
	{
		if (pObjectPlayer != NULL)
		{
			if (pObject != NULL)
			{
				//�v���C���[�̑I������
				int nSelect = pObjectPlayer->GetSelectObject();

				//�v���C���[�̈ʒu�擾���
				float aPos[3] = { pObject->GetPos().x,  pObject->GetPos().y , pObject->GetPos().z };

				//�v���C���[�̌����擾���
				float aRot[3] = { pObject->GetRot().x,pObject->GetRot().y ,pObject->GetRot().z };

				//�v���C���[�̑傫���擾���
				float aSize[3] = { pObject->GetSize().x,  pObject->GetSize().y , pObject->GetSize().z };

				//�v���C���[�̃X�s�[�h�̎擾
				float fSpeed = pObjectPlayer->GetSpeed();

				//�v���C���[�̓����蔻��擾���
				bool bHit = pObject->GetHit();

				//�v���C���[�̔j��ł��邩�ǂ����擾���
				bool bDestroy = pObject->GetDestroy();

				//���݂̎�ޕ\��
				ImGui::InputInt(u8"���f���̎��", &nSelect);

				//�v���C���[�̈ʒu�\��
				ImGui::InputFloat3(u8"�ʒu", &aPos[0]);

				//�v���C���[�̌����\��
				ImGui::InputFloat3(u8"����", &aRot[0]);

				//�v���C���[�̑傫���\��
				ImGui::InputFloat3(u8"�傫��", &aSize[0]);

				//���݂̃X�s�[�h�\��
				ImGui::DragFloat(u8"�ړ���", &fSpeed);

				//�v���C���[�̓����蔻��\��
				ImGui::Checkbox(u8"�����蔻��", &bHit);

				//�v���C���[�̔j��ł��邩�ǂ����\��
				ImGui::Checkbox(u8"�j��ł��邩�ǂ���", &bDestroy);

				if (nSelect != pObjectPlayer->GetSelectObject())
				{//���݂Ɖߋ��Ŏ�ނ��Ⴄ�ꍇ
				 //�I����ނ̐ݒu����
					pObjectPlayer->SetSelectObject(nSelect);
				}

				//�ʒu�̐ݒu����
				pObject->SetPos(D3DXVECTOR3(aPos[0], aPos[1], aPos[2]));
				//pObjectPlayer->SetPos(D3DXVECTOR3(aPos[0], aPos[1], aPos[2]));

				//�����̐ݒu����
				pObject->SetRot(D3DXVECTOR3(aRot[0], aRot[1], aRot[2]));

				//�傫���̐ݒu����
				pObject->SetSize(D3DXVECTOR3(aSize[0], aSize[1], aSize[2]));

				if (fSpeed != pObjectPlayer->GetSpeed())
				{//���݂Ɖߋ��ŃX�s�[�h���Ⴄ�ꍇ
				 //�X�s�[�h�̑��
					pObjectPlayer->SetSpeed(fSpeed);
				}

				//�����蔻��̐ݒu����
				pObject->SetHit(bHit);

				//�j��ł��邩�ǂ����̐ݒu����
				pObject->SetDestroy(bDestroy);


				//���f����������
				if(ImGui::Button(u8"���f���𐶐�����"))
				{
					if (pMap != NULL)
					{
						CObject *pObject = NULL;
						if (pObject == NULL)
						{
							//�I�u�W�F�N�g�̐���
							pObject = CObject::Create(D3DXVECTOR3(aPos[0], aPos[1], aPos[2]),
								D3DXVECTOR3(aRot[0], aRot[1], aRot[2]),
								D3DXVECTOR3(aSize[0], aSize[1], aSize[2]),
								bHit,
								bDestroy);

							//LPD3DXMESH		mesh = pMap->GetCModelCreate()->GetMesh(nSelect);
							//LPD3DXBUFFER;
							//DWORD;
							pObject->BindX(pMap->GetCModelCreate()->GetMesh(nSelect),
								pMap->GetCModelCreate()->GetBuffMat(nSelect),
								pMap->GetCModelCreate()->GetNumMat(nSelect));
							pObject->SetType(nSelect);
						}
					}
				}
			}

		}

	}

	// �E�B���h�E�����I��
	ImGui::End();


	// �t���[�����I��������
	ImGui::EndFrame();
}

//=============================================================================
// ImGui�̕`�揈��
//=============================================================================
void CImGui_Jukiya::Draw(void)
{
	// Update�Ő�������ImGui��\������
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}