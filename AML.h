#pragma once
#include <iostream>
#include "MyVector.h"
#include "Queue.h"
#include "Subway.h"
using namespace std;

// 计算乘车价格
double costCalculate(double s) {
	double ans;
	// 根据北京地铁收费标准进行计算
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
		// ceil是取天花板（一种取整方式~），为了解决不满多少算多少的问题
		ans = 6.0 + ceil((s - 32) / 20.0);
	}
	return ans;
}

// 边（Edge）节点
// T这个自定义类型就是弧上数据的类型，也就是info的类型。如果边上要存权值，可以设置为int，double等等
template<typename E>
class EdgeBox {
private:
	int iVex, jVex;
	EdgeBox<E>* iLink, * jLink;  // iLink指向下一条依附于顶点iVex的边，同理jLink指向下一条依附于顶点jVex的边
	E info;
public:
	// 构造析构
	EdgeBox(int iVex, int jVex, E info, EdgeBox<E>* iLink = nullptr, EdgeBox<E>* jLink = nullptr) {
		this->iVex = iVex;
		this->jVex = jVex;
		this->info = info;
		this->iLink = iLink;
		this->jLink = jLink;
	}
	// get,set 函数
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

// 顶点节点
// T这个自定义类型就是顶点的数据的类型，也就是data的类型。
template<typename V, typename E>
class VexNode {
private:
	V data;
	EdgeBox<E>* firstEdge;
	bool enabled;
public:
	// 构造析构.
	VexNode() : firstEdge(nullptr), enabled(true) {}
	VexNode(V data, EdgeBox<E>* firstEdge = nullptr) {
		this->data = data;
		this->firstEdge = firstEdge;
		this->enabled = true;
	}
	// get,set 函数
	// 获取不含"[CLOSED]"的数据
	V getData() {
		// 如果是enabled == true，则本来就无"[CLOSED]"标签，直接返回
		if (enabled) {
			return data;
		}
		else {
			// 去除"[CLOSED]"
			string str = data, suffix = "[CLOSED]";
			// 如果"[CLOSED]"在最后面
			if (str.rfind(suffix) == (str.size() - suffix.size())) {
				// 删除 "[CLOSED]"
				str = str.substr(0, str.size() - suffix.size());
			}
			return str;
		}
	}
	// 获取原始数据
	V getOrginData() {
		return data;
	}
	// 获取顶点数组中的顶点的第一条指向的边
	EdgeBox<E>* getFirstEdge() {
		return firstEdge;
	}
	// 获取顶点状态
	bool getEnabled() {
		return enabled;
	}
	// 设置顶点的第一条指向的边
	void setFirstEdge(EdgeBox<E>* firstEdge) {
		this->firstEdge = firstEdge;
		return;
	}
	// 设置顶点数据
	void setData(V data) {
		this->data = data;
		return;
	}
	// 设置顶点状态
	void setEnabled(bool enabled) {
		this->enabled = enabled;
	}
};
// 邻接多重表
// V是顶点数据类型，A是边数据类型
template<typename V, typename E>
class AMLGraph {
private:
	VexNode<V, E>* AMLlist;
	int vexnum, edgenum, maxsize;
public:
	// 构造析构
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
	// get,set 函数
	int getVexnum() {
		return vexnum;
	}
	int getEdgenum() {
		return edgenum;
	}
	int getMaxsize() {
		return maxsize;
	}
	// 功能
	// 扩容
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
	// 减容
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
	// 添加顶点
	bool addVex(V data) {
		for (int i = 0; i < vexnum; i++) {
			if (AMLlist[i].getData() == data) {
				return false;
			}
		}
		if (vexnum >= maxsize) {
			if (expandMem()) {
				//cout << "顶点数组已自动扩容。" << endl;
			}
			else {
				cout << "自动扩容失败。顶点数组已满，无法继续添加！" << endl;
				return false;
			}
		}
		AMLlist[vexnum++].setData(data);
		return true;
	}
	// 添加边
	bool addEdge(int iVex, int jVex, E info) {
		if (iVex >= vexnum || jVex >= vexnum || jVex < 0 || iVex < 0 || iVex == jVex) {
			return false;
		}
		// 检查边是否已经存在
		EdgeBox<E>* currentEdge = AMLlist[iVex].getFirstEdge();
		while (currentEdge != nullptr) {
			if ((currentEdge->getIVex() == iVex && currentEdge->getJVex() == jVex) ||
				(currentEdge->getIVex() == jVex && currentEdge->getJVex() == iVex)) {
				return false;
			}
			// 根据当前边的起始顶点是 iVex 还是 jVex 选择下一条边
			if (currentEdge->getIVex() == iVex) {
				currentEdge = currentEdge->getILink();
			}
			else {
				currentEdge = currentEdge->getJLink();
			}
		}
		// 新建边
		EdgeBox<E>* newEdge = new EdgeBox<E>(iVex, jVex, info);
		// 更新 iVex 的边列表
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
		// 更新 jVex 的边列表
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
		edgenum++; // 边的数量增加
		return true;
	}
	// 删除边
	bool deleteEdge(int iVex, int jVex) {
		if (iVex >= vexnum || jVex >= vexnum || jVex < 0 || iVex < 0 || iVex == jVex) {
			return false;
		}
		// 定义一些指针
		EdgeBox<E>* toDeleteEdge = nullptr;
		EdgeBox<E>* currentEdge = nullptr;
		EdgeBox<E>* preEdge = nullptr;
		EdgeBox<E>* preIEdge = nullptr;
		EdgeBox<E>* preJEdge = nullptr;
		// 先从iVex顶点开始遍历
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
		// 再从jVex顶点开始遍历
		currentEdge = AMLlist[jVex].getFirstEdge();
		preEdge = nullptr;
		while (currentEdge != nullptr) {
			if (preEdge != nullptr) {
				// 这里需要再次判断preI或者J是不是不准确的，如果已经正确
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
		// 这里又是一个坑，还需要后面的或判读，如果preIEdge不合法，就直接设置顶点数组里的顶点了
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
	// 清空整个AML
	bool clearList() {
		while (deleteVex(0));
		return true;
	}
	// 删除顶点
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

		// 遍历所有边，判断ivex和jvex的值
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
			//cout << "顶点数组已自动减容。" << endl;
		}
		return true;
	}
	// 修改边数据
	bool updateEdgeInfo(int iVex, int jVex, E info) {
		if (iVex >= vexnum || jVex >= vexnum || jVex < 0 || iVex < 0) {
			return false;
		}
		EdgeBox<E>* currentEdge = AMLlist[iVex].getFirstEdge();
		while (currentEdge != nullptr) {
			// 无相图，无论iVex和jVex哪个在前都能检测出是否一样
			if ((currentEdge->getIVex() == iVex && currentEdge->getJVex() == jVex) || (currentEdge->getIVex() == jVex && currentEdge->getJVex() == iVex)) {
				// 这里找到边了
				currentEdge->setInfo(info);
				return true;
			}
			// 根据当前边的起始顶点是 iVex 还是 jVex 选择下一条边
			// 为什么要有这个，因为如果我找的是1->0，但是因为1的firstEdge已经指向从0创建的0->1了，所以加这个判断可以让接下来的路走向从1指向的节点
			if (currentEdge->getIVex() == iVex) {
				currentEdge = currentEdge->getILink();
			}
			else {
				currentEdge = currentEdge->getJLink();
			}
		}
		return false;
	}
	// 修改顶点数据
	bool updateVexData(int vex, V data) {
		if (vex >= vexnum || vex < 0) {
			return false;
		}
		AMLlist[vex].setData(data);
		return true;
	}
	// 根据数据查找顶点的下标
	int getVexIndex(V data) {
		for (int i = 0; i < vexnum; i++) {
			if (AMLlist[i].getData() == data) {
				return i;
			}
		}
		// 未找到返回-1
		return -1;
	}
	// 获取边的权值
	E getEdgeInfo(int iVex, int jVex) {
		if (iVex >= vexnum || jVex >= vexnum || jVex < 0 || iVex < 0) {
			return E();
		}
		EdgeBox<E>* currentEdge = AMLlist[iVex].getFirstEdge();
		while (currentEdge != nullptr) {
			// 无相图，无论iVex和jVex哪个在前都能检测出是否一样
			if ((currentEdge->getIVex() == iVex && currentEdge->getJVex() == jVex) || (currentEdge->getIVex() == jVex && currentEdge->getJVex() == iVex)) {
				// 这里找到边了
				return currentEdge->getInfo();
			}
			// 根据当前边的起始顶点是 iVex 还是 jVex 选择下一条边
			// 为什么要有这个，因为如果我找的是1->0，但是因为1的firstEdge已经指向从0创建的0->1了，所以加这个判断可以让接下来的路走向从1指向的节点
			if (currentEdge->getIVex() == iVex) {
				currentEdge = currentEdge->getILink();
			}
			else {
				currentEdge = currentEdge->getJLink();
			}
		}
		return E();
	}
	// 修改边指向
	bool updateEdgeDirect(int iVex, int jVex, int newIVex, int newJVex) {
		// 判断传入的tailVex和headVex是否合法
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
	// 打印指定顶点的数据
	void printVexInfo(int vex) {
		if (vex >= vexnum || vex < 0) {
			return;
		}
		// 顶点数据
		VexNode<V, E>& vexNode = AMLlist[vex];
		cout << "[" << vex << "] " << vexNode.getOrginData() << endl;

		// 边数据
		EdgeBox<E>* currentEdge = vexNode.getFirstEdge();
		while (currentEdge != nullptr) {
			// 判断当前边的起始顶点（iVex）是不是传入需要打印的顶点
			if (currentEdge->getIVex() == vex) {
				cout << "[" << vex << "](" << vexNode.getOrginData() << ") <==(" << currentEdge->getInfo() << ")==> [" << currentEdge->getJVex() << "](" << AMLlist[currentEdge->getJVex()].getOrginData() << ")" << endl;
				currentEdge = currentEdge->getILink();
			}
			// 否则jVex == vex
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
	// 遍历整个顶点数组，打印所有顶点数据
	void printGraph() {
		for (int i = 0; i < vexnum; i++) {
			printVexInfo(i);
		}
		return;
	}	
	// 获取顶点状态
	int changeVexStatus(int vex) {
		if (vex >= vexnum || vex < 0) {
			// 下标不合法返回-1
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
	// 释放dist数组和path数组的空间
	void freeDistAndPath(E**& dist, int**& path) {
		// 判断dist和path是不是二手的
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
	// 使用弗洛伊德算法计算dist数组和path数组
	void calculateFloyd(E** &dist, int** &path) {
		// INF表示无穷大
		const E INF = numeric_limits<E>::max();
		// 分配空间&初始化
		dist = new E* [vexnum];
		path = new int* [vexnum];
		for (int i = 0; i < vexnum; i++) {
			dist[i] = new E[vexnum];
			path[i] = new int[vexnum];

			// 初始化dist和path为默认值，dist的对角线为0，其余为无穷大；path全部初始化为-1
			for (int j = 0; j < vexnum; j++) {
				if (i == j) {
					// 自己到自己的路径为0
					dist[i][j] = 0;
				}
				else {
					// 非自己到自己的情况先全部初始化为无穷大
					dist[i][j] = INF;
				}
				// 路径先全初始化为不存在（-1）
				path[i][j] = -1;
			}
		}

		// 第二次初始化dist和path，把邻接多重表转化为邻接矩阵
		for (int i = 0; i < vexnum; i++) {
			EdgeBox<E>* currentEdge = AMLlist[i].getFirstEdge();
			while (currentEdge != nullptr) {
				int j;
				// 找到边的另一端顶点j
				if (i == currentEdge->getIVex()) {
					j = currentEdge->getJVex();
				}
				else if (i == currentEdge->getJVex()) {
					j = currentEdge->getIVex();
				}
				else {
					break;
				}
				// 如果顶点是关闭的，并且不是自己到自己（因为自己到自己之前权值已经设置为0了），
				// 就把从顶点出发和到顶点的路线权值都设置为无穷大
				if (!AMLlist[i].getEnabled() && i != j) {
					for (int k = 0; k < vexnum; k++) {
						// 假设从disabled顶点出发或到达disabled顶点都设置为无穷大
						dist[k][i] = INF;
						dist[i][k] = INF;
						path[k][i] = -1;
						path[i][k] = -1;
					}
				}
				if (!AMLlist[j].getEnabled() && i != j) {
					for (int k = 0; k < vexnum; k++) {
						// 假设从disabled顶点出发或到达disabled顶点都设置为无穷大
						dist[k][j] = INF;
						dist[j][k] = INF;
						path[k][j] = -1;
						path[j][k] = -1;
					}
				}
				// 如果顶点不是关闭的，那么就正常赋值
				else {
					dist[i][j] = currentEdge->getInfo();
					path[i][j] = j;
				}
				// 不断移动到下一条边
				if (i == currentEdge->getIVex()) {
					currentEdge = currentEdge->getILink();
				}
				else {
					currentEdge = currentEdge->getJLink();
				}
			}
		}

		// 使用Floyd算法更新dist和path数组，动态规划思想
		// k是每次假设要经过的点的下标
		for (int k = 0; k < vexnum; k++) {
			// 如果顶点k是关闭的，跳过以k为中间点的路径更新
			if (!AMLlist[k].getEnabled()) {
				continue;
			}
			// 从i到j
			for (int i = 0; i < vexnum; i++) {
				for (int j = 0; j < vexnum; j++) {
					// 如果可以通过 顶点k 找到比i到j的路径 更短 的路径，则进行更新
					if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
						// 更新最短路径的权值
						dist[i][j] = dist[i][k] + dist[k][j];
						// 更新i到j的路径经过k点
						// 注意更新path的时候是从上一个path找，而不是从dist里找
						// https://www.bilibili.com/video/BV19k4y1Q7Gj?t=743.3
						path[i][j] = path[i][k];
					}
				}
			}
		}
		return;
	}
	// 打印最短路径
	MyVector<string> printFloydShortestPath(int srcVex, int destVex, E** const &dist, int** const &path) {
		if (srcVex < 0 || srcVex >= vexnum || destVex < 0 || destVex >= vexnum || srcVex == destVex) {
			return MyVector<string>();
		}
		// 如果查找从src到dest的元素是-1，则没有路径
		if (path[srcVex][destVex] == -1 or !getVexEnabled(srcVex)) {
			cout << "没有从 [" << AMLlist[srcVex].getOrginData() << "] 到 [" << AMLlist[destVex].getOrginData() << "] 的最短距离路线规划" << endl;
			if (voiceMode) {
				stringstream voiceString;
				voiceString << "没有从 [" << AMLlist[srcVex].getOrginData() << "] 到 [" << AMLlist[destVex].getOrginData() << "] 的最短距离路线规划";
				speakString(voiceString.str(), 6);
			}
			// 返回一个空的MyVector
			return MyVector<string>();
		}
		// 统计路线中搞得站点数
		int totalStations = 0;
		// 打印提示信息
		cout << "====================================================================================================" << endl;
		cout << "从 [" << AMLlist[srcVex].getOrginData() << "] 到 [" << AMLlist[destVex].getOrginData() << "] 的最短距离路径为：" << endl;
		if (voiceMode) {
			stringstream voiceString;
			voiceString << "从 [" << AMLlist[srcVex].getOrginData() << "] 到 [" << AMLlist[destVex].getOrginData() << "] 的最短距离路径如下";
			speakString(voiceString.str(), 6);
		}
		// 中间变量x，记录当前遍历到的站点下标
		int x = srcVex;
		// 按照路线顺序盛放站点名字的容器
		MyVector<string> stationNames;
		// 不断遍历dist和path数组，同时打印路径
		while (x != destVex) {
			cout << AMLlist[x].getOrginData() << " --(" << dist[x][path[x][destVex]] << "km)--> ";
			stationNames.push_back(AMLlist[x].getOrginData());
			x = path[x][destVex];
			totalStations++;
		}
		// 把最后一个站点放入站点名字的容器
		stationNames.push_back(AMLlist[destVex].getOrginData());
		// 打印最后一个站点
		cout << AMLlist[destVex].getOrginData();
		// 打印剩余的提示信息
		cout << "\n====================================================================================================";
		cout << "\n总距离：" << dist[srcVex][destVex] << "km，经过站点数：" << totalStations << "个，票价：" << costCalculate(dist[srcVex][destVex]) << "元" << endl;
		if (voiceMode) {
			stringstream voiceString;
			voiceString << "总距离：" << dist[srcVex][destVex] << "km，经过站点数：" << totalStations << "个，票价：" << costCalculate(dist[srcVex][destVex]) << "元";
			speakString(voiceString.str(), 6);
		}
		return stationNames;
	}
	// BFS算法查找最短路径
	MyVector<int> bfsShortestPath(int startVex, int endVex) {
		// 如果起始顶点不可用，直接返回空的vector
		if (!getVexEnabled(startVex)) {
			return MyVector<int>();
		}
		// 被访问过的顶点容器
		MyVector<bool> visited(vexnum, false);
		// 记录从起点到每个顶点的最短路径（vexnum是容器大小，-1是所有元素的初始值）
		MyVector<int> path(vexnum, -1);
		// 待访问顶点的队列
		ArrayQueue<int> q;
		// 标记起始顶点被访问了
		visited[startVex] = true;
		// 将起点顶点入队
		q.EnQueue(startVex);
		// 当队列不为空时，循环执行搜索
		while (!q.QueueEmpty()) {
			// 去队头然后出队
			int currentVex = q.getHeadElem();
			q.DeQueue();

			// 如果到达目标顶点，则构建路径并返回
			if (currentVex == endVex) {
				// 结果容器，按照顺序存储了路径上的站点下标
				MyVector<int> result;
				int crawl = endVex;
				result.push_back(crawl);
				// 回溯
				while (path[crawl] != -1) {
					result.push_back(path[crawl]);
					crawl = path[crawl];
				}
				// 反转路径
				reverse(result.begin(), result.end());
				return result;
			}
			// 遍历当前顶点的所有相邻顶点
			VexNode<V, E>& vexNode = AMLlist[currentVex];
			EdgeBox<E>* currentEdge = vexNode.getFirstEdge();
			while (currentEdge != nullptr) {
				int nextVex = (currentVex == currentEdge->getIVex()) ? currentEdge->getJVex() : currentEdge->getIVex();
				// 如果相邻顶点未访问并且可用，标记为已访问，记录路径，并将它入队
				if (!visited[nextVex] && getVexEnabled(nextVex)) {
					// 标记为已访问
					visited[nextVex] = true;
					// 记录路径
					path[nextVex] = currentVex;
					// 入队下一个顶点
					q.EnQueue(nextVex);
				}
				// 移动到下一条边
				currentEdge = (currentVex == currentEdge->getIVex()) ? currentEdge->getILink() : currentEdge->getJLink();
			}
		}

		// 如果没有找到路径，则返回空的vector
		return MyVector<int>();
	}
	MyVector<string> printBFSPath(int srcVex, int destVex) {
		// 调用bfsShortestPath获取一个线路上所有站点的MyVector容器
		MyVector<int> shortestPath = bfsShortestPath(srcVex, destVex);
		if (shortestPath.empty()) {
			cout << "没有从 [" << AMLlist[srcVex].getOrginData() << "] 到 [" << AMLlist[destVex].getOrginData() << "] 的最少站点路线规划" << endl;
			if (voiceMode) {
				stringstream voiceString;
				voiceString << "没有从 [" << AMLlist[srcVex].getOrginData() << "] 到 [" << AMLlist[destVex].getOrginData() << "] 的最少站点路线规划";
				speakString(voiceString.str(), 6);
			}
			return MyVector<string>();
		}
		else {
			int totalStations = 0;
			E totalDistance = 0;
			MyVector<string> stationNames;
			cout << "====================================================================================================" << endl;
			cout << "从 [" << AMLlist[srcVex].getOrginData() << "] 到 [" << AMLlist[destVex].getOrginData() << "] 的最少站点路径为：" << endl;
			if (voiceMode) {
				stringstream voiceString;
				voiceString << "从 [" << AMLlist[srcVex].getOrginData() << "] 到 [" << AMLlist[destVex].getOrginData() << "] 的最少站点路径如下";
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
			cout << "\n总距离：" << totalDistance <<"km，经过站点数：" << totalStations - 1<< "个，票价请参考最短路径的价格。" << endl;
			if (voiceMode) {
				stringstream voiceString;
				voiceString << "总距离：" << totalDistance << "km，经过站点数：" << totalStations - 1 << "个，票价请参考最短路径的价格。";
				speakString(voiceString.str(), 6);
			}
			
			return stationNames;
		}
	}
	// DFS递归
	void dfsRecursion(int v, bool visited[], MyVector<V>& results) {
		// 标记当前节点已访问
		visited[v] = true;
		results.push_back(AMLlist[v].getOrginData()); // 将节点数据添加到结果向量中

		// 然后接着从顶点v寻找还没有访问过的相邻顶点
		EdgeBox<E>* edge = AMLlist[v].getFirstEdge();
		while (edge != nullptr) {
			// 访问每一个与v相连接的节点w
			int w = (edge->getIVex() == v) ? edge->getJVex() : edge->getIVex();
			if (!visited[w]) {
				dfsRecursion(w, visited, results); // 对未访问的w进行递归遍历
			}
			// 获取下一条边
			edge = (edge->getIVex() == v) ? edge->getILink() : edge->getJLink();
		}
	}
	// DFS遍历
	void dfsTraverse() {
		MyVector<V> results;
		bool* visited = new bool[vexnum]; // 创建访问标记数组
		for (int i = 0; i < vexnum; ++i) {
			visited[i] = false; // 初始化所有顶点为未访问
		}

		//调用dfs函数，从顶点0开始遍历
		dfsRecursion(0, visited, results);

		// 打印DFS遍历结果
		for (int i = 0; i < results.size(); i++) {
			if (i == 0) {
				cout << results[i];
			}
			else {
				cout << " --> " << results[i];
			}
		}
		cout << "\n总计顶点数：" << vexnum << "个" << endl;
		delete[] visited;
		return;
	}
	// 通过AMLGraph类设置站点状态（VexNode中的属性）
	void setVexEnabled(int vex, bool enabled) {
		if (enabled) {
			cout << "已启用" << AMLlist[vex].getData() << "站" << endl;
		}
		else {
			cout << "已禁用" << AMLlist[vex].getData() << "站" << endl;
		}
		AMLlist[vex].setEnabled(enabled);
		return;
	}
	// 获取站点状态
	bool getVexEnabled(int vex) {
		if (vex >= vexnum || vex < 0) {
			return true;
		}
		return AMLlist[vex].getEnabled();
	}
	// 判断站点是否孤独，孤独已成瘾
	bool isVexAlone(int vex) {
		if (vex >= vexnum || vex < 0) {
			return false;
		}
		// 返回布尔表达式 如果顶点的第一个边指针为空，则说明这顶点是孤独的
		return (AMLlist[vex].getFirstEdge() == nullptr);
	}
	// 随机生成一个站点下标
	int getRandomVexIndex() {
		return rand() % vexnum;
	}
};
