#include "GraphsToSolve.h"
#include <math.h>

// находит ответ для алгоритма Демукрона
void GraphsToSolve::SolveDemoucron(array<array<int>^>^ matrix, int size, array<array<int>^>^ levels)
{
	levels[size - 1] = gcnew array<int>(0);
	int addedVerticesAmount = 1;

	for (int levelIndex = 0; levelIndex < size - 1 && addedVerticesAmount != size; levelIndex++)
	{
		levels[levelIndex] = gcnew array<int>(0);
		if (levelIndex == 0) // если первый уровень, помещаю в него первую вершину
		{
			Array::Resize(levels[levelIndex], 1);
			levels[0][0] = 1; // в массиве для первого уровня номер первой вершины
			//Trace::WriteLine("Вершина 1 добавлена в уровень 0");
		}
		else
		{
			int prevLevelIndex = levelIndex - 1;
			for (int i = 0; i < levels[prevLevelIndex]->Length; i++) // цикл обхода всех вершин предыдущего уровня
			{
				int vertexIndex = levels[prevLevelIndex][i] - 1;
				for (int j = 0; j < size - 1; j++) // цикл обхода строки в матрице смежности для вершины предудыщего уровня
				{
					if (matrix[vertexIndex][j] > 0 && vertexIndex != j && !IsInLevels(levels, j, levelIndex + 1)) // учитываем уровень, который строится сейчас, поскольку в него может быть уже добавлена текущая вершина
					{
						AddToLevel(levels, levelIndex, j);
						addedVerticesAmount++;
						if (addedVerticesAmount == size - 1)
						{
							addedVerticesAmount++;
							levels[levelIndex + 1] = gcnew array<int>(0);
							AddToLevel(levels, levelIndex + 1, size - 1);
						}
						//Trace::WriteLine("Вершина " + (j + 1).ToString() + " добавлена в уровень " + levelIndex.ToString());
					}
				}
			}
		}
	}
}

// добавляет вершину на уровень, используется в SolveDemoucron
void GraphsToSolve::AddToLevel(array<array<int>^>^ levels, int levelIndex, int vertexIndex)
{
	int length = levels[levelIndex]->Length;
	Array::Resize(levels[levelIndex], length + 1);
	levels[levelIndex][length] = vertexIndex + 1;
}

// проверяет есть ли вершина в уже построенных уровнях, используется в SolveDemoucron
bool GraphsToSolve::IsInLevels(array<array<int>^>^ levels, int vertexIndex, int curAmountOfLevels)
{
	for (int i = 0; i < curAmountOfLevels; i++)
	{
		for (int j = 0; j < levels[i]->Length; j++)
		{
			if (levels[i][j] == vertexIndex + 1)
				return true;
		}
	}
	return false;
}

// находит ответ для алгоритма Дейкстры
void GraphsToSolve::SolveDijkstra(array<array<int>^>^ matrix, int size, array<array<int>^>^ ways, array<int>^ correctMarkers)
{
	array<int>^ markers = gcnew array<int>(size);
	ways[0] = gcnew array<int>(size);
	
	markers[0] = 1;

	for (int i = 1; i < size; i++) {
		ways[i] = gcnew array<int>(size);
		ways[0][i] = 1000000;
		markers[i] = 0;
	}
	// Ищем минимальный путь алгоритмом Дейкстры
	ways[0][0] = 0;
	correctMarkers[0] = 1;
	markers[0] = 1;
	int curr_vertex = 0; //текущая вершина
	for (int i = 0; i < size; i++) { // заполняем size меток, по одной на каждой итерации
		for (int j = 0; j < size; j++) { // проходимся по строке в матрице для текущей вершины
			if (matrix[curr_vertex][j] != 0) { // если есть путь
				// если значение пути в вершину больше чем значение пути в эту вершину и из нее в ту то обновляем
				ways[i][j] = (ways[i][j] > (ways[i][curr_vertex] + matrix[curr_vertex][j])) ? ways[i][curr_vertex] + matrix[curr_vertex][j] : ways[i][j];
			}
		}
		int min_marker = 1000000;
		for (int j = 0; j < size; j++) { //проходимся по всем вершинам
			if (markers[j] != 1 && ways[i][j] < min_marker) { // если вершина не помечена постоянной и значение пути в нее минимально помечаем постоянной
				curr_vertex = j;
				min_marker = ways[i][j];
			}
		}
		markers[curr_vertex] = 1;
		if (i != size - 1)
		{
			correctMarkers[i + 1] = curr_vertex + 1;
			for (int j = 0; j < size; j++)
			{
				ways[i + 1][j] = ways[i][j];
			}
		}
	}
}

