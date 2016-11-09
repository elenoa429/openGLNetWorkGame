//==============================================================================
// タイトル     :   OpenALを利用したサウンドクラス
// ファイル名   :   saundAL.h
// 作成者       :   AT13B284 21 数藤凌哉
// 作成日       :   2016/06/17
//==============================================================================

//==============================================================================
// 更新履歴: -2016/06/17 数藤凌哉
//           ・制作開始
//==============================================================================

//==============================================================================
// インクルードガード
//==============================================================================
#pragma once

//==============================================================================
// インクルードファイル
//==============================================================================
#include "sound.h"

#include "al.h"
#include "alc.h"
#include "alut.h"

//==============================================================================
// ライブラリへのリンク設定
//==============================================================================
#pragma comment( lib , "OpenAL32.lib" )		// OpenAL用
#pragma comment( lib , "alut.lib" )			// ALUT用

//==============================================================================
// マクロ定義
//==============================================================================

//==============================================================================
// 構造体宣言
//==============================================================================

//==============================================================================
// クラス宣言
//==============================================================================
class CSoundAL : public CSound
{
	//---------------------------------------------
	// [ メンバ関数 ]
	//---------------------------------------------
public:
	// 取得処理
	static CSoundAL* GetSound( void ){ return m_pSoundAL; }

	// 再生処理
	virtual bool Play( SOUND_LABEL label );

	// 停止処理
	virtual bool Stop( SOUND_LABEL label );
	virtual bool Stop( void );

	// 生成処理
	static CSoundAL* Create( int createAudioSourceNum );

	// 破棄処理
	virtual void Release( void );

private:
	// 初期化処理
	virtual bool Init( int createAudioSourceNum );

private:
	// コンストラクタ
	CSoundAL();
	CSoundAL( const CSoundAL& ){};

	// デストラクタ
	~CSoundAL(){};

	// オペレーター
	void operator=( const CSoundAL& ){};

	//---------------------------------------------
	// [ メンバ変数 ]
	//---------------------------------------------
private:
	struct AUDIO_DATA
	{												/* ==オーディオデータ構造体== */
		ALuint buffer;									// オーディオデータバッファーの識別子
	};

	struct AUDIO_SOUCE
	{												/* ==オーディオソース構造体== */
		ALuint source;									// オーディオソース識別子
		int playLabel;									// 再生中のラベル
	};

	AUDIO_SOUCE* m_pAudioSource;					// オーディオソースへのポインタ
	int m_numAudioSource;							// オーディオソース生成個数

	AUDIO_DATA m_audioData[ SOUND_LABEL_MAX ];		// オーディオデータ

	static CSoundAL* m_pSoundAL;					// シングルトン用ポインタ
};

//==============================================================================
// プロトタイプ宣言
//==============================================================================
