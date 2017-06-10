//Global Variables for program control
//and declare prototype of functions.

// General constants
#define DEF_PI			3.14159265	// ��

// for warp table
#define DEF_WPTBLMAX_H	264			// ���[�s���O���W�e�[�u�������ő�T�C�Y
#define DEF_WPTBLMAX_V	144			// ���[�s���O���W�e�[�u�������ő�T�C�Y

// for LUT of interpolation filter
#define DEF_LUTSYM		6			// ��ԌW��LUT�V���{����
#define DEF_LUTCUT_MAX	1.2			// ��ԌW��LUT�J�b�g�I�t�W�����
#define DEF_LUTCUT_MIN	0.1			// ��ԌW��LUT�J�b�g�I�t�W������
#define DEF_LUTWIN_MAX	2.0			// ��ԌW��LUT�E�B���h�E�W�����
#define DEF_LUTWIN_MIN	0			// ��ԌW��LUT�E�B���h�E�W������

// for Cursor
#define DEF_CURSIZE		16			// 4�_�J�[�\���T�C�Y
// for 8-point
#define	DEF_WPGDSIZE	16			// 8�_�O���b�h�T�C�Y

// for dummy
//#define	DEF_WPDMYHW		32			// ���[�s���O�_�~�[�̈敝
#define	DEF_WPDMYHW		0			// ���[�s���O�_�~�[�̈敝
									// 16dot�Ԋu�␳���[�h�̂ݎg�p����16
									// 16 or 32dot�Ԋu�␳���[�h�g�p����32
									// �o�̓p�l���̊O���ɉ摜���͂ݏo���悤�ȕ␳���s��Ȃ��ꍇ��0��ݒ�
// Error
#define DEF_WPERR_NGZ		(20)
#define DEF_WPERR_CURPOS	(30)	// 4�_�J�[�\���ʒu�G���[



// Basic
extern int PM_WPDTMD;		// 16dot/32dot�Ԋu�␳���[�h(0:16dot, 1:32dot)

// H/V Keystone
extern float PM_WPKEYANG_H;	// ������`�␳�p�x[deg]
extern float PM_WPKEYANG_V;	// ������`�␳�p�x[deg]
extern float WPKEYANG_H_OLD;	// �O�̐�����`�␳�p�x[deg]
extern float WPKEYANG_V_OLD;	// �O�̐�����`�␳�p�x[deg]

typedef struct {
	float	axis;					// �v���W�F�N�^�����ʒu[%]
	float	dist;					// �v���W�F�N�^���e����[mm]
	float	vw;						// �v���W�F�N�^���e�摜������[mm]
} str_pjparam;
extern str_pjparam PM_PJPARAM;	// �v���W�F�N�^���w�n�p�����[�^
extern str_pjparam PJPARAM_OLD;	// �O�̃v���W�F�N�^���w�n�p�����[�^

// 4-corner Keystone
typedef struct {
	int tl_x,tl_y;					// 4�_�w����W����(X,Y)
	int tr_x,tr_y;					// 4�_�w����W�E��(X,Y)
	int bl_x,bl_y;					// 4�_�w����W����(X,Y)
	int br_x,br_y;					// 4�_�w����W�E��(X,Y)
} str_wppos4c;
extern str_wppos4c PM_WPPOS4C;	// 4�_�w����W
extern str_wppos4c WPPOS4C_OLD;	// �O��4�_�w����W

// for warp table
extern float Px[DEF_WPTBLMAX_H][DEF_WPTBLMAX_V];	// ���[�s���O���W�e�[�u��X
extern float Py[DEF_WPTBLMAX_H][DEF_WPTBLMAX_V];	// ���[�s���O���W�e�[�u��Y
extern int PHWNZ;			// round up �o�̓p�l��������f��/16(32)
extern int PVWNZ;			// round up �o�̓p�l��������f��/16(32)
extern float PHWHF;			// �o�̓p�l��������f��/2
extern float PVWHF;			// �o�̓p�l��������f��/2
extern int GPTx[3];		// �O���b�h�f�t�H���gX���W
extern int GPTy[3];		// �O���b�h�f�t�H���gY���W

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

