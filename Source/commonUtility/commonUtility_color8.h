//==============================================================================
// �^�C�g��     :   8Bit�����̐F�p�N���X
// �t�@�C����   :   commonUtility.color8.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/05
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/05 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include <Windows.h>

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �N���X�錾
//==============================================================================
class COLOR_U8
{
	/* ===�����o�֐�=== */
public:
	COLOR_U8();
	COLOR_U8( unsigned char r , unsigned char g , unsigned char b , unsigned char a );
	~COLOR_U8();

	/* ===�����o�ϐ�=== */
public:
	union
	{
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		};

		unsigned char colRGBA[ 4 ];

		DWORD col;
	};
};

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================