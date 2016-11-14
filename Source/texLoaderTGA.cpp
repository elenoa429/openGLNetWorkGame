//==============================================================================
// �^�C�g��     :   TGA�摜�ǂݍ��ݗp�N���X
// �t�@�C����   :   texLoaderTGA.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/06
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/06 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WARNING�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "texLoaderTGA.h"
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

//==============================================================================
// �֐��� : bool TextuerLoadTGA( char* path , CTexture** ppTexture )
// ����   : char* path           : �t�@�C���p�X
//          CTexture** ppTexture : �e�N�X�`���N���X�ւ̃_�u���|�C���^
// �߂�l : bool�^               : ��������
// ����   : TGA�摜�ǂݍ��ݏ���
//==============================================================================
bool CTexLoaderTGA::TextuerLoadTGA( char* path , CTexture** ppTexture )
{
	//--------------------------------------
	// [ �t�@�C���I�[�v�� ]
	//--------------------------------------
	FILE *fp;											// �t�@�C���|�C���^
	fp = fopen( path , "rb" );							// �w�肳�ꂽ�r�b�g�}�b�v�摜���J��

														/* ===�G���[�`�F�b�N=== */
	if( fp == NULL )
	{
		ErrorMsg(
			"�摜�̓ǂݍ��݂Ɏ��s���܂����B\n�t�@�C���� : " ,
			path );												// �G���[���b�Z�[�W�\��
		return false;											// �������s
	}

	//--------------------------------------
	// [ �t�@�C���ǂݍ��� ]
	//--------------------------------------
	BYTE headerBuff[ 18 ];

	fread( headerBuff , 1 , sizeof( headerBuff ) , fp );			// �w�b�_�[�̓ǂݍ���

	m_header.IDFieldLength  = headerBuff[ 0 ];
	m_header.colormapType   = headerBuff[ 1 ];
	m_header.type           = headerBuff[ 2 ];
	m_header.colormapOrigin = headerBuff[ 3 ] | headerBuff[ 4 ];
	m_header.colormapLength = headerBuff[ 5 ] | headerBuff[ 6 ];
	m_header.colormapDepth  = headerBuff[ 7 ];
	m_header.originX        = headerBuff[ 8 ] | headerBuff[ 9 ];
	m_header.originY        = headerBuff[ 10 ] | headerBuff[ 11 ];
	m_header.width          = headerBuff[ 12 ] | headerBuff[ 13 ];
	m_header.height         = headerBuff[ 14 ] | headerBuff[ 15 ];
	m_header.depth          = headerBuff[ 16 ];
	m_header.descriptor     = headerBuff[ 17 ];

	GLubyte* bits = NULL;											// �r�b�g�f�[�^�p�̃��[�N�ւ̃|�C���^
	bits = new GLubyte[ m_header.width * m_header.height * 4 ];		// �摜�f�[�^�̃��[�N�m��

	//--------------------------------------
	// [ �f�[�^�ǂݍ��ݏ��� ]
	//--------------------------------------
	for( int y = ( m_header.height - 1 ) ; y >= 0 ; y-- )
	{
		int bitIdxH = y * m_header.width;		// �r�b�g�̍s�C���f�b�N�X

		for( int x = 0 ; x < m_header.width ; x++ )
		{
			int bitIdx = ( bitIdxH + x ) * 4;	// �r�b�g�C���f�b�N�X

			BYTE r , g , b , a;
			b = fgetc( fp );
			g = fgetc( fp );
			r = fgetc( fp );
			a = fgetc( fp );

			bits[ bitIdx + 0 ] = r;
			bits[ bitIdx + 1 ] = g;
			bits[ bitIdx + 2 ] = b;
			bits[ bitIdx + 3 ] = a;
		}
	}

	//for( int y = 0 ; y < m_header.height - 1 ; y++ )
	//{
	//	int bitIdxH = y * m_header.width;		// �r�b�g�̍s�C���f�b�N�X

	//	for( int x = 0 ; x < m_header.width ; x++ )
	//	{
	//		int bitIdx = ( bitIdxH + x ) * 4;	// �r�b�g�C���f�b�N�X

	//		BYTE r , g , b , a;
	//		b = fgetc( fp );
	//		g = fgetc( fp );
	//		r = fgetc( fp );
	//		a = fgetc( fp );

	//		bits[ bitIdx + 0 ] = r;
	//		bits[ bitIdx + 1 ] = g;
	//		bits[ bitIdx + 2 ] = b;
	//		bits[ bitIdx + 3 ] = a;
	//	}
	//}

	//--------------------------------------
	// [ �e�N�X�`���������� ]
	//--------------------------------------
	ppTexture[ 0 ] = CTextureGL::Create( ( int )m_header.width , ( int )m_header.height , GL_RGBA , bits );		// ���������̌Ăяo��

	//--------------------------------------
	// [ �ǂݍ��ݏI������ ]
	//--------------------------------------
	delete[] bits;													// ���[�N���
	fclose( fp );													// �t�@�C���N���[�Y

	return true;	// ��������
}


//==============================================================================
// �֐��� : void ErrorMsg( char* errorMsg , char* path )
// ����   : char* errorMsg : �G���[���b�Z�[�W
//          char* path     : �ǂݍ��݂Ɏ��s�����t�@�C���p�X
// �߂�l : void
// ����   : �ǂݍ��ݎ��s���̃G���[���\���p
//==============================================================================
void CTexLoaderTGA::ErrorMsg( char* errorMsg , char* path )
{
	char errorMSG[ 1024 ] ={ '\0' };								// �G���[���b�Z�[�W�p�o�b�t�@�[

	strcpy( errorMSG , errorMsg );									// �G���[���̕�����}��

	if( path != NULL )
	{
		char pathBuff[ MAX_PATH ] ={ '\0' };						// �t�@�C���p�X�p�o�b�t�@�[
		strcpy( pathBuff , path );									// �o�b�t�@�Ƀp�X��ۑ�
		strcat( errorMSG , pathBuff );								// �t�@�C���p�X��}��
	}

	MessageBox( NULL , errorMSG , "ERROR!!" , MB_ICONWARNING );		// �G���[���b�Z�[�W�\��
}
