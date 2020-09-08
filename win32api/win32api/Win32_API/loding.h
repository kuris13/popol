#pragma once
#include "gameNode.h"
#include "progressBar.h"


typedef enum
{
	LOAD_IMAGE_0,			//빈 비트맵 이미지
	LOAD_IMAGE_1,			//일반 이미지
	LOAD_IMAGE_2,			//일반 이미지 (위치 좌표 포함)
	LOAD_FRAMEIMAGE_0,		//프레임 이미지
	LOAD_FRAMEIMAGE_1,		//프레임 이미지 (위치 좌표 포함)
	LOAD_SOUND,				//사운드
	LOAD_END				//끝
}LOAD_ITEM;

typedef struct
{
	string keyName;
	const char* fileName;
	int x, y, width, height, frameX, frameY;
	bool trans;
	COLORREF transColor;
}tagImageResource;




class loadItem
{
private:
	LOAD_ITEM _itemCategory;
	tagImageResource _imageResource;
public :
	//일반 이미지 초기화
	HRESULT init(string keyName, int width, int height);
	HRESULT init(string keyName, const char* fileName, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));
	HRESULT init(string keyName, const char* fileName, float x, float y,
		int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));

	//프레임 이미지 초기화
	HRESULT init(string keyName, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE,
		COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(string keyName, const char* fileName, int x, int y, int width, int height, int maxFrameX, int maxFrameY,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));

	//이미지 아이템 종류 가져오기
	LOAD_ITEM getLoadingItemCategory() { return _itemCategory; }
	//이미지 리소스 가져오기
	tagImageResource getItemResource() { return _imageResource; }



};



class loding : public gameNode
{
private:
	//loadItem 클래스 객체를 담을 벡터
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator arrLoadItem_Iter;

	arrLoadItem _vLoadItem;

	//로딩화면에서 사용할 이미지
	image* _background;
	progressBar* _loadingBar;
	int _currentGauge;




public:


	HRESULT init();
	void release();
	void update();
	void render();

	void loadImage(string strKey, int width, int height);
	void loadImage(string strKey, const char* fileName, int width, int height,
		BOOL isTrans =FALSE, COLORREF transColor = RGB(0,0,0));
	void loadImage(string strKey, const char* fileName, float x, float y, int width, int height,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0,0,0));

	void loadFrameImage(string strKey, const char* fileName, 
		int width, int height, int maxFrameX, int maxFrameY,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadFrameImage(string strKey, const char* fileName,
		float x,float y, int width, int height, int maxFrameX, int maxFrameY,
		BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//로딩이 완료된 상태를 검사
	BOOL loadingDone();
	
	//LoadItem클래스 벡터 가져오기
	arrLoadItem getLoadItem() { return _vLoadItem; }



};

