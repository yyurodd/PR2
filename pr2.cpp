#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

void fillArray(int Array[], int N) {
	srand(time(0));
	for (int i = 0; i < N; i++) {
		Array[i] = rand() % 200 - 100;
		if (Array[i] == -100) {
			Array[i] = 0;
		}
	}
}
void quickSort(int Array[], int end, int start) {
	int mid;
	int s = start;
	int e = end;
	mid = Array[(s + e) / 2];
	while (s < e) {
		while (Array[s] < mid) s++;
		while (Array[e] > mid) e--;
		if (s <= e) {
			swap(Array[s], Array[e]);
			s++;
			e--;
		}
	}
	if (start < e) quickSort(Array, e, start);
	if (s < end) quickSort(Array, end, s);
}

void timeForQuickSort()
{
	time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
	nanoseconds result;
	const int N = 100;
	int array[N]{};
	fillArray(array, N);
	cout << "Неотсортированный массив:: ";
	for (int i = 0; i < N; i++) {
		cout << array[i] << " ";
	}
	cout << "\n\n";

	start = steady_clock::now();
	quickSort(array, (N - 1), 0);
	end = steady_clock::now();

	cout << "Отсортированный массив: ";
	for (int i = 0; i < N; i++) {
		cout << array[i] << " ";
	}
	cout << "\n\n";

	result = duration_cast<nanoseconds>(end - start);
	cout << "Время быстрой сортировки: " << (result.count() / 1000000.0) << " мс" << "\n\n";

}

int binarySearch(int arr[], int value, int start, int end) {
	if (end >= start) {
		int mid = start + (end - start) / 2;

		if (arr[mid] == value) {
			return mid;
		}

		if (arr[mid] > value) {
			return binarySearch(arr, value, start, mid - 1);
		}

		return binarySearch(arr, value, mid + 1, end);
	}

	return -1;
}

void searchMinMax() {
	time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
	nanoseconds result;

	const int N = 100;
	int Array[N]{};
	fillArray(Array, N);
	int mn = Array[0];
	int mx = Array[0];

	start = steady_clock::now();
	for (int i = 1; i < N; i++) {
		mn = min(mn, Array[i]);
		mx = max(mx, Array[i]);
	}
	end = steady_clock::now();

	cout << "Минимальный элемент: " << mn << "\t" << "Максимальный элемент: " << mx << "\n";

	result = duration_cast<nanoseconds>(end - start);
	cout << "Время нахождения минимального и максимального элементов в неотсортированном массиве: " << (result.count() / 1000000.0) << " мс" << "\n";


	quickSort(Array, N - 1, 0);
	for (int i = 0; i < N; i++) {
		cout << Array[i] << " ";
	}
	start = steady_clock::now();
	mn = Array[0];
	mx = Array[N - 1];
	end = steady_clock::now();
	result = duration_cast<nanoseconds>(end - start);
	cout << "Время нахождения минимального и максимального элементов в отсортированном массиве: " << (result.count() / 1000000.0) << " мс" << "\n\n";
}


void averageValue()
{
	time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
	nanoseconds result;

	const int N = 100;
	int unsortedArray[N]{};
	fillArray(unsortedArray, N);
	cout << "Неотсортированный массив: \n";
	for (int i = 0; i < N; i++) {
		cout << unsortedArray[i] << " ";
	}
	cout << "\n";

	int mn = unsortedArray[0];
	int mx = unsortedArray[N - 1];
	int averageValue = round((mx + mn) / 2.0);

	cout << "Среднее значение: " << averageValue << "\n";

	int count = 0;
	cout << "Индексы равные среднему значению в неотсортированном массиве: ";
	start = steady_clock::now();
	for (int i = 0; i < N; i++) {
		if (unsortedArray[i] == averageValue) {
			cout << i << " ";
			count++;
		}
	}
	end = steady_clock::now();

	result = duration_cast<nanoseconds>(end - start);
	cout << "\n" << "Время подсчёта элементов равных среднему значению в неотсортированном массиве: " << (result.count() / 1000000.0) << " мс\n";

	quickSort(unsortedArray, N - 1, 0);
	cout << "\n" << "Отсортированный массив: " << "\n";
	for (int i = 0; i < N; i++) {
		cout << unsortedArray[i] << " ";
	}
	cout << "\n";

	cout << "Индексы равные среднему значению в отсортированном массиве: ";
	start = steady_clock::now();
	count = 0;
	for (int i = 0; i < N; i++) {
		if (unsortedArray[i] == averageValue) {
			cout << i << " ";
			count++;
		}

	}
	end = steady_clock::now();

	result = duration_cast<nanoseconds>(end - start);
	cout << "\n" << "Время подсчёта элементов равных среднему значению в отсортированном массиве: " << (result.count() / 1000000.0) << " мс\n";
	cout << "Количество: " << count << "\n";

}

