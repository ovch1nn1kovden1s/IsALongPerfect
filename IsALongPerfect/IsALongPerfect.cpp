#include <iostream>

using namespace std;

// перевод строки в целочисленный массив
void convertStrToInt(string str, int* array, int stringSize)
{
	for (int i = 0; i < stringSize; i++)
		array[i] = str[i] - 48;
}

// вывод массива
void outputArray(int* array, int size)
{
	for (int i = 0; i < size; i++)
		cout << array[i];
	cout << endl;
}

// заполнение массива нулями
void arrayZero(int* array, int& size)
{
	for (int i = 0; i < size; i++)
		array[i] = 0;
}

// сдвиг числа в массиве на один индекс
void shift(int* array, int size)
{
	for (int i = 0; i < size - 1; i++)
		array[i] = array[i + 1];
}

// удаление лишних нулей
void deleteZero(int* array, int& size)
{
	int i = 0;
	while ((array[i] == 0) && (i < size))
	{
		shift(array, size);
		size--;
	}
}

// приравнять массивы
void arrayEdual(int* arrayA, int sizeA, int* arrayB, int& sizeB)
{
	sizeB = sizeA;
	for (int i = 0; i < sizeB; i++)
		arrayB[i] = arrayA[i];
}

// сравнение длинных чисел
int comparingNumbers(int* arrayA, int sizeA, int* arrayB, int sizeB)
{
	if (sizeA == sizeB)
	{
		int k;
		for (int i = 0; i < sizeA; i++)
		{
			if (arrayA[i] > arrayB[i])
			{
				k = 1;
				break;
			}
			if (arrayA[i] < arrayB[i])
			{
				k = 2;
				break;
			}
			if (arrayA[i] == arrayB[i])
			{
				k = 0;
			}
		}
		return k;
	}
	if (sizeA > sizeB)
		return 1;
	if (sizeA < sizeB)
		return 2;
}

// сложение чисел A >= B
void comparison(int* arrayA, int& sizeA, int* arrayB, int sizeB)
{
	int sizeC = sizeA + 1;
	int* arrayC = new int[sizeC];
	arrayZero(arrayC, sizeC);
	int j = sizeB - 1, i = sizeA - 1;
	for (int c = sizeC - 1; c >= 0; c--)
	{
		if (i < 0)
			break;
		else
		{
			if (j < 0)
				arrayC[c] += arrayA[i];
			else
				arrayC[c] += arrayA[i] + arrayB[j];
			if (arrayC[c] >= 10)
			{
				arrayC[c - 1] += arrayC[c] / 10;
				arrayC[c] = arrayC[c] % 10;
			}
			j--;
			i--;
		}
	}
	//deleteZero(arrayC, sizeC);
	arrayEdual(arrayC, sizeC, arrayA, sizeA);
}

// умножение длинного числа на короткое, короткое < 10
void multiply(int* array, int& size, int del)
{
	int sizeC = size + 2;
	int* arrayC = new int[sizeC];
	arrayZero(arrayC, sizeC);
	int i = size;
	for (int c = sizeC; c >= 0; c--)
	{
		if (i < 0)
			break;
		else
		{
			arrayC[c] += array[i] * del;
			i--;
		}
		if (arrayC[c] >= 10)
		{
			arrayC[c - 1] += arrayC[c] / 10;
			arrayC[c] = arrayC[c] % 10;
		}
	}
	deleteZero(arrayC, sizeC);
	arrayEdual(arrayC, sizeC, array, size);
}

// вычетание длинных чисел A >= B
void subtracting(int* arrayA, int& sizeA, int* arrayB, int sizeB)
{
	int sizeC = sizeA;
	int* arrayC = new int[sizeC];
	arrayZero(arrayC, sizeC);
	int j = sizeB - 1;
	for (int c = sizeC - 1; c >= 0; c--)
	{
		if (j < 0)
		{
			if (arrayC[c] < 0)
			{
				arrayC[c] += 10;
				arrayC[c - 1]--;
			}
			arrayC[c] += arrayA[c];
		}
		else
		{
			if (arrayA[c] < arrayB[j])
			{
				arrayA[c] += 10;
				arrayC[c - 1]--;
			}
			arrayC[c] += arrayA[c] - arrayB[j];
			j--;
		}
		if (arrayC[c] >= 10)
		{
			arrayC[c - 1] += arrayC[c] / 10;
			arrayC[c] = arrayC[c] % 10;
		}
	}
	deleteZero(arrayC, sizeC);
	arrayEdual(arrayC, sizeC, arrayA, sizeA);
}

