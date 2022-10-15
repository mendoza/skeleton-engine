#ifndef SKELETON_STATE_MACHINE_HPP
#define SKELETON_STATE_MACHINE_HPP

#include <State.hpp>
#include <memory>
#include <stack>

namespace skeleton {
typedef std::unique_ptr<State> StateRef;
class StateMachine {

  public:
	StateMachine() {}
	~StateMachine() {}

	void addState(StateRef newState, bool isReplacing = true);
	void removeState();
	void processStateChanges();
	StateRef &getActiveState();

  private:
	std::stack<StateRef> States;
	StateRef NewState;
	bool IsRemoving;
	bool IsAdding;
	bool IsReplacing;
};
}; // namespace skeleton

#endif