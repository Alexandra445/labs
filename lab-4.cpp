#include <iostream>
#include <cmath>

using namespace std;

int N, M;
int K;

template <typename T>
void PrintMatrix(T** A1, size_t n, size_t m) {
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			if (j != m - 1) {
				cout << A1[i][j] << " ";
			}
			else {
				cout << A1[i][j];
			}
		}
		cout << std::endl;
	}
}

template <typename T>
void MultiplyMatrix(T** a, int64_t** b, int64_t** result, int exp, size_t n, size_t m) {
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			T sum = 0;
			for (size_t k = 0; k < m; ++k) {
				sum += a[i][k] * b[k][j];
			}
			result[i][j] = sum;
		}
	}
}

int main(int argc, const char* argv[]) {
	setlocale(LC_ALL, "RUS");

	bool isHuman = true;

	if (argc > 1 && strcmp(argv[1], "false") == 0) {
		isHuman = false;
	}

	if (isHuman) {
		cout << "Введите N (число строк): " << endl;
	}

	cin >> N;

	if (isHuman) {
		cout << "Введите M (число столбцов): " << endl;
	}

	cin >> M;

	int64_t** A1 = new int64_t * [N]; // A1 хранит указатели на массивы целых чисел типа int64t
	for (int i = 0; i < N; i++) {
		A1[i] = new int64_t[M];
	}

	if (isHuman) {
		cout << "Введите элементы матрицы A1 построчно: " << endl;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> A1[i][j];
		}
	}

	int vubor, x;

	while (true) {

		if (isHuman) {
			cout << "Введите команду (0 - выход, 1 - вывод матрицы A1, 2 - умножение матриц A1 на A2 , 3 - возведение в степень): " << endl;
		}

		cin >> vubor;

		if (vubor == 0) {
			break;
		}

		else if (vubor == 1) {
			if (isHuman) {
				cout << "Матрица A1:" << endl;
				PrintMatrix(A1, N, M);
			}
			else {
				PrintMatrix(A1, N, M);
			}
		}

		else if (vubor == 2) {
			if (isHuman) {
				cout << "Введите K (число столбцов): " << endl;
			}
			cin >> K;

			double** A2 = new double* [M];
			for (int i = 0; i < M; i++) {
				A2[i] = new double[K];
			}
			if (isHuman) {
				cout << "Введите элементы матрицы A2 построчно: " << endl;
			}
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < K; j++) {
					cin >> A2[i][j];
				}
			}

			double** result = new double* [N];
			for (int i = 0; i < N; i++) {
				result[i] = new double[K];
				for (int j = 0; j < K; j++) {
					result[i][j] = 0;
					for (int k = 0; k < M; k++) {
						result[i][j] += A1[i][k] * A2[k][j];
					}
				}
			}
			for (int i = 0; i < N; i++) {
				delete[] A1[i];
				A1[i] = new int64_t[K];
				for (int j = 0; j < K; j++) {
					A1[i][j] = static_cast<int64_t>(result[i][j]);
				}
			}

			M = K;
			for (int i = 0; i < N; i++) {
				delete[] result[i];
			}
			delete[] result;
			for (int i = 0; i < M; i++) {
				delete[] A2[i];
			}
			delete[] A2;
		}

		else if (vubor == 3) {
			if (N != M) {
				cout << "NO" << endl;
			}
			else {
				if (isHuman) {
					cout << "Введите показатель степени x: ";
				}
				cin >> x;

				if (x < 0) {
					if (isHuman) {
						cout << "Показатель степени должен быть натуральным числом" << endl;
					}
				}
				else {
					int64_t** result = new int64_t * [N];
					for (size_t i = 0; i < N; ++i) {
						result[i] = new int64_t[N];
						for (size_t j = 0; j < N; ++j) {
							result[i][j] = (i == j) ? 1 : 0;
						}
					}

					int64_t** temp = new int64_t * [N];
					for (size_t i = 0; i < N; ++i) {
						temp[i] = new int64_t[N];
					}

					while (x > 0) {
						if (x % 2 == 1) {
							MultiplyMatrix(result, A1, temp, N, N, N);
							swap(result, temp);
						}

						MultiplyMatrix(A1, A1, temp, N, N, N);
						swap(A1, temp);

						x /= 2;
					}

					for (int i = 0; i < N; i++) {
						delete[] A1[i];
					}
					delete[] A1;

					A1 = result;

					for (int i = 0; i < N; i++) {
						delete[] temp[i];
					}
					delete[] temp;

					M = N;
				}
			}
		}
	}
	for (int i = 0; i < N; i++) {
		delete[] A1[i];
	}
	delete[] A1;
}