// формирует матрицу в зависимости от аргументов
void GraphsToSolve::GenerateDijkstra(array<array<int>^>^ matrix, int size)
{
	array<array<int>^>^ routes = gcnew array<array<int>^>(size);
	Random^ rand = gcnew Random();
	int maxValue = 15;
	for (int i = 0; i < size; i++) {
		matrix[i] = gcnew array<int>(size);
	}

	//создание маршрутов
	int numOfRoutes = GenerateRoutes(routes, size);

	//заполнение матрицы
	for (int i = 0; i < numOfRoutes; i++) { // цикл для обхода путей
		matrix[0][routes[i][0]] = rand->Next(1, maxValue);
		matrix[routes[i][0]][0] = matrix[0][routes[i][0]];
		for (int j = 0; j < routes[i]->Length - 1; j++) { // цикл для обхода пути
			matrix[routes[i][j]][routes[i][j + 1]] = rand->Next(1, maxValue);
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
		matrix[routes[0][0]][routes[0][i]] = rand->Next(1, maxValue);
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

				if (matrix[routes[i][j]][routes[routeIndex][vertexIndex]] == 0 && routes[i][j] != routes[routeIndex][vertexIndex])
				{
					matrix[routes[i][j]][routes[routeIndex][vertexIndex]] = rand->Next(1, maxValue);
					matrix[routes[routeIndex][vertexIndex]][routes[i][j]] = matrix[routes[i][j]][routes[routeIndex][vertexIndex]];
					addedConnections++;
				}
				j++;
			}
		}
	}
}

void GraphsToSolve::GenerateDemoucron(array<array<int>^>^ matrix, int size)
{
	array<array<int>^>^ routes = gcnew array<array<int>^>(size);
	Random^ rand = gcnew Random();
	for (int i = 0; i < size; i++) {
		matrix[i] = gcnew array<int>(size);
	}

	int numOfRoutes = GenerateRoutes(routes, size);

	//заполнение матрицы
	for (int i = 0; i < numOfRoutes; i++) { // цикл для обхода путей
		matrix[0][routes[i][0]] = 1;
		for (int j = 0; j < routes[i]->Length - 1; j++) { // цикл для обхода пути
			matrix[routes[i][j]][routes[i][j + 1]] = 1;
		}
	}

	if (numOfRoutes == 1) // если один маршрут, добавить случайную связь
	{
		int i = rand->Next(1, size - 2);
		while (matrix[routes[0][0]][routes[0][i]] != 0)
		{
			i = rand->Next(1, size - 2);
		}
		matrix[routes[0][0]][routes[0][i]] = 1;
	}
	else // добавить случайные связи, если несколько маршрутов
	{
		for (int i = 0; i < numOfRoutes; i++) { // типа проход по маршрутам
			int j = 0;
			int addedConnections = 0;
			int routeIndex = 0;
			int vertexIndex = 0;
			int numOfConnections = 4 - numOfRoutes + 1; // для 2 путей будет 3, для 3 будет 2, для 4 будет 1
			while (addedConnections < numOfConnections && j < routes[i]->Length - 1) 
			{
				// блок рисует только на более вершины на следующих уровнях
				routeIndex = rand->Next(0, numOfRoutes); 
				vertexIndex = (j < routes[routeIndex]->Length - 1) ? rand->Next(j, routes[routeIndex]->Length - 1) : -1;
				// рисуем к вершине на текущем уровне
				if (vertexIndex == j)
				{

				}
				else if (vertexIndex != -1 && matrix[routes[i][j]][routes[routeIndex][vertexIndex]] == 0 && routes[i][j] != routes[routeIndex][vertexIndex] && matrix[routes[routeIndex][vertexIndex]][routes[i][j]] == 0)
				{
					matrix[routes[i][j]][routes[routeIndex][vertexIndex]] = 1;
					addedConnections++;
				}
				j++;

				//routeIndex = rand->Next(0, numOfRoutes); // связь с любым маршрутом
				//vertexIndex = rand->Next(0, routes[routeIndex]->Length - 1);

				//if (matrix[routes[i][j]][routes[routeIndex][vertexIndex]] == 0 && routes[i][j] != routes[routeIndex][vertexIndex])
				//{
				//	matrix[routes[i][j]][routes[routeIndex][vertexIndex]] = 1;
				//	matrix[routes[routeIndex][vertexIndex]][routes[i][j]] = matrix[routes[i][j]][routes[routeIndex][vertexIndex]];
				//	addedConnections++;
				//}
				//j++;
			}
		}
	}
}

int GraphsToSolve::GenerateRoutes(array<array<int>^>^ routes, int size)
{
	array<int>^ vertices = gcnew array<int>(size);
	Random^ rand = gcnew Random();
	int numOfRoutes = 0;
	int verticesOnRootsAmount = 0;

	for (int i = 0; i < size; i++) {
		vertices[i] = 1;
	}

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
	return numOfRoutes;
}
