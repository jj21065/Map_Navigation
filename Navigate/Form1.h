#pragma once
#include <windows.h>
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "User32.lib")
#include "glee.h"
#include "GLee.h"
#include <gl/glu.h> 
#include <gl/glut.h> 
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "glee.lib" )
#include <iostream>
#include <fstream>
#include "loadingSTL.h"
#include "glPrintf.h"
#include "Map.h"
#include <iterator>
#define HALF_WAY_NODES 5
static HWND m_hWnd;
static HDC  m_hDC;
static HGLRC m_hRC;
float m_srtMatrix[9];
GLdouble posX[8], posY[8], posZ[8];  //for selection
GLdouble cent[3];
int mousecount;
int NODES_NUM;
vector<float> dist;
vector<float> dist2;
vector<int>tempbuf;
vector<int>temphalfway;
double modelview[16] = { 0 };
double projection[16] = { 0 };
GLint viewport[4] = { 0 };
int  animateSpeed = 10;


enum{
	SET_NORMAL_MAP,
	SET_3D_MAP
};
enum{
	NORNAL_SELECT_MODE,
	HALFWAY_SELECT_MODE
};
	
	
namespace armtest {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO::Ports;

	[DllImport("opengl32.dll")]
	extern HDC wglSwapBuffers(HDC hdc);
	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
	
		float duu, du, oldmy, oldmx; //
		float wX, Wy; // for translatef the world co
		float c, PI;
		float zoom;
		int start, end;
		GLdouble *winX, *winY, *winZ;
		int MapState;
		int select_state;
		bool textFlag;
		float totalDist;
	public:
		loadingSTL* campus1, *campus1_buildings, *position, *destination, *model5, *model6, *model7;
		//Nodes *Node;
		MapData *map1;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::TextBox^  EndTextBox;

	private: System::Windows::Forms::TextBox^  BeginTextBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  set3DMap;
	private: System::Windows::Forms::Button^  setMap;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::Label^  WalkTimeLabel;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  TextONOFF;
	private: System::Windows::Forms::Label^  LockLabel;
	private: System::Windows::Forms::Button^  SetHalfWayButton;




	private: System::Windows::Forms::Label^  DistLabel;



