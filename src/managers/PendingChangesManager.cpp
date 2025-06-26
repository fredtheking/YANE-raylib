#include "PendingChangesManager.hpp"

void PendingChangesManager::Add(const std::function<void()> &func) {
  this->All.push_back(func);
}
void PendingChangesManager::Apply() {
  for (auto & function: this->All)
    function();
  this->All.clear();
}

