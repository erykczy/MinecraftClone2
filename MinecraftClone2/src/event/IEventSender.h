#pragma once
#include "src/app/util/Debug.h"
#include <vector>
#include <functional>

template<typename TEventListener>
class IEventSender {
public:
	virtual ~IEventSender() = default;

	void addListener(TEventListener* listener) {
		if (std::find(m_listeners.begin(), m_listeners.end(), listener) != m_listeners.end()) {
			Debug::logger << "The same listener has already been added!" << Debug::endError;
			return;
		}
		m_listeners.push_back(listener);
	}

	void removeListener(TEventListener* listener) {
		auto found{ std::find(m_listeners.begin(), m_listeners.end(), listener) };
		if (found == m_listeners.end()) return;
		m_listeners.erase(found);
	}

protected:
	void notifyListeners(std::function<void(TEventListener*)> func) {
		for (auto* listener : m_listeners) {
			func(listener);
		}
	}

private:
	std::vector<TEventListener*> m_listeners{};

};
