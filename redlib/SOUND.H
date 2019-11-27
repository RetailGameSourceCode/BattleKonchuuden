/*ak_sound tools
*----------------------------------------------------------------------------
*/

#ifndef __SOUND_H__
#define __SOUND_H__

#define BGM_UP  		0			/* volume up*/
#define BGM_DOWN		1			/* volume down*/



extern void AK_TEST(void);
extern void AK_BGM(void);
extern void AK_CLOSE(short);
extern void	BGM_VOL_SET(void);
extern void BGM_VOL_0(void);
extern void XA_START(void);/*�|�[�Y�����w�`���ĊJ����*/
extern int XA_FADE(void);/*XA FADEOUT*/
extern int XA_CNT(void);

/*�ȏ�ԑ�e�X�g�֐�*/

extern void SOUND_I(void);/*�T�E���h������(��SE�f�[�^���[�h)*/

extern void SE_LOAD(short);/*�{�җpSE�f�[�^���[�h�֐�*/
/*�O�Ŗ{�җp�f�[�^�A�P�̓^�C�g���R�[���f�[�^*/

extern void SE_ENT(int);
extern void SE_CLR(int);
extern void SE_ALLCLR(void);

extern void BGM_LOAD(int);
extern int BGM_ENT(short);// �Ԃ茌�͌��݂̉��t���a�f�lNO��Ԃ��܂��B
extern void BGM_CLR(short);
extern void BGM_PAUSE(void);
extern void BGM_RENT(short);/*BGM���v���C*/
extern void BGM_FADE(int,short,long);

extern void DATA_CLOSE(short);/*�I�����f�[�^�N���[�Y�֐�*/
/*1�őS���N���[�Y 2�łr�d 3�łr�d�p���N���[�Y*/

extern void XA_CLR(void);/*XA�N���A*/
extern int XA_LOAD(int);/*�w�`�Đ�*/

extern int XA_SYNC(void);/*���̊֐��͖��t���[���Ă�*/
// �Ԃ�l�O�F������ �P�F�I��

// �T�E���h�f�[�^�N���[�Y��V�X�e�����I�����܂�
extern void SOUND_E(void);/*�T�E���h�V�X�e���I��*/
#endif