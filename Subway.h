#pragma once
#include <iostream>
#include "MyVector.h"
#include "voice_func.h"
#define MAX_LINES 50
#define MAX_STATIONS 100
using namespace std;

class Subway {
private:
    string data[50][100];
    int lineNum;
    int stationNum[50];

public:
    // 构造
    Subway() {
        lineNum = 0;
        for (int i = 0; i < MAX_LINES; i++) {
            stationNum[i] = 0;
        }
        for (int i = 0; i < MAX_LINES; i++) {
            for (int j = 0; j < MAX_STATIONS; j++) {
                data[i][j] = "";
            }
        }
    }
    // 析构
    ~Subway() { }
    // 获取一个站点被多少线路拥有
    int getStationNumInAllLine(string stationName) {
        int ans = 0;
        for (int i = 0; i < lineNum; i++) {
            for (int j = 1; j < stationNum[i] + 1; j++) {
                if (data[i][j] == stationName) {
                    ans += 1;
                    break;
                }
            }
        }
        return ans;
    }
    // 获取地铁线路的站点数量
    int getStationNum(string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return -1;
        }
        return stationNum[currlineIndex];
    }
    // 获取线路的数量
    int getLineNum() {
        return lineNum;
    }
    string getLineName(int index) {
        return data[index][0];
    }
    // 获取一段站点路线有多少条地铁线路拥有
    int getStationPathInAllLine(string s1, string s2) {
        int ans = 0;
        for (int i = 0; i < lineNum; i++) {
            for (int j = 1; j < stationNum[i]; j++) {
                if (data[i][j] == s1 && data[i][j + 1] == s2 || data[i][j] == s2 && data[i][j + 1] == s1) {
                    ans++;
                }
            }
        }
        return ans;
    }
    // 获取线路下标
    int lineIndex(string lineName) {
        for (int i = 0; i < lineNum; i++) {
            if (data[i][0] == lineName) {
                return i;
            }
        }
        return -1;
    }
    // 获取站点下标
    int stationIndex(string stationName, string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return false;
        }
        for (int j = 1; j < stationNum[currlineIndex] + 1; j++) {
            if (data[currlineIndex][j] == stationName) {
                return j;
            }
        }
        return -1;
    }
    // 添加线路
    bool addLine(string lineName) {
        if (lineNum >= MAX_LINES) {
            return false;
        }
        for (int i = 0; i < lineNum; i++) {
            if (data[i][0] == lineName) {
                return false;
            }
        }
        data[lineNum++][0] = lineName;
        return true;
    }
    // 添加站点
    bool addStation(string stationName, string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return false;
        }
        if (stationNum[currlineIndex] >= MAX_STATIONS) {
            return false;
        }    
        for (int j = 1; j < stationNum[currlineIndex] + 1; j++) {
            // 添加站点时要考虑是不是环线，则加入第二个判断条件：第一站不是要添加的站
            if (data[currlineIndex][j] == stationName && data[currlineIndex][1] != stationName) {
                return false;
            }
        }
        data[currlineIndex][stationNum[currlineIndex] + 1] = stationName;
        stationNum[currlineIndex]++;
        return true;
    }
    // 在positionStationName后插入newStationName
    bool insertStation(string positionStationName, string newStationName, string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1 || stationNum[currlineIndex] >= MAX_STATIONS) {
            return false;
        }
        int positionIndex = -1;
        for (int i = 0; i < stationNum[currlineIndex] + 1; i++) {
            if (data[currlineIndex][i] == positionStationName) {
                positionIndex = i;
                break;
            }
        }
        if (positionIndex == -1) {
            return false;
        }
        // 将插入位置之后的站点向后移动
        for (int i = stationNum[currlineIndex]; i > positionIndex; i--) {
            data[currlineIndex][i + 1] = data[currlineIndex][i];
        }
        // 插入新的站点
        data[currlineIndex][positionIndex + 1] = newStationName;
        stationNum[currlineIndex]++;
        return true;
    }
    // 打印线路信息
    bool printLineInfo(string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return false;
        }
        cout << "北京地铁" << lineName << "：" << endl;
        if (stationNum[currlineIndex] == 0) {
            return true;
        }
        if (stationNum[currlineIndex] == 1) {
            cout << data[currlineIndex][1] << endl;
            return true;
        }
        for (int i = 1; i < stationNum[currlineIndex]; i++) {
            cout << data[currlineIndex][i] << " <---> ";
        }
        cout << data[currlineIndex][stationNum[currlineIndex]] << endl;
        return true;;
    }
    // 打印线路名称
    void printLineNames() {
        for (int i = 0; i < lineNum; i++) {
            cout << right << setw(15) << data[i][0] << "\t";
            if ((i + 1) % 5 == 0) {
                cout << endl;
            }
        }
        cout << endl;
        return;
    }
    // 打印整个地铁的所有信息
    void printSubwayInfo() {
        for (int i = 0; i < lineNum; i++) {
            printLineInfo(data[i][0]);
            cout << endl;
        }
        return;
    }
    // 获取一个线路的所有站点
    string* getStations(string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return nullptr;
        }
        return &data[currlineIndex][1];
    }
    // 删除线路
    bool deleteLine(string lineName) {
        for (int i = 0; i < lineNum; i++) {
            if (data[i][0] == lineName) {
                stationNum[i] = 0;
                for (int j = i; j < lineNum - 1; j++) {
                    for (int k = 0; k < MAX_STATIONS; k++) {
                        data[j][k] = data[j+1][k];
                    }
                }
                for (int k = 0; k < MAX_STATIONS; k++) {
                    data[lineNum - 1][k] = "";
                }
                lineNum--;
                return true;
            }
        }
        return false;
    }
    // 指定线路删除站点
    bool deleteStation(string stationName, string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return false;
        }
        for (int i = 1; i < stationNum[currlineIndex] + 1; i++) {
            if (data[currlineIndex][i] == stationName) {
                for (int j = i; j < stationNum[currlineIndex]; j++) {
                    data[currlineIndex][j] = data[currlineIndex][j + 1];
                }
                data[currlineIndex][stationNum[currlineIndex]] = "";
                stationNum[currlineIndex]--;
                return true;
            }
        }
        return false;
    }
    // 在所有线路中删除站点
    bool deleteStationAllLine(string stationName) {
        int flag = 0;
        for (int k = 0; k < lineNum; k++) {
            for (int i = 1; i < stationNum[k] + 1; i++) {
                if (data[k][i] == stationName) {
                    for (int j = i; j < stationNum[k]; j++) {
                        data[k][j] = data[k][j + 1];
                    }
                    data[k][stationNum[k]] = "";
                    stationNum[k]--;
                    flag = 1;
                }
            }
        }
        if (flag == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    // 修改线路名称
    bool modifyLineName(string oldLineName, string newLineName) {
        int currlineIndex = lineIndex(oldLineName);
        if (currlineIndex == -1) {
            return false;
        }
        // 检查新名称是否已存在
        if (lineIndex(newLineName) != -1) {
            return false;
        }
        data[currlineIndex][0] = newLineName;
        return true;
    }
    // 指定线路修改站点名称
    bool modifyStationName(string oldStationName, string newStationName, string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return false;
        }
        for (int i = 1; i < stationNum[currlineIndex] + 1; i++) {
            if (data[currlineIndex][i] == oldStationName) {
                data[currlineIndex][i] = newStationName;
                return true;
            }
        }
        return false;
    }
    // 在所有线路中修改站点名称
    bool modifyStationNameAllLine(string oldStationName, string newStationName) {
        int flag = 0;
        for (int j = 0; j < lineNum; j++) {
            for (int i = 1; i < stationNum[j] + 1; i++) {
                if (data[j][i] == oldStationName) {
                    data[j][i] = newStationName;
                    flag = 1;
                }
            }
        }
        if (flag == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    // 获取包含指定站点的所有线路
    MyVector<string> getLinesForStation(string stationName) {
        MyVector<string> lines;
        for (int i = 0; i < lineNum; i++) {
            for (int j = 1; j < stationNum[i] + 1; j++) {
                if (data[i][j] == stationName) {
                    lines.push_back(data[i][0]);
                    break;
                }
            }
        }
        return lines;
    }
    // 获取在线路中从站点1到站点2的方向名称
    string getPathToward(string station1, string station2, string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return "Error：不存在的线路名称";
        }
        // 如果第一站等于最后一站（说明是环线），则直接返回下一站，以下一站作为方向
        if (data[currlineIndex][1] == data[currlineIndex][stationNum[currlineIndex]]) {
            return station2;
        }
        // 从第二站开始遍历，找到上一站和下一站
        for (int i = 1; i < stationNum[currlineIndex]; i++) {
            if (data[currlineIndex][i] == station1) {
                if (i != 1 && data[currlineIndex][i - 1] == station2) {
                    // 返回第一站的方向
                    return data[currlineIndex][1];
                }
                else if (data[currlineIndex][i + 1] == station2){
                    // 返回最后一站的方向
                    return data[currlineIndex][stationNum[currlineIndex]];
                }
            }
            if (data[currlineIndex][i] == station2) {
                if (i != 1 && data[currlineIndex][i - 1] == station1) {
                    // 返回第一站的方向
                    return data[currlineIndex][stationNum[currlineIndex]];
                }
                else if (data[currlineIndex][i + 1] == station1) {
                    // 返回最后一站的方向
                    return data[currlineIndex][1];
                }
            }
        }
        return "Error: 未找到合法站点";
    }
    // 推算并打印换乘信息
    void printTransferInformation(MyVector<string> stations) {
        // 如果站点数量<=2直接返回
        if (stations.size() <= 2) {
            return;
        }
        // 在此定义一些变量
        int transferTimes = 0;
        string firstLine = "";
        string lastLine = "";
        // 上一条线路，防止清河站不换乘的奇葩现象
        string prevLine = "";
        cout << "地铁换乘小贴士：" << endl;
        if (voiceMode) speakString("地铁换乘小贴士");
        // 外层大循环，遍历所有站点
        for (int i = 0; i < stations.size() - 2; i++) {
            // 连续获取三个站点的信息
            string station1 = stations[i];
            string station2 = stations[i + 1];
            string station3 = stations[i + 2];
            // 获取三个站点分别所在的所有线路
            MyVector<string> lines1 = getLinesForStation(station1);
            MyVector<string> lines2 = getLinesForStation(station2);
            MyVector<string> lines3 = getLinesForStation(station3);
            // 查找station1和station2的共有线路（可能有多条，所以用MyVector）
            string commonLine12;
            MyVector<string> potentialLines;
            for (int j = 0; j < lines1.size(); j++) {
                for (int k = 0; k < lines2.size(); k++) {
                    if (lines1[j] == lines2[k]) {
                        potentialLines.push_back(lines1[j]);
                    }
                }
            }
            // 检查是否有可以继续到达station3的线路（优先选择与station3也共有的线路）
            for (int j = 0; j < potentialLines.size(); j++) {
                for (int k = 0; k < lines3.size(); k++) {
                    if (potentialLines[j] == lines3[k]) {
                        commonLine12 = potentialLines[j];
                        break;
                    }
                }
                if (!commonLine12.empty()) {
                    break;
                }
            }
            if (commonLine12.empty() && !potentialLines.empty()) {
                // 如果没有线路可以继续到station3（第二条线路），但有第一个共有线路，则使用第一个共有线路
                commonLine12 = potentialLines[0];
            }
            // 查找station2和station3的共有线路
            string commonLine23;
            for (int j = 0; j < lines2.size(); j++) {
                for (int k = 0; k < lines3.size(); k++) {
                    if (lines2[j] == lines3[k]) {
                        commonLine23 = lines2[j];
                        break;
                    }
                }
                // 如果找到了最优解就直接退出（最优解的意思就是12相同线的和23相同的线这两个线路一样）
                if (commonLine12 == commonLine23) {
                    break;
                }
            }
            if (firstLine == "") {
                firstLine = commonLine12;
            }
            // 如果station1和station2的共有线路和station2和station3的共有线路不同，则在station2需要换乘
            // 并且需要确保下一条线路不为空
            if (commonLine12 != commonLine23 && !commonLine23.empty()) {
                if (transferTimes == 0) {
                    firstLine = commonLine12;
                }
                cout << "在[" << station2 << "]需要从[北京地铁" << commonLine12 << "]换乘到[北京地铁" << commonLine23 << "](" << getPathToward(station2, station3, commonLine23) << "方向)" << endl;
                lastLine = commonLine23;
                transferTimes++;
            }
            else if (commonLine12 == commonLine23 && commonLine12 != prevLine && prevLine != "") {
                if (transferTimes == 0) {
                    firstLine = prevLine;
                }
                cout << "在[" << station2 << "]需要从[北京地铁" << prevLine << "]换乘到[北京地铁" << commonLine23 << "](" << getPathToward(station2, station3, commonLine23) << "方向)" << endl;
                lastLine = commonLine23;
                transferTimes++;
            }
            prevLine = commonLine23;
        }
        // 输出换乘信息
        if (transferTimes == 0) {
            cout << "好耶，该条线路无需换乘！您只需要从[北京地铁" << firstLine << "](" << getPathToward(stations[0], stations[1], firstLine) << "方向)的[" << stations[0] << "]上车，然后从[" << stations[stations.size() - 1] << "]下车" << endl << endl;
            if (voiceMode) {
                stringstream voiceString;
                voiceString << "好耶，该条线路无需换乘！您只需要从[北京地铁" << firstLine << "](" << getPathToward(stations[0], stations[1], firstLine) << "方向)的[" << stations[0] << "]上车，然后从[" << stations[stations.size() - 1] << "]下车";
                speakString(voiceString.str(), 7);
            }
        }
        else {
            cout << "共计需要换乘" << transferTimes << "次" << endl;
            cout << "请您从[北京地铁" << firstLine << "](" << getPathToward(stations[0], stations[1], firstLine) << "方向)的[" << stations[0] << "]上车，然后在[北京地铁" << lastLine << "]的[" << stations[stations.size() - 1] << "]下车" << endl << endl;
            if (voiceMode) {
                stringstream voiceString;
                voiceString << "共计需要换乘" << transferTimes << "次" << "请您从[北京地铁" << firstLine << "](" << getPathToward(stations[0], stations[1], firstLine) << "方向)的[" << stations[0] << "]上车，然后在[北京地铁" << lastLine << "]的[" << stations[stations.size() - 1] << "]下车";
                speakString(voiceString.str(), 7);
            }
        }
        return;
    }
};