#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
// - тест 5
// создание матрицы 
// mas - указатель на матрицу
// n - количество строк 
// m - количество столбцов
void createMatrix(int*** mas, unsigned n, unsigned m) {
	if ((n > 0) && (m > 0)) {
		(*mas) = new int* [n];
		for (unsigned i = 0; i < n; i++) {
			(*mas)[i] = new int[m];
			for (unsigned j = 0; j < m; j++)
				(*mas)[i][j] = 0;
		}
	}
}

// ввод матрицы с клавиатуры 
// mas -  указатель на матрицу
// n - количество строк 
// m - количество столбцов
void inputMatrix(int*** mas, unsigned n, unsigned m) {
	if (mas == nullptr) createMatrix(mas, n, m);
	cout << "enter matrix, line count = " << n << ", column count = " << m << endl;
	for (unsigned i = 0; i < n; i++) {
		cout << "enter line number " << i << endl;
		for (unsigned j = 0; j < m; j++)
			cin >> (*mas)[i][j];
	}
}

// вывод матрицы на экран 
// mas - матрица
// n - количество строк 
// m - количество столбцов
void outputMatrix(int** mas, unsigned n, unsigned m) {
	if (mas == nullptr) return;
	cout << setw(5);
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = 0; j < m; j++)
			cout << setw(5) << mas[i][j];
		cout << endl;
	}
}

// удаление матрицы
// mas -  указатель на матрицу
// n - количество строк 
void deleteMatrix(int*** mas, unsigned n) {
	if (mas != nullptr)
		for (unsigned i = 0; i < n; i++)
			delete[](*mas)[i];

	mas = nullptr;
}

// нахождение количества чисел с заданным значением,
// хранящихся в заданной строке матрицы
// mas - указатель на матрицу
// n - количество строк
// m - количество столбцов
// value - значение для подсчета
// numRow - номер строки для подсчета количества значений
unsigned countValueInRow(int** mas, unsigned n, unsigned m, int value, unsigned numRow)
{
	if (mas == nullptr) return 0;
	if (numRow < 0 || numRow >= n)
		return 0;
	unsigned count = 0;
	for (unsigned i = 0; i < m; i++)
		count += (mas[numRow][i] == value);
	return count;
}

// нахождение количества чисел с заданным значением,
// // хранящихся в заданном столбце матрицы
// // mas - указатель на матрицу
// // n - количество строк
// // m - количество столбцов
// // value - значение для подсчета
// // numCol - номер столбца для подсчета количества значений
unsigned countValueInCol(int** mas, unsigned n, unsigned m, int value, unsigned numCol) {
	if (mas == nullptr) return 0;
	if (numCol < 0 || numCol >= m) return 0; unsigned count = 0;
	for (unsigned i = 0; i < n; i++)count += (mas[i][numCol] == value);
	return count;
}



// Нахождение матрицы без одной строки и без одного столбца (нужно для нахождения определителя)
// mas - матрица
// n - количество строк и столбцов матрицы
// row - удаляемый ряд
// col - удаляемый столбец
// newmas - новая матрица
void getMatrixWithoutRowAndCol(int** mas, unsigned n, unsigned row, unsigned col, int** newmas) {
	int offsetRow = 0;
	int offsetCol = 0;
	for (int i = 0; i < n - 1; i++) {
		if (i == row) {
			offsetRow = 1;
		}

		offsetCol = 0;
		for (int j = 0; j < n - 1; j++) {
			if (j == col) {
				offsetCol = 1;
			}

			newmas[i][j] = mas[i + offsetRow][j + offsetCol];
		}
	}
}

// Нахождение определителя
// mas - матрица
// n - количество строк и столбцов матрицы
int getDeterminant(int** mas, unsigned n) {
	if (n > 0) {
		int det = 0;
		int scalar = 1;

		if (n == 1) {
			return mas[0][0];
		}

		if (n == 2) {
			return mas[0][0] * mas[1][1] - mas[0][1] * mas[1][0];
		}

		int** newmas = new int* [n - 1];
		for (int i = 0; i < n - 1; i++) {
			newmas[i] = new int[n - 1];
		}

		for (int j = 0; j < n; j++) {
			getMatrixWithoutRowAndCol(mas, n, 0, j, newmas);

			det = det + (scalar * mas[0][j] * getDeterminant(newmas, n - 1));

			scalar = -scalar;
		}

		for (int i = 0; i < n - 1; i++) {
			delete[] newmas[i];
		}
		delete[] newmas;

		return det;
	}
}


// Функция для вывода матрицы в файл
// mas - матрица
// n - количество строк
// m - количество столбцов
// filename - название файла
void outputMatrixToFile(int** mas, unsigned n, unsigned m, const string& filename) {
	ofstream outfile(filename);
	if (mas == nullptr) return;
	if (!outfile.is_open()) {
		cout << "error opening files: " << filename << endl;
		return;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			outfile << mas[i][j] << " ";
		}
		outfile << endl;
	}

	outfile.close();
}

