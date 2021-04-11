#ifndef EVENT_HPP
#define EVENT_HPP

class Event {
};

class QuitEvent : public Event {
};

enum Button {
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_ESCAPE
};

enum EventDirection {
	UP,
	DOWN
};

class ButtonEvent : public Event {
public:
	Button button;
	EventDirection direction;
};

enum MouseButton {
	LEFT,
	RIGHT,
	MIDDLE
};

class MouseButtonEvent : public ButtonEvent {
public:
	MouseButton button;
};

class ScrollEvent : public Event {
public:
	int dist;
};

class MouseMoveEvent : public Event {
public:
	int x;
	int y;
};

#endif // EVENT
