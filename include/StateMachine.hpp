#ifndef SKELETON_STATE_MACHINE_HPP
#define SKELETON_STATE_MACHINE_HPP

#include <State.hpp>
#include <memory>
#include <stack>

namespace skeleton {
class StateMachine {

  public:
	StateMachine() {}
	~StateMachine() {}

	void add_state(StateRef new_state, bool is_replacing = true);
	void remove_state();
	void process_state_changes();
	StateRef &get_active_state();

  private:
	std::stack<StateRef> states;
	StateRef latest_state;
	bool is_removing;
	bool is_adding;
	bool is_replacing;
};
}; // namespace skeleton

#endif