#include <StateMachine.hpp>

namespace Skeleton {
void StateMachine::addState(StateRef newState, bool isReplacing) {
	this->IsAdding = true;
	this->IsReplacing = isReplacing;
	this->NewState = std::move(newState);
}

void StateMachine::removeState() { this->IsRemoving = true; }

void StateMachine::processStateChanges() {
	if (this->IsRemoving && !this->States.empty()) {
		this->States.pop();
		if (!this->States.empty()) {
			this->States.top()->resume();
		}
		this->IsRemoving = false;
	}

	if (this->IsAdding) {
		if (!this->States.empty()) {
			if (this->IsReplacing) {
				this->States.pop();
			} else {
				this->States.top();
			}
		}

		this->States.push(std::move(this->NewState));
		this->States.top()->init();
		this->IsAdding = false;
	}
}

StateRef &StateMachine::getActiveState() { return this->States.top(); }
}; // namespace Skeleton