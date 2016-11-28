//==============================================================================
// �^�C�g��     :   �L�����N�^�[���N���X
// �t�@�C����   :   charcter.h
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/11/21
//==============================================================================

//==============================================================================
// �X�V����: -2016/11/21 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�K�[�h
//==============================================================================
#pragma once

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "scene.h"
#include "parentModelManagerGL.h"
#include "motionGL.h"

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
// �N���X�錾
//==============================================================================
class CCharcter : public CScene
{
	//---------------------------------------------
	// [ �񋓌^ ]
	//---------------------------------------------
public:
	enum ACTION_STATE
	{
		ACTION_NONE = 0,
		ACTION_MOVE,
		ACTION_ATTACK,
		ACTION_DEAD,
	};

	enum HELTH_STATE
	{
		HELTH_NONE = 0,
		HELTH_DEAD,
	};

	enum TYPE
	{
		TYPE_DOG = 0,
		TYPE_CAT,
		TYPE_PANDA,
		TYPE_PENGUIN,
	};

	//---------------------------------------------
	// [ �����o�֐� ]
	//---------------------------------------------
public:
	CCharcter();
	virtual ~CCharcter();

	virtual bool Init( TYPE type );
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetId( int id ){ m_id = id; }

	int GetId(){ return m_id; }

	//---------------------------------------------
	// [ �����o�ϐ� ]
	//---------------------------------------------
protected:
	VECTOR3 m_pos;
	VECTOR3 m_rot;
	VECTOR3 m_scl;

	TYPE m_type;								// �v���C���[�̎�ށB�����ڂ����߂���́B
	int m_id;									// �v���C���[ID�B�`P�̂��ƁB
	int m_life;									// ���C�t�B�c�@�̂��ƁB

	ACTION_STATE m_actionState;					// �s����Ԏ��ʎq
	HELTH_STATE m_helthState;					// �X�e�[�^�X��Ԏ��ʎq

	MATRIX m_mtxWorld;							// ���[���h�}�g���N�X
	CParentModelManagerGL* m_pModelManager;		// ���f���}�l�[�W���ւ̃|�C���^
	CMotionGL* m_pMotion;						// ���[�V���������ւ̃|�C���^
};

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================