#include "BehaviorDecorator.h";

using namespace UGK;

void BehaviorDecorator::Reset()
{
	state = BS_INACTIVE;
	child->Reset();
}

void BehaviorDecorator::Add( Behavior* behavior )
{
	child = behavior;
}