#pragma once
#include <iostream>
#include "MyVector.h"
#include "Queue.h"
#include "Subway.h"
using namespace std;

// ����˳��۸�
double costCalculate(double s) {
	double ans;
	// ���ݱ��������շѱ�׼���м���
	if (s <= 6) {
		ans = 3.0;
	}
	else if (s <= 12) {
		ans = 4.0;
	}
	else if (s <= 22) {
		ans = 5.0;
	}
	else if (s <= 32) {
		ans = 6.0;
	}
	else {
		// ceil��ȡ�컨�壨һ��ȡ����ʽ~����Ϊ�˽��������������ٵ�����
		ans = 6.0 + ceil((s - 32) / 20.0);
	}
	return ans;
}

// �ߣ�Edge���ڵ�
// T����Զ������;��ǻ������ݵ����ͣ�Ҳ����info�����͡��������Ҫ��Ȩֵ����������Ϊint��double�ȵ�
template<typename E>
class EdgeBox {
private:
	int iVex, jVex;
	EdgeBox<E>* iLink, * jLink;  // iLinkָ����һ�������ڶ���iVex�ıߣ�ͬ��jLinkָ����һ�������ڶ���jVex�ı�
	E info;
public:
	// ��������
	EdgeBox(int iVex, int jVex, E info, EdgeBox<E>* iLink = nullptr, EdgeBox<E>* jLink = nullptr) {
		this->iVex = iVex;
		this->jVex = jVex;
		this->info = info;
		this->iLink = iLink;
		this->jLink = jLink;
	}
	// get,set ����
	int getIVex() {
		return iVex;
	}
	int getJVex() {
		return jVex;
	}
	EdgeBox<E>* getILink() {
		return iLink;
	}
	EdgeBox<E>* getJLink() {
		return jLink;
	}
	E getInfo() {
		return info;
	}
	void setInfo(E info) {
		this->info = info;
		return;
	}
	void setILink(EdgeBox<E>* iLink) {
		this->iLink = iLink;
		return;
	}
	void setJLink(EdgeBox<E>* jLink) {
		this->jLink = jLink;
		return;
	}
	void setIVex(int iVex) {
		this->iVex = iVex;
	}
	void setJVex(int jVex) {
		this->jVex = jVex;
	}
};

