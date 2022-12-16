#pragma once

namespace GraphsToSolve {

	using namespace System;
	using namespace System::Diagnostics;
	void GenerateDijkstra(array<array<int>^>^ matrix, int size);
	void GenerateDemoucron(array<array<int>^>^ matrix, int size);
	void SolveDijkstra(array<array<int>^>^ matrix, int size, array<array<int>^>^ ways, array<int>^ correctMarkers);
	void SolveDemoucron(array<array<int>^>^ matrix, int size, array<array<int>^>^ levels);
	int GenerateRoutes(array<array<int>^>^ routes, int size);

	void AddToLevel(array<array<int>^>^ levels, int levelIndex, int vertexIndex);
	bool IsInLevels(array<array<int>^>^ levels, int vertexIndex, int curAmountOfLevels);
	bool AccessibleOnlyFromPrevLevel(array<array<int>^>^ matrix, array<array<int>^>^ levels, int prevLevelIndex, int vertexIndex, int size);
}