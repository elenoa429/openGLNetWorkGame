//==============================================================================
// �^�C�g��     :   OpenGL�p���f���N���X
// �t�@�C����   :   modelGL.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/05
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/05 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "modelGL.h"
#include "rendererGL.h"
#include "main.h"

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
// �֐��� : CModelGL()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CModelGL::CModelGL()
{
	m_subsetNum = 0;
	m_pSubsets  = NULL;
}

//==============================================================================
// �֐��� : ~CModelGL()
// ����   : void
// �߂�l : void
// ����   : �f�X�g���N�^
//==============================================================================
CModelGL::~CModelGL()
{

}

//==============================================================================
// �֐��� : bool DrawSubset( DWORD attribId )
// ����   : DWORD AttribId : �`��Ώ�ID
// �߂�l : void
// ����   : �T�u�Z�b�g���Ƃ̕`�揈��
//==============================================================================
bool CModelGL::DrawSubset( DWORD attribId )
{
	if( attribId >= m_subsetNum )
	{
		return false;	// �͈͊O�̂��ߏ������s
	}

	glEnable( GL_DEPTH_TEST );

	// �f�[�^����
	SUBSET modelData = m_pSubsets[ attribId ];

	VECTOR3* pPos = modelData.pPosBuff;
	VECTOR3* pNor = modelData.pNorBuff;
	VECTOR2* pTex = modelData.pTexBuff;

	DWORD idxNum = modelData.idxNum;

	// ���f���̕`�揈��
	glBegin( GL_TRIANGLES );
	{
		for( DWORD idxCnt = 0 ; idxCnt < idxNum ; idxCnt++ )
		{
			// �C���f�b�N�X�f�[�^�擾
			DWORD posIdx = m_pSubsets[ attribId ].pPosIdxBuff[ idxCnt ];
			DWORD norIdx = m_pSubsets[ attribId ].pNorIdxBuff[ idxCnt ];
			DWORD texIdx = m_pSubsets[ attribId ].pTexIdxBuff[ idxCnt ];

			// �e�f�[�^�擾
			VECTOR3 pos = pPos[ posIdx ];
			VECTOR3 nor = pNor[ norIdx ];
			VECTOR2 tex = pTex[ texIdx ];

			// �`�揈���Ăяo��
			glTexCoord2f( tex.x , tex.y );
			glNormal3f( nor.x , nor.y , nor.z );
			glVertex3f( pos.x , pos.y , pos.z );
		}
	}
	glEnd();

	glDisable( GL_DEPTH_TEST );

	return true;		// ��������
}

//==============================================================================
// �֐��� : void Release( void )
// ����   : void
// �߂�l : void
// ����   : �������
//==============================================================================
void CModelGL::Release( void )
{
	this->Uninit();
	delete this;
}

//==============================================================================
// �֐��� : void Uninit( void )
// ����   : void
// �߂�l : void
// ����   : �I������
//==============================================================================
void CModelGL::Uninit( void )
{
	// �f�[�^�Q���
	if( m_pSubsets != NULL )
	{
		for( DWORD i = 0 ; i < m_subsetNum ; i++ )
		{
			delete[] m_pSubsets[ i ].pPosBuff;
			delete[] m_pSubsets[ i ].pTexBuff;
			delete[] m_pSubsets[ i ].pNorBuff;
			delete[] m_pSubsets[ i ].pPosIdxBuff;
			delete[] m_pSubsets[ i ].pTexIdxBuff;
			delete[] m_pSubsets[ i ].pNorIdxBuff;

			m_pSubsets[ i ].pPosBuff = NULL;
			m_pSubsets[ i ].pTexBuff = NULL;
			m_pSubsets[ i ].pNorBuff = NULL;
			m_pSubsets[ i ].pPosIdxBuff = NULL;
			m_pSubsets[ i ].pTexIdxBuff = NULL;
			m_pSubsets[ i ].pNorIdxBuff = NULL;
		}

		delete[] m_pSubsets;
		m_pSubsets = NULL;
	}

	// ���N���X�̏I������
	CModel::Uninit();
}

//==============================================================================
// �֐��� : bool SetSubsets( int subsetNum , SUBSET* pDataBuff )
// ����   : int subsetNum     : �T�u�Z�b�g��
//          SUBSET* pDataBuff : �f�[�^�Q�ւ̃|�C���^
// �߂�l : bool�^            : ��������
// ����   : �T�u�Z�b�g�f�[�^�ݒ菈��
//==============================================================================
bool CModelGL::SetSubsets( int subsetNum , SUBSET* pDataBuff )
{
	if( subsetNum <= 0 )
	{
		return false;
	}

	if( pDataBuff == NULL )
	{
		return false;
	}

	// �ݒ菈��
	m_subsetNum = subsetNum;
	m_pSubsets  = pDataBuff;

	return true;
}

//==============================================================================
// �֐��� : bool SetBuffers( int subsetIdx , VECTOR3* pPosBuff , VECTOR2* pTexBuff , VECTOR3* pNorBuff ,
//                            DWORD* pPosIdxBuff , DWORD* pTexIdxBuff , DWORD* pNorIdxBuff )
// ����   : 
// �߂�l : bool�^ : ��������
// ����   : �o�b�t�@�[�̓o�^����
//==============================================================================
bool CModelGL::SetBuffers( int subsetIdx , VECTOR3* pPosBuff , VECTOR2* pTexBuff , VECTOR3* pNorBuff , DWORD* pPosIdxBuff , DWORD* pTexIdxBuff , DWORD* pNorIdxBuff )
{
	//m_pPosBuff    = pPosBuff;
	//m_pTexBuff    = pTexBuff;
	//m_pNorBuff    = pNorBuff;
	//m_pPosIdxBuff = pPosIdxBuff;
	//m_pTexIdxBuff = pTexIdxBuff;
	//m_pNorIdxBuff = pNorIdxBuff;

	return true;
}

//==============================================================================
// �֐��� : �T���v��
// ����   : void
// �߂�l : void
// ����   : �T���v������
//==============================================================================

