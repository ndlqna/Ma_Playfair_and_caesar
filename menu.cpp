#include <bits/stdc++.h>

using namespace std;

typedef struct{
    int hang; // Hàng của vị trí trong ma trận
    int cot; // Cột của vị trí trong ma trận
}viTri;

char matran[5][5]; // Biến toàn cục lưu trữ ma trận 5x5

// Hàm tạo ma trận từ khóa nhập vào
void taoMatran(string khoa)
{
    int coDau[26] = {0}; // Mảng đánh dấu ký tự đã xuất hiện
    int x = 0, y = 0; // Vị trí hiện tại trong ma trận
    for(int i=0; i<khoa.length(); i++)
    {
        if(khoa[i] == 'j') khoa[i] = 'i'; // thay j bằng i
        if(coDau[khoa[i]-'a'] == 0) // Nếu ký tự chưa xuất hiện
        {
            matran[x][y++] = khoa[i]; // Thêm ký tự vào ma trận
            coDau[khoa[i]-'a'] = 1; // Đánh dấu ký tự đã xuất hiện
        }
        if(y==5) x++, y=0; // Nếu đến cuối hàng, sang hàng mới
    }
    for(char ch = 'a'; ch <= 'z'; ch++)
    {
        if(ch == 'j') continue; // không điền j vì j đã được thay bằng i
        if(coDau[ch - 'a'] == 0) // Nếu ký tự chưa xuất hiện
        {
            matran[x][y++] = ch; // Thêm ký tự vào ma trận
            coDau[ch - 'a'] = 1 ; // Đánh dấu ký tự đã xuất hiện
        }
        if(y==5) x++, y=0; // Nếu đến cuối hàng, sang hàng mới
    }
}

// Hàm điều chỉnh bản mã để chuẩn bị mã hóa
string dieuChinhBanMa(string banMa)
{
    for(int i=0; i<banMa.length(); i++)
    {
        if(banMa[i] == 'j') banMa[i] = 'i'; // thay j bằng i
    }
    for(int i=1; i<banMa.length(); i+=2)
    {
        if(banMa[i-1] == banMa[i]) banMa.insert(i, "X"); // Thêm 'X' vào giữa 2 ký tự giống nhau
    }
    if(banMa.length()%2 != 0) banMa += "X"; // Nếu độ dài bản mã lẻ, thêm 'X' vào cuối
    return banMa;
}

// Hàm tìm vị trí của một ký tự trong ma trận
viTri timViTri(char c)
{
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(c == matran[i][j])
            {
                viTri p = {i, j}; // Tạo một viTri với hàng và cột tương ứng
                return p; // Trả về vị trí tìm thấy
            }
        }
    }
}

// Hàm mã hóa bản mã
string maMa(string banMa)
{
    string baMaDuocMa = ""; // Chuỗi lưu trữ bản mã đã được mã hóa
    for(int i=0; i<banMa.length(); i+=2)
    {
        viTri p1 = timViTri(banMa[i]); // Tìm vị trí của ký tự thứ nhất trong cặp
        viTri p2 = timViTri(banMa[i+1]); // Tìm vị trí của ký tự thứ hai trong cặp
        int x1 = p1.hang; int y1 = p1.cot;
        int x2 = p2.hang; int y2 = p2.cot;
        if( x1 == x2 ) // Nếu cặp ký tự cùng hàng
        {
            baMaDuocMa += matran[x1][(y1+1)%5]; // Ký tự thứ nhất trong cặp được mã hóa bằng cách dịch sang phải 1 vị trí
            baMaDuocMa += matran[x2][(y2+1)%5]; // Ký tự thứ hai trong cặp được mã hóa bằng cách dịch sang phải 1 vị trí
        }
        else if( y1 == y2 ) // Nếu cặp ký tự cùng cột
        {
            baMaDuocMa += matran[ (x1+1)%5 ][ y1 ]; // Ký tự thứ nhất trong cặp được mã hóa bằng cách dịch xuống 1 vị trí
            baMaDuocMa += matran[ (x2+1)%5 ][ y2 ]; // Ký tự thứ hai trong cặp được mã hóa bằng cách dịch xuống 1 vị trí
        }
        else // Nếu cặp ký tự không cùng hàng và không cùng cột
        {
            baMaDuocMa += matran[ x1 ][ y2 ]; // Ký tự thứ nhất trong cặp được mã hóa bằng ký tự ở vị trí của ký tự thứ hai
            baMaDuocMa += matran[ x2 ][ y1 ]; // Ký tự thứ hai trong cặp được mã hóa bằng ký tự ở vị trí của ký tự thứ nhất
        }
    }
    return baMaDuocMa;
}

