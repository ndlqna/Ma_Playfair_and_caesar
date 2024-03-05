#include "windows.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

#ifdef WIN32
void gotoxy(int x, int y)
{
  COORD cur = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
} 
#else
void gotoxy(int x, int y)
{
  printf("\033[%dG\033[%dd", x+1, y+1);
}
#endif

int textcolor(int Color)
{
  HANDLE h;
  h = GetStdHandle(STD_OUTPUT_HANDLE); 
  return SetConsoleTextAttribute(h, Color);
}

#define CYAN 10
#define YELLOW 14
//n

//Playpair
vector<char> create_playfair_matrix(string key) {
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    vector<char> matrix(25);
    key.erase(remove(key.begin(), key.end(), 'J'), key.end());
    key += alphabet;

    int k = 0;
    for (size_t i = 0; i < key.length(); ++i) {
        if (key[i] != ' ') {
            if (find(matrix.begin(), matrix.end(), key[i]) == matrix.end()) {
                matrix[k++] = key[i];
            }
        }
    }
    return matrix;
}
pair<char, char> encode_pair(vector<char>& matrix, char a, char b) {
    int index1, index2;
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (matrix[i] == a) {
            index1 = i;
        }
        if (matrix[i] == b) {
            index2 = i;
        }
    }
    int row1 = index1 / 5;
    int col1 = index1 % 5;
    int row2 = index2 / 5;
    int col2 = index2 % 5;

    if (row1 == row2) {
        return make_pair(matrix[row1 * 5 + (col1 + 1) % 5], matrix[row2 * 5 + (col2 + 1) % 5]);
    } else if (col1 == col2) {
        return make_pair(matrix[((row1 + 1) % 5) * 5 + col1], matrix[((row2 + 1) % 5) * 5 + col2]);
    } else {
        return make_pair(matrix[row1 * 5 + col2], matrix[row2 * 5 + col1]);
    }
}
pair<char, char> decode_pair(vector<char>& matrix, char a, char b) {
    int index1, index2;
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (matrix[i] == a) {
            index1 = i;
        }
        if (matrix[i] == b) {
            index2 = i;
        }
    }
    int row1 = index1 / 5;
    int col1 = index1 % 5;
    int row2 = index2 / 5;
    int col2 = index2 % 5;

    if (row1 == row2) {
        return make_pair(matrix[row1 * 5 + (col1 + 4) % 5], matrix[row2 * 5 + (col2 + 4) % 5]);
    } else if (col1 == col2) {
        return make_pair(matrix[((row1 + 4) % 5) * 5 + col1], matrix[((row2 + 4) % 5) * 5 + col2]);
    } else {
        return make_pair(matrix[row1 * 5 + col2], matrix[row2 * 5 + col1]);
    }
}

string playfair_cipher(string text, string key, string mode) {
    text.erase(remove(text.begin(), text.end(), ' '), text.end());
    text.erase(remove(text.begin(), text.end(), 'J'), text.end());
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    vector<char> playfair_matrix = create_playfair_matrix(key);

    string result = "";
    if (mode == "encode") {
        for (size_t i = 0; i < text.length(); i += 2) {
            pair<char, char> encoded_pair = encode_pair(playfair_matrix, text[i], text[i + 1]);
            result += encoded_pair.first;
            result += encoded_pair.second;
        }
    } else if (mode == "decode") {
        for (size_t i = 0; i < text.length(); i += 2) {
            pair<char, char> decoded_pair = decode_pair(playfair_matrix, text[i], text[i + 1]);
            result += decoded_pair.first;
            result += decoded_pair.second;
        }
    } else {
        return "Invalid mode";
    }
    return result;
}
void playpair(){
	system("cls");
	cout<<"Tao Ma Hay Giai Ma(T/G):";
	char c;cin>>c;
	if(c == 't'){
		cout<<"Nhap Ma Can Tao: ";
		string plaintext;
		cin.ignore();
		getline(cin,plaintext);
		string key;
		cout<<"Nhap Khoa: ";
		cin.ignore();
		getline(cin,key);
		string encrypted_text = playfair_cipher(plaintext, key, "encode");
    	cout << "Ma Tao La: " << encrypted_text << endl;
	}
	else{
		cout<<"Nhap Ma Can Giai: ";
		string plaintext;
		cin.ignore();
		getline(cin,plaintext);
		string key;
		cout<<"Nhap Khoa: ";
		cin.ignore();
		getline(cin,key);
		string decrypted_text = playfair_cipher(plaintext, key, "decode");
    	cout << "Ma Giai La: " << decrypted_text << endl;
	}
    getch(); 
}
//het
string encryptCaesar(string plaintext, int shift) {
  string ciphertext = "";
  for (int i = 0; i < plaintext.length(); i++) {
    char c = plaintext[i];
    if (isalpha(c)) {
      char base = (islower(c)) ? 'a' : 'A';
      c = (c - base + shift) % 26 + base;
    }
    ciphertext += c;
  }
  return ciphertext;
}

