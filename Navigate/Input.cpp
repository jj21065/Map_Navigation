#include "stdafx.h"
#include "Input.h"
#include <fstream>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;


STriangle * LoadStlASCII(const char * pPathname, int & nTriangles)
{
	STriangle * triArray = (STriangle *)0;

	try
	{
		if (!pPathname)
			throw new exception("�޼ƿ��~");

		ifstream fin;
		fin.open(pPathname, ios::in | ios::binary);
		if (!fin.good())
			throw new exception("�ɦW�θ��|���~! �L�k�}���ɮ�!");
		const int strLen = 256;
		char str[strLen];

		//���Y: solid name
		fin.getline(str, strLen);
		if (!fin.good())
			throw new exception("�L���e");
		if (strncmp("solid", str, strlen("solid")) != 0)
			throw new exception("�榡���X(�Lsolid)");//bad STL file

		std::vector<STriangle> triLst;
		//�T����
		while (!fin.eof())
		{
			STriangle tri;

			//facet normal nx ny nz
			fin >> str;//facet, but it also maybe "endsolid"
			//throw new exception(str);

			if (strncmp("endsolid", str, strlen("endsolid")) == 0)
				break;//over

			fin >> str;//normal
			if (!fin.good())
			{
				if (strncmp("\n", str, strlen("\n")) == 0)
					break;
				else
					throw new exception("�榡���X(�Lnormal)");
			}

			fin >> tri.n[0] >> tri.n[1] >> tri.n[2];
			if (!fin.good())
				throw new exception("�k�V�q�ƭ�Ū�����~");

			//outer loop
			fin >> str;//outer
			if (!fin.good())
				throw new exception("�榡���X(�Louter)");
			fin >> str;//loop
			if (!fin.good())
				throw new exception("�榡���X(�Lloop)");

			//vertex v1x v1y v1z
			fin >> str;//vertex
			if (!fin.good())
				throw new exception("�榡���X(�Lvertex)");
			fin >> tri.a[0] >> tri.a[1] >> tri.a[2];
			if (!fin.good())
				throw new exception("vertex 1 �ƭ�Ū�����~");

			//vertex v2x v2y v2z
			fin >> str;//vertex
			if (!fin.good())
				throw new exception("�榡���X(�Lvertex)");
			fin >> tri.b[0] >> tri.b[1] >> tri.b[2];
			if (!fin.good())
				throw new exception("vertex 2 �ƭ�Ū�����~");
			float vb[3] = { tri.b[0] - tri.a[0], tri.b[1] - tri.a[1], tri.b[2] - tri.a[2] };

			//vertex v3x v3y v3z
			fin >> str;//vertex
			if (!fin.good())
				throw new exception("�榡���X(�Lvertex)");
			fin >> tri.c[0] >> tri.c[1] >> tri.c[2];
			if (!fin.good())
				throw new exception("vertex 3 �ƭ�Ū�����~");
			float vc[3] = { tri.c[0] - tri.a[0], tri.c[1] - tri.a[1], tri.c[2] - tri.a[2] };

			//re-compute normal
			float normal[3] = { vb[1] * vc[2] - vb[2] * vc[1], vb[2] * vc[0] - vb[0] * vc[2], vb[0] * vc[1] - vb[1] * vc[0] };
			float len = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
			if (len > 0)
			{
				normal[0] /= len;
				normal[1] /= len;
				normal[2] /= len;
			}
			tri.n[0] = normal[0];
			tri.n[1] = normal[1];
			tri.n[2] = normal[2];

			triLst.push_back(tri);

			//endloop
			fin >> str;//endloop
			if (!fin.good())
				throw new exception("�榡���X(�Lendloop)");

			//endfacet
			fin >> str;//endfacet
			if (!fin.good())
				throw new exception("�榡���X(�Lendfacet)");



		}
		fin.clear();
		fin.close();

		nTriangles = triLst.size();
		if (nTriangles > 0)
		{
			triArray = new STriangle[nTriangles];
			for (int i = 0; i < nTriangles; i++)
			{
				triArray[i] = triLst[i];
			}
			triLst.clear();
		}
		return triArray;
	}
	catch (exception * e)
	{
		cout << "Ū�ɥ���!\n";
		cout << "���~�y�z�G" << e->what() << endl;
		//		exit(0);
		nTriangles = 0;
		return (STriangle *)0;
	}

}