// Hàm giải mã bản mã đã được mã hóa
string giaiMa(string banMaDuocMa)
{
    string banMaGoc = ""; // Chuỗi lưu trữ bản mã gốc sau khi được giải mã
    for(int i=0; i<banMaDuocMa.length(); i+=2) // i được tăng 2 để kiểm tra giá trị cặp
    {
        viTri p1 = timViTri(banMaDuocMa[i]); // Tìm vị trí của ký tự thứ nhất trong cặp
        viTri p2 = timViTri(banMaDuocMa[i+1]); // Tìm vị trí của ký tự thứ hai trong cặp
        int x1 = p1.hang; int y1 = p1.cot;
        int x2 = p2.hang; int y2 = p2.cot;
        if( x1 == x2 ) // Nếu cặp ký tự cùng hàng
        {
            banMaGoc += matran[x1][ --y1<0 ? 4: y1 ]; // Ký tự thứ nhất trong cặp được giải mã bằng cách dịch sang trái 1 vị trí
            banMaGoc += matran[x2][ --y2<0 ? 4: y2 ]; // Ký tự thứ hai trong cặp được giải mã bằng cách dịch sang trái 1 vị trí
        }
        else if( y1 == y2 ) // Nếu cặp ký tự cùng cột
        {
            banMaGoc += matran[ --x1<0 ? 4: x1 ][y1]; // Ký tự thứ nhất trong cặp được giải mã bằng cách dịch lên 1 vị trí
            banMaGoc += matran[ --x2<0 ? 4: x2 ][y2]; // Ký tự thứ hai trong cặp được giải mã bằng cách dịch lên 1 vị trí
        }
        else // Nếu cặp ký tự không cùng hàng và không cùng cột
        {
            banMaGoc += matran[ x1 ][ y2 ]; // Ký tự thứ nhất trong cặp được giải mã bằng ký tự ở vị trí của ký tự thứ hai
            banMaGoc += matran[ x2 ][ y1 ]; // Ký tự thứ hai trong cặp được giải mã bằng ký tự ở vị trí của ký tự thứ nhất
        }
    }
    return banMaGoc;
}

int main()
{
    string banMaGoc;
    cout << "Ban Ma : "; cin >> banMaGoc; // Nhập bản mã gốc
    string khoa;
    cout<<"Nhap Khoa: "; cin >> khoa; // Nhập khóa
    taoMatran(khoa); // Tạo ma trận từ khóa

    // In ra ma trận
    for(int k=0;k<5;k++)
    {
        for(int j=0;j<5;j++)
        {
            cout << matran[k][j] << " ";
        }
        cout << endl;
    }

    cout << "Ban Ma: " << banMaGoc << endl; // In ra bản mã gốc
    string banMaDieuChinh = dieuChinhBanMa(banMaGoc); // Điều chỉnh bản mã để chuẩn bị mã hóa
    cout << "Chinh Lai Ban Ma\t: " << banMaDieuChinh << endl; // In ra bản mã đã được điều chỉnh
    string baMaDuocMa = maMa(banMaDieuChinh); // Mã hóa bản mã
    cout << "Ma Duoc Tao \t: " << baMaDuocMa << endl; // In ra bản mã đã được mã hóa
    string banMaGiaiMaDuoc = giaiMa(baMaDuocMa); // Giải mã bản mã đã được mã hóa
    cout<< "Ma Duoc Giai Ma Lai \t: " << banMaGiaiMaDuoc << endl; // In ra bản mã đã được giải mã
}
