#include "GraphsToSolve.h"
#include <math.h>

// ������� ����� ��� ��������� ���������
void GraphsToSolve::SolveDemoucron(array<array<int>^>^ matrix, int size, array<array<int>^>^ levels)
{
	levels[size - 1] = gcnew array<int>(0);
	int addedVerticesAmount = 1;

	for (int levelIndex = 0; levelIndex < size - 1 && addedVerticesAmount != size; levelIndex++)
	{
		levels[levelIndex] = gcnew array<int>(0);
		if (levelIndex == 0) // ���� ������ �������, ������� � ���� ������ �������
		{
			Array::Resize(levels[levelIndex], 1);
			levels[0][0] = 1; // � ������� ��� ������� ������ ����� ������ �������
		}
		else
		{
			int prevLevelIndex = levelIndex - 1;
			for (int i = 0; i < levels[prevLevelIndex]->Length; i++) // ���� ������ ���� ������ ����������� ������
			{
				int vertexIndex = levels[prevLevelIndex][i] - 1;
				for (int j = 0; j < size - 1; j++) // ���� ������ ������ � ������� ��������� ��� ������� ����������� ������
				{
					if (matrix[vertexIndex][j] > 0 && vertexIndex != j && !IsInLevels(levels, j, levelIndex + 1) && AccessibleOnlyFromPrevLevel(matrix, levels, prevLevelIndex, j, size)) // ��������� �������, ������� �������� ������, ��������� � ���� ����� ���� ��� ��������� ������� �������
					{
						AddToLevel(levels, levelIndex, j);
						addedVerticesAmount++;
						if (addedVerticesAmount == size - 1)
						{
							addedVerticesAmount++;
							levels[levelIndex + 1] = gcnew array<int>(0);
							AddToLevel(levels, levelIndex + 1, size - 1);
						}
						//Trace::WriteLine("������� " + (j + 1).ToString() + " ��������� � ������� " + levelIndex.ToString());
					}
				}
			}
		}
	}
}

bool GraphsToSolve::AccessibleOnlyFromPrevLevel(array<array<int>^>^ matrix, array<array<int>^>^ levels, int prevLevelIndex, int vertexIndex, int size)
{
	// ���������� �� �������
	for (int i = 0; i < size; i++)
	{
		// ���� � ������� ����� ������� �� �������
		if (matrix[i][vertexIndex] > 0)
		{
			bool existsInLevels = false;
			// ������� ������ ���� ���� �� � ����� ���������� ������� �������
			for (int k = 0; k < prevLevelIndex + 1; k++)
			{
				// ���������, ���� �� i � levels[prevLevelIndex]
				bool existsInLevel = false;
				for (int j = 0; j < levels[k]->Length; j++)
				{
					if (levels[k][j] == i + 1)
						existsInLevel = true;
				}
				existsInLevels = existsInLevel || existsInLevels;
			}
			// ���� ����, ������ � vertexIndex ����� ������� �� ��������
			if (!existsInLevels)
			{
				Trace::WriteLine("� " + (vertexIndex + 1) + " ����� ������� �� �������� " + (i + 1) + ", �������� ��� � ���������� �������");
				return false;
			}
		}
	}
	return true;
}

// ��������� ������� �� �������, ������������ � SolveDemoucron
void GraphsToSolve::AddToLevel(array<array<int>^>^ levels, int levelIndex, int vertexIndex)
{
	int length = levels[levelIndex]->Length;
	Array::Resize(levels[levelIndex], length + 1);
	levels[levelIndex][length] = vertexIndex + 1;
}

// ��������� ���� �� ������� � ��� ����������� �������, ������������ � SolveDemoucron
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

