#include <list>
#include "Spirit.h"
using namespace std;

#define Button_Single 0x01
#define Button_Multi  0x02
#define Button_Rank   0x03
#define Button_Exit   0x04

#define Menu_ID_Background    0x01
#define Menu_ID_Button       0x02
#define Menu_ID_Button_Spark 0x03

#define Direct_Left   1
#define Direct_Right -1
#define Direct_Up     2
#define Direct_Down  -2

extern LPDIRECTDRAWSURFACE7 lpddsoff;

typedef struct Port//方块的连线节点，必须初始化而且全值为0
{
	int p_x,
		p_y;
	int direct[4];     //存储具有四种方向的优先级数据数组
	int direct_from;   //上一个节点由那一个方向来的？
	int direct_to;     //下一个前往的节点
	int corner_counter;//节点回折次数
}*PPort;

class GameFrame//游戏主框架
{
friend class Spirit;

protected:
	static GameFrame *p_GFP;         //指向自身的指针
	int Array[12][18];               //游戏区数组
	int timer_set;                   //计时器
	int tick_count;
	int tickperpix;
	RECT timer_src_len;
	RECT timer_des_len;
	BitmapSur_PTR SpiritBMP_1[26];   //精灵位图数组1
	BitmapSur_PTR SpiritBMP_2[26];   //精灵位图数组2
	BitmapSur_PTR MainMenuBMP;       //主菜单位图
	BitmapSur_PTR BackgroundBMP;     //游戏背景区域位图
	BitmapSur_PTR ButtonBMP_1[4];    //按钮位图
	BitmapSur_PTR ButtonBMP_2[4];    
	BitmapSur_PTR rimBMP;            //方框位图
	BitmapSur_PTR Link_1BMP[6];      //连线位图
	BitmapSur_PTR Link_2BMP[6];
	BitmapSur_PTR TimerBMP;       //时间条位图
	BitmapSur_PTR NumberBMP[10];     //数字位图
	LPDIRECTDRAWSURFACE7 link_surface;
	DDBLTFX ddbltfx_black,ddbltfx_white;
public:
	list<Port> link_list;
	Spirit Sp_Button[4];
	Spirit Sp_Block[160];
	Spirit Sp_Link[6];
	Spirit Sp_Exit;
	POINT rim_pos[2];
	BOOL  dolink;
	BOOL  time_out;
    UINT Gf_msg;
	LPARAM Gf_lparam;
public:
	GameFrame(int win_width,int win_heigth);
	~GameFrame();
	static GameFrame *GetGameFramePoint();//获取自身指针

	//============================消息类成员函数
	LRESULT inline ProcEvent(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);//消息处理函数
	BOOL MouseMove(RECT rect_temp);
	BOOL MouseMoveInSpirit(Spirit sp_temp);
	BOOL LButton_On_Click(RECT rect_temp);
	BOOL LButtonClick_InSpirit(Spirit sp_temp);

	//============================游戏执行进程非引擎函数
	int Init_Menu();
	int Draw_Menu(int draw_id);
	int Single_Mode_Init();
	int NumberBmp_Init();
	int Draw_Region();
	int Draw_Block();
	int Draw_Number(POINT pos_temp,char num_temp[]);
	int Draw_Timer();
	int Check_Select_Null(POINT point_temp);
	int Draw_Rim(int rim_id);
	int Reset_Rim();
	int Draw_LinkSur();
	int Blt_LinkSur(LPDIRECTDRAWSURFACE7 lpdds_temp);
	int Update_Score();
	int Check_Linked(Port current_node,Port src_node,Port dest_node);
	int Clean_Block();
	int Check_DeadLock();
	int Check_GameOver();

	BOOL Select_Pos(PPOINT point_pos);//响应鼠标事件并获得鼠标位置
	Port Arrange_Direct(Port port_temp,POINT dest_point);
	BOOL Can_go(Port port_temp,Port dest_port,int direct_temp);
	Port Go_Next_Port(Port port_temp,int direct_temp);
	void Set_Port(PPort port_temp,POINT point_temp);
	void Set_Array__(POINT point_temp,int value_temp);
	void Start_Link(){dolink = TRUE;}
	void Stop_Link(){dolink = FALSE;}
	void Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds_temp,LPDDBLTFX lpddbltfx_temp);
	void Disrupt_BlockArea();
	BOOL IsExit();
	
};