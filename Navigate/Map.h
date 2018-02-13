#include "Node.h"
#include <vector>
using namespace std;

//// a Map object
class  MapData
{
public:
	int Node_num; /// 此地圖點數量
	string filepath;  // 讀取締圖路徑
	Nodes *Node;    /// 記錄地圖節點資料
	vector<float> dist;    // 基本距離矩陣
	vector<float> dist2;   // floyd最短距離矩陣
	
	//MapData(){};
	MapData(string s);
	~MapData(){};

public:
	bool runDist();
	bool LoadMap(string inputpath);
	void getCent();
	float setRoute(int p1, int p2, vector<float>D, vector<float>Dfinval, vector<int>&tempbuf);
};

// MapData::~ MapData()
//{
//	 /* if (Node != nullptr)
//		  delete[]Node;*/
//}