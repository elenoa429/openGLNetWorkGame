//==============================================================================
// �^�C�g��     :   BMP�摜�ǂݍ��ݗp�N���X
// �t�@�C����   :   texLoaderBMP.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/05/02
//==============================================================================

//==============================================================================
// �X�V����: -2016/05/02 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WARNING�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "texLoaderBMP.h"
#include <string.h>

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================

//==============================================================================
// �񋓌^�錾
//==============================================================================
enum BMP_BITCOUNT
{								/* ===�r�b�g�}�b�v�摜�̃r�b�g�J�E���g���ʎq=== */
	BMP_COLOR_2         = 1,		// 2�F���m�N���摜
	BMP_COLOR_16        = 4,		// 16�F�摜
	BMP_COLOR_256       = 8,		// 256�F�摜
	BMP_COLOR_TRUE      = 24,		// true color�摜( 1677���F )
	BMP_COLOR_TRUE_PLUS = 32,		// true color�摜( 1677���F )( ��{�I�ɂ͏�Ɠ�������...���ȁH )
};

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
// �֐��� : bool TextuerLoadBMP( char* path , CTexture** ppTexture )
// ����   : char* path           : bmp�摜�̃t�@�C���p�X
//          CTexture** ppTexture : �e�N�X�`���i�[��|�C���^
// �߂�l : bool�^ : ��������
// ����   : bmp�摜�ǂݍ��ݏ���
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP( char* path , CTexture** ppTexture )
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
			"�摜�̓ǂݍ��݂Ɏ��s���܂����B\n�t�@�C���� : ",
			path );												// �G���[���b�Z�[�W�\��
		return false;											// �������s
	}

	//--------------------------------------
	// [ �w�b�_�[�̓ǂݍ��� ]
	//--------------------------------------
	BITMAPFILEHEADER bmfh;										// �r�b�g�}�b�v�t�@�C���w�b�_�[
	BITMAPINFOHEADER bmih;										// �r�b�g�}�b�v�C���t�H�w�b�_�[

	fread( &bmfh , sizeof( BITMAPFILEHEADER ) , 1 , fp );		// �r�b�g�}�b�v�t�@�C���w�b�_�[�̓ǂݍ���
	fread( &bmih , sizeof( BITMAPINFOHEADER ) , 1 , fp );		// �r�b�g�}�b�v�C���t�H�w�b�_�[�̓ǂݍ���

	//--------------------------------------
	// [ ���ʕ����̓ǂݍ��� ]
	//--------------------------------------
	LONG width    = bmih.biWidth;								// �摜��
	LONG height   = bmih.biHeight;								// �摜����
	WORD bitCount = bmih.biBitCount;							// �F�r�b�g��

	//--------------------------------------
	// [ �r�b�g���ɉ������F���̎擾���� ]
	//--------------------------------------
	GLubyte* bits = NULL;										// �r�b�g�f�[�^�p�̃��[�N�ւ̃|�C���^
	bool bResult = false;										// ��������

	bits = new GLubyte[ width * height * 3 ];					// �摜�T�C�Y���̃��[�N�𓮓I�m��

	switch( bitCount )
	{
		case BMP_COLOR_2:
		{
			ErrorMsg(
				"���m�N���摜�ǂݍ��ݏ����͖������ł��B\n�t�@�C���� : ",
				path );															// �G���[���b�Z�[�W�\��
			bResult = TextuerLoadBMP_BIT_1( fp , width , height , bits );		// �ǂݍ��ݏ���
			break;
		}

		case BMP_COLOR_16:
		{
			ErrorMsg(
				"16�F�摜�ǂݍ��ݏ����͖������ł��B\n�t�@�C���� : ",
				path );															// �G���[���b�Z�[�W�\��
			bResult = TextuerLoadBMP_BIT_4( fp , width , height , bits );		// �ǂݍ��ݏ���
			break;
		}

		case BMP_COLOR_256:
		{
			bResult = TextuerLoadBMP_BIT_8( fp , width , height , bits );		// �ǂݍ��ݏ���
			break;
		}

		case BMP_COLOR_TRUE:
		{
			bResult = TextuerLoadBMP_BIT_24( fp , width , height , bits );		// �ǂݍ��ݏ���
			break;
		}

		case BMP_COLOR_TRUE_PLUS:
		{
			bResult = TextuerLoadBMP_BIT_32( fp , width , height , bits );		// �ǂݍ��ݏ���
			break;
		}

		default:
		{
			ErrorMsg(
				"�r�b�g��񂪂��܂��ǂݎ��܂���B\n�t�@�C�������Ă���\��������܂��B\n�t�@�C���� : " ,
				path );												// �G���[���b�Z�[�W�\��
			bResult = false;
			break;
		}
	}

	/* ===�G���[�`�F�b�N=== */
	if( bResult == false )
	{
		return false;	// �������s
	}

	//--------------------------------------
	// [ �e�N�X�`���������� ]
	//--------------------------------------
	ppTexture[ 0 ] = CTextureGL::Create( ( int )width , ( int )height , GL_RGB , bits );		// ���������̌Ăяo��

	//--------------------------------------
	// [ �ǂݍ��ݏI������ ]
	//--------------------------------------
	delete[] bits;													// ���[�N���
	fclose( fp );													// �t�@�C���N���[�Y

	return true;	// ��������
}

