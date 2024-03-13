#include <iostream>
#include <fstream>
using namespace std;

struct BMPFileHeaderChar
{
	//zrobic stale dlugosci np. const int T=2;
	char bfType[2];
	unsigned char bfSize[4];
	unsigned char bfReserved1[2];
	unsigned char bfReserved2[2];
	unsigned char bfOffBits[4];
};
struct BMPInfoHeaderChar
{
	//zrobic stale dlugosci np. const int T=2;
	unsigned char biSize[4];
	unsigned char biWidth[4];
	unsigned char biHeight[4];
	unsigned char biPlanes[2];
	unsigned char biBitCount[2];
	unsigned char biCompression[4];
	unsigned char biSizeImage[4];
	unsigned char biXpelsPerMeter[4];
	unsigned char biYpelsPerMeter[4];
	unsigned char biCrlUses[4];
	unsigned char biCrlImportant[4];
};

struct BMPFileHeaderInt
{
	string bfType = {};
	int bfSize = 0;
	int bfReserved1 = 0;
	int bfReserved2 = 0;
	int bfOffBits = 0;
};
struct BMPInfoHeaderInt
{
	int biSize;
	int biWidth;
	int biHeight;
	int biPlanes;
	int biBitCount;
	int biCompression;
	int biSizeImage;
	int biXpelsPerMeter;
	int biYpelsPerMeter;
	int biCrlUses;
	int biCrlImportant;
};

struct sobel
{
	const int S1[3][3] = { {-1, 0, 1},{-2, 0, 2},{-1, 0, 1} };
	const int S2[3][3] = { { 0, 1, 2},{-1, 0, 1},{-2, -1, 0} };
	const int S3[3][3] = { { 1, 2, 1},{ 0, 0, 0},{-1, -2, -1} };
	const int S4[3][3] = { { 2, 1, 0},{ 1, 0, -1},{ 0, -1, -2} };
	const int S5[3][3] = { { 1, 0, -1},{ 2, 0, -2},{ 1, 0, -1} };
	const int S6[3][3] = { { 0, -1, -2},{ 1, 0, -1},{ 2, 1, 0} };
	const int S7[3][3] = { {-1, -2, -1},{ 0, 0, 0},{ 1, 2, 1} };
	const int S8[3][3] = { {-2, -1, 0},{-1, 0, 1},{ 0, 1, 2} };
};

streamoff odczytBfh(ifstream& img, BMPFileHeaderChar& bfh)
{
	img.read(reinterpret_cast<char*>(&bfh.bfType), 2);
	img.read(reinterpret_cast<char*>(&bfh.bfSize), 4);
	img.read(reinterpret_cast<char*>(&bfh.bfReserved1), 2);
	img.read(reinterpret_cast<char*>(&bfh.bfReserved2), 2);
	img.read(reinterpret_cast<char*>(&bfh.bfOffBits), 4);
	return img.tellg();
}
streamoff odczytBih(ifstream& img, BMPInfoHeaderChar& bih, streamoff przesuniecie)
{
	img.seekg(przesuniecie, img.beg);
	img.read(reinterpret_cast<char*>(&bih.biSize), 4);
	img.read(reinterpret_cast<char*>(&bih.biWidth), 4);
	img.read(reinterpret_cast<char*>(&bih.biHeight), 4);
	img.read(reinterpret_cast<char*>(&bih.biPlanes), 2);
	img.read(reinterpret_cast<char*>(&bih.biBitCount), 2);
	img.read(reinterpret_cast<char*>(&bih.biCompression), 4);
	img.read(reinterpret_cast<char*>(&bih.biSizeImage), 4);
	img.read(reinterpret_cast<char*>(&bih.biXpelsPerMeter), 4);
	img.read(reinterpret_cast<char*>(&bih.biYpelsPerMeter), 4);
	img.read(reinterpret_cast<char*>(&bih.biCrlUses), 4);
	img.read(reinterpret_cast<char*>(&bih.biCrlImportant), 4);
	return img.tellg();
}

int zamiana(int liczba, int potega)
{
	return liczba * pow(256, potega);

}
void konwersjaBfh(BMPFileHeaderChar bfh, BMPFileHeaderInt& bfh2)
{
	int wartosc, liczba;

	for (int i = 0; i < 2; i++)
	{
		bfh2.bfType += bfh.bfType[i];
	}

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bfh.bfSize[i];
		wartosc += zamiana(liczba, i);
	}
	bfh2.bfSize = wartosc;

	wartosc = 0;
	for (int i = 0; i < 2; i++)
	{
		liczba = bfh.bfReserved1[i];
		wartosc += zamiana(liczba, i);
	}
	bfh2.bfReserved1 = wartosc;

	wartosc = 0;
	for (int i = 0; i < 2; i++)
	{
		liczba = bfh.bfReserved2[i];
		wartosc += zamiana(liczba, i);
	}
	bfh2.bfReserved1 = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bfh.bfOffBits[i];
		wartosc += zamiana(liczba, i);
	}
	bfh2.bfOffBits = wartosc;
}
void wypisanieBfh(BMPFileHeaderInt bfh)
{
	cout<<endl << "BITMAPFILEHEADER";
	cout << "\nbfType: ";
	cout << bfh.bfType;
	cout << "\nbfSize: ";
	cout << bfh.bfSize;
	cout << "\nbfReserved1:";
	cout << bfh.bfReserved1;
	cout << "\nbfReserved2: ";
	cout << bfh.bfReserved2;
	cout << "\nbfOffBits: ";
	cout << bfh.bfOffBits;
	cout << endl;
}

