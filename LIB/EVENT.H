/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  System Name   : 98025 "�������["                                       */
/*  Machine & OS  : Sony Play Station                                      */
/*  Language      : GNU C                                                  */
/*                                                                         */
/*  File Contents : 2D MAP EVENT                                           */
/*  File Name     : event.h                                                */
/*                                                           by H.TATEYAMA */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#ifndef _EVENT_H_
#define _EVENT_H_


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  �}�N�� & �u��                                                          */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
#define       MAX_AREA            61
#define       MAX_AREA_EVENT      256
#define       EVTWAIT             0
#define       EVTJUDGE            1
#define       EVTPRACTICE         2
#define       EVTINIT             3
#define       EVT_COMMAND_MAX     151

enum {
    EQU,
    SMALL,
    LARGE,
    CUT,
};



/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*                                                                         */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern char             cEventOn, cEvtReqPerm, cEvtFade, cHitEvent;
extern short            request_event_no;


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  �֐��̃v���g�^�C�v�錾                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern void event_flag_set(short iEventNo);
extern short event_flag_get(short iEventNo);     // �C�x���g�t���O�Q�b�g 
extern void event_flag_clear(void);              // �C�x���g�t���O�N���A 
extern void event_init(void);                    // �C�x���g�C�j�V�����C�Y 
extern void event_ctrl(void);                    // �C�x���g�R���g���[�� 
extern void evtdata_set(void);                   // �C�x���g�f�[�^�Z�b�g 
extern void request_event(short event);          // �w��C�x���g�v�� 
extern void request_event_data(short event);     // �w��C�x���g�f�[�^�v�� 
extern void evt_data_judge(void);                // �C�x���g�f�[�^���f 
extern short get_s(void);                        // short get 
extern void evt_data_practice(void);             // �C�x���g�f�[�^���s 
extern void hit_event(short iEventno);           // ����N���C�x���g 
extern void gp_print(short iSta);                // GREAT POOR DISP 
extern void ec_mes(void);
extern void ec_mes_wait(void);
extern void ec_move(void);
extern void ec_move_wait(void);
extern void ec_mark(void);
extern void ec_ang_set(void);
extern void ec_demo_count_set(void);
extern void ec_demo_count_wait(void);
extern void ec_fade(void);
extern void ec_fade_wait(void);
extern void ec_if_demo_count(void);
extern void ec_tc_set(void);
extern void ec_tc_wait(void);
extern void ec_xa(void);
extern void ec_xa_wait(void);
extern void ec_next_prcs(void);
extern void ec_mp_lim_ch(void);
extern void ec_wpos_set(void);
extern void ec_wpos_add(void);
extern void ec_exit(void);
extern void ec_pos(void);
extern void ec_if_day(void);
extern void ec_jump(void);
extern void ec_next_event(void);
extern void ec_mes_set(void);
extern void ec_result(void);
extern void ec_result_wait(void);
extern void ec_if_pno(void);
extern void ec_next_area(void);
extern void ec_push_pad_wait(void);
extern void ec_mes_sendt(void);
extern void ec_disp_check(void);
extern void ec_if_get_event(void);
extern void ec_event_set(void);
extern void ec_shop(void);
extern void ec_shop_wait(void);
extern void ec_random_set(void);
extern void ec_if_random(void);
extern void ec_map_load_wait(void);
extern void ec_next_day(void);

void get_pos12(FIXED pos[XYZ]);           // 12 bit shift


/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  �C�x���g�f�[�^�p�}�N����`                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
//       COMMAND                     EXPLANATION           USAGE 
#define  EC_MES              0    // ���b�Z�[�W�\��        EC_MES(10) 
                                  // ����   �K�� EC_MES_WAIT �ő҂��ƁI ��т܂��I�I 
#define  EC_MES_WAIT         1    // ���b�Z�[�W�I����҂�  EC_MES_WAIT 
#define  EC_MOVE             2    // �w����W�Ɉړ�        EC_MOVE(chara No, pos x, pos y) 
                                  //                       EC_MOVE(0, 20, 50) 
#define  EC_MOVE_WAIT        3    // �ړ��I���҂�          EC_MOVE_WAIT(0) 
#define  EC_MARK             4    // �W�����v���̃}�[�N    EC_MARK(0~15) 
#define  EC_ANG_SET          5    // SD�L�����̌������w��  EC_ANG_SET(No, way) 
                                  // way 0:�� 1:���� 2:�� 3:�E�� 4:�E 5:�E�� 6:�� 7:���� 
#define  EC_DEMO_COUNT_SET   6    // �f���J�E���g�Z�b�g    EC_DEMO_COUNT_SET(12) 
#define  EC_DEMO_COUNT_WAIT  7    // �f���J�E���g�҂�      EC_DEMO_COUNT_WAIT(20) 
#define  EC_FADE             8    // �V�[����ς����� fade EC_FADE(syurui, In or Out, speed) 
                                  // syurui(1:�� 2:��) / In or Out(1:IN 2:OUT 3:STOP) / speed(0~255) 
#define  EC_FADE_WAIT        9    // FADE �҂�             EC_FADE_WAIT 
#define  EC_IF_DEMO_COUNT    10   // DEMO COUNT ��������   EC_IF_DEMO_COUNT(a, b, c, d) 
                                  // if((demo_counter + a) b(SMALL or LARGE or EQU) c) goto d 
#define  EC_TC_SET           11   // ��b�L�����Z�b�g      EC_TC_SET(LorR, ���, �L�������, �ڃp�`) 
                                  // LorR(0 or 1) / ���(0:NO DISP 1:IN 2:DISP 3:OUT) / ���(�\��ԍ�) / 
