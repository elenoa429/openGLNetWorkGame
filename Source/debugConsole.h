//==============================================================================
// �^�C�g��     :   �f�o�b�O�p�R���\�[���N���X
// �t�@�C����   :   debugConsole.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/11/11
//==============================================================================

//==============================================================================
// �X�V����: -2016/11/11 ��������
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
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �O���錾
//==============================================================================

//==============================================================================
// �N���X�錾
//==============================================================================
class CDebugConsole
{
	//---------------------------------------------
	// [ �����o�֐� ]
	//---------------------------------------------
public:
	bool Init();
	void Uninit();
	
	bool Print( char *fmt , ... );

	static CDebugConsole* GetInstance()
	{
		static CDebugConsole instance;
		return &instance;
	}

private:
	CDebugConsole(){};
	~CDebugConsole(){};

	CDebugConsole( const CDebugConsole& ){};
	CDebugConsole& operator=( const CDebugConsole& ){};
	CDebugConsole( CDebugConsole&& ){};
	CDebugConsole& operator=( CDebugConsole&& ){};

	//---------------------------------------------
	// [ �����o�ϐ� ]
	//---------------------------------------------
private:
	HANDLE m_hStdOutput;							// �W���o�͂̃n���h��
	CONSOLE_SCREEN_BUFFER_INFO m_screenBuffer;		// �X�N���[���o�b�t�@�[���
};

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================