//==============================================================================
// タイトル     :   バッファー基底クラス
// ファイル名   :   buffer.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/06
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/06 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include <Windows.h>

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CBuffer
{
	//---------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------
public:
	// 解放処理
	virtual void Release( void ) = 0;

	// プライベートデータ取得
	virtual bool GetPrivateData( void** ppData , DWORD* pSizeOfData ) = 0;

	// プライベートデータ設定
	virtual bool SetPrivateData( void* pData , DWORD sizeOfData ) = 0;

	//---------------------------------------------
	// [ メンバ変数 ]
	//---------------------------------------------

};

typedef class CBuffer* LPBuffer;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
