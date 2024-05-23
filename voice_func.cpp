#include <iostream>
#include "voice_func.h"
#include <windows.h>
#include <atlbase.h>
#include <sapi.h>
using namespace std;
bool voiceMode = true;

// ��л  https://blog.csdn.net/haimianjie2012/article/details/90238838

// ��stringת����wstring  https://blog.csdn.net/libaineu2004/article/details/119393505
wstring string2wstring(string str) {
	wstring result;
	//��ȡ��������С��������ռ䣬��������С���ַ�����  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //����ַ�����β  
	//ɾ��������������ֵ  
	result.append(buffer);
	delete[] buffer;
	return result;
}

// ����wstring���͵��ַ����������������ʶ��ĺ���
void speakWString(const wstring& text, int speed) {
	CoInitialize(NULL);       // ��ʼ��COM��
	CComPtr<ISpVoice> pVoice;   // ���������ϳɽӿ�ָ��
	// ���Դ���һ�������ϳɶ���
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
	if (SUCCEEDED(hr)) {
		// ��������Ϊ�е��ٶȣ�2��
		pVoice->SetRate(speed);
		// ����Speak���������ı��ʶ���0����Ĭ�ϵ��ʶ���־
		hr = pVoice->Speak(text.c_str(), 0, NULL);
		if (FAILED(hr)) {    // ����ʶ�ʧ�ܣ����������Ϣ
			cout << "�ı��ʶ�ʧ�ܣ���Ϊ���ر�����ģʽ" << endl;
			voiceMode = false;
		}
	}
	else {
		// ���������ϳɶ���ʧ��ʱ�Ĵ�����Ϣ
		cout << "���������ϳɶ���ʧ�ܣ���Ϊ���ر�����ģʽ" << endl;
		voiceMode = false;
	}
	pVoice.Release();   // �ͷ������ϳɽӿ�ָ��
	CoUninitialize();   // �رռ�����COM��
	return;
}
// ����stringȻ�����Բ���
void speakString(string text, int speed) {
	speakWString(string2wstring(text), speed);
}