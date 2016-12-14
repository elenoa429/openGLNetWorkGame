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
#include "collider3DSphere.h"

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

	enum CHARCTER_TYPE
	{
		CHARCTER_TYPE_RABBITS = 0,
		CHARCTER_TYPE_CAT,
		CHARCTER_TYPE_PANDA,
		CHARCTER_TYPE_PENGUIN,
		CHARCTER_TYPE_MAX,
	};
	
	enum FACE_STATE
	{
		FACE_NOMAL = 0,
	};

	//---------------------------------------------
	// [ �����o�֐� ]
	//---------------------------------------------
public:
	CCharcter();
	virtual ~CCharcter();

	virtual bool Init( int charcterType );
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetId( int id ){ m_id = id; }
	void SetPos( VECTOR3 pos ){ m_pos = pos; }
	void SetRot( VECTOR3 rot ){ m_rot = rot; }
	void SetMov( VECTOR3 mov ){ m_mov = mov; }

	int GetId(){ return m_id; }
	VECTOR3 GetPos(){ return m_pos; }
	VECTOR3 GetRot(){ return m_rot; }
	VECTOR3 GetMov(){ return m_mov; }

	CCollider3DSphere* GetBoundingSphere(){ return m_pBoundingSphere; }

	void Rotation( void );
	//---------------------------------------------
	// [ �����o�ϐ� ]
	//---------------------------------------------
protected:
	VECTOR3 m_pos;
	VECTOR3 m_rot;
	VECTOR3 m_rotMokuhyou;		// �ڕW�̌���
	VECTOR3 m_scl;
	float m_Width;
	float m_Height;
	float m_Depth;
	VECTOR3 m_Atari;			// �����蔻��

	VECTOR3 m_mov;				// �ړ���
	float m_axcel;				// �����x
	float m_axcelAttack;		// �A�^�b�N���̉����x
	VECTOR3 m_gensui;			// �ړ��̌����l
	VECTOR3 m_gensuiAttack;		// �A�^�b�N���̌����l
	float m_jump;				// �W�����v��
	float m_spinAxcel;			// �U������̉����x
	float m_spinGensui;			// �U������̌���

	CHARCTER_TYPE m_type;						// �v���C���[�̎�ށB�����ڂ����߂���́B
	int m_id;									// �v���C���[ID�B�`P�̂��ƁB
	int m_life;									// ���C�t�B�c�@�̂��ƁB

	ACTION_STATE m_actionState;					// �s����Ԏ��ʎq
	HELTH_STATE m_helthState;					// �X�e�[�^�X��Ԏ��ʎq

	MATRIX m_mtxWorld;							// ���[���h�}�g���N�X

	CCollider3DSphere* m_pBoundingSphere;		// ���̃o�E���f�B���O�{�����[��

	LPModel    m_pModel;						// ���f���f�[�^
	DWORD      m_numMat;						// �}�e���A����
	LPMaterial m_pMat;							// �}�e���A���ւ̃|�C���^
	//--------------------------------------------
	// [ ����Ǝ��̐ݒ� ]
	//--------------------------------------------
	float Buff;					// �o�t�@�ӂ��Ƃ΂���*1.12,�ړ����x*1.12
	float Debuff;				// �f�o�t �ӂ��Ƃ΂��ꗦ*1.12,�X�^�~�i����
	float Stamina;				// �X�^�~�i �̓�����,�W�����v,�q�b�v�h���b�v�ŏ���
	bool JumpFlag;				// �W�����v���Ă��邩
	int life;					// ���C�t
	FACE_STATE FaceState;		// �X�^�~�i�ɂ���ăL�����̕\���ς���
	//TYPE Drop[LIFE_MAX * 4];	// �N�𗎂Ƃ�����
	//TYPE Droped[LIFE_MAX];		// �N�ɗ��Ƃ��ꂽ��
};

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
