//==============================================================================
// �^�C�g��     :   ���̃v���C���[�N���X
// �t�@�C����   :   otherPlayer.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/11/28
//==============================================================================

//==============================================================================
// �X�V����: -2016/11/28 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "charcter.h"

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �N���X�錾
//==============================================================================
class COtherPlayer : public CCharcter
{
	//---------------------------------------------
	// [ �����o�֐� ]
	//---------------------------------------------
public:
	COtherPlayer();
	~COtherPlayer();

	static COtherPlayer* Create();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	//---------------------------------------------
	// [ �����o�ϐ� ]
	//---------------------------------------------
private:

};

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================