void lessThanA(int value)
{
	const int N = 100;
	int array[N]{};
	fillArray(array, N);
	quickSort(array, N - 1, 0);
	int count;
	cout << "Отсортированный массив: ";
	for (int i = 0; i < N; i++) {
		cout << i << ": " << array[i] << "    ";
	}
	cout << "\n\n";

	int i = binarySearch(array, value, 0, N - 1), elem = value - 1;

	while (i == -1 && elem >= -99) {
		int i = binarySearch(array, --elem, 0, N - 1);
	}

	for (i = 0; i < N; i++) {
		if (array[i] >= value) {
			break;
		}
	}
	int res;
	if (value < -99) {
		res = 0;
	}
	else {
		res = i;
	}
	cout << "Количество элементов, меньших чем a: " << res << "\n";
}

void moreThanB(int value) {
	const int N = 100;
	int array[N]{};
	fillArray(array, N);
	quickSort(array, N - 1, 0);

	cout << "Отсортированный массив: ";
	for (int i = 0; i < N; i++) {
		cout << i << ": " << array[i] << "    ";
	}
	cout << "\n\n";

	int i = binarySearch(array, value, 0, N - 1), elem = value + 1;
	while (i == -1 && elem <= 99) {
		i = binarySearch(array, ++elem, 0, N - 1);
	}

	for (i; i >= 0; i--) {
		if (array[i] <= value) {
			break;
		}
	}
	int res;
	if (value >= 99) {
		res = 0;
	}
	else if (value <= -101) {
		res = 100;
	}
	else {
		res = 100 - (i + 1);
	}

	cout << "Количество элементов больших чем b: " << res << "\n";
}

void compareTime(int x) {
	time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
	nanoseconds result;

	const int N = 100;
	int array[N] = {};
	fillArray(array, N);
	quickSort(array, N - 1, 0);

	cout << "Отсортированный массив: ";
	for (int i = 0; i < N; i++) {
		cout << array[i] << " ";
	}
	cout << "\n\n";

	bool isThere;
	start = steady_clock::now();
	binarySearch(array, x, 0, N - 1);
	end = steady_clock::now();
	isThere = binarySearch(array, x, 0, N - 1) != -1;

	cout << "Есть ли в массиве число: " << (isThere ? "есть" : "нету") << "\n";

	result = duration_cast<nanoseconds>(end - start);
	cout << "Время бинарного поиска: " << (result.count() / 1000000.0) << " мс" << "\n";

	int i = 0;
	start = steady_clock::now();
	while (array[i] <= x) {
		if (array[i] == x) {
			break;
		}
		i++;
	}
	end = steady_clock::now();

	result = duration_cast<nanoseconds>(end - start);
	cout << "Время перебором: " << (result.count() / 1000000.0) << " мс" << "\n";

}

void replace(int i, int j)
{
	time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
	nanoseconds result;

	const int N = 100;
	int array[N] = {};
	fillArray(array, N);

	for (int k = 0; k < N; k++) {
		if (k == i || k == j) {
			cout << "{" << array[k] << "} ";
		}
		else {
			cout << array[k] << ' ';
		}
	}
	cout << "\n\n";


	start = steady_clock::now();
	swap(array[i], array[j]);
	end = steady_clock::now();

	for (int k = 0; k < N; k++) {
		if (k == i || k == j) {
			cout << "{" << array[k] << "} ";
		}
		else {
			cout << array[k] << ' ';
		}
	}
	cout << "\n";

	result = duration_cast<nanoseconds>(end - start);
	cout << "\n" << "Время перестановки элементов: " << (result.count() / 1000000.0) << " мс\n";

}

//idz start


