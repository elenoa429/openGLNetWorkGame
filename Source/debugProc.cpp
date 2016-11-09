//==============================================================================
// �^�C�g��     :   �f�o�b�O�v���V�[�W��
// �t�@�C����   :   debugProc.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/20
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/20 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WANING�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "debugProc.h"
#include "fontGL.h"
#include <stdio.h>

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================

//==============================================================================
// �O���[�o���錾
//==============================================================================

//==============================================================================
// �ÓI�ϐ�
//==============================================================================
CDebugProc* CDebugProc::pDebugProc = NULL;

//==============================================================================
// �֐��� : CDebugProc()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CDebugProc::CDebugProc()
{
	m_pFont = NULL;
}

//==============================================================================
// �֐��� : ~CDebugProc()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CDebugProc::~CDebugProc()
{
}

//==============================================================================
// �֐��� : void Create( void )
// ����   : void
// �߂�l : void
// ����   : ��������
//==============================================================================
void CDebugProc::Create( void )
{
	if( pDebugProc == NULL )
	{
		pDebugProc = new CDebugProc;

		if ( pDebugProc->Init() == false )
		{
			CDebugProc::Release();
		}
	}
}

//==============================================================================
// �֐��� : void Release( void )
// ����   : void
// �߂�l : void
// ����   : �������
//==============================================================================
void CDebugProc::Release( void )
{
	if( pDebugProc != NULL )
	{
		pDebugProc->Uninit();
		delete pDebugProc;
		pDebugProc = NULL;
	}
}

//==============================================================================
// �֐��� : bool Init( void )
// ����   : void
// �߂�l : void
// ����   : ����������
//==============================================================================
bool CDebugProc::Init( void )
{
	CFontGL* pNewFontGL = new CFontGL;

	if( pNewFontGL->Init( 16 , "�l�r�S�V�b�N" ) == false )
	{
		pNewFontGL->Uninit();
		delete pNewFontGL;
		pNewFontGL = NULL;

		return false;
	}

	m_pFont = pNewFontGL;

	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CDebugProc::Uninit( void )
{
	if ( m_pFont != NULL )
	{
		CFontGL* pDeleteFontGL = ( CFontGL* )m_pFont;

		pDeleteFontGL->Uninit();
		delete pDeleteFontGL;
		pDeleteFontGL = NULL;

		m_pFont = NULL;
	}
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CDebugProc::Update( void )
{
	m_pFont->Update();
}

//==============================================================================
// �֐��� : void Draw( void )
// ����   : void
// �߂�l : void
// ����   : �`�揈��
//==============================================================================
void CDebugProc::Draw( void )
{
	m_pFont->Draw();
	m_pFont->ResetBuff();
}

//==============================================================================
// �֐��� : bool PrintDebugProc( char *fmt , ... )
// ����   : void
// �߂�l : void
// ����   : �o�̓o�b�t�@�[�ւ̏������ݏ���
//==============================================================================
bool CDebugProc::PrintDebugProc( char *fmt , ... )
{
	/* ===�ψ������當���񐶐�=== */
	va_list ap;															// �ψ����p�̃|�C���^
	char aSourceBuff[ OUT_BUFF_SIZE_HEIGHT * OUT_BUFF_SIZE_WIDTH ];		// �擾���̃o�b�t�@�[
	bool bResult = false;												// ��������

	va_start( ap , fmt );												// �ψ�����p����ݒ�
	vsprintf( &aSourceBuff[ 0 ] , fmt , ap );							// �擾���������i�[
	va_end( ap );														// �ψ����ݒ�I��

	/* ===��������������̘A��=== */
	bResult = m_pFont->Cat( aSourceBuff );

	return bResult;														// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : CDebugProc( const CDebugProc& )
// ����   : void
// �߂�l : void
// ����   : �R�s�[�R���X�g���N�^
//==============================================================================
CDebugProc::CDebugProc( const CDebugProc& )
{
}

//==============================================================================
// �֐��� : CDebugProc& operator=( const CDebugProc& )
// ����   : void
// �߂�l : void
// ����   : �I�y���[�^�[
//==============================================================================
void CDebugProc::operator=( const CDebugProc& )
{
}