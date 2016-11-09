//==============================================================================
// �^�C�g��     :   OpenAL�𗘗p�����T�E���h�N���X
// �t�@�C����   :   saundAL.cpp
// �쐬��       :   AT13B284 21 ��������
// �쐬��       :   2016/06/17
//==============================================================================

//==============================================================================
// �X�V����: -2016/06/17 ��������
//           �E����J�n
//==============================================================================

//==============================================================================
// �C���N���[�h�t�@�C��
//==============================================================================
#include "soundAL.h"
#include <stdlib.h>

//==============================================================================
// ���C�u�����ւ̃����N�ݒ�
//==============================================================================

//==============================================================================
// �񋓌^�錾
//==============================================================================

//==============================================================================
// �}�N����`
//==============================================================================

//==============================================================================
// �\���̐錾
//==============================================================================

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================

//==============================================================================
// �O���[�o���錾
//==============================================================================

//==============================================================================
// �ÓI�ϐ�
//==============================================================================
CSoundAL* CSoundAL::m_pSoundAL = NULL;

//==============================================================================
// �֐��� : CSoundAL()
// ����   : void
// �߂�l : void
// ����   : �f�t�H���g�R���X�g���N�^
//==============================================================================
CSoundAL::CSoundAL()
{
	m_pAudioSource   = NULL;
	m_numAudioSource = 0;
}

//==============================================================================
// �֐��� : bool Play( SOUND_LABEL label )
// ����   : SOUND_LABEL label : �Ώۂ̃��x��
// �߂�l : bool�^
// ����   : �Đ�����
//==============================================================================
bool CSoundAL::Play( SOUND_LABEL label )
{
	for( int i = 0 ; i < m_numAudioSource ; i++ )
	{
		// �\�[�X�̏�Ԃ��擾
		ALint state;
		alGetSourcei( m_pAudioSource[ i ].source , AL_SOURCE_STATE , &state );

		// ��~��or��������ԂȂ�΁A�Đ��Ɏg��
		if( state == AL_STOPPED || state == AL_INITIAL )
		{
			// �p�����[�^�ݒ�
			ALint loop = m_soundParam[ label ].nLoopCnt == -1 ? AL_TRUE : AL_FALSE;		// ���[�v�Đ��t���O

			alSourcei( m_pAudioSource[ i ].source , AL_BUFFER , m_audioData[ label ].buffer );
			alSourcei( m_pAudioSource[ i ].source , AL_LOOPING , loop );

			// �Đ�
			alSourcePlay( m_pAudioSource[ i ].source );
			m_pAudioSource[ i ].playLabel = label;				// ���x�����Ђ��t���Ă���

			return true;	// ��������
		}
	}

	return false;			// �������s
}

//==============================================================================
// �֐��� : bool Stop( SOUND_LABEL label )
// ����   : SOUND_LABEL label : �Ώۂ̃��x��
// �߂�l : bool�^
// ����   : ��~����
//==============================================================================
bool CSoundAL::Stop( SOUND_LABEL label )
{
	bool result = false;		// ��������

	for( int i = 0 ; i < m_numAudioSource ; i++ )
	{
		// ���ꃉ�x���Đ����̃\�[�X��S�Ē�~������
		if( m_pAudioSource[ i ].playLabel == label )
		{
			alSourceStop( m_pAudioSource[ i ].source );
			m_pAudioSource[ i ].playLabel = -1;				// ���x���̉���������
			result = true;
		}
	}

	return result;		// �������ʂ̕ԋp
}

//==============================================================================
// �֐��� : bool Stop( void )
// ����   : void
// �߂�l : bool�^
// ����   : ��~����( �S�� )
//==============================================================================
bool CSoundAL::Stop( void )
{
	for( int i = 0 ; i < m_numAudioSource ; i++ )
	{
		// �S�Ẵ\�[�X�ɒ�~���߂𗬂�
		alSourceStop( m_pAudioSource[ i ].source );
		m_pAudioSource[ i ].playLabel = -1;				// ���x���̉���������
	}

	return true;
}

//==============================================================================
// �֐��� : CSoundAL* Create( int createAudioSourceNum )
// ����   : int createAudioSourceNum : �I�[�f�B�I�\�[�X������( �����قǉ��𕡐��点�� )
// �߂�l : CSoundAL*�^
// ����   : ��������
//==============================================================================
CSoundAL* CSoundAL::Create( int createAudioSourceNum )
{
	// �C���X�^���X�����E������
	m_pSoundAL = new CSoundAL;

	if( m_pSoundAL->Init( createAudioSourceNum ) == false )
	{
		m_pSoundAL->Release();
		m_pSoundAL = NULL;
	}

	return m_pSoundAL;
}


//==============================================================================
// �֐��� : void Release( void )
// ����   : void
// �߂�l : void
// ����   : �j������
//==============================================================================
void CSoundAL::Release( void )
{
	// �I�[�f�B�I�f�[�^�̔j��
	for( int i = 0 ; i < SOUND_LABEL_MAX ; i++ )
	{
		alDeleteBuffers( 1 , &m_audioData[ i ].buffer );
	}

	// �I�[�f�B�I�\�[�X�̔j��
	if( m_pAudioSource != NULL )
	{
		for( int i = 0 ; i < m_numAudioSource ; i++ )
		{
			alDeleteSources( 1 , &m_pAudioSource[ i ].source );
		}

		delete[] m_pAudioSource;
		m_pAudioSource = NULL;
	}

	// OpenAL�̏I������
	alutExit();

	// ���g�̔j��
	delete this;
}

//==============================================================================
// �֐��� : bool Init( int createAudioSourceNum )
// ����   : int createAudioSourceNum : �I�[�f�B�I�\�[�X������( �����قǉ��𕡐��点�� )
// �߂�l : bool�^
// ����   : ����������
//==============================================================================
bool CSoundAL::Init( int createAudioSourceNum )
{
	// OpenAL�̏�����
	alutInit( &__argc , __argv );

	// �I�[�f�B�I�f�[�^�̐���
	for( int i = 0 ; i < SOUND_LABEL_MAX ; i++ )
	{
		m_audioData[ i ].buffer = alutCreateBufferFromFile( m_soundParam[ i ].pFileName );
	}

	// �I�[�f�B�I�\�[�X�̐���
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

	return true;		// ��������
}

