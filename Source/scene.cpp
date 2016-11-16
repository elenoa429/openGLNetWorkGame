//==============================================================================
// タイトル     :   シーンクラス
// ファイル名   :   scene.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/04/19
//==============================================================================

//==============================================================================
// 更新履歴: -2016/04/19 数藤凌哉
//           ・制作開始
//           -2016/05/16
//           ・リスト構造の管理機構を作成
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "scene.h"
#include "main.h"

//==============================================================================
// 列挙型宣言
//==============================================================================

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// プロトタイプ宣言
//==============================================================================

//==============================================================================
// グローバル宣言
//==============================================================================

//==============================================================================
// 静的変数
//==============================================================================
CScene* CScene::m_pTop[ PRIORITY_TYPE_MAX ] = { NULL };
CScene* CScene::m_pCur[ PRIORITY_TYPE_MAX ] = { NULL };

//==============================================================================
// 関数名 : CScene( int priority , OBJ_TYPE type )
// 引数   : int priority  : 描画優先度
//          OBJ_TYPE type : シーンタイプ
// 戻り値 : void
// 説明   : 引数付きコンストラクタ
//==============================================================================
CScene::CScene( int priority , OBJ_TYPE type )
{
	//--------------------------------------
	// [ インスタンスをリストに登録する ]
	//--------------------------------------
	LinkList( priority );

	//--------------------------------------
	// [ 変数初期化 ]
	//--------------------------------------
	m_priority = priority;
	m_type     = type;
}

//==============================================================================
// 関数名 : ~CScene()
// 引数   : void
// 戻り値 : void
// 説明   : デストラクタ
//==============================================================================
CScene::~CScene()
{
}

//==============================================================================
// 関数名 : void UpdateAll( void )
// 引数   : void
// 戻り値 : void
// 説明   : リストに登録されたインスタンス全ての更新処理
//==============================================================================
void CScene::UpdateAll( void )
{
	for( int i = 0 ; i < PRIORITY_TYPE_MAX ; i++ )
	{
		CScene *pCur = m_pTop[ i ];			// 現在参照しているポインタ
		CScene *pNext;						// 次に参照するポインタ

		while( pCur != NULL )				// リスト全てを参照するまで繰り返し
		{
			pNext = pCur->m_pNext;			// 次へのポインタを保持
			pCur->Update();					// 更新処理の呼び出し
			pCur = pNext;					// 次へのポインタを現在のポインタに格納
		}
	}
}

//==============================================================================
// 関数名 : void DrawAll( void )
// 引数   : void
// 戻り値 : void
// 説明   : リストに登録されたインスタンス全ての描画処理
//==============================================================================
void CScene::DrawAll( void )
{
	for( int i = 0 ; i < PRIORITY_TYPE_MAX ; i++ )
	{
		CScene *pCur = m_pTop[ i ];			// 現在参照しているポインタ
		CScene *pNext;						// 次に参照するポインタ

		while( pCur != NULL )				// リスト全てを参照するまで繰り返し
		{
			pNext = pCur->m_pNext;			// 次へのポインタを保持
			pCur->Draw();					// 描画処理の呼び出し
			pCur = pNext;					// 次へのポインタを現在のポインタに格納
		}
	}
}

//==============================================================================
// 関数名 : void ReleaseAll( void )
// 引数   : void
// 戻り値 : void
// 説明   : リストに登録されたインスタンス全ての解放処理
//==============================================================================
void CScene::ReleaseAll( void )
{
	for( int i = 0 ; i < PRIORITY_TYPE_MAX ; i++ )
	{
		CScene *pCur = m_pTop[ i ];			// 現在参照しているポインタ
		CScene *pNext;						// 次に参照するポインタ

		while( pCur != NULL )				// リスト全てを参照するまで繰り返し
		{
			pNext = pCur->m_pNext;			// 次へのポインタを保持
			pCur->Uninit();					// 終了処理の呼び出し
			delete pCur;					// インスタンスの削除
			pCur = pNext;					// 次へのポインタを現在のポインタに格納
		}

		m_pTop[ i ] = NULL;					// 先頭ポインタのNULL埋め
		m_pCur[ i ] = NULL;					// 末尾ポインタのNULL埋め
	}
}

//==============================================================================
// 関数名 : void Release( void )
// 引数   : void
// 戻り値 : void
// 説明   : 解放処理
//==============================================================================
void CScene::Release( void )
{
	UnlinkList( m_priority );		// リストから解放
	this->Uninit();					// 終了処理の呼び出し
	delete this;					// インスタンス削除
}

//==============================================================================
// 関数名 : void LinkList( int priority )
// 引数   : int priority : 描画優先度
// 戻り値 : void
// 説明   : リストへインスタンスを登録する処理
//==============================================================================
void CScene::LinkList( int priority )
{
	// リストに初めて自身を登録するとき
	if( m_pTop[ priority ] == NULL )
	{
		m_pTop[ priority ] = this;				// 自身しかいない＝先頭にあたるため
	}

	if( m_pCur[ priority ] == NULL )
	{
		m_pCur[ priority ] = this;				// 自身しかいない＝最後尾にあたるため
	}

	// リストのリンク処理
	m_pCur[ priority ]->m_pNext = this;			// 現在最後尾にあたる部分のNextを自身に設定

	if( m_pCur[ priority ] == this )
	{
		m_pPrev = NULL;							// 自身しかいない＝前にリストが存在しないため
	}
	else
	{
		m_pPrev = m_pCur[ priority ];			// 最後尾が自身になるため
	}

	m_pCur[ priority ] = this;					// 最後尾を自身に登録
	m_pNext = NULL;								// 次はまだ存在しないため
}

//==============================================================================
// 関数名 : void UnlinkList( int priority )
// 引数   : int priority : 描画優先度
// 戻り値 : void
// 説明   : リストのインスタンスを削除する処理
//==============================================================================
void CScene::UnlinkList( int priority )
{
	// 前にあるインスタンスに対する処理
	if( this == m_pTop[ priority ] )
	{
		m_pTop[ priority ] = m_pNext;
	}
	else
	{
		m_pPrev->m_pNext = m_pNext;		// 前にあるインスタンスに、自身の次のインスタンスへのポインタを登録
	}

	// 次にあるインスタンスに対する処理
	if( this == m_pCur[ priority ] )
	{
		m_pCur[ priority ] = m_pPrev;
	}
	else
	{
		m_pNext->m_pPrev = m_pPrev;		// 次にあるインスタンスに、自身の前のインスタンスへのポインタを登録
	}
}