//==============================================================================
// �֐��� : bool TextuerLoadBMP_BIT_1( FILE* fp , LONG width , LONG height , GLubyte* bits )
// ����   : FILE* fp           : bmp�摜�̃t�@�C���|�C���^( �ǂݍ��ݍς� )
//          LONG width         : �摜��
//          LONG height        : �摜����
//          GLubyte* bits      : �e�N�X�`���i�[��|�C���^( �̈�m�ۍς� )
// �߂�l : bool�^             : ��������
// ����   : �F�r�b�g��1�̃r�b�g�}�b�v�ǂݍ��݊֐�
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_1( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	return false;	// �������s

	return true;	// ��������
}

//==============================================================================
// �֐��� : bool TextuerLoadBMP_BIT_4( FILE* fp , LONG width , LONG height , GLubyte* bits )
// ����   : FILE* fp           : bmp�摜�̃t�@�C���|�C���^( �ǂݍ��ݍς� )
//          LONG width         : �摜��
//          LONG height        : �摜����
//          GLubyte* bits      : �e�N�X�`���i�[��|�C���^( �̈�m�ۍς� )
// �߂�l : bool�^             : ��������
// ����   : �F�r�b�g��4�̃r�b�g�}�b�v�ǂݍ��݊֐�
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_4( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	return false;	// �������s

	return true;	// ��������
}

//==============================================================================
// �֐��� : bool TextuerLoadBMP_BIT_8( FILE* fp , LONG width , LONG height , GLubyte* bits )
// ����   : FILE* fp           : bmp�摜�̃t�@�C���|�C���^( �ǂݍ��ݍς� )
//          LONG width         : �摜��
//          LONG height        : �摜����
//          GLubyte* bits      : �e�N�X�`���i�[��|�C���^( �̈�m�ۍς� )
// �߂�l : bool�^             : ��������
// ����   : �F�r�b�g��8�̃r�b�g�}�b�v�ǂݍ��݊֐�
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_8( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	//--------------------------------------
	// [ �p���b�g�f�[�^�̐����E�擾���� ]
	//--------------------------------------
	int nWidthByteNum = ( int )width % 4;							// �����̃r�b�g���̂��܂�
	BYTE colIdx;													// �F�C���f�b�N�X�i�[�惏�[�N

	RGBQUAD *pColPalette = NULL;									// �J���[�p���b�g�f�[�^
	pColPalette = new RGBQUAD[ 256 ];								// �p���b�g���������I�m��
	fread( &pColPalette[ 0 ] , sizeof( RGBQUAD ) , 256 , fp );		// �J���[�p���b�g�f�[�^�̓ǂݍ���

	//--------------------------------------
	// [ �F�f�[�^�̎擾���� ]
	//--------------------------------------
	for( int y = ( height - 1 ); y >= 0; y-- )									// �t������ǂݍ���
	{
		int bitIdxH = ( width * y * 3 );										// ���ݓǂݍ���ł���r�b�g�̍s�C���f�b�N�X( 3��RGB�����̃r�b�g���l�������� )

		for( int x = 0; x < width; x++ )										// 1�s�ǂݍ���
		{
			/* ===�f�[�^�Ǎ�����=== */
			fread( &colIdx , 1 , 1 , fp );										// �J���[�C���f�b�N�X�ǂݍ���

			/* ===���[�N�Ƀf�[�^���=== */
			int bitIdx = bitIdxH + ( x * 3 );									// ���ݓǂݍ���ł���r�b�g�̃C���f�b�N�X( 3��RGB�����̃r�b�g���l�������� )

			bits[ bitIdx + 0 ] = ( GLubyte )pColPalette[ colIdx ].rgbRed;		// R�������
			bits[ bitIdx + 1 ] = ( GLubyte )pColPalette[ colIdx ].rgbGreen;		// G�������
			bits[ bitIdx + 2 ] = ( GLubyte )pColPalette[ colIdx ].rgbBlue;		// B�������
		}

		/* ===1Byte�����݂̂��߁A���܂��ǂݍ���=== */
		if( nWidthByteNum != 0 )
		{
			for( int i = 0; ( i + nWidthByteNum ) < 4; i++ )
			{
				fread( &colIdx , 1 , 1 , fp );									// �]��̓ǂݍ���
			}
		}
	}

	/* ===�I������=== */
	delete[] pColPalette;									// �J���[�p���b�g���
	

	return true;	// ��������
}

