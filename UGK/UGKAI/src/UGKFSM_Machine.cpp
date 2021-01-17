/** Definition of FSM methods linked to a character

*	Prephix = UGKFSMM_

*	@author:	José Alapont Luján
				Claudia Cañada Luna
				Ramon Molla
				Joan Sancho

*	@version 2016-02
*/

#include "UGKFSM_Machine.h"
#include "UGKFA_Concurrent_States.h"
#include <ctime>
#include <iostream>

using namespace UGK;
using namespace std;
FSM_Machine::FSM_Machine(){}

/*
*	\fn FSM_Machine::FSM_Machine(FA_Classic* fsm)
*	\brief Initializes a new instance of the FSM_Machine class.
*	\param fsm FA object
*	\return 
*	\warning FSM_Manager uses this method to initialize a machine
*/
FSM_Machine::FSM_Machine(FA_Classic* fsm)
{
	FSM = fsm;
	CurrentState = FSM->getInitialState();
	MaxEnabled = 1;

	if (FSM->getFAtype() == "Concurrent_States")
	{

		MaxEnabled = dynamic_cast<FA_Concurrent_States*> (FSM)->getMaxConcurrent();
		for (int i = 0; i < MaxEnabled; i++)
		{
			SuperiorStack.push_back(stack<FSM_State*>());
			FSM_Stack.push_back(stack<FA_Classic*>());

			list<stack<FA_Classic*>>::iterator it = FSM_Stack.begin();
			advance(it, i);
			it->push(FSM);
			ControlStack.push_back(stack<FSM_State*>());

			list<stack<FSM_State*>>::iterator it2 = ControlStack.begin();
			advance(it2, i);
			it2->push(CurrentState);

		}

		UGKFAC_StateList inits = dynamic_cast<FA_Concurrent_States*> (FSM)->getInitials();
		for (list<FSM_State*>::iterator st = inits.begin(); st != inits.end(); ++st) EnabledStates.push_back(*st);
		StatesCredits = dynamic_cast<FA_Concurrent_States*> (FSM)->getCreditsDic();
	}
	else
	{
		MaxEnabled = 1;
		SuperiorStack.push_back(stack<FSM_State*>());
		FSM_Stack.push_back(stack<FA_Classic*>());

		list<stack<FA_Classic*>>::iterator it = FSM_Stack.begin();
		it->push(FSM);

		ControlStack.push_back(stack<FSM_State*>());
		list<stack<FSM_State*>>::iterator it2 = ControlStack.begin();
		it2->push(CurrentState);

		EnabledStates.push_back(FSM->getInitialState());
	}

	UpdateEnabled = false;
	inertialTimer = clock();
}

/*
*	\fn FA_Classic* FSM_Machine::getFSM()
*	\brief Get Current FSM
*	\return FA object
*/
FA_Classic* FSM_Machine::getFSM()
{
	return FSM;
}

/*
*	\fn FSM_State* FSM_Machine::getCurrentState()
*	\brief Get Current State (not valid for Concurrent States)
*	\return State object
*/
FSM_State* FSM_Machine::getCurrentState()
{
	return CurrentState;
}

/*
*	\fn UGKFAC_StateList FSM_Machine::getEnabledStates()
*	\brief Get Current States
*	\return List of enabled states
*/
UGKFAC_StateList FSM_Machine::getEnabledStates()
{
	return EnabledStates;
}

/*
*	\fn UGKFAC_StateList FSM_Machine::getEnabledStates()
*	\brief Get Current States
*	\return List of enabled states
*/
void FSM_Machine::setCurrentState(FSM_State* state)
{
	CurrentState = state;
}

