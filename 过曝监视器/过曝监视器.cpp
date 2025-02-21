#define EIGEN_USE_MKL_ALL
#include <Eigen/Core>
#include <windows.h>
#include <wininet.h>
#pragma comment(lib,"Wininet.lib")
#undef max
import std;
[[noreturn]] static void 普通报错(std::string const& 错误信息)
{
	std::cerr << 错误信息 << std::endl;
	system("pause");
	exit(1);
}
template<size_t 长度>
static std::string 转当前代码页(wchar_t const(&宽字符串)[长度])//引用数组参数可以避免退化成指针
{
	std::string 当前代码页;
	constexpr size_t 字符数 = 长度 - 1;
	当前代码页.resize_and_overwrite(字符数 * 3, [宽字符串](char* 指针, size_t 容量)
		{
			return WideCharToMultiByte(CP_ACP, 0, 宽字符串, 字符数, 指针, 容量, NULL, NULL);
		});
	return 当前代码页;
}
template<size_t 长度>
inline static void 普通报错(wchar_t const(&宽字符串)[长度])
{
	普通报错(转当前代码页(宽字符串));
}
//查找指定句柄窗口子级中的第几个（从1开始，一定会向下挖一级）
static void 平级查找(uint16_t 第几个, HWND& 窗口句柄, std::ostringstream& 错误信息流)
{
	错误信息流 << "\\SWT_Window0[";
	std::string const 错误信息 = 错误信息流.str();
	HWND const 父窗口 = 窗口句柄;
	窗口句柄 = NULL;
	for (uint16_t a = 0; a < 第几个; ++a)
	{
		if (!(窗口句柄 = FindWindowExW(父窗口, 窗口句柄, L"SWT_Window0", NULL)))
		{
			错误信息流 << a << "]";
			throw& 错误信息流;
		}
	}
	错误信息流 << 第几个 - 1 << "]";
}
//向下挖一级
inline static void 单级查找(HWND& 父窗口, std::ostringstream& 错误信息流, char const* 窗口类)
{
	错误信息流 << "\\" << 窗口类;
	if (!(父窗口 = FindWindowExA(父窗口, NULL, 窗口类, NULL)))
		throw& 错误信息流;
}
static void 指针末端(HWND& 窗口句柄, std::ostringstream& 错误信息流,RECT&窗口矩形)
{
	try
	{
		单级查找(窗口句柄, 错误信息流, "SWT_Window0");
		平级查找(2, 窗口句柄, 错误信息流);
		单级查找(窗口句柄, 错误信息流, "SWT_Window0");
		单级查找(窗口句柄, 错误信息流, "SWT_WindowOwnDC0");
	}
	catch (std::ostringstream*)
	{
		return;
	}
	if (!GetWindowRect(窗口句柄, &窗口矩形) || WindowFromPoint({ (窗口矩形.left + 窗口矩形.right) / 2,(窗口矩形.top + 窗口矩形.bottom) / 2 }) != 窗口句柄)
		窗口句柄 = NULL;
}
static auto 输出当前时间()
{
	time_t const 当前时间 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	return std::put_time(localtime(&当前时间), "%Y-%m-%d %H:%M:%S ");
}
int main(int argc, char* argv[])
{
	std::ostringstream 错误信息流{ 转当前代码页(L"找不到窗口："),std::ios::app };
	错误信息流 << "SWT_Window0::OLYMPUS FV31S - SW";
	HWND 父窗口 = FindWindowW(L"SWT_Window0", L"OLYMPUS FV31S-SW");
	if (!父窗口)
		普通报错(错误信息流.str());
	try
	{
		平级查找(4, 父窗口, 错误信息流);
		单级查找(父窗口, 错误信息流, "SWT_Window0");
		单级查找(父窗口, 错误信息流, "SWT_Window0");
		平级查找(8, 父窗口, 错误信息流);
		单级查找(父窗口, 错误信息流, "SWT_Window0");
		单级查找(父窗口, 错误信息流, "SWT_Window0");
		平级查找(2, 父窗口, 错误信息流);
		平级查找(2, 父窗口, 错误信息流);
		单级查找(父窗口, 错误信息流, "SWT_Window0");
		单级查找(父窗口, 错误信息流, "SWT_Window0");
		平级查找(2, 父窗口, 错误信息流);
		单级查找(父窗口, 错误信息流, "SWT_Window0");
	}
	catch (std::ostringstream*)
	{
		普通报错(错误信息流.str());
	}
	错误信息流 << "\\SWT_Window0[";
	std::string const 错误前缀 = 错误信息流.str();
	std::chrono::seconds 错误等待{ 1 };
	unsigned long 警报阈值;
	if (argc > 1)
	{
		char* 字符指针;
		警报阈值 = std::strtoul(argv[1], &字符指针, 10);
		if (*字符指针 || 警报阈值 > std::numeric_limits<uint8_t>::max())
			普通报错(L"警报阈值不能大于255");
	}
	else
	{
		std::cout << 转当前代码页(L"输入警报阈值（0~255）：");
		std::cin >> 警报阈值;
		if (警报阈值 > std::numeric_limits<uint8_t>::max())
			普通报错(L"警报阈值不能大于255");
	}
	std::string 喵码;
	if (argc > 2)
	{
		if (std::strlen(argv[2]) != 7)
			普通报错(L"喵码必须是一个7位的字符串");
		喵码 = argv[2];
	}
	else
	{
		std::cout << 转当前代码页(L"输入喵码：");
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, 喵码);
		if (喵码.size() != 7)
			普通报错(L"喵码必须是一个7位的字符串");
	}
	std::cout << 转当前代码页(L"监视中，发现过曝将发送喵提醒……") << std::endl;
	for (;;)
	{
		std::ostringstream Tile错误信息流{ 错误前缀,std::ios::app };
		Tile错误信息流 << "0]";
		HWND const 指针窗口 = FindWindowExA(父窗口, NULL, "SWT_Window0", NULL);
		if (!指针窗口)
		{
			std::cerr << 输出当前时间() << Tile错误信息流.str() << std::endl;
			std::this_thread::sleep_for(错误等待 *= 2);
			continue;
		}
		HWND 末端窗口 = 指针窗口;
		RECT 窗口矩形;
		指针末端(末端窗口, Tile错误信息流, 窗口矩形);
		if (!末端窗口)
		{
			末端窗口 = FindWindowExA(父窗口, 指针窗口, "SWT_Window0", NULL);
			std::ostringstream Single错误信息流{ 错误前缀,std::ios::app };
			Single错误信息流 << "1]";
			if (末端窗口)
			{
				指针末端(末端窗口, Single错误信息流, 窗口矩形);
				if (末端窗口)
					goto 成功获取窗口;
			}
			static std::string const 遮挡提示 = 转当前代码页(L"请检查成像预览窗口是否被遮挡？");
			std::cerr << std::endl << 输出当前时间() << std::endl << Tile错误信息流.str() << std::endl << Single错误信息流.str() << std::endl << 遮挡提示 << std::endl;
			std::this_thread::sleep_for(错误等待 *= 2);
			continue;
		}
	成功获取窗口:
		HDC const 窗口设备上下文 = GetDC(末端窗口);
		HBITMAP const 位图句柄 = CreateCompatibleBitmap(窗口设备上下文, 窗口矩形.right - 窗口矩形.left, 窗口矩形.bottom - 窗口矩形.top);
		HDC const 内存设备上下文 = CreateCompatibleDC(窗口设备上下文);
		SelectObject(内存设备上下文, 位图句柄);
		BitBlt(内存设备上下文, 0, 0, 窗口矩形.right - 窗口矩形.left, 窗口矩形.bottom - 窗口矩形.top, 窗口设备上下文, 0, 0, SRCCOPY);
		ReleaseDC(末端窗口, 窗口设备上下文);
		BITMAP 位图;
		GetObject(位图句柄, sizeof(位图), &位图);
		BITMAPINFO 位图信息 = { {
				.biSize = sizeof(BITMAPINFOHEADER),
				.biWidth = 位图.bmWidth,
				.biHeight = 位图.bmHeight,
				.biPlanes = 1,
				.biBitCount = 位图.bmBitsPixel,
				.biCompression = BI_RGB
			} };
		Eigen::Matrix<uint8_t, Eigen::Dynamic, 1>像素数组(位图.bmWidthBytes * 位图.bmHeight);
		GetDIBits(内存设备上下文, 位图句柄, 0, 位图.bmHeight, 像素数组.data(), &位图信息, DIB_RGB_COLORS);
		DeleteDC(内存设备上下文);
		DeleteObject(位图句柄);
		uint16_t const 当前亮度 = 像素数组.cast<uint32_t>().mean();
		static std::string const 当前亮度提示 = 转当前代码页(L"当前亮度：");
		std::cout << 输出当前时间() << 当前亮度提示 << 当前亮度 << std::endl;
		if (当前亮度 > 警报阈值)
		{
			static HINTERNET const 代理 = InternetOpenW(L"", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
			HINTERNET const 连接 = InternetOpenUrlA(代理, ("http://miaotixing.com/trigger?id=" + 喵码).c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
			DWORD 状态码;
			DWORD 字节数 = sizeof(状态码);
			HttpQueryInfo(连接, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &状态码, &字节数, NULL);
			time_t const 当前时间 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::cout << std::put_time(localtime(&当前时间), "%Y-%m-%d %H:%M:%S ");
			if (状态码 == HTTP_STATUS_OK)
			{
				static std::string 缓冲;
				bool 需要扩张;
				DWORD 已写字节数 = 0;
				auto const 更新方法 = [连接, &字节数, &需要扩张, &已写字节数](char* 指针, size_t 容量)
					{
						//MSVC的bug，size会在调用用户方法之前被修改，因此访问不到原本的size
						需要扩张 = !InternetReadFile(连接, 指针 + 已写字节数, 容量 - 已写字节数, &字节数);
						return 已写字节数 += 字节数;
					};
				缓冲.resize_and_overwrite(std::max<size_t>(1, 缓冲.capacity()), 更新方法);
				for (;;)
					if (需要扩张)
						缓冲.resize_and_overwrite(缓冲.capacity() << 1, 更新方法);
					else if (字节数)
						缓冲.resize_and_overwrite(缓冲.capacity(), 更新方法);
					else
						break;
				static std::string const 警报成功 = 转当前代码页(L"检测到过曝，已发送警报：");
				std::cout << 警报成功 << 缓冲 << std::endl;
			}
			else
			{
				static std::string const 警报失败 = 转当前代码页(L"检测到过曝，但发送警报失败：HTTP ");
				std::cerr << 警报失败 << 状态码 << std::endl;
			}
			InternetCloseHandle(连接);
			static std::string const 任意键继续 = 转当前代码页(L"按任意键以继续监视：");
			std::cout << 任意键继续;
			std::cin.get(); // 等待用户按任意键
		}
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(错误等待 = 1s);
	}
}