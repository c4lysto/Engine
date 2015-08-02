#ifndef _RECON_INPUT_H_
#define _RECON_INPUT_H_

#include "../Utilities/UtilitiesInclude.h"
#include "../Math Lib/MathLib.h"
#include "../Utilities/Function.h"

#if RECON_OS_64BIT
typedef long long QWORD;
#endif

namespace recon
{

enum class InputState : unsigned char
{
	Pressed		= 0x0,
	Down		= 0x1,
	Released	= 0x2,
	Changed		= 0x4
};

enum class InputDevice : unsigned char
{
	None		= 0x0,
	Mouse		= 0x1,
	Keyboard	= 0x2,
	Gamepad1	= 0x4,
	Gamepad2	= 0x8,
	Gamepad3	= 0x10,
	Gamepad4	= 0x20,

	GamepadAny	= (Gamepad1 | Gamepad2 | Gamepad3 | Gamepad4)
};

enum class InputModifier : unsigned char
{
	None	= 0,
	LCtrl	= 0x1,
	LShift	= 0x2,
	LAlt	= 0x4,
	RCtrl	= 0x8,
	RShift	= 0x10,
	RAlt	= 0x20,

	Ctrl	= (LCtrl | RCtrl),
	Shift	= (LShift | RShift),
	Alt		= (LAlt | RAlt)
};

enum class InputID : unsigned short
{
	// Keyboard
	None	= 0,
	Esc		= 1,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	ZERO,
	Minus,
	Equals,
	Backspace,
	Tab,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	LBracket,
	RBracket,
	Enter,
	LCtrl,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Semicolon,
	Apostrophe,
	Tilde,
	LShift,
	Backslash,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	Comma,
	Period,
	Slash,
	RShift,
	NUM_Asterisk,
	LAlt,
	Space,
	CapsLock,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	NumLock,
	ScrollLock,
	NUM_7,
	NUM_8,
	NUM_9,
	NUM_Minus,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_Plus,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_0,
	NUM_Period,
	NUM_Divide	= (53 | 0x80),			// 53 + (flags & (0x2))
	NUM_Enter	= (28 | 0x80),			// 28 + (flags & (0x2))
	// 86 is skipped for some reason...
	F11			= 87,					// 87
	F12,								// 88
	Insert		= (82 | (0x80)),		// 82 + (flags & (0x2))
	Delete		= (83 | (0x80)),		// 83 + (flags & (0x2))
	Home		= (71 | (0x80)),		// 71 + (flags & (0x2))
	End			= (79 | (0x80)),		// 79 + (flags & (0x2))
	PageUp		= (73 | (0x80)),		// 73 + (flags & (0x2))
	PageDown	= (81 | (0x80)),		// 81 + (flags & (0x2))
	Left		= (75 | (0x80)),		// 75 + (flags & (0x2))
	Right		= (77 | (0x80)),		// 77 + (flags & (0x2))
	Up			= (72 | (0x80)),		// 72 + (flags & (0x2))
	Down		= (80 | (0x80)),		// 80 + (flags & (0x2))
	RAlt		= (56 | (0x80)),		// 56 + (flags & (0x2))
	RCtrl		= (29 | (0x80)),		// 29 + (flags & (0x2))

	// Mouse
	MouseButton1 = 0x100,
	MouseLButton = MouseButton1,
	MouseButton2,
	MouseRButton = MouseButton2,
	MouseButton3,
	MouseMButton = MouseButton3,
	MouseButton4,
	MouseButton5,
	MouseWheelUp,
	MouseWheelDown,
	MouseMove
};

struct InputEvent
{
	InputID m_eInputID			: 16;
	InputState m_eInputState	: 4;
	InputModifier m_eModifiers	: 6;
	InputDevice m_eDeviceID		: 6;

	InputEvent() : m_eInputID(InputID::None), m_eDeviceID(InputDevice::None), m_eInputState(InputState::Changed), m_eModifiers(InputModifier::None) {}
	InputEvent(InputDevice eDID) : m_eDeviceID(eDID) {}
	InputEvent(InputDevice eDID, InputID eKID, InputState eIS, InputModifier eModifiers = InputModifier::None)
			: m_eDeviceID(eDID), m_eInputID(eKID), m_eInputState(eIS), m_eModifiers(eModifiers) {}

	virtual ~InputEvent() {}

	bool operator==(const InputEvent& rhs) const
	{
		if(m_eInputID != rhs.m_eInputID)
			return false;
		if(m_eInputState < rhs.m_eInputState)
			return false;
		if(m_eModifiers < rhs.m_eModifiers)
			return false;
		if(m_eDeviceID < rhs.m_eDeviceID)
			return false;	

		return true;
	}

	bool operator<(const InputEvent& rhs) const
	{
		if((m_eInputID < rhs.m_eInputID) ||
		   (m_eInputState < rhs.m_eInputState) ||
		   (m_eModifiers < rhs.m_eModifiers) ||
		   (m_eDeviceID < rhs.m_eDeviceID))
		{
			return true;
		}

		return false;
	}

	bool IsSameButton(const InputEvent& rhs) const
	{
		if(m_eInputID != rhs.m_eInputID)
			return false;
		if(m_eInputState != rhs.m_eInputState)
			return false;
		if(m_eDeviceID != rhs.m_eDeviceID)
			return false;

		return true;
	}

	virtual InputEvent* MakeNewCopy() const
	{
		return new InputEvent(*this);
	}
};

struct InputMouseButtonEvent : public InputEvent
{
	Vec2f m_vMousePos;

	InputMouseButtonEvent() : InputEvent(InputDevice::Mouse, InputID::None, InputState::Down) {}
	InputMouseButtonEvent(InputID eKID, InputState eIS, InputModifier modifiers, Vec2f_In vCurrMousePos)
		: InputEvent(InputDevice::Mouse, eKID, eIS, modifiers), m_vMousePos(vCurrMousePos) {}

	virtual ~InputMouseButtonEvent() {}

	virtual InputEvent* MakeNewCopy() const
	{
		return new InputMouseButtonEvent(*this);
	}
};

struct InputMouseMoveEvent : public InputEvent
{
	Vec2f m_vMousePos;
	Vec2f m_vMouseMovement;

	InputMouseMoveEvent() : InputEvent(InputDevice::Mouse, InputID::MouseMove, InputState::Changed) {}
	InputMouseMoveEvent(Vec2f_In vCurrMousePos, Vec2f_In vCurrMouseMovement)
		: InputEvent(InputDevice::Mouse, InputID::MouseMove, InputState::Changed, InputModifier::None), m_vMousePos(vCurrMousePos), m_vMouseMovement(vCurrMouseMovement) {}

	virtual ~InputMouseMoveEvent() {}

	virtual InputEvent* MakeNewCopy() const
	{
		return new InputMouseMoveEvent(*this);
	}
};

typedef Function<void(const InputEvent&)> InputCallbackfn;

} // namespace recon

#endif