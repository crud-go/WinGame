#include "AnimationLoader.h"

std::map<AnimationFile, _Animation> AnimationLoader::AnimationData;
bool AnimationLoader::loadAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, _Animation& root, float duration) {
	char buf[256] = { 0 };

	// ����ͼƬ
	ID2D1Bitmap1* Src_Bitmap = nullptr;
	Src_Bitmap = Resource::Instance().GetBitmap(bitmapFile); //������ԴͼƬ
	if (Src_Bitmap == nullptr) return false;

	// ����Json
	Json::Value* data_;
	data_ = Resource::Instance().GetJson(jsonFile);
	if (data_ == nullptr) return false;
	Json::Value& data = *data_;

	int animation_num = data["meta"]["frameTags"].size();

	for (int j = 0; j < animation_num; j++)
	{
		std::string name = data["meta"]["frameTags"][j]["name"].asString();

		int from = data["meta"]["frameTags"][j]["from"].asInt();
		int to = data["meta"]["frameTags"][j]["to"].asInt();

		int count = 0;
		for (int i = from; i != to + 1; i++)
		{
			animation_data anim_data = { 0 };
			anim_data.Frame.x = data["frames"][i]["frame"]["x"].asUInt();
			anim_data.Frame.y = data["frames"][i]["frame"]["y"].asUInt();
			anim_data.Frame.w = data["frames"][i]["frame"]["w"].asUInt();
			anim_data.Frame.h = data["frames"][i]["frame"]["h"].asUInt();

			anim_data.SourceSize.w = data["frames"][i]["sourceSize"]["w"].asUInt();
			anim_data.SourceSize.h = data["frames"][i]["sourceSize"]["h"].asUInt();

			anim_data.SpriteSourcePos.x = data["frames"][i]["spriteSourceSize"]["x"].asUInt();
			anim_data.SpriteSourcePos.y = data["frames"][i]["spriteSourceSize"]["y"].asUInt();
			anim_data.SpriteSourcePos.w = data["frames"][i]["spriteSourceSize"]["w"].asUInt();
			anim_data.SpriteSourcePos.h = data["frames"][i]["spriteSourceSize"]["h"].asUInt();

			root[name].first.push_back(nullptr);
			root[name].first.at(count) = CreateSpritesBitmap(Src_Bitmap, &anim_data);//���������ļ��ü�ͼƬ

			assert(root[name].first.at(count) != NULL);
			root[name].second = duration;
			//m_now_animation = &root.find(name);

			count++;
		}
	}

	 Resource::Instance().ReleaseBitmap(bitmapFile);
	return true;
}
ID2D1Bitmap1* AnimationLoader::CreateSpritesBitmap(ID2D1Bitmap1* srcBitmap, animation_data* d)
{
	ID2D1Bitmap1* recBitmap = nullptr;
	// ���� һ�� bitmap
	D2D1_BITMAP_PROPERTIES1 d2d1_bitmap_def = {};
	d2d1_bitmap_def.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	d2d1_bitmap_def.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	d2d1_bitmap_def.dpiX = USER_DEFAULT_SCREEN_DPI;
	d2d1_bitmap_def.dpiY = USER_DEFAULT_SCREEN_DPI;
	d2d1_bitmap_def.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;

	auto m_content = D2dRender::Instance()->getD2dDeviceContext();
	auto hr = m_content->CreateBitmap
	(
		{ d->SourceSize.w, d->SourceSize.h }, 0, 0,
		d2d1_bitmap_def,
		&recBitmap
	);
	if (FAILED(hr)) return nullptr;

	// ��ȡԭ���ľ�����һ�±���
	D2D1_MATRIX_3X2_F last_matrix;
	m_content->GetTransform(&last_matrix);
	m_content->SetTarget(recBitmap);
	m_content->SetTransform(D2D1::Matrix3x2F::Translation(0.0f, 0.0f));	// �ǵ��ȹ�λ�����
	m_content->BeginDraw();
	m_content->Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.0f));
	m_content->DrawBitmap(srcBitmap,
		D2D1::RectF(d->SpriteSourcePos.x, d->SpriteSourcePos.y, d->SpriteSourcePos.x + d->SpriteSourcePos.w, d->SpriteSourcePos.y + d->SpriteSourcePos.h),
		1.0f,
		D2D1_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(d->Frame.x, d->Frame.y, d->Frame.x + d->Frame.w, d->Frame.y + d->Frame.h)
	);
	hr = m_content->EndDraw();

	if (FAILED(hr)) return nullptr;

	m_content->SetTarget(D2dRender::Instance()->getRenderTarget());
	m_content->SetTransform(last_matrix);

	return recBitmap;
}
_Animation* AnimationLoader::GetAnimation(const std::wstring& bitmapFile, const std::wstring& jsonFile, float duration)
{
	auto anim =AnimationData.find(std::make_pair(bitmapFile, jsonFile));//�����ļ��Ƿ񱻼��ع�

	if (anim ==AnimationData.end())
	{
		// û�ҵ�������
		AnimationData[std::make_pair(bitmapFile, jsonFile)];

		if (!loadAnimation(bitmapFile, jsonFile, AnimationData.at(std::make_pair(bitmapFile, jsonFile)), duration))//���ض����ļ�
			return nullptr;
		else
			return &AnimationData[std::make_pair(bitmapFile, jsonFile)];

		return nullptr;
	}
	else
	{
		// �ҵ��˾ͷ���
		return &anim->second;
	}
}
