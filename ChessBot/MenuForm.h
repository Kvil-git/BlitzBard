#pragma once
#include "3d/Rendering.h"
#include "BoardForm.h"

World world;
Model model;
Camera camera;
std::vector<Triangle3> polygonsToDraw;

enum StartingPosition {
	standart,
	castling,
	enPassant,
	endGame,
	promotion
};

namespace MainProgramMenu {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MainMenu : public System::Windows::Forms::Form {
	public:
		bool playerColor = 0;
		int mouseX;
		int mouseY;
		int mouseZ = 4;
		int x0;
		int y0;
		float scalarX = 4.7f;
		float scalarY = 4.7f;
		float scalarZ = 4.7f;
	private: System::Windows::Forms::CheckedListBox^ checkedListBox1;

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Label^ buttonText;

	private: System::Windows::Forms::ListBox^ listBox1;


	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Timer^ timer1;






	public:
		MainMenu(void) {
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}


	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainMenu() {
			if (components) delete components;
		}

	
		   /// <summary>
		   /// Обязательная переменная конструктора.
		   /// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		   void InitializeComponent(void) {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->buttonText = (gcnew System::Windows::Forms::Label());
			   this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->panel1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			   this->pictureBox1->Location = System::Drawing::Point(483, 13);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(911, 608);
			   this->pictureBox1->TabIndex = 6;
			   this->pictureBox1->TabStop = false;
			   this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainMenu::pictureBox1_Paint);
			   this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainMenu::pictureBox1_MouseMove);
			   // 
			   // timer1
			   // 
			   this->timer1->Tick += gcnew System::EventHandler(this, &MainMenu::timer1_Tick);
			   // 
			   // checkedListBox1
			   // 
			   this->checkedListBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				   static_cast<System::Int32>(static_cast<System::Byte>(28)));
			   this->checkedListBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->checkedListBox1->CheckOnClick = true;
			   this->checkedListBox1->Font = (gcnew System::Drawing::Font(L"Inter Black", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->checkedListBox1->ForeColor = System::Drawing::Color::White;
			   this->checkedListBox1->FormattingEnabled = true;
			   this->checkedListBox1->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"x", L"y", L"z", L"dir", L"clr" });
			   this->checkedListBox1->Location = System::Drawing::Point(1196, 13);
			   this->checkedListBox1->Name = L"checkedListBox1";
			   this->checkedListBox1->Size = System::Drawing::Size(69, 170);
			   this->checkedListBox1->TabIndex = 7;
			   // 
			   // panel1
			   // 
			   this->panel1->BackColor = System::Drawing::Color::Transparent;
			   this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->panel1->Controls->Add(this->buttonText);
			   this->panel1->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->panel1->Location = System::Drawing::Point(29, 263);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(418, 60);
			   this->panel1->TabIndex = 8;
			   this->panel1->Click += gcnew System::EventHandler(this, &MainMenu::panel1_Click);
			   this->panel1->MouseEnter += gcnew System::EventHandler(this, &MainMenu::panel1_MouseEnter);
			   // 
			   // buttonText
			   // 
			   this->buttonText->AutoSize = true;
			   this->buttonText->Font = (gcnew System::Drawing::Font(L"Inter Black", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->buttonText->ForeColor = System::Drawing::Color::White;
			   this->buttonText->Location = System::Drawing::Point(113, 14);
			   this->buttonText->Name = L"buttonText";
			   this->buttonText->Size = System::Drawing::Size(199, 29);
			   this->buttonText->TabIndex = 0;
			   this->buttonText->Text = L"Почати Партію";
			   this->buttonText->Click += gcnew System::EventHandler(this, &MainMenu::panel1_Click);
			   // 
			   // listBox1
			   // 
			   this->listBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				   static_cast<System::Int32>(static_cast<System::Byte>(28)));
			   this->listBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->listBox1->Font = (gcnew System::Drawing::Font(L"Inter Black", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->listBox1->ForeColor = System::Drawing::Color::White;
			   this->listBox1->FormattingEnabled = true;
			   this->listBox1->ItemHeight = 29;
			   this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				   L"початок партії", L"рокірування", L"взяття на проході",
					   L"ендшпіль", L"прохідний пішак"
			   });
			   this->listBox1->Location = System::Drawing::Point(29, 139);
			   this->listBox1->Name = L"listBox1";
			   this->listBox1->Size = System::Drawing::Size(418, 87);
			   this->listBox1->TabIndex = 9;
			   // 
			   // MainMenu
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				   static_cast<System::Int32>(static_cast<System::Byte>(28)));
			   this->ClientSize = System::Drawing::Size(1406, 633);
			   this->Controls->Add(this->listBox1);
			   this->Controls->Add(this->panel1);
			   this->Controls->Add(this->checkedListBox1);
			   this->Controls->Add(this->pictureBox1);
			   this->Name = L"MainMenu";
			   this->Text = L"Main Menu";
			   this->Load += gcnew System::EventHandler(this, &MainMenu::MainMenu_Load);
			   this->SizeChanged += gcnew System::EventHandler(this, &MainMenu::MainMenu_SizeChanged);
			   this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainMenu::MainMenu_MouseMove);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->panel1->ResumeLayout(false);
			   this->panel1->PerformLayout();
			   this->ResumeLayout(false);

		   }
