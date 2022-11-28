#pragma once

namespace DijkstraGeneration {

	using namespace System;
	using namespace System::Diagnostics;
	void GenerateMatrix(array<array<int>^>^ matrix, int size);
	void SolveDijkstra(array<array<int>^>^ ways, int size, array<array<int>^>^ matrix, array<int>^ correctMarkers);
	void FillRandom(int index, array<array<int>^>^ matrix, int size, array<int>^ amounts);
	bool BetweenFirstLast(int index, array<array<int>^>^ matrix, int size, int j);
}