#pragma once

namespace GraphsToSolve {

	using namespace System;
	using namespace System::Diagnostics;
	void GenerateMatrix(array<array<int>^>^ matrix, int size, bool generateWithValues);
	void SolveDijkstra(array<array<int>^>^ matrix, int size, array<array<int>^>^ ways, array<int>^ correctMarkers);
	void SolveDemoucron(array<array<int>^>^ matrix, int size, array<array<int>^>^ levels);

	void AddToLevel(array<array<int>^>^ levels, int levelIndex, int vertexIndex);
	bool IsInLevels(array<array<int>^>^ levels, int vertexIndex, int curAmountOfLevels);
}