#pragma endregion

		   PointF toPointF(const Vector2& vector) {
			   PointF output; output.X = vector.X; output.Y = vector.Y;
			   return output;
		   }

		   PointF toPointF(const Vector3& vector) {
			   PointF output; output.X = vector.X; output.Y = vector.Y;
			   return output;
		   }

		   Vector3 rotateVector(const Vector3& vector) {
			   float x = world.xRotAngle / 180 * PI;
			   float y = world.yRotAngle / 180 * PI;
			   float z = world.zRotAngle / 180 * PI;
			   Vector3 output = vector;

			   float elements[3][3] = {
				   cos(y) * cos(z),   sin(x) * sin(y) * sin(z) - cos(x) * sin(z),   cos(x) * sin(y) * cos(z) + sin(x) * sin(z),
				   sin(x) * cos(y),   sin(x) * sin(y) * sin(z) + cos(x) * cos(z),   sin(x) * sin(y) * cos(z) - cos(x) * sin(z),
				   -sin(y),		   cos(y) * sin(z),							     cos(y) * cos(z)
			   };
			   Matrix3x3 rotation(elements);
			   output *= rotation;
			   return output;
		   }

		   Vector3 scaleVector(const Vector3& vector) {
			   Vector3 output = vector;
			   output.X *= scalarX;
			   output.Y *= scalarY;
			   output.Z *= scalarZ;
			   return output;
		   }

		   Vector4 toHomogeneous(const Vector3& input) {
			   Vector4 output;
			   output.elements[0] = input.X;
			   output.elements[1] = input.Y;
			   output.elements[2] = input.Z;
			   output.elements[3] = 1;
			   return output;
		   }

		   Vector3 toVector3(const Vector4 input) {
			   Vector3 output;
			   output.X = input.elements[0] / input.elements[3];
			   output.Y = input.elements[1] / input.elements[3];
			   output.Z = input.elements[2] / input.elements[3];
			   return output;
		   }


		   Vector4 projectVector(const Vector4& input) {
			   float ctg = 1 / tanf(camera.fov / 360 * PI); // cotangent of half fovX
			   float z = input.elements[2];
			   float q = z * camera.Far / (z * camera.Far - camera.Near);

			   float elements[4][4]{
				  camera.aspectRatio * ctg,		 0,				   0,									    0,
				  0,							ctg,			   0,									    0,
				  0,							 0,				  q,										1,
				  0,							 0,				  -camera.Near * q,							0
			   };

			   Matrix4x4 perspective(elements);
			   Vector4 output = input;
			   output *= perspective;
			   return output;
		   }




		   //Vector3 projectVector(const Vector3& input) {
			  // const float f = 1.0 / tan(camera.fov / 360.0 * PI); // cotangent of half fovX
			  // float q = input.Z * camera.Far / (camera.Far - camera.Near);
			  // Vector3 output;
			  // output.X = (camera.aspectRatio * f * input.X) / input.Z;
			  // output.Y = (camera.aspectRatio * f * input.Y ) / input.Z;
			  // output.Z = (input.Z * q) - (camera.Near * q);
			  // return output;
		   //}


		   Vector3 projectVector(const Vector3& input) {
			   Vector3 output;
			   float rads = camera.fov * PI / 360;
			   const float f = cos(rads)/sin(rads); // cotangent of half fovX
			   float x = input.X;
			   float y = input.Y;
			   float z = input.Z;
			   float q = camera.Far / (camera.Far - camera.Near);
			   
			   output.X = (camera.aspectRatio * f * x);
			   output.Y = (f * y);
			   output.Z = (z * q) - (camera.Near * q);

			   return output;
		   }
		   

		   /*System::Drawing::PointF toPoint2D(const Vector3& vector) {
			   float outputX = (-vector.Z + vector.X) + x0;
			   float outputY = ((-vector.Z - vector.X) + vector.Y) + y0;
			   return PointF(outputX, outputY);
		   }*/

		   /*float elements[4][4]{
				  0,	  		    			0,					1,									    0,
				  0,							0,			        q,									   -camera.Near * q,
				  0,							ctg,				0,									    0,
				  camera.aspectRatio * ctg,		0,					0,				 						0
			};*/


		   /*System::Drawing::PointF toPoint2D(const Vector3& vector) {
			   float outputX = PIECE_SIZE * (-vector.Z + vector.X) + x0;
			   float outputY = PIECE_SIZE * ((-vector.Z - vector.X) + vector.Y) + y0;
			   return PointF(outputX, outputY);
		   }*/

		   

		   void rotateModel(bool rotateX, bool rotateY, bool rotateZ) {

			   if (rotateX) {
				   pictureBox1->Invalidate();
				   if (camera.increment) world.xRotAngle+=3;
				   else world.xRotAngle-= 3;
			   }

			   if (rotateY) {
				   pictureBox1->Invalidate();
				   if (camera.increment) world.yRotAngle+= 3;
				   else world.yRotAngle-= 3;
			   }

			   if (rotateZ) {
				   pictureBox1->Invalidate();
				   if (camera.increment) world.zRotAngle+= 3;
				   else world.zRotAngle-= 3;
			   }
		   }


	private: System::Void MainMenu_Load(System::Object^ sender, System::EventArgs^ e) {
		x0 = pictureBox1->Width / 2;
		y0 = pictureBox1->Height / 2;

		camera.position.X = pictureBox1->Width / 2;
		camera.position.Y = pictureBox1->Height / 2;
		camera.position.Z = -1000.0f;

		this->panel1->BackgroundImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\button.png");
		this->Icon = gcnew System::Drawing::Icon("D:\\Chess\\ChessBot\\Board.ico");
		pictureBox1->Invalidate();
		this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);

		timer1->Enabled = true;
		timer1->Start();

		// Load .obj File
		bool loadout = model.loadFromFile("D:\\Chess\\ChessBot\\ChessBot\\resources\\models\\knight.obj");


		// Check to see if it loaded

		// If so continue
		if (loadout) {
			// Create/Open e1Out.txt
			std::ofstream file("logs.txt");
			file << "Model loaded successfully\n";
			/*for (uint8_t i = 0; i < polygonsToDraw.size(); i++) {
				file << "Polygon: "
					<< intToString<int>(i) << ":\n"
					<< "Vertex1.X:\t"
					<< model.LoadedPolygons[i].vertex1.Position.X << "\n"
					<< "Vertex1.Y:\t"
					<< model.LoadedPolygons[i].vertex1.Position.Y << "\n"
					<< "Vertex1.Z:\t"
					<< model.LoadedPolygons[i].vertex1.Position.Z << "\n"
					<< "Vertex1.Normal.X:\t"
					<< model.LoadedPolygons[i].vertex1.Normal.X << "\n"
					<< "Vertex1.Normal.Y:\t"
					<< model.LoadedPolygons[i].vertex1.Normal.Y << "\n"
					<< "Vertex1.Normal.Z:\t"
					<< model.LoadedPolygons[i].vertex1.Normal.Z << "\n"
					<< "Vertex2.X:\t"
					<< model.LoadedPolygons[i].vertex2.Position.X << "\n"
					<< "Vertex2.Y:\t"
					<< model.LoadedPolygons[i].vertex2.Position.Y << "\n"
					<< "Vertex2.Z:\t"
					<< model.LoadedPolygons[i].vertex2.Position.Z << "\n"
					<< "Vertex2.Normal.X:\t"
					<< model.LoadedPolygons[i].vertex2.Normal.X << "\n"
					<< "Vertex2.Normal.Y:\t"
					<< model.LoadedPolygons[i].vertex2.Normal.Y << "\n"
					<< "Vertex2.Normal.Z:\t"
					<< model.LoadedPolygons[i].vertex2.Normal.Z << "\n"
					<< "Vertex3.X:\t"
					<< model.LoadedPolygons[i].vertex3.Position.X << "\n"
					<< "Vertex3.Y:\t"
					<< model.LoadedPolygons[i].vertex3.Position.Y << "\n"
					<< "Vertex3.Z:\t"
					<< model.LoadedPolygons[i].vertex3.Position.Z << "\n"
					<< "Vertex3.Normal.X:\t"
					<< model.LoadedPolygons[i].vertex3.Normal.X << "\n"
					<< "Vertex3.Normal.Y:\t"
					<< model.LoadedPolygons[i].vertex3.Normal.Y << "\n"
					<< "Vertex3.Normal.Z:\t"
					<< model.LoadedPolygons[i].vertex3.Normal.Z << "\n\n\n\n";
			}*/

			// Close File
			file.close();
		} else { //output error
			// Create/Open e1Out.txt
			std::ofstream file("logs.txt");

			// Output Error
			file << "Failed to load model. May have failed to find it or it was not an .obj file.\n";

			// Close File
			file.close();
		}
	}

	private:System::Void Child_FormClosed(System::Object^ sender, System::EventArgs^ e) {//объявили метод
		if (this->Visible == false) this->Show();//который обеспечит открытие главной при обработке закрытия дочерней
	}

	private: System::Void MainMenu_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		mouseX = e->Location.X;
		mouseY = e->Location.Y;
		pictureBox1->Invalidate();
	}

	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