string decryptCaesar(string ciphertext, int shift) {
  return encryptCaesar(ciphertext, 26 - shift);
}

void casaesar() {
	system("cls");
	cout<<"Tao Ma Hay Giai Ma(T/G):";
	char c;cin>>c;
	if(c == 't'){
		string message;
		int shift;
		cout << "Nhap chuoi can tao ma: ";
		cin.ignore();
		getline(cin, message);
		cout << "Nhap so buoc di chuyen (shift): ";
		cin >> shift;
		string encryptedMessage = encryptCaesar(message, shift);
		cout << "Chuoi da ma hoa: " << encryptedMessage << endl;
	}
	else{
		string message;
		int shift;
		cout << "Nhap chuoi can ma hoa: ";
		cin.ignore();
		getline(cin, message);
		cout << "Nhap so buoc di chuyen : ";
		cin >> shift;
		string decryptedMessage = decryptCaesar(message, shift);
		cout << "Chuoi da giai ma la: " << decryptedMessage << endl;
	}
    getch(); 
}
//Viet xau s ra man hinh tai toa do (x,y) voi mau la color
void Write(char *s,int x,int y, int color)
{
  textcolor(color);
  gotoxy(x,y); cout<<s;
  textcolor(15);
}

void Khung(int x1,int y1,int x2,int y2)
{ int x,y;
  gotoxy(x1,y1); cout<<"É";
  gotoxy(x2,y1); cout<<"»";
  gotoxy(x1,y2); cout<<"È";
  gotoxy(x2,y2); cout<<"¼";
  for(x=x1+1;x<x2;x++)
  {
	gotoxy(x,y1); cout<<"Í";
	gotoxy(x,y2); cout<<"Í";
  }
  for(y=y1+1;y<y2;y++)
  {
	gotoxy(x1,y); cout<<"º";
	gotoxy(x2,y); cout<<"º";
  }
}
/*Tao ra menu tai toa do (x0,y0) voi n dong luu trong bien s
chon: dong menu hien thoi (khac mau voi cac dong khac) */
void Ve_menu(int x0,int y0,int chon,int n,char *s[])
{
  system("cls");
  Khung(x0-2,y0-1,x0+30,y0+n);
  for(int i=0;i<n;i++)
	 if(i==chon) Write(s[i],x0,y0+i,CYAN);
	 else Write(s[i],x0,y0+i,YELLOW);
  Write("Copyright (c) 2024 by NGUYEN DUC LEN.",x0-4,y0+n+5,10);
}

int main()
{
  char ch,*st[20]; //Ghi cac dong menu
  system("cls");
  st[0]="Tao Va Giai Ma Playfair.";
  st[1]="Tao Va Giai Ma Caesar.";
  st[2]="Thoat.";
  
  int x0=40,y0=5,chon=0,luuchon,sodong=3,ok=FALSE;
  Ve_menu(x0,y0,chon,sodong,st);
  do
  {
  ch=getch(); //Nhan mot phim
  switch (ch)
	{
		case 72: //phim len
			luuchon=chon;
			chon--;
			if(chon<0) chon=sodong-1;
			Write(st[luuchon],x0,y0+luuchon,YELLOW);
			Write(st[chon],x0,y0+chon,CYAN);
			break;
		case 80://phim xuong
			luuchon=chon;
			chon++;
			if(chon==sodong) chon=0;
			Write(st[luuchon],x0,y0+luuchon,YELLOW);
			Write(st[chon],x0,y0+chon,CYAN);
			break;
		case 13: //phim ENTER
		ok=TRUE; break;
	}
	if (ok==TRUE) //Neu phim ENTER duoc nhan
	{
	  switch (chon)
		{
		 case 0:
			//Baitap0();
			playpair();
			Ve_menu(x0,y0,chon,sodong,st);
			break;
		 case 1:
			casaesar();
			Ve_menu(x0,y0,chon,sodong,st);
			break;
		 case 2: exit(0);
		}
	  ok=FALSE; //tra lai trang thai ENTER chua duoc nhan
	}
  }
  while (ch!=27);//Nhan phim ESC de thoat khoi chuong trinh
}
