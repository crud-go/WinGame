#pragma once
#include<wrl/client.h>
#include<d2d1_1.h>
#include"Render.h"
#include<fstream> 
#include"./include/json/json.h"
#ifdef _DEBUG

#pragma comment(lib,".\\lib\\Debug\\jsoncpp_static.lib")

#else

#pragma comment(lib,".\\lib\\Release\\jsoncpp_static.lib")

#endif
class Resource
{

public:
	Resource(const Resource&) = delete;
	Resource& operator=(const Resource&) = delete;

	static Resource& Instance() {
		static Resource m_instance;
		return m_instance;
	}

	 ID2D1Bitmap1* GetBitmap(std::wstring file);
	 Json::Value* GetJson(std::wstring file);
	 bool LoadBitmapFromFile(std::wstring file, ID2D1Bitmap1** Bitmap);
	 void ReleaseBitmap(const std::wstring& file);
  ~Resource();
private:
  	Resource();
	std::map<std::wstring, ComPtr<ID2D1Bitmap1>> m_Bitmaps;

	std::map<std::wstring, std::unique_ptr<Json::Value>> m_Jsons;

	ComPtr<IWICImagingFactory>      m_wicImgFactory;

	


};

