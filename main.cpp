/***************************
		 COPYRIGHT
 ����������·С���֣�������Աά����
	   Author:SmallBambooCode
	 2024��4��24��12��32�����幦�����
	 2024��5��8��21��20����������ʶ�����
	 2024��5��10��18��20����ɽ���KIMI AI
	 2024��5��22��21��25����ɶ��û������¼ʹ���Լ���ѯ��ʷ����
	 ��ǰ��������4000��+
****************************/
#include <iostream>
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include "AML.h"
#include "Subway.h"
#include "voice_func.h"
#include "User.h"
#pragma comment(lib, "Winmm.lib")
#define or ||
#define and &&
using namespace std;
// ��ӡ����
void printAbout() {
	system("cls");
	cout << "===============================================================================================" << endl;
	cout << "[                                ����������·С���� - ���ڱ����                              ]" << endl;
	cout << "===============================================================================================" << endl;
	cout << "[  ����������·С������һ��Ϊ��󱱾������˿ͼ�������Ա��Ƶ�ʵ���������                     ]" << endl;
	cout << "[  ���߱��ḻ�Ĺ��ܺ����Ի�����ƣ��ǳ˿��ճ����к͵�����·ά����Ա�����ĵ����������ߡ�       ]" << endl;
	cout << "===============================================================================================" << endl;
	cout << "[  ȫվ�����·�鿴���ṩ�����ĵ���վ�����·��Ϣ�����ڲ��ģ�����滮�г̡�                   ]" << endl;
	cout << "[  ��·�滮���֣�ֻ�����������յ㣬���ɵõ����·��������վ���������ܹ滮���������������ʾ ]" << endl;
	cout << "[  �����˴�����վ��ͳ�ƣ��Լ�Ʊ�ۼ��㣬ȷ���˿ͳ������ǡ�                                     ]" << endl;
	cout << "[  ���·��̽�����ṩ���·�߹��ܣ�Ϊ��̽���ĳ˿��ṩ�µĳ������顣                           ]" << endl;
	cout << "[  �����ʶ�ģʽ��ͨ���򵥵İ����������ɼ��������ʶ������������Ŀɷ����ԡ�                   ]" << endl;
	cout << "[  �ۺϵ�վ��·��ά�����������Աͨ����̨��ӡ�ɾ�����޸�վ�����·��Ϣ���Ա���Ϣ�ļ�ʱ���¡� ]" << endl;
	cout << "[  վ��״̬�л���������ظ�����վ�Ŀ���״̬�����Ӧ��ͻ���¼���ά����Ҫ��                     ]" << endl;
	cout << "[  ��Ϣ���£��޸�վ�����ơ���·���Ƽ���̨����ȣ�ȷ����Ϣ��׼ȷ�Ժ�ϵͳ�İ�ȫ�ԡ�             ]" << endl;
	cout << "===============================================================================================" << endl;
	cout << "[  �ɡ�SmallBambooCode����������ı���������·С���֣�������Ϊ���˿��ṩ�����ĳ��й滮��  ]" << endl;
	cout << "[  ����Ϊ����Ա������Ч�ʵ�ά��������������Ϊ�����������к͹�������ܻ�������                 ]" << endl;
	cout << "[  �ڷ������еĿ�����У�����ÿһ�ε���֮�ö���ü򵥶��ɿ�����л����ʹ�ã�                   ]" << endl;
	cout << "===============================================================================================" << endl;
}
// �����û�
void loadUser(MyVector<User*>& users) {
	//�½��ļ�������
	ifstream inputFile("user.txt");
	if (!inputFile.is_open()) {
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	//�½����ڶ�ȡÿһ�е��ַ���line
	string line;
	//��ÿһ�ж��浽line��
	while (getline(inputFile, line)) {
		string usertype, username, password;
		istringstream iss(line);
		//�з�line�е�����
		iss >> usertype >> username >> password;
		//����usertype�ж��½�ʲô��Ķ���
		User* t = nullptr;
		if (usertype == "Root") {
			t = new Root(username, password);
		}
		else {
			t = new Common(username, password);
		}
		users.push_back(t);
	}
	inputFile.close();
	return;
}
// ���ص���վ��
void loadStation(AMLGraph<string, double>& graph, Subway& subway) {
	ifstream file("map.txt");
	if (!file.is_open()) {
		cout << "map.txt�ļ���ȡʧ��" << endl;
		return;
	}
	int count = 0;
	string line;
	string station;
	string distance_str;
	string currLine = "";
	while (getline(file, line)) {
		istringstream iss(line);
		iss >> station >> distance_str;
		if (station[0] == '#') {
			// ��ʽ���ʱɾ��#��
			station.erase(0, 1);
			cout << "���ڼ��� ��������" << station << endl;
			subway.addLine(station);
			currLine = station;
			//Sleep(100);
		}
		else {
			subway.addStation(station, currLine);
			if (graph.addVex(station)) {
				count++;
			}
		}
	}
	cout << "վ�������ɣ�����" << count << "��վ�㡣" << endl;
	return;
}
// ���ص���·��
void loadPath(AMLGraph<string, double>& graph) {
	ifstream file("map.txt");
	if (!file.is_open()) {
		cout << "map.txt�ļ���ȡʧ��" << endl;
		return;
	}
	int count = 0;
	string line;
	string station;
	string distance_str;
	double distance;
	MyVector<string> stations;
	MyVector<double> distances;
	while (getline(file, line)) {
		istringstream iss(line);
		iss >> station >> distance_str;
		distance = atof(distance_str.c_str());
		if (station[0] == '#') {
			stations.push_back("#");
			distances.push_back(distance);
		}
		else {
			stations.push_back(station);
			distances.push_back(distance);
		}
	}
	// ��ʼ���·��
	for (int i = 0; i < stations.size() - 1; i++) {
		if (stations[i] == "#" or stations[i + 1] == "#") {
			continue;
		}
		if (graph.addEdge(graph.getVexIndex(stations[i]), graph.getVexIndex(stations[i + 1]), distances[i])) {
			count++;
		}

		//cout << stations[i] << "<-" << distances[i] << "->" << stations[i + 1] << endl;
	}
	cout << "�Ѽ���" << count << "��·�ߡ�" << endl;
	return;
}
// ע��
void User::signUp(MyVector<User*>& data) {
	while (1) {
		system("cls");
		cout << "\t\t\t\t==========================" << endl;
		cout << "\t\t\t\t[   ������������  ע��   ]" << endl;
		cout << "\t\t\t\t==========================" << endl;
		string iusername, ipassword;
		while (1) {
			int flag = 0;
			iusername = "";
			//�û������벿��
			cout << "\t\t\t\t�������û�����";
			int inputCount = 0;
			char usrChar;
			while (1) {
				usrChar = _getch();
				if (usrChar == 13) {
					//ѭ��������������ַ������ڻس�
					cout << endl;
					break;
				}
				if (usrChar == 8 && inputCount > 0) {
					//��ɾ����
					cout << "\b \b";
					iusername.pop_back();//�Ƴ�ĩβ�ַ�
					inputCount--;
				}
				else if (usrChar != 8 && usrChar != 32 && inputCount < 20) {
					//������ʾ�û���
					cout << usrChar;
					iusername.push_back(usrChar);
					inputCount++;
				}
			}
			if (iusername.length() == 0) {
				cout << "\t\t\t\t�û������Ϸ������������룡" << endl;
				Sleep(2000);
				continue;
			}
			//ע�����
			for (int i = 0; i < data.size(); i++) {
				if (data[i]->getUsername() == iusername) {
					cout << "\t\t\t\tע��ʧ�ܣ���������û����Ѵ��ڣ�������ע�ᡣ" << endl;
					Sleep(2000);
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				continue;
			}
			break;
		}
		while (1) {
			//�������벿��
			cout << "\t\t\t\t���������룺";
			int inputCount = 0;
			char pwdChar;
			while (1) {
				pwdChar = _getch();
				if (pwdChar == 13) {
					cout << endl;
					break;
				}
				if (pwdChar == 8 && inputCount > 0) {
					cout << "\b \b";
					ipassword.pop_back();
					inputCount--;
				}
				else if (pwdChar != 8 && inputCount < 20) {
					//���Թ��� 
					cout << "*";
					ipassword.push_back(pwdChar);
					inputCount++;
				}
			}
			if (ipassword.length() == 0) {
				cout << "\t\t\t\t���벻�Ϸ������������룡" << endl;
				ipassword = "";
				Sleep(2000);
				continue;
			}
			break;
		}
		cout << "\t\t\t\tע��ɹ�����ӭ����" << iusername << endl;
		ipassword = encrype(ipassword);
		data.push_back(currUser = new Common(iusername, ipassword));
		saveUser(data);
		Sleep(1500);
		break;
	}
	return;
}
// ��¼
int User::signIn(MyVector<User*>& data) {
	system("cls");
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[   ������������  ��¼   ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	if (data.empty()) {
		cout << "\t\t\t\tϵͳ��û���û�������ע�ᣡ" << endl;
		Sleep(2000);
		return 2;
	}
	for (int i = 4; i >= 0; i--) {
		string iusername, ipassword;
		cout << "\t\t\t\t�������û�����";
		int inputCount = 0;
		char usrChar;
		while (1) {
			usrChar = _getch();
			if (usrChar == 13) {
				//ѭ��������������ַ������ڻس�
				cout << endl;
				break;
			}
			if (usrChar == 8 && inputCount > 0) {
				//��ɾ����
				cout << "\b \b";
				iusername.pop_back();//�Ƴ�ĩβ�ַ�
				inputCount--;
			}
			else if (usrChar != 8 && usrChar != 32 && inputCount < 20) {
				//������ʾ�û���
				cout << usrChar;
				iusername.push_back(usrChar);
				inputCount++;
			}
		}
		//�������벿��
		cout << "\t\t\t\t���������룺";
		inputCount = 0;
		char pwdChar;
		while (1) {
			pwdChar = _getch();
			if (pwdChar == 13) {
				cout << endl;
				break;
			}
			if (pwdChar == 8 && inputCount > 0) {
				cout << "\b \b";
				ipassword.pop_back();
				inputCount--;
			}
			else if (pwdChar != 8 && inputCount < 20) {
				//���Թ��� 
				cout << "*";
				ipassword.push_back(pwdChar);
				inputCount++;
			}
		}
		//�����ϣ����
		ipassword = encrype(ipassword);
		for (int i = 0; i < data.size(); i++) {
			if (data[i]->checkInfo(iusername, ipassword)) {
				//���µ�ǰ�û�
				currUser = data[i];
				//��ӭ��
				if (currUser->getType() == "Root") {
					cout << "\t\t\t\t����Ա��½�ɹ���" << iusername << endl;
				}
				else {
					cout << "\t\t\t\t��½�ɹ�����ӭ����" << iusername << endl;
				}
				Sleep(2000);
				return 1;
			}
		}
		cout << "\t\t\t\t�û�������������㻹��" << i << "�λ��ᣡ" << endl;
	}
	cout << "\t\t\t\t��½ʧ�ܣ�" << endl;
	return 0;
}
// �����û�����
void User::setType(string usertype, MyVector<User*>& data) {
	//ע�����setTypeʱ��һ��Ҫ���û����µ�¼�������ٴ�ʹ�ù���ʱ��ǰ�û��ڵ��Ѿ��ͷ��ˣ�
	//�޷�ֱ���ڲ�ͬ���͵��������ֱ��ת�����������½�һ���µĽڵ�
	User* t = nullptr;
	if (usertype == "Root") {
		t = new Root(this->getUsername(), this->getPassword());
	}
	else {
		t = new Common(this->getUsername(), this->getPassword());
	}
	data.push_back(t);
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == this) {
			data.erase(i);
			return;
		}
	}
	return;
}
int main() {
	AMLGraph<string, double> graph;
	Subway bjsubway;
	MyVector<User*> users;
	loadUser(users);
	cout << "��ӭʹ�ñ���������·С���֣�ϵͳ��ʼ����..." << endl;
	loadStation(graph, bjsubway);
	loadPath(graph);
	double** dist = nullptr;
	int** path = nullptr;
	graph.calculateFloyd(dist, path);
	loading();
	Sleep(1000);
	short defaultX = 39;
	short defaultY = 3;
	int currChoice = 0;
	char inputChar;
	while (1) {
		system("cls");
		cout << "\t\t\t\t==========================" << endl;
		cout << "\t\t\t\t[   ����������·С����   ]" << endl;
		cout << "\t\t\t\t==========================" << endl;
		cout << "\t\t\t\t[     [ ]ͨ��֤��¼      ]" << endl;
		cout << "\t\t\t\t[     [ ]ע��ͨ��֤      ]" << endl;
		cout << "\t\t\t\t[     [ ]���¼ʹ��      ]" << endl;
		cout << "\t\t\t\t[     [ ]���ڱ�ϵͳ      ]" << endl;
		cout << "\t\t\t\t[     [ ]�˳���ϵͳ      ]" << endl;
		cout << "\t\t\t\t==========================";
		printSelection(defaultX, defaultY);
		while (1) {
			inputChar = _getch();
			if (inputChar == 13 or inputChar == '5') {
				// ѭ��������������ַ������ڻس�
				break;
			}
			if ((inputChar == 'w' or inputChar == '8') and currChoice > 0) {
				// ��ͷ�����ƶ�
				printSelection(defaultX, defaultY, true);
				printSelection(defaultX, --defaultY);
				currChoice--;
			}
			else if ((inputChar == 's' or inputChar == '2') and currChoice < 4) {
				// ��ͷ�����ƶ�
				printSelection(defaultX, defaultY, true);
				printSelection(defaultX, ++defaultY);
				currChoice++;
			}
		}
		cout << endl;
		//switch-case��֧
		switch (currChoice) {
			//��¼
			case 0:
				//�жϵ�¼����ֵ
				if (users[0]->signIn(users) != 1) {
					continue;
				}
				//�ɹ���¼������û��˵�ѡ��
				currUser->enterMenu(graph, dist, path, bjsubway, users);
				break;
			//ע��
			case 1:
				users[0]->signUp(users);
				currUser->enterMenu(graph, dist, path, bjsubway, users);
				break;
			//���¼ʹ��
			case 2:
				UnloginedMenu(graph, dist, path, bjsubway);
				break;
			//����
			case 3:
				printAbout();
				PlaySound(TEXT("about.wav"), NULL, SND_FILENAME | SND_ASYNC);
				system("pause");
				PlaySound(NULL, 0, 0);
				break;
			// �˳�
			case 4:
				// ɾ�������ڸ��������㷨��������ά����
				for (int i = 0; i < graph.getVexnum(); ++i) {
					delete[] dist[i];
					dist[i] = nullptr;
					delete[] path[i];
					path[i] = nullptr;
				}
				delete[] dist;
				dist = nullptr;
				delete[] path;
				path = nullptr;
				//���浱ǰ�û�
				saveUser(users);
				return 0;
		}
	}
	return 0;
}