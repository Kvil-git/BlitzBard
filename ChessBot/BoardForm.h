#pragma once
#define ANIMDELAY 100
#define THEME1_WHITECOLOR "#ffce9e"
#define THEME1_BLACKCOLOR "#d18b47"
#define THEME2_WHITECOLOR "#eeeed5"
#define THEME2_BLACKCOLOR "#7d945d"
#define THEME3_WHITECOLOR "#ebd1b9"
#define THEME3_BLACKCOLOR "#a26e5b"

#define BOARD_SIZE_COEFFICIENT 1.0f

#define PROMOTION_X_OFFSET 0
#define BOARD_X_OFFSET -30
#define BOARD_Y_OFFSET -30
#define BOARD_SQR_LENGTH 50

#define PIECE_X_OFFSET -40
#define PIECE_Y_OFFSET -40

#define HOVER_COLOR Color::LimeGreen
#define SELECTED_COLOR Color::Orange
#define LEGALMOVE_COLOR Color::PaleGreen
#define CAPTURE_COLOR Color::Red
#define OCCUPIED_COLOR Color::MediumOrchid



#include "chessBackend/Game.cpp"
chessBackend::Game game;
namespace ChessBot {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	/// 
	public ref class BoardForm : public System::Windows::Forms::Form {
	private:
		cli::array<Panel^>^ board = gcnew cli::array<Panel^>(64);
		cli::array<Panel^>^ promotionButtons = gcnew cli::array<Panel^>(4);
		String^ FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
		Color whiteColor, blackColor, selectedColor, hoverColor, legalMoveColor, captureColor, occupiedColor, promotionColor;
		bool isPieceClicked = 0;
		int8_t clickedPieceIndex = -1;
		String^ clickedPiece = "E";

		bool isLoaded = 0;

		bool movingPlayer = 1;
		int Theme = 1;
		bool sounds = 1;
		int botElo = 900;
		int timeControl = 1;
		bool playerColor = 1;
		bool promotionClicked = 0;

		uint8_t enPassantSquare = 0;
		uint8_t castlingRights = 0b00001111;

		int squareTo = 0, squareFrom = 0;

		float widthScalar = 1.0f, heightScalar = 1.0f;

		System::Media::SoundPlayer^ clickSound   = gcnew System::Media::SoundPlayer("D:\\Chess\\ChessBot\\ChessBot\\resources\\sounds\\clickSound.wav");
		System::Media::SoundPlayer^ promotionSound = gcnew System::Media::SoundPlayer("C:\\Windows\\Media\\tada.wav");
		System::Media::SoundPlayer^ errorSound   = gcnew System::Media::SoundPlayer("D:\\Chess\\ChessBot\\ChessBot\\resources\\sounds\\error.wav");
	
		int originalFormWidth, originalFormHeight;
		

		Image^ whitePawnImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\whitePawn.png");
		Image^ blackPawnImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\blackPawn.png");
		Image^ whiteKnightImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\whiteKnight.png");
		Image^ blackKnightImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\blackKnight.png");
		Image^ whiteBishopImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\whiteBishop.png");
		Image^ blackBishopImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\blackBishop.png");
		Image^ whiteRookImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\whiteRook.png");
		Image^ blackRookImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\blackRook.png");
		Image^ whiteQueenImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\whiteQueen.png");
		Image^ blackQueenImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\blackQueen.png");
		Image^ whiteKingImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\whiteKing.png");
		Image^ blackKingImage = Image::FromFile(L"D:\\Chess\\ChessBot\\ChessBot\\resources\\images\\blackKing.png");



	public:
		BoardForm(void) {
			InitializeComponent();
			switch (Theme) {
				case 1:
					whiteColor = ColorTranslator::FromHtml(THEME1_WHITECOLOR);
					blackColor = ColorTranslator::FromHtml(THEME1_BLACKCOLOR); break;
				case 2:
					whiteColor = ColorTranslator::FromHtml(THEME2_WHITECOLOR);
					blackColor = ColorTranslator::FromHtml(THEME2_BLACKCOLOR); break;
				case 3:
					whiteColor = ColorTranslator::FromHtml(THEME3_WHITECOLOR);
					blackColor = ColorTranslator::FromHtml(THEME3_BLACKCOLOR); break;
			} promotionColor = ColorTranslator::FromHtml("#dedede");

			legalMoveColor = LEGALMOVE_COLOR;
			captureColor = CAPTURE_COLOR;
			occupiedColor = OCCUPIED_COLOR;
			hoverColor = HOVER_COLOR;
			selectedColor = SELECTED_COLOR;
		}

		BoardForm(String^ FEN) : BoardForm() {
			this->FEN = FEN;
		}

		BoardForm(String^ FEN, bool playerColor) : BoardForm() {
			this->FEN = FEN;
			this->playerColor = playerColor;
		}

		BoardForm(String^ FEN, int Theme, int botElo, int timeControl, bool playerColor, bool movingPlayer) : BoardForm() {
			this->Theme = Theme;
			this->botElo = botElo;
			this->timeControl = timeControl;
			this->playerColor = playerColor;
			this->movingPlayer = movingPlayer;
			this->FEN = FEN;
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~BoardForm() {
			if (components) delete components;
			for (uint8_t i = 0; i < 64; i++) delete[] board[i];
			delete board;
		}

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::CheckBox^ soundCheckBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void) {
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->soundCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Minecraftia", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(712, 412);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 33);
			this->label1->TabIndex = 0;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(710, 92);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(399, 26);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(710, 124);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(399, 40);
			this->button1->TabIndex = 2;
			this->button1->Text = L"set FEN";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &BoardForm::button1_Click);
			// 
			// soundCheckBox
			// 
			this->soundCheckBox->AutoSize = true;
			this->soundCheckBox->Checked = true;
			this->soundCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->soundCheckBox->Font = (gcnew System::Drawing::Font(L"Inter Black", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->soundCheckBox->ForeColor = System::Drawing::Color::White;
			this->soundCheckBox->Location = System::Drawing::Point(710, 196);
			this->soundCheckBox->Name = L"soundCheckBox";
			this->soundCheckBox->Size = System::Drawing::Size(131, 33);
			this->soundCheckBox->TabIndex = 19;
			this->soundCheckBox->Text = L"Sounds";
			this->soundCheckBox->UseVisualStyleBackColor = true;
			this->soundCheckBox->CheckedChanged += gcnew System::EventHandler(this, &BoardForm::soundCheckBox_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Minecraftia", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(703, 323);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(234, 84);
			this->label3->TabIndex = 20;
			this->label3->Text = L"FormattedFEN: \r\n\r\n";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Minecraftia", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(710, 235);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(399, 75);
			this->textBox2->TabIndex = 21;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Minecraftia", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(937, 494);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 33);
			this->label2->TabIndex = 3;
			// 
			// BoardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(28)), static_cast<System::Int32>(static_cast<System::Byte>(28)),
				static_cast<System::Int32>(static_cast<System::Byte>(28)));
			this->ClientSize = System::Drawing::Size(1258, 664);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->soundCheckBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Name = L"BoardForm";
			this->Text = L"ChessBoard";
			this->Load += gcnew System::EventHandler(this, &BoardForm::BoardForm_Load);
			this->Resize += gcnew System::EventHandler(this, &BoardForm::BoardForm_Resize);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	
		private:inline bool isEmpty(uint8_t square) {
			return board[square]->BackgroundImage == nullptr;
		}
		
		private:inline bool checkImg(const uint8_t &square, System::Drawing::Image^ img) {
			return board[square]->BackgroundImage == img;
		}

		private:inline void setImg(const uint8_t &square, System::Drawing::Image^ img) {
			return board[square]->BackgroundImage = img;
		}


		private:std::string toStdString(System::String^ string) {
			std::string output;
			for (uint8_t i = 0; i < string->Length; i++) output += string[i];
			return output;
		}
	
		

		private:void resizeSquares() {
			bool squares = 0; if (playerColor) squares = 1;
			uint8_t counter;
			float lengthScaling = powf(widthScalar*widthScalar * heightScalar*heightScalar,1.0f/4.0f);
			int sqrLength = BOARD_SQR_LENGTH * lengthScaling;

			(playerColor) ? counter = 0 : counter = 56;

			for (int8_t y = 8; y > 0; y--) {
				for (int8_t x = 1; x < 9; x++) {
					if (!playerColor) counter = (((y - 1) << 3) + (x - 1));
					if (squares) board[counter]->BackColor = whiteColor;
					else board[counter]->BackColor = blackColor;
					board[counter]->Location = System::Drawing::Point(BOARD_X_OFFSET + sqrLength * x, BOARD_Y_OFFSET + sqrLength * y);
					board[counter]->Size = System::Drawing::Size(sqrLength, sqrLength);
					board[counter]->BringToFront();
					board[counter]->Refresh();
					if(playerColor) counter++;
					squares = !squares;
				} squares = !squares;
			} this->Invalidate();
		}

		private:void drawSquares() {
			bool squares = 1; if (playerColor) squares = 0;
			uint8_t counter;

			(playerColor) ? counter = 0 : counter = 56;

			for (int8_t y = 8; y > 0; y--) {
				for (int8_t x = 1; x < 9; x++){
					if (!playerColor) counter = (((y - 1) << 3) + (x - 1));
					board[counter]->Tag = Convert::ToString((int)squares);
					if (squares) board[counter]->BackColor = whiteColor; //g->FillRectangle(whiteBrush, BOARD_X_OFFSET + BOARD_SQR_LENGTH * x, BOARD_Y_OFFSET + BOARD_SQR_LENGTH * y, BOARD_SQR_LENGTH, BOARD_SQR_LENGTH);
					else board[counter]->BackColor = blackColor; //g->FillRectangle(blackBrush, BOARD_X_OFFSET + BOARD_SQR_LENGTH * x, BOARD_Y_OFFSET + BOARD_SQR_LENGTH * y, BOARD_SQR_LENGTH, BOARD_SQR_LENGTH);
					board[counter]->Location = System::Drawing::Point(BOARD_X_OFFSET + BOARD_SQR_LENGTH * x, BOARD_Y_OFFSET + BOARD_SQR_LENGTH * y);
					board[counter]->Name = Convert::ToString(x * y);
					board[counter]->Size = System::Drawing::Size(BOARD_SQR_LENGTH, BOARD_SQR_LENGTH);
					board[counter]->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
					board[counter]->BringToFront();
					board[counter]->Refresh();
					if(playerColor) counter++;
					squares = !squares;
				} squares = !squares;
			}
		}

		private:void drawPawnMoves(uint8_t index, Color color) {
			if(index > 0 && index < 64){
				bool pieceColor = 0;
				if (Convert::ToString(board[index]->Tag)[1] == 'P') pieceColor = 1;
					if(pieceColor){
						if (index + 8 < 63 && isEmpty(index+8)) {
							board[index + 8]->BackColor = color;
							if (index > 7 && index < 16 && isEmpty(index + 16)) board[index + 16]->BackColor = color;
						}
						String^ temp = Convert::ToString(board[index]->Tag);
						if ((index & 7) < 7) {
							String^ tag = Convert::ToString(board[index + 9]->Tag);
							if (!isEmpty(index + 9) && temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + 9]->BackColor = captureColor;
							if (index + 9 == enPassantSquare && checkImg(index + 1, blackPawnImage)) board[index + 9]->BackColor = captureColor;
						}
						if ((index & 7) > 0) {
							String^ tag = Convert::ToString(board[index + 7]->Tag);
							if (board[index + 7]->BackgroundImage != nullptr && temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + 7]->BackColor = captureColor;
							if (index + 7 == enPassantSquare && checkImg(index - 1, blackPawnImage)) board[index + 7]->BackColor = captureColor;
						}
					} else {
						if (index - 8 > 0 && isEmpty(index - 8)) {
							board[index - 8]->BackColor = color;
							if (index > 47 && index < 56 && isEmpty(index - 16)) board[index - 16]->BackColor = color;
						}
						String^ temp = Convert::ToString(board[index]->Tag);
						if ((index & 7) > 0) {
							String^ tag = Convert::ToString(board[index - 9]->Tag);
							if (!isEmpty(index - 9) && temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - 9]->BackColor = captureColor;
							if (index - 9 == enPassantSquare && checkImg(index - 1, whitePawnImage)) board[index - 9]->BackColor = captureColor;
						}
						if ((index & 7) < 7) {
							String^ tag = Convert::ToString(board[index - 7]->Tag);
							if (!isEmpty(index - 7) && temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - 7]->BackColor = captureColor;
							if (index - 7 == enPassantSquare && checkImg(index + 1, whitePawnImage)) board[index - 7]->BackColor = captureColor;
						}
					}
			}
		}

		private:void drawKingMoves(uint8_t index, Color color) {
				String^ temp = Convert::ToString(board[index]->Tag);
				if (castlingRights) {
					if (index == 60) {
						if (CHECK_BIT(castlingRights, 2) && checkImg(63, blackRookImage) && isEmpty(62) && isEmpty(61)) {
							board[62]->BackColor = color;
						}

						if (CHECK_BIT(castlingRights, 3) && checkImg(56, whiteRookImage) && isEmpty(57) && isEmpty(58) && isEmpty(59)){
							board[58]->BackColor = color;
						}
					} else if (index == 4) {
						if (CHECK_BIT(castlingRights, 0) && checkImg(7,whiteRookImage) && isEmpty(6) && isEmpty(5)) {
							board[6]->BackColor = color;
						}

						if (CHECK_BIT(castlingRights, 1) && checkImg(0, whiteRookImage) && isEmpty(1) && isEmpty(2) && isEmpty(3)) {
							board[5]->BackColor = color;
						}
					}
				}

				if (index > 7) {
					for (uint8_t i = 9; i >= 7; i--){
						if (((index & 7) == 7 && i == 7) || ((index & 7) == 0 && i == 9)) continue;
						if (board[index - i]->BackgroundImage == nullptr) board[index - i]->BackColor = color;
						else if (temp[temp->Length - 1] != Convert::ToString(board[index - i]->Tag)[Convert::ToString(board[index - i]->Tag)->Length - 1]) board[index - i]->BackColor = captureColor;
					}
				}

				if (index < 56) {
					for (uint8_t i = 9; i >= 7; i--){
						if (  ((index & 7) == 7 && i == 9) || ((index & 7) == 0 && i == 7)  ) continue;
						if (board[index + i]->BackgroundImage == nullptr) board[index + i]->BackColor = color;
						else if (temp[temp->Length - 1] != Convert::ToString(board[index + i]->Tag)[Convert::ToString(board[index + i]->Tag)->Length - 1]) board[index + i]->BackColor = captureColor;
					}
				}

				if ((index & 7) > 0) {
					if (board[index - 1]->BackgroundImage == nullptr) board[index - 1]->BackColor = color;
					else if (temp[temp->Length - 1] != Convert::ToString(board[index - 1]->Tag)[Convert::ToString(board[index - 1]->Tag)->Length - 1]) board[index - 1]->BackColor = captureColor;
				}

				if ((index & 7) < 7) {
					if (board[index + 1]->BackgroundImage == nullptr) board[index + 1]->BackColor = color;
					else if (temp[temp->Length - 1] != Convert::ToString(board[index + 1]->Tag)[Convert::ToString(board[index + 1]->Tag)->Length - 1]) board[index + 1]->BackColor = captureColor;
				}
		}



		//   8/8/8/3kb3/8/4K3/8/1B4B1 w - - 0 1
		private:void drawBishopMoves(uint8_t index, Color color){
			uint8_t column = index & 7;
			uint8_t row = index >> 3;
			if (index > 7) {
				for (uint8_t i = 1; i <= row && i <= column; i++) {
					if (board[index - i * 9]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index - i * 9]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - i * 9]->BackColor = captureColor;
						break;
					}
					board[index - i * 9]->BackColor = color;
				}

				for (uint8_t i = 1; i <= row && i <= 7 - column; i++) {
					if (board[index - i * 7]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index - i * 7]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - i * 7]->BackColor = captureColor;
						break;
					}
					board[index - i * 7]->BackColor = color;
				}
			}
			if (index < 56) {
				for (uint8_t i = 1; i <= 7 - row && i <= column; i++) {
					if (board[index + i * 7]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index + i * 7]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + i * 7]->BackColor = captureColor;
						break;
					}
					board[index + i * 7]->BackColor = color;
				}

				for (uint8_t i = 1; i <= 7 - row && i <= 7 - column; i++) {
					if (board[index + i * 9]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index + i * 9]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + i * 9]->BackColor = captureColor;
						break;
					}
					board[index + i * 9]->BackColor = color;
				}
			}
		}


		//     r6R/8/4r3/3kb3/8/4K3/8/1B4B1 w - - 0 1
		private:void drawRookMoves(uint8_t index, Color pieceColor) {
			uint8_t column = index & 7;
			uint8_t row = index >> 3;
			bool colour = (pieceColor == whiteColor);
				for (uint8_t i = 1; i <= column; i++) {
					if (board[index - i]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index - i]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - i]->BackColor = captureColor;
						break;
					} else board[index - i]->BackColor = legalMoveColor;
				}

				for (uint8_t i = 1; i <= 7-column; i++) {
					if (board[index + i]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index + i]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + i]->BackColor = captureColor;
						break;
					} else board[index + i]->BackColor = legalMoveColor;
				}

				for (uint8_t i = 1; i <= row; i++) {
					if (board[index - i * 8]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index - i * 8]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - i * 8]->BackColor = captureColor;
						break;
					} else board[index - i * 8]->BackColor = legalMoveColor;
				}

				for (uint8_t i = 1; i <= 7 - row; i++) {
					if (board[index + i * 8]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index + i * 8]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + i * 8]->BackColor = captureColor;
						break;
					} else board[index + i * 8]->BackColor = legalMoveColor;
				}
		}

		private:void drawKnightMoves(uint8_t index, Color color) {
			if (color == whiteColor) color = blackColor;
			else if (color == blackColor) color = whiteColor;

			uint8_t knightTest = index  & 7;
			if (knightTest) {
				if (index - 17 >= 0) {
					if (board[index - 17]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index - 17]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - 17]->BackColor = captureColor;
					} else board[index - 17]->BackColor = color;
				}

				if (index + 15 < 64) {
					if (board[index + 15]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index + 15]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + 15]->BackColor = captureColor;
					} else board[index + 15]->BackColor = color;
				}
			}

			if (knightTest > 1) {
				if (index - 10 >= 0) {
					if (board[index - 10]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index - 10]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - 10]->BackColor = captureColor;
					} else board[index - 10]->BackColor = color;
				}

				if (index + 6 < 64) {
					if (board[index + 6]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index + 6]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + 6]->BackColor = captureColor;
						
					} else board[index + 6]->BackColor = color;
				}
			}
			if (knightTest < 6) {
				if (index - 6 >= 0) {
					if (board[index - 6]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index - 6]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - 6]->BackColor = captureColor;
					} else board[index - 6]->BackColor = color;
				}

				if (index + 10 < 64) {
					if (board[index + 10]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index + 10]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + 10]->BackColor = captureColor;
					} else board[index + 10]->BackColor = color;
				}
			}
			if (knightTest < 7) {
				if (index - 15 >= 0) {
					if (board[index - 15]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index - 15]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index - 15]->BackColor = captureColor;
					} else board[index - 15]->BackColor = color;
				}
				if (index + 17 < 64) {
					if (board[index + 17]->BackgroundImage != nullptr) {
						String^ temp = Convert::ToString(board[index]->Tag);
						String^ tag = Convert::ToString(board[index + 17]->Tag);
						if (temp[temp->Length - 1] != tag[tag->Length - 1]) board[index + 17]->BackColor = captureColor;
					} else board[index + 17]->BackColor = color;
				}
			}
		}

		private:void drawPieces(const std::string &FEN) {
			std::string formattedFEN;
			uint8_t i = 0;
			//ѕочаток обробки р€д≥в дошки
			while (FEN[i] != ' ') {
				if (FEN[i] == '/') { i++; continue; }
				switch (FEN[i]) {
					case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':
						for (uint8_t j = 0; j < charToInt<uint8_t>(FEN[i]); j++) formattedFEN += '1'; break;
					default:
						formattedFEN += FEN[i]; break;
				} i++;
			}
			uint8_t counter = 0;
			for (int8_t row = 7; row >= 0; row--) {
				for (int8_t column = 0; column <= 7; column++) {
					int8_t i = (row<<3) + column;
					bool pieceColor = 0;
					switch (formattedFEN[counter]) {
						case 'P': board[i]->BackgroundImage = whitePawnImage;   board[i]->Tag += "P"; pieceColor = 1; break;
						case 'p': board[i]->BackgroundImage = blackPawnImage;   board[i]->Tag += "p"; break;
						case 'N': board[i]->BackgroundImage = whiteKnightImage; board[i]->Tag += "N"; pieceColor = 1; break;
						case 'n': board[i]->BackgroundImage = blackKnightImage; board[i]->Tag += "n"; break;
						case 'B': board[i]->BackgroundImage = whiteBishopImage; board[i]->Tag += "B"; pieceColor = 1; break;
						case 'b': board[i]->BackgroundImage = blackBishopImage; board[i]->Tag += "b"; break;
						case 'R': board[i]->BackgroundImage = whiteRookImage;   board[i]->Tag += "R"; pieceColor = 1; break;
						case 'r': board[i]->BackgroundImage = blackRookImage;   board[i]->Tag += "r"; break;
						case 'Q': board[i]->BackgroundImage = whiteQueenImage;  board[i]->Tag += "Q"; pieceColor = 1; break;
						case 'q': board[i]->BackgroundImage = blackQueenImage;  board[i]->Tag += "q"; break;
						case 'K': board[i]->BackgroundImage = whiteKingImage;   board[i]->Tag += "K"; pieceColor = 1; break;
						case 'k': board[i]->BackgroundImage = blackKingImage;   board[i]->Tag += "k"; break;
						default: board[i]->Tag += "E"; board[i]->BackgroundImage = nullptr; board[i]->Refresh();
					} board[i]->Tag += Convert::ToString(i); board[i]->Tag += ((int)pieceColor).ToString(); counter++;
				}
			}
				
			
		}

		private:void drawBoard(const std::string &fen) {
			drawSquares();
			resizeSquares();
			drawPieces(fen);
		}

		private:void drawLegalMoves(System::Object^ sender) {
			Panel^ panel = safe_cast<Panel^>(sender);
			String^ tag = Convert::ToString(panel->Tag);
			uint8_t index = getPanelIndex(sender);

			if (panel->BackgroundImage) {
				if(panel->BackColor!=selectedColor) panel->BackColor = hoverColor;
				panel->Cursor = System::Windows::Forms::Cursors::Hand;

				switch (tag[1]) {
					case 'P':
					case 'p': 
							  drawPawnMoves(index, legalMoveColor); break;
					case 'N':
					case 'n': 
							  drawKnightMoves(index, legalMoveColor); break;
					case 'B':
					case 'b': 
							  drawBishopMoves(index, legalMoveColor);  break;
					case 'R':
					case 'r': 
							  drawRookMoves(index, legalMoveColor); break;
					case 'Q':
					case 'q':
							  drawBishopMoves(index, legalMoveColor);
							  drawRookMoves(index, legalMoveColor); break;
					case 'K':
					case 'k':
							  drawKingMoves(index, legalMoveColor); break;
				}
			}

			label1->Text = "\n" + tag;
	
		}

		void initializeGame() {
			movingPlayer = game.currentPosition.getMovingPlayer();
			castlingRights = game.currentPosition.getCastlingRights();
			enPassantSquare = game.currentPosition.getEnPassantSquare();

			textBox2->Text = Convert::ToString(game.currentPosition.getWhitePawns());
			label2->Text = "En Passant Index: " + enPassantSquare;
			label2->Text += "\nCastling Rights: ";
			for (uint8_t i = 0; i < 4; i++) label2->Text += CHECK_BIT(castlingRights, i);
		}

		private: void clearAllMoves() {
			bool squares = 1; uint8_t counter = 0;
			for (uint8_t y = 1; y < 9; y++) {
				for (uint8_t x = 1; x < 9; x++) {
					if (squares) board[counter]->BackColor = whiteColor;
					else board[counter]->BackColor = blackColor;
					counter++;
					squares = !squares;
				} squares = !squares;
			}
		}

		private: System::Void BoardForm_Resize(System::Object^ sender, System::EventArgs^ e) {
			if (isLoaded) {
				widthScalar = (float)(this->Width) / (float)(originalFormWidth);
				heightScalar = (float)(this->Height) / (float)(originalFormHeight);
				resizeSquares();
			}
		}

		private: System::Void BoardForm_Load(System::Object^ sender, System::EventArgs^ e) {
			this->Icon = gcnew System::Drawing::Icon("D:\\Chess\\ChessBot\\Board.ico");
			MessageBox::Show("FEN: " + FEN);
			std::string fen = toStdString(FEN);

			game = chessBackend::Game(fen,botElo,timeControl,playerColor);

			initializeGame();

			for (uint8_t i = 0; i < 64; i++) {
				board[i] = gcnew Panel();
				Controls->Add(board[i]);
				board[i]->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowOnly;
				board[i]->AutoSize = true;
				board[i]->Click += gcnew System::EventHandler(this, &BoardForm::square_Click);
				board[i]->MouseEnter += gcnew System::EventHandler(this, &BoardForm::square_MouseEnter);
				board[i]->MouseLeave += gcnew System::EventHandler(this, &BoardForm::square_MouseLeave);
			}

			drawBoard(fen);

			for (uint8_t i = 0; i < 4; i++) {
				promotionButtons[i] = gcnew Panel();
				Controls->Add(promotionButtons[i]);
				promotionButtons[i]->Cursor = System::Windows::Forms::Cursors::Hand;
				promotionButtons[i]->Name = Convert::ToString(i);
				promotionButtons[i]->AutoSize = true;
				promotionButtons[i]->Click += gcnew System::EventHandler(this, &BoardForm::promotion_Click);
				promotionButtons[i]->MouseEnter += gcnew System::EventHandler(this, &BoardForm::promotion_MouseEnter);
				promotionButtons[i]->MouseLeave += gcnew System::EventHandler(this, &BoardForm::promotion_MouseLeave);
				promotionButtons[i]->Hide();
			}

			originalFormWidth = this->Size.Width;
			originalFormHeight = this->Size.Height;

			isLoaded = 1;
			widthScalar = (float)(this->Width) / (float)(originalFormWidth);
			heightScalar = (float)(this->Height) / (float)(originalFormHeight);
		}

		uint8_t getPanelIndex(System::Object^ sender) {
			Panel^ panel = safe_cast<Panel^>(sender);
			String^ tag = Convert::ToString(panel->Tag);
			label1->Text = tag;
			std::string temp;
			for (uint8_t i = 0; i < tag->Length-3; i++) temp += tag[i+2];
			return stringToInt<uint8_t>(temp);
		}

		uint8_t getPanelIndex(Panel^ panel) {
			String^ tag = Convert::ToString(panel->Tag);
			label1->Text = tag;
			std::string temp;
			for (uint8_t i = 0; i < tag->Length - 3; i++) temp += tag[i + 2];
			return stringToInt<uint8_t>(temp);
		}

		String^ getSquareName(uint8_t squareIndex) {
			String^ square;
			switch (squareIndex & 7) { //column
				case 0: square += "a"; break;
				case 1: square += "b"; break;
				case 2: square += "c"; break;
				case 3: square += "d"; break;
				case 4: square += "e"; break;
				case 5: square += "f"; break;
				case 6: square += "g"; break;
				case 7: square += "h"; break;
			} square += Convert::ToString(1 + (squareIndex >> 3));
			return square;
		}

		private: System::Void square_Click(System::Object^ sender, System::EventArgs^ e) {
			Panel^ panel = safe_cast<Panel^>(sender);
			bool capture = (panel->BackColor == captureColor);

			if (capture && sounds || promotionClicked && sounds) promotionSound->Play();
			if (sounds) clickSound->Play();

			if (promotionClicked) {
				for (uint8_t i = 0; i < 4; i++) promotionButtons[i]->Hide();
				promotionClicked = 0;
			} else {			
				textBox2->Text = Convert::ToString(game.currentPosition.getWhitePawns());
				if (isPieceClicked) {
					if ((panel->BackColor == legalMoveColor || capture)) {
						String^ tag = Convert::ToString(board[clickedPieceIndex]->Tag);
						if (tag[tag->Length-1] == ((int)movingPlayer).ToString()[0]) {
							squareFrom = clickedPieceIndex;
							squareTo = getPanelIndex(panel);

							if ((squareTo >> 3) == 0 && Convert::ToString(board[squareFrom]->Tag)[1] == 'p') {
								drawPromotionButtons(squareTo, 0);
							} else if ((squareTo >> 3) == 7 && Convert::ToString(board[squareFrom]->Tag)[1] == 'P') {
								drawPromotionButtons(squareTo, 1);
							} else {
								if (clickedPiece == "K" && squareFrom == 4) {
									if (squareTo == 6) {
										setImg(5,whiteRookImage);
										setImg(7,nullptr);

										board[5]->Tag = "0R50";
										board[7]->Tag = "0E70";

									} else if (squareTo == 2) {
										setImg(3, whiteRookImage);
										setImg(0, nullptr);

										board[3]->Tag = "0R30";
										board[0]->Tag = "0E00";
									}
								} else if (clickedPiece == "K" && squareFrom == 60) {
									if (squareTo == 62) {
										setImg(61, blackRookImage);
										setImg(63, nullptr);

										board[61]->Tag = "1R611";
										board[63]->Tag = "1E630";
									} else if (squareTo == 58) {
										setImg(59, blackRookImage);
										setImg(56, nullptr);

										board[59]->Tag = "1R591";
										board[56]->Tag = "0E560";
									}
								} else if (clickedPiece == "p" && squareTo == enPassantSquare) {
									board[enPassantSquare + 8]->BackgroundImage = nullptr;
									board[enPassantSquare + 8]->Tag = Convert::ToString(board[enPassantSquare + 8]->Tag)[0] + "E" + (enPassantSquare - 8) + "0";
								} else if (clickedPiece == "P" && squareTo == enPassantSquare) {
									board[enPassantSquare - 8]->BackgroundImage = nullptr;
									board[enPassantSquare - 8]->Tag = Convert::ToString(board[enPassantSquare - 8]->Tag)[0] + "E" + (enPassantSquare - 8) + "1";
								}

								chessBackend::Move newMove(game.currentPosition, (uint8_t)squareFrom, (uint8_t)squareTo, pieceToInt(clickedPiece[0]), 0);

								game.makeMove(newMove);

								castlingRights = game.currentPosition.getCastlingRights();
								enPassantSquare = game.currentPosition.getEnPassantSquare();

								label2->Text = "Last move: " + getSquareName(squareFrom) + "to " + getSquareName(squareTo);

								board[squareTo]->BackgroundImage = board[squareFrom]->BackgroundImage;
								board[squareFrom]->BackgroundImage = nullptr;

								board[squareFrom]->Tag = Convert::ToString(board[squareFrom]->Tag)[0] + "E" + squareFrom.ToString() + "0";
								board[squareTo]->Tag = Convert::ToString(board[squareTo]->Tag)[0] + clickedPiece + squareTo.ToString() + ((int)movingPlayer).ToString();
								movingPlayer = !movingPlayer;
							}
						} else label2->Text = "Its not your move!";
					} else {
						label2->Text = "Illegal move!";
						if(sounds) errorSound->Play();
					}
					clearAllMoves();
					isPieceClicked = 0;
					clickedPieceIndex = 0;
					clickedPiece = "E";
				} else {
					drawLegalMoves(sender);
					isPieceClicked = 1;
					clickedPieceIndex = getPanelIndex(sender);
					clickedPiece = ""; clickedPiece += Convert::ToString(board[clickedPieceIndex]->Tag)[1];
					if(board[clickedPieceIndex]->BackgroundImage!=nullptr) board[clickedPieceIndex]->BackColor = selectedColor;
				}
				this->Invalidate();
			}
		}

		private: System::Void square_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
			safe_cast<Panel^>(sender)->Cursor = System::Windows::Forms::Cursors::Default;
			if (isPieceClicked) {
				if (getPanelIndex(sender) == clickedPieceIndex) drawLegalMoves(sender);
			} else drawLegalMoves(sender);
			this->Invalidate();
		}

		private: System::Void square_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
			if(!isPieceClicked) clearAllMoves();
			this->Invalidate();
		}

		private: void drawPromotionButtons(uint8_t index, bool pawnColor) {
			uint8_t column = (index & 7) + 1;
			if (pawnColor) { //якщо б≥лий п≥шак
				uint8_t counter = 0;
				promotionButtons[0]->BackgroundImage = whiteKnightImage;
				promotionButtons[1]->BackgroundImage = whiteBishopImage;
				promotionButtons[2]->BackgroundImage = whiteRookImage;
				promotionButtons[3]->BackgroundImage = whiteQueenImage;

				for (uint8_t i = 1; i < 5; i++) {
					promotionButtons[counter]->Location = System::Drawing::Point(BOARD_X_OFFSET + BOARD_SQR_LENGTH * column, BOARD_Y_OFFSET + BOARD_SQR_LENGTH * i);
					counter++;
				}
			} else { //якщо монтеЌ≈√–о
				uint8_t counter = 0;
				promotionButtons[0]->BackgroundImage = blackKnightImage;
				promotionButtons[1]->BackgroundImage = blackBishopImage;
				promotionButtons[2]->BackgroundImage = blackRookImage;
				promotionButtons[3]->BackgroundImage = blackQueenImage;

				for (uint8_t i = 8; i > 4; i--) {
					promotionButtons[counter]->Location = System::Drawing::Point(BOARD_X_OFFSET + BOARD_SQR_LENGTH * column, BOARD_Y_OFFSET + BOARD_SQR_LENGTH * i);
					counter++;
				}
			}

			

			for (uint8_t i = 0; i < 4; i++) {
				promotionButtons[i]->Show();
				promotionButtons[i]->BorderStyle = BorderStyle::FixedSingle;
				promotionButtons[i]->BackColor = promotionColor;
				promotionButtons[i]->Size = System::Drawing::Size(BOARD_SQR_LENGTH, BOARD_SQR_LENGTH);
				promotionButtons[i]->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
				promotionButtons[i]->BringToFront();
				promotionButtons[i]->Invalidate();
			} this->Invalidate();

			promotionClicked = 1;
		}

		private: System::Void promotion_Click(System::Object^ sender, System::EventArgs^ e) {
			Panel^ button = safe_cast<Panel^>(sender);
			String^ promotionPiece;
			if (squareFrom >> 3) {    // якщо б≥лий п≥шак д≥йшов до к≥нц€ дошки
				switch (button->Name[0]) {
					case '0': board[squareTo]->BackgroundImage = whiteKnightImage; promotionPiece += "N"; break;
					case '1': board[squareTo]->BackgroundImage = whiteBishopImage; promotionPiece += "B"; break;
					case '2': board[squareTo]->BackgroundImage = whiteRookImage;   promotionPiece += "R"; break;
					case '3': board[squareTo]->BackgroundImage = whiteQueenImage;  promotionPiece += "Q"; break;
				}
			} else {    // якщо п≥шак чорний
				switch (button->Name[0]) {
					case '0': board[squareTo]->BackgroundImage = blackKnightImage; promotionPiece += "n"; break;
					case '1': board[squareTo]->BackgroundImage = blackBishopImage; promotionPiece += "b"; break;
					case '2': board[squareTo]->BackgroundImage = blackRookImage;   promotionPiece += "r"; break;
					case '3': board[squareTo]->BackgroundImage = blackQueenImage;  promotionPiece += "q"; break;
				}
			}

			board[squareFrom]->BackgroundImage = nullptr;
			board[squareFrom]->Tag = Convert::ToString(board[squareFrom]->Tag)[0] + promotionPiece + squareFrom.ToString() + "0";
			board[squareTo]->Tag = Convert::ToString(board[squareTo]->Tag)[0] + promotionPiece + squareTo.ToString() + ((int)movingPlayer).ToString();
			
			movingPlayer = !movingPlayer;

			for (uint8_t i = 0; i < 4; i++) promotionButtons[i]->Hide();

		}

		private: System::Void promotion_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
			Panel^ button = safe_cast<Panel^>(sender);
			button->BackColor = selectedColor;
		}

		private: System::Void promotion_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
			Panel^ button = safe_cast<Panel^>(sender);
			button->BackColor = promotionColor;
		}

		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			std::string fen;
			if (textBox1->Text!="") fen = toStdString(Convert::ToString(textBox1->Text));
			else fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

			drawBoard(fen);
			game.eraseGame();
			game = chessBackend::Game(fen, botElo, timeControl, playerColor);

			initializeGame();
			
		}

		private: System::Void soundCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			sounds = !sounds;
		}
	};
}
