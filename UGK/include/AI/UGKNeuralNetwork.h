
/**	Class that ...

Prefix CNNL_: Class Neural Network Layer

@author
@version 2016-01-06

*/

#include <UGKNeuralNetworkLayer.h>
#include <list>

/**
*	CHTMLParser

*	@author
*	@version 2016-01
*/

namespace UGK
{
	class CNeuralNetwork
	{
	public:
		CNeuralNetworkLayer	InputLayer;
		CNeuralNetworkLayer	HiddenLayer;
		CNeuralNetworkLayer	OutputLayer;

		void	Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput);
		void	CustomInitialize(std::list<CNeuralNetworkLayer> layers);
		void	CleanUp();
		void	SetInput(int i, double value);
		double	GetOutput(int i);
		void	SetDesiredOutput(int i, double value);
		void	FeedForward(void);
		void	BackPropagate(void);
		double	CalculateError(void);
		void	SetLearningRate(double rate);
		void	SetMomentum(bool useMomentum, double factor);
	};
}