//Сложение двух заданных строк матрицы
//matrix - матрица
//rows - количество строк матрицы
//cols - количество столбцов матрицы
//rowMatrix1 - строка матрицы(куда прибавляем)
//rowMatrix2 - строка матрицы(что прибавляем)
//element - элемент матрицы
void summationRowsMatrix(int*** matrix, size_t rows, size_t cols, size_t rowMatrix1, size_t rowMatrix2) {
	if (matrix == nullptr) {
		return;
	}

	//Проверка входных данных на корректность
	if (rowMatrix1 < 0 || rowMatrix2 < 0 || rows < 0 || cols < 0
		|| rowMatrix2 > rows || rowMatrix1 > rows) {
		std::cout << "Выход за пределы массива" << std::endl;
	}
	else {
		for (int j = 0; j < cols; ++j) {
			(*matrix)[rowMatrix1][j] += (*matrix)[rowMatrix2][j];
		}
	}

	return;
}

//Сложение двух заданных столбцов матрицы
//matrix - матрица
//rows - количество строк матрицы
//cols - количество столбцов матрицы
//colMatrix1 - столбец матрицы(куда прибавляем)
//colMatrix2 - столбец матрицы(что прибавляем)
void summationColsMatrix(int*** matrix, size_t rows, size_t cols, size_t colMatrix1, size_t colMatrix2) {
	if (matrix == nullptr) {
		return;
	}

	//Проверка входных данных на корректность
	if (colMatrix1 < 0 || colMatrix2 < 0 || rows < 0 || cols < 0
		|| colMatrix2 > rows || colMatrix1 > rows) {
		std::cout << "Выход за пределы массива" << std::endl;
	}
	else {
		for (int i = 0; i < rows; ++i) {
			(*matrix)[i][colMatrix1] += (*matrix)[i][colMatrix2];
		}
	}

	return;
}

//Сложение двух матриц
//matrix1 - матрица1(к которой прибавляем)
//rows1 - количество строк матрицы1
//cols1 - количество столбцов матрицы1
//matrix2 - матрица2(которую прибавляем)
//rows2 - количество строк матрицы2
//cols2 - количество столбцов матрицы2
void summationMatrix(int*** matrix1, size_t rows1, size_t cols1, int*** matrix2, size_t rows2, size_t cols2) {

	if (matrix1 == nullptr || matrix2 == nullptr) {
		return;
	}

	//Проверка возможности сложения матриц
	if (rows1 == rows2 && cols1 == cols2) {
		for (int i = 0; i < rows1; ++i) {
			for (int j = 0; j < cols2; ++j) {
				(*matrix1)[i][j] += (*matrix2)[i][j];
			}
		}
	}
	else {
		std::cout << "Матрицы невозможно сложить" << std::endl;
	}

	return;
}

// Умножение строки матрицы на целое число  
// mas - матрица
// rows - количество строк
// columns - количество столбцов
// numRow - номер строки, которую нужно умножить
// num - целое число, на которое умножается строка
// result - изменённая матрица

void multiplyingRowByNumber(int** mas, unsigned rows, unsigned columns, unsigned numRow, int num, int*** result) {
	if (mas == nullptr) return;
	if (numRow < 0) return;

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			if (i == numRow)
				(*result)[i][j] = mas[i][j] * num;
			else
				(*result)[i][j] = mas[i][j];
}
// Умножение столбца матрицы на целое число  
// mas - матрица
// rows - количество строк
// columns - количество столбцов
// numColumns - номер столбца, который нужно умножить
// num - целое число, на которое умножается столбец
// result - изменённая матрица

void multiplyingColumnByNumber(int** mas, unsigned rows, unsigned columns, unsigned numColumn, int num, int*** result) {
	if (mas == nullptr) return;
	if (numColumn < 0) return;

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			if (j == numColumn)
				(*result)[i][j] = mas[i][j] * num;
			else
				(*result)[i][j] = mas[i][j];
}

// Умножение матрицы на целое число  
// mas - матрица
// rows - количество строк
// columns - количество столбцов
// num - целое число, на которое умножается матрица
// result - изменённая матрица

void multiplyingMatrixByNumber(int** mas, unsigned rows, unsigned columns, int num, int*** result) {
	if (mas == nullptr) return;

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			(*result)[i][j] = (mas[i][j]) * num;
}

