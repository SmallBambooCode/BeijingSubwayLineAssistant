#include <iostream>
#include "voice_func.h"
#include <windows.h>
#include <atlbase.h>
#include <sapi.h>
using namespace std;
bool voiceMode = true;

// 感谢  https://blog.csdn.net/haimianjie2012/article/details/90238838

// 将string转换成wstring  https://blog.csdn.net/libaineu2004/article/details/119393505
wstring string2wstring(string str) {
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

// 传入wstring类型的字符串，并进行语音朗读的函数
void speakWString(const wstring& text, int speed) {
	CoInitialize(NULL);       // 初始化COM库
	CComPtr<ISpVoice> pVoice;   // 创建语音合成接口指针
	// 尝试创建一个语音合成对象
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (SUCCEEDED(hr)) {
		// 设置语速为中等速度（2）
		pVoice->SetRate(speed);
		// 调用Speak方法进行文本朗读，0代表默认的朗读标志
		hr = pVoice->Speak(text.c_str(), 0, NULL);
		if (FAILED(hr)) {    // 如果朗读失败，输出错误信息
			cout << "文本朗读失败，已为您关闭语音模式" << endl;
			voiceMode = false;
		}
	}
	else {
		// 创建语音合成对象失败时的错误信息
		cout << "创建语音合成对象失败，已为您关闭语音模式" << endl;
		voiceMode = false;
	}
	pVoice.Release();   // 释放语音合成接口指针
	CoUninitialize();   // 关闭及清理COM库
	return;
}
// 传入string然后语言播放
void speakString(string text, int speed) {
	speakWString(string2wstring(text), speed);
}