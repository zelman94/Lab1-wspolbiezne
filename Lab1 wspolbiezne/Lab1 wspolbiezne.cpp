// Lab1 wspolbiezne.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include "MatrixCalculator.h"
#include <cstring>

int main()
{
	srand(time(NULL));
	MatrixCalculator calc(5);
	calc.multiplyMatrixes();
	calc.show();
	std::cin.get();
}