// есть ли остаток от деления
int division(int* arrayA, int sizeA, int* arrayB, int sizeB)
{
	int sizeAF = sizeA;
	int* arrayAF = new int[sizeAF];
	arrayEdual(arrayA, sizeA, arrayAF, sizeAF);
	while (true)
	{
		int sizeP = sizeB;
		int* arrayP = new int[sizeP];
		for (int i = 0; i < sizeP; i++)
			arrayP[i] = arrayAF[i];
		if (comparingNumbers(arrayP, sizeP, arrayB, sizeB) == 2)
		{
			sizeP++;
			arrayP[sizeP - 1] = arrayA[sizeB];
		}
		int c = 0;
		int sizeBP = sizeB;
		int* arrayBP = new int[sizeBP];
		arrayEdual(arrayB, sizeB, arrayBP, sizeBP);
		for (int i = 1; i < 10; i++)
		{
			multiply(arrayBP, sizeBP, i);
			if (comparingNumbers(arrayBP, sizeBP, arrayP, sizeP) == 1)
			{
				arrayEdual(arrayB, sizeB, arrayBP, sizeBP);
				c = i - 1;
				break;
			}
			if (i == 9)
				c = 9;
			arrayEdual(arrayB, sizeB, arrayBP, sizeBP);
		}
		multiply(arrayBP, sizeBP, c);
		int* arraySub = new int[sizeAF];
		arrayZero(arraySub, sizeAF);
		if (arrayAF[0] < arrayBP[0])
		{
			int i = 1;
			for (int j = 0; j < sizeBP; j++)
			{
				arraySub[i] = arrayBP[j];
				i++;
			}
		}
		else
		{
			for (int i = 0; i < sizeBP; i++)
				arraySub[i] = arrayBP[i];
		}
		subtracting(arrayAF, sizeAF, arraySub, sizeAF);
		if (comparingNumbers(arrayAF, sizeAF, arrayB, sizeB) == 2)
			break;
	}
	if (sizeAF == 0)
		return 0; // остатка нет
	else
		return 1; // остаток есть
}

// является ли число совершенным
int perfectNumber(int* arrayA, int sizeA)
{
	int k = 0;
	int sizeSumDivs = sizeA;
	int* arraySumDivs = new int[sizeSumDivs];
	arrayZero(arraySumDivs, sizeSumDivs);
	int sizeI = sizeA;
	int* arrayI = new int[sizeI];
	arrayEdual(arrayA, sizeA, arrayI, sizeI);
	int arrayOne[2] = { 0, 1 };
	while (true)
	{
		subtracting(arrayI, sizeI, arrayOne, 2);
		if (arrayI[0] == 0)
		{
			shift(arrayI, sizeI);
			sizeI--;
		}
		if (division(arrayA, sizeA, arrayI, sizeI) == 0)
		{
			comparison(arraySumDivs, sizeSumDivs, arrayI, sizeI);
			if (arraySumDivs[0] == 0)
			{
				shift(arraySumDivs, sizeSumDivs);
				sizeSumDivs--;
			}
		}
		if ((sizeI == 1) && (arrayI[0] == 1))
			break;
	}
	if (comparingNumbers(arrayA, sizeA, arraySumDivs, sizeSumDivs) == 0)
		k = 1; // число совершенное
	return k;
}

int main()
{
	setlocale(LC_ALL, "");
	cout << " ----- ПРОВЕРКА ЧИСЛА НА СОВЕРШЕННОСТЬ -----" << endl;
	cout << endl << "Введите число: ";
	string inputStr;
	cin >> inputStr;
	int numberSize = inputStr.length();
	int* arrayNumber = new int[numberSize];
	convertStrToInt(inputStr, arrayNumber, numberSize);
	if (perfectNumber(arrayNumber, numberSize) == 1)
		cout << "Число является совершенным" << endl;
	else
		cout << "Число не является совершенным" << endl;
	return 0;
}