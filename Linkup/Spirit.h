#include "t3dlib1.h"

//======================================================
//BitMapSur结构体及其调用函数
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
 


class Spirit//精灵引擎
{
friend class GameFrame;
protected:
	RECT posRect; //精灵位置
	int Sp_Width,Sp_Height;
	BitmapSur_PTR look[2]; //图片资源指针序列
	USHORT type; //精灵种类编号
	BOOL flag; //状态标志

public:
	//=================构造函数与析构函数
	Spirit();
	Spirit(USHORT ustype,RECT pos);
	~Spirit();

	//==================各种成员读写
	RECT Get_Rect(){return posRect;}
	USHORT Get_Type() {return type;}
	BOOL Get_Flag(){return flag;}
	void Change_Postion(RECT rect_temp) {posRect = rect_temp;}//改变位置
	void Change_Type(USHORT type_temp) {type = type_temp;}
	void Turn_Flag() {flag = !flag;}
	RECT Window_Rect();
	void Updata_WH();

	//==================封装的函数
	int Create_Spirit(USHORT ustype,RECT pos);//创建精灵，若使用带参构造函数可不用

	//||------------------读取精灵位图------------------||
	int Load_Look(char *file_name_temp,int look_id);
	int Load_Look(char *file_name_temp,int look_id,LPRECT size_temp,int cell_x,int cell_y);
	int Load_Look(BitmapSur_PTR bmsp_temp,int look_id);
	//||------------------读取精灵位图------------------||

	BOOL Mouse_Move(UINT msg_temp,LPARAM lparam_temp);
	BOOL Click_Spirit(UINT msg_temp,LPARAM lparam_temp);//鼠标点击精灵事件，被点击返回TRUE
	int Draw_Spirit(LPDIRECTDRAWSURFACE7 surface_temp,int window_mode,int look_id);
	int Draw_Spirit(LPDIRECTDRAWSURFACE7 surface_temp,DDCOLORKEY srcKey_temp,int window_mode,int look_id);//画精灵

};
