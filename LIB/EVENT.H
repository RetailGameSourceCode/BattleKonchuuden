/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
/*  System Name   : 98025 "昆虫げー"                                       */
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
/*  マクロ & 置換                                                          */
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
/*  関数のプロトタイプ宣言                                                 */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
extern void event_flag_set(short iEventNo);
extern short event_flag_get(short iEventNo);     // イベントフラグゲット 
extern void event_flag_clear(void);              // イベントフラグクリア 
extern void event_init(void);                    // イベントイニシャライズ 
extern void event_ctrl(void);                    // イベントコントロール 
extern void evtdata_set(void);                   // イベントデータセット 
extern void request_event(short event);          // 指定イベント要求 
extern void request_event_data(short event);     // 指定イベントデータ要求 
extern void evt_data_judge(void);                // イベントデータ判断 
extern short get_s(void);                        // short get 
extern void evt_data_practice(void);             // イベントデータ実行 
extern void hit_event(short iEventno);           // 当り起動イベント 
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
/*  イベントデータ用マクロ定義                                             */
/*--+----1----+----2----+----3----+----4----+----5----+----6----+----7----+*/
//       COMMAND                     EXPLANATION           USAGE 
#define  EC_MES              0    // メッセージ表示        EC_MES(10) 
                                  // ※注   必ず EC_MES_WAIT で待つこと！ 飛びます！！ 
#define  EC_MES_WAIT         1    // メッセージ終了を待つ  EC_MES_WAIT 
#define  EC_MOVE             2    // 指定座標に移動        EC_MOVE(chara No, pos x, pos y) 
                                  //                       EC_MOVE(0, 20, 50) 
#define  EC_MOVE_WAIT        3    // 移動終了待ち          EC_MOVE_WAIT(0) 
#define  EC_MARK             4    // ジャンプ時のマーク    EC_MARK(0~15) 
#define  EC_ANG_SET          5    // SDキャラの向きを指定  EC_ANG_SET(No, way) 
                                  // way 0:左 1:左下 2:下 3:右下 4:右 5:右上 6:上 7:左上 
#define  EC_DEMO_COUNT_SET   6    // デモカウントセット    EC_DEMO_COUNT_SET(12) 
#define  EC_DEMO_COUNT_WAIT  7    // デモカウント待ち      EC_DEMO_COUNT_WAIT(20) 
#define  EC_FADE             8    // シーンを変えずに fade EC_FADE(syurui, In or Out, speed) 
                                  // syurui(1:白 2:黒) / In or Out(1:IN 2:OUT 3:STOP) / speed(0~255) 
#define  EC_FADE_WAIT        9    // FADE 待ち             EC_FADE_WAIT 
#define  EC_IF_DEMO_COUNT    10   // DEMO COUNT 条件分岐   EC_IF_DEMO_COUNT(a, b, c, d) 
                                  // if((demo_counter + a) b(SMALL or LARGE or EQU) c) goto d 
#define  EC_TC_SET           11   // 会話キャラセット      EC_TC_SET(LorR, 状態, キャラ種類, 目パチ) 
                                  // LorR(0 or 1) / 状態(0:NO DISP 1:IN 2:DISP 3:OUT) / 種類(表情番号) / 
#define  EC_TC_WAIT          12   // 会話キャラ待ち        EC_TC_WAIT(LorR(0:L 1:R), 0or2(0:NO DISP 2:DISP)) 
#define  EC_XA               13   // XA 呼び出し           EC_XA(XA_NAME) 
#define  EC_XA_WAIT          14   // XA 終了待ち           EC_XA_WAIT 
#define  EC_NEXT_PRCS        15   // 次のプロセスへ        EC_NEXT_PRCS(3) 
#define  EC_MP_LIM_CH        16   // map player lim ch     EC_MP_LIM_CH(0 or 1)
#define  EC_WPOS_SET         17   // world pos (画面) set  EC_WPOS_SET(X, 210) 
#define  EC_WPOS_ADD         18   // world pos add         EC_WPOS_ADD(X, 10) 
#define  EC_EXIT             19   // 抜ける                EC_EXIT 
#define  EC_POS              20   // map player pos set    EC_POS(chara No, x, y) 
#define  EC_IF_DAY           21   // 日にちで分岐          EC_IF_DAY(month, day, <or>or=, jump) 
#define  EC_JUMP             22   // マークへジャンプ      EC_JUMP(1) 
#define  EC_NEXT_EVENT       23   // 次のイベントへ        EC_NEXT_EVENT(2) 
#define  EC_MES_SET          24   // MESSAGE FILE SET      EC_MES_SET(0) <- 
// 0:ｱﾊﾟｰﾄ 1:ﾍﾟｯﾄ 2:ｺｳﾊﾞﾝ 3:ｺｳｴﾝ 4:ｲｴ 5:ｾﾝﾄｳｺﾞ 6:ﾍﾔ 7:ｼｮｳｶﾞｯｺｳ 8:ﾏﾁﾊｽﾞﾚ 9:ﾓｴﾉｲｴ 10:ﾕｷﾉｲｴ 11:SLG 
#define  EC_RESULT           25   // RESULT ON             EC_RESULT 
#define  EC_RESULT_WAIT      26   // RESULT WAIT           EC_RESULT_WAIT 
#define  EC_IF_PNO           27   // pcb.pno で分岐        EC_IF_PNO(pno, jump) 
#define  EC_NEXT_AREA        28   // prcs & area 移動      EC_NEXT_AREA(prcs No, area No) 
                                  // prcs 4:マップ画面 
#define  EC_PUSH_PAD_WAIT    29   // pad wait              EC_PUSH_PAD_WAIT 
#define  EC_MES_SENDT        30   // メッセージ時間送り    EC_MES_SENDT(30) <- frame wait 
                                  // 使用例
                                  // EC_MES(115) 
                                  // EC_MES_SENDT(30)       <- 30 frame 毎に送られます。(次ページも同じ) 
                                  // EC_MES_WAIT            <- wait しないと飛びます！！ 
#define  EC_DISP_CHECK       31   // 表示フラグセット      EC_DISP_CHECK(chara No, 1) <- 0:OFF / 1:ON 
#define  EC_IF_GET_EVENT     32   // EVENT FLAG を見て分岐 EC_IF_GET_EVENT(1020, 2) 
#define  EC_EVENT_SET        33   // イベントフラグセット  EC_EVENT_SET(-15) 
#define  EC_SHOP             34   // 虫屋でお買い物        EC_SHOP 
#define  EC_SHOP_WAIT        35   // お買い物終了待ち      EC_SHOP_WAIT 
#define  EC_RANDOM_SET       36   // ランダム発生          EC_RANDOM_SET(10)  <-  (0~10) 
                                  // EC_RANDOM_SET(2) <- 0 or 1 or 2 
#define  EC_IF_RANDOM        37   // ランダムを見て分岐    EC_IF_RANDOM(a, b, c) 
                                  // if((random a(SMALL or LARGE or EQU) b) goto c 
                                  // EC_RANDOM_SET(9) 
                                  // EC_IF_RANDOM(EQU, 5, 0) <- RANDOM が 5 なら 0 へ飛ぶ 
#define  EC_MAP_LOAD_WAIT    38   // マップロード終了待ち  EC_MAP_LOAD_WAIT 
#define  EC_NEXT_DAY         39   // 次の日へ              EC_NEXT_DAY 


#endif


