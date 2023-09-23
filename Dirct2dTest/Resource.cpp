#include "Resource.h"

Resource::~Resource()
{

	m_Bitmaps.clear();
	m_Jsons.clear();

}

Resource::Resource()
{
 HRESULT hr=CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&this->m_wicImgFactory));
 assert(SUCCEEDED(hr));
}

ID2D1Bitmap1* Resource::GetBitmap(std::wstring file)
{
	auto it = m_Bitmaps.find(file);

	if (it == m_Bitmaps.end())
	{
		// 没找到，加载
	m_Bitmaps[file] = ComPtr<ID2D1Bitmap1>();
	  LoadBitmapFromFile(file, &m_Bitmaps[file]);
		if (m_Bitmaps[file].Get() == nullptr) std::wcout << L"资源加载失败：" << file << std::endl;
		return m_Bitmaps[file].Get();
	}
	else
	{
		// 找到了
		return it->second.Get();
	}
	return nullptr;
}

Json::Value* Resource::GetJson(std::wstring file)
{

	auto it = m_Jsons.find(file);

	if (it == m_Jsons.end())
	{
		// 没找到，加载
		m_Jsons.insert(std::make_pair(file, std::make_unique<Json::Value>()));

		char buf[256] = { 0 };
		std::ifstream in;
		in.open(file);
		if (in.fail()) return nullptr;
		Json::CharReaderBuilder ReaderBuilder;
		ReaderBuilder["emitUTF8"] = true;
		std::string strerr;
		bool ok = Json::parseFromStream(ReaderBuilder, in, m_Jsons[file].get(), &strerr);
		if (!ok) { std::wcout << L"资源加载失败：" << file << std::endl; return nullptr; }
		in.close();

		return m_Jsons[file].get();
	}
	else
	{
		// 找到了
		return it->second.get();
	}
}


bool Resource::LoadBitmapFromFile(std::wstring file, ID2D1Bitmap1** Bitmap)
{


	HRESULT hr = S_OK;
	ComPtr<IWICBitmapDecoder> WicBitmap;
	ComPtr<IWICBitmapFrameDecode> WicFrameDec;

	hr = this->m_wicImgFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &WicBitmap);
	assert(SUCCEEDED(hr));
	if (FAILED(hr)) return false;

	hr = WicBitmap->GetFrame(0, &WicFrameDec);
	assert(SUCCEEDED(hr));
	if (FAILED(hr)) return false;

	WICPixelFormatGUID Format;
	ComPtr<IWICBitmapSource> WicBitmapSource;
	WicFrameDec->GetPixelFormat(&Format);
	if (Format != GUID_WICPixelFormat32bppPBGRA)
	{
		// 需要转换格式
		ComPtr<IWICFormatConverter> wic_converter;
		hr = this->m_wicImgFactory->CreateFormatConverter(&wic_converter);
		assert(SUCCEEDED(hr));
		if (FAILED(hr)) return false;

		hr = wic_converter->Initialize(
			WicFrameDec.Get(),
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.0f,
			WICBitmapPaletteTypeCustom);
		assert(SUCCEEDED(hr));
		if (FAILED(hr)) return false;

		wic_converter.As(&WicBitmapSource);
	}
	else
	{
		WicFrameDec.As(&WicBitmapSource);
	}

	hr = D2dRender::Instance()->getD2dDeviceContext()->CreateBitmapFromWicBitmap(WicBitmapSource.Get(), Bitmap);
	assert(SUCCEEDED(hr));
	if (FAILED(hr)) return false;

	return true;
}

void Resource::ReleaseBitmap(const std::wstring& file)
{

	auto it = m_Bitmaps.find(file);
	if (it != m_Bitmaps.end())
	{
		m_Bitmaps.erase(it);
	}

}