// ����ڵ�
// T����Զ������;��Ƕ�������ݵ����ͣ�Ҳ����data�����͡�
template<typename V, typename E>
class VexNode {
private:
	V data;
	EdgeBox<E>* firstEdge;
	bool enabled;
public:
	// ��������.
	VexNode() : firstEdge(nullptr), enabled(true) {}
	VexNode(V data, EdgeBox<E>* firstEdge = nullptr) {
		this->data = data;
		this->firstEdge = firstEdge;
		this->enabled = true;
	}
	// get,set ����
	// ��ȡ����"[CLOSED]"������
	V getData() {
		// �����enabled == true����������"[CLOSED]"��ǩ��ֱ�ӷ���
		if (enabled) {
			return data;
		}
		else {
			// ȥ��"[CLOSED]"
			string str = data, suffix = "[CLOSED]";
			// ���"[CLOSED]"�������
			if (str.rfind(suffix) == (str.size() - suffix.size())) {
				// ɾ�� "[CLOSED]"
				str = str.substr(0, str.size() - suffix.size());
			}
			return str;
		}
	}
	// ��ȡԭʼ����
	V getOrginData() {
		return data;
	}
	// ��ȡ���������еĶ���ĵ�һ��ָ��ı�
	EdgeBox<E>* getFirstEdge() {
		return firstEdge;
	}
	// ��ȡ����״̬
	bool getEnabled() {
		return enabled;
	}
	// ���ö���ĵ�һ��ָ��ı�
	void setFirstEdge(EdgeBox<E>* firstEdge) {
		this->firstEdge = firstEdge;
		return;
	}
	// ���ö�������
	void setData(V data) {
		this->data = data;
		return;
	}
	// ���ö���״̬
	void setEnabled(bool enabled) {
		this->enabled = enabled;
	}
};
// �ڽӶ��ر�
// V�Ƕ����������ͣ�A�Ǳ���������
template<typename V, typename E>
class AMLGraph {
private:
	VexNode<V, E>* AMLlist;
	int vexnum, edgenum, maxsize;
public:
	// ��������
	AMLGraph() {
		AMLlist = new VexNode<V, E>[4];
		vexnum = 0;
		edgenum = 0;
		maxsize = 4;
	}
	~AMLGraph() {
		clearList();
		delete[] AMLlist;
		AMLlist = nullptr;
	}
	// get,set ����
	int getVexnum() {
		return vexnum;
	}
	int getEdgenum() {
		return edgenum;
	}
	int getMaxsize() {
		return maxsize;
	}
	// ����
	// ����
	bool expandMem() {
		maxsize *= 2;
		VexNode<V, E>* oldData = AMLlist;
		AMLlist = new VexNode<V, E>[maxsize];
		if (AMLlist == nullptr) {
			AMLlist = oldData;
			maxsize /= 2;
			return false;
		}
		for (int i = 0; i < vexnum; i++) {
			AMLlist[i] = oldData[i];
		}
		delete[] oldData;
		oldData = nullptr;
		return true;
	}
	// ����
	bool reduceMem() {
		maxsize /= 2;
		VexNode<V, E>* oldData = AMLlist;
		AMLlist = new VexNode<V, E>[maxsize];
		if (AMLlist == nullptr) {
			AMLlist = oldData;
			maxsize *= 2;
			return false;
		}
		for (int i = 0; i < vexnum; i++) {
			AMLlist[i] = oldData[i];
		}
		delete[] oldData;
		oldData = nullptr;
		return true;
	}
	// ��Ӷ���
	bool addVex(V data) {
		for (int i = 0; i < vexnum; i++) {
			if (AMLlist[i].getData() == data) {
				return false;
			}
		}
		if (vexnum >= maxsize) {
			if (expandMem()) {
				//cout << "�����������Զ����ݡ�" << endl;
			}
			else {
				cout << "�Զ�����ʧ�ܡ����������������޷�������ӣ�" << endl;
				return false;
			}
		}
		AMLlist[vexnum++].setData(data);
		return true;
	}
	// ��ӱ�
	bool addEdge(int iVex, int jVex, E info) {
		if (iVex >= vexnum || jVex >= vexnum || jVex < 0 || iVex < 0 || iVex == jVex) {
			return false;
		}
		// �����Ƿ��Ѿ�����
		EdgeBox<E>* currentEdge = AMLlist[iVex].getFirstEdge();
		while (currentEdge != nullptr) {
			if ((currentEdge->getIVex() == iVex && currentEdge->getJVex() == jVex) ||
				(currentEdge->getIVex() == jVex && currentEdge->getJVex() == iVex)) {
				return false;
			}
			// ���ݵ�ǰ�ߵ���ʼ������ iVex ���� jVex ѡ����һ����
			if (currentEdge->getIVex() == iVex) {
				currentEdge = currentEdge->getILink();
			}
			else {
				currentEdge = currentEdge->getJLink();
			}
		}
		// �½���
		EdgeBox<E>* newEdge = new EdgeBox<E>(iVex, jVex, info);
		// ���� iVex �ı��б�
		currentEdge = AMLlist[iVex].getFirstEdge();
		if (currentEdge == nullptr) {
			AMLlist[iVex].setFirstEdge(newEdge);
		}
		else {
			EdgeBox<E>* lastEdge = nullptr;
			while (currentEdge != nullptr) {
				lastEdge = currentEdge;
				currentEdge = (currentEdge->getIVex() == iVex) ? currentEdge->getILink() : currentEdge->getJLink();
			}
			if (lastEdge->getIVex() == iVex) {
				lastEdge->setILink(newEdge);
			}
			else {
				lastEdge->setJLink(newEdge);
			}
		}
		// ���� jVex �ı��б�
		currentEdge = AMLlist[jVex].getFirstEdge();
		if (currentEdge == nullptr) {
			AMLlist[jVex].setFirstEdge(newEdge);
		}
		else {
			EdgeBox<E>* lastEdge = nullptr;
			while (currentEdge != nullptr) {
				lastEdge = currentEdge;
				currentEdge = (currentEdge->getJVex() == jVex) ? currentEdge->getJLink() : currentEdge->getILink();
			}
			if (lastEdge->getJVex() == jVex) {
				lastEdge->setJLink(newEdge);
			}
			else {
				lastEdge->setILink(newEdge);
			}
		}
		edgenum++; // �ߵ���������
		return true;
	}
	// ɾ����
	bool deleteEdge(int iVex, int jVex) {
		if (iVex >= vexnum || jVex >= vexnum || jVex < 0 || iVex < 0 || iVex == jVex) {
			return false;
		}
		// ����һЩָ��
		EdgeBox<E>* toDeleteEdge = nullptr;
		EdgeBox<E>* currentEdge = nullptr;
		EdgeBox<E>* preEdge = nullptr;
		EdgeBox<E>* preIEdge = nullptr;
		EdgeBox<E>* preJEdge = nullptr;
		// �ȴ�iVex���㿪ʼ����
		currentEdge = AMLlist[iVex].getFirstEdge();
		while (currentEdge != nullptr) {
			if (preEdge != nullptr) {
				if (preEdge->getIVex() == currentEdge->getIVex() || preEdge->getJVex() == currentEdge->getIVex()) {
					preIEdge = preEdge;
				}
				if (preEdge->getIVex() == currentEdge->getJVex() || preEdge->getJVex() == currentEdge->getJVex()) {
					preJEdge = preEdge;
				}
			}
			if ((currentEdge->getIVex() == iVex && currentEdge->getJVex() == jVex) || (currentEdge->getIVex() == jVex && currentEdge->getJVex() == iVex)) {
				toDeleteEdge = currentEdge;
				break;
			}
			if (currentEdge->getIVex() == iVex || currentEdge->getIVex() == jVex) {
				preEdge = currentEdge;
				currentEdge = currentEdge->getILink();
				continue;
			}
			else if (currentEdge->getJVex() == iVex || currentEdge->getJVex() == jVex) {
				preEdge = currentEdge;
				currentEdge = currentEdge->getJLink();
				continue;
			}
			else {
				break;
			}
		}
		// �ٴ�jVex���㿪ʼ����
		currentEdge = AMLlist[jVex].getFirstEdge();
		preEdge = nullptr;
		while (currentEdge != nullptr) {
			if (preEdge != nullptr) {
				// ������Ҫ�ٴ��ж�preI����J�ǲ��ǲ�׼ȷ�ģ�����Ѿ���ȷ
				if (preIEdge == nullptr || (preIEdge->getILink() != toDeleteEdge && preIEdge->getJLink() != toDeleteEdge)) {
					if (preEdge->getIVex() == currentEdge->getIVex() || preEdge->getJVex() == currentEdge->getIVex()) {
						preIEdge = preEdge;
					}
				}
				if (preJEdge == nullptr || (preJEdge->getILink() != toDeleteEdge && preJEdge->getJLink() != toDeleteEdge)) {
					if (preEdge->getIVex() == currentEdge->getJVex() || preEdge->getJVex() == currentEdge->getJVex()) {
						preJEdge = preEdge;
					}
				}
			}
			if ((currentEdge->getIVex() == iVex && currentEdge->getJVex() == jVex) || (currentEdge->getIVex() == jVex && currentEdge->getJVex() == iVex)) {
				break;
			}
			if (currentEdge->getIVex() == iVex || currentEdge->getIVex() == jVex) {
				preEdge = currentEdge;
				currentEdge = currentEdge->getILink();
				continue;
			}
			else if (currentEdge->getJVex() == iVex || currentEdge->getJVex() == jVex) {
				preEdge = currentEdge;
				currentEdge = currentEdge->getJLink();
				continue;
			}
			else {
				break;
			}
		}
		if (toDeleteEdge == nullptr) {
			return false;
		}
		// ��������һ���ӣ�����Ҫ����Ļ��ж������preIEdge���Ϸ�����ֱ�����ö���������Ķ�����
		if (preIEdge == nullptr || (preIEdge->getILink() != toDeleteEdge && preIEdge->getJLink() != toDeleteEdge)) {
			AMLlist[toDeleteEdge->getIVex()].setFirstEdge(toDeleteEdge->getILink());
		}
		else {
			if (preIEdge->getIVex() == toDeleteEdge->getIVex()) {
				preIEdge->setILink(toDeleteEdge->getILink());
			}
			else {
				preIEdge->setJLink(toDeleteEdge->getILink());
			}
		}
		if (preJEdge == nullptr || (preJEdge->getILink() != toDeleteEdge && preJEdge->getJLink() != toDeleteEdge)) {
			AMLlist[toDeleteEdge->getJVex()].setFirstEdge(toDeleteEdge->getJLink());
		}
		else {
			if (preJEdge->getJVex() == toDeleteEdge->getJVex()) {
				preJEdge->setJLink(toDeleteEdge->getJLink());
			}
			else {
				preJEdge->setILink(toDeleteEdge->getJLink());
			}
		}
		delete toDeleteEdge;
		edgenum--;
		return true;
	}
	// �������AML
	bool clearList() {
		while (deleteVex(0));
		return true;
	}
	// ɾ������
	bool deleteVex(int vex) {
		if (vex >= vexnum || vex < 0) {
			return false;
		}
		for (int i = 0; i < vexnum; i++) {
			if (i != vex) {
				deleteEdge(vex, i);
			}
		}
		for (int i = vex; i < vexnum - 1; i++) {
			AMLlist[i] = AMLlist[i + 1];
		}
		vexnum--;
		int acIndex = 0;
		EdgeBox<E>** already_changed = new EdgeBox<E>*[edgenum];

		// �������бߣ��ж�ivex��jvex��ֵ
		for (int i = 0; i < vexnum; i++) {
			EdgeBox<E>* currentEdge = AMLlist[i].getFirstEdge();
			while (currentEdge != nullptr) {
				bool change = false;
				for (int j = 0; j < acIndex; j++) {
					if (already_changed[j] == currentEdge) {
						change = true;
						break;
					}
				}
				if (!change) {
					if (currentEdge->getIVex() >= vex) {
						currentEdge->setIVex(currentEdge->getIVex() - 1);
					}
					if (currentEdge->getJVex() >= vex) {
						currentEdge->setJVex(currentEdge->getJVex() - 1);
					}
					already_changed[acIndex++] = currentEdge;
				}
				if (currentEdge->getIVex() == i) {
					currentEdge = currentEdge->getILink();
				}
				else if (currentEdge->getJVex() == i) {
					currentEdge = currentEdge->getJLink();
				}
				else {
					break;
				}
			}
		}
		delete[] already_changed;
		if (vexnum <= maxsize / 2 && maxsize > 4) {
			reduceMem();
			//cout << "�����������Զ����ݡ�" << endl;
		}
		return true;
	}
	// �޸ı�����
	bool updateEdgeInfo(int iVex, int jVex, E info) {
		if (iVex >= vexnum || jVex >= vexnum || jVex < 0 || iVex < 0) {
			return false;
		}
		EdgeBox<E>* currentEdge = AMLlist[iVex].getFirstEdge();
		while (currentEdge != nullptr) {
			// ����ͼ������iVex��jVex�ĸ���ǰ���ܼ����Ƿ�һ��
			if ((currentEdge->getIVex() == iVex && currentEdge->getJVex() == jVex) || (currentEdge->getIVex() == jVex && currentEdge->getJVex() == iVex)) {
				// �����ҵ�����
				currentEdge->setInfo(info);
				return true;
			}
			// ���ݵ�ǰ�ߵ���ʼ������ iVex ���� jVex ѡ����һ����
			// ΪʲôҪ���������Ϊ������ҵ���1->0��������Ϊ1��firstEdge�Ѿ�ָ���0������0->1�ˣ����Լ�����жϿ����ý�������·�����1ָ��Ľڵ�
			if (currentEdge->getIVex() == iVex) {
				currentEdge = currentEdge->getILink();
			}
			else {
				currentEdge = currentEdge->getJLink();
			}
		}
		return false;
	}
	// �޸Ķ�������
	bool updateVexData(int vex, V data) {
		if (vex >= vexnum || vex < 0) {
			return false;
		}
		AMLlist[vex].setData(data);
		return true;
	}
	// �������ݲ��Ҷ�����±�
	int getVexIndex(V data) {
		for (int i = 0; i < vexnum; i++) {
			if (AMLlist[i].getData() == data) {
				return i;
			}
		}
		// δ�ҵ�����-1
		return -1;
	}
	// ��ȡ�ߵ�Ȩֵ
	E getEdgeInfo(int iVex, int jVex) {
		if (iVex >= vexnum || jVex >= vexnum || jVex < 0 || iVex < 0) {
			return E();
		}
		EdgeBox<E>* currentEdge = AMLlist[iVex].getFirstEdge();
		while (currentEdge != nullptr) {
			// ����ͼ������iVex��jVex�ĸ���ǰ���ܼ����Ƿ�һ��
			if ((currentEdge->getIVex() == iVex && currentEdge->getJVex() == jVex) || (currentEdge->getIVex() == jVex && currentEdge->getJVex() == iVex)) {
				// �����ҵ�����
				return currentEdge->getInfo();
			}
			// ���ݵ�ǰ�ߵ���ʼ������ iVex ���� jVex ѡ����һ����
			// ΪʲôҪ���������Ϊ������ҵ���1->0��������Ϊ1��firstEdge�Ѿ�ָ���0������0->1�ˣ����Լ�����жϿ����ý�������·�����1ָ��Ľڵ�
			if (currentEdge->getIVex() == iVex) {
				currentEdge = currentEdge->getILink();
			}
			else {
				currentEdge = currentEdge->getJLink();
			}
		}
		return E();
	}
	// �޸ı�ָ��
	bool updateEdgeDirect(int iVex, int jVex, int newIVex, int newJVex) {
		// �жϴ����tailVex��headVex�Ƿ�Ϸ�
		if (iVex >= vexnum || jVex >= vexnum || newIVex >= vexnum || newJVex >= vexnum || iVex < 0 || jVex < 0 || newIVex < 0 || newJVex < 0) {
			return false;
		}
		if (!addEdge(newIVex, newJVex, getEdgeInfo(iVex, jVex))) {
			return false;
		}
		if (!deleteEdge(iVex, jVex)) {
			return false;
		}
		return true;
	}
	// ��ӡָ�����������
	void printVexInfo(int vex) {
		if (vex >= vexnum || vex < 0) {
			return;
		}
		// ��������
		VexNode<V, E>& vexNode = AMLlist[vex];
		cout << "[" << vex << "] " << vexNode.getOrginData() << endl;

		// ������
		EdgeBox<E>* currentEdge = vexNode.getFirstEdge();
		while (currentEdge != nullptr) {
			// �жϵ�ǰ�ߵ���ʼ���㣨iVex���ǲ��Ǵ�����Ҫ��ӡ�Ķ���
			if (currentEdge->getIVex() == vex) {
				cout << "[" << vex << "](" << vexNode.getOrginData() << ") <==(" << currentEdge->getInfo() << ")==> [" << currentEdge->getJVex() << "](" << AMLlist[currentEdge->getJVex()].getOrginData() << ")" << endl;
				currentEdge = currentEdge->getILink();
			}
			// ����jVex == vex
			else if (currentEdge->getJVex() == vex) {
				cout << "[" << vex << "](" << vexNode.getOrginData() << ") <==(" << currentEdge->getInfo() << ")==> [" << currentEdge->getIVex() << "](" << AMLlist[currentEdge->getIVex()].getOrginData() << ")" << endl;
				currentEdge = currentEdge->getJLink();
			}
			else {
				break;
			}
		}
		cout << endl;
		return;
	}
	// ���������������飬��ӡ���ж�������
	void printGraph() {
		for (int i = 0; i < vexnum; i++) {
			printVexInfo(i);
		}
		return;
	}	
	// ��ȡ����״̬
	int changeVexStatus(int vex) {
		if (vex >= vexnum || vex < 0) {
			// �±겻�Ϸ�����-1
			return -1;
		}
		bool ans = AMLlist[vex].getEnabled();
		if (ans) {
			AMLlist[vex].setEnabled(false);
		}
		else {
			AMLlist[vex].setEnabled(true);
		}
		return ans;
	}
	// �ͷ�dist�����path����Ŀռ�
	void freeDistAndPath(E**& dist, int**& path) {
		// �ж�dist��path�ǲ��Ƕ��ֵ�
		if (dist != nullptr || path != nullptr) {
			for (int i = 0; i < vexnum; ++i) {
				delete[] dist[i];
				dist[i] = nullptr;
				delete[] path[i];
				path[i] = nullptr;
			}
			delete[] dist;
			dist = nullptr;
			delete[] path;
			path = nullptr;
		}
		return;
	}
	// ʹ�ø��������㷨����dist�����path����
	void calculateFloyd(E** &dist, int** &path) {
		// INF��ʾ�����
		const E INF = numeric_limits<E>::max();
		// ����ռ�&��ʼ��
		dist = new E* [vexnum];
		path = new int* [vexnum];
		for (int i = 0; i < vexnum; i++) {
			dist[i] = new E[vexnum];
			path[i] = new int[vexnum];

			// ��ʼ��dist��pathΪĬ��ֵ��dist�ĶԽ���Ϊ0������Ϊ�����pathȫ����ʼ��Ϊ-1
			for (int j = 0; j < vexnum; j++) {
				if (i == j) {
					// �Լ����Լ���·��Ϊ0
					dist[i][j] = 0;
				}
				else {
					// ���Լ����Լ��������ȫ����ʼ��Ϊ�����
					dist[i][j] = INF;
				}
				// ·����ȫ��ʼ��Ϊ�����ڣ�-1��
				path[i][j] = -1;
			}
		}

		// �ڶ��γ�ʼ��dist��path�����ڽӶ��ر�ת��Ϊ�ڽӾ���
		for (int i = 0; i < vexnum; i++) {
			EdgeBox<E>* currentEdge = AMLlist[i].getFirstEdge();
			while (currentEdge != nullptr) {
				int j;
				// �ҵ��ߵ���һ�˶���j
				if (i == currentEdge->getIVex()) {
					j = currentEdge->getJVex();
				}
				else if (i == currentEdge->getJVex()) {
					j = currentEdge->getIVex();
				}
				else {
					break;
				}
				// ��������ǹرյģ����Ҳ����Լ����Լ�����Ϊ�Լ����Լ�֮ǰȨֵ�Ѿ�����Ϊ0�ˣ���
				// �ͰѴӶ�������͵������·��Ȩֵ������Ϊ�����
				if (!AMLlist[i].getEnabled() && i != j) {
					for (int k = 0; k < vexnum; k++) {
						// �����disabled��������򵽴�disabled���㶼����Ϊ�����
						dist[k][i] = INF;
						dist[i][k] = INF;
						path[k][i] = -1;
						path[i][k] = -1;
					}
				}
				if (!AMLlist[j].getEnabled() && i != j) {
					for (int k = 0; k < vexnum; k++) {
						// �����disabled��������򵽴�disabled���㶼����Ϊ�����
						dist[k][j] = INF;
						dist[j][k] = INF;
						path[k][j] = -1;
						path[j][k] = -1;
					}
				}
				// ������㲻�ǹرյģ���ô��������ֵ
				else {
					dist[i][j] = currentEdge->getInfo();
					path[i][j] = j;
				}
				// �����ƶ�����һ����
				if (i == currentEdge->getIVex()) {
					currentEdge = currentEdge->getILink();
				}
				else {
					currentEdge = currentEdge->getJLink();
				}
			}
		}

		// ʹ��Floyd�㷨����dist��path���飬��̬�滮˼��
		// k��ÿ�μ���Ҫ�����ĵ���±�
		for (int k = 0; k < vexnum; k++) {
			// �������k�ǹرյģ�������kΪ�м���·������
			if (!AMLlist[k].getEnabled()) {
				continue;
			}
			// ��i��j
			for (int i = 0; i < vexnum; i++) {
				for (int j = 0; j < vexnum; j++) {
					// �������ͨ�� ����k �ҵ���i��j��·�� ���� ��·��������и���
					if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
						// �������·����Ȩֵ
						dist[i][j] = dist[i][k] + dist[k][j];
						// ����i��j��·������k��
						// ע�����path��ʱ���Ǵ���һ��path�ң������Ǵ�dist����
						// https://www.bilibili.com/video/BV19k4y1Q7Gj?t=743.3
						path[i][j] = path[i][k];
					}
				}
			}
		}
		return;
	}
	// ��ӡ���·��
	MyVector<string> printFloydShortestPath(int srcVex, int destVex, E** const &dist, int** const &path) {
		if (srcVex < 0 || srcVex >= vexnum || destVex < 0 || destVex >= vexnum || srcVex == destVex) {
			return MyVector<string>();
		}
		// ������Ҵ�src��dest��Ԫ����-1����û��·��
		if (path[srcVex][destVex] == -1 or !getVexEnabled(srcVex)) {
			cout << "û�д� [" << AMLlist[srcVex].getOrginData() << "] �� [" << AMLlist[destVex].getOrginData() << "] ����̾���·�߹滮" << endl;
			if (voiceMode) {
				stringstream voiceString;
				voiceString << "û�д� [" << AMLlist[srcVex].getOrginData() << "] �� [" << AMLlist[destVex].getOrginData() << "] ����̾���·�߹滮";
				speakString(voiceString.str(), 6);
			}
			// ����һ���յ�MyVector
			return MyVector<string>();
		}
		// ͳ��·���и��վ����
		int totalStations = 0;
		// ��ӡ��ʾ��Ϣ
		cout << "====================================================================================================" << endl;
		cout << "�� [" << AMLlist[srcVex].getOrginData() << "] �� [" << AMLlist[destVex].getOrginData() << "] ����̾���·��Ϊ��" << endl;
		if (voiceMode) {
			stringstream voiceString;
			voiceString << "�� [" << AMLlist[srcVex].getOrginData() << "] �� [" << AMLlist[destVex].getOrginData() << "] ����̾���·������";
			speakString(voiceString.str(), 6);
		}
		// �м����x����¼��ǰ��������վ���±�
		int x = srcVex;
		// ����·��˳��ʢ��վ�����ֵ�����
		MyVector<string> stationNames;
		// ���ϱ���dist��path���飬ͬʱ��ӡ·��
		while (x != destVex) {
			cout << AMLlist[x].getOrginData() << " --(" << dist[x][path[x][destVex]] << "km)--> ";
			stationNames.push_back(AMLlist[x].getOrginData());
			x = path[x][destVex];
			totalStations++;
		}
		// �����һ��վ�����վ�����ֵ�����
		stationNames.push_back(AMLlist[destVex].getOrginData());
		// ��ӡ���һ��վ��
		cout << AMLlist[destVex].getOrginData();
		// ��ӡʣ�����ʾ��Ϣ
		cout << "\n====================================================================================================";
		cout << "\n�ܾ��룺" << dist[srcVex][destVex] << "km������վ������" << totalStations << "����Ʊ�ۣ�" << costCalculate(dist[srcVex][destVex]) << "Ԫ" << endl;
		if (voiceMode) {
			stringstream voiceString;
			voiceString << "�ܾ��룺" << dist[srcVex][destVex] << "km������վ������" << totalStations << "����Ʊ�ۣ�" << costCalculate(dist[srcVex][destVex]) << "Ԫ";
			speakString(voiceString.str(), 6);
		}
		return stationNames;
	}
	// BFS�㷨�������·��
	MyVector<int> bfsShortestPath(int startVex, int endVex) {
		// �����ʼ���㲻���ã�ֱ�ӷ��ؿյ�vector
		if (!getVexEnabled(startVex)) {
			return MyVector<int>();
		}
		// �����ʹ��Ķ�������
		MyVector<bool> visited(vexnum, false);
		// ��¼����㵽ÿ����������·����vexnum��������С��-1������Ԫ�صĳ�ʼֵ��
		MyVector<int> path(vexnum, -1);
		// �����ʶ���Ķ���
		ArrayQueue<int> q;
		// �����ʼ���㱻������
		visited[startVex] = true;
		// ����㶥�����
		q.EnQueue(startVex);
		// �����в�Ϊ��ʱ��ѭ��ִ������
		while (!q.QueueEmpty()) {
			// ȥ��ͷȻ�����
			int currentVex = q.getHeadElem();
			q.DeQueue();

			// �������Ŀ�궥�㣬�򹹽�·��������
			if (currentVex == endVex) {
				// �������������˳��洢��·���ϵ�վ���±�
				MyVector<int> result;
				int crawl = endVex;
				result.push_back(crawl);
				// ����
				while (path[crawl] != -1) {
					result.push_back(path[crawl]);
					crawl = path[crawl];
				}
				// ��ת·��
				reverse(result.begin(), result.end());
				return result;
			}
			// ������ǰ������������ڶ���
			VexNode<V, E>& vexNode = AMLlist[currentVex];
			EdgeBox<E>* currentEdge = vexNode.getFirstEdge();
			while (currentEdge != nullptr) {
				int nextVex = (currentVex == currentEdge->getIVex()) ? currentEdge->getJVex() : currentEdge->getIVex();
				// ������ڶ���δ���ʲ��ҿ��ã����Ϊ�ѷ��ʣ���¼·�������������
				if (!visited[nextVex] && getVexEnabled(nextVex)) {
					// ���Ϊ�ѷ���
					visited[nextVex] = true;
					// ��¼·��
					path[nextVex] = currentVex;
					// �����һ������
					q.EnQueue(nextVex);
				}
				// �ƶ�����һ����
				currentEdge = (currentVex == currentEdge->getIVex()) ? currentEdge->getILink() : currentEdge->getJLink();
			}
		}

		// ���û���ҵ�·�����򷵻ؿյ�vector
		return MyVector<int>();
	}
	MyVector<string> printBFSPath(int srcVex, int destVex) {
		// ����bfsShortestPath��ȡһ����·������վ���MyVector����
		MyVector<int> shortestPath = bfsShortestPath(srcVex, destVex);
		if (shortestPath.empty()) {
			cout << "û�д� [" << AMLlist[srcVex].getOrginData() << "] �� [" << AMLlist[destVex].getOrginData() << "] ������վ��·�߹滮" << endl;
			if (voiceMode) {
				stringstream voiceString;
				voiceString << "û�д� [" << AMLlist[srcVex].getOrginData() << "] �� [" << AMLlist[destVex].getOrginData() << "] ������վ��·�߹滮";
				speakString(voiceString.str(), 6);
			}
			return MyVector<string>();
		}
		else {
			int totalStations = 0;
			E totalDistance = 0;
			MyVector<string> stationNames;
			cout << "====================================================================================================" << endl;
			cout << "�� [" << AMLlist[srcVex].getOrginData() << "] �� [" << AMLlist[destVex].getOrginData() << "] ������վ��·��Ϊ��" << endl;
			if (voiceMode) {
				stringstream voiceString;
				voiceString << "�� [" << AMLlist[srcVex].getOrginData() << "] �� [" << AMLlist[destVex].getOrginData() << "] ������վ��·������";
				speakString(voiceString.str(), 6);
			}
			for (int i = 0; i < shortestPath.size(); i++) {
				if (i > 0) {
					cout << " --(" << getEdgeInfo(shortestPath[i - 1], shortestPath[i]) << "km)--> ";
					totalDistance += getEdgeInfo(shortestPath[i - 1], shortestPath[i]);
				}
				cout << AMLlist[shortestPath[i]].getOrginData();
				stationNames.push_back(AMLlist[shortestPath[i]].getOrginData());
				totalStations++;
			}
			cout << "\n====================================================================================================";
			cout << "\n�ܾ��룺" << totalDistance <<"km������վ������" << totalStations - 1<< "����Ʊ����ο����·���ļ۸�" << endl;
			if (voiceMode) {
				stringstream voiceString;
				voiceString << "�ܾ��룺" << totalDistance << "km������վ������" << totalStations - 1 << "����Ʊ����ο����·���ļ۸�";
				speakString(voiceString.str(), 6);
			}
			
			return stationNames;
		}
	}
	// DFS�ݹ�
	void dfsRecursion(int v, bool visited[], MyVector<V>& results) {
		// ��ǵ�ǰ�ڵ��ѷ���
		visited[v] = true;
		results.push_back(AMLlist[v].getOrginData()); // ���ڵ�������ӵ����������

		// Ȼ����ŴӶ���vѰ�һ�û�з��ʹ������ڶ���
		EdgeBox<E>* edge = AMLlist[v].getFirstEdge();
		while (edge != nullptr) {
			// ����ÿһ����v�����ӵĽڵ�w
			int w = (edge->getIVex() == v) ? edge->getJVex() : edge->getIVex();
			if (!visited[w]) {
				dfsRecursion(w, visited, results); // ��δ���ʵ�w���еݹ����
			}
			// ��ȡ��һ����
			edge = (edge->getIVex() == v) ? edge->getILink() : edge->getJLink();
		}
	}
	// DFS����
	void dfsTraverse() {
		MyVector<V> results;
		bool* visited = new bool[vexnum]; // �������ʱ������
		for (int i = 0; i < vexnum; ++i) {
			visited[i] = false; // ��ʼ�����ж���Ϊδ����
		}

		//����dfs�������Ӷ���0��ʼ����
		dfsRecursion(0, visited, results);

		// ��ӡDFS�������
		for (int i = 0; i < results.size(); i++) {
			if (i == 0) {
				cout << results[i];
			}
			else {
				cout << " --> " << results[i];
			}
		}
		cout << "\n�ܼƶ�������" << vexnum << "��" << endl;
		delete[] visited;
		return;
	}
	// ͨ��AMLGraph������վ��״̬��VexNode�е����ԣ�
	void setVexEnabled(int vex, bool enabled) {
		if (enabled) {
			cout << "������" << AMLlist[vex].getData() << "վ" << endl;
		}
		else {
			cout << "�ѽ���" << AMLlist[vex].getData() << "վ" << endl;
		}
		AMLlist[vex].setEnabled(enabled);
		return;
	}
	// ��ȡվ��״̬
	bool getVexEnabled(int vex) {
		if (vex >= vexnum || vex < 0) {
			return true;
		}
		return AMLlist[vex].getEnabled();
	}
	// �ж�վ���Ƿ�¶����¶��ѳ��
	bool isVexAlone(int vex) {
		if (vex >= vexnum || vex < 0) {
			return false;
		}
		// ���ز������ʽ �������ĵ�һ����ָ��Ϊ�գ���˵���ⶥ���ǹ¶���
		return (AMLlist[vex].getFirstEdge() == nullptr);
	}
	// �������һ��վ���±�
	int getRandomVexIndex() {
		return rand() % vexnum;
	}
};
