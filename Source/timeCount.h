//==============================================================================
// タイトル     :   時間計測・表示クラス
// ファイル名   :   timeCount.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/20
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/20 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include "main.h"
#include "number2D.h"

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
class CTimeCount : public CScene
{
	//---------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------
public:
	CTimeCount();
	~CTimeCount();

	static CTimeCount* Create( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath = NULL );

	virtual bool Init( int numPlace , VECTOR3 pos , VECTOR3 size , int texDivW , int texDivH , char* texPath );
	virtual void Uninit( void );
	virtual void Update( void );
	virtual void Draw( void );

	void SetTime( int time , int delay = 60 );
	void SetColor( COLOR_F32 col );

	void SetOutputLeftZeroEnable( bool flags )
	{
		m_isOutputLeftZero = flags;
	}

	int GetTime( void ){ return m_time; }

private:
	void PrintTime( void );

	//---------------------------------------------
	// [ メンバ変数 ]
	//---------------------------------------------
protected:
	VECTOR3 m_pos;
	VECTOR3 m_rot;
	VECTOR3 m_size;
	COLOR_F32 m_col;

	CTexture* m_pTexture;								// テクスチャへのポインタ
	CNumber2D** m_ppNumber;								// 数字処理へのダブルポインタ
	int m_numPlace;										// 桁数( =上の処理の生成数のこと )

	int m_time;											// 現在時刻
	int m_timeCnt;										// 時間のずらすカウンタ
	int m_timeDelay;									// 時刻がずれるまでに必要な時間

	bool m_isOutputLeftZero;							// 左に0があった時に表示するorしないを判定
};

//==============================================================================
// プロトタイプ宣言
//==============================================================================
