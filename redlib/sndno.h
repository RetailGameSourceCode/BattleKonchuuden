#if !defined _SNDNO_H_
#define _SNDNO_H_

// SE&SEQ no header                         1998/10/23 by red


#define BGM         3
#define SE          2
#define ALL         1

/* XAの番号はxano.hへ移動しました*/



/****************************************************************************************
2.フィールドマップ・シミュレーション・戦闘のBGMのわけかた＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊

フィールドマップ　初日～10日        BGM_MAP2
                  11日～19日        BGM_MAP
                  20日～最終日      BGM_MAP3
                           
シミュレーション　一戦闘ごとに BGM_SIMU,BGM_SIMU2,BGM_SIMU3 を順番に
　　　　　　　　　(１ターンでもどってきて変えるわけではないです。)

戦闘                     ランダム...　(変えるかもしれません。)





3.シナリオ部分ＢＧＭコール表：基本的に終りの指定がないものはフェードアウトです。＊＊＊＊＊
　　　　　　　　　　　　　　空白は前のシーンからの続きで鳴らします。
　　　　　　　　　　　　　　nnn*は、nnnのシーン共通で鳴らします。
xano.hのコメント部の数字に対応しています


001             BGM_SCHOOL
002_1           BGM_HOME
002_2           BGM_ENJOY
003             BGM_NORMAL
004_1   
004_2           BGM_ANGRY
005
006             BGM_HOME
007*            BGM_DEPARTURE
008*            BGM_DEPARTURE
009*            BGM_DEPARTURE
010*            BGM_DEPARTURE
011*            BGM_DEPARTURE
012*            フィールドマップの曲、そのまま
013*            フィールドマップの曲、そのまま
014*            フィールドマップの曲、そのまま
015*            フィールドマップの曲、そのまま

017_1           off
017_2           BGM_HAPPY
018             BGM_ENJOY
019
020 
021             BGM_SAD
022
023
024*            BGM_HOME
025*            BGM_HOME
026_1           BGM_HOME
026_2           BGM_ENJOY
027             前に流れていたBGMをそのまま
028             前に流れていたBGMをそのまま
029             BGM_ANGRY
030             BGM_ANGRY
031             BGM_ANGRY
032             BGM_ANGRY
033             BGM_NORMAL
034             BGM_ENJOY
035_1           BGM_HOME
035_2           off
036*            BGM_ANGRY
037             BGM_LOST
038*            フィールドマップの曲、そのまま
039*            フィールドマップの曲、そのまま
040             フィールドマップの曲、そのまま
041             フィールドマップの曲、そのまま
042             BGM_POLICE
043 
044*            BGM_POLICE
045*            BGM_POLICE
046             BGM_POLICE
047_1           BGM_POLICE
047_2           BGM_LOST
048             BGM_POLICE
049
050
051             BGM_NORMAL
052*            フィールドマップの曲、そのまま
053             BGM_NORMAL
054             BGM_NORMAL
055             BGM_SAD
056
057             BGM_NORMAL
058             BGM_NORMAL
059             BGM_POLICE
060             BGM_ENJOY
061             マップ画面:フィールドマップの曲、そのまま
    イベント画面から:BGM_NORMAL
062    
063*            フィールドマップの曲、そのまま
064             フィールドマップの曲、そのまま
065             BGM_SCHOOL
066
067*            フィールドマップの曲、そのまま
068*            フィールドマップの曲、そのまま
069*            フィールドマップの曲、そのまま
070             フィールドマップの曲、そのまま
071             BGM_SCHOOL
072 
073             BGM_ENJOY
074             BGM_SAD
075*            フィールドマップの曲、そのまま
076*            フィールドマップの曲、そのまま
077             フィールドマップの曲、そのまま  
078             フィールドマップの曲、そのまま  
079             フィールドマップの曲、そのまま  
080             BGM_HOTARU
081
082             BGM_NORMAL
083             BGM_NORMAL
084             BGM_NORMAL  
085_1           BGM_ANGRY   
085_2           フィールドマップの曲、そのまま  
085_3           フィールドマップの曲、そのまま  
086             BGM_NORMAL
087             BGM_SAD
088             BGM_ENJOY
089             BGM_ENJOY
090             BGM_SHOP
091
092*            BGM_SHOP
093*            BGM_SHOP
094             BGM_SHOP
095             BGM_SHOP
096             BGM_SHOP
097             フィールドマップの曲、そのまま  
098             BGM_SHOP
099             BGM_SHOP
100             ペットショップに行ったらBGM_SHOPが鳴る
101             BGM_SHOP
102             BGM_ENJOY
103
104             BGM_SCHOOL
105
106             BGM_POLICE
107
108
109             BGM_ENJOY
110             BGM_SAD
111             off
112             BGM_SAD
113 
114             BGM_SAD
115             BGM_SAD
116_1   
116_2           off
116_3           BGM_LAST
117             BGM_EPILOGUE
118_1           BGM_EPILOGUE
118_2

スタッフロール　(XA_ED)

118_3           BGM_ENJOY

***************************************************************************************/