STriangle * LoadStlBinary(const char * pPathname, int & nTriangles)
{
	STriangle * triArray = (STriangle *)0;

	try
	{
		if (!pPathname)
			throw new exception("�޼ƿ��~");

		ifstream fin;
		fin.open(pPathname, ios::in | ios::binary);
		if (!fin.good())
			throw new exception("�ɦW�θ��|���~! �L�k�}���ɮ�!");

		const unsigned int tmpLen = 80;
		char tmpBuff[tmpLen];

		//read Header
		fin.read(tmpBuff, tmpLen);
		if (!fin.good())
			throw new exception("�榡���X(header���~)");
		//headInfo = new char[tmpLen];
		//strncpy(headInfo, tmpBuff, tmpLen);

		//how many triangles ?
		fin.read((char *)&nTriangles, 4);//unsigned long, must be 4 bytes
		if (!fin.good())
			throw new exception("�榡���X(�T������ƿ��~)");

		//allocate array memory
		if (nTriangles > 0)
		{
			triArray = new STriangle[nTriangles];
		}

		//read triangles
		std::vector<STriangle> triLst;
		fin.seekg(84, ios::beg);
		for (int i = 0; i < nTriangles; i++)
		{
			fin.read(tmpBuff, 50);
			if (!fin.good())
				throw new exception("�榡���X");
			int gc = fin.gcount();
			if (gc < 50)
				throw;//��Ƥ����A�i�H�t�~�B�z�A���ܩ󧹥�����

			triArray[i].a[0] = *(float *)(tmpBuff + 12);
			triArray[i].a[1] = *(float *)(tmpBuff + 16);
			triArray[i].a[2] = *(float *)(tmpBuff + 20);

			triArray[i].b[0] = *(float *)(tmpBuff + 24);
			triArray[i].b[1] = *(float *)(tmpBuff + 28);
			triArray[i].b[2] = *(float *)(tmpBuff + 32);

			triArray[i].c[0] = *(float *)(tmpBuff + 36);
			triArray[i].c[1] = *(float *)(tmpBuff + 40);
			triArray[i].c[2] = *(float *)(tmpBuff + 44);

			//re-compute normal		
			float vb[3] = { triArray[i].b[0] - triArray[i].a[0], triArray[i].b[1] - triArray[i].a[1], triArray[i].b[2] - triArray[i].a[2] };
			float vc[3] = { triArray[i].c[0] - triArray[i].a[0], triArray[i].c[1] - triArray[i].a[1], triArray[i].c[2] - triArray[i].a[2] };
			float normal[3] = { vb[1] * vc[2] - vb[2] * vc[1], vb[2] * vc[0] - vb[0] * vc[2], vb[0] * vc[1] - vb[1] * vc[0] };
			float len = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
			if (len > 0)
			{
				normal[0] /= len;
				normal[1] /= len;
				normal[2] /= len;
			}
			triArray[i].n[0] = normal[0];
			triArray[i].n[1] = normal[1];
			triArray[i].n[2] = normal[2];

			//==================================
			//ignore the Attribute byte count
			//= *(float *)(tmpBuff+48);
			//= *(float *)(tmpBuff+49);
			//==================================
		}
		fin.clear();
		fin.close();
	}
	catch (exception * e)
	{
		//cout << "Ū�ɥ���!\n";
		//cout << "���~�y�z�G" << e->what() << endl;
		//		exit(0);
		nTriangles = 0;
		return (STriangle *)0;
	}

	return triArray;
}


void gotoxy(int x, int y)  //cursor an gewuenschte position auf dem bildschirm setzen
{
	CONSOLE_SCREEN_BUFFER_INFO        csbiInfo;                            //variablendklaration
	HANDLE    hConsoleOut;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	csbiInfo.dwCursorPosition.X = x;                                    //cursorposition X koordinate festlegen
	csbiInfo.dwCursorPosition.Y = y;                                    //cursorposition Y koordinate festlegen
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);    //den cursor an die festgelegte koordinate setzen
}
