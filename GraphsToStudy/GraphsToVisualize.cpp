#include "GraphsToVisualize.h"
#include "DijkstraVisualizationForm.h"
//#include "MalgrangeVisualizationForm.h"
//#include "DemoucronVisualizationForm.h"

void GraphsToVisualize::VisualizeDijkstra(array<array<int>^>^ matrix, int size, array<array<int>^>^ ways, array<int>^ correctMarkers)
{
	DijkstraVisualization::DijkstraVisualizationForm^ DijkstraVisualizationForm = gcnew DijkstraVisualization::DijkstraVisualizationForm(matrix, size, ways, correctMarkers);
	DijkstraVisualizationForm->Show();
}