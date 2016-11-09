//==============================================================================
// タイトル     :   デバッグプロシージャ
// ファイル名   :   debugProc.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/05/20
//==============================================================================

//==============================================================================
// 更新履歴: -2016/05/20 数藤凌哉
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
#include "font.h"

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CDebugProc
{
	/* ===メンバ関数=== */
public:
	static CDebugProc* GetDebugProc( void ){		// インスタンス取得処理
		return pDebugProc;
	}

	static void Create( void );						// 生成処理
	static void Release( void );					// 解放処理

	virtual bool Init( void );						// 初期化処理
	virtual void Uninit( void );					// 終了処理
	virtual void Update( void );					// 更新処理
	virtual void Draw( void );						// 描画処理

	bool PrintDebugProc( char *fmt , ... );			// 出力バッファーへの書き込み

private:
	CDebugProc();									// デフォルトコンストラクタ
	~CDebugProc();									// デストラクタ
	CDebugProc( const CDebugProc& );				// コピーコンストラクタ
	void operator=( const CDebugProc& );			// オペレーター

	/* ===メンバ変数=== */
private:
	static CDebugProc* pDebugProc;		// デバッグプロシージャへのポインタ

	CFont* m_pFont;						// フォントへのポインタ

};

//==============================================================================
// プロトタイプ宣言
//==============================================================================
