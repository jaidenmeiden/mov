#include <UGKNeuralNetworkLayer.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

using namespace UGK;

/** Recommended book for using NeuralNetworks on videogames:
* (1) AI for game developers de Bourg&Seemann, O'Reilly Press.
* (2) AI techniques for game programming de Mat Buckland, Premier Press.
* The implemetation you're seeing has been adapted from the implementation which can be found in the first book.
* The second book provides an excellent source of knowledge for a future work combining neural networks and genetic algorithms.
*/

/*! Class corresponding to a neuron layer. Note that its parameters are provided afterwards. */
CNeuralNetworkLayer::CNeuralNetworkLayer()
{
	/* Constructor.
	*/
	ParentLayer = NULL;
	ChildLayer = NULL;
	UseMomentum = false;
	MomentumFactor = 0.9;
}

void CNeuralNetworkLayer::Initialize(int NumNodes, CNeuralNetworkLayer* parent, CNeuralNetworkLayer* child)
{
	/* neuron layer initialization. Note that paramaters need to build the layer are provided now: number of neurons, parent layer and child layer.
	*/
	int	i, j;

	NeuronValues = (double*)malloc(sizeof(double) * NumberOfNodes);
	DesiredValues = (double*)malloc(sizeof(double) * NumberOfNodes);
	Errors = (double*)malloc(sizeof(double) * NumberOfNodes);

	if (parent != NULL)
	{
		ParentLayer = parent;
	}

	if (child != NULL)
	{
		ChildLayer = child;


		Weights = (double**)malloc(sizeof(double*) * NumberOfNodes);
		WeightChanges = (double**)malloc(sizeof(double*) * NumberOfNodes);
		for (i = 0; i<NumberOfNodes; i++)
		{
			Weights[i] = (double*)malloc(sizeof(double) * NumberOfChildNodes);
			WeightChanges[i] = (double*)malloc(sizeof(double) * NumberOfChildNodes);
		}

		BiasValues = (double*)malloc(sizeof(double) * NumberOfChildNodes);
		BiasWeights = (double*)malloc(sizeof(double) * NumberOfChildNodes);
	}
	else {
		Weights = NULL;
		BiasValues = NULL;
		BiasWeights = NULL;
	}

	for (i = 0; i<NumberOfNodes; i++)
	{
		NeuronValues[i] = 0;
		DesiredValues[i] = 0;
		Errors[i] = 0;

		if (ChildLayer != NULL)
			for (j = 0; j<NumberOfChildNodes; j++)
			{
				Weights[i][j] = 0;
				WeightChanges[i][j] = 0;
			}
	}

	if (ChildLayer != NULL)
		for (j = 0; j<NumberOfChildNodes; j++)
		{
			BiasValues[j] = -1;
			BiasWeights[j] = 0;
		}

}

void CNeuralNetworkLayer::CleanUp(void)
{
	/* Free memory.
	*/
	int	i;

	free(NeuronValues);
	free(DesiredValues);
	free(Errors);

	if (Weights != NULL)
	{
		for (i = 0; i<NumberOfNodes; i++)
		{
			free(Weights[i]);
			free(WeightChanges[i]);
		}

		free(Weights);
		free(WeightChanges);
	}

	if (BiasValues != NULL) free(BiasValues);
	if (BiasWeights != NULL) free(BiasWeights);
}

void CNeuralNetworkLayer::RandomizeWeights(void)
{
	/* Random inicialization of the weights of each neuron in the layer.
	*/

	int	i, j;
	int	min = 0;
	int	max = 200;
	int	number;

	srand((unsigned)time(NULL));

	for (i = 0; i<NumberOfNodes; i++)
	{
		for (j = 0; j<NumberOfChildNodes; j++)
		{
			number = (((abs(rand()) % (max - min + 1)) + min));

			if (number>max)
				number = max;

			if (number<min)
				number = min;

			Weights[i][j] = number / 100.0f - 1;
		}
	}

	for (j = 0; j<NumberOfChildNodes; j++)
	{
		number = (((abs(rand()) % (max - min + 1)) + min));

		if (number>max)
			number = max;

		if (number<min)
			number = min;

		BiasWeights[j] = number / 100.0f - 1;
	}
}

void CNeuralNetworkLayer::CalculateErrors(void)
{
	/* Calculates output errors (differences between the desired outputs and the actual outputs).
	*/

	int		i, j;
	double	sum;

	if (ChildLayer == NULL) 
	{
		for (i = 0; i<NumberOfNodes; i++)
		{
			Errors[i] = (DesiredValues[i] - NeuronValues[i]) * NeuronValues[i] * (1.0f - NeuronValues[i]);
		}
	}
	else if (ParentLayer == NULL) { 
		for (i = 0; i<NumberOfNodes; i++)
		{
			Errors[i] = 0.0f;
		}
	}
	else { 
		for (i = 0; i<NumberOfNodes; i++)
		{
			sum = 0;
			for (j = 0; j<NumberOfChildNodes; j++)
			{
				sum += ChildLayer->Errors[j] * Weights[i][j];
			}
			Errors[i] = sum * NeuronValues[i] * (1.0f - NeuronValues[i]);
		}
	}
}

void CNeuralNetworkLayer::AdjustWeights(void)
{
	/* Adjusts the weights of each neuron.
	*/

	int		i, j;
	double	dw;

	if (ChildLayer != NULL)
	{
		for (i = 0; i<NumberOfNodes; i++)
		{
			for (j = 0; j<NumberOfChildNodes; j++)
			{
				dw = LearningRate * ChildLayer->Errors[j] * NeuronValues[i];
				Weights[i][j] += dw + MomentumFactor * WeightChanges[i][j];
				WeightChanges[i][j] = dw;
			}
		}

		for (j = 0; j<NumberOfChildNodes; j++)
		{
			BiasWeights[j] += LearningRate * ChildLayer->Errors[j] * BiasValues[j];
		}
	}
}

void CNeuralNetworkLayer::CalculateNeuronValues(void)
{
	/* Calculates the output of each neuron.
	*/

	int		i, j;
	double	x;

	if (ParentLayer != NULL)
	{
		for (j = 0; j<NumberOfNodes; j++)
		{
			x = 0;
			for (i = 0; i<NumberOfParentNodes; i++)
			{
				x += ParentLayer->NeuronValues[i] * ParentLayer->Weights[i][j];
			}
			x += ParentLayer->BiasValues[j] * ParentLayer->BiasWeights[j];

			switch (ActFunction)
			{
				case SIGMOID:
					NeuronValues[j] = 1.0f / (1 + exp(-x));
					break;
			}
		}
	}
}