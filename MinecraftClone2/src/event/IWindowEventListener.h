#pragma once

class Window;

class IWindowEventListener {
public:
	virtual ~IWindowEventListener() = default;

	virtual void onWindowSizeChanged(Window& window) {}
};