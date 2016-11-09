//==============================================================================
// �^�C�g��     :   ���_�o�b�t�@�[���N���X
// �t�@�C����   :   vertexBuffer.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/06
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/06 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "commonUtility.h"
#include "buffer.h"

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �N���X�錾
//==============================================================================
class CVertexBuffer : public CBuffer
{
	//---------------------------------------------
	// [ �����o�֐� ]
	//---------------------------------------------
public:
	// �R���X�g���N�^
	CVertexBuffer(){}

	// �f�X�g���N�^
	~CVertexBuffer(){}

	// �o�b�t�@�[��L����
	virtual bool Lock( unsigned int offset , unsigned int size , void** ppData , unsigned long flags ) = 0;

	// �o�b�t�@�[��L����
	virtual bool Unlock( void ) = 0;

	// �������
	virtual void Release( void ) = 0;

	// �v���C�x�[�g�f�[�^�擾
	virtual bool GetPrivateData( void** ppData , DWORD* pSizeOfData ) = 0;

	// �v���C�x�[�g�f�[�^�ݒ�
	virtual bool SetPrivateData( void* pData , DWORD sizeOfData ) = 0;

	//---------------------------------------------
	// [ �����o�ϐ� ]
	//---------------------------------------------

};

typedef class CVertexBuffer* LPVertexBuffer;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================