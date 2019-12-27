#pragma once
#include <State.hpp>
#include <memory>
#include <stack>

namespace Skeleton {
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
  std::stack<StateRef> _states;
  StateRef _newState;
  bool _isRemoving;
  bool _isAdding;
  bool _isReplacing;
};
} // namespace Skeleton