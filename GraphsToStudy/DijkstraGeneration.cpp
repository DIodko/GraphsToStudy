#include "DijkstraGeneration.h"
#include <math.h>
void DijkstraGeneration::GenerateMatrix(array<array<int>^>^ matrix, int size)
{
	array<int>^ vertices = gcnew array<int>(size);
	array<array<int>^>^ routes = gcnew array<array<int>^>(size);
	Random^ rand = gcnew Random();
	for (int i = 0; i < size; i++) {
		matrix[i] = gcnew array<int>(size);
		vertices[i] = 1;
	}
	//создание маршрутов
	int numOfRoutes = 0;
	int verticesOnRootsAmount = 0;
	for (int i = 0; i < size && verticesOnRootsAmount < size - 2; i++) {
		routes[i] = gcnew array<int>(0);
		numOfRoutes++;
		int j = 0;
		bool routeDone = false;
		while (!routeDone) {
			int probability = rand->Next(0, 100);
			int num = 0;
			if ((probability < 50 && j < 4) || j < size / 3) {
				num = rand->Next(1, size - 1);
				while (vertices[num] == 0)
				{
					num = rand->Next(1, size - 1);
				}
				Array::Resize(routes[i], routes[i]->Length + 1);
				routes[i][j] = num;
				vertices[num] = 0;
				j++;
				verticesOnRootsAmount++;
			}
			if (verticesOnRootsAmount == size - 2 || (probability >= 50 && j >= size / 3 - 1) || j >= 4) {
				Array::Resize(routes[i], routes[i]->Length + 1);
				routes[i][j] = size - 1;
				routeDone = true;
			}
		}
	}

	// отладочный вывод маршрутов
	for (int i = 0; i < numOfRoutes; i++)
	{
		Trace::Write((i + 1) + ": ");
		for (int j = 0; j < routes[i]->Length; j++)
		{
			Trace::Write(routes[i][j] + 1 + " ");
		}
		Trace::WriteLine("");
	}

	//заполнение матрицы
	for (int i = 0; i < numOfRoutes; i++) { // цикл для обхода путей
		matrix[0][routes[i][0]] = rand->Next(1, 15);
		matrix[routes[i][0]][0] = matrix[0][routes[i][0]];
		for (int j = 0; j < routes[i]->Length - 1; j++) { // цикл для обхода пути
			matrix[routes[i][j]][routes[i][j + 1]] = rand->Next(1, 15);
			matrix[routes[i][j + 1]][routes[i][j]] = matrix[routes[i][j]][routes[i][j + 1]];
		}
	}

	if (numOfRoutes == 1) // если один маршрут, добавить случайную связь
	{
		int i = rand->Next(1, size - 2);
		while (matrix[routes[0][0]][routes[0][i]] != 0)
		{
			i = rand->Next(1, size - 2);
		}
		matrix[routes[0][0]][routes[0][i]] = rand->Next(1, 15);
		matrix[routes[0][i]][routes[0][0]] = matrix[routes[0][0]][routes[0][i]];
	}
	else // добавить случайные связи, если несколько маршрутов
	{
		for (int i = 0; i < numOfRoutes; i++) { // типа проход по маршрутам
			int j = 0;
			int addedConnections = 0;
			int routeIndex = 0;
			int vertexIndex = 0;
			int numOfConnections = 4 - numOfRoutes + 1; // для 2 путей будет 3, для 3 будет 2, для 4 будет 1
			while (addedConnections < numOfConnections && j < routes[i]->Length - 1) {
				routeIndex = rand->Next(0, numOfRoutes); // связь с любым маршрутом
				vertexIndex = rand->Next(0, routes[routeIndex]->Length - 1);

				if (matrix[routes[i][j]][routes[routeIndex][vertexIndex]] == 0)
				{
					matrix[routes[i][j]][routes[routeIndex][vertexIndex]] = rand->Next(1, 15);
					matrix[routes[routeIndex][vertexIndex]][routes[i][j]] = matrix[routes[i][j]][routes[routeIndex][vertexIndex]];
					addedConnections++;
				}
				j++;
			}
		}
	}
	//return matrix;
}

void DijkstraGeneration::SolveDijkstra(array<int>^ ways, int size, array<array<int>^>^ matrix)
{
	array<array<int>^>^ correct_ways = gcnew array<array<int>^>(size);
	array<int>^ correct_markers = gcnew array<int>(size);
	array<int>^ markers = gcnew array<int>(size);

	ways[0] = 0;
	markers[0] = 1;

	for (int i = 1; i < size; i++) {
		ways[i] = 1000000;
		markers[i] = 0;
	}
	// Ищем минимальный путь алгоритмом Дейкстры

	int curr_vertex = 0; //текущая вершина
	for (int k = 0; markers[size - 1] == 0; k++) { // заполняем size меток, по одной на каждой итерации
		correct_ways[k] = gcnew array<int>(size);
		for (int j = 0; j < size; j++) { // проходимся по строке в матрице для текущей вершины
			if (matrix[curr_vertex][j] != 0) { // если есть путь
				// если значение пути в вершину больше чем значение пути в эту вершину и из нее в ту то обновляем
				ways[j] = (ways[j] > (ways[curr_vertex] + matrix[curr_vertex][j])) ? ways[curr_vertex] + matrix[curr_vertex][j] : ways[j];
			}
		}
		int min_marker = 1000000;
		for (int i = 0; i < size; i++) { //проходимся по всем вершинам
			if (markers[i] != 1 && ways[i] < min_marker) { // если вершина не помечена постоянной и значение пути в нее минимально помечаем постоянной
				curr_vertex = i;
				min_marker = ways[i];
			}
		}
		ways->CopyTo(correct_ways[k], 0);
		correct_markers[k] = curr_vertex;
		markers[curr_vertex] = 1;
	}
	//return ways;
}

// не должны перезаписывать уже созданное значение, не должны записывать на главную диагональ
// не должно быть больше 4 путей в вершину, если есть путь в 1, не должно быть пути в 20 и наоборот
void DijkstraGeneration::FillRandom(int index, array<array<int>^>^ matrix, int size, array<int>^ amounts)
{
	Random^ rand = gcnew Random();
	int j = rand->Next(0, size);
	while (matrix[index][j] > 0 || index == j || amounts[j] >= 4 || abs(index - j) == size - 1
		|| BetweenFirstLast(index, matrix, size, j))
	{
		j = rand->Next(0, size);
	}
	amounts[j]++;
	amounts[index]++;
	matrix[index][j] = rand->Next(1, 15);
	matrix[j][index] = matrix[index][j];
}

bool DijkstraGeneration::BetweenFirstLast(int index, array<array<int>^>^ matrix, int size, int j)
{
	return (matrix[0][j] > 0 && index == size - 1) ||
		(matrix[size - 1][j] > 0 && index == 0) ||
		(matrix[0][index] > 0 && j == size - 1) ||
		(matrix[size - 1][index] > 0 && j == 0);
}
