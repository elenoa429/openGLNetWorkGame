//==============================================================================
// �^�C�g��     :   OpenGL�p���[�V�����N���X
// �t�@�C����   :   motionGL.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/09/16
//==============================================================================

//==============================================================================
// �X�V����: -2016/09/16 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// WARNING�h�~
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "motionGL.h"
#include <stdio.h>
#include <string.h>

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================

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
// �֐��� : CMotionGL()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CMotionGL::CMotionGL()
{
	m_motionInfo.motionNum   = 0;
	m_motionInfo.pMotionData = NULL;
	m_motionIdx              = 0;
	m_flameCnt               = 0;;
}

//==============================================================================
// �֐��� : ~CMotionGL()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CMotionGL::~CMotionGL()
{

}

//==============================================================================
// �֐��� : CMotionGL* Create( const char* pMotionFileName )
// ����   : const char* pMotionFileName : �ǂݍ��݃��[�V�����t�@�C����
// �߂�l : CMotionGL*�^                : ���������C���X�^���X
// ����   : ��������
//==============================================================================
CMotionGL* CMotionGL::Create( const char* pMotionFileName )
{
	CMotionGL* pNewInstance = new CMotionGL;

	if( pNewInstance->Init( pMotionFileName ) == false )
	{
		pNewInstance->Release();
		pNewInstance = NULL;
	}

	return pNewInstance;
}

//==============================================================================
// �֐��� : void Release( void )
// ����   : void
// �߂�l : void
// ����   : �������
//==============================================================================
void CMotionGL::Release( void )
{
	Uninit();
	delete this;
}

//==============================================================================
// �֐��� : bool Init( const char* pMotionFileName )
// ����   : const char* pMotionFileName : �ǂݍ��݃��[�V�����t�@�C����
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CMotionGL::Init( const char* pMotionFileName )
{
	// ���̏���
	m_motionInfo.pMotionData = new MOTION;
	m_motionInfo.motionNum   = 1;

	// ���[�V�����ǂݍ��ݏ���
	if( LoadMotion( pMotionFileName , 0 ) == false )
	{
		return false;
	}

	return true;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CMotionGL::Uninit( void )
{
	if( m_motionInfo.pMotionData != NULL )
	{
		for( int i = 0 ; i < m_motionInfo.motionNum ; i++ )
		{
			delete[] m_motionInfo.pMotionData[ i ].pKeyInfoData;
			m_motionInfo.pMotionData[ i ].pKeyInfoData = NULL;
		}

		delete[] m_motionInfo.pMotionData;
		m_motionInfo.pMotionData = NULL;
	}
}

//==============================================================================
// �֐��� : void Update( void )
// ����   : void
// �߂�l : void
// ����   : �X�V����
//==============================================================================
void CMotionGL::Update( void )
{
	m_flameCnt++;

	if( m_flameCnt >= m_motionInfo.pMotionData[ m_motionIdx ].keyNum )
	{
		m_flameCnt = 0;
	}
}

//==============================================================================
// �֐��� : bool SetMotionData( CParentModelManagerGL* pSetModel )
// ����   : CParentModelManagerGL* pSetModel : �ݒ�Ώۂ̃��f���f�[�^
// �߂�l : bool�^
// ����   : ���[�V�����ݒ菈��
//==============================================================================
bool CMotionGL::SetMotionData( CParentModelManagerGL* pSetModel )
{
	int modelNum = pSetModel->GetModelListSize();

	for( int i = 0 ; i < modelNum ; i++ )
	{
		CParentModelGL* pModel = pSetModel->GetModelData( i );

		float posX = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].posX;
		float posY = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].posY;
		float posZ = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].posZ;
		float rotX = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].rotX;
		float rotY = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].rotY;
		float rotZ = m_motionInfo.pMotionData[ m_motionIdx ].pKeyInfoData[ m_flameCnt ].keyData[ i ].rotZ;

		pModel->SetPos( VECTOR3( posX , posY , posZ ) );
		pModel->SetRotDegree( VECTOR3( rotX , rotY , rotZ ) );
	}

	return true;
}

//==============================================================================
// �֐��� : bool LoadMotion( const char* pMotionFileName )
// ����   : const char* pMotionFileName : ���[�V�����t�@�C����
//          int motionIdx               : �ݒ��C���f�b�N�X
// �߂�l : bool�^
// ����   : ���[�V�����ǂݍ��ݏ���
//==============================================================================
bool CMotionGL::LoadMotion( const char* pMotionFileName , int motionIdx )
{
	// anm�t�@�C���I�[�v��
	FILE* fp;
	
	fopen_s( &fp , pMotionFileName , "rt" );

	if( fp == NULL )
	{
		return false;
	}

	// �v�f���擾
	int flameNum = 0;

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
		if( strcmp( token , "fr" ) == 0 )
		{
			flameNum++;
		}
	}

	// ���[�N�m��
	m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData = new KEY_INFO[ flameNum ];
	m_motionInfo.pMotionData[ motionIdx ].joinyNum = 3;
	m_motionInfo.pMotionData[ motionIdx ].keyNum   = flameNum;

	// �f�[�^�ǂݍ���
	int flameIdx = -1;
	int jointIdx = 0;
	
	fseek( fp , 0 , SEEK_SET );					// �t�@�C���ʒu��擪�ɃZ�b�g

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
		if( strcmp( token , "fr" ) == 0 )
		{
			flameIdx++;
			jointIdx = 0;

			fscanf( fp , "%d" , &m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].flame );
		}
		else if( strcmp( token , "ky" ) == 0 )
		{
			fscanf( fp , "%f %f %f %f %f %f" ,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].posX,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].posY,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].posZ,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].rotX,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].rotY,
				&m_motionInfo.pMotionData[ motionIdx ].pKeyInfoData[ flameIdx ].keyData[ jointIdx ].rotZ );

			jointIdx++;
		}
	}

	// �t�@�C���N���[�Y
	fclose( fp );

	return true;
}
