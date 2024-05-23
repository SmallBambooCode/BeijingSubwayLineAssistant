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
    // ����
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
    // ����
    ~Subway() { }
    // ��ȡһ��վ�㱻������·ӵ��
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
    // ��ȡ������·��վ������
    int getStationNum(string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return -1;
        }
        return stationNum[currlineIndex];
    }
    // ��ȡ��·������
    int getLineNum() {
        return lineNum;
    }
    string getLineName(int index) {
        return data[index][0];
    }
    // ��ȡһ��վ��·���ж�����������·ӵ��
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
    // ��ȡ��·�±�
    int lineIndex(string lineName) {
        for (int i = 0; i < lineNum; i++) {
            if (data[i][0] == lineName) {
                return i;
            }
        }
        return -1;
    }
    // ��ȡվ���±�
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
    // �����·
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
    // ���վ��
    bool addStation(string stationName, string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return false;
        }
        if (stationNum[currlineIndex] >= MAX_STATIONS) {
            return false;
        }    
        for (int j = 1; j < stationNum[currlineIndex] + 1; j++) {
            // ���վ��ʱҪ�����ǲ��ǻ��ߣ������ڶ����ж���������һվ����Ҫ��ӵ�վ
            if (data[currlineIndex][j] == stationName && data[currlineIndex][1] != stationName) {
                return false;
            }
        }
        data[currlineIndex][stationNum[currlineIndex] + 1] = stationName;
        stationNum[currlineIndex]++;
        return true;
    }
    // ��positionStationName�����newStationName
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
        // ������λ��֮���վ������ƶ�
        for (int i = stationNum[currlineIndex]; i > positionIndex; i--) {
            data[currlineIndex][i + 1] = data[currlineIndex][i];
        }
        // �����µ�վ��
        data[currlineIndex][positionIndex + 1] = newStationName;
        stationNum[currlineIndex]++;
        return true;
    }
    // ��ӡ��·��Ϣ
    bool printLineInfo(string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return false;
        }
        cout << "��������" << lineName << "��" << endl;
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
    // ��ӡ��·����
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
    // ��ӡ����������������Ϣ
    void printSubwayInfo() {
        for (int i = 0; i < lineNum; i++) {
            printLineInfo(data[i][0]);
            cout << endl;
        }
        return;
    }
    // ��ȡһ����·������վ��
    string* getStations(string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return nullptr;
        }
        return &data[currlineIndex][1];
    }
    // ɾ����·
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
    // ָ����·ɾ��վ��
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
    // ��������·��ɾ��վ��
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
    // �޸���·����
    bool modifyLineName(string oldLineName, string newLineName) {
        int currlineIndex = lineIndex(oldLineName);
        if (currlineIndex == -1) {
            return false;
        }
        // ����������Ƿ��Ѵ���
        if (lineIndex(newLineName) != -1) {
            return false;
        }
        data[currlineIndex][0] = newLineName;
        return true;
    }
    // ָ����·�޸�վ������
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
    // ��������·���޸�վ������
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
    // ��ȡ����ָ��վ���������·
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
    // ��ȡ����·�д�վ��1��վ��2�ķ�������
    string getPathToward(string station1, string station2, string lineName) {
        int currlineIndex = lineIndex(lineName);
        if (currlineIndex == -1) {
            return "Error�������ڵ���·����";
        }
        // �����һվ�������һվ��˵���ǻ��ߣ�����ֱ�ӷ�����һվ������һվ��Ϊ����
        if (data[currlineIndex][1] == data[currlineIndex][stationNum[currlineIndex]]) {
            return station2;
        }
        // �ӵڶ�վ��ʼ�������ҵ���һվ����һվ
        for (int i = 1; i < stationNum[currlineIndex]; i++) {
            if (data[currlineIndex][i] == station1) {
                if (i != 1 && data[currlineIndex][i - 1] == station2) {
                    // ���ص�һվ�ķ���
                    return data[currlineIndex][1];
                }
                else if (data[currlineIndex][i + 1] == station2){
                    // �������һվ�ķ���
                    return data[currlineIndex][stationNum[currlineIndex]];
                }
            }
            if (data[currlineIndex][i] == station2) {
                if (i != 1 && data[currlineIndex][i - 1] == station1) {
                    // ���ص�һվ�ķ���
                    return data[currlineIndex][stationNum[currlineIndex]];
                }
                else if (data[currlineIndex][i + 1] == station1) {
                    // �������һվ�ķ���
                    return data[currlineIndex][1];
                }
            }
        }
        return "Error: δ�ҵ��Ϸ�վ��";
    }
    // ���㲢��ӡ������Ϣ
    void printTransferInformation(MyVector<string> stations) {
        // ���վ������<=2ֱ�ӷ���
        if (stations.size() <= 2) {
            return;
        }
        // �ڴ˶���һЩ����
        int transferTimes = 0;
        string firstLine = "";
        string lastLine = "";
        // ��һ����·����ֹ���վ�����˵���������
        string prevLine = "";
        cout << "��������С��ʿ��" << endl;
        if (voiceMode) speakString("��������С��ʿ");
        // ����ѭ������������վ��
        for (int i = 0; i < stations.size() - 2; i++) {
            // ������ȡ����վ�����Ϣ
            string station1 = stations[i];
            string station2 = stations[i + 1];
            string station3 = stations[i + 2];
            // ��ȡ����վ��ֱ����ڵ�������·
            MyVector<string> lines1 = getLinesForStation(station1);
            MyVector<string> lines2 = getLinesForStation(station2);
            MyVector<string> lines3 = getLinesForStation(station3);
            // ����station1��station2�Ĺ�����·�������ж�����������MyVector��
            string commonLine12;
            MyVector<string> potentialLines;
            for (int j = 0; j < lines1.size(); j++) {
                for (int k = 0; k < lines2.size(); k++) {
                    if (lines1[j] == lines2[k]) {
                        potentialLines.push_back(lines1[j]);
                    }
                }
            }
            // ����Ƿ��п��Լ�������station3����·������ѡ����station3Ҳ���е���·��
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
                // ���û����·���Լ�����station3���ڶ�����·�������е�һ��������·����ʹ�õ�һ��������·
                commonLine12 = potentialLines[0];
            }
            // ����station2��station3�Ĺ�����·
            string commonLine23;
            for (int j = 0; j < lines2.size(); j++) {
                for (int k = 0; k < lines3.size(); k++) {
                    if (lines2[j] == lines3[k]) {
                        commonLine23 = lines2[j];
                        break;
                    }
                }
                // ����ҵ������Ž��ֱ���˳������Ž����˼����12��ͬ�ߵĺ�23��ͬ������������·һ����
                if (commonLine12 == commonLine23) {
                    break;
                }
            }
            if (firstLine == "") {
                firstLine = commonLine12;
            }
            // ���station1��station2�Ĺ�����·��station2��station3�Ĺ�����·��ͬ������station2��Ҫ����
            // ������Ҫȷ����һ����·��Ϊ��
            if (commonLine12 != commonLine23 && !commonLine23.empty()) {
                if (transferTimes == 0) {
                    firstLine = commonLine12;
                }
                cout << "��[" << station2 << "]��Ҫ��[��������" << commonLine12 << "]���˵�[��������" << commonLine23 << "](" << getPathToward(station2, station3, commonLine23) << "����)" << endl;
                lastLine = commonLine23;
                transferTimes++;
            }
            else if (commonLine12 == commonLine23 && commonLine12 != prevLine && prevLine != "") {
                if (transferTimes == 0) {
                    firstLine = prevLine;
                }
                cout << "��[" << station2 << "]��Ҫ��[��������" << prevLine << "]���˵�[��������" << commonLine23 << "](" << getPathToward(station2, station3, commonLine23) << "����)" << endl;
                lastLine = commonLine23;
                transferTimes++;
            }
            prevLine = commonLine23;
        }
        // ���������Ϣ
        if (transferTimes == 0) {
            cout << "��Ү��������·���軻�ˣ���ֻ��Ҫ��[��������" << firstLine << "](" << getPathToward(stations[0], stations[1], firstLine) << "����)��[" << stations[0] << "]�ϳ���Ȼ���[" << stations[stations.size() - 1] << "]�³�" << endl << endl;
            if (voiceMode) {
                stringstream voiceString;
                voiceString << "��Ү��������·���軻�ˣ���ֻ��Ҫ��[��������" << firstLine << "](" << getPathToward(stations[0], stations[1], firstLine) << "����)��[" << stations[0] << "]�ϳ���Ȼ���[" << stations[stations.size() - 1] << "]�³�";
                speakString(voiceString.str(), 7);
            }
        }
        else {
            cout << "������Ҫ����" << transferTimes << "��" << endl;
            cout << "������[��������" << firstLine << "](" << getPathToward(stations[0], stations[1], firstLine) << "����)��[" << stations[0] << "]�ϳ���Ȼ����[��������" << lastLine << "]��[" << stations[stations.size() - 1] << "]�³�" << endl << endl;
            if (voiceMode) {
                stringstream voiceString;
                voiceString << "������Ҫ����" << transferTimes << "��" << "������[��������" << firstLine << "](" << getPathToward(stations[0], stations[1], firstLine) << "����)��[" << stations[0] << "]�ϳ���Ȼ����[��������" << lastLine << "]��[" << stations[stations.size() - 1] << "]�³�";
                speakString(voiceString.str(), 7);
            }
        }
        return;
    }
};