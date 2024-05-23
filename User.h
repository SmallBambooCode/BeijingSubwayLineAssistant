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
// 密码加密函数
string encrype(string str) {
	//创建一个哈希器对象以对字符串的内容进行哈希处理
	hash<string> hasher;
	//计算字符串的哈希值
	size_t hash = hasher(str);
	//将哈希值转换为字符串表示形式
	return to_string(hash);
}
void loading() {
	for (int i = 0; i <= 10; i++) {
		printf("加载中: [");
		for (int j = 0; j < i; j++) {
			printf("██");
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
		//光标回退
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
	cout << "\t\t\t\t[   北京地铁线路小助手   ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[     [ ]查看所有站点    ]" << endl;
	cout << "\t\t\t\t[     [ ]查看地铁线路    ]" << endl;
	cout << "\t\t\t\t[     [ ]路线规划        ]" << endl;
	cout << "\t\t\t\t[     [ ]价格计算        ]" << endl;
	cout << "\t\t\t\t[     [ ]站点查询        ]" << endl;
	cout << "\t\t\t\t[     [ ]打开线路图      ]" << endl;
	cout << "\t\t\t\t[     [ ]随机路线        ]" << endl;
	cout << "\t\t\t\t[     [ ]地铁AI助手      ]" << endl;
	cout << "\t\t\t\t[     [ ]修改账号密码    ]" << endl;
	cout << "\t\t\t\t[     [ ]注销通行证      ]" << endl;
	cout << "\t\t\t\t[     [ ]路线规划历史    ]" << endl;
	cout << "\t\t\t\t[     [ ]退出登录        ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[ Jerry Coding With Love ]" << endl;
	cout << "\t\t\t\t[  按\"V\"键可切换语音模式 ]" << endl;
	cout << "\t\t\t\t==========================";
	return;
}
void printUnloginedMenu() {
	system("cls");
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[   北京地铁线路小助手   ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[     [ ]查看地铁线路    ]" << endl;
	cout << "\t\t\t\t[     [ ]路线规划        ]" << endl;
	cout << "\t\t\t\t[     [ ]站点查询        ]" << endl;
	cout << "\t\t\t\t[     [ ]打开线路图      ]" << endl;
	cout << "\t\t\t\t[     [ ]退出此页面      ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[    登录享受更多功能    ]" << endl;
	cout << "\t\t\t\t==========================";
	return;
}
void printManageMenu() {
	system("cls");
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[  北京地铁线路维护后台  ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[    [ ]查看所有站点     ]" << endl;
	cout << "\t\t\t\t[    [ ]查看地铁线路     ]" << endl;
	cout << "\t\t\t\t[    [ ]添加站点         ]" << endl;
	cout << "\t\t\t\t[    [ ]添加站点路线     ]" << endl;
	cout << "\t\t\t\t[    [ ]添加地铁线路     ]" << endl;
	cout << "\t\t\t\t[    [ ]切换站点状态     ]" << endl;
	cout << "\t\t\t\t[    [ ]删除站点         ]" << endl;
	cout << "\t\t\t\t[    [ ]删除站点路线     ]" << endl;
	cout << "\t\t\t\t[    [ ]删除地铁线路     ]" << endl;
	cout << "\t\t\t\t[    [ ]修改站点名称     ]" << endl;
	cout << "\t\t\t\t[    [ ]修改线路名称     ]" << endl;
	cout << "\t\t\t\t[    [ ]DFS遍历测试      ]" << endl;
	cout << "\t\t\t\t[    [ ]查看通行证       ]" << endl;
	cout << "\t\t\t\t[    [ ]修改权限组       ]" << endl;
	cout << "\t\t\t\t[    [ ]通行证改密       ]" << endl;
	cout << "\t\t\t\t[    [ ]删除通行证       ]" << endl;
	cout << "\t\t\t\t[    [ ]退出维护后台     ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[ Jerry Coding With Love ]" << endl;
	cout << "\t\t\t\t==========================";
	return;
}
// 按位置打印
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
// 保存map.txt文件
bool saveMap(AMLGraph<string, double>& graph, Subway& subway) {
	ofstream file("map.txt");
	if (!file.is_open()) {
		cout << "map.txt文件读取失败" << endl;
		return false;
	}
	string suffix = "[CLOSED]";
	// 外循环，循环的是subway对象中的所有线路
	for (int i = 0; i < subway.getLineNum(); i++) {
		int stationNum = subway.getStationNum(subway.getLineName(i));
		string* stations = subway.getStations(subway.getLineName(i));
		// 内循环，将末尾存在[CLOSED]的站名消除掉[CLOSED]
		for (int j = 0; j < stationNum; j++) {
			if (stations[j].rfind(suffix) == (stations[j].size() - suffix.size())) {
				// 删除 "[CLOSED]"
				stations[j] = stations[j].substr(0, stations[j].size() - suffix.size());
			}
		}
		// 正式输出线路信息
		file << "#" << subway.getLineName(i) << "\t0.00" << endl;
		// 内循环，输出非最后站点的站名和到下一站的权值
		for (int j = 0; j < stationNum - 1; j++) {
			file << stations[j] << "\t" << graph.getEdgeInfo(graph.getVexIndex(stations[j]), graph.getVexIndex(stations[j + 1])) << endl;
		}
		// 最后一站的权值是0
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
	//构造和析构
	User(string username = "UNKNWON", string password = "UNKNWON") {
		this->username = username;
		this->password = password;
	}
	~User() {}
	//功能实现
	void signUp(MyVector<User*>& data);
	int signIn(MyVector<User*>& data);
	virtual string getType() = 0;//获取用户类型，返回不同类型
	virtual int enterMenu(AMLGraph<string, double>& graph, double**& dist, int**& path, Subway& bjsubway, MyVector<User*>& data) = 0;//不同用户进入不同菜单
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
		//如果history.txt文件不存在，则调用ofstream进行新建文件
		if (!readFile.good()) {
			ofstream createFile("history.txt");
			if (!createFile.is_open()) {
				cout << "\t\t\t\t无法创建history.txt文件！" << endl;
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
		//覆盖文件
		ofstream saveFile("history.txt");
		if (!saveFile.is_open()) {
			cout << "文件打开失败！" << endl;
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
	virtual void printUser(MyVector<User*>& data) = 0;//只有Root能查看
	virtual int deleteUser(MyVector<User*>& data) = 0;//非Root只能删自己
	virtual int fixType(MyVector<User*>& data) = 0;//只有Root能修改用户类型
	virtual void fixPassword(MyVector<User*>& data) = 0;//非Root只能改自己的密码
	//运算符重载
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
// 保存用户
void saveUser(MyVector<User*>& users) {
	//在功能实现中需要调用saveNode，所以必须要传头节点指针，否则用当前用户的节点就错了！
	//新建文件输出流
	ofstream saveFile("user.txt");
	if (!saveFile.is_open()) {
		cout << "文件打开失败！" << endl;
		Sleep(2000);
		return;
	}
	//因为调用saveNode的对象只有头节点，所以this指针就是头节点指针，赋给temp进行遍历
	for (int i = 0; i < users.size(); i++) {
		//把内容输出到文件
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
		cout << "\t\t\t\t[         管理员  查看通行证           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t 权限组  用户名" << endl;
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
		cout << "\t\t\t\t[           通行证  删除用户           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		string currUsername = currUser->getUsername();
		cout << "\t\t\t\t当前的用户数据如下：" << endl;
		cout << "\t\t\t\t 权限组  用户名" << endl;
		for (int i = 0; i < data.size(); i++) {
			cout << "\t\t\t\t" << setw(7) << data[i]->getType() << setw(8) << data[i]->getUsername() << endl;
		}
		string content;
		while (1) {
			int returnValue = 0;
			cout << "\t\t\t\t请输入您要删除的用户：";
			cin >> content;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//判断要删除的用户是否为当前登录用户，以便执行自动退出登录功能
			if (currUser->getUsername() == content) {
				returnValue = 1;
			}
			else {
				returnValue = 0;
			}
			for (int i = 0; i < data.size(); i++) {
				if (data[i]->getUsername() == content) {
					if (returnValue == 0 && data[i]->getType() == "Root") {
						cout << "\t\t\t\t您无法删除除了自己的其他管理员，删除失败。" << endl;
						Sleep(1500);
						return 0;
					}
					if (returnValue == 1) {
						cout << "\t\t\t\t您删除的是当前管理用户，即将退出登录。" << endl;
					}
					if (data[i]->getType() == "Common") {
						data[i]->deleteHistory();
					}
					//调用函数模板，删除节点
					data.erase(i);
					cout << "\t\t\t\t用户删除成功！" << endl;
					saveUser(data);
					Sleep(3000);
					return returnValue;
				}
			}
			cout << "\t\t\t\t找不到用户，请重新输入用户名！" << endl;
			Sleep(2000);
			continue;
		}
		return 0;
	}
	//管理员修改权限组
	int fixType(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[         管理员  修改权限组           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t当前的用户数据如下：" << endl;
		cout << "\t\t\t\t 权限组  用户名" << endl;
		for (int i = 0; i < data.size(); i++) {
			cout << "\t\t\t\t" << setw(7) << data[i]->getType() << setw(8) << data[i]->getUsername() << endl;
		}
		string content;
		while (1) {
			cout << "\t\t\t\t请输入您要修改的用户：";
			cin >> content;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//定义returnValue，最终实现判断修改完成后是否需要自动退出账号！
			int returnValue = 0;
			//如果修改的是当前用户，那么最终自动退出登录
			if (currUser->getUsername() == content) {
				returnValue = 1;
			}
			for (int i = 0; i < data.size(); i++) {
				if (data[i]->getUsername() == content) {
					if (returnValue == 0 && data[i]->getType() == "Root") {
						cout << "\t\t\t\t您无法修改除了自己的其他管理员的权限组，修改失败。" << endl;
						Sleep(1500);
						return 0;
					}
					int input;
					cout << "\t\t\t\t[ [1]普通用户 [2]管理员 ]" << endl;
					while (1) {
						cout << "\t\t\t\t请选择要修改为的权限组：";
						if (!(cin >> input) || input < 0 || input > 2) {
							cout << "\t\t\t\t数据输入错误，请重新输入！" << endl;
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
						cout << "\t\t\t\t修改完成！";
						saveUser(data);
						if (returnValue == 1) {
							cout << "您修改的是当前用户的权限组，即将自动退出登录。" << endl;
						}
						else {
							cout << endl;
						}
						Sleep(3000);
						return returnValue;
					}
				}
			}
			cout << "\t\t\t\t找不到用户，请重新输入用户名！" << endl;
			Sleep(2000);
			continue;
		}
	}
	void fixPassword(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[           通行证  修改密码           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t当前的用户数据如下：" << endl;
		cout << "\t\t\t\t 权限组  用户名" << endl;
		for (int i = 0; i < data.size(); i++) {
			cout << "\t\t\t\t" << setw(7) << data[i]->getType() << setw(8) << data[i]->getUsername() << endl;
		}
		string content;
		while (1) {
			cout << "\t\t\t\t请输入您要修改的用户：";
			cin >> content;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			for (int i = 0; i < data.size(); i++) {
				if (data[i]->getUsername() == content) {
					if (data[i]->getType() == "Root" && currUser->getUsername() != content) {
						cout << "\t\t\t\t您无法修改除了自己的其他管理员的密码，修改失败。" << endl;
						Sleep(1500);
						return;
					}
					string ipassword;
					while (1) {
						cout << "\t\t\t\t找到数据，请输入用户 " << content << " 的新的密码：";
						//密码输入
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
								//密显功能 
								cout << "*";
								ipassword.push_back(pwdChar);
								inputCount++;
							}
						}
						if (ipassword.length() == 0) {
							cout << "\t\t\t\t密码不合法，请重新输入！" << endl;
							ipassword = "";
							Sleep(2000);
							continue;
						}
						break;
					}
					ipassword = encrype(ipassword);
					//重设密码
					data[i]->setPassword(ipassword);
					cout << "\t\t\t\t修改成功！" << endl;
					saveUser(data);
					Sleep(2000);
					return;
				}
			}
			cout << "\t\t\t\t找不到用户，请重新输入用户名！" << endl;
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
					// 循环条件：输入的字符不等于回车
					break;
				}
				if ((inputChar == 'w' or inputChar == '8') and currChoice > 0) {
					// 箭头向上移动
					printSelection(defaultX, defaultY, true);
					printSelection(defaultX, --defaultY);
					currChoice--;
				}
				else if ((inputChar == 's' or inputChar == '2') and currChoice < 16) {
					// 箭头向下移动
					printSelection(defaultX, defaultY, true);
					printSelection(defaultX, ++defaultY);
					currChoice++;
				}
			}
			cout << endl;
			// 在switch-case中输入的变量都在这里定义
			string stationName, lineName, begin, end, command, oldLineName, oldStationName;
			string* stations = nullptr;
			stringstream stationInfo, lineInfo;
			int stationIndex = -1, beginIndex = -1, endIndex = -1, addType = 0, stationNum = 0, oldStationIndex = -1, flag = 0;
			double s, s2;
			switch (currChoice) {

			case 0:
				cout << "所有地铁站如下：" << endl;
				graph.printGraph();
				system("pause");
				break;
			case 1:
				cout << "当前最新版地图包含以下线路：" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "请按照以上提示输入您要查询的地铁线路：";
					if (!(cin >> lineName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					break;
				}
				if (bjsubway.printLineInfo(lineName)) {
					while (1) {
						cout << "是否查看该线路的更多信息(y/n)：";
						if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						break;
					}
					if (charinput == 'y') {
						if (lineName == "17号线北段") {
							lineName = "17号线";
							lineInfo << "start " << "https://baike.baidu.com/item/北京地铁" << lineName;
						}
						else if (lineName == "亦庄T1线") {
							lineName = "亦庄新城现代有轨电车T1线";
							lineInfo << "start " << "https://baike.baidu.com/item/" << lineName;
						}
						else {
							lineInfo << "start " << "https://baike.baidu.com/item/北京地铁" << lineName;
						}

						command = lineInfo.str();
						if (!system(command.c_str())) {
							cout << "已成功打开北京地铁" << lineName << "的在线信息。" << endl;
						}
						else {
							cout << "无法打开网页。" << endl;
						}
						Sleep(2000);
					}
				}
				else {
					cout << "您输入的线路不存在！" << endl;
				}
				system("pause");
				break;
			case 2:

				while (1) {
					cout << "请输入您要添加的站点名称：";
					if (!(cin >> stationName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
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
				cout << "添加完成" << endl;
				system("pause");
				break;
			case 3:
				cout << "添加站点路线规则：输入三个站点，三个站点相邻，第一个和第三个站点存在，第二个站点为新站点，从而让新站点插入到旧的站点之中。\n您可以选择是否输入第一个站点和第三个站点，进而达到前插和后插的效果。" << endl;
				cout << "当前最新版地图包含以下线路：" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "请输入您要操作的线路：";
					if (!(cin >> lineName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) == -1) {
						cout << "您输入的线路不存在，请重新输入！" << endl;
						continue;
					}
					break;
				}
				bjsubway.printLineInfo(lineName);
				while (1) {

					while (1) {
						cout << "请输入新的地铁站名：";
						if (!(cin >> stationName)) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						stationIndex = graph.getVexIndex(stationName);
						if (stationIndex == -1) {
							cout << "不存在您输入的地铁站，请重新输入！" << endl;
							continue;
						}
						if (!graph.getVexEnabled(stationIndex)) {
							cout << "您输入的地铁站为关闭状态，无法对此进行操作，请重新输入！" << endl;
							continue;
						}
						break;
					}

					while (1) {
						cout << "请输入前一个地铁站名（输入n为忽略此选项）：";
						if (!(cin >> begin)) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						if (begin != "n") {
							beginIndex = graph.getVexIndex(begin);
							if (beginIndex == -1) {
								cout << "不存在您输入的地铁站，请重新输入！" << endl;
								continue;
							}
							if (!graph.getVexEnabled(stationIndex)) {
								cout << "您输入的地铁站为关闭状态，无法对此进行操作，请重新输入！" << endl;
								continue;
							}
						}
						break;
					}

					while (1) {
						cout << "请输入后一个地铁站名（输入n为忽略此选项）：";
						if (!(cin >> end)) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						if (end != "n") {
							endIndex = graph.getVexIndex(end);
							if (endIndex == -1) {
								cout << "不存在您输入的地铁站，请重新输入！" << endl;
								continue;
							}
							if (!graph.getVexEnabled(stationIndex)) {
								cout << "您输入的地铁站为关闭状态，无法对此进行操作，请重新输入！" << endl;
								continue;
							}
						}
						break;
					}

					if (begin == "n" and end == "n") {
						cout << "您不能同时忽略输入前后两个站点！请重新输入站点。" << endl;
						system("pause");
						continue;
					}
					else if (begin == "n" and end != "n") {
						// 前插
						addType = 1;
					}
					else if (begin != "n" and end == "n") {
						// 后插
						addType = 2;
					}
					else {
						if (abs(bjsubway.stationIndex(begin, lineName) - bjsubway.stationIndex(end, lineName)) != 1) {
							cout << "您输入的站点不相邻，请重新输入！" << endl;
							system("pause");
							continue;
						}
						// 默认中间插
					}
					if (addType == 0) {
						while (1) {
							cout << "请输入新站点与前一站点间的距离：";
							if (!(cin >> s)) {
								cout << "数据输入错误，请重新输入！" << endl;
								//清空输入缓存区
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								system("pause");
								continue;
							}
							break;
						}
						while (1) {
							cout << "请输入新站点与后一站点间的距离：";
							if (!(cin >> s2)) {
								cout << "数据输入错误，请重新输入！" << endl;
								//清空输入缓存区
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
							cout << "请输入已输入的两站点间的距离：";
							if (!(cin >> s)) {
								cout << "数据输入错误，请重新输入！" << endl;
								//清空输入缓存区
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
				// 中间插入
				if (addType == 0) {
					bjsubway.insertStation(begin, stationName, lineName);
					graph.deleteEdge(beginIndex, endIndex);
					graph.addEdge(beginIndex, stationIndex, s);
					graph.addEdge(endIndex, stationIndex, s2);
				}
				// 前插
				else if (addType == 1) {
					bjsubway.insertStation(lineName, stationName, lineName);
					graph.addEdge(endIndex, stationIndex, s);
				}
				// 后插
				else {
					bjsubway.addStation(stationName, lineName);
					graph.addEdge(beginIndex, stationIndex, s);
				}
				graph.calculateFloyd(dist, path);
				cout << "站点路线添加成功！" << endl;
				system("pause");
				break;
			case 4:
				cout << "当前最新版地图包含以下线路：" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "请输入您要新增的线路：";
					if (!(cin >> lineName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) != -1) {
						cout << "您输入的线路已存在，请重新输入！" << endl;
						continue;
					}
					break;
				}
				bjsubway.addLine(lineName);
				cout << "地铁线路添加完成，请从已有站点中为线路添加一个初始站点" << endl;
				while (1) {
					cout << "请输入新的地铁站名：";
					if (!(cin >> stationName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex == -1) {
						cout << "不存在您输入的地铁站，请重新输入！" << endl;
						continue;
					}
					break;
				}
				bjsubway.addStation(stationName, lineName);
				cout << "初始站点添加完成" << endl;
				system("pause");
				break;
			case 5:
				while (1) {
					cout << "请输入要切换状态地铁站名：";
					if (!(cin >> stationName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex == -1) {
						cout << "不存在您输入的地铁站，请重新输入！" << endl;
						continue;
					}
					break;
				}
				graph.freeDistAndPath(dist, path);
				if (graph.changeVexStatus(stationIndex) == 0) {
					cout << "当前站点状态为停用，已切换为启用" << endl;
					bjsubway.modifyStationNameAllLine(stationName + "[CLOSED]", stationName);
					graph.updateVexData(stationIndex, stationName);
				}
				else {
					cout << "当前站点状态为启用，已切换为停用" << endl;
					bjsubway.modifyStationNameAllLine(stationName, stationName + "[CLOSED]");
					graph.updateVexData(stationIndex, stationName + "[CLOSED]");
				}
				graph.calculateFloyd(dist, path);
				system("pause");
				break;
			case 6:
				while (1) {
					cout << "请输入要删除的地铁站名：";
					if (!(cin >> stationName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex == -1) {
						cout << "不存在您输入的地铁站，请重新输入！" << endl;
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
				cout << "已删除" << stationName << "站" << endl;
				system("pause");
				break;
			case 7:
				cout << "删除站点路线规则：输入三个站点，三个站点相邻，第一个和第三个站点存在，第二个站点为要删除的站点。\n您可以选择是否输入第一个站点和第三个站点，进而达到前删和后删的效果。" << endl;
				cout << "当前最新版地图包含以下线路：" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "请输入您要操作的线路：";
					if (!(cin >> lineName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) == -1) {
						cout << "您输入的线路不存在，请重新输入！" << endl;
						continue;
					}
					break;
				}
				bjsubway.printLineInfo(lineName);
				while (1) {
					while (1) {
						cout << "请输入要删除的地铁站名：";
						if (!(cin >> stationName)) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						stationIndex = graph.getVexIndex(stationName);
						if (stationIndex == -1) {
							cout << "不存在您输入的地铁站，请重新输入！" << endl;
							continue;
						}
						if (!graph.getVexEnabled(stationIndex)) {
							cout << "您输入的地铁站为关闭状态，无法对此进行操作，请重新输入！" << endl;
							continue;
						}
						break;
					}

					while (1) {
						cout << "请输入前一个地铁站名（输入n为忽略此选项）：";
						if (!(cin >> begin)) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						if (begin != "n") {
							beginIndex = graph.getVexIndex(begin);
							if (beginIndex == -1) {
								cout << "不存在您输入的地铁站，请重新输入！" << endl;
								continue;
							}
							if (!graph.getVexEnabled(stationIndex)) {
								cout << "您输入的地铁站为关闭状态，无法对此进行操作，请重新输入！" << endl;
								continue;
							}
						}
						break;
					}

					while (1) {
						cout << "请输入后一个地铁站名（输入n为忽略此选项）：";
						if (!(cin >> end)) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						if (end != "n") {
							endIndex = graph.getVexIndex(end);
							if (endIndex == -1) {
								cout << "不存在您输入的地铁站，请重新输入！" << endl;
								continue;
							}
							if (!graph.getVexEnabled(stationIndex)) {
								cout << "您输入的地铁站为关闭状态，无法对此进行操作，请重新输入！" << endl;
								continue;
							}
						}
						break;
					}

					if (begin == "n" and end == "n") {
						cout << "您不能同时忽略输入前后两个站点！请重新输入站点。" << endl;
						system("pause");
						continue;
					}
					else if (begin == "n" and end != "n") {
						// 前删
						addType = 1;
					}
					else if (begin != "n" and end == "n") {
						// 后删
						addType = 2;
					}
					else {
						if (abs(bjsubway.stationIndex(begin, lineName) - bjsubway.stationIndex(end, lineName)) != 2) {
							cout << "您输入的站点不相邻，请重新输入！" << endl;
							system("pause");
							continue;
						}
						while (1) {
							cout << "请输入删除之后前后两站点间的距离：";
							if (!(cin >> s)) {
								cout << "数据输入错误，请重新输入！" << endl;
								//清空输入缓存区
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								system("pause");
								continue;
							}
							break;
						}
						// 默认中间插
					}

					break;
				}
				graph.freeDistAndPath(dist, path);
				// 中间删
				if (addType == 0) {
					bjsubway.deleteStation(stationName, lineName);
					graph.deleteEdge(beginIndex, stationIndex);
					graph.deleteEdge(stationIndex, endIndex);
					graph.addEdge(beginIndex, endIndex, s);
					// 中间删的时候，如果要删的节点在其他线路上还有联系，就不删这一站，否则就删除这一站
					if (graph.isVexAlone(graph.getVexIndex(stationName))) {
						graph.deleteVex(graph.getVexIndex(stationName));
					}
				}
				// 前删
				else if (addType == 1) {
					bjsubway.deleteStation(stationName, lineName);
					graph.deleteEdge(stationIndex, endIndex);
					if (graph.isVexAlone(graph.getVexIndex(stationName))) {
						graph.deleteVex(graph.getVexIndex(stationName));
					}
				}
				// 后删
				else {
					bjsubway.deleteStation(stationName, lineName);
					graph.deleteEdge(beginIndex, stationIndex);
					if (graph.isVexAlone(graph.getVexIndex(stationName))) {
						graph.deleteVex(graph.getVexIndex(stationName));
					}
				}
				graph.calculateFloyd(dist, path);
				cout << "站点路线删除成功！" << endl;
				system("pause");
				break;
			case 8:
				cout << "当前最新版地图包含以下线路：" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "请输入您要删除的线路：";
					if (!(cin >> lineName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) == -1) {
						cout << "您输入的线路不存在，请重新输入！" << endl;
						continue;
					}
					break;
				}
				graph.freeDistAndPath(dist, path);
				stations = bjsubway.getStations(lineName);
				stationNum = bjsubway.getStationNum(lineName);
				// 循环删除线路
				for (int i = 0; i < stationNum - 1; i++) {
					// 这个线路仅在一个地铁路线上时，才删除边
					if (bjsubway.getStationPathInAllLine(stations[i], stations[i + 1]) <= 1) {
						graph.deleteEdge(graph.getVexIndex(stations[i]), graph.getVexIndex(stations[i + 1]));
					}
				}
				// 孤独的节点直接删除
				for (int i = 0; i < stationNum; i++) {
					if (graph.isVexAlone(graph.getVexIndex(stations[i]))) {
						graph.deleteVex(graph.getVexIndex(stations[i]));
					}
				}
				bjsubway.deleteLine(lineName);
				graph.calculateFloyd(dist, path);
				cout << "线路已删除完成！" << endl;
				system("pause");
				break;
			case 9:
				while (1) {
					cout << "请输入要修改的地铁站名：";
					if (!(cin >> oldStationName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					oldStationIndex = graph.getVexIndex(oldStationName);
					if (oldStationIndex == -1) {
						cout << "不存在您输入的地铁站，请重新输入！" << endl;
						continue;
					}
					break;
				}
				while (1) {
					cout << "请输入新的地铁站名：";
					if (!(cin >> stationName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex != -1) {
						cout << "新输入的新的地铁站名已存在，请重新输入！" << endl;
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
				cout << "站点名修改成功" << endl;
				system("pause");
				break;
			case 10:
				cout << "当前最新版地图包含以下线路：" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "请输入您要修改的线路名称：";
					if (!(cin >> oldLineName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(oldLineName) == -1) {
						cout << "您输入的线路名称不存在，请重新输入！" << endl;
						continue;
					}
					break;
				}
				while (1) {
					cout << "请输入新的线路名称：";
					if (!(cin >> lineName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					if (bjsubway.lineIndex(lineName) != -1) {
						cout << "您输入的线路名称已存在，请重新输入！" << endl;
						continue;
					}
					break;
				}
				bjsubway.modifyLineName(oldLineName, lineName);
				cout << "线路名称修改完成" << endl;
				system("pause");
				break;
			case 11:
				cout << "以下是所有站点从第一个站点开始DFS遍历的结果：" << endl;
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
					cout << "退出提示: 是否要保存更改至地图文件?(y/n)：";
					if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						continue;
					}
					break;
				}
				if (charinput == 'y') {
					if (saveMap(graph, bjsubway)) cout << "保存成功，将在2秒后退出" << endl;
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
		cout << "\t\t\t\t没有权限！" << endl;
		return;
	}
	int deleteUser(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[           通行证  用户注销           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		int input, flag = 0;
		cout << "\t\t\t\t警告！您正在进行当前用户：" << currUser->getUsername() << " 的注销操作！" << endl;
		while (1) {
			cout << "\t\t\t\t是否确认注销？[1]确认  [0]取消：";
			if (!(cin >> input) || input < 0 || input > 1) {
				cout << "\t\t\t\t数据输入错误，请重新输入！" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				Sleep(2000);
				continue;
			}
			if (input == 1) {
				//直接调用deleteNode删除当前节点
				for (int i = 0; i < data.size(); i++) {
					if (data[i] == currUser) {
						data[i]->deleteHistory();
						data.erase(i);
						break;
					}
				}
				cout << "\t\t\t\t账户注销成功！" << endl;
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
		cout << "\t\t\t\t没有权限！" << endl;
		return 0;
	}
	void fixPassword(MyVector<User*>& data) {
		system("cls");
		cout << "\t\t\t\t========================================" << endl;
		cout << "\t\t\t\t[           通行证  修改密码           ]" << endl;
		cout << "\t\t\t\t========================================" << endl;
		string ipassword;
		while (1) {
			cout << "\t\t\t\t请输入您的新密码：";
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
					//密显功能 
					cout << "*";
					ipassword.push_back(pwdChar);
					inputCount++;
				}
			}
			if (ipassword.length() == 0) {
				cout << "\t\t\t\t密码不合法，请重新输入！" << endl;
				ipassword = "";
				Sleep(2000);
				continue;
			}
			break;
		}
		ipassword = encrype(ipassword);
		currUser->setPassword(ipassword);
		cout << "\t\t\t\t修改成功！即将退出。" << endl;
		saveUser(data);
		Sleep(2000);
		return;
	}
	void saveHistory(string startStation, string endStation) {
		//用追加方式打开文件
		ofstream saveFile("history.txt", ios::app);
		if (!saveFile.is_open()) {
			cout << "文件打开失败！" << endl;
			Sleep(2000);
			return;
		}
		//getTime()更新当前时间，返回值为字符串
		saveFile << currUser->getUsername() << ' ' << startStation << ' ' << endStation << endl;
		saveFile.close();
		return;
	}
	void printHistory() {
		int printCount = 0;
		string line;
		ifstream readFile("history.txt");
		//如果history.txt文件不存在，则调用ofstream进行新建文件
		if (!readFile.good()) {
			ofstream createFile("history.txt");
			if (!createFile.is_open()) {
				cout << "\t\t\t\t无法创建history.txt文件！" << endl;
				Sleep(2000);
				return;
			}
			createFile.close();
			readFile.open("history.txt");
		}
		system("cls");
		cout << "\t\t\t\t==========================" << endl;
		cout << "\t\t\t\t[    我的历史线路规划    ]" << endl;
		cout << "\t\t\t\t==========================" << endl;
		while (getline(readFile, line)) {
			string username, startStation, endStation;
			istringstream iss(line);
			iss >> username >> startStation >> endStation;
			//判断载入的文件是不是当前用户
			if (currUser->getUsername() != username) {
				continue;
			}
			cout << "\t\t\t\t" << startStation << " --> " << endStation << endl;
			printCount++;
		}
		readFile.close();
		if (printCount == 0) {
			cout << "\t\t\t\t暂无历史路线规划，去试试路线规划功能吧！" << endl;
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
					// 循环条件：输入的字符不等于回车
					break;
				}
				if (inputChar == 'F') {
					system("start Python后端启动.bat");
					Sleep(1000);
					system("start 地铁线路查询前端.html");
				}
				if (inputChar == 'V') {
					if (voiceMode == false) {
						voiceMode = true;
						cout << "\n已开启语音模式";
						if (voiceMode) speakString("已开启语音模式");
						Sleep(1500);
						printMenu();
						printSelection(defaultX, defaultY);
					}
					else {
						voiceMode = false;
						cout << "\n已关闭语音模式";
						Sleep(1500);
						printMenu();
						printSelection(defaultX, defaultY);
					}
				}
				if ((inputChar == 'w' or inputChar == '8') and currChoice > 0) {
					// 箭头向上移动
					printSelection(defaultX, defaultY, true);
					printSelection(defaultX, --defaultY);
					currChoice--;
				}
				else if ((inputChar == 's' or inputChar == '2') and currChoice < 11) {
					// 箭头向下移动
					printSelection(defaultX, defaultY, true);
					printSelection(defaultX, ++defaultY);
					currChoice++;
				}
			}
			cout << endl;
			// 在switch-case中输入的变量都在这里定义
			string stationName, lineName, begin, end, command, suffix = "站";
			stringstream stationInfo, lineInfo;
			MyVector<string> stationNames;
			stringstream voiceString;
			int stationIndex, beginIndex, endIndex, flag=0;
			double s;
			char charinput;
			switch (currChoice) {

				case 0:
					cout << "所有地铁站如下：" << endl;
					graph.printGraph();
					if (voiceMode) speakString("所有地铁站如下");
					system("pause");
					break;
				case 1:
					cout << "当前最新版地图包含以下线路：" << endl;
					bjsubway.printLineNames();
					if (voiceMode) speakString("当前最新版地图包含以下线路");
					while (1) {
						cout << "请按照以上提示输入您要查询的地铁线路：";
						if (voiceMode) speakString("请按照以上提示输入您要查询的地铁线路");
						if (!(cin >> lineName)) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						break;
					}
					if (bjsubway.printLineInfo(lineName)) {
						while (1) {
							cout << "是否查看该线路的更多信息(y/n)：";
							if (voiceMode) speakString("是否查看该线路的更多信息");
							if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
								cout << "数据输入错误，请重新输入！" << endl;
								if (voiceMode) speakString("数据输入错误，请重新输入");
								//清空输入缓存区
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								continue;
							}
							break;
						}
						if (charinput == 'y') {
							if (lineName == "17号线北段") {
								lineName = "17号线";
								lineInfo << "start " << "https://baike.baidu.com/item/北京地铁" << lineName;
							}
							else if (lineName == "亦庄T1线") {
								lineName = "亦庄新城现代有轨电车T1线";
								lineInfo << "start " << "https://baike.baidu.com/item/" << lineName;
							}
							else {
								lineInfo << "start " << "https://baike.baidu.com/item/北京地铁" << lineName;
							}

							command = lineInfo.str();
							if (!system(command.c_str())) {
								cout << "已成功打开北京地铁" << lineName << "的在线信息。" << endl;
								if (voiceMode) {
									voiceString.str("");  // 清空stringstream对象
									voiceString << "已成功打开北京地铁" << lineName << "的在线信息。";
									speakString(voiceString.str());
								}
							}
							else {
								cout << "无法打开网页。" << endl;
								if (voiceMode) speakString("无法打开网页");
							}
							Sleep(1000);
						}
					}
					else {
						cout << "您输入的线路不存在！" << endl;
						if (voiceMode) speakString("您输入的线路不存在");
					}
					system("pause");
					break;
				case 2:
					while (1) {
						cout << "请输入起点地铁站名：";
						if (voiceMode) speakString("请输入起点地铁站名");
						if (!(cin >> begin)) {
							cout << "数据输入错误，请重新输入！" << endl;
							if (voiceMode) speakString("数据输入错误，请重新输入");
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						beginIndex = graph.getVexIndex(begin);
						if (beginIndex == -1) {
							cout << "不存在您输入的地铁站，请重新输入！" << endl;
							if (voiceMode) speakString("不存在您输入的地铁站，请重新输入");
							continue;
						}
						break;
					}
					while (1) {
						cout << "请输入终点地铁站名：";
						if (voiceMode) speakString("请输入终点地铁站名");
						if (!(cin >> end)) {
							cout << "数据输入错误，请重新输入！" << endl;
							if (voiceMode) speakString("数据输入错误，请重新输入");
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						endIndex = graph.getVexIndex(end);
						if (endIndex == -1) {
							cout << "不存在您输入的地铁站，请重新输入！" << endl;
							if (voiceMode) speakString("不存在您输入的地铁站，请重新输入");
							continue;
						}
						if (endIndex == beginIndex) {
							cout << "您搁这原地TP呢？请重新输入！" << endl;
							if (voiceMode) speakString("您搁这原地TP呢？请重新输入！");
							continue;
						}
						break;
					}
					// 保存查询历史
					saveHistory(begin, end);
					// 弗洛伊德
					stationNames = graph.printFloydShortestPath(beginIndex, endIndex, dist, path);
					bjsubway.printTransferInformation(stationNames);
					// BFS
					stationNames = graph.printBFSPath(beginIndex, endIndex);
					bjsubway.printTransferInformation(stationNames);
					system("pause");
					break;
				case 3:
					while (1) {
						cout << "请输入乘坐距离(km)：";
						if (voiceMode) speakString("请输入乘坐距离");
						if (!(cin >> s)) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						break;
					}
					cout << "票价：" << costCalculate(s) << "元" << endl;
					if (voiceMode) {
						voiceString.str("");
						voiceString << "票价：" << costCalculate(s) << "元";
						speakString(voiceString.str());
					}
					system("pause");
					break;
				case 4:
					while (1) {
						cout << "请输入您要查找的地铁站名：";
						if (voiceMode) speakString("请输入您要查找的地铁站名");
						if (!(cin >> stationName)) {
							cout << "数据输入错误，请重新输入！" << endl;
							if (voiceMode) speakString("数据输入错误，请重新输入");
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							system("pause");
							continue;
						}
						break;
					}
					stationIndex = graph.getVexIndex(stationName);
					if (stationIndex != -1) {
						cout << "查找成功！以下是该地铁站信息：" << endl;
						if (voiceMode) speakString("查找成功！以下是该地铁站信息");
						graph.printVexInfo(stationIndex);
						while (1) {
							cout << "是否查看该站点的周边信息(y/n)：";
							if (voiceMode) speakString("是否查看该站点的周边信息");
							if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
								cout << "数据输入错误，请重新输入！" << endl;
								if (voiceMode) speakString("数据输入错误，请重新输入");
								//清空输入缓存区
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
								continue;
							}
							break;
						}
						if (charinput == 'y') {
							// 如果站名后有"站"字
							if (stationName.rfind(suffix) == (stationName.size() - suffix.size())) {
								stationInfo << "start " << "https://baike.baidu.com/item/" << stationName;
							}
							else {
								stationInfo << "start " << "https://baike.baidu.com/item/" << stationName << "站";
							}
							command = stationInfo.str();
							if (!system(command.c_str())) {
								cout << "已成功打开" << stationName << "站的在线信息。" << endl;
								if (voiceMode) {
									voiceString.str("");
									voiceString << "已成功打开" << stationName << "站的在线信息";
									speakString(voiceString.str());
								}
							}
							else {
								cout << "无法打开网页。" << endl;
								if (voiceMode) speakString("无法打开网页");
							}
							Sleep(2000);
						}
					}
					else {
						cout << "找不到您输入的地铁站。" << endl;
						if (voiceMode) speakString("找不到您输入的地铁站");
					}
					system("pause");
					break;
				case 5:
					command = "start lwt.png";
					if (!system(command.c_str())) {
						cout << "地铁线路图已成功打开。" << endl;
						if (voiceMode) speakString("地铁线路图已成功打开");
					}
					else {
						cout << "无法打开文件。" << endl;
						if (voiceMode) speakString("无法打开文件");
					}
					Sleep(1000);
					break;

				case 6:
					cout << "已为您生成两个随机站点的路线规划：" << endl;
					if (voiceMode) speakString("已为您生成两个随机站点的路线规划");
					srand(time(0));
					beginIndex = graph.getRandomVexIndex();
					endIndex = graph.getRandomVexIndex();
					// 弗洛伊德
					stationNames = graph.printFloydShortestPath(beginIndex, endIndex, dist, path);
					bjsubway.printTransferInformation(stationNames);
					// BFS
					stationNames = graph.printBFSPath(beginIndex, endIndex);
					bjsubway.printTransferInformation(stationNames);
					system("pause");
					break;
				case 7:
					system("start PythonAI启动.bat");
					cout << "已启动北京地铁AI助手" << endl;
					if (voiceMode) speakString("已启动北京地铁AI助手");
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
					cout << "\n感谢您使用Jerry开发的《北京地铁线路小助手》，我们下次再见！" << endl;
					if (voiceMode) speakString("感谢您使用Jerry开发的《北京地铁线路小助手》，我们下次再见");
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
				// 循环条件：输入的字符不等于回车
				break;
			}
			if ((inputChar == 'w' or inputChar == '8') and currChoice > 0) {
				// 箭头向上移动
				printSelection(defaultX, defaultY, true);
				printSelection(defaultX, --defaultY);
				currChoice--;
			}
			else if ((inputChar == 's' or inputChar == '2') and currChoice < 4) {
				// 箭头向下移动
				printSelection(defaultX, defaultY, true);
				printSelection(defaultX, ++defaultY);
				currChoice++;
			}
		}
		cout << endl;
		// 在switch-case中输入的变量都在这里定义
		string stationName, lineName, begin, end, command, suffix = "站";
		stringstream stationInfo, lineInfo;
		MyVector<string> stationNames;
		int stationIndex, beginIndex, endIndex;
		char charinput;
		switch (currChoice) {

			case 0:
				cout << "当前最新版地图包含以下线路：" << endl;
				bjsubway.printLineNames();
				while (1) {
					cout << "请按照以上提示输入您要查询的地铁线路：";
					if (!(cin >> lineName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					break;
				}
				if (bjsubway.printLineInfo(lineName)) {
					while (1) {
						cout << "是否查看该线路的更多信息(y/n)：";
						if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						break;
					}
					if (charinput == 'y') {
						if (lineName == "17号线北段") {
							lineName = "17号线";
							lineInfo << "start " << "https://baike.baidu.com/item/北京地铁" << lineName;
						}
						else if (lineName == "亦庄T1线") {
							lineName = "亦庄新城现代有轨电车T1线";
							lineInfo << "start " << "https://baike.baidu.com/item/" << lineName;
						}
						else {
							lineInfo << "start " << "https://baike.baidu.com/item/北京地铁" << lineName;
						}

						command = lineInfo.str();
						if (!system(command.c_str())) {
							cout << "已成功打开北京地铁" << lineName << "的在线信息。" << endl;
						}
						else {
							cout << "无法打开网页。" << endl;
						}
						Sleep(1000);
					}
				}
				else {
					cout << "您输入的线路不存在！" << endl;
				}
				system("pause");
				break;
			case 1:
				while (1) {
					cout << "请输入起点地铁站名：";
					if (!(cin >> begin)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					beginIndex = graph.getVexIndex(begin);
					if (beginIndex == -1) {
						cout << "不存在您输入的地铁站，请重新输入！" << endl;
						continue;
					}
					break;
				}
				while (1) {
					cout << "请输入终点地铁站名：";
					if (!(cin >> end)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					endIndex = graph.getVexIndex(end);
					if (endIndex == -1) {
						cout << "不存在您输入的地铁站，请重新输入！" << endl;
						continue;
					}
					if (endIndex == beginIndex) {
						cout << "您搁这原地TP呢？请重新输入！" << endl;
						continue;
					}
					break;
				}
				// 弗洛伊德
				stationNames = graph.printFloydShortestPath(beginIndex, endIndex, dist, path);
				// BFS
				stationNames = graph.printBFSPath(beginIndex, endIndex);
				system("pause");
				break;
			case 2:
				while (1) {
					cout << "请输入您要查找的地铁站名：";
					if (!(cin >> stationName)) {
						cout << "数据输入错误，请重新输入！" << endl;
						//清空输入缓存区
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						system("pause");
						continue;
					}
					break;
				}
				stationIndex = graph.getVexIndex(stationName);
				if (stationIndex != -1) {
					cout << "查找成功！以下是该地铁站信息：" << endl;
					graph.printVexInfo(stationIndex);
					while (1) {
						cout << "是否查看该站点的周边信息(y/n)：";
						if (!(cin >> charinput) or (charinput != 'y' and charinput != 'n')) {
							cout << "数据输入错误，请重新输入！" << endl;
							//清空输入缓存区
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						break;
					}
					if (charinput == 'y') {
						// 如果站名后有"站"字
						if (stationName.rfind(suffix) == (stationName.size() - suffix.size())) {
							stationInfo << "start " << "https://baike.baidu.com/item/" << stationName;
						}
						else {
							stationInfo << "start " << "https://baike.baidu.com/item/" << stationName << "站";
						}
						command = stationInfo.str();
						if (!system(command.c_str())) {
							cout << "已成功打开" << stationName << "站的在线信息" << endl;
						}
						else {
							cout << "无法打开网页。" << endl;
						}
						Sleep(2000);
					}
				}
				else {
					cout << "找不到您输入的地铁站。" << endl;
				}
				system("pause");
				break;
			case 3:
				command = "start lwt.png";
				if (!system(command.c_str())) {
					cout << "地铁线路图已成功打开。" << endl;
				}
				else {
					cout << "无法打开文件。" << endl;
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