#pragma region горизонтальний поворот
			if (world.xRotAngle < 360 && world.xRotAngle > -360) {
				if (e->Location.X + 321 > mouseX) world.xRotAngle += 1;
				else if (e->Location.X + 321 < mouseX) world.xRotAngle -= 1;
			}

#pragma endregion

#pragma region вертикальний поворот
			if (world.yRotAngle < 360 && world.yRotAngle > -360) {
				if (e->Location.Y + 9 > mouseY) world.yRotAngle += 1;
				else if (e->Location.Y + 9 < mouseY) world.yRotAngle -= 1;
			}
#pragma endregion

		}
		else if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			x0 = e->X;
			y0 = e->Y;
		}

		mouseX = e->Location.X + 321;
		mouseY = e->Location.Y + 9;
		pictureBox1->Invalidate();


	}
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		polygonsToDraw.clear();
		pictureBox1->CreateGraphics();

		for (int i = model.LoadedPolygons.size() - 1; i >= 0; i--) {
			Vector3 orig1 = model.LoadedPolygons[i].vertex1.Position;
			Vector3 orig2 = model.LoadedPolygons[i].vertex2.Position;
			Vector3 orig3 = model.LoadedPolygons[i].vertex3.Position;

			/*orig1.X = orig1.X - orig1.Z;
			orig2.X = orig2.X - orig2.Z;
			orig3.X = orig3.X - orig3.Z;

			orig1.Y = orig1.Y - orig1.Z;
			orig2.Y = orig2.Y - orig2.Z;
			orig3.Y = orig3.Y - orig3.Z;*/

			/*orig1 = projectVector(orig1);
			orig2 = projectVector(orig2);
			orig3 = projectVector(orig3);*/


			Vector3 transformed1 = projectVector(rotateVector((scaleVector((orig1)))));
			Vector3 transformed2 = projectVector(rotateVector((scaleVector((orig2)))));
			Vector3 transformed3 = projectVector(rotateVector((scaleVector((orig3)))));

			Vector3 faceNormal = projectVector(getTriangleNormal(transformed1, transformed2, transformed3));

			Vector3 cameraRay = transformed1 - camera.position;
			if (dotProduct(cameraRay, faceNormal) > 0.0f) {

				/*if ((faceNormal.X * (transformed1.X - camera.position.X + x0) +
					faceNormal.Y * (transformed1.Y - camera.position.Y + y0) +
					faceNormal.Z * (transformed1.Z - camera.position.Z)) > 0.0f) {*/

					/*PointF point1 = PointF(projected1.X + x0, projected1.Y + y0);
					PointF point2 = PointF(projected2.X + x0, projected2.Y + y0);
					PointF point3 = PointF(projected3.X + x0, projected3.Y + y0);*/
				
				polygonsToDraw.push_back(Triangle3((transformed1), (transformed2), (transformed3), faceNormal));

				//float angle = 400 * angleBetweenVectors<float, float>(mouseX, mouseY, point1.X, point1.Y);
				//uint8_t lightAngle1 = 200 - mapValues<float, uint8_t>(angle, 0.0f, 1000.0f, 5.0f, 255.0f);
				//angle = 400 * angleBetweenVectors<float, float>(mouseX, mouseY, point2.X, point2.Y);
				//uint8_t lightAngle2 = 200 - mapValues<float, uint8_t>(angle, 0.0f, 1000.0f, 0.0f, 255.0f);
				//angle = 400 * angleBetweenVectors<float, float>(mouseX, mouseY, point3.X, point3.Y);
				//uint8_t lightAngle3 = 200 - mapValues<float, uint8_t>(angle, 0.0f, 1000.0f, 5.0f, 255.0f);

				//String^ green = toSystemString(intToHexString(lightAngle2));
				//String^ red = toSystemString(intToHexString(lightAngle1));
				//String^ blue = toSystemString(intToHexString(lightAngle3));

				//Graphics^ g = e->Graphics;
				//Pen^ pen = gcnew Pen(Color::BlueViolet, 1.0f);
				//SolidBrush^ brush = gcnew SolidBrush(Color::White);
				////Color brushColor = ColorTranslator::FromHtml("#" + red + "00" + blue);
				//Color brushColor = ColorTranslator::FromHtml("#" + red + green + blue);
				//brush->Color = brushColor;
				//g->FillPolygon(brush, points);
				////g->DrawPolygon(pen, points);
			}
		}

		sortTrianglesByZ(polygonsToDraw);

		for (int i = 0; i < polygonsToDraw.size(); i++) {


			PointF point1 = PointF(polygonsToDraw[i].vertex1.Position.X + x0, polygonsToDraw[i].vertex1.Position.Y + y0);
			PointF point2 = PointF(polygonsToDraw[i].vertex2.Position.X + x0, polygonsToDraw[i].vertex2.Position.Y + y0);
			PointF point3 = PointF(polygonsToDraw[i].vertex3.Position.X + x0, polygonsToDraw[i].vertex3.Position.Y + y0);


			cli::array<PointF>^ points = { point1, point2, point3 };

			// If ray is aligned with normal, then triangle is visible
			Vector3 lightDirection(0.0f, 1.0f, -1.0f);
			lightDirection.normalize();
			uint8_t lightIntensity = 100 * dotProduct(lightDirection, polygonsToDraw[i].faceNormal);

			float angle = 400 * angleBetweenVectors<float, float>(mouseX, mouseY, point1.X, point1.Y);
			uint8_t lightAngle1 = 200 - mapValues<float>(angle, 0.0f, 1000.0f, 5.0f, 255.0f);
			/*angle = 400 * angleBetweenVectors<float, float>(mouseX, mouseY, point2.X, point2.Y);
			uint8_t lightAngle2 = 200 - mapValues<float, uint8_t>(angle, 0.0f, 1000.0f, 0.0f, 255.0f);
			angle = 400 * angleBetweenVectors<float, float>(mouseX, mouseY, point3.X, point3.Y);
			uint8_t lightAngle3 = 200 - mapValues<float, uint8_t>(angle, 0.0f, 1000.0f, 5.0f, 255.0f);*/

			String^ red = toSystemString(intToHexString(lightAngle1));

			Graphics^ g = e->Graphics;
			Color brushColor = ColorTranslator::FromHtml("#" + red + red + red);
			SolidBrush^ brush = gcnew SolidBrush(Color::White);
			brush->Color = brushColor;
			g->FillPolygon(brush, points);
			Pen^ pen = gcnew Pen(Color::BlueViolet, 1.0f);
			g->FillPolygon(brush, points);
			//g->DrawPolygon(pen, points);
		}



}

	/*private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		x0 = pictureBox1->Width / 2;
		y0 = pictureBox1->Height / 2;
		pictureBox1->Invalidate();
	}*/

	private: System::Void MainMenu_SizeChanged(System::Object^ sender, System::EventArgs^ e) {
		pictureBox1->Location.X = this->Width;
		pictureBox1->Invalidate();
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		camera.increment = checkedListBox1->CheckedIndices->Contains(3);
		playerColor = checkedListBox1->CheckedIndices->Contains(4);
		rotateModel(checkedListBox1->CheckedIndices->Contains(0), checkedListBox1->CheckedIndices->Contains(1), checkedListBox1->CheckedIndices->Contains(2));
	}

	private: System::Void panel1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ FEN;
		switch (listBox1->SelectedIndex) {
			case standart:  FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; break;
			case castling:  FEN = "r4b1r/ppp3pp/8/4p3/2Pq4/3P4/PP2QPPP/2k1K2R w K - 0 18"; break;
			case enPassant: FEN = "2r3k1/1q1nbppp/r3p3/3pP3/pPpP4/P1Q2N2/2RN1PPP/2R4K b KQkq b3 0 23"; break;
			case endGame:   FEN = "8/KBN5/8/2k5/8/8/8/8 w - - 0 1"; break;
			case promotion: FEN = "8/1k3P2/8/8/8/8/1K6/8 w - - 0 1"; break;
		}
		
		ChessBot::BoardForm^ boardForm = gcnew ChessBot::BoardForm(FEN, playerColor);
		boardForm->Show();
		boardForm->Closed += gcnew EventHandler(this, &MainMenu::Child_FormClosed);//подписались
		this->Hide();
	}

	static Color DarkenColor(Color inColor, double lightenAmount){
		return Color::FromArgb(
	   inColor.A,
	   (int)max(0, inColor.R - 255 * lightenAmount),
	   (int)max(0, inColor.G - 255 * lightenAmount),
	   (int)max(0, inColor.B - 255 * lightenAmount));
	}

	private: System::Void panel1_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		panel1->BackgroundImage;
	}
};
}
