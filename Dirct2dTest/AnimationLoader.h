#pragma once
#include"include/json/json.h"
#include"Render.h"
#include"Resource.h"
struct _frame { UINT32 x; UINT32 y; UINT32 w; UINT32 h; };	// ��ǰλͼҪ�и��λ��
struct _sourceSize { UINT32 w; UINT32 h; };			// Ҫ���ɵľ���Ĵ�С
struct _spriteSourcePos { UINT32 x; UINT32 y; UINT32 w; UINT32 h; };		// ��Ŀ��λͼ����������λͼ�ھ���ͼ�е�λ��
struct animation_data
{
	_frame Frame = { 0 };
	_sourceSize SourceSize = { 0 };
	_spriteSourcePos SpriteSourcePos = { 0 };
};

using AnimationFile = std::pair< std::wstring, std::wstring >;
using _Animation = std::map< std::string, std::pair< std::vector<ID2D1Bitmap1*>, float > >;
class AnimationLoader
{
public:
  static	bool loadAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, _Animation& root, float duration);
  static	ID2D1Bitmap1* CreateSpritesBitmap(ID2D1Bitmap1* srcBitmap, animation_data* d);
  static	_Animation* GetAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration);
private:


	static std::map<AnimationFile, _Animation> AnimationData;

};

