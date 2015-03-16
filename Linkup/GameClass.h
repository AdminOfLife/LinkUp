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

typedef struct Port//��������߽ڵ㣬�����ʼ������ȫֵΪ0
{
	int p_x,
		p_y;
	int direct[4];     //�洢�������ַ�������ȼ���������
	int direct_from;   //��һ���ڵ�����һ���������ģ�
	int direct_to;     //��һ��ǰ���Ľڵ�
	int corner_counter;//�ڵ���۴���
}*PPort;

class GameFrame//��Ϸ�����
{
friend class Spirit;

protected:
	static GameFrame *p_GFP;         //ָ�������ָ��
	int Array[12][18];               //��Ϸ������
	int timer_set;                   //��ʱ��
	int tick_count;
	int tickperpix;
	RECT timer_src_len;
	RECT timer_des_len;
	BitmapSur_PTR SpiritBMP_1[26];   //����λͼ����1
	BitmapSur_PTR SpiritBMP_2[26];   //����λͼ����2
	BitmapSur_PTR MainMenuBMP;       //���˵�λͼ
	BitmapSur_PTR BackgroundBMP;     //��Ϸ��������λͼ
	BitmapSur_PTR ButtonBMP_1[4];    //��ťλͼ
	BitmapSur_PTR ButtonBMP_2[4];    
	BitmapSur_PTR rimBMP;            //����λͼ
	BitmapSur_PTR Link_1BMP[6];      //����λͼ
	BitmapSur_PTR Link_2BMP[6];
	BitmapSur_PTR TimerBMP;       //ʱ����λͼ
	BitmapSur_PTR NumberBMP[10];     //����λͼ
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
	static GameFrame *GetGameFramePoint();//��ȡ����ָ��

	//============================��Ϣ���Ա����
	LRESULT inline ProcEvent(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);//��Ϣ������
	BOOL MouseMove(RECT rect_temp);
	BOOL MouseMoveInSpirit(Spirit sp_temp);
	BOOL LButton_On_Click(RECT rect_temp);
	BOOL LButtonClick_InSpirit(Spirit sp_temp);

	//============================��Ϸִ�н��̷����溯��
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

	BOOL Select_Pos(PPOINT point_pos);//��Ӧ����¼���������λ��
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