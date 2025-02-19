#include <windows.h>
#include <wininet.h>
#include <stdint.h>
#define EIGEN_USE_MKL_ALL
import <Eigen/Core>;
#undef max
import std;
[[noreturn]] static void 异常退出()
{
	system("pause");
	exit(1);
}
[[noreturn]] static void 普通报错(std::string_view 错误信息)
{
	std::cerr << 错误信息 << std::endl;
	异常退出();
}
//查找指定句柄窗口子级中的第几个（从1开始，一定会向下挖一级）
static void 平级查找(uint16_t 第几个, HWND& 父窗口, std::ostringstream& 错误信息流)
{
	错误信息流 << "\\SWT_Window0[";
	std::string const 错误信息 = 错误信息流.str();
	HWND const 父窗口 = 父窗口;
	父窗口 = NULL;
	for (uint16_t a = 0; a < 第几个; ++a)
	{
		if (!(父窗口 = FindWindowExW(父窗口, 父窗口, L"SWT_Window0", NULL)))
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
int main(int argc, char* argv[])
{
	unsigned long 警报阈值;
	if (argc > 1)
	{
		char* 字符指针;
		警报阈值 = std::strtoul(argv[1], &字符指针, 10);
		if (*字符指针 || 警报阈值 > std::numeric_limits<uint8_t>::max())
			普通报错("警报阈值不能大于255");
	}
	else
	{
		std::cout << "输入警报阈值（0~255）：";
		std::cin >> 警报阈值;
		if (警报阈值 > std::numeric_limits<uint8_t>::max())
			普通报错("警报阈值不能大于255");
	}
	std::string 喵码;
	if (argc > 2)
	{
		if (std::strlen(argv[2]) != 7)
			普通报错("喵码必须是一个7位的字符串");
		喵码 = argv[2];
	}
	else
	{
		std::cout << "输入喵码：";
		std::getline(std::cin, 喵码);
		if (喵码.size() != 7)
			普通报错("喵码必须是一个7位的字符串");
	}
	std::ostringstream 错误信息流{ "找不到窗口：SWT_Window0::OLYMPUS FV31S-SW", std::ios::app };
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
	HWND 指针窗口 = FindWindowExA(父窗口, NULL, "SWT_Window0", NULL);
	std::ostringstream 尝试错误信息流{ 错误信息流.str(),std::ios::app };
	尝试错误信息流 << "0]";
	if (!指针窗口)
		普通报错(尝试错误信息流.str());
	HWND 末端窗口 = 指针窗口;
	RECT 窗口矩形;
	指针末端(末端窗口, 尝试错误信息流, 窗口矩形);
	if (末端窗口)
		错误信息流 = std::move(尝试错误信息流);
	else
	{
		末端窗口 = FindWindowExA(父窗口, 指针窗口, "SWT_Window0", NULL);
		错误信息流 << "1]";
		if (末端窗口)
		{
			指针末端(末端窗口, 错误信息流, 窗口矩形);
			if (末端窗口)
				goto 成功获取窗口;
		}
		std::cerr << 尝试错误信息流.str() << std::endl;
		std::cerr << 错误信息流.str() << std::endl;
		异常退出();
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
	if (像素数组.cast<uint32_t>().mean() > 警报阈值)
	{
		HINTERNET const 代理 = InternetOpenW(L"", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		HINTERNET const 连接 = InternetOpenUrlA(代理, ("http://miaotixing.com/trigger?id=" + 喵码).c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
		DWORD 状态码;
		DWORD 字节数 = sizeof(状态码);
		HttpQueryInfo(连接, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &状态码, &字节数, NULL);
		InternetCloseHandle(连接);
		InternetCloseHandle(代理);
		time_t 当前时间 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		auto const 时间字符串 = std::put_time(localtime(&当前时间), "%Y-%m-%d %H:%M:%S");
		if (状态码 == HTTP_STATUS_OK)
			std::cout << "检测到过曝，已发送警报" << std::endl;
		else
			std::cerr << "检测到过曝，但发送警报失败：" << 状态码 << std::endl;
	}
}