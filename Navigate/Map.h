#include "Node.h"
#include <vector>
using namespace std;

//// a Map object
class  MapData
{
public:
	int Node_num; /// ���a���I�ƶq
	string filepath;  // Ū���l�ϸ��|
	Nodes *Node;    /// �O���a�ϸ`�I���
	vector<float> dist;    // �򥻶Z���x�}
	vector<float> dist2;   // floyd�̵u�Z���x�}
	
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