/*
*	\fn list<int> FSM_Machine::UpdateFSM(list<int> Events)
*	\brief Updates situation of current/s FSM
*	\param A list of int Events
*	\return A List of integer value actions to do
*	\warning It was not taken into account the following functionalities:
*	\n Inertial conduct based on stages in FA_Inertial
*	\n Good performance in FA_Stack
*	\n Leave a SubFSM when finish and continue the execution of a superior FSM
*	\n Correct performance of FA_Concurrent_State as SubFSM
*/
list<int> FSM_Machine::UpdateFSM(list<int> Events)
{
	
	DoActions.clear();
	EnabledStatesCopy.clear();
	for (list<FSM_State*>::iterator i = EnabledStates.begin(); i != EnabledStates.end(); ++i) EnabledStatesCopy.push_back(*i);

	int es = 0;
	list<FSM_State*> onCycle;
	
	for (list<FSM_State*>::iterator s = EnabledStates.begin(); s != EnabledStates.end(); ++s){
		t_aux = nullptr;
		change = false;
		stackable = false;
		list<stack<FA_Classic*>>::iterator it = next(FSM_Stack.begin(), es);
		FSM = it->top();

		int CEvent = -1;
		CEvent = Events.front();
		
		if (CEvent == -1) return DoActions;
		if (FSM->getFAtype() == "Classic"){
			if (FSM->isProbabilistic()){
				list<FSM_Transition*> tr = CurrentState->getTransitions();
				for (list<FSM_Transition*>::iterator t = tr.begin(); t != tr.end(); ++t){
					RandomNumber = rand() % 100;
					UGKFSMT_EventList t_events = (*t)->getEvents();

					for (UGKFSMT_EventList::iterator ev = t_events.begin(); ev != t_events.end(); ++ev){
						if ((*ev)->getEventTag() == CEvent){
							if (RandomNumber < (*t)->getProbability()){
								t_aux = *t;

								if (CurrentState->getTag() != t_aux->getFinal()->getTag()){
									change = true;
								}
								else{
									change = false;
								}

								break;
							}
						}
					}

					if (t_aux != nullptr) break;
				}
			}
			else{
				list<FSM_Transition*> tr = CurrentState->getTransitions();
				for (list<FSM_Transition*>::iterator t = tr.begin(); t != tr.end(); ++t){
					UGKFSMT_EventList t_events = (*t)->getEvents();

					for (UGKFSMT_EventList::iterator ev = t_events.begin(); ev != t_events.end(); ++ev){
						if ((*ev)->getEventTag() == CEvent){
								t_aux = *t;

								if (CurrentState->getTag() != t_aux->getFinal()->getTag()){
									change = true;
								}
								else{
									change = false;
								}

								break;
						}
					}

					if (t_aux != nullptr) break;
				}
			}

			if (change){
				if (t_aux->getFinal()->getSubFA() != nullptr){
					DoActions.push_back(CurrentState->getOutAction());
					DoActions.push_back(t_aux->getAction());
					list<stack<FSM_State*>>::iterator ss = next(SuperiorStack.begin(), es);
					ss->push(t_aux->getFinal());
					it->push(t_aux->getFinal()->getSubFA());

					if (t_aux->getFinal()->getSubFA()->getFAtype() == "Concurrent_States"){
						list<FSM_State*> cs = dynamic_cast<FA_Concurrent_States*> (t_aux->getFinal()->getSubFA())->getInitials();
						for (list<FSM_State*>::iterator sta = cs.begin(); sta != cs.end(); ++sta){
							DoActions.push_back((*sta)->getInAction());
						}
					}
					else{
						CurrentState = t_aux->getFinal()->getSubFA()->getInitialState();
						DoActions.push_back(CurrentState->getInAction());
					}
				}
				else{
					DoActions.push_back(CurrentState->getOutAction());
					DoActions.push_back(t_aux->getAction());
					CurrentState = t_aux->getFinal();
					DoActions.push_back(CurrentState->getInAction());
				}
			}

			t_aux = nullptr;
		}
		else if (FSM->getFAtype() == "Inertial"){

			if (CEvent != lastEvent) inertialTimer = 0;

			if (FSM->isProbabilistic()){
				list<FSM_Transition*> tr = CurrentState->getTransitions();
				for (list<FSM_Transition*>::iterator t = tr.begin(); t != tr.end(); ++t){
					RandomNumber = rand() % 100;
					list<FSM_Event*> t_events = (*t)->getEvents();

					for (list<FSM_Event*>::iterator ev = t_events.begin(); ev != t_events.end(); ++ev){
						if ((*ev)->getEventTag() == CEvent){
							if (RandomNumber < (*t)->getProbability()){
								t_aux = *t;

								if (CurrentState->getTag() != t_aux->getFinal()->getTag()){
									change = true;
									inertialTimer = clock();
								}
								else{
									change = false;
								}

								break;
							}
						}
					}

					if (t_aux != nullptr) break;
				}
			}
			else{
				list<FSM_Transition*> tr = CurrentState->getTransitions();
				for (list<FSM_Transition*>::iterator t = tr.begin(); t != tr.end(); ++t){
					list<FSM_Event*> t_events = (*t)->getEvents();

					for (list<FSM_Event*>::iterator ev = t_events.begin(); ev != t_events.end(); ++ev){
						if ((*ev)->getEventTag() == CEvent){
								t_aux = *t;

								if (CurrentState->getTag() != t_aux->getFinal()->getTag()){
									change = true;
									inertialTimer = clock();
								}
								else{
									change = false;
								}

								break;
						}
					}

					if (t_aux != nullptr) break;
				}
			}

			if (change){
				if (t_aux->getFinal()->getSubFA() != nullptr){
					if ((clock() - inertialTimer) / (CLOCKS_PER_SEC / 1000) > CurrentState->getLatency()){
						DoActions.push_back(CurrentState->getOutAction());
						DoActions.push_back(t_aux->getAction());
						list<stack<FSM_State*>>::iterator ss = next(SuperiorStack.begin(), es);
						ss->push(t_aux->getFinal());
						it->push(t_aux->getFinal()->getSubFA());

						if (t_aux->getFinal()->getSubFA()->getFAtype() == "Concurrent_States"){
							list<FSM_State*> cs = dynamic_cast<FA_Concurrent_States*> (t_aux->getFinal()->getSubFA())->getInitials();
							for (list<FSM_State*>::iterator sta = cs.begin(); sta != cs.end(); ++sta){
								DoActions.push_back((*sta)->getInAction());
							}
						}
						else{
							CurrentState = t_aux->getFinal()->getSubFA()->getInitialState();
							DoActions.push_back(CurrentState->getInAction());
						}

						inertialTimer = 0;
					}
					else{
						DoActions.push_back(CurrentState->getAction());
					}
				}
				else{
					if ((clock() - inertialTimer) / (CLOCKS_PER_SEC/1000)> CurrentState->getLatency()){
						DoActions.push_back(CurrentState->getOutAction());
						DoActions.push_back(t_aux->getAction());
						CurrentState = t_aux->getFinal();
						DoActions.push_back(CurrentState->getInAction());
						inertialTimer = 0;
					}
					else{
						DoActions.push_back(CurrentState->getAction());
					}
				}
			}

			lastEvent = CEvent;
			t_aux = nullptr;
		}
		
		else if (FSM->getFAtype() == "Stack-based"){

				if (FSM->isProbabilistic()){
					list<FSM_Transition*> tr = CurrentState->getTransitions();
					for (list<FSM_Transition*>::iterator t = tr.begin(); t != tr.end(); ++t){
						RandomNumber = rand() % 100;
						list<FSM_Event*> t_events = (*t)->getEvents();

						for (list<FSM_Event*>::iterator ev = t_events.begin(); ev != t_events.end(); ++ev){
							if ((*ev)->getEventTag() == CEvent){
								if (RandomNumber < (*t)->getProbability()){
									t_aux = *t;

									if (CurrentState->getTag() != t_aux->getFinal()->getTag()){
										change = true;

										if ((*ev)->getEventType() == FSM_STACKABLE_EVENT && ((*t)->getFinal()->getPriority() > CurrentState->getPriority()))
											stackable = true;
									}
									else{
										change = false;
									}

									break;
								}
							}
						}

						if (t_aux != nullptr) break;
					}
				}
				else{
					list<FSM_Transition*> tr = CurrentState->getTransitions();
					for (list<FSM_Transition*>::iterator t = tr.begin(); t != tr.end(); ++t){
						list<FSM_Event*> t_events = (*t)->getEvents();

						for (list<FSM_Event*>::iterator ev = t_events.begin(); ev != t_events.end(); ++ev){
							if ((*ev)->getEventTag() == CEvent){
									t_aux = *t;

									if (CurrentState->getTag() != t_aux->getFinal()->getTag()){
										change = true;

										if ((*ev)->getEventType() == FSM_STACKABLE_EVENT && ((*t)->getFinal()->getPriority() > CurrentState->getPriority()))
											stackable = true;
									}
									else{
										change = false;
									}

									break;
							}
						}

						if (t_aux != nullptr) break;
					}
				}

				if (change){
					if (stackable){
						if (t_aux->getFinal()->getSubFA() != nullptr){
							DoActions.push_back(CurrentState->getOutAction());
							DoActions.push_back(t_aux->getAction());
							list<stack<FSM_State*>>::iterator ss = next(SuperiorStack.begin(), es);
							ss->push(t_aux->getFinal());
							it->push(t_aux->getFinal()->getSubFA());

							if (t_aux->getFinal()->getSubFA()->getTag() == CONCURRENT_STATES){
								list<FSM_State*> cs = dynamic_cast<FA_Concurrent_States*> (t_aux->getFinal()->getSubFA())->getInitials();
								for (list<FSM_State*>::iterator sta = cs.begin(); sta != cs.end(); ++sta){
									DoActions.push_back((*sta)->getInAction());
								}
							}
							else{
								CurrentState = t_aux->getFinal()->getSubFA()->getInitialState();
								DoActions.push_back(CurrentState->getInAction());
							}

							list<stack<FSM_State*>>::iterator cons = next(ControlStack.begin(), es);
							cons->push(CurrentState);
						}
						else{
							DoActions.push_back(CurrentState->getOutAction());
							DoActions.push_back(t_aux->getAction());
							CurrentState = t_aux->getFinal();
							DoActions.push_back(CurrentState->getInAction());
							list<stack<FSM_State*>>::iterator cons = next(ControlStack.begin(), es);
							cons->push(CurrentState);
						}
					}
					else{
						if (t_aux->getFinal()->getSubFA() != nullptr){
							DoActions.push_back(CurrentState->getOutAction());
							DoActions.push_back(t_aux->getAction());
							list<stack<FSM_State*>>::iterator ss = next(SuperiorStack.begin(), es);
							ss->push(t_aux->getFinal());
							it->push(t_aux->getFinal()->getSubFA());

							if (t_aux->getFinal()->getSubFA()->getFAtype() == "Concurrent_States"){
								list<FSM_State*> cs = dynamic_cast<FA_Concurrent_States*> (t_aux->getFinal()->getSubFA())->getInitials();
								for (list<FSM_State*>::iterator sta = cs.begin(); sta != cs.end(); ++sta){
									DoActions.push_back((*sta)->getInAction());
								}
							}
							else{
								CurrentState = t_aux->getFinal()->getSubFA()->getInitialState();
								DoActions.push_back(CurrentState->getInAction());
							}

							list<stack<FSM_State*>>::iterator cons = next(ControlStack.begin(), es);
							cons->pop();
							cons->push(CurrentState);
						}
						else{
							DoActions.push_back(CurrentState->getOutAction());
							DoActions.push_back(t_aux->getAction());
							CurrentState = t_aux->getFinal();
							DoActions.push_back(CurrentState->getInAction());
							list<stack<FSM_State*>>::iterator cons = next(ControlStack.begin(), es);
							cons->pop();
							cons->push(CurrentState);
						}
					}
				}

		}
		else if (FSM->getFAtype() == "Concurrent_States"){
			for (list<int>::iterator CurrentEvent = Events.begin(); CurrentEvent != Events.end(); ++CurrentEvent){
				t_aux = nullptr;
				change = false;
				list<FSM_State*>::iterator ens = next(EnabledStatesCopy.begin(), es);
				if (StatesCredits[(*ens)->getTag()] > 0){
					if (FSM->isProbabilistic()){
						list<FSM_Transition*> tr = (*ens)->getTransitions();
						for (list<FSM_Transition*>::iterator t = tr.begin(); t != tr.end(); ++t){
							RandomNumber = rand()%100;
							list<FSM_Event*> t_events = (*t)->getEvents();
							
							for (list<FSM_Event*>::iterator ev = t_events.begin(); ev != t_events.end(); ++ev){
								if ((*ev)->getEventTag() == *CurrentEvent){
									if (RandomNumber < (*t)->getProbability()){
										t_aux = *t;

										if ((*ens)->getTag() != t_aux->getFinal()->getTag()){
											change = true;
										}
										else{
											change = false;
										}

										break;
									}
								}
							}

							if (t_aux != nullptr) break;
						}
					}
					else{
						list<FSM_Transition*> tr = (*ens)->getTransitions();
						for (list<FSM_Transition*>::iterator t = tr.begin(); t != tr.end(); ++t){
							list<FSM_Event*> t_events = (*t)->getEvents();

							for (list<FSM_Event*>::iterator ev = t_events.begin(); ev != t_events.end(); ++ev){
								if ((*ev)->getEventTag() == *CurrentEvent && (*ens)->getTag() == (*t)->getFinal()->getTag()){
									t_aux = *t;
									break;
								}
								else{
									t_aux = *t;
									change = true;
									break;
								}
							}

							if (t_aux != nullptr) break;
						}
					}

					if (change){
						bool contains = false;
						for (list<FSM_State*>::iterator oc = onCycle.begin(); oc != onCycle.end(); ++oc){
							if (*oc == t_aux->getFinal()){
								contains = true;
								break;
							}
						}
						if (!contains){
							int CurrentCredits = StatesCredits[(*ens)->getTag()];
							bool contains2 = false;
							for (list<FSM_State*>::iterator oc2 = onCycle.begin(); oc2 != onCycle.end(); ++oc2){
								if (*oc2 == *ens){
									contains2 = true;
									break;
								}
							}

							if (CurrentCredits > 1 || (CurrentCredits == 1 && !contains2)){
								if (t_aux->getFinal()->getSubFA() != nullptr){
									DoActions.push_back((*ens)->getOutAction());
									StatesCredits[(*ens)->getTag()] = CurrentCredits - 1;
									DoActions.push_back(t_aux->getAction());
									list<stack<FSM_State*>>::iterator ss = next(SuperiorStack.begin(), es);
									ss->push(t_aux->getFinal());
									it->push(t_aux->getFinal()->getSubFA());
									StatesCredits[t_aux->getFinal()->getTag()] = StatesCredits[t_aux->getFinal()->getTag()] + 1;

									if (t_aux->getFinal()->getSubFA()->getFAtype() == "Concurrent_States"){
										list<FSM_State*> cs = dynamic_cast<FA_Concurrent_States*> (t_aux->getFinal()->getSubFA())->getInitials();
										for (list<FSM_State*>::iterator sta = cs.begin(); sta != cs.end(); ++sta){
											DoActions.push_back((*sta)->getInAction());
										}
									}
									else{
										*ens = t_aux->getFinal()->getSubFA()->getInitialState();
										DoActions.push_back((*ens)->getInAction());
									}

									onCycle.push_back(t_aux->getFinal());
								}
								else{
									DoActions.push_back((*ens)->getOutAction());
									StatesCredits[(*ens)->getTag()] = CurrentCredits - 1;
									DoActions.push_back(t_aux->getAction());
									*ens = t_aux->getFinal();
									StatesCredits[(*ens)->getTag()] = StatesCredits[(*ens)->getTag()] + 1;
									DoActions.push_back((*ens)->getInAction());
									onCycle.push_back(t_aux->getFinal());
								}
							}
						}
					}
					else{
						bool contains = false;
						for (list<FSM_State*>::iterator oc = onCycle.begin(); oc != onCycle.end(); ++oc){
							if (*oc == *ens){
								contains = true;
								break;
							}
						}
						if (t_aux == nullptr){
							list<stack<FSM_State*>>::iterator ss = next(SuperiorStack.begin(), es);
							if (ss->size() > 0){
								*ens = ss->top();
								ss->pop();
								it->pop();
							}
						}
						else{
							if (!contains){
								onCycle.push_back(*ens);
								DoActions.push_back((*s)->getAction());
							}
						}
					}
				}
				else break;
			}

			UpdateEnabled = true;
		}

		es++;
	}

	if (UpdateEnabled){
		UpdateEnabled = false;
		EnabledStates.clear();
		for (list<FSM_State*>::iterator i = onCycle.begin(); i != onCycle.end(); ++i){
			EnabledStates.push_back(*i);
		}
		if (EnabledStates.size() == 0){
			for (map<int, int>::iterator entry = StatesCredits.begin(); entry != StatesCredits.end(); ++entry){
				if (entry->second > 0) EnabledStates.push_back(FSM->getStateByTag(entry->first));
			}
		}
	}

	return DoActions;

}

