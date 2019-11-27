/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : POLYGON MODEL/MOTION ENGINE                              */
/*  File Attribute: HEADER                                                   */
/*  File Name     : MODEL.H                                                  */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _MODEL_H_
#define _MODEL_H_

/*----- Language Header Files -----*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  OBJECT MAX                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define OBJECTMAX	(43)					/* �P���f���ɑ΂���ő�I�u�W�F�N�g�� */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MODEL DATA INFORMATION                                                   */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	short			status;					/* ���f���̃X�e�[�^�X */
	u_long			attribute;				/* ���f���S�̂̃A�g���r���[�g */
	short			Objnum;					/* ���f�����O�f�[�^�̃I�u�W�F�N�g�̐���ێ����� */
	long			pos[XYZ];				/* ���f���̍��W�n */
	short			ang[XYZ];				/* ���W�n����邽�߂̃��[�e�[�V�����x�N�^�[ */
//	long			scl[XYZ];				/* ���f���̃X�P�[�� */
	long			trans[XYZ];				/* ���[�V�����̃g�����X */
	GsDOBJ2			object[OBJECTMAX];		/* �I�u�W�F�N�g�n���h�� �I�u�W�F�N�g�̐������K�v */
	GsCOORDINATE2	objpos[OBJECTMAX];		/* �I�u�W�F�N�g���Ƃ̍��W�n */
	SVECTOR			objang[OBJECTMAX];		/* ���W�n����邽�߂̃��[�e�[�V�����x�N�^�[ */
//	VECTOR			objscl[OBJECTMAX];		/* �I�u�W�F�N�g�̃X�P�[�� */
} MODEL ;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MODEL ATTRIBUTE INFORMATION                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define OBJ_NBLEND	(GsALON | GsAZERO)		/* ������ */
#define OBJ_ABLEND	(GsALON | GsAONE)		/* ���Z */
#define OBJ_HBLEND	(GsALON | GsATWO)		/* ���Z */
#define OBJ_SBLEND	(GsALON | GsATHREE)		/* �����Z */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  KAISOU DATA ( CLS FILE ) INFORMATION                                     */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	short			exist;					/* �I�u�W�F�N�g�����݂��邩�H�i�P����A�O���Ȃ��j */
	short			parts_no;				/* �I�u�W�F�N�g�̃p�[�c�i���o�[ */
	short			super;					/* �e�I�u�W�F�N�g�̔ԍ�(PARENT��WORLD) */
	short			ang[XYZ];				/* �A���O�� */
	long			pos[XYZ];				/* �g�����X�f�[�^ */
	long			scl[XYZ];				/* �X�P�[�� */
} KAISOU;

#define EXIST		(1)
#define NOT_EXIST	(0)
#define PARENT		(-1)

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOTION MAX                                                               */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#define FRAMEMAX	(144)					/* ���[�V�����̍ő�t���[���� */

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOTION DATA INFORMATION                                                  */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	long			pos[XYZ];				/* ���[�g�I�u�W�F�N�g�̃g�����X */
	short			ang[OBJECTMAX][XYZ];	/* �I�u�W�F�N�g���Ƃ̃A���O�� */
} MOTION_DATA;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  MOTION INFORMATION                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	u_short			num;					/* ���[�V�����i���o�[ */
	u_short			frame;					/* ���[�V�����̑��t���[���� */
	u_short			parts;					/* ���f���̃p�[�c�� */
	u_short			count;					/* ���[�V�����̃t���[���� */
	short			loop;					/* ���[�v�J�E���^ */
	int				*otbl;					/* �I�u�W�F�N�g�i���o�[�e�[�u�� */
	MOTION_DATA		*bufp;					/* ���[�V�����f�[�^�o�b�t�@ */
} MOTION;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CAMERA INFORMATION                                                       */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	GsRVIEW2		view;					/* ���_��ݒ肷�邽�߂̍\���� */
	GsCOORDINATE2	DView;					/* ���_���Ԃ牺������W�n */
	int				mode;					/* ���[�h */
	short			angle;					/* �A���O�� */
	SVECTOR			svec;					/* �x�N�g�� */
	long			*work;					/* �^�[�Q�b�g�̃��[�N */
	long			timer;					/* �^�C�}�[ */
	long			totaltime;				/* ������ */
	VECTOR			start;					/* �n�_ */
	VECTOR			relay;					/* ���p�_ */
	VECTOR			terminal;				/* �I�_ */
} CAMERA;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PROTOTYPE DIFINITIONS                                                    */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern GsF_LIGHT	pslt[3];				/* ���s������ݒ肷�邽�߂̍\���� */
extern GsRVIEW2		view;					/* ���_��ݒ肷�邽�߂̍\���� */
extern u_short		Projection;				/* �v���W�F�N�V���� */
extern u_char		reflect;				/* ���˗� */
extern CAMERA		cam;					/* �J���� */
extern u_char		model_col[RGB];			/* �J���[�|���S���F�w�� */
extern u_short		tpage;					/* �e�N�X�`���y�[�W�w�� */

extern void model_sort(MODEL *mod, u_char rfl);
extern void motion_init(u_char *adr, MOTION *mot, u_short num, short loop);
extern void motion_test(MODEL *mod, MOTION *mot);
extern void camera_init();
extern void camera_move();
extern void light_init();
extern void fog_init();
extern void model_init(long *tmd, MODEL *mod);
extern void coord_init(KAISOU *cls, MODEL *mod);
extern void jt_init4();						/* �`����̏����� */
extern void jt_smnlset();					/* ���}�b�s���O( LIGHT OFF )�̓o�^ */
extern void jt_smlset();					/* ���}�b�s���O( LIGHT ON  )�̓o�^ */
extern void jt_smsplset();					/* ���}�b�s���O( ���F )�̓o�^ */
extern void jt_smsp3lset();					/* ���}�b�s���O( �N���c�� )�̓o�^ */
extern void jt_smsp4lset();					/* ���}�b�s���O( �`���[ )�̓o�^ */
extern void jt_wireset();					/* ���C���[�t���[���̓o�^ */
extern void jt_colorset();					/* �J���[�|���S��( LIGHT OFF )�̓o�^ */
extern void jt_colorcset();					/* �J���[�|���S��( LIGHT ON  )�̓o�^ */
extern void jt_tpageset();					/* TPAGE�t���|���S���̓o�^ */
extern void jt_opticsset();					/* ���w���ʂ̓o�^ */
extern void jt_wire2set();					/* ���C���[�t���[���i���Z�j */
extern void jt_glassset();					/* �K���X�̓o�^ */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _MODEL_H_ */