// ������� ����� ��� ��������� ��������
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
	// ���� ����������� ���� ���������� ��������
	ways[0][0] = 0;
	correctMarkers[0] = 1;
	markers[0] = 1;
	int curr_vertex = 0; //������� �������
	for (int i = 0; i < size; i++) { // ��������� size �����, �� ����� �� ������ ��������
		for (int j = 0; j < size; j++) { // ���������� �� ������ � ������� ��� ������� �������
			if (matrix[curr_vertex][j] != 0) { // ���� ���� ����
				// ���� �������� ���� � ������� ������ ��� �������� ���� � ��� ������� � �� ��� � �� �� ���������
				ways[i][j] = (ways[i][j] > (ways[i][curr_vertex] + matrix[curr_vertex][j])) ? ways[i][curr_vertex] + matrix[curr_vertex][j] : ways[i][j];
			}
		}
		int min_marker = 1000000;
		for (int j = 0; j < size; j++) { //���������� �� ���� ��������
			if (markers[j] != 1 && ways[i][j] < min_marker) { // ���� ������� �� �������� ���������� � �������� ���� � ��� ���������� �������� ����������
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

// ��������� ������� � ����������� �� ����������
void GraphsToSolve::GenerateDijkstra(array<array<int>^>^ matrix, int size)
{
	array<array<int>^>^ routes = gcnew array<array<int>^>(size);
	Random^ rand = gcnew Random();
	int maxValue = 15;
	for (int i = 0; i < size; i++) {
		matrix[i] = gcnew array<int>(size);
	}

	//�������� ���������
	int numOfRoutes = GenerateRoutes(routes, size);

	//���������� �������
	for (int i = 0; i < numOfRoutes; i++) { // ���� ��� ������ �����
		matrix[0][routes[i][0]] = rand->Next(1, maxValue);
		matrix[routes[i][0]][0] = matrix[0][routes[i][0]];
		for (int j = 0; j < routes[i]->Length - 1; j++) { // ���� ��� ������ ����
			matrix[routes[i][j]][routes[i][j + 1]] = rand->Next(1, maxValue);
			matrix[routes[i][j + 1]][routes[i][j]] = matrix[routes[i][j]][routes[i][j + 1]];
		}
	}

	if (numOfRoutes == 1) // ���� ���� �������, �������� ��������� �����
	{
		int i = rand->Next(1, size - 2);
		while (matrix[routes[0][0]][routes[0][i]] != 0)
		{
			i = rand->Next(1, size - 2);
		}
		matrix[routes[0][0]][routes[0][i]] = rand->Next(1, maxValue);
		matrix[routes[0][i]][routes[0][0]] = matrix[routes[0][0]][routes[0][i]];
	}
	else // �������� ��������� �����, ���� ��������� ���������
	{
		int numOfConnections = 5 - numOfRoutes; // ��� 2 ����� ����� 3, ��� 3 ����� 2, ��� 4 ����� 1
		for (int i = 0; i < numOfRoutes; i++) { // ���� ������ �� ���������
			int j = 0;
			int addedConnections = 0;
			while (addedConnections < numOfConnections && j < routes[i]->Length - 1) {
				int routeIndex = rand->Next(0, numOfRoutes); // ����� � ����� ���������
				int vertexIndex = rand->Next(0, routes[routeIndex]->Length - 1);

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

	//���������� �������
	for (int i = 0; i < numOfRoutes; i++) { // ���� ��� ������ �����
		matrix[0][routes[i][0]] = 1;
		for (int j = 0; j < routes[i]->Length - 1; j++) { // ���� ��� ������ ����
			matrix[routes[i][j]][routes[i][j + 1]] = 1;
		}
	}

	if (numOfRoutes == 1) // ���� ���� �������, �������� ��������� �����
	{
		int i = rand->Next(1, size - 2);
		while (matrix[routes[0][0]][routes[0][i]] != 0)
		{
			i = rand->Next(1, size - 2);
		}
		matrix[routes[0][0]][routes[0][i]] = 1;
	}
	else // �������� ��������� �����, ���� ��������� ���������
	{
		int numOfConnections = 5 - numOfRoutes; // ��� 2 ����� ����� 3, ��� 3 ����� 2, ��� 4 ����� 1
		array<int>^ directions = gcnew array<int>(size);

		for (int i = 0; i < size; i++)
		{
			directions[i] = rand->Next(0, 2);
		}

		for (int i = 0; i < numOfRoutes; i++) { // ���� ������ �� ���������
			int j = 0;
			int direction = directions[j];
			int addedConnections = 0;
			while (addedConnections < numOfConnections && j < routes[i]->Length - 1) 
			{
				direction = directions[j];
				// ������ � ������� �� ������� ������
				if (rand->Next(0, 2) == 0)
				{
					int routeIndex = rand->Next(0, numOfRoutes);
					int vertexIndex = (j < routes[routeIndex]->Length - 1) ? j : -1;
					// ��� ������ � ���� �������
					if (vertexIndex != -1 &&
						matrix[routes[i][j]][routes[routeIndex][vertexIndex]] == 0 &&
						matrix[routes[routeIndex][vertexIndex]][routes[i][j]] == 0 &&
						routes[i][j] != routes[routeIndex][vertexIndex])
					{
						if (direction)
						{
							Trace::WriteLine("������ ����� �����");
							if (i >= routeIndex)
							{
								Trace::WriteLine("������ �� " + (routes[i][j]) + " � " + (routes[routeIndex][vertexIndex]));
								matrix[routes[i][j]][routes[routeIndex][vertexIndex]] = 1;
							}
							else
							{
								Trace::WriteLine("������ �� " + (routes[routeIndex][vertexIndex]) + " � " + (routes[i][j]));
								matrix[routes[routeIndex][vertexIndex]][routes[i][j]] = 1;
							}
						}
						else
						{
							Trace::WriteLine("������ ������ ����");
							if (i >= routeIndex)
							{
								Trace::WriteLine("������ �� " + (routes[routeIndex][vertexIndex]) + " � " + (routes[i][j]));
								matrix[routes[routeIndex][vertexIndex]][routes[i][j]] = 1;
							}
							else
							{
								Trace::WriteLine("������ �� " + (routes[i][j]) + " � " + (routes[routeIndex][vertexIndex]));
								matrix[routes[i][j]][routes[routeIndex][vertexIndex]] = 1;
							}
						}
						addedConnections++;
					}
				}
				else // ������ � ������� ������
				{
					int routeIndex = rand->Next(0, numOfRoutes);
					int vertexIndex = (j + 1 < routes[routeIndex]->Length - 1) ? rand->Next(j + 1, routes[routeIndex]->Length - 1) : -1;
					if (vertexIndex != -1 && 
							matrix[routes[i][j]][routes[routeIndex][vertexIndex]] == 0 && 
							matrix[routes[routeIndex][vertexIndex]][routes[i][j]] == 0 &&
							routes[i][j] != routes[routeIndex][vertexIndex])
					{
						matrix[routes[i][j]][routes[routeIndex][vertexIndex]] = 1;
						addedConnections++;
					}
				}
				j++;
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

	for (int i = 0; i < size; i++) 
	{
		vertices[i] = 1;
	}

	for (int i = 0; i < size && verticesOnRootsAmount < size - 2; i++) 
	{
		routes[i] = gcnew array<int>(0);
		numOfRoutes++;
		int j = 0;
		bool routeDone = false;
		while (!routeDone) 
		{
			int probability = rand->Next(0, 100);
			int num = 0;
			if ((probability < 50 && j < 4) || j < size / 3) 
			{
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
			if (verticesOnRootsAmount == size - 2 || (probability >= 50 && j >= size / 3 - 1) || j >= 4) 
			{
				Array::Resize(routes[i], routes[i]->Length + 1);
				routes[i][j] = size - 1;
				routeDone = true;
			}
		}
	}
	return numOfRoutes;
}
