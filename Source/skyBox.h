//==============================================================================
// �^�C�g��     :   �X�J�C�{�b�N�X�N���X
// �t�@�C����   :   skyBox.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/16
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/16 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "main.h"
#include "sceneGL3D.h"

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �N���X�錾
//==============================================================================
class CSkyBox : public CSceneGL3D
{
	/* ===�����o�֐�=== */
public:
	CSkyBox();								// �f�t�H���g�R���X�g���N�^
	~CSkyBox();								// �f�X�g���N�^

	virtual bool Init( char* texPath );		// ����������
	virtual void Uninit( void );			// �I������
	virtual void Update( void );			// �X�V����
	virtual void Draw( void );				// �`�揈��

private:
	float texUPos( int uPos );				// U���W�Z�o����
	float texVPos( int vPos );				// V���W�Z�o����

	/* ===�����o�ϐ�=== */
protected:
	VECTOR2 m_texUnitSize;					// �e�N�X�`��1���̑傫��

	int m_DivTexU;							// �e�N�X�`��U���W�̕�����
	int m_DivTexV;							// �e�N�X�`��V���W�̕�����
};

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
