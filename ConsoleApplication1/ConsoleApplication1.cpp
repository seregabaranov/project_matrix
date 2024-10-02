#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
// -
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
void inputMatrix(int *** mas, unsigned n, unsigned m) {
	if (mas == nullptr) createMatrix(mas, n, m);
	cout << "enter matrix, line count = " << n << ", column count = "<< m << endl;
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
	if (mas!=nullptr) 
		for (unsigned i = 0; i < n; i++)
		delete[] (*mas)[i];
	
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
int getDeterminant(int **mas, unsigned n) {
    if (n > 0){
        int det = 0;
        int scalar = 1; 
        
        if(n == 1) {
            return mas[0][0];
        }

        if(n == 2) {
            return mas[0][0]*mas[1][1] - mas[0][1]*mas[1][0];
        }
        
        int **newmas = new int*[n-1];
        for(int i = 0; i < n-1; i++) {
            newmas[i] = new int[n-1];
        }

        for(int j = 0; j < n; j++) {
            getMatrixWithoutRowAndCol(mas, n, 0, j, newmas);

            det = det + (scalar * mas[0][j] * getDeterminant(newmas, n-1));

            scalar = -scalar;
        }

        for(int i = 0; i < n-1; i++) {
            delete [] newmas[i];
        }
        delete [] newmas;
        
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



// основная программа
int main()
{
	int** mas = nullptr, n = 4, m = 4;

	createMatrix(&mas, n, m);
	inputMatrix(&mas, n, m);
	outputMatrix(mas, n, m);
	deleteMatrix(&mas, n);
}

