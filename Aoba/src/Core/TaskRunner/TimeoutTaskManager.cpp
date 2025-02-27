﻿#include "TimeoutTaskManager.hpp"

namespace s3d::aoba {
    size_t TimeoutTaskManager::addTask(const std::function<void()>& task, uint64_t ms, bool threading) {
        m_timeouts.emplace_back(task, ms, threading);
        return m_timeouts[m_timeouts.size() - 1].id();
    }

    bool TimeoutTaskManager::isAlive(size_t id) const noexcept {
        for (const auto& timeout : m_timeouts) {
            if (timeout.id() == id) {
                return timeout.isAlive();
            }
        }
        return false;
    }

    bool TimeoutTaskManager::isRunning(size_t id) const noexcept {
        for (const auto& timeout : m_timeouts) {
            if (timeout.id() == id) {
                return timeout.isRunning();
            }
        }
        return false;
    }

    void TimeoutTaskManager::update() {
        bool timeoutDeletable = true;

        for (auto& timeout : m_timeouts) {
            timeout.update();
            timeoutDeletable &= !timeout.isAlive();
        }

        if (timeoutDeletable) {
            m_timeouts.clear();
            m_timeouts.shrink_to_fit();
        }
    }

    bool TimeoutTaskManager::stop(size_t id) noexcept {
        for (auto& timeout : m_timeouts) {
            if (timeout.id() == id) {
                return timeout.stop();
            }
        }
        return false;
    }

    bool TimeoutTaskManager::restart(size_t id) noexcept {
        for (auto& timeout : m_timeouts) {
            if (timeout.id() == id) {
                return timeout.restart();
            }
        }
        return false;
    }
}