//==============================================================================
// �֐��� : bool TextuerLoadBMP_BIT_24( FILE* fp , LONG width , LONG height , GLubyte* bits )
// ����   : FILE* fp           : bmp�摜�̃t�@�C���|�C���^( �ǂݍ��ݍς� )
//          LONG width         : �摜��
//          LONG height        : �摜����
//          GLubyte* bits      : �e�N�X�`���i�[��|�C���^( �̈�m�ۍς� )
// �߂�l : bool�^             : ��������
// ����   : �F�r�b�g��24�̃r�b�g�}�b�v�ǂݍ��݊֐�
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_24( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	//--------------------------------------
	// [ ���l : ��������E��ɓǂݍ��� ]
	//--------------------------------------
	GLubyte r , g , b;										// RGB�J���[

	for( int y = ( height - 1 ) ; y >= 0 ; y-- )			// �t������ǂݍ���
	{
		int bitIdxH = ( width * y * 3 );					// ���ݓǂݍ���ł���r�b�g�̍s�C���f�b�N�X( 3��RGB�����̃r�b�g���l�������� )

		for( int x = 0 ; x < width ; x++ )					// 1�s�ǂݍ���
		{
			/* ===�f�[�^�Ǎ�=== */
			fread( &b , 1 , 1 , fp );						// B�����ǂݍ���
			fread( &g , 1 , 1 , fp );						// G�����ǂݍ���
			fread( &r , 1 , 1 , fp );						// R�����ǂݍ���

			/* ===���[�N�Ƀf�[�^���=== */
			int bitIdx = bitIdxH + ( x * 3 );				// ���ݓǂݍ���ł���r�b�g�̃C���f�b�N�X( 3��RGB�����̃r�b�g���l�������� )

			bits[ bitIdx + 0 ] = r;							// R�������
			bits[ bitIdx + 1 ] = g;							// G�������
			bits[ bitIdx + 2 ] = b;							// B�������
		}
	}

	return true;	// ��������
}

//==============================================================================
// �֐��� : bool TextuerLoadBMP_BIT_32( FILE* fp , LONG width , LONG height , GLubyte* bits )
// ����   : FILE* fp           : bmp�摜�̃t�@�C���|�C���^( �ǂݍ��ݍς� )
//          LONG width         : �摜��
//          LONG height        : �摜����
//          GLubyte* bits      : �e�N�X�`���i�[��|�C���^( �̈�m�ۍς� )
// �߂�l : bool�^             : ��������
// ����   : �F�r�b�g��32�̃r�b�g�}�b�v�ǂݍ��݊֐�
//==============================================================================
bool CTexLoaderBMP::TextuerLoadBMP_BIT_32( FILE* fp , LONG width , LONG height , GLubyte* bits )
{
	//--------------------------------------
	// [ ���l : ��������E��ɓǂݍ��� ]
	//--------------------------------------
	GLubyte r , g , b , a;									// RGBA�J���[

	for( int y = ( height - 1 ); y >= 0; y-- )				// �t������ǂݍ���
	{
		int bitIdxH = ( width * y * 3 );					// ���ݓǂݍ���ł���r�b�g�̍s�C���f�b�N�X( 3��RGB�����̃r�b�g���l�������� )

		for( int x = 0; x < width; x++ )					// 1�s�ǂݍ���
		{
			/* ===�f�[�^�Ǎ�=== */
			fread( &b , 1 , 1 , fp );						// B�����ǂݍ���
			fread( &g , 1 , 1 , fp );						// G�����ǂݍ���
			fread( &r , 1 , 1 , fp );						// R�����ǂݍ���
			fread( &a , 1 , 1 , fp );						// ���ʂȕ�����ǂݍ��ޏ���

			/* ===���[�N�Ƀf�[�^���=== */
			int bitIdx = bitIdxH + ( x * 3 );				// ���ݓǂݍ���ł���r�b�g�̃C���f�b�N�X( 3��RGB�����̃r�b�g���l�������� )

			bits[ bitIdx + 0 ] = r;							// R�������
			bits[ bitIdx + 1 ] = g;							// G�������
			bits[ bitIdx + 2 ] = b;							// B�������
		}
	}

	return true;	// ��������
}

//==============================================================================
// �֐��� : void ErrorMsg( char* errorMsg , char* path )
// ����   : char* errorMsg : �G���[���b�Z�[�W
//          char* path     : �ǂݍ��݂Ɏ��s�����t�@�C���p�X
// �߂�l : void
// ����   : �ǂݍ��ݎ��s���̃G���[���\���p
//==============================================================================
void CTexLoaderBMP::ErrorMsg( char* errorMsg , char* path )
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
