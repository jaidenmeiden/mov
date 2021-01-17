/****************************************
*	Author:		Nathaniel Meyer			*
*	E-Mail:		nath_meyer@hotmail.com	*
*	Website:	http://www.nutty.ca		*
*										*
*   You are free to use, redistribute,  *
*   and alter this file in anyway, so   *
*   long as credit is given where due.	*
****************************************/
//Refactored by Ramón Mollá on 2011-08

#include <State.h>
#include <UGKString.h>

using namespace UGK;

using UGK::State;
using UGK::eWhen;
using UGK::eType;

/*
	Constructor / Destructor
*/
State::State ()
{
	clean();
}

State::~State ()
{
}

/*
	Clean
*/
void State::clean ()
{
	Name = UGKS_EMPTY_STRING;

	// Clean transitions
	Transition.clear();
	Specification.clear();
	
	SpecificationDo.func=0;
	SpecificationEntry.func=0;
	SpecificationExit.func=0;
}

/*
	Transitions
*/
void State::addTransition(STT_EventType Event, State *cState)
{
	// Add a transition to the list
	_transition temp;
	temp.Event=Event;
	temp.cTo=cState;

	Transition.push_back(temp);
	
}

bool State::incoming(const STT_EventType Event, LPSTR *args, void *O)
{
	CCharacter *Object = (CCharacter*)O;

	for(unsigned int i=0, itrMax=Specification.size();i<itrMax;i++){

		if(0 == Specification[i].Event.compare(Event)){
			if (Specification[i].func != NULL){
				Specification[i].func(args, Object);
			}
			return true;
		}
	}
	if (SpecificationEntry.func != NULL){
		SpecificationEntry.func(args, Object);
	}
	if (SpecificationDo.func != NULL){
		SpecificationDo.func(args, Object);
	}
	return true;
}

State* State::outgoing(const STT_EventType Event, LPSTR *args, void *O)
{
	CCharacter *Object = (CCharacter*)O;

	// Find the State to which this Event is tied to
	for(unsigned int i=0, itrTransMax=Transition.size();i<itrTransMax;i++){
		if(0 == Transition[i].Event.compare(Event)){
			// Run the exit action
			if (SpecificationExit.func != NULL){
				SpecificationExit.func(args, Object);
			}
			return Transition[i].cTo;
		}
	}

	return NULL;
}

/*
	addAction
*/
void State::addAction(eWhen when, eType type, STT_NameType name, mFuncPtr funcPtr){
	switch(when){
		case eOnEntry:
			if ( type == eAction ){
				SpecificationEntry.name = name;
				SpecificationEntry.type=type;
				SpecificationEntry.func = funcPtr;
			}
			break;
		case eDo:
			if ( type == eAction ){
				SpecificationDo.name = name;
				SpecificationDo.type=type;
				SpecificationDo.func = funcPtr;
			}
			break;
		case eOnExit:
			if ( type == eAction ){
				SpecificationExit.name = name;
				SpecificationExit.type=type;
				SpecificationExit.func = funcPtr;
			}
			break;
	}

}

void State::addAction(eWhen when, eType type, STT_NameType name, const STT_EventType Event, mFuncPtr funcPtr)
{
	if(when == eOnEvent){

		if(type == eAction){

			_specification temp;
			temp.name = name;
			temp.Event=Event;
			temp.type=type;
			temp.func=funcPtr;

			Specification.push_back(temp);
		}
	}
}

///*	Accessor Methods */
//CString			State::getName()		{ return Name; }
//unsigned int	State::getEvents()		{ return Specification.size(); }
//unsigned int	State::getTransitions()	{ return Transition.size(); }
//
//void State::AddSpecification(_specification s){ Specification.push_back(s); }
//_specification State::GetSpecification(int s) { return Specification[s]; }
//
//void State::AddTransition(_transition t){ Transition.push_back(t); }
//_transition State::GetTransition(int t)	{ return Transition[t]; };
//
