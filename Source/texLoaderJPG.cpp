//==============================================================================
// �^�C�g��     :   JPG�摜�ǂݍ��ݗp�N���X
// �t�@�C����   :   texLoaderJPG.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/12
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/12 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WARNING�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "texLoaderJPG.h"
#include <stdio.h>

extern "C"
{
#define XMD_H
#include "lib\libjpeg\include\jpeglib.h"
#include "lib\libjpeg\include\jerror.h"
}

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================
#ifdef _DEBUG
#pragma comment( lib, "lib\\libjpeg\\lib\\libjpegd.lib" )
#else
#pragma comment( lib, "lib\\libjpeg\\lib\\libjpeg.lib" )
#endif

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
bool CTexLoaderJPG::TextuerLoadJPG( char* path , CTexture** ppTexture )
{
	//--------------------------------------
	// [ �t�@�C���I�[�v�� ]
	//--------------------------------------
	FILE *fp;													// �t�@�C���|�C���^
	fp = fopen( path , "rb" );									// �w�肳�ꂽ�r�b�g�}�b�v�摜���J��

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
	jpeg_decompress_struct cInfo;
	jpeg_error_mgr jErr;

	cInfo.err = jpeg_std_error( &jErr );

	jpeg_create_decompress( &cInfo );

	// �ǂݍ��݃t�@�C���ݒ�
	jpeg_stdio_src( &cInfo , fp );

	// �w�b�_�[�ǂݍ���
	jpeg_read_header( &cInfo , TRUE );

	// �f�R�[�h�X�^�[�g
	jpeg_start_decompress( &cInfo );

	// �摜�p�����[�^�ݒ�
	LONG biWidth  = ( ( cInfo.output_width + 3 ) & 0xFFFFFFFC );
	LONG biHeight = cInfo.output_height;

	// JPEG 1���C���̃o�C�g��
	int nJpegLineBytes = biWidth * cInfo.output_components;

	// Bitmap 1���C���̃o�C�g��
	long nBmpLineBytes = ( biWidth * 3 + 3 ) & 0xFFFFFFFC;

	// Bitmap �̍ŉ����C���Ƀ|�C���^�ݒ�
	LPBYTE lpJpgData = new BYTE[ cInfo.output_height * nBmpLineBytes ];
	LPBYTE lpJpgDataTop = lpJpgData;											// �o�b�t�@�̐擪�ʒu���L�^

	lpJpgData += cInfo.output_height * nBmpLineBytes;
	while( cInfo.output_scanline < cInfo.output_height )
	{
		// �|�C���^�� 1���C�������炷
		lpJpgData -= nBmpLineBytes;
		JSAMPROW praw = ( JSAMPROW )lpJpgData;

		// Jpeg �� 1���C���ǂݍ���
		jpeg_read_scanlines( &cInfo , ( JSAMPARRAY )&praw , 1 );
	}

	jpeg_finish_decompress( &cInfo );
	jpeg_destroy_decompress( &cInfo );

	// �摜�̃r�b�g����UV���W�Ŏg����悤�ɃX���b�v����
	GLubyte* bits = new GLubyte[ cInfo.output_height * nBmpLineBytes ];									// �X���b�v�������̂��i�[���郏�[�N
	int heightNum = cInfo.output_height;																// ������

	for( int i = 0 ; i < heightNum; i++  )
	{
		long setPointDst = i * nBmpLineBytes;															// Dst�̊i�[�n�_( �ォ�牺�� )
		long setPointSrc = ( cInfo.output_height * nBmpLineBytes - nBmpLineBytes ) - setPointDst;		// Src�̊i�[�n�_( �������� )
		long setSize     = nBmpLineBytes * sizeof( GLubyte );											// �i�[�T�C�Y( �P�s������̑傫�� )

		memcpy( &bits[ setPointDst ] , &lpJpgDataTop[ setPointSrc ] , setSize );						// �������R�s�[
	}

	//--------------------------------------
	// [ �e�N�X�`���������� ]
	//--------------------------------------
	*ppTexture = CTextureGL::Create( ( int )biWidth , ( int )biHeight , GL_RGB , bits );	// ���������̌Ăяo��

	//--------------------------------------
	// [ �ǂݍ��ݏI������ ]
	//--------------------------------------
	fclose( fp );													// �t�@�C���N���[�Y

	delete[] bits;
	bits = NULL;

	delete[] lpJpgData;
	lpJpgData = NULL;

	return true;	// ��������
}


//==============================================================================
// �֐��� : void ErrorMsg( char* errorMsg , char* path )
// ����   : char* errorMsg : �G���[���b�Z�[�W
//          char* path     : �ǂݍ��݂Ɏ��s�����t�@�C���p�X
// �߂�l : void
// ����   : �ǂݍ��ݎ��s���̃G���[���\���p
//==============================================================================
void CTexLoaderJPG::ErrorMsg( char* errorMsg , char* path )
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
