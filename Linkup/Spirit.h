#include "t3dlib1.h"

//======================================================
//BitMapSur�ṹ�弰����ú���
typedef struct BitmapSur
{
	int width;
	int height;
	LPDIRECTDRAWSURFACE7 surface;
}*BitmapSur_PTR;
//

BitmapSur_PTR Load_For_BitmapSur(int width_temp,int heigth_temp,char *file_name_temp);
BitmapSur_PTR Load_For_BitmapSur(int width_temp,int heigth_temp,char *file_name_temp,
					   LPRECT size_temp,int cell_x,int cell_y);

int Draw_BmpSur(LPDIRECTDRAWSURFACE7 surface_temp,RECT rect_temp,BitmapSur bmps_temp);
int Draw_BmpSur(LPDIRECTDRAWSURFACE7 surface_temp,RECT rect_temp,BitmapSur bmps_temp,
				DDCOLORKEY srcKey_temp);

int Draw_BmpSur_Win(LPDIRECTDRAWSURFACE7 surface_temp,RECT rect_temp,BitmapSur bmps_temp);
int Draw_BmpSur_Win(LPDIRECTDRAWSURFACE7 surface_temp,RECT rect_temp,BitmapSur bmps_temp,
					DDCOLORKEY srcKey_temp);

//========================================================
 


class Spirit//��������
{
friend class GameFrame;
protected:
	RECT posRect; //����λ��
	int Sp_Width,Sp_Height;
	BitmapSur_PTR look[2]; //ͼƬ��Դָ������
	USHORT type; //����������
	BOOL flag; //״̬��־

public:
	//=================���캯������������
	Spirit();
	Spirit(USHORT ustype,RECT pos);
	~Spirit();

	//==================���ֳ�Ա��д
	RECT Get_Rect(){return posRect;}
	USHORT Get_Type() {return type;}
	BOOL Get_Flag(){return flag;}
	void Change_Postion(RECT rect_temp) {posRect = rect_temp;}//�ı�λ��
	void Change_Type(USHORT type_temp) {type = type_temp;}
	void Turn_Flag() {flag = !flag;}
	RECT Window_Rect();
	void Updata_WH();

	//==================��װ�ĺ���
	int Create_Spirit(USHORT ustype,RECT pos);//�������飬��ʹ�ô��ι��캯���ɲ���

	//||------------------��ȡ����λͼ------------------||
	int Load_Look(char *file_name_temp,int look_id);
	int Load_Look(char *file_name_temp,int look_id,LPRECT size_temp,int cell_x,int cell_y);
	int Load_Look(BitmapSur_PTR bmsp_temp,int look_id);
	//||------------------��ȡ����λͼ------------------||

	BOOL Mouse_Move(UINT msg_temp,LPARAM lparam_temp);
	BOOL Click_Spirit(UINT msg_temp,LPARAM lparam_temp);//����������¼������������TRUE
	int Draw_Spirit(LPDIRECTDRAWSURFACE7 surface_temp,int window_mode,int look_id);
	int Draw_Spirit(LPDIRECTDRAWSURFACE7 surface_temp,DDCOLORKEY srcKey_temp,int window_mode,int look_id);//������

};
