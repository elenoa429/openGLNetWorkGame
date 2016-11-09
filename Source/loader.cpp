//==============================================================================
// �^�C�g��     :   �t�@�C���ǂݍ��ݗp�N���X
// �t�@�C����   :   loader.cpp
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
#include "loader.h"
#include <string.h>

/* ===�e�탍�[�_�[�̃C���N���[�h=== */
#include "texLoaderBMP.h"
#include "texLoaderTGA.h"
#include "texLoaderJPG.h"
#include "texLoaderPNG.h"

#include "ModelLoaderOBJ.h"

#include "materialLoaderMTL.h"

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================
#define EXTENSION_LEN_MAX	( 64 )		// �g���q�̍ő啶����( �����܂Ŏg�����͕s�� )

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
// �֐��� : bool TextuerLoad( char* path , CTexture** ppTexture )
// ����   : char* path           : �t�@�C���p�X( exe����̑��΍��W���]�܂��� )
//          CTexture** ppTexture : �e�N�X�`���i�[��|�C���^
// �߂�l : bool�^ : ��������
// ����   : �e�N�X�`���ǂݍ��ݏ���
//==============================================================================
bool CLoader::TextuerLoad( char* path , CTexture** ppTexture )
{
	//--------------------------------------
	// [ �g���q�̎擾 ]
	//--------------------------------------
	char pathBuff[ MAX_PATH ] = { '\0' };	// �t�@�C���p�X�p�o�b�t�@�[
	char* extension = NULL;					// �g���q�i�[�p�|�C���^

	strcpy( pathBuff , path );				// �o�b�t�@�Ƀp�X��ۑ�
	strtok( pathBuff , "." );				// �t�@�C���p�X�̊g���q�ȊO�̕�����r��( �����ɂ͂�������... )
	extension = strtok( NULL , "." );		// �g���q���擾

	/* ===�G���[�`�F�b�N=== */
	if( extension == NULL )
	{
		ErrorMsg(
			"�g���q��������܂���B\n�t�@�C���� : ",
			path );							// �G���[���b�Z�[�W�\��

		return false;						// �g���q��������Ȃ�or�擾���s
	}

	//--------------------------------------
	// [ �g���q�ɑΉ����������̌Ăяo�� ]
	//--------------------------------------
	bool bResult = false;	// ��������

	if( strcmp( extension , "bmp" ) == 0 )
	{
		CTexLoaderBMP* pTexLoaderBMP = new CTexLoaderBMP;				// ���[�_�[�̐���
		bResult = pTexLoaderBMP->TextuerLoadBMP( path , ppTexture );	// BMP�摜�ǂݍ���
		delete pTexLoaderBMP;											// ���[�_�[�폜
		pTexLoaderBMP = NULL;											// NULL����
	}
	else if( strcmp( extension , "tga" ) == 0 )
	{
		CTexLoaderTGA* pTexLoaderTGA = new CTexLoaderTGA;				// ���[�_�[�̐���
		bResult = pTexLoaderTGA->TextuerLoadTGA( path , ppTexture );	// TGA�摜�ǂݍ���
		delete pTexLoaderTGA;											// ���[�_�[�폜
		pTexLoaderTGA = NULL;											// NULL����
	}
	else if( strcmp( extension , "png" ) == 0 )
	{
		CTexLoaderPNG* pTexLoaderPNG = new CTexLoaderPNG;				// ���[�_�[�̐���
		bResult = pTexLoaderPNG->TextuerLoadPNG( path , ppTexture );	// PNG�摜�ǂݍ���
		delete pTexLoaderPNG;											// ���[�_�[�폜
		pTexLoaderPNG = NULL;											// NULL����
	}
	else if( strcmp( extension , "jpg" ) == 0 )
	{
		CTexLoaderJPG* pTexLoaderJPG = new CTexLoaderJPG;				// ���[�_�[�̐���
		bResult = pTexLoaderJPG->TextuerLoadJPG( path , ppTexture );	// JPG�摜�ǂݍ���
		delete pTexLoaderJPG;											// ���[�_�[�폜
		pTexLoaderJPG = NULL;											// NULL����
	}
	else
	{
		ErrorMsg(
			"�����������̊g���q�ł��B\n�t�@�C���� : " ,
			path );							// �G���[���b�Z�[�W�\��
	}

	return bResult;		// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool ModelLoad( char* pFileName , CMaterialBuffe** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
// ����   : char* pFileName               : �t�@�C����
//          CMaterialBuffer *ppMaterials  : �}�e���A���p�o�b�t�@�[�ւ̃_�u���|�C���^
//          DWORD* pNumMaterials          : �}�e���A�����i�[��|�C���^
//          CModel** ppModelMesh          : ���f���f�[�^�ւ̃_�u���|�C���^
// �߂�l : bool�^ : ��������
// ����   : �e�N�X�`���ǂݍ��ݏ���
//==============================================================================
bool CLoader::ModelLoad( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
{
	//--------------------------------------
	// [ �g���q�̎擾 ]
	//--------------------------------------
	char pathBuff[ MAX_PATH ] = { '\0' };	// �t�@�C���p�X�p�o�b�t�@�[
	char* extension = NULL;					// �g���q�i�[�p�|�C���^

	strcpy( pathBuff , pFileName );			// �o�b�t�@�Ƀt�@�C���l�[����ۑ�
	strtok( pathBuff , "." );				// �t�@�C���p�X�̊g���q�ȊO�̕�����r��( �����ɂ͂�������... )
	extension = strtok( NULL , "." );		// �g���q���擾

	/* ===�G���[�`�F�b�N=== */
	if( extension == NULL )
	{
		ErrorMsg(
			"�g���q��������܂���B\n�t�@�C���� : ",
			pFileName );

		return false;						// �g���q��������Ȃ�or�擾���s
	}

	//--------------------------------------
	// [ �g���q�ɑΉ����������̌Ăяo�� ]
	//--------------------------------------
	bool bResult = false;	// ��������

	if( strcmp( extension , "obj" ) == 0 )
	{
		CModelLoaderOBJ* pModelLoaderOBJ = new CModelLoaderOBJ;			// ���[�_�[�̐���
		bResult = pModelLoaderOBJ->ModelLoadOBJ( pFileName , ppMaterials , pNumMaterials , ppModelMesh );	// OBJ�t�@�C������̃f�[�^�ǂݍ���
		delete pModelLoaderOBJ;											// ���[�_�[�폜
		pModelLoaderOBJ = NULL;											// NULL����
	}
	else
	{
		ErrorMsg(
			"�����������̊g���q�ł��B\n�t�@�C���� : " ,
			pFileName );
	}

	return bResult;		// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool MaterialLoad( char* pFileName , CMaterial** ppMaterial )
// ����   : char* pFileName        : �t�@�C����
//          CMaterial** ppMaterial : �}�e���A�������ւ̃_�u���|�C���^
// �߂�l : bool�^                 : ��������
// ����   : �}�e���A���f�[�^�ǂݍ��ݏ���
//==============================================================================
bool CLoader::MaterialLoad( char* pFileName , CMaterial** ppMaterial )
{
	//--------------------------------------
	// [ �g���q�̎擾 ]
	//--------------------------------------
	char pathBuff[ MAX_PATH ] = { '\0' };	// �t�@�C���p�X�p�o�b�t�@�[
	char* extension = NULL;					// �g���q�i�[�p�|�C���^

	strcpy( pathBuff , pFileName );			// �o�b�t�@�Ƀt�@�C���l�[����ۑ�
	strtok( pathBuff , "." );				// �t�@�C���p�X�̊g���q�ȊO�̕�����r��( �����ɂ͂�������... )
	extension = strtok( NULL , "." );		// �g���q���擾

	// �G���[�`�F�b�N
	if( extension == NULL )
	{
		ErrorMsg(
			"�g���q��������܂���B\n�t�@�C���� : " ,
			pFileName );

		return false;						// �g���q��������Ȃ�or�擾���s
	}

	//--------------------------------------
	// [ �g���q�ɑΉ����������̌Ăяo�� ]
	//--------------------------------------
	bool bResult = false;	// ��������

	if( strcmp( extension , "mtl" ) == 0 )
	{
		CMaterialLoaderMTL* pMaterialLoaderMTL = new CMaterialLoaderMTL;			// ���[�_�[�̐���
		bResult = pMaterialLoaderMTL->MaterialLoadMTL( pFileName , ppMaterial );	// MTL�t�@�C������̃f�[�^�ǂݍ���
		delete pMaterialLoaderMTL;													// ���[�_�[�폜
		pMaterialLoaderMTL = NULL;													// NULL����
	}
	else
	{
		ErrorMsg(
			"�����������̊g���q�ł��B\n�t�@�C���� : " ,
			pFileName );
	}

	return bResult;		// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : void ErrorMsg( char* errorMsg , char* path )
// ����   : char* errorMsg : �G���[���b�Z�[�W
//          char* path     : �ǂݍ��݂Ɏ��s�����t�@�C���p�X
// �߂�l : void
// ����   : �ǂݍ��ݎ��s���̃G���[���\���p
//==============================================================================
void CLoader::ErrorMsg( char* errorMsg , char* path )
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
