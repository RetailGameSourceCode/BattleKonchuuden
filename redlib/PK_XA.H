//
//
//	PS XA Driver Ver 1.0
//
//


#if !defined _PK_XA_H_
#define		_PK_XA_H_

#include	<kernel.h>
#include	<sys/types.h>
#include	<libsnd.h>
#include	<libcd.h>

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

typedef struct {
	char				sfno;						// XA file No
	char				ch;							// XA Ch No
	char				offset;						// start sector offset
	char				vol;						// Play Volume
	unsigned short		time;						// Play time
	char				pad0,pad1;
} XA_DATA;

#define	s_char	signed char

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

enum {
	 XA_WM_READY= 0
	,XA_WM_PLAY
};

#define		SCTSIZE	2336
#define		RNGSIZE	1

/* ---  XA size �� �t���[�����ϊ��萔  ���ʂ͕t���Ă̓_���ł� ---------- */

#define		XATIME	8 * 60 / 75 / 2336
// ���L�̃}�N����czarmac.h S2F()�ƃo�b�e�B���O����̂ŃR�����g�A�E�g�i��{�I�ɒ��l�Ȃ̂Ŗ��Ȃ��j 
//#define		S2F		8*60/75/SCTSIZE
#define		s2f(x)	((x)*8*60/75/SCTSIZE)

/* -------------------------------------------------------------------- */

extern volatile s_char	xa_working_mode;

void	XaInit(CdlLOC xa_loc[], XA_DATA xa_data[], char *buff);
void	XaVSyncJob(void );
int		XaSeekS(int xa_no);
void	xa_seek(int	xa_no);
void	xa_stop(void );
void	set_xa_mode(void );

// 1997/10/01 append by Czar 
extern volatile int	xa_vsync_f;
extern volatile s_char	xa_working_mode;
extern volatile int	xa_error;
extern volatile int	xa_flame;
extern volatile int	xa_time_work;

#define CDDATA_READ_CLOSE() \
{\
	SsSetSerialVol(SS_SERIAL_A, 0,0);\
	xa_vsync_f= 0;\
	CdReadyCallback(NULL);\
	CdSyncCallback(NULL);\
	CdControl(CdlPause, NULL,NULL);\
	xa_flame= -1;\
	xa_working_mode= XA_WM_READY;\
	xa_error= 0;\
}

// end of append by Czar

#define	XaPlay(xa_no)		xa_seek(xa_no)
#define	XaStop()			xa_stop()
#define	XaModeSet()			set_xa_mode()
#define	XaSeek(xa_no)		XaSeekS(xa_no)

#endif








#if 0

XaInit		XA�V�X�e��������(�t�@�C���ݒ�)
			XA�V�X�e�����g�p����ɂ�����n�߂ɌĂ�ł����B

	�`��	void		XaInit(CdlLOC xa_loc[], XA_DATA xa_data[], char *buff)

	����	xa_loc[]	�t�@�C���|�W�V�����z��擪�A�h���X
						�S xa_loc[]�̓f�[�^���ݒ肳��Ă���K�v������܂��B
yy
			xa_data[]	XA �����f�[�^
						�S xa_data[] �̓f�[�^���ݒ肳��Ă���K�v������܂��B

			buff		SCTSIZE*RNGSIZE byte���̓ǂ݂����o�b�t�@

XaVSyncJob	�Đ����ԊǗ�
			XaInit()�� 1/60sec �̊��荞�݂��g�p���� �Ăё�����B

	�`��	void		XaVSyncJob(void )



XaModeSet	CD�V�X�e����XA �Đ����[�h�ɐݒ肷��B
			 �n�߂āA���邢�� CD����̃f�[�^���[�h,DA�Đ��� �� XA���Đ�����Ƃ�
			�ɂ��炩���ߌĂ�ł��� (�u���b�N����܂�)

	�`��	void		XaModeSet(void )






XaPlay		XA�Đ�

	�`��	void		XaPlay(int xa_no)

	����	xa_no		XA No





XaSeek		XA No�ɂ��V�[�N���N�G�X�g�𔭍s����B
		(CdControlF()�g�p,��n��(�G���[����,�V�[�N�I���m�F��)�̓��[�U������B)

	�`��	void		XaSeek(int xa_no)

	����	xa_no		XA No





XaStop		XA�����I��

	�`��	void		XaStop(void )


#endif
