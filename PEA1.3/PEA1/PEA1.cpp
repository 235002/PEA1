// PEA1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include "Library.cpp"
#include "Matrix.h"
#include "DynamicProgramming.h"
#include "BruteForce.h"
using namespace std;

LARGE_INTEGER startTimer()
{
	LARGE_INTEGER start;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return start;
}
LARGE_INTEGER endTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return stop;
}

string fileNames[7] = { "test0.txt", "test1.txt", "test10.txt" ,  "test13.txt", "test14.txt", "test15.txt", "test17.txt" };


int main()
{
	LARGE_INTEGER performanceCountStart, performanceCountEnd;
	Matrix *matrix = new Matrix();

	char option;
	string fileName;

	do
	{
		cout << endl;
		cout << "===== MENU =====" << endl;
		cout << "1. Wczytaj graf z pliku" << endl;
		cout << "2. Wyswietl graf w postaci macierzy" << endl;
		cout << "3. TSP - przeglad zupelny" << endl;
		cout << "4. TSP - programowanie dynamiczne" << endl;
		cout << "5. Test" << endl;
		cout << "0. Wyjscie z programu" << endl;
		cout << "Podaj opcje: ";
		cin >> option;

		switch (option)
		{
			case '1': {
				system("CLS");
				cout << "Podaj nazwe pliku: ";
				cin >> fileName;
				matrix->loadFromFile(fileName);
			}break;

			case '2': {
				system("CLS");
				cout << "Macierz z danymi: " << endl;
				matrix->showCities();
				matrix->showMatrix();
			}break;

			case '3': {
				system("CLS");
				BruteForce *bf = new BruteForce();
				cout << "Wybierz wierzcholek poczatkowy: ";
				cin >> bf->v0;
				cout << endl << "Rozpoczynam przeglad zupelny." << endl;

				performanceCountStart = startTimer();

				bf->przegladZupelny(*matrix, bf->v0);

				performanceCountEnd = endTimer(); //zapamiętujemy koniec czasu
				double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

				cout << endl << "Czas wykonania: " << tm << " [us]" << endl;
				delete bf;
			}break;

			case '4': {
				system("CLS");
				int v;
				cout << "Wybierz wierzcholek poczatkowy: ";
				cin >> v;
				cout << endl << "Rozpoczynam rozwiazywanie programowaniem dynamicznym." << endl;

				performanceCountStart = startTimer();

				DynamicProgramming	*dp = new DynamicProgramming(*matrix, v);
							   				 			  
				performanceCountEnd = endTimer(); //zapamiętujemy koniec czasu

				cout << "Najlepsza sciezka: ";
				dp->showPath();					cout << endl;
				dp->showCost();

				double tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;

				cout << endl << "Czas wykonania: " << tm << " [us]" << endl;

				delete dp;
			}break;

			case '5': {
				fstream file;
				int repeats = 100;
				int fileNumber = 7;
				double tm, avgTime;
				double totalTime = 0;

				file.open("wyniki2.txt", std::ios::out);
				if (file.good())
				{
					//TEST BRUTE FORCE
					BruteForce *bf = new BruteForce();
					cout << endl << endl << endl << "_________________________________________________" << endl;
					cout << "Wykonyawnie testu dla przegladu zupelnego" << endl;
					file << "Wykonyawnie testu dla przegladu zupelnego" << endl;
					for (int i = 0; i < fileNumber; i++)
					{
						cout << "==================================================" << endl;
						cout << "Wykonywanie testu dla pliku: " << fileNames[i] << endl;
						matrix->loadFromFile(fileNames[i]);
						matrix->showCities();
						matrix->showMatrix();

						for (int i = 0; i < repeats; i++)
						{
							performanceCountStart = startTimer();

							bf->przegladZupelny(*matrix, 0);

							performanceCountEnd = endTimer(); //zapamiętujemy koniec czasu
							tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
							totalTime = totalTime + tm;
							cout << endl << "Czas wykonania: " << tm << " [us]" << endl;
						}

						avgTime = totalTime / repeats;

						cout << endl << "Sredni czas wykonania: " << avgTime << " [us]" << endl;
						file << "Wynik dla  pliku: " << fileNames[i] << "   Średni czas wykonania: " << avgTime << " [us] " << endl;
						cout << "==================================================" << endl;
					}
					delete bf;
					cout << "_________________________________________________" << endl;


					tm = totalTime = avgTime = 0;

					//TEST DYNAMIC PROGRAMMING
					cout << "_________________________________________________" << endl;
					cout << "Wykonyawnie testu dla programowania dynamicznego" << endl;
					file << "Wykonyawnie testu dla programowania dynamicznego" << endl;
					for (int i = 0; i < fileNumber; i++)
					{
						cout << "==================================================" << endl;
						cout << "Wykonywanie testu dla pliku: " << fileNames[i] << endl;
						matrix->loadFromFile(fileNames[i]);
						matrix->showCities();
						matrix->showMatrix();

						for (int i = 0; i < repeats; i++)
						{
							performanceCountStart = startTimer();

							DynamicProgramming *dp = new DynamicProgramming(*matrix, 0);

							performanceCountEnd = endTimer(); //zapamiętujemy koniec czasu

							cout << "Najlepsza sciezka: ";
							dp->showPath();					cout << endl;
							cout << "Koszt sciezki: ";
							dp->lowestCost;					cout << endl;

							tm = performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
							totalTime = totalTime + tm;
							cout << endl << "Czas wykonania: " << tm << " [us]" << endl;
							delete dp;
						}
						avgTime = totalTime / repeats;

						cout << endl << "Sredni czas wykonania: " << avgTime << " [us]" << endl;
						file << "Wynik dla pliku: " << fileNames[i] << "   Średni czas wykonania: " << avgTime << " [us] " << endl;
						cout << "==================================================" << endl;
					}
					cout << "_________________________________________________" << endl;
					cout << "========|W Y K O N A N O  W S Z Y S T K I E  T E S T Y|========" << endl;
					file.close();
				}
				else
				{
					cout << "Nie udało się otworzyć pliku do zapisu danych!" << endl;
				}

			}break;

			default:
				system("CLS");
				cout << "Nie ma takiej opcji!" << endl;
				break;
		}
	} while (option != '0');

	delete matrix;
	return 0;
}

