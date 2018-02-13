#include <vector>
#define MaxDist 1e9
using namespace  std;
class Points
{
public:
	double x, y;
public:
	Points(){
		x = 0; y = 0;
	}
	Points(double xx, double yy)
	{
		x = xx; y = yy;
	}

};
//class BasicNode
//{
//
//public:
//	~BasicNode(){};
//	virtual void setNodes(Point& P, int i) = 0;
//};

class Nodes 
{
	//Nodes(double xi, double yi, char* n) :BasicNode(xi, yi, n)
	//{}
private:
	int ind;
	string name;

public:
	Points data;
	Nodes* branchNode[10];

	int treenodecount;
	Nodes(){
		treenodecount = 0;
		for (int i = 0; i < 10; i++)
		{
			branchNode[i] = nullptr;
		}

	};
	void setNodes(Points& P, int i)
	{
		data = P;
		ind = i;
	}
	string getName()
	{
		return name;
	}
	void setName(string n)
	{
		name = n;
	}
	void showData();

};