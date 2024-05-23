/***************************
		 COPYRIGHT
 北京地铁线路小助手（含管理员维护）
	   Author:SmallBambooCode
	 2024年4月24日12点32分整体功能完成
	 2024年5月8日21点20分完成语音朗读功能
	 2024年5月10日18点20分完成接入KIMI AI
	 2024年5月22日21点25分完成多用户和免登录使用以及查询历史功能
	 当前代码量：4000行+
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
// 打印关于
void printAbout() {
	system("cls");
	cout << "===============================================================================================" << endl;
	cout << "[                                北京地铁线路小助手 - 关于本软件                              ]" << endl;
	cout << "===============================================================================================" << endl;
	cout << "[  北京地铁线路小助手是一款为广大北京地铁乘客及管理人员设计的实用性软件。                     ]" << endl;
	cout << "[  它具备丰富的功能和人性化的设计，是乘客日常出行和地铁线路维护人员工作的得力辅助工具。       ]" << endl;
	cout << "===============================================================================================" << endl;
	cout << "[  全站点和线路查看：提供完整的地铁站点和线路信息，易于查阅，方便规划行程。                   ]" << endl;
	cout << "[  线路规划助手：只需输入起点和终点，即可得到最短路径和最少站点数的智能规划结果，附带换乘提示 ]" << endl;
	cout << "[  、换乘次数、站点统计，以及票价计算，确保乘客出行无忧。                                     ]" << endl;
	cout << "[  随机路线探索：提供随机路线功能，为爱探索的乘客提供新的出行体验。                           ]" << endl;
	cout << "[  语音朗读模式：通过简单的按键操作即可激活语音朗读，提高了软件的可访问性。                   ]" << endl;
	cout << "[  综合的站点路线维护：允许管理员通过后台添加、删除或修改站点和线路信息，以便信息的及时更新。 ]" << endl;
	cout << "[  站点状态切换：方便调控各地铁站的开闭状态，灵活应对突发事件或维修需要。                     ]" << endl;
	cout << "[  信息更新：修改站点名称、线路名称及后台密码等，确保信息的准确性和系统的安全性。             ]" << endl;
	cout << "===============================================================================================" << endl;
	cout << "[  由「SmallBambooCode」倾力打造的北京地铁线路小助手，不论是为广大乘客提供便利的出行规划，  ]" << endl;
	cout << "[  还是为管理员带来高效率的维护操作，都将成为北京地铁出行和管理的智能化利器。                 ]" << endl;
	cout << "[  在繁华都市的快节奏中，它让每一次地铁之旅都变得简单而可靠。感谢您的使用！                   ]" << endl;
	cout << "===============================================================================================" << endl;
}
// 加载用户
void loadUser(MyVector<User*>& users) {
	//新建文件输入流
	ifstream inputFile("user.txt");
	if (!inputFile.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
	}
	//新建用于读取每一行的字符串line
	string line;
	//把每一行都存到line里
	while (getline(inputFile, line)) {
		string usertype, username, password;
		istringstream iss(line);
		//切分line中的内容
		iss >> usertype >> username >> password;
		//根据usertype判断新建什么类的对象
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
// 加载地铁站点
void loadStation(AMLGraph<string, double>& graph, Subway& subway) {
	ifstream file("map.txt");
	if (!file.is_open()) {
		cout << "map.txt文件读取失败" << endl;
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
			// 正式添加时删除#号
			station.erase(0, 1);
			cout << "正在加载 北京地铁" << station << endl;
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
	cout << "站点加载完成！共计" << count << "个站点。" << endl;
	return;
}
// 加载地铁路线
void loadPath(AMLGraph<string, double>& graph) {
	ifstream file("map.txt");
	if (!file.is_open()) {
		cout << "map.txt文件读取失败" << endl;
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
	// 开始添加路径
	for (int i = 0; i < stations.size() - 1; i++) {
		if (stations[i] == "#" or stations[i + 1] == "#") {
			continue;
		}
		if (graph.addEdge(graph.getVexIndex(stations[i]), graph.getVexIndex(stations[i + 1]), distances[i])) {
			count++;
		}

		//cout << stations[i] << "<-" << distances[i] << "->" << stations[i + 1] << endl;
	}
	cout << "已加载" << count << "条路线。" << endl;
	return;
}
// 注册
void User::signUp(MyVector<User*>& data) {
	while (1) {
		system("cls");
		cout << "\t\t\t\t==========================" << endl;
		cout << "\t\t\t\t[   北京地铁导航  注册   ]" << endl;
		cout << "\t\t\t\t==========================" << endl;
		string iusername, ipassword;
		while (1) {
			int flag = 0;
			iusername = "";
			//用户名输入部分
			cout << "\t\t\t\t请输入用户名：";
			int inputCount = 0;
			char usrChar;
			while (1) {
				usrChar = _getch();
				if (usrChar == 13) {
					//循环条件：输入的字符不等于回车
					cout << endl;
					break;
				}
				if (usrChar == 8 && inputCount > 0) {
					//回删功能
					cout << "\b \b";
					iusername.pop_back();//移除末尾字符
					inputCount--;
				}
				else if (usrChar != 8 && usrChar != 32 && inputCount < 20) {
					//正常显示用户名
					cout << usrChar;
					iusername.push_back(usrChar);
					inputCount++;
				}
			}
			if (iusername.length() == 0) {
				cout << "\t\t\t\t用户名不合法，请重新输入！" << endl;
				Sleep(2000);
				continue;
			}
			//注册查重
			for (int i = 0; i < data.size(); i++) {
				if (data[i]->getUsername() == iusername) {
					cout << "\t\t\t\t注册失败，您输入的用户名已存在，请重新注册。" << endl;
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
			//密码输入部分
			cout << "\t\t\t\t请输入密码：";
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
		cout << "\t\t\t\t注册成功！欢迎您：" << iusername << endl;
		ipassword = encrype(ipassword);
		data.push_back(currUser = new Common(iusername, ipassword));
		saveUser(data);
		Sleep(1500);
		break;
	}
	return;
}
// 登录
int User::signIn(MyVector<User*>& data) {
	system("cls");
	cout << "\t\t\t\t==========================" << endl;
	cout << "\t\t\t\t[   北京地铁导航  登录   ]" << endl;
	cout << "\t\t\t\t==========================" << endl;
	if (data.empty()) {
		cout << "\t\t\t\t系统中没有用户，请先注册！" << endl;
		Sleep(2000);
		return 2;
	}
	for (int i = 4; i >= 0; i--) {
		string iusername, ipassword;
		cout << "\t\t\t\t请输入用户名：";
		int inputCount = 0;
		char usrChar;
		while (1) {
			usrChar = _getch();
			if (usrChar == 13) {
				//循环条件：输入的字符不等于回车
				cout << endl;
				break;
			}
			if (usrChar == 8 && inputCount > 0) {
				//回删功能
				cout << "\b \b";
				iusername.pop_back();//移除末尾字符
				inputCount--;
			}
			else if (usrChar != 8 && usrChar != 32 && inputCount < 20) {
				//正常显示用户名
				cout << usrChar;
				iusername.push_back(usrChar);
				inputCount++;
			}
		}
		//密码输入部分
		cout << "\t\t\t\t请输入密码：";
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
				//密显功能 
				cout << "*";
				ipassword.push_back(pwdChar);
				inputCount++;
			}
		}
		//密码哈希加密
		ipassword = encrype(ipassword);
		for (int i = 0; i < data.size(); i++) {
			if (data[i]->checkInfo(iusername, ipassword)) {
				//更新当前用户
				currUser = data[i];
				//欢迎语
				if (currUser->getType() == "Root") {
					cout << "\t\t\t\t管理员登陆成功：" << iusername << endl;
				}
				else {
					cout << "\t\t\t\t登陆成功！欢迎您：" << iusername << endl;
				}
				Sleep(2000);
				return 1;
			}
		}
		cout << "\t\t\t\t用户名或密码错误，你还有" << i << "次机会！" << endl;
	}
	cout << "\t\t\t\t登陆失败！" << endl;
	return 0;
}
// 更改用户类型
void User::setType(string usertype, MyVector<User*>& data) {
	//注意调用setType时，一定要让用户重新登录，否则再次使用功能时当前用户节点已经释放了！
	//无法直接在不同类型的子类对象直接转换，所以先新建一个新的节点
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
	cout << "欢迎使用北京地铁线路小助手，系统初始化中..." << endl;
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
		cout << "\t\t\t\t[   北京地铁线路小助手   ]" << endl;
		cout << "\t\t\t\t==========================" << endl;
		cout << "\t\t\t\t[     [ ]通行证登录      ]" << endl;
		cout << "\t\t\t\t[     [ ]注册通行证      ]" << endl;
		cout << "\t\t\t\t[     [ ]免登录使用      ]" << endl;
		cout << "\t\t\t\t[     [ ]关于本系统      ]" << endl;
		cout << "\t\t\t\t[     [ ]退出本系统      ]" << endl;
		cout << "\t\t\t\t==========================";
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
		//switch-case分支
		switch (currChoice) {
			//登录
			case 0:
				//判断登录返回值
				if (users[0]->signIn(users) != 1) {
					continue;
				}
				//成功登录后进入用户菜单选项
				currUser->enterMenu(graph, dist, path, bjsubway, users);
				break;
			//注册
			case 1:
				users[0]->signUp(users);
				currUser->enterMenu(graph, dist, path, bjsubway, users);
				break;
			//免登录使用
			case 2:
				UnloginedMenu(graph, dist, path, bjsubway);
				break;
			//关于
			case 3:
				printAbout();
				PlaySound(TEXT("about.wav"), NULL, SND_FILENAME | SND_ASYNC);
				system("pause");
				PlaySound(NULL, 0, 0);
				break;
			// 退出
			case 4:
				// 删除掉用于弗洛伊德算法的两个二维数组
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
				//保存当前用户
				saveUser(users);
				return 0;
		}
	}
	return 0;
}