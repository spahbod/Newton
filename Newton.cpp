// Newton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int SymbolNewtona(int n,int k);
double DwumianNewtona(double x, double y, int n);

int _tmain(int argc, _TCHAR* argv[]){
	//omp_set_num_threads(4);
	const int size = 100; 
	clock_t start,stop;
	double czasP,czasNP,czas1,czas2;
		double sumP = 0;
	double sumNP = 0;

	for(int index = 0 ; index<size ; index++){	
		start = clock();		
		
			#pragma omp parallel for
			for(int i = 1; i <= 100; i++){
			 DwumianNewtona(100,1000,100);		 
			}
		stop = clock();
		czasP = ((double)(stop - start)) / CLOCKS_PER_SEC;
		sumP = sumP + czasP;

		start = clock();
		for(int i = 1; i <= 100; i++){
			DwumianNewtona(100,1000,100);
		}
		stop = clock();
		czasNP = ((double)(stop - start)) / CLOCKS_PER_SEC;
		sumNP = sumNP+ czasNP;
	}

	cout << "P:"<< sumP/size << "\t" << "NP:" << sumNP/size << endl;
	cout << "Przespieszenie :" << sumNP/sumP << endl;

	int loop = 10000000;
	start = clock();

	for(int i = 0;i<loop;i++)
		SymbolNewtona(10,3);

	for(int i = 0;i<loop;i++)
		SymbolNewtona(10,3);

	for(int i = 0;i<loop;i++)
		SymbolNewtona(10,3);



	stop = clock();
	czas1 = ((double)(stop - start)) / CLOCKS_PER_SEC;

	cout << "Czas 1 :" << czas1 << "\t";

	start = clock();

#pragma omp parallel  sections
{
	#pragma omp section
	for(int i = 0;i<loop;i++)
		SymbolNewtona(10,3);

	#pragma omp section
	for(int i = 0;i<loop;i++)
		SymbolNewtona(10,3);

	#pragma omp section
	for(int i = 0;i<loop;i++)
		SymbolNewtona(10,3);
}


	stop = clock();
	czas2 = ((double)(stop - start)) / CLOCKS_PER_SEC;

	cout << "Czas 2 :" << czas2 <<endl;
	cout << "Przyspieszenie :" << czas1/czas2 <<endl;


	system("PAUSE");
	return 0;
}

int SymbolNewtona(int n, int k){
	int wynik = 1; 
			for(int i = 1; i <= k; i++){
				wynik = wynik * ( n - i + 1 ) / i;      
			} 	
	return wynik;     
}

double DwumianNewtona(double x, double y, int n){ 
	double wynik = 0;
			for(int i = 0; i <= n; i++){
				wynik = wynik + SymbolNewtona(n,i) * pow((double)x,(int)n-i) * pow((double)y,(int)i); 																						 
			}
	return wynik;     
}

