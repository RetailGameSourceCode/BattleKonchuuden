/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  System Name   : INSECT POKEMON                                           */
/*  Machine & OS  : Sony PlayStation / PlayStation OS ( R3000 )              */
/*  Language      : GNU C                                                    */
/*                                                                           */
/*  File Contents : BATTLE SCENE                                             */
/*  File Attribute: HEADER                                                   */
/*  File Name     : BATTLE.H                                                 */
/*                                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#ifndef _BATTLE_H_
#define _BATTLE_H_

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PLAYER STRUCT                                                            */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	char	tmd[37000];	// TMDデータの最大
	char	cls[2048];	// CLSデータの最大
} P_BUFF;

typedef struct {
	short	status;
	short	chrno;
	u_char	reflect;
	u_char	model_col[3];
	task_a	render;
	MODEL	*mod;
	MOTION	*mot;
	P_BUFF	*buf;
	char	*motd;
	long	length;
	long	timer;					/* タイマー */
	long	totaltime;				/* 総時間 */
	VECTOR	start;					/* 始点 */
	VECTOR	terminal;				/* 終点 */
	u_short	lv;
	u_long	hp;
	u_long	hpmax;
	u_long	dp;
	u_long	dpmax;
	u_short	ap;
	u_short	apmax;
	u_short	aura;
	u_short	attack;
	u_short	deffence;
	u_short	hitrate;
	u_short	evasion;
	u_short	crank;
	u_short	arank;
	u_short	hpdisp;
	u_short	dpdisp;
	u_short	apdisp;
	u_short	hyper;
	u_short	power;
	short	command[5];
	u_short	size;
	u_short	hitpos;
	u_short	*seq;					/* 戦闘シーケンスデータ */
} P_MODEL;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  CAMERA PATH                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	short	time;
	VECTOR	p0;
	VECTOR	p1;
} PATH2;

typedef struct {
	short	time;
	VECTOR	p0;
	VECTOR	p1;
	VECTOR	p2;
} PATH3;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  ZANZO POSITION                                                           */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
typedef struct {
	short	no;
	VECTOR	ofs0;
	VECTOR	ofs1;
} Z_POS;

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  TASK NUMBER                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
enum {
	_screen_set,
	_vs_wait,
	_command_init,
	_command,
	_command_analyze,
	_win_demo,
	_fade_wait,
	_camera_set2,
	_camera_set4,
	_motion_wait,
	_motion_wait2,
	_goahead,
	_attack,
	_kumi,
	_nage,
	_tackle,
	_returnset,
	_floting,
	_rush,
	_rush_hit,
	_rush1,
	_rush2,
	_rush3,
	_rush4,
	_zoom,
	_renda,
	_rush_pass,
	_returnset2,
	_laser0,
	_laser1,
	_laser2,
	_laser3,
	_laser4,
	_laser5,
	_missile0,
	_missile1,
	_missile2,
	_ranbu,
	_aura_tame0,
	_aura_tame1,
	_aura_tame2,
	_dummy,
};

/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
/*  PLAYER WORK                                                              */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+--*/
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern  "C" {
#endif

extern u_char		BattleStatus;
extern u_char		ba_totalturn;
extern u_short		seq[100];
extern P_MODEL		*pp, *ep;
extern P_MODEL		player[2];
extern MODEL		model[2];
extern MOTION		motion[2];
extern MOTION_DATA	motbuf[2][FRAMEMAX];	/* モーションデータバッファ */
extern long			LightPos[XYZ];
extern short		eflt[RGB];
extern VECTOR		trans, pos[4];
extern Z_POS		*zp;
extern DRAWENV		env[2];
extern long			pp_distance;
extern int			DemoPlayTimer;

extern int Battle();
int hit_check();
int damage_set(short rate);
void dummy();
void screen_set();
void vs_wait();
void command_init();
void command();
void command_analyze();
void fade_wait();
void win_demo();
void goahead();
void camera_set2();
void camera_set4();
void at_field(VECTOR *cpos);
void hibana(u_short flag);
void hit_effect(u_short flag);
void attack();
void motion_wait();
void motion_wait2();
void returnset();
void floting();
void rush();
void rush1();
void rush2();
void rush3();
void rush4();
void nage();
void kumi();
void rush_hit();
void returnset2();
void tackle();
void renda();
void zoom();
void rush_pass();
void beam_pos();
void laser0();
void laser1();
void laser2();
void laser3();
void laser4();
void laser5();
void missile0();
void missile1();
void missile2();
void ranbu();
void aura_tame0();
void aura_tame1();
void aura_tame2();

extern const short next_motion[];
extern const Z_POS *zpos[];
extern const short keta4[];

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _BATTLE_H_ */
