#include "stdafx.h"
#include "Map.h"
#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
bool MapData::runDist()
{
	for (int k = 0; k < Node_num; k++)
	for (int i = 0; i < Node_num; i++)
	for (int j = 0; j < Node_num; j++)
	{
		if (dist2[i*Node_num + j] > dist2[i + k*Node_num] + dist2[k*Node_num + j])
		{
			dist2[i*Node_num + j] = dist2[i + k*Node_num] + dist2[k*Node_num + j];
		}
	}
	return true;
}
bool MapData::LoadMap(string inputpath)
{
	setlocale(LC_ALL, "Chinese-simplified");
	fstream inputfile;
	string str;
	inputfile.open(inputpath, ios::in);
	if (!inputfile.good())
	{
		printf("load map failed!! \n");
		return false;
	}
		
	//getline(inputfile, str);
	//inputfile >> str;
	while (inputfile >> str)//算有幾個點
	{
		if (str == ";")
			break;
		Node_num++;
		
	}
	Node = new Nodes[Node_num];
	inputfile.close();
	inputfile.open(inputpath, ios::in);
	for (int i = 0; i < Node_num; i++)
	{
		string str;
		inputfile >> str;
		Node[i].setName(str);
	}
	inputfile >> str;
	// 讀取做標點
	for (int i = 0; i < Node_num; i++)
	{
		string strx, stry;
		inputfile >> strx;
		inputfile >> stry;
		Node[i].setNodes(Points(atof(strx.c_str()), atof(stry.c_str())), i);
	}
	getCent();
	/// 讀取距離矩陣
	for (int i = 0; i < Node_num*Node_num; i++)
	{
		inputfile >> str;
		if (str == "x")
		{
			dist.push_back(MaxDist);
		}
		else
		{
			dist.push_back(atof(str.c_str()));
		}
	}
	dist2 = dist;
	runDist();
	/*for (int i = 0; i < Node_num; i++)
	{
	for (int j = 0; j < Node_num; j++)
	{
	std::cout << dist[i*Node_num + j]<<"  ";
	}
	std::cout << std::endl;
	}*/
	
	return true;
}
void MapData::getCent()
{
	float min[3] = { 1e7, 1e7, 1e7 };
	float max[3] = { -1e7, -1e7, -1e7 };
	for (int i = 0; i < Node_num; i++)
	{
		//a
		if (Node[i].data.x < min[0])
			min[0] = Node[i].data.x;
		else if (Node[i].data.x > max[0])
			max[0] = Node[i].data.x;

		if (Node[i].data.y < min[1])
			min[1] = Node[i].data.y;
		else if (Node[i].data.y > max[1])
			max[1] = Node[i].data.y;

		//b
		if (Node[i].data.x < min[0])
			min[0] = Node[i].data.x;
		else if (Node[i].data.x > max[0])
			max[0] = Node[i].data.x;

		if (Node[i].data.y < min[1])
			min[1] = Node[i].data.y;
		else if (Node[i].data.y > max[1])
			max[1] = Node[i].data.y;

	}
	/*cent[0] = (min[0] + max[0]) / 2.0f;
	cent[1] = (min[1] + max[1]) / 2.0f;
	cent[2] = 0;*/

}
float getDistance(vector<float>D, int p1, int p2, int size)
{
	return D[p1*size + p2];
}
float MapData::setRoute(int p1, int p2, vector<float>D, vector<float>Dfinval, vector<int>&tempbuf)
{
	tempbuf.push_back(p1);
	int last = p1;
	int neiborbuffer[5] = { -1 };
	int tp1 = p1, tp2 = p2;
	float minF = MaxDist;
	float distance = 0;
	float tempd = 0;
	int tempind = -1;
	bool finish = 0;
	
	while (1)
	{
		minF = MaxDist;
		for (int i = 0; i < Node_num; i++)
		{
			if (i != tp1&&i != last && D[tp1*Node_num + i] < MaxDist)// 不能是上一個//不能是不連通的點
			{
				//for (int k = 0; k < tempbuf.size(); k++) // 不能是走過的節點
				//{
				//	if (i == tempbuf[k])
				//}
				//Do F = G + H // G = dist to next node, H = dist to end;
				if (i == tp2)
				{
					finish = true;
					tempind = tp2;
					break;
				}
				tempd = distance;
				float g = getDistance(D, tp1, i, Node_num);
				float H = getDistance(Dfinval, i, tp2, Node_num);
				tempd += getDistance(D, tp1, i, Node_num); // 原有distance 加上到分支個點距離 = F

				if (minF >= tempd + H) // G + H
				{
					minF = tempd + getDistance(Dfinval, i, tp2, Node_num);
					tempind = i;
					//break;
				}
			}
		}



		distance += tempd;
		last = tp1;
		tempbuf.push_back(tempind);
		tp1 = tempind;
		if (finish == true)
		{
			//cout << "dist = " << distance;
			break;
		}
	}

	return Dfinval[tempbuf.at(0)*Node_num+tempbuf.at(tempbuf.size()-1)];
}
MapData::MapData(string s) :filepath(s)
{
	Node_num = 0;
	LoadMap(s);
	
}