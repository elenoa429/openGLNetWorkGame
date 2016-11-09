//==============================================================================
// �^�C�g��     :   ������֌W�����̒��ۃN���X
// �t�@�C����   :   font.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/18
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/18 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WARNIG�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "font.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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

//==============================================================================
// �֐��� : CFont()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CFont::CFont()
{
	m_refHIdx = 0;
}

//==============================================================================
// �֐��� : ~CFont()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CFont::~CFont()
{
}

//==============================================================================
// �֐��� : bool Init( void )
// ����   : void
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CFont::Init( void )
{
	CFont::ResetBuff();					// �o�̓o�b�t�@�[�̏�����
	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CFont::Uninit( void )
{

}

//==============================================================================
// �֐��� : bool Cat( char* source )
// ����   : char* source : �A����
// �߂�l : bool�^       : ��������
// ����   : �o�̓o�b�t�@�[�̕�����Ƃ̘A������
//==============================================================================
bool CFont::Cat( char* source )
{
	// ----------------------------------------------------------------------
	// [ �擾����������ƃo�b�t�@�[�̕������A�� ]
	// ----------------------------------------------------------------------
	char* strTop = source;											// �Q�ƒn�_�̐擪
	char* strCur = source;											// ���݂̎Q�ƒn�_
	bool bResult = false;											// ��������
	int len = 0;													// �Q�ƕ�����

	if( source == NULL )
	{
		return false;												// �G���[�`�F�b�N
	}

	while( *strTop != '\0' )
	{
		/* ===���s�R�[�h�̂܂ł̕��������m�F=== */
		len = 0;

		while( *strCur != '\n' && *strCur != '\0' )
		{
			len++;
			strCur++;
		}

		/* ===������̌���=== */
		int destLen   = 0;														// �o�͐�̕�����
		int sourceLen = 0;														// �o�͌��̕�����
		int limitSize = ( OUT_BUFF_SIZE_WIDTH * OUT_BUFF_SIZE_HEIGHT ) - ( m_refHIdx * OUT_BUFF_SIZE_WIDTH );	// ���E���e�T�C�Y

		destLen = strlen( &m_outBuffHW[ m_refHIdx ][ 0 ] );						// ���݊i�[����Ă��镶�������擾
		sourceLen = strlen( strCur );											// �o�͌��̕��������擾

		if( destLen + sourceLen <= limitSize )									// �o�b�t�@�I�[�o�[�����Ȃ��悤�Ƀ��~�b�^�[��������
		{
			strncat( &m_outBuffHW[ m_refHIdx ][ 0 ] , strTop , len );			// �擾�������̌���
		}
		else
		{
			return false;														// �������s
		}

		// ���s�̏���
		while( len >= OUT_BUFF_SIZE_WIDTH )
		{
			len -= OUT_BUFF_SIZE_WIDTH;
			m_refHIdx++;
		}

		while( *strCur == '\n' )
		{
			strCur++;
			m_refHIdx++;
		}

		if( m_refHIdx >= OUT_BUFF_SIZE_HEIGHT )
		{
			m_refHIdx = OUT_BUFF_SIZE_HEIGHT - 1;
		}

		// �Q�ƈʒu�ύX
		strTop = strCur + len;													// �擪�ʒu�����炷
	}

	if( *strTop == '\0' )
	{
		bResult = true;															// ��������
	}

	//strCur = strtok( source , "\n" );

	//while( strCur != NULL )
	//{
	//	int nDestLen = 0;											// �o�͐�̕�����
	//	int nSourceLen = 0;											// �o�͌��̕�����

	//	strNext = strtok( NULL , "\n" );

	//	nDestLen = strlen( &m_outBuffW[ 0 ] );						// ���݊i�[����Ă��镶�������擾
	//	nSourceLen = strlen( strCur );								// �o�͌��̕��������擾

	//	if( nDestLen + nSourceLen <= FONT_LIMIT_OUT_BUFF_SIZE )		// �o�b�t�@�I�[�o�[�����Ȃ��悤�Ƀ��~�b�^�[��������
	//	{
	//		strcat( &m_outBuffHW[ m_refHIdx ][ 0 ] , strCur );		// �擾�������̌���
	//		bResult = true;											// ��������
	//	}

	//	if( strNext != NULL )
	//	{
	//		if( m_refHIdx < OUT_BUFF_SIZE_HEIGHT - 1 )
	//		{
	//			/* ===���s�R�[�h�̌����m���߂�=== */
	//			char* checkStr = strCur;
	//			int newLineCnt = 0;

	//			while( checkStr != strNext )
	//			{
	//				if( *checkStr == '\n' )
	//				{
	//					newLineCnt++;		// ���s�R�[�h����
	//				}

	//				checkStr++;				// ���̃g�[�N���Ɉړ�
	//			};

	//			m_refHIdx += newLineCnt;	// ���������������s

	//			if( m_refHIdx >= OUT_BUFF_SIZE_HEIGHT )
	//			{
	//				m_refHIdx = OUT_BUFF_SIZE_HEIGHT - 1;		// �ő�Q�ƈʒu�܂Ŗ߂�
	//			}
	//		}
	//	}

	//	strCur = strNext;

	//}

	return bResult;												// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool Print( char *fmt , ... )
// ����   : char *fmt : �i�[���镶����
//          ...       : �ψ���( ������ɕϊ����i�[ )
// �߂�l : bool�^    : ��������
// ����   : �o�̓o�b�t�@�[�ɕ�����𑗂鏈��
//==============================================================================
bool CFont::Print( char *fmt , ... )
{
	// ----------------------------------------------------------------------
	// [ �擾������������o�b�t�@�[�Ɋi�[ ]
	// ----------------------------------------------------------------------
	va_list ap;															// �ψ����p�̃|�C���^
	char aSourceBuff[ OUT_BUFF_SIZE_HEIGHT * OUT_BUFF_SIZE_WIDTH ];		// �擾���̃o�b�t�@�[
	bool bResult =  false;												// ��������

	va_start( ap, fmt );												// �ψ�����p����ݒ�

	vsprintf( &aSourceBuff[ 0 ] , fmt , ap );							// �擾���������i�[

	va_end( ap );														// �ψ����ݒ�I��

	// ----------------------------------------------------------------------
	// [ �o�̓o�b�t�@�[�ɐ���������������i�[ ]
	// ----------------------------------------------------------------------
	bResult = this->Cat( aSourceBuff );									// ��������

	return bResult;														// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : void ResetBuff( void )
// ����   : void
// �߂�l : void
// ����   : �o�̓o�b�t�@�[�̏���������
//==============================================================================
void CFont::ResetBuff( void )
{
	memset( m_outBuffW , 0 , sizeof( m_outBuffW ) );	// ���g0����

	m_refHIdx = 0;										// �Q�ƃC���f�b�N�X���Z�b�g
}