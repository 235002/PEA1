#pragma once
#include <iostream>


//Klasa po�wi�cona macierzy s�siedztwa
//Zadania utworzenie macierzy
//Oczdczyt i zapis do pliku
class Matrix
{
public:
	int cities;			//okre�la liczb� miast
	int **matrix;		//Wska�nik do tablicy dwuwymiarowej, b�dzie reprezentacj� macierzy s�siedztwa
	
	Matrix();
	~Matrix();

	int getCities();
	void setCities(int c);

	//int getMatrix(int i, int j);
	void setMatrrix(int cities);

	void addValueToMatrix(int i, int j, int x);
	void showMatrix();
	void showCities();

	void loadFromFile(std::string fileName);
	//void saveToFile(std::string fileName, int **matrix);
	//vector<std::string> split(const std::string& s, char delimiter);

};