#define  EC_TC_WAIT          12   // ��b�L�����҂�        EC_TC_WAIT(LorR(0:L 1:R), 0or2(0:NO DISP 2:DISP)) 
#define  EC_XA               13   // XA �Ăяo��           EC_XA(XA_NAME) 
#define  EC_XA_WAIT          14   // XA �I���҂�           EC_XA_WAIT 
#define  EC_NEXT_PRCS        15   // ���̃v���Z�X��        EC_NEXT_PRCS(3) 
#define  EC_MP_LIM_CH        16   // map player lim ch     EC_MP_LIM_CH(0 or 1)
#define  EC_WPOS_SET         17   // world pos (���) set  EC_WPOS_SET(X, 210) 
#define  EC_WPOS_ADD         18   // world pos add         EC_WPOS_ADD(X, 10) 
#define  EC_EXIT             19   // ������                EC_EXIT 
#define  EC_POS              20   // map player pos set    EC_POS(chara No, x, y) 
#define  EC_IF_DAY           21   // ���ɂ��ŕ���          EC_IF_DAY(month, day, <or>or=, jump) 
#define  EC_JUMP             22   // �}�[�N�փW�����v      EC_JUMP(1) 
#define  EC_NEXT_EVENT       23   // ���̃C�x���g��        EC_NEXT_EVENT(2) 
#define  EC_MES_SET          24   // MESSAGE FILE SET      EC_MES_SET(0) <- 
// 0:��߰� 1:�߯� 2:����� 3:���� 4:�� 5:��ĳ�� 6:�� 7:����ޯ�� 8:��ʽ�� 9:Ӵɲ� 10:շɲ� 11:SLG 
#define  EC_RESULT           25   // RESULT ON             EC_RESULT 
#define  EC_RESULT_WAIT      26   // RESULT WAIT           EC_RESULT_WAIT 
#define  EC_IF_PNO           27   // pcb.pno �ŕ���        EC_IF_PNO(pno, jump) 
#define  EC_NEXT_AREA        28   // prcs & area �ړ�      EC_NEXT_AREA(prcs No, area No) 
                                  // prcs 4:�}�b�v��� 
#define  EC_PUSH_PAD_WAIT    29   // pad wait              EC_PUSH_PAD_WAIT 
#define  EC_MES_SENDT        30   // ���b�Z�[�W���ԑ���    EC_MES_SENDT(30) <- frame wait 
                                  // �g�p��
                                  // EC_MES(115) 
                                  // EC_MES_SENDT(30)       <- 30 frame ���ɑ����܂��B(���y�[�W������) 
                                  // EC_MES_WAIT            <- wait ���Ȃ��Ɣ�т܂��I�I 
#define  EC_DISP_CHECK       31   // �\���t���O�Z�b�g      EC_DISP_CHECK(chara No, 1) <- 0:OFF / 1:ON 
#define  EC_IF_GET_EVENT     32   // EVENT FLAG �����ĕ��� EC_IF_GET_EVENT(1020, 2) 
#define  EC_EVENT_SET        33   // �C�x���g�t���O�Z�b�g  EC_EVENT_SET(-15) 
#define  EC_SHOP             34   // �����ł�������        EC_SHOP 
#define  EC_SHOP_WAIT        35   // ���������I���҂�      EC_SHOP_WAIT 
#define  EC_RANDOM_SET       36   // �����_������          EC_RANDOM_SET(10)  <-  (0~10) 
                                  // EC_RANDOM_SET(2) <- 0 or 1 or 2 
#define  EC_IF_RANDOM        37   // �����_�������ĕ���    EC_IF_RANDOM(a, b, c) 
                                  // if((random a(SMALL or LARGE or EQU) b) goto c 
                                  // EC_RANDOM_SET(9) 
                                  // EC_IF_RANDOM(EQU, 5, 0) <- RANDOM �� 5 �Ȃ� 0 �֔�� 
#define  EC_MAP_LOAD_WAIT    38   // �}�b�v���[�h�I���҂�  EC_MAP_LOAD_WAIT 
#define  EC_NEXT_DAY         39   // ���̓���              EC_NEXT_DAY 


#endif


