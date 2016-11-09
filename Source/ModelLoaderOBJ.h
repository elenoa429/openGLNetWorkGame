//==============================================================================
// タイトル     :   OBJファイルからのモデル読み込み処理用クラス
// ファイル名   :   ModelLoaderOBJ.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/11
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/11 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include "materialBuffer.h"
#include "model.h"

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CModelLoaderOBJ
{
	//---------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------
public:
	// 読み込み処理
	bool ModelLoadOBJ( char* pFileName , CMaterialBuffer** ppMaterials , DWORD* pNumMaterials , CModel** ppModelMesh );

	//---------------------------------------------
	// [ メンバ変数 ]
	//---------------------------------------------
};

//==============================================================================
// プロトタイプ宣言
//==============================================================================

