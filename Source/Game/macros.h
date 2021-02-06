#pragma once
#define PP_CONCAT_NX(A, B) A ## B
#define PP_CONCAT(A, B) PP_CONCAT_NX(A, B)
#define SAFE_CREATE(aPointer, aClass) aPointer = new aClass
#define SAFE_DELETE(aPointer) if (aPointer) delete aPointer; aPointer = nullptr
#define SAFE_INIT(aPointer) if (aPointer != nullptr) aPointer = nullptr
#define SAFE_DELETE_VECTOR(anStdVector)									\
for (auto& PP_CONCAT(aMacroPointerAtLine, __LINE__) : anStdVector) {	\
	SAFE_DELETE(PP_CONCAT(aMacroPointerAtLine, __LINE__));				\
}

#pragma region Common Key Codes
#define KEY_ESCAPE		27
#define KEY_SPACE		32
#define KEY_ENTER		13
#define KEY_BACKSPACE	8
#define KEY_TAB			9
// Unclear wether this is left or right shift key
#define KEY_SHIFT		16
// Unclear wether this is left or right control key
#define KEY_CTRL		17
#define KEY_0			48
#define KEY_1			49
#define KEY_2			50
#define KEY_3			51
#define KEY_4			52
#define KEY_5			53
#define KEY_6			54
#define KEY_7			55
#define KEY_8			56
#define KEY_9			57
#define KEY_NUMPAD_0	96
#define KEY_NUMPAD_1	97
#define KEY_NUMPAD_2	98
#define KEY_NUMPAD_3	99
#define KEY_NUMPAD_4	100
#define KEY_NUMPAD_5	101
#define KEY_NUMPAD_6	102
#define KEY_NUMPAD_7	103
#define KEY_NUMPAD_8	104
#define KEY_NUMPAD_9	105
#pragma endregion

#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH  1920
// Used in conjunction with SETCONSOLECOLOR as a color reset
#define CONSOLE_COLOR_WHITE	 15
// Used in conjunction with SETCONSOLECOLOR to indicate an error
#define CONSOLE_COLOR_RED	 12
// Used in conjunction with SETCONSOLECOLOR to indicate a warning
#define CONSOLE_COLOR_YELLOW 14

#define CONSOLE_COLOR_CYAN 11

#define CONSOLE_COLOR_NORMAL	CONSOLE_COLOR_WHITE
#define CONSOLE_COLOR_WARNING	CONSOLE_COLOR_YELLOW
#define CONSOLE_COLOR_ERROR		CONSOLE_COLOR_RED
#define CONSOLE_COLOR_ONE_TIME	CONSOLE_COLOR_CYAN

#define MATH_PI std::acos(-1.0f)

#define DELTA_TIME Timer::GetInstance()->TGetDeltaTime()