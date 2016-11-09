//==============================================================================
// �^�C�g��     :   OBJ�t�@�C������̃��f���ǂݍ��ݏ����p�N���X
// �t�@�C����   :   ModelLoaderOBJ.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/11
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/11 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "ModelLoaderOBJ.h"
#include <stdio.h>
#include "modelGL.h"

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
// �֐��� : bool ModelLoadOBJ( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
// ����   : char* pFileName               : �t�@�C����
//          CMaterialBuffer** ppMaterials : �}�e���A���p�o�b�t�@�[�ւ̃_�u���|�C���^
//          DWORD* pNumMaterials          : �}�e���A�����i�[��|�C���^
//          CModel** ppModelMesh          : ���f���f�[�^�ւ̃_�u���|�C���^
// �߂�l : bool�^ : ��������
// ����   : �f�[�^�ǂݍ��ݏ���
//==============================================================================
bool CModelLoaderOBJ::ModelLoadOBJ( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh )
{
	// �t�@�C���I�[�v��
	FILE* fp = fopen( pFileName , "rt" );

	if( fp == NULL )
	{
		return false;	// �t�@�C���I�[�v�����s�ɂ�菈�����s
	}

	//-------------------------------------------------
	// [ �f�[�^���[�N�̐������� ]
	//-------------------------------------------------
	// �f�[�^�e�[�u���̐���
	CModelGL::SUBSET* pSubsetTable = NULL;			// �f�[�^�e�[�u���̐擪�|�C���^
	DWORD numGroup = 0;								// �O���[�v��

	while( 1 )
	{
		// �g�[�N���擾
		char token[ 256 ] = { 0 };

		fscanf( fp , "%s" , token );

		// �t�@�C���̏I�[�܂œ��B�ɂ�菈���I��
		if( feof( fp ) != 0 )
		{
			break;
		}

		// �g�[�N�����
		if( strcmp( token , "g" ) == 0 )
		{
			numGroup++;
		}
	}

	pSubsetTable = new CModelGL::SUBSET[ numGroup ];			// �f�[�^�e�[�u������

	// ���[�N��������
	for( DWORD i = 0 ; i < numGroup ; i++ )
	{
		pSubsetTable[ i ].pPosBuff   = NULL;
		pSubsetTable[ i ].pTexBuff   = NULL;
		pSubsetTable[ i ].pNorBuff   = NULL;
		pSubsetTable[ i ].posDataNum = 0;
		pSubsetTable[ i ].texDataNum = 0;
		pSubsetTable[ i ].norDataNum = 0;

		pSubsetTable[ i ].pPosIdxBuff = NULL;
		pSubsetTable[ i ].pTexIdxBuff = NULL;
		pSubsetTable[ i ].pNorIdxBuff = NULL;
		pSubsetTable[ i ].idxNum      = 0;
	}

	fseek( fp , 0 , SEEK_SET );									// �t�@�C���ʒu��擪�ɃZ�b�g

	// �ŏ��̃O���[�v�擪�֔��
	while( 1 )
	{
		// �g�[�N���擾
		char token[ 256 ] = { 0 };

		fscanf( fp , "%s" , token );

		// �t�@�C���̏I�[�܂œ��B�ɂ�菈���I��
		if( feof( fp ) != 0 )
		{
			break;
		}

		// �g�[�N�����
		if( strcmp( token , "g" ) == 0 )
		{
			break;
		}
	}

	// ���[�N����
	for( UINT groupCnt = 0 ; groupCnt < numGroup ; groupCnt++ )
	{
		// �e�v�f���̊m�F
		DWORD numPos = 0;						// ���_���W��
		DWORD numTex = 0;						// �e�N�X�`�����W��
		DWORD numNor = 0;						// �@����
		DWORD numFace = 0;						// �ʐ�
		char token[ 256 ] = { 0 };				// �g�[�N���p���[�N
		DWORD groupIdxNum = 0;					// �O���[�v���̒��_�C���f�b�N�X��

		while( 1 )
		{
			// �g�[�N���擾
			fscanf( fp , "%s" , token );

			// �g�[�N�����
			if( feof( fp ) != 0 || strcmp( token , "g" ) == 0 )
			{
				break;		// �t�@�C���̏I�[�܂œ��Bor���̃O���[�v�̐擪�ɓ��B�ɂ�菈���I��
			}

			if( strcmp( token , "v" ) == 0 )
			{
				numPos++;
			}
			else if( strcmp( token , "vt" ) == 0 )
			{
				numTex++;
			}
			else if( strcmp( token , "vn" ) == 0 )
			{
				numNor++;
			}
			else if( strcmp( token , "f" ) == 0 )
			{
				numFace++;
				groupIdxNum++;
			}
		}

		// �f�[�^���[�N�m��
		pSubsetTable[ groupCnt ].pPosBuff = new VECTOR3[ numPos ];
		pSubsetTable[ groupCnt ].pTexBuff = new VECTOR2[ numTex ];
		pSubsetTable[ groupCnt ].pNorBuff = new VECTOR3[ numNor ];
		pSubsetTable[ groupCnt ].posDataNum = numPos;
		pSubsetTable[ groupCnt ].texDataNum = numTex;
		pSubsetTable[ groupCnt ].norDataNum = numNor;

		DWORD idxNum = numFace * 3;		// ���_�C���f�b�N�X��

		pSubsetTable[ groupCnt ].pPosIdxBuff = new DWORD[ idxNum ];
		pSubsetTable[ groupCnt ].pTexIdxBuff = new DWORD[ idxNum ];
		pSubsetTable[ groupCnt ].pNorIdxBuff = new DWORD[ idxNum ];
		pSubsetTable[ groupCnt ].idxNum      = idxNum;
	}

	fseek( fp , 0 , SEEK_SET );									// �t�@�C���ʒu��擪�ɃZ�b�g

	//-------------------------------------------------
	// [ �f�[�^�i�[���� ]
	//-------------------------------------------------
	// �e�v�f���̊m�F
	DWORD idxPos       = 0;			// ���_���W�i�[�ʒu
	DWORD idxTex       = 0;			// �e�N�X�`�����W�i�[�ʒu
	DWORD idxNor       = 0;			// �@���i�[�ʒu
	DWORD idxOffsetPos = 0;			// ���_���W�i�[�ʒu�܂ł̃I�t�Z�b�g
	DWORD idxOffsetTex = 0;			// �e�N�X�`�����W�i�[�ʒu�܂ł̃I�t�Z�b�g
	DWORD idxOffsetNor = 0;			// �@���i�[�ʒu�܂ł̃I�t�Z�b�g
	DWORD idxIdx       = 0;			// �C���f�b�N�X�i�[�ʒu
	int idxGroup       = -1;		// ���ݎQ�Ƃ��Ă���O���[�v�̃C���f�b�N�X
	char token[ 256 ]  = { 0 };		// �g�[�N���p���[�N

	while( 1 )
	{
		// �g�[�N���擾
		fscanf( fp , "%s" , token );

		// �g�[�N�����
		if( feof( fp ) != 0 )
		{
			break;		// �t�@�C���̏I�[�܂œ��Bor���̃O���[�v�̐擪�ɓ��B�ɂ�菈���I��
		}

		if( strcmp( token , "v" ) == 0 )
		{
			fscanf( fp , "%f%f%f" ,
				&pSubsetTable[ idxGroup ].pPosBuff[ idxPos ].x ,
				&pSubsetTable[ idxGroup ].pPosBuff[ idxPos ].y ,
				&pSubsetTable[ idxGroup ].pPosBuff[ idxPos ].z );

			idxPos++;
		}
		else if( strcmp( token , "vt" ) == 0 )
		{
			fscanf( fp , "%f%f" ,
				&pSubsetTable[ idxGroup ].pTexBuff[ idxTex ].x ,
				&pSubsetTable[ idxGroup ].pTexBuff[ idxTex ].y );

			idxTex++;
		}
		else if( strcmp( token , "vn" ) == 0 )
		{
			fscanf( fp , "%f%f%f" ,
				&pSubsetTable[ idxGroup ].pNorBuff[ idxNor ].x ,
				&pSubsetTable[ idxGroup ].pNorBuff[ idxNor ].y ,
				&pSubsetTable[ idxGroup ].pNorBuff[ idxNor ].z );

			idxNor++;
		}
		else if( strcmp( token , "f" ) == 0 )
		{
			for( int i = 0 ; i < 3 ; i++ )
			{
				fscanf( fp , "%d/%d/%d" ,
					&pSubsetTable[ idxGroup ].pPosIdxBuff[ idxIdx ] ,
					&pSubsetTable[ idxGroup ].pTexIdxBuff[ idxIdx ] ,
					&pSubsetTable[ idxGroup ].pNorIdxBuff[ idxIdx ] );

				pSubsetTable[ idxGroup ].pPosIdxBuff[ idxIdx ] = pSubsetTable[ idxGroup ].pPosIdxBuff[ idxIdx ] - ( idxOffsetPos + 1 );
				pSubsetTable[ idxGroup ].pTexIdxBuff[ idxIdx ] = pSubsetTable[ idxGroup ].pTexIdxBuff[ idxIdx ] - ( idxOffsetTex + 1 );
				pSubsetTable[ idxGroup ].pNorIdxBuff[ idxIdx ] = pSubsetTable[ idxGroup ].pNorIdxBuff[ idxIdx ] - ( idxOffsetNor + 1 );

				idxIdx++;
			}
		}
		else if( strcmp( token , "g" ) == 0 )
		{
			idxGroup++;
			idxOffsetPos += idxPos;
			idxOffsetTex += idxTex;
			idxOffsetNor += idxNor;
			idxPos = 0;
			idxTex = 0;
			idxNor = 0;
			idxIdx = 0;
		}
	}

	// �i�[�����f�[�^�������̊e�v�f�ɓo�^
	*pNumMaterials = numGroup;											// �����ɂ̓O���[�v��==�}�e���A�����ł͂Ȃ��̂����A��U�����
	
	*ppModelMesh = new CModelGL;
	LPModelGL modelGL = dynamic_cast< LPModelGL >( *ppModelMesh );
	modelGL->Init( pFileName );
	modelGL->SetSubsets( numGroup , pSubsetTable );

	// �I������
	fclose( fp );

	return true;		// ��������
}

