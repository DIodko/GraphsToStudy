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
	//�������� ���������
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

	// ���������� ����� ���������
	for (int i = 0; i < numOfRoutes; i++)
	{
		Trace::Write((i + 1) + ": ");
		for (int j = 0; j < routes[i]->Length; j++)
		{
			Trace::Write(routes[i][j] + 1 + " ");
		}
		Trace::WriteLine("");
	}

	//���������� �������
	for (int i = 0; i < numOfRoutes; i++) { // ���� ��� ������ �����
		matrix[0][routes[i][0]] = rand->Next(1, 15);
		matrix[routes[i][0]][0] = matrix[0][routes[i][0]];
		for (int j = 0; j < routes[i]->Length - 1; j++) { // ���� ��� ������ ����
			matrix[routes[i][j]][routes[i][j + 1]] = rand->Next(1, 15);
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
		matrix[routes[0][0]][routes[0][i]] = rand->Next(1, 15);
		matrix[routes[0][i]][routes[0][0]] = matrix[routes[0][0]][routes[0][i]];
	}
	else // �������� ��������� �����, ���� ��������� ���������
	{
		for (int i = 0; i < numOfRoutes; i++) { // ���� ������ �� ���������
			int j = 0;
			int addedConnections = 0;
			int routeIndex = 0;
			int vertexIndex = 0;
			int numOfConnections = 4 - numOfRoutes + 1; // ��� 2 ����� ����� 3, ��� 3 ����� 2, ��� 4 ����� 1
			while (addedConnections < numOfConnections && j < routes[i]->Length - 1) {
				routeIndex = rand->Next(0, numOfRoutes); // ����� � ����� ���������
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
}

void DijkstraGeneration::SolveDijkstra(array<int>^ ways, int size, array<array<int>^>^ matrix)
{
	array<int>^ correct_markers = gcnew array<int>(size);
	array<int>^ markers = gcnew array<int>(size);

	ways[0] = 0;
	markers[0] = 1;

	for (int i = 1; i < size; i++) {
		ways[i] = 1000000;
		markers[i] = 0;
	}
	// ���� ����������� ���� ���������� ��������
	correct_markers[0] = 0;
	markers[0] = 1;
	ways[0] = 0;
	Trace::WriteLine("������� " + 0 + " ������� ����������");
	Trace::Write("������ ����� �� �������� " + 0 + ": ");
	for (int j = 0; j < size; j++)
	{
		Trace::Write(ways[j] + " ");
	}
	Trace::WriteLine("");
	int curr_vertex = 0; //������� �������
	for (int i = 1; i < size; i++) { // ��������� size �����, �� ����� �� ������ ��������
		for (int j = 0; j < size; j++) { // ���������� �� ������ � ������� ��� ������� �������
			if (matrix[curr_vertex][j] != 0) { // ���� ���� ����
				// ���� �������� ���� � ������� ������ ��� �������� ���� � ��� ������� � �� ��� � �� �� ���������
				ways[j] = (ways[j] > (ways[curr_vertex] + matrix[curr_vertex][j])) ? ways[curr_vertex] + matrix[curr_vertex][j] : ways[j];
			}
		}
		int min_marker = 1000000;
		for (int j = 0; j < size; j++) { //���������� �� ���� ��������
			if (markers[j] != 1 && ways[j] < min_marker) { // ���� ������� �� �������� ���������� � �������� ���� � ��� ���������� �������� ����������
				curr_vertex = j;
				min_marker = ways[j];
			}
		}
		correct_markers[i] = curr_vertex;
		markers[curr_vertex] = 1;
		Trace::WriteLine("������� " + (correct_markers[i] + 1) + " ������� ����������");
		Trace::Write("������ ����� �� �������� " + i + ": ");
		for (int j = 0; j < size; j++)
		{
			Trace::Write(ways[j] + " ");
		}
		Trace::WriteLine("");
	}
	Trace::Write("���������� ������ �����: ");
	for (int i = 0; i < size; i++)
	{
		Trace::Write(ways[i] + " ");
	}
	Trace::WriteLine("");
}

// �� ������ �������������� ��� ��������� ��������, �� ������ ���������� �� ������� ���������
// �� ������ ���� ������ 4 ����� � �������, ���� ���� ���� � 1, �� ������ ���� ���� � 20 � ��������
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