// количество попарно несовпадающих элементов в двух строках
// firstRow - указатель на первую строку
// secondRow - указатель на вторую строку
// firstSize - кол-во элементов в первой строке
// secondSize - кол-во элементов во второй строке
int countPairwiseDifferentElementsTwoRows(int* firstRow, unsigned firstSize, int* secondRow, unsigned secondSize) {

	unsigned count = 0;

	if (firstRow == nullptr || secondRow == nullptr) return count;

	unsigned cols = min(firstSize, secondSize);

	for (int i = 0; i < cols; i++)
		if (firstRow[i] != secondRow[i]) count++;

	return count;
}

// количество попарно несовпадающих элементов в двух матрицах
// firstMas - указатель на первую матрицу
// secMas - указатель на вторую матрицу
// firstRows - количество строк в первой матрице 
// firstCols - количество столбцов в первой матрице
// secRows - количество строк во второй матрице
// secCols - количество столбцов во второй матрице
int countPairwiseDifferentElementsTwoMatrices(int** firstMas, unsigned firstRows, unsigned firstCols, int** secMas, unsigned secRows, unsigned secCols) {

	unsigned count = 0;

	if (firstMas == nullptr || secMas == nullptr) return 0;

	unsigned rows = min(firstRows, secRows);

	for (int i = 0; i < rows; i++)
		count += countPairwiseDifferentElementsTwoRows(firstMas[i], firstCols, secMas[i], secCols);

	return count;
}

// n - количество строк 
// m - количество столбцов
// num - номер удаляемой строки
int** deleteLine(int** mas, int n, int m, int num) {
	if (n <= num) return mas; // проверка на наличие удаляемой строки в матрице
	int** out = new int* [n - 1]; // создание новой матрицы
	for (int i = 0, k = 0; i < n; i++, k++) {
		if (i == num) k--; // в случае достижения номера удаляемой строки мы пропускаем итерацию
		else {
			out[k] = new int[m]; // создание строки
			for (int j = 0; j < m; j++) { // заполнение элементами матрицы
				out[k][j] = mas[i][j];
			}
		}
	}
	return out;
}


int menu() {
	int result;
	cout << " 1 - createMatrix" << endl;
	cout << " 2 - inputMatrix" << endl;
	cout << " 3 - outputMatrix" << endl;
	cout << " 4 - outputMatrixToFile" << endl;
	cout << " 5 - getDeterminant" << endl;
	cout << " 6 - multiplyingRowByNumber" << endl;
	cout << " 7 - multiplyingColumnByNumber" << endl;
	cout << " 8 - multiplyingMatrixByNumber" << endl;
	cout << " 9 - countValueInRow" << endl;
	cout << "10 - countValueInCol" << endl;

	cout << " 0 - exit" << endl;

	cin >> result;
	return result;
}
// основная программа
int main()
{
	setlocale(0, "");
	int** mas = nullptr, ** mas2 = nullptr, n = 0, m = 0, row, column, number;
	string filename;

	while (1) {

		switch (menu())
		{
		case 1:
			cout << "enter n, m:";
			cin >> n >> m;
			createMatrix(&mas, n, m);
			system("cls");
			cout << "createMatrix - done\n\n";
			break;
		case 2:
			inputMatrix(&mas, n, m);
			system("cls");
			cout << "createMatrix - done\n\n";
			break;
		case 3:
			system("cls");
			outputMatrix(mas, n, m);
			cout << "outputMatrix - done\n\n";
			break;
		case 4:
			cout << "enter filename:";
			cin >> filename;
			outputMatrixToFile(mas, n, m, filename);
			system("cls");
			cout << "outputMatrixToFile - done\n\n";
			break;
		case 5:
			system("cls");
			cout << "getDeterminant=" << getDeterminant(mas, n) << endl;
			break;
		case 6:
			cout << "enter row, number:";
			cin >> row >> number;
			createMatrix(&mas2, n, m);
			multiplyingRowByNumber(mas, n, m, row, number, &mas2);
			system("cls");
			outputMatrix(mas2, n, m);
			break;
		case 7:
			cout << "enter column, number:";
			cin >> column >> number;
			createMatrix(&mas2, n, m);
			multiplyingColumnByNumber(mas, n, m, column, number, &mas2);
			system("cls");
			outputMatrix(mas2, n, m);
			break;
		case 8:
			cout << "enter number:";
			cin >> number;
			createMatrix(&mas2, n, m);
			multiplyingMatrixByNumber(mas, n, m, number, &mas2);
			system("cls");
			outputMatrix(mas2, n, m);
			break;
		case 9:
			cout << "enter row, value:";
			cin >> row>> number;
			system("cls");
			cout<<"countValueInRow="<<countValueInRow(mas, n, m, number, row)<<endl;
			break;
		case 10:
			cout << "enter column, value:";
			cin >> column >> number;
			system("cls");
			cout << "countValueInCol=" << countValueInCol(mas, n, m, number, column) << endl;
		break;		case 0: return 0;
			break;
		}
	}

	deleteMatrix(&mas, n);
	deleteMatrix(&mas2, n);
}

