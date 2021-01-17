
/**	Class that ...

Prefix CNNL_: Class Neural Network Layer

@author 
@version 2016-01-06

*/

/**
*	CHTMLParser

*	@author 
*	@version 2016-01
*/

namespace UGK
{
	typedef enum {
		SIGMOID,
		RELU,
		TAHN,
	} ACT_FUNCTION;

	class CNeuralNetworkLayer
	{
	public:
		int			NumberOfNodes;
		int			NumberOfChildNodes;
		int			NumberOfParentNodes;
		double**	Weights;
		double**	WeightChanges;
		double*		NeuronValues;
		double*		DesiredValues;
		double*		Errors;
		double*		BiasWeights;
		double*		BiasValues;
		double		LearningRate;
		ACT_FUNCTION ActFunction;

		bool		UseMomentum;
		double		MomentumFactor;

		CNeuralNetworkLayer*		ParentLayer;
		CNeuralNetworkLayer*		ChildLayer;

		CNeuralNetworkLayer();

		void	Initialize(int	NumNodes, CNeuralNetworkLayer* parent, CNeuralNetworkLayer* child);
		void	CleanUp(void);
		void	RandomizeWeights(void);
		void	CalculateErrors(void);
		void	AdjustWeights(void);
		void	CalculateNeuronValues(void);

	};
}	//Name space UGK