#include "stdafx.h"
#include "loadingSTL.h"

loadingSTL::loadingSTL()
{
}

loadingSTL::~loadingSTL()
{
}

void loadingSTL::SettingVBO(System::String^ s)
{
	MarshalNetToStdString(s);
	triArray = LoadStlBinary(os.c_str(), nTriangles);
	InitVBO();
}

void loadingSTL::InitVBO()
{
	cent = Calcent();
	VBOv = new float[nTriangles * 9];
	VBOn = new float[nTriangles * 9];
	int i;
	
	for (i = 0; i < nTriangles; i++)
	{

		VBOv[i * 9 + 0] = triArray[i].a[0];
		VBOv[i * 9 + 1] = triArray[i].a[1];
		VBOv[i * 9 + 2] = triArray[i].a[2];

		VBOv[i * 9 + 3] = triArray[i].b[0];
		VBOv[i * 9 + 4] = triArray[i].b[1];
		VBOv[i * 9 + 5] = triArray[i].b[2];

		VBOv[i * 9 + 6] = triArray[i].c[0];
		VBOv[i * 9 + 7] = triArray[i].c[1];
		VBOv[i * 9 + 8] = triArray[i].c[2];

		VBOn[i * 9 + 0] = triArray[i].n[0];
		VBOn[i * 9 + 1] = triArray[i].n[1];
		VBOn[i * 9 + 2] = triArray[i].n[2];

		VBOn[i * 9 + 3] = triArray[i].n[0];
		VBOn[i * 9 + 4] = triArray[i].n[1];
		VBOn[i * 9 + 5] = triArray[i].n[2];

		VBOn[i * 9 + 6] = triArray[i].n[0];
		VBOn[i * 9 + 7] = triArray[i].n[1];
		VBOn[i * 9 + 8] = triArray[i].n[2];
	}

	glGenBuffers(2, VBO_index);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles * 9 * sizeof(float), VBOv, GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles * 9 * sizeof(float), VBOn, GL_STATIC_DRAW);

}

float * loadingSTL::Calcent()
{
	if (triArray)
	{
		cent = new float[3];
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles; i++)
		{
			//a
			if (triArray[i].a[0] < min[0])
				min[0] = triArray[i].a[0];
			else if (triArray[i].a[0] > max[0])
				max[0] = triArray[i].a[0];

			if (triArray[i].a[1] < min[1])
				min[1] = triArray[i].a[1];
			else if (triArray[i].a[1] > max[1])
				max[1] = triArray[i].a[1];

			if (triArray[i].a[2] < min[2])
				min[2] = triArray[i].a[2];
			else if (triArray[i].a[2] > max[2])
				max[2] = triArray[i].a[2];

			//b
			if (triArray[i].b[0] < min[0])
				min[0] = triArray[i].b[0];
			else if (triArray[i].b[0] > max[0])
				max[0] = triArray[i].b[0];

			if (triArray[i].b[1] < min[1])
				min[1] = triArray[i].b[1];
			else if (triArray[i].b[1] > max[1])
				max[1] = triArray[i].b[1];

			if (triArray[i].b[2] < min[2])
				min[2] = triArray[i].b[2];
			else if (triArray[i].b[2] > max[2])
				max[2] = triArray[i].b[2];

			//c
			if (triArray[i].c[0] < min[0])
				min[0] = triArray[i].c[0];
			else if (triArray[i].c[0] > max[0])
				max[0] = triArray[i].c[0];

			if (triArray[i].c[1] < min[1])
				min[1] = triArray[i].c[1];
			else if (triArray[i].c[1] > max[1])
				max[1] = triArray[i].c[1];

			if (triArray[i].c[2] < min[2])
				min[2] = triArray[i].c[2];
			else if (triArray[i].c[2] > max[2])
				max[2] = triArray[i].c[2];
		}
		cent[0] = (min[0] + max[0]) / 2.0f;
		cent[1] = (min[1] + max[1]) / 2.0f;
		cent[2] = (min[2] + max[2]) / 2.0f;

		/*std::cout << "\n成功匯入STL檔!!\n"
		<< "此模型共有:" << nTriangles << "個三角網格\n"
		<< "邊界盒的中心為( " << cent[0] << " , " << cent[1] << " , " << cent[2] << " )\n";*/
		return cent;
	}
	return nullptr;
}

void loadingSTL::Draw()
{
	//以VBO畫三角網格
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Vertex
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, nTriangles * 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glEnd();

}

void loadingSTL::MarshalNetToStdString(System::String^ s)
{
	using System::IntPtr;
	using System::Runtime::InteropServices::Marshal;

	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}