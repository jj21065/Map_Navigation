#include "stdafx.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
bool runDist();

void Nodes::showData()
{
	cout << "X:" << data.x << " Y:" << data.y << endl;
}
//bool Nodes::setRoute(int p1, int p2, int last,int size, vector<float>D, vector<float>Dfinval, vector<int>&tempbuf)
//{
//	tempbuf.push_back(p1);
//	int neiborbuffer[5] = { -1 };
//	int tp1 = p1, tp2 = p2;
//	float minF = MaxDist;
//	float distance = 0;
//	float tempd = 0;
//	int tempind = -1;
//	bool finish = 0;
//	while (1)
//	{
//		minF = MaxDist;
//		for (int i = 0; i < size; i++)
//		{
//			if (i != tp1&&i != last && D[tp1*size + i] < MaxDist)// 不能是上一個//不能是不連通的點
//			{
//					//for (int k = 0; k < tempbuf.size(); k++) // 不能是走過的節點
//					//{
//					//	if (i == tempbuf[k])
//					//}
//				//Do F = G + H // G = dist to next node, H = dist to end;
//				if (i == tp2)
//				{
//					finish = true;
//					tempind = tp2;
//					break;
//				}
//				tempd = distance;
//				float g = getDistance(D, tp1, i, size);
//				float H = getDistance(Dfinval, i, tp2, size);
//				tempd += getDistance(D, tp1, i, size); // 原有distance 加上到分支個點距離 = F
//				
//				if (minF >= tempd + H) // G + H
//				{
//					minF = tempd + getDistance(Dfinval, i, tp2, size);
//					tempind = i;
//					//break;
//				}
//			}
//		}
//
//		distance += tempd;
//		last = tp1;
//		tempbuf.push_back(tempind);
//		tp1 = tempind;
//		if (finish == true)
//		{
//			cout << "dist = " << distance;
//			break;
//		}
//			
//	}
//	return true;
//}