void idz(int array[], int x) {
	srand(time(0));
	const int N = 100;

	int countOdd = 0, countEven = 0;
	for (int i = 0; i < N; i++) {
		if (i % 2 != 0 && abs(array[i]) % 2 != 0) {
			++countOdd;
		}
		else if (i % 2 == 0 && abs(array[i]) % 2 == 0) {
			++countEven;
		}
	}
	cout << "\nКоличество нечетных элементов имеющих нечетные значения в изначальном: " << countOdd << "\n";
	cout << "Количество четных элементов имеющих четные значения в изначальном массиве: " << countEven << "\n\n";

	int cou = 0;
	int d = 0;
	for (int j = 1; j < 10; j++) {
		for (int i = 0; i < N; i++) {
			if (abs(array[i]) % j == 0) {
				++cou;
			}
		}
		++d;
		cout << "Количество элементов нацело делящихся на " << d << " в изначальном массиве: " << cou << "\n";
		cou = 0;

	}
	cout << "\n";

	for (int i = 0; i < N; i++) {
		if (abs(array[i]) % 2 == 0) {
			array[i] = array[i] - x;
		}
	}

	for (int i = 0; i < N; i++) {
		if (abs(array[i]) % 2 != 0) {
			int k = array[i];
			array[i] = array[i] * (rand() % 10);
			if (array[i] == 0) {
				array[i] = k;
			}
		}
	}

	cout << "Измененный массив: ";
	for (int i = 0; i < N; i++) {
		cout << array[i] << " ";
	}
	cout << "\n\n";

	int countOddM = 0, countEvenM = 0;
	for (int i = 0; i < N; i++) {
		if (i % 2 != 0 && abs(array[i]) % 2 != 0) {
			++countOddM;
		}
		else if (i % 2 == 0 && abs(array[i]) % 2 == 0) {
			++countEvenM;
		}
	}
	cout << "\nКоличество нечетных элементов имеющих нечетные значения в измененном массиве: " << countOddM << "\n";
	cout << "Количество четных элементов имеющих четные значения в измененном массиве: " << countEvenM << "\n\n";

	int couM = 0;
	int dM = 0;
	for (int j = 1; j < 10; j++) {
		for (int i = 0; i < N; i++) {
			if (abs(array[i]) % j == 0) {
				++couM;
			}
		}
		++dM;
		cout << "Количество элементов нацело делящихся на " << dM << " в измененном массиве: " << couM << "\n";
		couM = 0;

	}
	cout << "\n";
}

//idz end

void launch(char task) {
	switch (task) {
	case '1':
		timeForQuickSort();
		break;
	case '2':
		searchMinMax();
		break;
	case '3':
		averageValue();
		break;
	case '4':
		int a;
		cout << "Введите число a: ";
		cin >> a;
		cout << "\n";
		lessThanA(a);
		break;
	case '5':
		int b;
		cout << "Введите число b: ";
		cin >> b;
		cout << "\n";
		moreThanB(b);
		break;
	case '6':
		int n;
		cout << "Введите искомое число: ";
		cin >> n;
		cout << "\n";
		compareTime(n);
		break;
	case '7':
		int i, j;
		cout << "Введите индексы заменяемых элементов(i, j): ";
		cin >> i >> j;
		cout << "\n";
		if ((i > 99 || i < 0) || (j > 99 || j < 0)) {
			cout << "Неверный ввод.\n";
		}
		else {
			replace(i, j);
		}
		break;
	case '8':
		const int N = 100;
		int array[N] = {};
		int x;
		fillArray(array, N);
		cout << "Массив: " << "\n";
		for (int i = 0; i < N; i++) {
			cout << array[i] << " ";
		}
		cout << "\nВведите значение на которое будут уменьшены все четные элементы: ";
		cin >> x;
		idz(array, x);
	}
}

int main() {
	setlocale(0, "");
	cout << "1) Отсортировать массив быстрой сортировкой (от меньшего к большему). Определить время, затраченное на сортировку.\n"
		<< "2) Найти максимальный и минимальный элемент массива. Подсчитать время поиска этих элементов в отсортированном массиве и неотсортированном.\n"
		<< "3) Вывести среднее значение (если необходимо, число нужно округлить) максимального и минимального значения в отсортированном и неотсортированном.\nВывести индексы всех элементов, которые равны этому значению, и их количество. Вывести время поиска.\n"
		<< "4) Вывести количество элементов в отсортированном массиве, которые меньше числа a, которое инициализируется пользователем.\n"
		<< "5) Вывести количество элементов в отсортированном массиве, которые больше числа b, которое инициализируется пользователем.\n"
		<< "6) Вывести информацию о том, есть ли введенное пользователем число в отсортированном массиве.\n Реализация алгоритма бинарного поиска. Сравнение скорости его работы с обычным перебором. (*)\n"
		<< "7) Поменять местами элементы массива, индексы которых вводит пользователь. Вывести скорость обмена.\n"
		<< "8) ИДЗ: Уменьшить каждый четный элемент на введенное значение, каждый нечетный элемент умножить на случайную величину от 1 до 9,\n вывести на экран сколько четных элементов имеют четные значения,\n сколько нечетных элементов имеют нечетные значения,\n вывести количество элементов, которые нацело делятся на числа от 1 до 9.\n"
		<< "0) Чтобы выйти\n";

	char task;
	while (true) {
		cout << "Введите номер задания: ";
		cin >> task;
		if (task == '0') {
			break;
		}
		else {
			launch(task);
		}
		
	}
	return 0;
}
