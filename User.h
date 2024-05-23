#pragma once
#include <iostream>
#define NOMINMAX
#include <windows.h>
#include <conio.h>
#include "AML.h"
#include "Subway.h"
#include "voice_func.h"
#include "MyVector.h"
using namespace std;
class User;
User* currUser;
// ������ܺ���
string encrype(string str) {
	//����һ����ϣ�������Զ��ַ��������ݽ��й�ϣ����
	hash<string> hasher;
	//�����ַ����Ĺ�ϣֵ
	size_t hash = hasher(str);
	//����ϣֵת��Ϊ�ַ�����ʾ��ʽ
	return to_string(hash);
}
void loading() {
	for (int i = 0; i <= 10; i++) {
		printf("������: [");
		for (int j = 0; j < i; j++) {
			printf("����");
		}
		for (int j = i; j < 10; j++) {
			printf("  ");
		}
		printf("] %d%%", i * 10);
		if (i < 5) {
			Sleep(100);
		}
		else if (i < 8) {
			Sleep(200);
		}
		else {
			Sleep(300);
		}
		//������
		for (int i = 0; i < 50; i++) {
			printf("\b");
		}
	}
	printf("Done!");
	Sleep(200);
	return;
}
void printMenu() {
	system("cls");
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[   ����������·С����   ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[     [ ]�鿴����վ��    ]" << endl;
	cout << "\t\t\t\t[     [ ]�鿴������·    ]" << endl;
	cout << "\t\t\t\t[     [ ]·�߹滮        ]" << endl;
	cout << "\t\t\t\t[     [ ]�۸����        ]" << endl;
	cout << "\t\t\t\t[     [ ]վ���ѯ        ]" << endl;
	cout << "\t\t\t\t[     [ ]����·ͼ      ]" << endl;
	cout << "\t\t\t\t[     [ ]���·��        ]" << endl;
	cout << "\t\t\t\t[     [ ]����AI����      ]" << endl;
	cout << "\t\t\t\t[     [ ]�޸��˺�����    ]" << endl;
	cout << "\t\t\t\t[     [ ]ע��ͨ��֤      ]" << endl;
	cout << "\t\t\t\t[     [ ]·�߹滮��ʷ    ]" << endl;
	cout << "\t\t\t\t[     [ ]�˳���¼        ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[ Jerry Coding With Love ]" << endl;
	cout << "\t\t\t\t[  ��\"V\"�����л�����ģʽ ]" << endl;
	cout << "\t\t\t\t==========================";
	return;
}
void printUnloginedMenu() {
	system("cls");
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[   ����������·С����   ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[     [ ]�鿴������·    ]" << endl;
	cout << "\t\t\t\t[     [ ]·�߹滮        ]" << endl;
	cout << "\t\t\t\t[     [ ]վ���ѯ        ]" << endl;
	cout << "\t\t\t\t[     [ ]����·ͼ      ]" << endl;
	cout << "\t\t\t\t[     [ ]�˳���ҳ��      ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[    ��¼���ܸ��๦��    ]" << endl;
	cout << "\t\t\t\t==========================";
	return;
}
void printManageMenu() {
	system("cls");
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[  ����������·ά����̨  ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[    [ ]�鿴����վ��     ]" << endl;
	cout << "\t\t\t\t[    [ ]�鿴������·     ]" << endl;
	cout << "\t\t\t\t[    [ ]���վ��         ]" << endl;
	cout << "\t\t\t\t[    [ ]���վ��·��     ]" << endl;
	cout << "\t\t\t\t[    [ ]��ӵ�����·     ]" << endl;
	cout << "\t\t\t\t[    [ ]�л�վ��״̬     ]" << endl;
	cout << "\t\t\t\t[    [ ]ɾ��վ��         ]" << endl;
	cout << "\t\t\t\t[    [ ]ɾ��վ��·��     ]" << endl;
	cout << "\t\t\t\t[    [ ]ɾ��������·     ]" << endl;
	cout << "\t\t\t\t[    [ ]�޸�վ������     ]" << endl;
	cout << "\t\t\t\t[    [ ]�޸���·����     ]" << endl;
	cout << "\t\t\t\t[    [ ]DFS��������      ]" << endl;
	cout << "\t\t\t\t[    [ ]�鿴ͨ��֤       ]" << endl;
	cout << "\t\t\t\t[    [ ]�޸�Ȩ����       ]" << endl;
	cout << "\t\t\t\t[    [ ]ͨ��֤����       ]" << endl;
	cout << "\t\t\t\t[    [ ]ɾ��ͨ��֤       ]" << endl;
	cout << "\t\t\t\t[    [ ]�˳�ά����̨     ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[ Jerry Coding With Love ]" << endl;
	cout << "\t\t\t\t==========================";
	return;
}
// ��λ�ô�ӡ
void printSelection(short x, short y, bool isClear = false) {
	CONSOLE_SCREEN_BUFFER_INFO cursorInfo;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &cursorInfo);
	COORD bakPos = cursorInfo.dwCursorPosition;
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
	if (isClear) {
		cout << " ";
	}
	else {
		cout << "@";
	}
	SetConsoleCursorPosition(hOut, bakPos);
	return;
}
// ����map.txt�ļ�
bool saveMap(AMLGraph<string, double>& graph, Subway& subway) {
	ofstream file("map.txt");
	if (!file.is_open()) {
		cout << "map.txt�ļ���ȡʧ��" << endl;
		return false;
	}
	string suffix = "[CLOSED]";
	// ��ѭ����ѭ������subway�����е�������·
	for (int i = 0; i < subway.getLineNum(); i++) {
		int stationNum = subway.getStationNum(subway.getLineName(i));
		string* stations = subway.getStations(subway.getLineName(i));
		// ��ѭ������ĩβ����[CLOSED]��վ��������[CLOSED]
		for (int j = 0; j < stationNum; j++) {
			if (stations[j].rfind(suffix) == (stations[j].size() - suffix.size())) {
				// ɾ�� "[CLOSED]"
				stations[j] = stations[j].substr(0, stations[j].size() - suffix.size());
			}
		}
		// ��ʽ�����·��Ϣ
		file << "#" << subway.getLineName(i) << "\t0.00" << endl;
		// ��ѭ������������վ���վ���͵���һվ��Ȩֵ
		for (int j = 0; j < stationNum - 1; j++) {
			file << stations[j] << "\t" << graph.getEdgeInfo(graph.getVexIndex(stations[j]), graph.getVexIndex(stations[j + 1])) << endl;
		}
		// ���һվ��Ȩֵ��0
		file << stations[stationNum - 1] << "\t0.00" << endl;
	}
	file.close();
	return true;
}

class User {
private:
	string username;
	string password;
public:
	//���������
	User(string username = "UNKNWON", string password = "UNKNWON") {
		this->username = username;
		this->password = password;
	}
	~User() {}
	//����ʵ��
	void signUp(MyVector<User*>& data);
	int signIn(MyVector<User*>& data);
	virtual string getType() = 0;//��ȡ�û����ͣ����ز�ͬ����
	virtual int enterMenu(AMLGraph<string, double>& graph, double**& dist, int**& path, Subway& bjsubway, MyVector<User*>& data) = 0;//��ͬ�û����벻ͬ�˵�
	int checkInfo(string username, string password) {
		if (this->getUsername() == username && this->getPassword() == password) {
			return 1;
		}
		else {
			return 0;
		}
	}
	void deleteHistory() {
		string line;
		ifstream readFile("history.txt");
		//���history.txt�ļ������ڣ������ofstream�����½��ļ�
		if (!readFile.good()) {
			ofstream createFile("history.txt");
			if (!createFile.is_open()) {
				cout << "\t\t\t\t�޷�����history.txt�ļ���" << endl;
				Sleep(2000);
				return;
			}
			createFile.close();
			readFile.open("history.txt");
		}
		MyVector<string> usernames, starts, ends;
		while (getline(readFile, line)) {
			string username, startStation, endStation;
			istringstream iss(line);
			iss >> username >> startStation >> endStation;
			usernames.push_back(username);
			starts.push_back(startStation);
			ends.push_back(endStation);
		}
		readFile.close();
		//�����ļ�
		ofstream saveFile("history.txt");
		if (!saveFile.is_open()) {
			cout << "�ļ���ʧ�ܣ�" << endl;
			Sleep(2000);
			return;
		}
		string currUserName = this->getUsername();
		for (int i = 0; i < usernames.size(); i++) {
			if (usernames[i] != currUserName) {
				saveFile << usernames[i] << ' ' << starts[i] << ' ' << ends[i] << endl;
			}
		}
		saveFile.close();
		return;
	}
	string getUsername() {
		return this->username;
	}
	string getPassword() {
		return this->password;
	}
	void setPassword(string newPassword) {
		this->password = newPassword;
	}
	void setType(string usertype, MyVector<User*>& data);
	virtual void printUser(MyVector<User*>& data) = 0;//ֻ��Root�ܲ鿴
	virtual int deleteUser(MyVector<User*>& data) = 0;//��Rootֻ��ɾ�Լ�
	virtual int fixType(MyVector<User*>& data) = 0;//ֻ��Root���޸��û�����
	virtual void fixPassword(MyVector<User*>& data) = 0;//��Rootֻ�ܸ��Լ�������
	//���������
	bool operator==(User& obj) {
		if (this->username == obj.username && this->password == obj.password) {
			return true;
		}
		else {
			return false;
		}
	}
	friend ostream& operator<< (ostream& out, User& t) {
		out << setw(7) << t.getType() << setw(8) << t.getUsername();
		return out;
	}
	friend istream& operator>> (istream& in, User& t) {
		cin >> t.username >> t.password;
		return in;
	}
};
// �����û�
void saveUser(MyVector<User*>& users) {
	//�ڹ���ʵ������Ҫ����saveNode�����Ա���Ҫ��ͷ�ڵ�ָ�룬�����õ�ǰ�û��Ľڵ�ʹ��ˣ�
	//�½��ļ������
	ofstream saveFile("user.txt");
	if (!saveFile.is_open()) {
		cout << "�ļ���ʧ�ܣ�" << endl;
		Sleep(2000);
		return;
	}
	//��Ϊ����saveNode�Ķ���ֻ��ͷ�ڵ㣬����thisָ�����ͷ�ڵ�ָ�룬����temp���б���
	for (int i = 0; i < users.size(); i++) {
		//������������ļ�
		saveFile << users[i]->getType() << ' ' << users[i]->getUsername() << ' ' << users[i]->getPassword() << endl;
	}
	saveFile.close();
	return;
}
//================================================================================//
class Root : public User {
public:
	Root(string username, string password) : User(username, password) { }
	string getType() {
		return "Root";
	}
	void printUser(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[         ����Ա  �鿴ͨ��֤           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t Ȩ����  �û���" << endl;
		for (int i = 0; i < data.size(); i++) {
			cout << "\t\t\t\t" << setw(7) << data[i]->getType() << setw(8) << data[i]->getUsername() << endl;
		}
		cout << "\t\t\t\t";
		system("pause");
		return;
	}
	int deleteUser(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[           ͨ��֤  ɾ���û�           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		string currUsername = currUser->getUsername();
		cout << "\t\t\t\t��ǰ���û��������£�" << endl;
		cout << "\t\t\t\t Ȩ����  �û���" << endl;
		for (int i = 0; i < data.size(); i++) {
			cout << "\t\t\t\t" << setw(7) << data[i]->getType() << setw(8) << data[i]->getUsername() << endl;
		}
		string content;
		while (1) {
			int returnValue = 0;
			cout << "\t\t\t\t��������Ҫɾ�����û���";
			cin >> content;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//�ж�Ҫɾ�����û��Ƿ�Ϊ��ǰ��¼�û����Ա�ִ���Զ��˳���¼����
			if (currUser->getUsername() == content) {
				returnValue = 1;
			}
			else {
				returnValue = 0;
			}
			for (int i = 0; i < data.size(); i++) {
				if (data[i]->getUsername() == content) {
					if (returnValue == 0 && data[i]->getType() == "Root") {
						cout << "\t\t\t\t���޷�ɾ�������Լ�����������Ա��ɾ��ʧ�ܡ�" << endl;
						Sleep(1500);
						return 0;
					}
					if (returnValue == 1) {
						cout << "\t\t\t\t��ɾ�����ǵ�ǰ�����û��������˳���¼��" << endl;
					}
					if (data[i]->getType() == "Common") {
						data[i]->deleteHistory();
					}
					//���ú���ģ�壬ɾ���ڵ�
					data.erase(i);
					cout << "\t\t\t\t�û�ɾ���ɹ���" << endl;
					saveUser(data);
					Sleep(3000);
					return returnValue;
				}
			}
			cout << "\t\t\t\t�Ҳ����û��������������û�����" << endl;
			Sleep(2000);
			continue;
		}
		return 0;
	}
	//����Ա�޸�Ȩ����
	int fixType(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[         ����Ա  �޸�Ȩ����           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t��ǰ���û��������£�" << endl;
		cout << "\t\t\t\t Ȩ����  �û���" << endl;
		for (int i = 0; i < data.size(); i++) {
			cout << "\t\t\t\t" << setw(7) << data[i]->getType() << setw(8) << data[i]->getUsername() << endl;
		}
		string content;
		while (1) {
			cout << "\t\t\t\t��������Ҫ�޸ĵ��û���";
			cin >> content;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//����returnValue������ʵ���ж��޸���ɺ��Ƿ���Ҫ�Զ��˳��˺ţ�
			int returnValue = 0;
			//����޸ĵ��ǵ�ǰ�û�����ô�����Զ��˳���¼
			if (currUser->getUsername() == content) {
				returnValue = 1;
			}
			for (int i = 0; i < data.size(); i++) {
				if (data[i]->getUsername() == content) {
					if (returnValue == 0 && data[i]->getType() == "Root") {
						cout << "\t\t\t\t���޷��޸ĳ����Լ�����������Ա��Ȩ���飬�޸�ʧ�ܡ�" << endl;
						Sleep(1500);
						return 0;
					}
					int input;
					cout << "\t\t\t\t[ [1]��ͨ�û� [2]����Ա ]" << endl;
					while (1) {
						cout << "\t\t\t\t��ѡ��Ҫ�޸�Ϊ��Ȩ���飺";
						if (!(cin >> input) || input < 0 || input > 2) {
							cout << "\t\t\t\t��������������������룡" << endl;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							Sleep(2000);
							continue;
						}
						if (input == 2) {
							data[i]->setType("Root", data);
						}
						else {
							data[i]->setType("Common", data);
						}
						cout << "\t\t\t\t�޸���ɣ�";
						saveUser(data);
						if (returnValue == 1) {
							cout << "���޸ĵ��ǵ�ǰ�û���Ȩ���飬�����Զ��˳���¼��" << endl;
						}
						else {
							cout << endl;
						}
						Sleep(3000);
						return returnValue;
					}
				}
			}
			cout << "\t\t\t\t�Ҳ����û��������������û�����" << endl;
			Sleep(2000);
			continue;
		}
	}
	void fixPassword(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[           ͨ��֤  �޸�����           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t��ǰ���û��������£�" << endl;
		cout << "\t\t\t\t Ȩ����  �û���" << endl;
		for (int i = 0; i < data.size(); i++) {
			cout << "\t\t\t\t" << setw(7) << data[i]->getType() << setw(8) << data[i]->getUsername() << endl;
		}
		string content;
		while (1) {
			cout << "\t\t\t\t��������Ҫ�޸ĵ��û���";
			cin >> content;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for (int i = 0; i < data.size(); i++) {
				if (data[i]->getUsername() == content) {
					if (data[i]->getType() == "Root" && currUser->getUsername() != content) {
						cout << "\t\t\t\t���޷��޸ĳ����Լ�����������Ա�����룬�޸�ʧ�ܡ�" << endl;
						Sleep(1500);
						return;
					}
					string ipassword;
					while (1) {
						cout << "\t\t\t\t�ҵ����ݣ��������û� " << content << " ���µ����룺";
						//��������
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
					ipassword = encrype(ipassword);
					//��������
					data[i]->setPassword(ipassword);
					cout << "\t\t\t\t�޸ĳɹ���" << endl;
					saveUser(data);
					Sleep(2000);
					return;
				}
			}
			cout << "\t\t\t\t�Ҳ����û��������������û�����" << endl;
			continue;
		}
	}
	int enterMenu(AMLGraph<string, double>& graph, double**& dist, int**& path, Subway& bjsubway, MyVector<User*>& data) {
		short defaultX = 38;
		short defaultY = 3;
		int currChoice = 0;
		char inputChar;
		char charinput;
		while (1) {
			printManageMenu();
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
				else if ((inputChar == 's' or inputChar == '2') and currChoice < 16) {
					// ��ͷ�����ƶ�
					printSelection(defaultX, defaultY, true);
					printSelection(defaultX, ++defaultY);
					currChoice++;
				}
			}
			cout << endl;
			// ��switch-case������ı����������ﶨ��
			string stationName, lineName, begin, end, command, oldLineName, oldStationName;
			string* stations = nullptr;
			stringstream stationInfo, lineInfo;
			int stationIndex = -1, beginIndex = -1, endIndex = -1, addType = 0, stationNum = 0, oldStationIndex = -1, flag = 0;
			double s, s2;
			switch (currChoice) {

			case 0:
				cout << "���е���վ���£�" << endl;
				graph.printGraph();
				system("pause");
				break;
			case 1:
				cout << "��ǰ���°��ͼ����������·��" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "�밴��������ʾ������Ҫ��ѯ�ĵ�����·��";
					if (!(cin >> lineName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					break;
				}
				if (bjsubway.printLineInfo(lineName)) {
					while (1) {
						cout << "�Ƿ�鿴����·�ĸ�����Ϣ(y/n)��";
						if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						break;
					}
					if (charinput == 'y') {
						if (lineName == "17���߱���") {
							lineName = "17����";
							lineInfo << "start " << "https://baike.baidu.com/item/��������" << lineName;
						}
						else if (lineName == "��ׯT1��") {
							lineName = "��ׯ�³��ִ��й�糵T1��";
							lineInfo << "start " << "https://baike.baidu.com/item/" << lineName;
						}
						else {
							lineInfo << "start " << "https://baike.baidu.com/item/��������" << lineName;
						}

						command = lineInfo.str();
						if (!system(command.c_str())) {
							cout << "�ѳɹ��򿪱�������" << lineName << "��������Ϣ��" << endl;
						}
						else {
							cout << "�޷�����ҳ��" << endl;
						}
						Sleep(2000);
					}
				}
				else {
					cout << "���������·�����ڣ�" << endl;
				}
				system("pause");
				break;
			case 2:

				while (1) {
					cout << "��������Ҫ��ӵ�վ�����ƣ�";
					if (!(cin >> stationName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					break;
				}
				graph.freeDistAndPath(dist, path);
				graph.addVex(stationName);
				graph.calculateFloyd(dist, path);
				cout << "������" << endl;
				system("pause");
				break;
			case 3:
				cout << "���վ��·�߹�����������վ�㣬����վ�����ڣ���һ���͵�����վ����ڣ��ڶ���վ��Ϊ��վ�㣬�Ӷ�����վ����뵽�ɵ�վ��֮�С�\n������ѡ���Ƿ������һ��վ��͵�����վ�㣬�����ﵽǰ��ͺ���Ч����" << endl;
				cout << "��ǰ���°��ͼ����������·��" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "��������Ҫ��������·��";
					if (!(cin >> lineName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) == -1) {
						cout << "���������·�����ڣ����������룡" << endl;
						continue;
					}
					break;
				}
				bjsubway.printLineInfo(lineName);
				while (1) {

					while (1) {
						cout << "�������µĵ���վ����";
						if (!(cin >> stationName)) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						stationIndex = graph.getVexIndex(stationName);
						if (stationIndex == -1) {
							cout << "������������ĵ���վ�����������룡" << endl;
							continue;
						}
						if (!graph.getVexEnabled(stationIndex)) {
							cout << "������ĵ���վΪ�ر�״̬���޷��Դ˽��в��������������룡" << endl;
							continue;
						}
						break;
					}

					while (1) {
						cout << "������ǰһ������վ��������nΪ���Դ�ѡ���";
						if (!(cin >> begin)) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						if (begin != "n") {
							beginIndex = graph.getVexIndex(begin);
							if (beginIndex == -1) {
								cout << "������������ĵ���վ�����������룡" << endl;
								continue;
							}
							if (!graph.getVexEnabled(stationIndex)) {
								cout << "������ĵ���վΪ�ر�״̬���޷��Դ˽��в��������������룡" << endl;
								continue;
							}
						}
						break;
					}

					while (1) {
						cout << "�������һ������վ��������nΪ���Դ�ѡ���";
						if (!(cin >> end)) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						if (end != "n") {
							endIndex = graph.getVexIndex(end);
							if (endIndex == -1) {
								cout << "������������ĵ���վ�����������룡" << endl;
								continue;
							}
							if (!graph.getVexEnabled(stationIndex)) {
								cout << "������ĵ���վΪ�ر�״̬���޷��Դ˽��в��������������룡" << endl;
								continue;
							}
						}
						break;
					}

					if (begin == "n" and end == "n") {
						cout << "������ͬʱ��������ǰ������վ�㣡����������վ�㡣" << endl;
						system("pause");
						continue;
					}
					else if (begin == "n" and end != "n") {
						// ǰ��
						addType = 1;
					}
					else if (begin != "n" and end == "n") {
						// ���
						addType = 2;
					}
					else {
						if (abs(bjsubway.stationIndex(begin, lineName) - bjsubway.stationIndex(end, lineName)) != 1) {
							cout << "�������վ�㲻���ڣ����������룡" << endl;
							system("pause");
							continue;
						}
						// Ĭ���м��
					}
					if (addType == 0) {
						while (1) {
							cout << "��������վ����ǰһվ���ľ��룺";
							if (!(cin >> s)) {
								cout << "��������������������룡" << endl;
								//������뻺����
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								system("pause");
								continue;
							}
							break;
						}
						while (1) {
							cout << "��������վ�����һվ���ľ��룺";
							if (!(cin >> s2)) {
								cout << "��������������������룡" << endl;
								//������뻺����
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								system("pause");
								continue;
							}
							break;
						}
					}
					else {
						while (1) {
							cout << "���������������վ���ľ��룺";
							if (!(cin >> s)) {
								cout << "��������������������룡" << endl;
								//������뻺����
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								system("pause");
								continue;
							}
							break;
						}
					}
					break;
				}
				graph.freeDistAndPath(dist, path);
				// �м����
				if (addType == 0) {
					bjsubway.insertStation(begin, stationName, lineName);
					graph.deleteEdge(beginIndex, endIndex);
					graph.addEdge(beginIndex, stationIndex, s);
					graph.addEdge(endIndex, stationIndex, s2);
				}
				// ǰ��
				else if (addType == 1) {
					bjsubway.insertStation(lineName, stationName, lineName);
					graph.addEdge(endIndex, stationIndex, s);
				}
				// ���
				else {
					bjsubway.addStation(stationName, lineName);
					graph.addEdge(beginIndex, stationIndex, s);
				}
				graph.calculateFloyd(dist, path);
				cout << "վ��·����ӳɹ���" << endl;
				system("pause");
				break;
			case 4:
				cout << "��ǰ���°��ͼ����������·��" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "��������Ҫ��������·��";
					if (!(cin >> lineName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) != -1) {
						cout << "���������·�Ѵ��ڣ����������룡" << endl;
						continue;
					}
					break;
				}
				bjsubway.addLine(lineName);
				cout << "������·�����ɣ��������վ����Ϊ��·���һ����ʼվ��" << endl;
				while (1) {
					cout << "�������µĵ���վ����";
					if (!(cin >> stationName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex == -1) {
						cout << "������������ĵ���վ�����������룡" << endl;
						continue;
					}
					break;
				}
				bjsubway.addStation(stationName, lineName);
				cout << "��ʼվ��������" << endl;
				system("pause");
				break;
			case 5:
				while (1) {
					cout << "������Ҫ�л�״̬����վ����";
					if (!(cin >> stationName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex == -1) {
						cout << "������������ĵ���վ�����������룡" << endl;
						continue;
					}
					break;
				}
				graph.freeDistAndPath(dist, path);
				if (graph.changeVexStatus(stationIndex) == 0) {
					cout << "��ǰվ��״̬Ϊͣ�ã����л�Ϊ����" << endl;
					bjsubway.modifyStationNameAllLine(stationName + "[CLOSED]", stationName);
					graph.updateVexData(stationIndex, stationName);
				}
				else {
					cout << "��ǰվ��״̬Ϊ���ã����л�Ϊͣ��" << endl;
					bjsubway.modifyStationNameAllLine(stationName, stationName + "[CLOSED]");
					graph.updateVexData(stationIndex, stationName + "[CLOSED]");
				}
				graph.calculateFloyd(dist, path);
				system("pause");
				break;
			case 6:
				while (1) {
					cout << "������Ҫɾ���ĵ���վ����";
					if (!(cin >> stationName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex == -1) {
						cout << "������������ĵ���վ�����������룡" << endl;
						continue;
					}
					break;
				}
				graph.freeDistAndPath(dist, path);
				if (graph.getVexEnabled(stationIndex)) {
					bjsubway.deleteStationAllLine(stationName);
				}
				else {
					bjsubway.deleteStationAllLine(stationName + "[CLOSED]");
				}
				graph.deleteVex(stationIndex);
				graph.calculateFloyd(dist, path);
				cout << "��ɾ��" << stationName << "վ" << endl;
				system("pause");
				break;
			case 7:
				cout << "ɾ��վ��·�߹�����������վ�㣬����վ�����ڣ���һ���͵�����վ����ڣ��ڶ���վ��ΪҪɾ����վ�㡣\n������ѡ���Ƿ������һ��վ��͵�����վ�㣬�����ﵽǰɾ�ͺ�ɾ��Ч����" << endl;
				cout << "��ǰ���°��ͼ����������·��" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "��������Ҫ��������·��";
					if (!(cin >> lineName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) == -1) {
						cout << "���������·�����ڣ����������룡" << endl;
						continue;
					}
					break;
				}
				bjsubway.printLineInfo(lineName);
				while (1) {
					while (1) {
						cout << "������Ҫɾ���ĵ���վ����";
						if (!(cin >> stationName)) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						stationIndex = graph.getVexIndex(stationName);
						if (stationIndex == -1) {
							cout << "������������ĵ���վ�����������룡" << endl;
							continue;
						}
						if (!graph.getVexEnabled(stationIndex)) {
							cout << "������ĵ���վΪ�ر�״̬���޷��Դ˽��в��������������룡" << endl;
							continue;
						}
						break;
					}

					while (1) {
						cout << "������ǰһ������վ��������nΪ���Դ�ѡ���";
						if (!(cin >> begin)) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						if (begin != "n") {
							beginIndex = graph.getVexIndex(begin);
							if (beginIndex == -1) {
								cout << "������������ĵ���վ�����������룡" << endl;
								continue;
							}
							if (!graph.getVexEnabled(stationIndex)) {
								cout << "������ĵ���վΪ�ر�״̬���޷��Դ˽��в��������������룡" << endl;
								continue;
							}
						}
						break;
					}

					while (1) {
						cout << "�������һ������վ��������nΪ���Դ�ѡ���";
						if (!(cin >> end)) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						if (end != "n") {
							endIndex = graph.getVexIndex(end);
							if (endIndex == -1) {
								cout << "������������ĵ���վ�����������룡" << endl;
								continue;
							}
							if (!graph.getVexEnabled(stationIndex)) {
								cout << "������ĵ���վΪ�ر�״̬���޷��Դ˽��в��������������룡" << endl;
								continue;
							}
						}
						break;
					}

					if (begin == "n" and end == "n") {
						cout << "������ͬʱ��������ǰ������վ�㣡����������վ�㡣" << endl;
						system("pause");
						continue;
					}
					else if (begin == "n" and end != "n") {
						// ǰɾ
						addType = 1;
					}
					else if (begin != "n" and end == "n") {
						// ��ɾ
						addType = 2;
					}
					else {
						if (abs(bjsubway.stationIndex(begin, lineName) - bjsubway.stationIndex(end, lineName)) != 2) {
							cout << "�������վ�㲻���ڣ����������룡" << endl;
							system("pause");
							continue;
						}
						while (1) {
							cout << "������ɾ��֮��ǰ����վ���ľ��룺";
							if (!(cin >> s)) {
								cout << "��������������������룡" << endl;
								//������뻺����
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								system("pause");
								continue;
							}
							break;
						}
						// Ĭ���м��
					}

					break;
				}
				graph.freeDistAndPath(dist, path);
				// �м�ɾ
				if (addType == 0) {
					bjsubway.deleteStation(stationName, lineName);
					graph.deleteEdge(beginIndex, stationIndex);
					graph.deleteEdge(stationIndex, endIndex);
					graph.addEdge(beginIndex, endIndex, s);
					// �м�ɾ��ʱ�����Ҫɾ�Ľڵ���������·�ϻ�����ϵ���Ͳ�ɾ��һվ�������ɾ����һվ
					if (graph.isVexAlone(graph.getVexIndex(stationName))) {
						graph.deleteVex(graph.getVexIndex(stationName));
					}
				}
				// ǰɾ
				else if (addType == 1) {
					bjsubway.deleteStation(stationName, lineName);
					graph.deleteEdge(stationIndex, endIndex);
					if (graph.isVexAlone(graph.getVexIndex(stationName))) {
						graph.deleteVex(graph.getVexIndex(stationName));
					}
				}
				// ��ɾ
				else {
					bjsubway.deleteStation(stationName, lineName);
					graph.deleteEdge(beginIndex, stationIndex);
					if (graph.isVexAlone(graph.getVexIndex(stationName))) {
						graph.deleteVex(graph.getVexIndex(stationName));
					}
				}
				graph.calculateFloyd(dist, path);
				cout << "վ��·��ɾ���ɹ���" << endl;
				system("pause");
				break;
			case 8:
				cout << "��ǰ���°��ͼ����������·��" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "��������Ҫɾ������·��";
					if (!(cin >> lineName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) == -1) {
						cout << "���������·�����ڣ����������룡" << endl;
						continue;
					}
					break;
				}
				graph.freeDistAndPath(dist, path);
				stations = bjsubway.getStations(lineName);
				stationNum = bjsubway.getStationNum(lineName);
				// ѭ��ɾ����·
				for (int i = 0; i < stationNum - 1; i++) {
					// �����·����һ������·����ʱ����ɾ����
					if (bjsubway.getStationPathInAllLine(stations[i], stations[i + 1]) <= 1) {
						graph.deleteEdge(graph.getVexIndex(stations[i]), graph.getVexIndex(stations[i + 1]));
					}
				}
				// �¶��Ľڵ�ֱ��ɾ��
				for (int i = 0; i < stationNum; i++) {
					if (graph.isVexAlone(graph.getVexIndex(stations[i]))) {
						graph.deleteVex(graph.getVexIndex(stations[i]));
					}
				}
				bjsubway.deleteLine(lineName);
				graph.calculateFloyd(dist, path);
				cout << "��·��ɾ����ɣ�" << endl;
				system("pause");
				break;
			case 9:
				while (1) {
					cout << "������Ҫ�޸ĵĵ���վ����";
					if (!(cin >> oldStationName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					oldStationIndex = graph.getVexIndex(oldStationName);
					if (oldStationIndex == -1) {
						cout << "������������ĵ���վ�����������룡" << endl;
						continue;
					}
					break;
				}
				while (1) {
					cout << "�������µĵ���վ����";
					if (!(cin >> stationName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex != -1) {
						cout << "��������µĵ���վ���Ѵ��ڣ����������룡" << endl;
						continue;
					}
					break;
				}

				if (graph.getVexEnabled(oldStationIndex)) {
					bjsubway.modifyStationNameAllLine(oldStationName, stationName);
					graph.updateVexData(oldStationIndex, stationName);
				}
				else {
					bjsubway.modifyStationNameAllLine(oldStationName + "[CLOSED]", stationName + "[CLOSED]");
					graph.updateVexData(oldStationIndex, stationName + "[CLOSED]");
				}
				cout << "վ�����޸ĳɹ�" << endl;
				system("pause");
				break;
			case 10:
				cout << "��ǰ���°��ͼ����������·��" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "��������Ҫ�޸ĵ���·���ƣ�";
					if (!(cin >> oldLineName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(oldLineName) == -1) {
						cout << "���������·���Ʋ����ڣ����������룡" << endl;
						continue;
					}
					break;
				}
				while (1) {
					cout << "�������µ���·���ƣ�";
					if (!(cin >> lineName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) != -1) {
						cout << "���������·�����Ѵ��ڣ����������룡" << endl;
						continue;
					}
					break;
				}
				bjsubway.modifyLineName(oldLineName, lineName);
				cout << "��·�����޸����" << endl;
				system("pause");
				break;
			case 11:
				cout << "����������վ��ӵ�һ��վ�㿪ʼDFS�����Ľ����" << endl;
				graph.dfsTraverse();
				system("pause");
				break;
			case 12:
				currUser->printUser(data);
				break;
			case 13:
				if (currUser->fixType(data)) {
					flag = 1;
				}
				break;
			case 14:
				currUser->fixPassword(data);
				break;
			case 15:
				if (currUser->deleteUser(data)) {
					flag = 1;
				}
				break;
			case 16:
				while (1) {
					cout << "�˳���ʾ: �Ƿ�Ҫ�����������ͼ�ļ�?(y/n)��";
					if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						continue;
					}
					break;
				}
				if (charinput == 'y') {
					if (saveMap(graph, bjsubway)) cout << "����ɹ�������2����˳�" << endl;
					Sleep(2000);
				}
				currUser = nullptr;
				return 0;
			}
			if (flag == 1) {
				break;
			}
		}

		return 0;
	}
};
//================================================================================//
class Common : public User {
public:
	Common(string username, string password) : User(username, password) { }
	string getType() {
		return "Common";
	}
	void printUser(MyVector<User*>& data) {
		cout << "\t\t\t\tû��Ȩ�ޣ�" << endl;
		return;
	}
	int deleteUser(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[           ͨ��֤  �û�ע��           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		int input, flag = 0;
		cout << "\t\t\t\t���棡�����ڽ��е�ǰ�û���" << currUser->getUsername() << " ��ע��������" << endl;
		while (1) {
			cout << "\t\t\t\t�Ƿ�ȷ��ע����[1]ȷ��  [0]ȡ����";
			if (!(cin >> input) || input < 0 || input > 1) {
				cout << "\t\t\t\t��������������������룡" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				Sleep(2000);
				continue;
			}
			if (input == 1) {
				//ֱ�ӵ���deleteNodeɾ����ǰ�ڵ�
				for (int i = 0; i < data.size(); i++) {
					if (data[i] == currUser) {
						data[i]->deleteHistory();
						data.erase(i);
						break;
					}
				}
				cout << "\t\t\t\t�˻�ע���ɹ���" << endl;
				saveUser(data);
				Sleep(2000);
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	int fixType(MyVector<User*>& data) {
		cout << "\t\t\t\tû��Ȩ�ޣ�" << endl;
		return 0;
	}
	void fixPassword(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[           ͨ��֤  �޸�����           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		string ipassword;
		while (1) {
			cout << "\t\t\t\t���������������룺";
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
		ipassword = encrype(ipassword);
		currUser->setPassword(ipassword);
		cout << "\t\t\t\t�޸ĳɹ��������˳���" << endl;
		saveUser(data);
		Sleep(2000);
		return;
	}
	void saveHistory(string startStation, string endStation) {
		//��׷�ӷ�ʽ���ļ�
		ofstream saveFile("history.txt", ios::app);
		if (!saveFile.is_open()) {
			cout << "�ļ���ʧ�ܣ�" << endl;
			Sleep(2000);
			return;
		}
		//getTime()���µ�ǰʱ�䣬����ֵΪ�ַ���
		saveFile << currUser->getUsername() << ' ' << startStation << ' ' << endStation << endl;
		saveFile.close();
		return;
	}
	void printHistory() {
		int printCount = 0;
		string line;
		ifstream readFile("history.txt");
		//���history.txt�ļ������ڣ������ofstream�����½��ļ�
		if (!readFile.good()) {
			ofstream createFile("history.txt");
			if (!createFile.is_open()) {
				cout << "\t\t\t\t�޷�����history.txt�ļ���" << endl;
				Sleep(2000);
				return;
			}
			createFile.close();
			readFile.open("history.txt");
		}
		system("cls");
		cout << "\t\t\t\t==========================" << endl;
		cout << "\t\t\t\t[    �ҵ���ʷ��·�滮    ]" << endl;
		cout << "\t\t\t\t==========================" << endl;
		while (getline(readFile, line)) {
			string username, startStation, endStation;
			istringstream iss(line);
			iss >> username >> startStation >> endStation;
			//�ж�������ļ��ǲ��ǵ�ǰ�û�
			if (currUser->getUsername() != username) {
				continue;
			}
			cout << "\t\t\t\t" << startStation << " --> " << endStation << endl;
			printCount++;
		}
		readFile.close();
		if (printCount == 0) {
			cout << "\t\t\t\t������ʷ·�߹滮��ȥ����·�߹滮���ܰɣ�" << endl;
		}
		cout << "\t\t\t\t";
		system("pause");
		return;
	}
	int enterMenu(AMLGraph<string, double>& graph, double**& dist, int**& path, Subway& bjsubway, MyVector<User*>& data) {
		voiceMode = true;
		short defaultX = 39;
		short defaultY = 3;
		int currChoice = 0;
		char inputChar;
		while (1) {
			printMenu();
			printSelection(defaultX, defaultY);
			while (1) {
				inputChar = _getch();
				if (inputChar == 13 or inputChar == '5') {
					// ѭ��������������ַ������ڻس�
					break;
				}
				if (inputChar == 'F') {
					system("start Python�������.bat");
					Sleep(1000);
					system("start ������·��ѯǰ��.html");
				}
				if (inputChar == 'V') {
					if (voiceMode == false) {
						voiceMode = true;
						cout << "\n�ѿ�������ģʽ";
						if (voiceMode) speakString("�ѿ�������ģʽ");
						Sleep(1500);
						printMenu();
						printSelection(defaultX, defaultY);
					}
					else {
						voiceMode = false;
						cout << "\n�ѹر�����ģʽ";
						Sleep(1500);
						printMenu();
						printSelection(defaultX, defaultY);
					}
				}
				if ((inputChar == 'w' or inputChar == '8') and currChoice > 0) {
					// ��ͷ�����ƶ�
					printSelection(defaultX, defaultY, true);
					printSelection(defaultX, --defaultY);
					currChoice--;
				}
				else if ((inputChar == 's' or inputChar == '2') and currChoice < 11) {
					// ��ͷ�����ƶ�
					printSelection(defaultX, defaultY, true);
					printSelection(defaultX, ++defaultY);
					currChoice++;
				}
			}
			cout << endl;
			// ��switch-case������ı����������ﶨ��
			string stationName, lineName, begin, end, command, suffix = "վ";
			stringstream stationInfo, lineInfo;
			MyVector<string> stationNames;
			stringstream voiceString;
			int stationIndex, beginIndex, endIndex, flag=0;
			double s;
			char charinput;
			switch (currChoice) {

				case 0:
					cout << "���е���վ���£�" << endl;
					graph.printGraph();
					if (voiceMode) speakString("���е���վ����");
					system("pause");
					break;
				case 1:
					cout << "��ǰ���°��ͼ����������·��" << endl;
					bjsubway.printLineNames();
					if (voiceMode) speakString("��ǰ���°��ͼ����������·");
					while (1) {
						cout << "�밴��������ʾ������Ҫ��ѯ�ĵ�����·��";
						if (voiceMode) speakString("�밴��������ʾ������Ҫ��ѯ�ĵ�����·");
						if (!(cin >> lineName)) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						break;
					}
					if (bjsubway.printLineInfo(lineName)) {
						while (1) {
							cout << "�Ƿ�鿴����·�ĸ�����Ϣ(y/n)��";
							if (voiceMode) speakString("�Ƿ�鿴����·�ĸ�����Ϣ");
							if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
								cout << "��������������������룡" << endl;
								if (voiceMode) speakString("���������������������");
								//������뻺����
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								continue;
							}
							break;
						}
						if (charinput == 'y') {
							if (lineName == "17���߱���") {
								lineName = "17����";
								lineInfo << "start " << "https://baike.baidu.com/item/��������" << lineName;
							}
							else if (lineName == "��ׯT1��") {
								lineName = "��ׯ�³��ִ��й�糵T1��";
								lineInfo << "start " << "https://baike.baidu.com/item/" << lineName;
							}
							else {
								lineInfo << "start " << "https://baike.baidu.com/item/��������" << lineName;
							}

							command = lineInfo.str();
							if (!system(command.c_str())) {
								cout << "�ѳɹ��򿪱�������" << lineName << "��������Ϣ��" << endl;
								if (voiceMode) {
									voiceString.str("");  // ���stringstream����
									voiceString << "�ѳɹ��򿪱�������" << lineName << "��������Ϣ��";
									speakString(voiceString.str());
								}
							}
							else {
								cout << "�޷�����ҳ��" << endl;
								if (voiceMode) speakString("�޷�����ҳ");
							}
							Sleep(1000);
						}
					}
					else {
						cout << "���������·�����ڣ�" << endl;
						if (voiceMode) speakString("���������·������");
					}
					system("pause");
					break;
				case 2:
					while (1) {
						cout << "������������վ����";
						if (voiceMode) speakString("������������վ��");
						if (!(cin >> begin)) {
							cout << "��������������������룡" << endl;
							if (voiceMode) speakString("���������������������");
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						beginIndex = graph.getVexIndex(begin);
						if (beginIndex == -1) {
							cout << "������������ĵ���վ�����������룡" << endl;
							if (voiceMode) speakString("������������ĵ���վ������������");
							continue;
						}
						break;
					}
					while (1) {
						cout << "�������յ����վ����";
						if (voiceMode) speakString("�������յ����վ��");
						if (!(cin >> end)) {
							cout << "��������������������룡" << endl;
							if (voiceMode) speakString("���������������������");
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						endIndex = graph.getVexIndex(end);
						if (endIndex == -1) {
							cout << "������������ĵ���վ�����������룡" << endl;
							if (voiceMode) speakString("������������ĵ���վ������������");
							continue;
						}
						if (endIndex == beginIndex) {
							cout << "������ԭ��TP�أ����������룡" << endl;
							if (voiceMode) speakString("������ԭ��TP�أ����������룡");
							continue;
						}
						break;
					}
					// �����ѯ��ʷ
					saveHistory(begin, end);
					// ��������
					stationNames = graph.printFloydShortestPath(beginIndex, endIndex, dist, path);
					bjsubway.printTransferInformation(stationNames);
					// BFS
					stationNames = graph.printBFSPath(beginIndex, endIndex);
					bjsubway.printTransferInformation(stationNames);
					system("pause");
					break;
				case 3:
					while (1) {
						cout << "�������������(km)��";
						if (voiceMode) speakString("�������������");
						if (!(cin >> s)) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						break;
					}
					cout << "Ʊ�ۣ�" << costCalculate(s) << "Ԫ" << endl;
					if (voiceMode) {
						voiceString.str("");
						voiceString << "Ʊ�ۣ�" << costCalculate(s) << "Ԫ";
						speakString(voiceString.str());
					}
					system("pause");
					break;
				case 4:
					while (1) {
						cout << "��������Ҫ���ҵĵ���վ����";
						if (voiceMode) speakString("��������Ҫ���ҵĵ���վ��");
						if (!(cin >> stationName)) {
							cout << "��������������������룡" << endl;
							if (voiceMode) speakString("���������������������");
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						break;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex != -1) {
						cout << "���ҳɹ��������Ǹõ���վ��Ϣ��" << endl;
						if (voiceMode) speakString("���ҳɹ��������Ǹõ���վ��Ϣ");
						graph.printVexInfo(stationIndex);
						while (1) {
							cout << "�Ƿ�鿴��վ����ܱ���Ϣ(y/n)��";
							if (voiceMode) speakString("�Ƿ�鿴��վ����ܱ���Ϣ");
							if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
								cout << "��������������������룡" << endl;
								if (voiceMode) speakString("���������������������");
								//������뻺����
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								continue;
							}
							break;
						}
						if (charinput == 'y') {
							// ���վ������"վ"��
							if (stationName.rfind(suffix) == (stationName.size() - suffix.size())) {
								stationInfo << "start " << "https://baike.baidu.com/item/" << stationName;
							}
							else {
								stationInfo << "start " << "https://baike.baidu.com/item/" << stationName << "վ";
							}
							command = stationInfo.str();
							if (!system(command.c_str())) {
								cout << "�ѳɹ���" << stationName << "վ��������Ϣ��" << endl;
								if (voiceMode) {
									voiceString.str("");
									voiceString << "�ѳɹ���" << stationName << "վ��������Ϣ";
									speakString(voiceString.str());
								}
							}
							else {
								cout << "�޷�����ҳ��" << endl;
								if (voiceMode) speakString("�޷�����ҳ");
							}
							Sleep(2000);
						}
					}
					else {
						cout << "�Ҳ���������ĵ���վ��" << endl;
						if (voiceMode) speakString("�Ҳ���������ĵ���վ");
					}
					system("pause");
					break;
				case 5:
					command = "start lwt.png";
					if (!system(command.c_str())) {
						cout << "������·ͼ�ѳɹ��򿪡�" << endl;
						if (voiceMode) speakString("������·ͼ�ѳɹ���");
					}
					else {
						cout << "�޷����ļ���" << endl;
						if (voiceMode) speakString("�޷����ļ�");
					}
					Sleep(1000);
					break;

				case 6:
					cout << "��Ϊ�������������վ���·�߹滮��" << endl;
					if (voiceMode) speakString("��Ϊ�������������վ���·�߹滮");
					srand(time(0));
					beginIndex = graph.getRandomVexIndex();
					endIndex = graph.getRandomVexIndex();
					// ��������
					stationNames = graph.printFloydShortestPath(beginIndex, endIndex, dist, path);
					bjsubway.printTransferInformation(stationNames);
					// BFS
					stationNames = graph.printBFSPath(beginIndex, endIndex);
					bjsubway.printTransferInformation(stationNames);
					system("pause");
					break;
				case 7:
					system("start PythonAI����.bat");
					cout << "��������������AI����" << endl;
					if (voiceMode) speakString("��������������AI����");
					Sleep(1000);
					break;
				case 8:
					currUser->fixPassword(data);
					break;
				case 9:
					if (currUser->deleteUser(data)) {
						flag = 1;
					}
					break;
				case 10:
					printHistory();
					break;
				case 11:
					cout << "\n��л��ʹ��Jerry�����ġ�����������·С���֡��������´��ټ���" << endl;
					if (voiceMode) speakString("��л��ʹ��Jerry�����ġ�����������·С���֡��������´��ټ�");
					if (voiceMode) speakString("Thank you for taking beijing subway, have a nice day!", 3);
					currUser = nullptr;
					return 0;
			}
			if (flag == 1) {
				break;
			}
		}
		return 0;
	}
};

int UnloginedMenu(AMLGraph<string, double>& graph, double**& dist, int**& path, Subway& bjsubway) {
	bool voiceModeBak = voiceMode;
	voiceMode = false;
	short defaultX = 39;
	short defaultY = 3;
	int currChoice = 0;
	char inputChar;
	while (1) {
		printUnloginedMenu();
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
		// ��switch-case������ı����������ﶨ��
		string stationName, lineName, begin, end, command, suffix = "վ";
		stringstream stationInfo, lineInfo;
		MyVector<string> stationNames;
		int stationIndex, beginIndex, endIndex;
		char charinput;
		switch (currChoice) {

			case 0:
				cout << "��ǰ���°��ͼ����������·��" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "�밴��������ʾ������Ҫ��ѯ�ĵ�����·��";
					if (!(cin >> lineName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					break;
				}
				if (bjsubway.printLineInfo(lineName)) {
					while (1) {
						cout << "�Ƿ�鿴����·�ĸ�����Ϣ(y/n)��";
						if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						break;
					}
					if (charinput == 'y') {
						if (lineName == "17���߱���") {
							lineName = "17����";
							lineInfo << "start " << "https://baike.baidu.com/item/��������" << lineName;
						}
						else if (lineName == "��ׯT1��") {
							lineName = "��ׯ�³��ִ��й�糵T1��";
							lineInfo << "start " << "https://baike.baidu.com/item/" << lineName;
						}
						else {
							lineInfo << "start " << "https://baike.baidu.com/item/��������" << lineName;
						}

						command = lineInfo.str();
						if (!system(command.c_str())) {
							cout << "�ѳɹ��򿪱�������" << lineName << "��������Ϣ��" << endl;
						}
						else {
							cout << "�޷�����ҳ��" << endl;
						}
						Sleep(1000);
					}
				}
				else {
					cout << "���������·�����ڣ�" << endl;
				}
				system("pause");
				break;
			case 1:
				while (1) {
					cout << "������������վ����";
					if (!(cin >> begin)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					beginIndex = graph.getVexIndex(begin);
					if (beginIndex == -1) {
						cout << "������������ĵ���վ�����������룡" << endl;
						continue;
					}
					break;
				}
				while (1) {
					cout << "�������յ����վ����";
					if (!(cin >> end)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					endIndex = graph.getVexIndex(end);
					if (endIndex == -1) {
						cout << "������������ĵ���վ�����������룡" << endl;
						continue;
					}
					if (endIndex == beginIndex) {
						cout << "������ԭ��TP�أ����������룡" << endl;
						continue;
					}
					break;
				}
				// ��������
				stationNames = graph.printFloydShortestPath(beginIndex, endIndex, dist, path);
				// BFS
				stationNames = graph.printBFSPath(beginIndex, endIndex);
				system("pause");
				break;
			case 2:
				while (1) {
					cout << "��������Ҫ���ҵĵ���վ����";
					if (!(cin >> stationName)) {
						cout << "��������������������룡" << endl;
						//������뻺����
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					break;
				}
				stationIndex = graph.getVexIndex(stationName);
				if (stationIndex != -1) {
					cout << "���ҳɹ��������Ǹõ���վ��Ϣ��" << endl;
					graph.printVexInfo(stationIndex);
					while (1) {
						cout << "�Ƿ�鿴��վ����ܱ���Ϣ(y/n)��";
						if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
							cout << "��������������������룡" << endl;
							//������뻺����
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						break;
					}
					if (charinput == 'y') {
						// ���վ������"վ"��
						if (stationName.rfind(suffix) == (stationName.size() - suffix.size())) {
							stationInfo << "start " << "https://baike.baidu.com/item/" << stationName;
						}
						else {
							stationInfo << "start " << "https://baike.baidu.com/item/" << stationName << "վ";
						}
						command = stationInfo.str();
						if (!system(command.c_str())) {
							cout << "�ѳɹ���" << stationName << "վ��������Ϣ" << endl;
						}
						else {
							cout << "�޷�����ҳ��" << endl;
						}
						Sleep(2000);
					}
				}
				else {
					cout << "�Ҳ���������ĵ���վ��" << endl;
				}
				system("pause");
				break;
			case 3:
				command = "start lwt.png";
				if (!system(command.c_str())) {
					cout << "������·ͼ�ѳɹ��򿪡�" << endl;
				}
				else {
					cout << "�޷����ļ���" << endl;
				}
				Sleep(1000);
				break;
			case 4:
				voiceMode = voiceModeBak;
				return 0;
		}
	}
	return 0;
}