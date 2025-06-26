#pragma once
#include <functional>
#include <vector>

class PendingChangesManager {
  PendingChangesManager() = default;
  ~PendingChangesManager() = default;
  std::vector<std::function<void()>> All;
public:
  PendingChangesManager(const PendingChangesManager&) = delete;
  PendingChangesManager& operator=(const PendingChangesManager&) = delete;

  static PendingChangesManager& Instance() {
    static PendingChangesManager singleton;
    return singleton;
  }

  void Add(const std::function<void()> &func);
  void Apply();
};
