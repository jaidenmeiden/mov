#include "BehaviorComposite.h";

using namespace UGK;

void BehaviorComposite::OnStart()
{
	if( children.size() > 0 )
	{
		currentChild = children.front();
		currentIndex = 0;
	}
}

void BehaviorComposite::Reset()
{
	state = BS_INACTIVE;
	for( int i = 0; i < children.size(); i++ )
		children[i]->Reset();
}

int BehaviorComposite::GetChildCount()
{
	return children.size();
}

void BehaviorComposite::Add( Behavior* behavior )
{
	children.push_back(behavior);
}

void BehaviorComposite::Clear()
{
	children.clear();
}