//==============================================================================
// タイトル     :   OpenALを利用したサウンドクラス
// ファイル名   :   saundAL.cpp
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/17
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/17 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードファイル
//==============================================================================
#include "soundAL.h"
#include <stdlib.h>

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================

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
CSoundAL* CSoundAL::m_pSoundAL = NULL;

//==============================================================================
// 関数名 : CSoundAL()
// 引数   : void
// 戻り値 : void
// 説明   : デフォルトコンストラクタ
//==============================================================================
CSoundAL::CSoundAL()
{
	m_pAudioSource   = NULL;
	m_numAudioSource = 0;
}

//==============================================================================
// 関数名 : bool Play( SOUND_LABEL label )
// 引数   : SOUND_LABEL label : 対象のラベル
// 戻り値 : bool型
// 説明   : 再生処理
//==============================================================================
bool CSoundAL::Play( SOUND_LABEL label )
{
	for( int i = 0 ; i < m_numAudioSource ; i++ )
	{
		// ソースの状態を取得
		ALint state;
		alGetSourcei( m_pAudioSource[ i ].source , AL_SOURCE_STATE , &state );

		// 停止中or初期化状態ならば、再生に使う
		if( state == AL_STOPPED || state == AL_INITIAL )
		{
			// パラメータ設定
			ALint loop = m_soundParam[ label ].nLoopCnt == -1 ? AL_TRUE : AL_FALSE;		// ループ再生フラグ

			alSourcei( m_pAudioSource[ i ].source , AL_BUFFER , m_audioData[ label ].buffer );
			alSourcei( m_pAudioSource[ i ].source , AL_LOOPING , loop );

			// 再生
			alSourcePlay( m_pAudioSource[ i ].source );
			m_pAudioSource[ i ].playLabel = label;				// ラベルをひも付けておく

			return true;	// 処理成功
		}
	}

	return false;			// 処理失敗
}

//==============================================================================
// 関数名 : bool Stop( SOUND_LABEL label )
// 引数   : SOUND_LABEL label : 対象のラベル
// 戻り値 : bool型
// 説明   : 停止処理
//==============================================================================
bool CSoundAL::Stop( SOUND_LABEL label )
{
	bool result = false;		// 処理結果

	for( int i = 0 ; i < m_numAudioSource ; i++ )
	{
		// 同一ラベル再生中のソースを全て停止させる
		if( m_pAudioSource[ i ].playLabel == label )
		{
			alSourceStop( m_pAudioSource[ i ].source );
			m_pAudioSource[ i ].playLabel = -1;				// ラベルの解除をする
			result = true;
		}
	}

	return result;		// 処理結果の返却
}

//==============================================================================
// 関数名 : bool Stop( void )
// 引数   : void
// 戻り値 : bool型
// 説明   : 停止処理( 全部 )
//==============================================================================
bool CSoundAL::Stop( void )
{
	for( int i = 0 ; i < m_numAudioSource ; i++ )
	{
		// 全てのソースに停止命令を流す
		alSourceStop( m_pAudioSource[ i ].source );
		m_pAudioSource[ i ].playLabel = -1;				// ラベルの解除をする
	}

	return true;
}

//==============================================================================
// 関数名 : CSoundAL* Create( int createAudioSourceNum )
// 引数   : int createAudioSourceNum : オーディオソース生成数( 多いほど音を複数鳴らせる )
// 戻り値 : CSoundAL*型
// 説明   : 生成処理
//==============================================================================
CSoundAL* CSoundAL::Create( int createAudioSourceNum )
{
	// インスタンス生成・初期化
	m_pSoundAL = new CSoundAL;

	if( m_pSoundAL->Init( createAudioSourceNum ) == false )
	{
		m_pSoundAL->Release();
		m_pSoundAL = NULL;
	}

	return m_pSoundAL;
}


//==============================================================================
// 関数名 : void Release( void )
// 引数   : void
// 戻り値 : void
// 説明   : 破棄処理
//==============================================================================
void CSoundAL::Release( void )
{
	// オーディオデータの破棄
	for( int i = 0 ; i < SOUND_LABEL_MAX ; i++ )
	{
		alDeleteBuffers( 1 , &m_audioData[ i ].buffer );
	}

	// オーディオソースの破棄
	if( m_pAudioSource != NULL )
	{
		for( int i = 0 ; i < m_numAudioSource ; i++ )
		{
			alDeleteSources( 1 , &m_pAudioSource[ i ].source );
		}

		delete[] m_pAudioSource;
		m_pAudioSource = NULL;
	}

	// OpenALの終了処理
	alutExit();

	// 自身の破棄
	delete this;
}

//==============================================================================
// 関数名 : bool Init( int createAudioSourceNum )
// 引数   : int createAudioSourceNum : オーディオソース生成数( 多いほど音を複数鳴らせる )
// 戻り値 : bool型
// 説明   : 初期化処理
//==============================================================================
bool CSoundAL::Init( int createAudioSourceNum )
{
	// OpenALの初期化
	alutInit( &__argc , __argv );

	// オーディオデータの生成
	for( int i = 0 ; i < SOUND_LABEL_MAX ; i++ )
	{
		m_audioData[ i ].buffer = alutCreateBufferFromFile( m_soundParam[ i ].pFileName );
	}

	// オーディオソースの生成
	m_pAudioSource = new AUDIO_SOUCE[ createAudioSourceNum ];

	for( int i = 0 ; i < createAudioSourceNum ; i++ )
	{
		alGenSources( 1 , &m_pAudioSource[ i ].source );
		m_pAudioSource[ i ].playLabel = -1;
	}

	m_numAudioSource = createAudioSourceNum;

	//alSourcei( g_source , AL_BUFFER , g_buffer );
	//alSourcei( g_source , AL_LOOPING , AL_TRUE );
	//alSourcePlay( g_source );

	return true;		// 処理成功
}

