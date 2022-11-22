#include "GraphsToVisualize.h"
#include "DijkstraVisualizationForm.h"
//#include "MalgrangeVisualizationForm.h"
//#include "DemoucronVisualizationForm.h"

void GraphsToVisualize::VisualizeDijkstra(array<array<int>^>^ matrix, int size, array<int>^ ways)
{
	DijkstraVisualization::DijkstraVisualizationForm^ DijkstraVisualizationForm = gcnew DijkstraVisualization::DijkstraVisualizationForm(matrix, size, ways);
	DijkstraVisualizationForm->Show();
}