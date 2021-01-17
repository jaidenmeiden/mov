#include <UGKNeuralNetwork.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <list>

using namespace UGK;

/** Recommended book for using NeuralNetworks on videogames:
* (1) AI for game developers de Bourg&Seemann, O'Reilly Press.
* (2) AI techniques for game programming de Mat Buckland, Premier Press.
* The implemetation you're seeing has been adapted from the implementation which can be found in the first book.
* The second book provides an excellent source of knowledge for a future work combining neural networks and genetic algorithms.
*/

/*! Class corresponding to the neural network itself. */
void CNeuralNetwork::Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput)
{
	/* Initialize the neural network, providing its number of inputs, number of neurons on its hidden layer and its number of outputs.
	*/

	InputLayer.NumberOfNodes = nNodesInput;
	InputLayer.NumberOfChildNodes = nNodesHidden;
	InputLayer.NumberOfParentNodes = 0;	
	InputLayer.ActFunction = SIGMOID;
	InputLayer.Initialize(nNodesInput, NULL, &HiddenLayer);
	InputLayer.RandomizeWeights();
	
	HiddenLayer.NumberOfNodes = nNodesHidden;
	HiddenLayer.NumberOfChildNodes = nNodesOutput;
	HiddenLayer.NumberOfParentNodes = nNodesInput;
	HiddenLayer.ActFunction = SIGMOID;
	HiddenLayer.Initialize(nNodesHidden, &InputLayer, &OutputLayer);
	HiddenLayer.RandomizeWeights();
	
	OutputLayer.NumberOfNodes = nNodesOutput;
	OutputLayer.NumberOfChildNodes = 0;
	OutputLayer.NumberOfParentNodes = nNodesHidden;
	OutputLayer.ActFunction = SIGMOID;
	OutputLayer.Initialize(nNodesOutput, &HiddenLayer, NULL);	
	
}

void CNeuralNetwork::CustomInitialize(std::list<CNeuralNetworkLayer> layers)
{
	/* Initialize the neural network with custom arquitectures.

	for (list<CNeuralNetworkLayer>::iterator i = layers.begin(); i != layers.end(); ++i){

	}
	*/
}

void CNeuralNetwork::CleanUp()
{
	/* Free memory.
	*/
	InputLayer.CleanUp();
	HiddenLayer.CleanUp();
	OutputLayer.CleanUp();
}

void CNeuralNetwork::SetInput(int i, double value)
{
	/* Get the input of a specific neuron on the input layer (specifying its position on the input layer).
	*/

	if((i>=0) && (i<InputLayer.NumberOfNodes))
	{
		InputLayer.NeuronValues[i] = value;
	}
}

double CNeuralNetwork::GetOutput(int i)
{
	/* Get the output of a specific neuron on the output layer (specifying its position on the output layer).
	*/
	if((i>=0) && (i<OutputLayer.NumberOfNodes))
	{
		return OutputLayer.NeuronValues[i];
	}

	return (double) INT_MAX;
}

void CNeuralNetwork::SetDesiredOutput(int i, double value)
{
	/* Specify the desired output for a certain neuron on the output layer, specifying its position.
	*/

	if((i>=0) && (i<OutputLayer.NumberOfNodes))
	{
		OutputLayer.DesiredValues[i] = value;
	}
}

void CNeuralNetwork::FeedForward(void)
{
	/* Inputs are propagated through he network to provide a new set of output values.
	*/
	InputLayer.CalculateNeuronValues();
	HiddenLayer.CalculateNeuronValues();
	OutputLayer.CalculateNeuronValues();
}

void CNeuralNetwork::BackPropagate(void)
{
	/* Weights on each neuron are tweaked based on the output error.
	*/
	OutputLayer.CalculateErrors();
	HiddenLayer.CalculateErrors();

	HiddenLayer.AdjustWeights();
	InputLayer.AdjustWeights();
}

double CNeuralNetwork::CalculateError(void)
{
	/* Calculation of the errors (differences between the expected outputs and the actual outputs).
	*/
	int		i;
	double	error = 0;

	for(i=0; i<OutputLayer.NumberOfNodes; i++)
	{
		error += pow(OutputLayer.NeuronValues[i] - OutputLayer.DesiredValues[i], 2);
	}

	error = error / OutputLayer.NumberOfNodes;

	return error;
}

void CNeuralNetwork::SetLearningRate(double rate)
{
	/* Specify the learning rate: low values don't cause any jitter, high values converge faster.
	*/
	InputLayer.LearningRate = rate;
	HiddenLayer.LearningRate = rate;
	OutputLayer.LearningRate = rate;
} 

void CNeuralNetwork::SetMomentum(bool useMomentum, double factor)
{
	/* Specify if momentum is being used along with its magnitude (in order to avoid getting stalled in local minima).
	*/
	InputLayer.UseMomentum = useMomentum;
	HiddenLayer.UseMomentum = useMomentum;
	OutputLayer.UseMomentum = useMomentum;

	InputLayer.MomentumFactor = factor;
	HiddenLayer.MomentumFactor = factor;
	OutputLayer.MomentumFactor = factor;
}