#ifndef LOADINGSTL_H
#define LOADINGSTL_H

#include <windows.h>
#include "Input.h"
#include "GLee.h"
#include <gl/glu.h> 
#include <gl/glut.h> 
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "glee.lib" )
#include <string>

 class loadingSTL
{
public:
	loadingSTL();
	~loadingSTL();
	void InitVBO();
	float * Calcent();//�p�⤤�I
	void Draw();//�e�ҫ�
	void SettingVBO(System::String^ s);//�i��VBO�]�w
	void MarshalNetToStdString(System::String^ s);//Ū�J�r��
	float *cent;
	

public:
	unsigned int VBO_index[2];
	float *VBOv, *VBOn;

	int nTriangles = 0;
	STriangle *triArray;
	std::string os;
	
};


#endif // !LOADINGSTL_H
