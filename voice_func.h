#pragma once
#include <string>
using namespace std;
wstring string2wstring(string str);
void speakWString(const wstring& text, int speed);
void speakString(string text, int speed = 5);
extern bool voiceMode;