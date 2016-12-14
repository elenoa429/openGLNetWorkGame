//==============================================================================
// タイトル     :   キャラクター基底クラス
// ファイル名   :   charcter.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/11/21
//==============================================================================

//==============================================================================
// 更新履歴: -2016/11/21 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include "scene.h"
#include "parentModelManagerGL.h"
#include "motionGL.h"
#include "collider3DSphere.h"

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CCharcter : public CScene
{
	//---------------------------------------------
	// [ 列挙型 ]
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
	// [ メンバ関数 ]
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
	// [ メンバ変数 ]
	//---------------------------------------------
protected:
	VECTOR3 m_pos;
	VECTOR3 m_rot;
	VECTOR3 m_rotMokuhyou;		// 目標の向き
	VECTOR3 m_scl;
	float m_Width;
	float m_Height;
	float m_Depth;
	VECTOR3 m_Atari;			// 当たり判定

	VECTOR3 m_mov;				// 移動力
	float m_axcel;				// 加速度
	float m_axcelAttack;		// アタック時の加速度
	VECTOR3 m_gensui;			// 移動の減衰値
	VECTOR3 m_gensuiAttack;		// アタック時の減衰値
	float m_jump;				// ジャンプ力
	float m_spinAxcel;			// 振り向きの加速度
	float m_spinGensui;			// 振り向きの減衰

	CHARCTER_TYPE m_type;						// プレイヤーの種類。見た目を決めるもの。
	int m_id;									// プレイヤーID。～Pのこと。
	int m_life;									// ライフ。残機のこと。

	ACTION_STATE m_actionState;					// 行動状態識別子
	HELTH_STATE m_helthState;					// ステータス状態識別子

	MATRIX m_mtxWorld;							// ワールドマトリクス

	CCollider3DSphere* m_pBoundingSphere;		// 球のバウンディングボリューム

	LPModel    m_pModel;						// モデルデータ
	DWORD      m_numMat;						// マテリアル数
	LPMaterial m_pMat;							// マテリアルへのポインタ
	//--------------------------------------------
	// [ 今作独自の設定 ]
	//--------------------------------------------
	float Buff;					// バフ　ふっとばし率*1.12,移動速度*1.12
	float Debuff;				// デバフ ふっとばされ率*1.12,スタミナ減少
	float Stamina;				// スタミナ 体当たり,ジャンプ,ヒップドロップで消費
	bool JumpFlag;				// ジャンプしているか
	int life;					// ライフ
	FACE_STATE FaceState;		// スタミナによってキャラの表情を変える
	//TYPE Drop[LIFE_MAX * 4];	// 誰を落としたか
	//TYPE Droped[LIFE_MAX];		// 誰に落とされたか
};

//==============================================================================
// プロトタイプ宣言
//==============================================================================