void konwersjaBih(BMPInfoHeaderChar bih, BMPInfoHeaderInt& bih2)
{
	int wartosc, liczba;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biSize[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biSize = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biWidth[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biWidth = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biHeight[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biHeight = wartosc;

	wartosc = 0;
	for (int i = 0; i < 2; i++)
	{
		liczba = bih.biPlanes[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biPlanes = wartosc;

	wartosc = 0;
	for (int i = 0; i < 2; i++)
	{
		liczba = bih.biBitCount[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biBitCount = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biCompression[i];
		wartosc += zamiana(liczba, i);
		//dopisac rodzaj kompresji (z projektu)
	}
	bih2.biCompression = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biSizeImage[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biSizeImage = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biXpelsPerMeter[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biXpelsPerMeter = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biYpelsPerMeter[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biYpelsPerMeter = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biCrlUses[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biCrlUses = wartosc;

	wartosc = 0;
	for (int i = 0; i < 4; i++)
	{
		liczba = bih.biCrlImportant[i];
		wartosc += zamiana(liczba, i);
	}
	bih2.biCrlImportant = wartosc;
	cout << endl;
}
void wypisanieBih(BMPInfoHeaderInt bih)
{
	cout << "BITMAPINFOHEADER";

	cout << "\nbiSize:";
	cout << bih.biSize;

	cout << "\nbiWidth:";
	cout << bih.biWidth;

	cout << "\nbiHeight:";
	cout << bih.biHeight;

	cout << "\nbiPlanes:";
	cout << bih.biPlanes;

	cout << "\nbiBitCount:";
	cout << bih.biBitCount;

	cout << "\nbiCompression:";
	cout << bih.biCompression;

	cout << "\nbiSizeImage:";
	cout << bih.biSizeImage;

	cout << "\nbiXpelsPerMeter:";
	cout << bih.biXpelsPerMeter;

	cout << "\nbiYpelsPerMeter:";
	cout << bih.biYpelsPerMeter;

	cout << "\nbiCrlUses:";
	cout << bih.biCrlUses;

	cout << "\nbiCrlImportant:";
	cout << bih.biCrlImportant;
	cout << endl;
}

int** tworzenieTablicy(BMPInfoHeaderInt bihDec)
{
	int** tab = new int* [bihDec.biHeight];
	for (int i = 0; i < bihDec.biHeight; i++)
		tab[i] = new int[bihDec.biWidth];

	return tab;
}

void usuwanieTablicy(int** tab, BMPInfoHeaderInt bihDec)
{
	for (int i = 0; i < bihDec.biHeight; i++)
		delete[] tab[i];
	delete[] tab;
}

void wczytywanie(ifstream& img, int** blue, int** green, int** red, int x, int y)
{
	unsigned char pix[3];

	img.read(reinterpret_cast<char*>(pix), 3);
	blue[x][y] = pix[0];
	green[x][y] = pix[1];
	red[x][y] = pix[2];
}

void zerowanie(int** tab, BMPInfoHeaderInt bih)
{
	for (int i = 0; i < bih.biHeight; i++)
	{
		for (int j = 0; j < bih.biWidth; j++)
		{
			tab[i][j] = 0;
		}
	}
}

int normalizacja(int m)
{
	if (m < 0)
		m = 0;
	if (m > 255)
		m = 255;
	return m;
}

void wypisanie(int** b, int** g, int** r, BMPInfoHeaderInt bih)
{
	for (int i = bih.biHeight - 1; i >= 0; i--)
	{
		for (int j = 0; j < bih.biWidth; j++)
		{
			cout << b[i][j] << " ";
			cout << g[i][j] << " ";
			cout << r[i][j] << " | ";
		}
		cout << endl;
	}
}

void zapisDanychBMP(ofstream& img2, int** blue, int** green, int** red, BMPInfoHeaderInt bih, int iloscZer)
{
	int zero = 0;
	unsigned int b, g, r;
	for (int i = bih.biHeight - 1; i >= 0; i--)
	{
		for (int j = 0; j < bih.biWidth; j++)
		{
			b = blue[i][j];
			img2.write((char*)&b, 1);
			g = green[i][j];
			img2.write((char*)&g, 1);
			r = red[i][j];
			img2.write((char*)&r, 1);
		}
		for (int k = 0; k < iloscZer; k++)
		{
			img2.write((const char*)&zero, 1);
		}
	}
}

void przepisanieBFHiBIH(ifstream& img, ofstream& img2, BMPFileHeaderInt bfh)
{
	if (img2.fail())
	{
		cout << "Nie mozna zapisac nowego pliku";
	}
	else
	{
		img.seekg(0, img.beg);
		char znak[1];
		while (img.tellg() < bfh.bfOffBits)
		{
			img.read(znak, 1);
			img2.write(znak, 1);
		}
	}
}

void operatorSobela(int** pix, BMPInfoHeaderInt bih, sobel m, int** pix2)
{
	int m1, m2, m3, m4, m5, m6, m7, m8;
	for (int x = 1; x < bih.biHeight - 1; x++)
	{
		for (int y = 1; y < bih.biWidth - 1; y++)
		{
			m1 = 0; m2 = 0; m3 = 0; m4 = 0; m5 = 0; m6 = 0; m7 = 0; m8 = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m1 += pix[x + i - 1][y + j - 1] * m.S1[i][j];
					m2 += pix[x + i - 1][y + j - 1] * m.S2[i][j];
					m3 += pix[x + i - 1][y + j - 1] * m.S3[i][j];
					m4 += pix[x + i - 1][y + j - 1] * m.S4[i][j];
					m5 += pix[x + i - 1][y + j - 1] * m.S5[i][j];
					m6 += pix[x + i - 1][y + j - 1] * m.S6[i][j];
					m7 += pix[x + i - 1][y + j - 1] * m.S7[i][j];
					m8 += pix[x + i - 1][y + j - 1] * m.S8[i][j];
				}
			}
			m1 = normalizacja(m1);
			m2 = normalizacja(m2);
			m3 = normalizacja(m3);
			m4 = normalizacja(m4);
			m5 = normalizacja(m5);
			m6 = normalizacja(m6);
			m7 = normalizacja(m7);
			m8 = normalizacja(m8);

			pix2[x][y] = (m1 + m2 + m3 + m4 + m5 + m6 + m7 + m8) / 4;
		}
	}
}

int main()
{
	BMPFileHeaderChar bfh;
	BMPInfoHeaderChar bih;
	BMPFileHeaderInt bfhDec;
	BMPInfoHeaderInt bihDec;
	sobel maski;
	streamoff pozycjaKursora;
	string nazwaPliku, nazwaPliku2;
	cout<<"Nazwa pliku: ";
	cin >> nazwaPliku;
	nazwaPliku = nazwaPliku + ".bmp";

	ifstream img(nazwaPliku, ios::in | ios::binary);
	if (!img.is_open())
	{
		cout <<endl<< "Nie mozna otworzyc pliku.";
		return 0;
	}

	pozycjaKursora = odczytBfh(img, bfh);
	konwersjaBfh(bfh, bfhDec);
	wypisanieBfh(bfhDec);

	pozycjaKursora = odczytBih(img, bih, pozycjaKursora);
	konwersjaBih(bih, bihDec);
	wypisanieBih(bihDec);

	int** blue = tworzenieTablicy(bihDec);
	int** green = tworzenieTablicy(bihDec);
	int** red = tworzenieTablicy(bihDec);

	//cout<<endl<<"Nazwa nowego pliku: ";
	//cin >> nazwaPliku2;
	//nazwaPliku2 = nazwaPliku2 + ".bmp";
	nazwaPliku2 = "new.bmp";

	ofstream img2(nazwaPliku2, ios::out | ios::binary | ios::trunc);
	if (!img2.is_open())
	{
		cout <<endl<< "Nie mozna otworzyc pliku 2.";
		return 0;
	}

	img.seekg(bfhDec.bfOffBits, img.beg);
	int zeroweBajty = bihDec.biWidth % 4;
	for (int i = bihDec.biHeight - 1; i >= 0; i--)
	{
		for (int j = 0; j < bihDec.biWidth; j++)
		{
			wczytywanie(img, blue, green, red, i, j);
		}
		unsigned char pix[3];
		img.read(reinterpret_cast<char*>(pix), zeroweBajty);
	}

	int** blue2 = tworzenieTablicy(bihDec);
	int** green2 = tworzenieTablicy(bihDec);
	int** red2 = tworzenieTablicy(bihDec);

	zerowanie(blue2, bihDec);
	zerowanie(green2, bihDec);
	zerowanie(red2, bihDec);

	operatorSobela(blue, bihDec, maski, blue2);
	operatorSobela(green, bihDec, maski, green2);
	operatorSobela(red, bihDec, maski, red2);

	przepisanieBFHiBIH(img, img2, bfhDec);
	zapisDanychBMP(img2, blue2, green2, red2, bihDec, zeroweBajty);

	img.close();
	img2.close();
	cout << endl << "Nowy plik zostal zapisany";

	usuwanieTablicy(blue, bihDec);
	usuwanieTablicy(green, bihDec);
	usuwanieTablicy(red, bihDec);

	usuwanieTablicy(blue2, bihDec);
	usuwanieTablicy(green2, bihDec);
	usuwanieTablicy(red2, bihDec);
}
