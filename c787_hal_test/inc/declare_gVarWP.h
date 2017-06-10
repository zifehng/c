//Global Variables for program control
//and declare prototype of functions.

// General constants
#define DEF_PI			3.14159265	// π

// for warp table
#define DEF_WPTBLMAX_H	264			// ワーピング座標テーブル水平最大サイズ
#define DEF_WPTBLMAX_V	144			// ワーピング座標テーブル垂直最大サイズ

// for LUT of interpolation filter
#define DEF_LUTSYM		6			// 補間係数LUTシンボル数
#define DEF_LUTCUT_MAX	1.2			// 補間係数LUTカットオフ係数上限
#define DEF_LUTCUT_MIN	0.1			// 補間係数LUTカットオフ係数下限
#define DEF_LUTWIN_MAX	2.0			// 補間係数LUTウィンドウ係数上限
#define DEF_LUTWIN_MIN	0			// 補間係数LUTウィンドウ係数下限

// for Cursor
#define DEF_CURSIZE		16			// 4点カーソルサイズ
// for 8-point
#define	DEF_WPGDSIZE	16			// 8点グリッドサイズ

// for dummy
//#define	DEF_WPDMYHW		32			// ワーピングダミー領域幅
#define	DEF_WPDMYHW		0			// ワーピングダミー領域幅
									// 16dot間隔補正モードのみ使用時は16
									// 16 or 32dot間隔補正モード使用時は32
									// 出力パネルの外側に画像がはみ出すような補正を行わない場合は0を設定
// Error
#define DEF_WPERR_NGZ		(20)
#define DEF_WPERR_CURPOS	(30)	// 4点カーソル位置エラー



// Basic
extern int PM_WPDTMD;		// 16dot/32dot間隔補正モード(0:16dot, 1:32dot)

// H/V Keystone
extern float PM_WPKEYANG_H;	// 水平台形補正角度[deg]
extern float PM_WPKEYANG_V;	// 垂直台形補正角度[deg]
extern float WPKEYANG_H_OLD;	// 前の水平台形補正角度[deg]
extern float WPKEYANG_V_OLD;	// 前の垂直台形補正角度[deg]

typedef struct {
	float	axis;					// プロジェクタ光軸位置[%]
	float	dist;					// プロジェクタ投影距離[mm]
	float	vw;						// プロジェクタ投影画像垂直幅[mm]
} str_pjparam;
extern str_pjparam PM_PJPARAM;	// プロジェクタ光学系パラメータ
extern str_pjparam PJPARAM_OLD;	// 前のプロジェクタ光学系パラメータ

// 4-corner Keystone
typedef struct {
	int tl_x,tl_y;					// 4点指定座標左上(X,Y)
	int tr_x,tr_y;					// 4点指定座標右上(X,Y)
	int bl_x,bl_y;					// 4点指定座標左下(X,Y)
	int br_x,br_y;					// 4点指定座標右下(X,Y)
} str_wppos4c;
extern str_wppos4c PM_WPPOS4C;	// 4点指定座標
extern str_wppos4c WPPOS4C_OLD;	// 前の4点指定座標

// for warp table
extern float Px[DEF_WPTBLMAX_H][DEF_WPTBLMAX_V];	// ワーピング座標テーブルX
extern float Py[DEF_WPTBLMAX_H][DEF_WPTBLMAX_V];	// ワーピング座標テーブルY
extern int PHWNZ;			// round up 出力パネル水平画素数/16(32)
extern int PVWNZ;			// round up 出力パネル垂直画素数/16(32)
extern float PHWHF;			// 出力パネル水平画素数/2
extern float PVWHF;			// 出力パネル垂直画素数/2
extern int GPTx[3];		// グリッドデフォルトX座標
extern int GPTy[3];		// グリッドデフォルトY座標

// for warp table (Warp LUT Gen)
extern int HMIN;			
extern int my_VMIN;		

struct wpkey_param {
    float wpkey_ang_h;
    float wpkey_ang_v;
    str_pjparam pj_param;
    str_wppos4c wp_pos4c;
};


extern void InitWpTable(void);
extern void InitWpGrid(void);
extern int SetWpKey4c(str_wppos4c *p4c);
extern int SetCurPos(str_wppos4c *p4c);
extern void SetWpGrid(int gx, int gy, int chg);
extern void CalcHomography(str_wppos4c *p4c);
extern void WriteWpTable(void);
extern void SetLut(void);
extern void SetLut_wplg(void);
extern int Calc4Corner(float AngH, float AngV, str_pjparam *pjp, str_wppos4c *p4c);
extern int open_device();
extern unsigned int read_IWARP2(int ad, int ch_offset);
extern void write_IWARP2(int ad, int dt, int ch_offset, int force);
extern void wait1_povs(void);

typedef unsigned long ulong;

