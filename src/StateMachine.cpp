#include <StateMachine.hpp>

namespace skeleton {
void StateMachine::add_state(StateRef newState, bool isReplacing) {
	this->is_adding = true;
	this->is_replacing = isReplacing;
	this->latest_state = std::move(newState);
}

void StateMachine::remove_state() { this->is_removing = true; }

void StateMachine::process_state_changes() {
	if (this->is_removing && !this->states.empty()) {
		this->states.pop();
		if (!this->states.empty()) {
			this->states.top()->resume();
		}
		this->is_removing = false;
	}

	if (this->is_adding) {
		if (!this->states.empty()) {
			if (this->is_replacing) {
				this->states.pop();
			} else {
				this->states.top();
			}
		}

		this->states.push(std::move(this->latest_state));
		this->states.top()->init();
		this->is_adding = false;
	}
}

StateRef &StateMachine::get_active_state() { return this->states.top(); }
}; // namespace skeleton