	public:
		//		Nodes* nodeTree = new Nodes();
	public:
		Form1(void)
		{

			InitializeComponent();
			/*this->WindowState = FormWindowState::Maximized;
			this->TopMost = true;*/

			OpenGLInit();
			//splitContainer1->SplitterDistance = groupBox1->Width ;
			zoom = 0.1;
			duu = 0; du = 0, oldmy = -1, oldmx = -1; wX = 0; Wy = 0;
			PI = 3.14195;
			c = PI / 180.0f; //
			mousecount = 0;

			campus1 = new loadingSTL;
			campus1_buildings = new loadingSTL;
			position = new loadingSTL;
			destination = new loadingSTL;
			model5 = new loadingSTL;
			model6 = new loadingSTL;
			model7 = new loadingSTL;
			map1 = new MapData(".\\NodeData\\outputnew2.txt");
			campus1->SettingVBO(".\\Models\\campus1.STL");
			campus1_buildings->SettingVBO(".\\Models\\campus1_buildings.STL");
			position->SettingVBO(".\\Models\\Position.STL");
			destination->SettingVBO(".\\Models\\Position.STL");

			start = -1; end = -1;
			textFlag = true;
			MapState = SET_NORMAL_MAP;
			select_state = NORNAL_SELECT_MODE;
			winX = new GLdouble[map1->Node_num];
			winY = new GLdouble[map1->Node_num];
			winZ = new GLdouble[map1->Node_num];

			DrawScene();
		}
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			delete campus1; delete campus1_buildings; delete position; delete destination; delete model5; delete model6; delete model7;
			delete[]winX; delete[]winY; delete[]winZ;
			if (components)
			{
				delete components;
			}
		}
	protected:
	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->set3DMap = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->setMap = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->SetHalfWayButton = (gcnew System::Windows::Forms::Button());
			this->LockLabel = (gcnew System::Windows::Forms::Label());
			this->TextONOFF = (gcnew System::Windows::Forms::Button());
			this->WalkTimeLabel = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->BeginTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->DistLabel = (gcnew System::Windows::Forms::Label());
			this->EndTextBox = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->BackColor = System::Drawing::Color::SteelBlue;
			this->splitContainer1->Panel1->Controls->Add(this->button2);
			this->splitContainer1->Panel1->Controls->Add(this->set3DMap);
			this->splitContainer1->Panel1->Controls->Add(this->button1);
			this->splitContainer1->Panel1->Controls->Add(this->setMap);
			this->splitContainer1->Panel1->Controls->Add(this->groupBox1);
			this->splitContainer1->Panel1->Margin = System::Windows::Forms::Padding(10);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::OpenGLPanel_Paint);
			this->splitContainer1->Panel2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OpenGLPanel_MouseDown);
			this->splitContainer1->Panel2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OpenGLPanel_MouseMove);
			this->splitContainer1->Panel2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OpenGLPanel_MouseUp);
			this->splitContainer1->Panel2->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OpenGLPanel__MouseWheel);
			this->splitContainer1->Panel2->Resize += gcnew System::EventHandler(this, &Form1::splitContainer1_Panel2_Resize);
			this->splitContainer1->Size = System::Drawing::Size(979, 719);
			this->splitContainer1->SplitterDistance = 198;
			this->splitContainer1->TabIndex = 9;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(21, 97);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(109, 23);
			this->button2->TabIndex = 11;
			this->button2->Text = L"3D Mode";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::set3DMap_Click);
			// 
			// set3DMap
			// 
			this->set3DMap->Location = System::Drawing::Point(21, 97);
			this->set3DMap->Name = L"set3DMap";
			this->set3DMap->Size = System::Drawing::Size(109, 23);
			this->set3DMap->TabIndex = 11;
			this->set3DMap->Text = L"Set 3D Map";
			this->set3DMap->UseVisualStyleBackColor = true;
			this->set3DMap->Click += gcnew System::EventHandler(this, &Form1::set3DMap_Click);
			// 
			// button1
			// 
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DarkGray;
			this->button1->Location = System::Drawing::Point(21, 68);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(109, 23);
			this->button1->TabIndex = 10;
			this->button1->Text = L"2D Mode";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::setMap_Click);
			// 
			// setMap
			// 
			this->setMap->Location = System::Drawing::Point(21, 68);
			this->setMap->Name = L"setMap";
			this->setMap->Size = System::Drawing::Size(109, 23);
			this->setMap->TabIndex = 10;
			this->setMap->Text = L"Set Normal Map";
			this->setMap->UseVisualStyleBackColor = true;
			this->setMap->Click += gcnew System::EventHandler(this, &Form1::setMap_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->SetHalfWayButton);
			this->groupBox1->Controls->Add(this->LockLabel);
			this->groupBox1->Controls->Add(this->TextONOFF);
			this->groupBox1->Controls->Add(this->WalkTimeLabel);
			this->groupBox1->Controls->Add(this->richTextBox1);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->BeginTextBox);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->DistLabel);
			this->groupBox1->Controls->Add(this->EndTextBox);
			this->groupBox1->Controls->Add(this->pictureBox2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->groupBox1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->groupBox1->Location = System::Drawing::Point(12, 26);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(254, 604);
			this->groupBox1->TabIndex = 12;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Info";
			// 
			// SetHalfWayButton
			// 
			this->SetHalfWayButton->Font = (gcnew System::Drawing::Font(L"新細明體", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->SetHalfWayButton->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->SetHalfWayButton->Location = System::Drawing::Point(6, 565);
			this->SetHalfWayButton->Name = L"SetHalfWayButton";
			this->SetHalfWayButton->Size = System::Drawing::Size(124, 23);
			this->SetHalfWayButton->TabIndex = 15;
			this->SetHalfWayButton->Text = L"開啟中途點模式";
			this->SetHalfWayButton->UseVisualStyleBackColor = true;
			this->SetHalfWayButton->Click += gcnew System::EventHandler(this, &Form1::SetHalfWayButton_Click);
			// 
			// LockLabel
			// 
			this->LockLabel->AutoSize = true;
			this->LockLabel->BackColor = System::Drawing::Color::SteelBlue;
			this->LockLabel->Font = (gcnew System::Drawing::Font(L"新細明體", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->LockLabel->ForeColor = System::Drawing::Color::Red;
			this->LockLabel->Location = System::Drawing::Point(124, 48);
			this->LockLabel->Name = L"LockLabel";
			this->LockLabel->Size = System::Drawing::Size(72, 11);
			this->LockLabel->TabIndex = 14;
			this->LockLabel->Text = L"View Locked";
			// 
			// TextONOFF
			// 
			this->TextONOFF->Font = (gcnew System::Drawing::Font(L"新細明體", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TextONOFF->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->TextONOFF->Location = System::Drawing::Point(9, 100);
			this->TextONOFF->Name = L"TextONOFF";
			this->TextONOFF->Size = System::Drawing::Size(109, 23);
			this->TextONOFF->TabIndex = 13;
			this->TextONOFF->Text = L"字幕 ON";
			this->TextONOFF->UseVisualStyleBackColor = true;
			this->TextONOFF->Click += gcnew System::EventHandler(this, &Form1::TextONOFF_Click);
			// 
			// WalkTimeLabel
			// 
			this->WalkTimeLabel->AutoSize = true;
			this->WalkTimeLabel->Font = (gcnew System::Drawing::Font(L"新細明體", 10, System::Drawing::FontStyle::Bold));
			this->WalkTimeLabel->Location = System::Drawing::Point(55, 297);
			this->WalkTimeLabel->Name = L"WalkTimeLabel";
			this->WalkTimeLabel->Size = System::Drawing::Size(82, 14);
			this->WalkTimeLabel->TabIndex = 1;
			this->WalkTimeLabel->Text = L"步行時間：";
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::LightBlue;
			this->richTextBox1->Location = System::Drawing::Point(9, 337);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(167, 199);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label3->Location = System::Drawing::Point(55, 266);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(42, 16);
			this->label3->TabIndex = 6;
			this->label3->Text = L"距離";
			// 
			// BeginTextBox
			// 
			this->BeginTextBox->BackColor = System::Drawing::Color::SteelBlue;
			this->BeginTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->BeginTextBox->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->BeginTextBox->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->BeginTextBox->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BeginTextBox->Location = System::Drawing::Point(119, 188);
			this->BeginTextBox->Name = L"BeginTextBox";
			this->BeginTextBox->Size = System::Drawing::Size(116, 20);
			this->BeginTextBox->TabIndex = 1;
			this->BeginTextBox->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label2->Location = System::Drawing::Point(55, 228);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(42, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"終點";
			// 
			// DistLabel
			// 
			this->DistLabel->AutoSize = true;
			this->DistLabel->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->DistLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->DistLabel->Location = System::Drawing::Point(116, 266);
			this->DistLabel->Name = L"DistLabel";
			this->DistLabel->Size = System::Drawing::Size(17, 16);
			this->DistLabel->TabIndex = 9;
			this->DistLabel->Text = L"0";
			// 
			// EndTextBox
			// 
			this->EndTextBox->BackColor = System::Drawing::Color::SteelBlue;
			this->EndTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->EndTextBox->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->EndTextBox->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->EndTextBox->Location = System::Drawing::Point(119, 228);
			this->EndTextBox->Name = L"EndTextBox";
			this->EndTextBox->Size = System::Drawing::Size(116, 20);
			this->EndTextBox->TabIndex = 2;
			this->EndTextBox->Text = L"0";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(18, 176);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(31, 32);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 8;
			this->pictureBox2->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"新細明體", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label1->Location = System::Drawing::Point(55, 188);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"起點";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(18, 216);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(31, 32);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(979, 719);
			this->Controls->Add(this->splitContainer1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->splitContainer1->Panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		void DrawScene(void)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			GLfloat light_pos1[4] = { 150, 200, 200, 1 };
			GLfloat light_pos2[4] = { -150, 200, 200, 1 };
			float color1[4] = { 1, 1, 0.5, 1 };
			float destination_color[4] = { 1, 0, 0.0, 1 };
			float position_color[4] = { 0, 0.0, 1, 1 };
			float floorcolor[4] = { 0.05, 0.05, 0.05, 1 };
			float campuscolor[4] = { 0.5, 0.5, 0.5, 1 };
			float buildings_color1[4] = { 0.5, 0.2, 0.2, 1 };

			

			Draw_axis();
			glScalef(zoom, zoom, zoom);
			glTranslatef(wX, Wy, 0);

			glRotatef(duu, 1, 0, 0);
			glRotatef(du, 0, 0, 1);

			

			glPushMatrix();
			////////////////////////////////////////////////////////////
			

			glPushMatrix();
			glEnable(GL_LIGHTING); //Enable lighting
			glEnable(GL_LIGHT0); //Enable light #0
			glTranslatef(0, 10, 0);
			if (posX[0] != 0)
			{
				glPushMatrix();
				glTranslatef(posX[0], posY[0], posZ[0]);
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, position_color);
				glRotatef(90, 1, 0, 0);
				position->Draw();
				glPopMatrix();
			}
			if (posX[1] != 0)
			{
				glPushMatrix();
				glTranslatef(posX[1], posY[1], posZ[1]);
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, destination_color);
				glRotatef(90, 1, 0, 0);
				destination->Draw();
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();
			{
				//glRotatef(-90, 1, 0, 0);
				glTranslatef(-campus1->cent[0], -campus1->cent[1], 0);
				//glTranslatef(0, -100, 50); /// 全部模型 往-y移動100
				//glEnable(GL_LIGHTING); //Enable lighting
				//glEnable(GL_LIGHT0); //Enable light #0


				/// 畫節點////////////////////////////////////////////////////////////////
				glPushMatrix();
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				glPointSize(6);
				glColor3f(1, 0, 0);
				glBegin(GL_POINTS); /// 畫節點
				for (int i = 0; i < map1->Node_num; i++)
				{
					if (i == start || i == end)
					{
						glColor3f(0, 0, 1);
					}
					else
					{
						glColor3f(1, 0, 0);
					}
					glVertex3f(map1->Node[i].data.x, map1->Node[i].data.y, 2);
				}
				glEnd();
				glPopMatrix();
				///////////////////////////////////////////////////////////////////////
				///畫建築物////////////////////////////////////////////////////////////
				glPushMatrix();
				glEnable(GL_LIGHTING); //Enable lighting
				glEnable(GL_LIGHT0); //Enable light #0
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, campuscolor);
				campus1->Draw();
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, buildings_color1);
				campus1_buildings->Draw();
				glPopMatrix();
				////////////////////////////////////////////////////////////
				///地板////////////////////////////////////////////////////////////
				glPushMatrix();
				glTranslatef(0, 0, -2500);
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, floorcolor);
				glutSolidCube(5000);
				glPopMatrix();

				///畫路徑////////////////////////////////////////////////////////////
				glPushMatrix();
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				glLineWidth(6);
				glColor3f(0, 1, 0);
				glEnable(GL_LINE_STIPPLE);
				GLint factor = 4;// 值可改為1~5
				GLushort pattern = 0x5555;
				glLineStipple(factor, pattern);
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < tempbuf.size(); i++)
				{
					glVertex3f(map1->Node[tempbuf[i]].data.x, map1->Node[tempbuf[i]].data.y, 2);
				}
				glEnd();
				glPopMatrix();
				////////////////////////////////////////////////////////////


				////////////////////////////////////////////////////////////
				/*double modelview[16] = { 0 };
				double projection[16] = { 0 };
				GLint viewport[4] = { 0 };*/
				glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
				glGetDoublev(GL_PROJECTION_MATRIX, projection);
				glGetIntegerv(GL_VIEWPORT, viewport);
				for (int i = 0; i < map1->Node_num; i++)
				{
					GLdouble px = map1->Node[i].data.x, py = map1->Node[i].data.y, pz = 0;
					gluProject(px, py, pz, modelview, projection, viewport, &winX[i], &winY[i], &winZ[i]);

					winY[i] = splitContainer1->Panel2->Height - winY[i];
					if (textFlag == true)
					if (winY[i] > 0 && winX[i] > 0 && winY[i] < splitContainer1->Panel2->Height && winX[i] < splitContainer1->Panel2->Width)
					{
						glPushMatrix();
						glPrintf(">>glut(%i,%i)", (int)winX[i] - 40, (int)winY[i]);
						glColor3f(1, 1, 0);
						if (map1->Node[i].getName() != "NULL")
							glPrintf(map1->Node[i].getName().c_str());
						glPopMatrix();
					}

				}
				glPushMatrix();
				glPrintf(">>glut(%i,%i)", 20, 20);
				glColor3f(1, 1, 0);
				glPrintf("成功大學自強校區");
				glPopMatrix();
			}
			glPopMatrix();
			glPopMatrix();

			glFlush();
			SwapBuffers(m_hDC);
		}

		void OpenGLInit(void)
		{
			// Get Handle
			//m_hWnd = (HWND)this->OpenGLPanel->Handle.ToInt32();
			m_hWnd = (HWND)this->splitContainer1->Panel2->Handle.ToInt32();
			m_hDC = GetDC(m_hWnd);
			//WGL::wglSwapBuffers((unsigned int)m_hDC);
			wglSwapBuffers(m_hDC);
			// Set pixel format
			PIXELFORMATDESCRIPTOR pfd;
			//WGL::ZeroPixelDescriptor(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = (byte)(PFD_TYPE_RGBA);
			pfd.cColorBits = 32;
			pfd.cDepthBits = 32;
			pfd.iLayerType = (byte)(PFD_MAIN_PLANE);

			int nFormat = ChoosePixelFormat(m_hDC, &pfd);
			SetPixelFormat(m_hDC, nFormat, &pfd);
			// Create OpenGL Rendering Context
			m_hRC = (wglCreateContext(m_hDC));
			if (m_hRC == 0)
				MessageBox::Show("wglCreateContext Error");
			// Assign OpenGL Rendering Context
			if (wglMakeCurrent(m_hDC, m_hRC) == false)
				MessageBox::Show("wglMakeCurrent Error");

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glEnable(GL_DEPTH_TEST);

			glDepthFunc(GL_LESS);

			glDepthFunc(GL_LEQUAL);
			//GL.glEnable(GL.GL_CULL_FACE);
			glCullFace(GL_BACK);

			glShadeModel(GL_FLAT);
			glEnable(GL_NORMALIZE);
			glEnable(GL_CULL_FACE);


			glClearDepth(1.0f);

			wglMakeCurrent(m_hDC, m_hRC);
			/*glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			GLfloat nRange = 70.f;
			glOrtho(-nRange, nRange, -nRange, nRange, -nRange * 50, nRange * 50);
			glMatrixMode(GL_MODELVIEW);*/

		}
		double round2(double x, int n)
		{
			long v;
			v = pow((double)10, n);
			return floor(x*v + 0.5) / v;

		}

		void Draw_axis()
		{
			int z_layer = 3000;
			int axis_length = 8;
			glPushMatrix();
			glTranslatef(70, -60, z_layer);
			//glRotatef(30, 1, 0, 0);

			glRotatef(duu, 1, 0, 0);
			glRotatef(du, 0, 0, 1);


			glDisable(GL_LINE_STIPPLE);
			glRotatef(90, 1, 0, 0);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
			glLineWidth(3);
			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 4); // North
			glVertex3f(0, 0, -axis_length);
			glEnd();

			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(-2, 0, -axis_length - 2); // North
			glVertex3f(-2, 0, -axis_length - 6);
			glEnd();
			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(-2, 0, -axis_length - 6);
			glVertex3f(1, 0, -axis_length - 2);
			glEnd();
			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3f(1, 0, -axis_length - 2);
			glVertex3f(1, 0, -axis_length - 6);
			glEnd();

			glBegin(GL_LINES);
			glColor3f(0, 0, 1);
			glVertex3f(-axis_length + 5, 0, 0); // Y
			glVertex3f(axis_length - 5, 0, 0);
			glEnd();


			glPopMatrix();

		}
		void Select_point(int x, int y, int i)
		{
			/*GLfloat winX, winY, winZ;
			double modelview[16] = { 0 };
			double projection[16] = { 0 };
			GLint viewport[4] = { 0 };*/
			GLfloat winX, winY, winZ;
			glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
			glGetDoublev(GL_PROJECTION_MATRIX, projection);
			glGetIntegerv(GL_VIEWPORT, viewport);

			winX = (float)x;
			winY = (float)viewport[3] - (float)y;
			glReadPixels(int(winX), int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX[i], &posY[i], &posZ[i]);
			printf("\n ax = %f", posX[i]);
			printf("\n ay = %f", posY[i]);
			printf("\n az = %f", posZ[i]);
		}
		float setRoute(vector<int>&buffer) //// 使用者操作互動
		{

			buffer.clear();
			cout << "經過的節編號:" << endl;

			float Distance = map1->setRoute(start, end, map1->dist, map1->dist2, buffer);

			for (int i = 0; i < buffer.size(); i++)
			{
				cout << buffer[i] + 1 << " ";

			}
			String ^str = "經過： \n";
			for (int i = 1; i < buffer.size(); i++)
			{
				if (map1->Node[buffer[i]].getName() != "NULL")
				{
					String^ a = gcnew String(map1->Node[buffer[i]].getName().c_str());
					str = str + " -> " + a + "\n";
					richTextBox1->Text = str;
				}
			}

			setlocale(LC_ALL, "Chinese-simplified");

			return Distance*0.6777; /// to kilometer
		}
		float setHalfWayRoute(int s,int e,vector<int>halfway,vector<int>&buffer)
		{
			//tempbuf.clear();
			buffer.clear();
			
			
			halfway.insert(halfway.begin(), s);
			halfway.insert(halfway.end(), e);
			vector<int>::iterator it = buffer.begin();
			float dd = 0;
			for (int i = 0; i < halfway.size()-1; i++)
			{
				vector<int>temp;
				float Distance = map1->setRoute(halfway[i], halfway[i + 1], map1->dist, map1->dist2, temp);
				dd += Distance;
				for (int j = 0; j < temp.size(); j++)
				{
					//if (buffer[buffer.size()] != temp[0])
					buffer.push_back(temp[j]);
				}
				
			}
			String ^str = "經過： \n";
			for (int i = 1; i < buffer.size(); i++)
			{
				if (map1->Node[buffer[i]].getName() != "NULL")
				{
					String^ a = gcnew String(map1->Node[buffer[i]].getName().c_str());
					str = str + " -> " + a + "\n";
					richTextBox1->Text = str;
				}
			}
			return dd;
		}
		

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 DrawScene();
	}
	private: System::Void OpenGLPanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //cout << e->X << " " << e->Y << endl;
				 if (e->Button == System::Windows::Forms::MouseButtons::Left && MapState == SET_3D_MAP) //滑鼠左鍵按下
				 {

					 du += e->X - oldmx;
					 if (du > 360)
						 du = 0;
					 if (du < 0)
						 du = 360;
					 duu += (e->Y - oldmy);
					 if (duu >= 0)
						 duu = 0;
					 else if (duu <= -90)
						 duu = -90;
					 oldmx = e->X, oldmy = e->Y;
					 DrawScene();

				 }

				 else if (e->Button == System::Windows::Forms::MouseButtons::Middle)
				 {
					 wX += (float)(e->X - oldmx);
					 Wy += (float)(-(e->Y - oldmy));
					 DrawScene();
					 oldmx = e->X;
					 oldmy = e->Y;
				 }
	}
	private: System::Void OpenGLPanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

				 oldmx = e->X;
				 oldmy = e->Y;

				 if (e->Button == System::Windows::Forms::MouseButtons::Right)
				 {
					 // Select_point(e->X, e->Y, 0);

				 }


				 printf("\n");

	}
	private: System::Void OpenGLPanel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if (e->Button == System::Windows::Forms::MouseButtons::Right)
				 {
					 if (select_state == NORNAL_SELECT_MODE)
					 {
						 for (int i = 0; i < map1->Node_num; i++)
						 {
							 float err = sqrt(pow(winX[i] - e->X, 2) + pow(winY[i] - e->Y, 2));
							 if (err <= 10)
							 {
								 if (mousecount == 0)
								 {
									 tempbuf.clear();
									 start = i;
									 end = -1;
									 String^ s = gcnew String(map1->Node[i].getName().c_str());
									 BeginTextBox->Text = s;
									 if (map1->Node[i].getName() == "NULL")
										 BeginTextBox->Text = "校內道路";
								 }
								 if (mousecount == 1)
								 {
									 end = i;
									 String^ e = gcnew String(map1->Node[i].getName().c_str());
									 EndTextBox->Text = e;
									 if (map1->Node[i].getName() == "NULL")
										 EndTextBox->Text = "校內道路";

									 totalDist = setRoute(tempbuf);
									 DistLabel->Text = totalDist.ToString("0.0") + "  公尺";
									 float walk_time = totalDist / (4500 / 60);
									 WalkTimeLabel->Text = "步行時間：" + walk_time.ToString("0.0") + " 分鐘";
								 }
								 Select_point(e->X, e->Y, mousecount);
								 mousecount = (mousecount + 1) % 2;
							 }
						 }
					 }
					 else if (select_state == HALFWAY_SELECT_MODE)
					 {
						 for (int i = 0; i < map1->Node_num; i++)
						 {
							 float err = sqrt(pow(winX[i] - e->X, 2) + pow(winY[i] - e->Y, 2));
							 if (err <= 10)
							 {
								 if (mousecount == 0)
								 {
									 tempbuf.clear();
									 start = i;
									 end = -1;
									 String^ s = gcnew String(map1->Node[i].getName().c_str());
									 BeginTextBox->Text = s;
									 if (map1->Node[i].getName() == "NULL")
										 BeginTextBox->Text = "校內道路";
								 }
								 if (mousecount == 1)
								 {
									 end = i;
									 String^ e = gcnew String(map1->Node[i].getName().c_str());
									 EndTextBox->Text = e;
									 if (map1->Node[i].getName() == "NULL")
										 EndTextBox->Text = "校內道路";

									 totalDist = setRoute(tempbuf);
									 DistLabel->Text = totalDist.ToString("0.0") + "  公尺";
									 float walk_time = totalDist / (5000 / 60);
									 WalkTimeLabel->Text = "步行時間：" + walk_time.ToString("0.0") + " 分鐘";
								 }
								 if (mousecount > 1)
								 {
									 temphalfway.push_back(i);
									 float Distance = setHalfWayRoute(start, end, temphalfway, tempbuf);
									 
								 }
								 Select_point(e->X, e->Y, mousecount);
								 mousecount = (mousecount + 1);
							 }
						 }
					 }
					 

				 }
				 DrawScene();
	}
	private: System::Void OpenGLPanel__MouseWheel(Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
	{
				 // Update the drawing based upon the mouse wheel scrolling.
				 ///int numberOfTextLinesToMove = e->Delta * SystemInformation::MouseWheelScrollLines / 120;
				 if (zoom > 0.1 || (e->Delta * SystemInformation::MouseWheelScrollLines) > 0)
				 {
					 zoom += (float)(e->Delta * SystemInformation::MouseWheelScrollLines) / 7200;
					 if (zoom < 0.1)
						 zoom = 0.1;
				 }

				 printf("%f", zoom);
				 DrawScene();

	}
	private: System::Void OpenGLPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 DrawScene();
	}
	private: System::Void splitContainer1_Panel2_Resize(System::Object^  sender, System::EventArgs^  e) {
				 glMatrixMode(GL_PROJECTION);
				 glLoadIdentity();

				 GLfloat nRange = 70.f;
				 int cx = splitContainer1->Panel2->Width;
				 int cy = splitContainer1->Panel2->Height;
				 if (cx <= cy)//glOrtho
					 glOrtho(-nRange, nRange, -nRange*cy / cx, nRange*cy / cx, -nRange * 50, nRange * 50);
				 else
					 glOrtho(-nRange*cx / cy, nRange*cx / cy, -nRange, nRange, -nRange * 50, nRange * 50);

				 glMatrixMode(GL_MODELVIEW);
				 glViewport(0, 0, cx, cy);
	}

	private: System::Void setMap_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (MapState == SET_3D_MAP)
				 {
					 MapState = SET_NORMAL_MAP;
					 /*du = 0;
					 duu = 0;*/
					 timer1->Interval = 30;
					 textFlag = false;
					 timer1->Enabled = true;
					 LockLabel->Show();
					 DrawScene();
				 }

	}
	private: System::Void set3DMap_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (MapState == SET_NORMAL_MAP)
				 {
					 timer1->Interval = 30;
					 textFlag = false;
					 timer1->Enabled = true;
					 MapState = SET_3D_MAP;
					 LockLabel->Hide();
					 DrawScene();
				 }

	}
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 //DrawScene();
				 if (MapState == SET_NORMAL_MAP)
				 {

					 if (du != 0 || duu != 0)
					 {
						 if (du > 180)
						 {
							 du += animateSpeed;
							 if (du >= 360)
								 du = 0;
						 }
						 else
						 {
							 du -= animateSpeed;
							 if (du <= 0)
								 du = 0;
						 }

						 duu += animateSpeed;

						 if (duu >= 0)
							 duu = 0;

					 }
					 if (du == 0 && duu == 0){
						 textFlag = true;
						 timer1->Enabled = false;
					 }
						
				 }
				 else if (MapState == SET_3D_MAP)
				 {
					 if (du != 330 || duu != -30)
					 {
						 du -= animateSpeed;
						 if (abs(abs(du) - 30) <= 5)
							 du = 330;
						 duu -= animateSpeed;
						 if (duu -= 30)
							 duu = -30;

					 }
					 if (du == 330 && duu == -30)
					 {
						 textFlag = true;
						 timer1->Enabled = false;
					 }
				 }
				 DrawScene();

	}
	private: System::Void TextONOFF_Click(System::Object^  sender, System::EventArgs^  e) {
				 textFlag = (textFlag + 1) % 2;
				 DrawScene();
	}
	private: System::Void SetHalfWayButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (select_state == NORNAL_SELECT_MODE)
				 {
					 SetHalfWayButton->Text = "關閉中途點模式";
					 select_state = HALFWAY_SELECT_MODE;
				 }
					 
				 else if (select_state == HALFWAY_SELECT_MODE)
				 {
					 select_state = NORNAL_SELECT_MODE;
					 SetHalfWayButton->Text = "開啟中途點模式";
				 }
				 temphalfway.clear();
				 tempbuf.clear();
				 mousecount = 0;
	}
};
}