/*
*	\fn FSM_State* UpdateFSM(UGKS_String event_name)
*	\brief Updates situation of current/s FSM
*	\param A an event name
*	\return The new current state
*	\warning It was not taken into account the following functionalities:
*/
FSM_State* FSM_Machine::UpdateFSM(UGKS_String event_name)
{
	cout << "FSM operating: " << FSM->getFAid() << "\n";

	cout << "Current AI state: " << CurrentState->getID() << "\n";

	UGKFSMS_TransitionList stateTransitions = CurrentState->getTransitions();
	UGKFSMS_TransitionList possibleTransitions;

	if (FSM->getFAtype() == "Classic")
	{
		for (list<FSM_Transition*>::iterator it = stateTransitions.begin(); it != stateTransitions.end(); it++)
		{
			cout << "Transition: " << (*it)->getID() << "\n";
			UGKFSMT_EventList auxEvents = (*it)->getEvents();
			for (list<FSM_Event*>::iterator iter = auxEvents.begin(); iter != auxEvents.end(); iter++)
			{
				cout << "  Event: " << (*iter)->getID() << "\n";
				if((*iter)->getID() == event_name)
				{
					cout << "Selected transition: " << (*it)->getID() << " with event: " << (*iter)->getID() << " with destination: " << (*it)->getFinal()->getID() << "\n";
					possibleTransitions.push_back(*it);
					break;
				}
			}
		}

		int v2 = rand() % 100 + 1;
		int accumulatedProbability = 1;
		for (list<FSM_Transition*>::iterator it = possibleTransitions.begin(); it != possibleTransitions.end(); it++)
		{
			cout << "Selected transition from possibles: " << (*it)->getID() << " with probability: " << (*it)->getProbability() << " and number: " << v2 << "\n";
			cout << "looking in range: " << accumulatedProbability << " < " << v2 << " < " << (*it)->getProbability()+accumulatedProbability << "\n";
			if (accumulatedProbability <= v2 && v2 <= (*it)->getProbability()+accumulatedProbability)
			{
				cout << "Moving to state: " << (*it)->getFinal()->getID() << "\n";
				setCurrentState((*it)->getFinal());
				return CurrentState;
			}
			else
				accumulatedProbability += (*it)->getProbability();
		}
	}

	else if (FSM->getFAtype() == "Inertial")
	{
		double elapsed_time = (clock() - inertialTimer)/ (double)CLOCKS_PER_SEC;

		cout << "Elapsed time: " << elapsed_time << " State latency: " << CurrentState->getLatency() << "\n";

		if (elapsed_time > CurrentState->getLatency())
		{

			for (list<FSM_Transition*>::iterator it = stateTransitions.begin(); it != stateTransitions.end(); it++)
			{
				cout << "Transition: " << (*it)->getID() << "\n";
				UGKFSMT_EventList auxEvents = (*it)->getEvents();
				for (list<FSM_Event*>::iterator iter = auxEvents.begin(); iter != auxEvents.end(); iter++)
				{
					cout << "  Event: " << (*iter)->getID() << "\n";
					if ((*iter)->getID() == event_name)
					{
						cout << "Selected transition: " << (*it)->getID() << " with event: " << (*iter)->getID() << " with destination: " << (*it)->getFinal()->getID() << "\n";
						possibleTransitions.push_back(*it);
						break;
					}
				}
			}

			int v2 = rand() % 100 + 1;
			int accumulatedProbability = 1;
			for (list<FSM_Transition*>::iterator it = possibleTransitions.begin(); it != possibleTransitions.end(); it++)
			{
				cout << "Selected transition from possibles: " << (*it)->getID() << " with probability: " << (*it)->getProbability() << " and number: " << v2 << "\n";
				cout << "looking in range: " << accumulatedProbability << " < " << v2 << " < " << (*it)->getProbability() + accumulatedProbability << "\n";
				if (accumulatedProbability <= v2 && v2 <= (*it)->getProbability() + accumulatedProbability)
				{
					cout << "Moving to state: " << (*it)->getFinal()->getID() << "\n";
					setCurrentState((*it)->getFinal());
					inertialTimer = clock();
					return CurrentState;
				}
				else
					accumulatedProbability += (*it)->getProbability();
			}
		}
	}

	return CurrentState;
}