enum{// se02.vab
        SE_ATTACK1 = 0x00000000,            // 体当たり１
        SE_ATTACK2,                         // 体当たり２
        SE_ATTACK3,                         // 体当たり３
        SE_ATTACK4,                         // 体当たり４

        SE_DOWN1,                           // たたきつけ１
        SE_DOWN2,                           // たたきつけ２
        SE_DOWN3,                           // たたきつけ３

        SE_DASH1,                           // ダッシュ１
        SE_DASH2,                           // ダッシュ２
        SE_DASH3,                           // ダッシュ３

        SE_BARIA1,                          // バリア１
        SE_BARIA2,                          // バリア２
        SE_BEAM1,                           // ビーム１
        SE_CHARGE1,                         // チャージ１

        SE_CUR1,                            // カーソル移動1
        SE_CUR2,                            // カーソル移動2
        SE_CUR3,                            // カーソル移動3
        SE_NEXT,                            // 文字送り
        SE_OK1,                             // 決定1
        SE_OK2,                             // 決定2
        SE_OK3,                             // 決定3
        SE_CANCEL,                          // キャンセル
        SE_PAUSE,                           // ポーズ
        SE_TURN1,                           // ターン1
        SE_TURN2,                           // ターン2
        
        SE_TTURN,                           // タイトル文字反転
        SE_TSTOP,                           // タイトル文字ストップ
        SE_TMOVE,                           // タイトル文字移動
        
        SE_BREAK,                           // 画面割れ後崩れ
        SE_CRASH,                           // 対戦画面衝突音
        SE_LV_UP,                           // レベルアップ
// se01.vab
        SE_T_SHOUHEI,                       // タイトルコール正平
        SE_T_LILY,                          // タイトルコールリリー
// se03.vab
        SE_LV_UP_PDA1,                      // PDA用「いぇーい」
        SE_LV_UP_PDA2,                      // PDA用「やったあ」
};



enum{// seq no
        BGM_HOME        = 2,                            // メニュー、帰ってきた時
        BGM_ENJOY       = 5,                            // イベント 楽しい
        BGM_MAP         = 8,                            // フィールドマップ
        BGM_DEPARTURE   = 11,                           // メニュー、出発
        BGM_NORMAL      = 14,                           // イベント ノーマル
        BGM_SIMU        = 17,                           // シミュレーション用
        BGM_SEL         = 20,                           // 図鑑モード
        BGM_HAPPY       = 23,                           // イベント、喜び
        BGM_ANGRY       = 26,                           // イベント、怒り
        BGM_SAD         = 29,                           // イベント、哀しい
        BGM_LOST        = 32,                           // イベント、迷い
        BGM_SIMU2       = 35,                           // シミュレーション２
        BGM_MAP2        = 38,                           // フィールドマップ２
        BGM_CHAR_SEL    = 41,                           // キャラセレクト１
        BGM_SCHOOL      = 44,                           // イベント、学校
        BGM_POLICE      = 47,                           // イベント、おまわりさん
        BGM_HOTARU      = 50,                           // 蛍イベント
        BGM_LAST        = 53,                           // ラストイベント
        BGM_MAP3        = /*56*/ 59,                            // フィールドマップ３
        BGM_SIMU3       = /*59*/ 56,                            // シミュレーション３
        BGM_EPILOGUE    = 62,                           // イベント、エピローグ
// Oct 13th in the making sounds
        BGM_SHOP        = 67,                           // イベント、ペットショップ
};
#endif