#include "pch.h"
#include "InputManager.h"

CommonUtilities::InputManager::InputManager()
{
    for (size_t i = 0; i <= 0xff; i++)
    {
        myCurrentKeyMap[i] = false;
    }
    for (size_t i = 0; i < static_cast<int>(eMouseInput::eEnd); i++)
    {
        myMouseMap[static_cast<eMouseInput>(i)] = false;
    }
    LockMouseToWindow(true);
}

bool CommonUtilities::InputManager::IsKeyPressed(const int aKeyCode) const
{
    return myCurrentKeyMap.at(aKeyCode) && !myPreviousKeyMap.at(aKeyCode);
}

bool CommonUtilities::InputManager::IsKeyDown(const int aKeyCode) const
{
    return myCurrentKeyMap.at(aKeyCode) && myPreviousKeyMap.at(aKeyCode);
}

bool CommonUtilities::InputManager::IsKeyUp(const int aKeyCode) const
{
    return !myCurrentKeyMap.at(aKeyCode) && myPreviousKeyMap.at(aKeyCode);
}

CommonUtilities::Vector2f  CommonUtilities::InputManager::GetMousePosition() const
{
    return myMousePosition;
}

CommonUtilities::Vector2f CommonUtilities::InputManager::GetMouseDelta() const { return myDelta; }

bool CommonUtilities::InputManager::GetMouseLDown() const
{
    return myMouseMap.at(eMouseInput::eLDown);
}

bool CommonUtilities::InputManager::GetMouseRDown() const
{
    return myMouseMap.at(eMouseInput::eRDown);
}

bool CommonUtilities::InputManager::GetMouseLReleased() const
{
    return myMouseMap.at(eMouseInput::eLUp);
}

bool CommonUtilities::InputManager::GetMouseRReleased() const
{
    return myMouseMap.at(eMouseInput::eRUp);
}

bool CommonUtilities::InputManager::GetMouseLPressed() const
{
    return myMouseMap.at(eMouseInput::eLPressed);
}

bool CommonUtilities::InputManager::GetMouseRPressed() const
{
    return myMouseMap.at(eMouseInput::eRPressed);
}

bool CommonUtilities::InputManager::GetMouseMDown() const
{
    return myMouseMap.at(eMouseInput::eMiddleDown);
}

bool CommonUtilities::InputManager::GetMouseMReleased() const
{
    return myMouseMap.at(eMouseInput::eMiddleUp);
}

bool CommonUtilities::InputManager::GetMouseMPressed() const
{
    return myMouseMap.at(eMouseInput::eMiddlePressed);
}

float CommonUtilities::InputManager::GetScroll() const { return myScroll; }

void CommonUtilities::InputManager::Update()
{
    myPreviousKeyMap = myCurrentKeyMap;
    for (int i = 0; i <= 0xff; i++)
    {
        myCurrentKeyMap[i] = GetAsyncKeyState(i);
    }
}

void CommonUtilities::InputManager::SetMousePos(const Vector2f aPosition)
{
    POINT tempPoint;
    tempPoint.x = aPosition.x;
    tempPoint.y = aPosition.y;
    ClientToScreen(GetActiveWindow(), &tempPoint);
    SetCursorPos(tempPoint.x, tempPoint.y);
}

void CommonUtilities::InputManager::LockMouseToWindow(bool aLockMouse)
{
    if (aLockMouse)
    {
        RECT rect;
        GetClientRect(GetActiveWindow(), &rect);

        POINT upperL;
        upperL.x = rect.left;
        upperL.y = rect.top;

        POINT lowerR;
        lowerR.x = rect.right;
        lowerR.y = rect.bottom;
        MapWindowPoints(GetActiveWindow(), nullptr, &upperL, 1);
        MapWindowPoints(GetActiveWindow(), nullptr, &lowerR, 1);

        rect.left = upperL.x;
        rect.top = upperL.y;
        rect.right = lowerR.x;
        rect.bottom = lowerR.y;
        ClipCursor(&rect);
    }
    else
    {
        ClipCursor(nullptr);
    }
}

bool CommonUtilities::InputManager::UpdateMouseInputEvents(HWND hwndMain, UINT message, WPARAM wParam, LPARAM lParam)
{

    POINT cursorPosition{ 0 , 0 };
    myScroll = 0;

    for (size_t i = 0; i < static_cast<int>(eMouseInput::eLDown); i++)
    {
        myMouseMap[static_cast<eMouseInput>(i)] = false;
    }


    switch (message)
    {

    case WM_MOUSEMOVE:
        GetCursorPos(&cursorPosition);
        ScreenToClient(hwndMain, &cursorPosition);

        myDelta.x = myMousePosition.x - cursorPosition.x;
        myDelta.y = myMousePosition.y - cursorPosition.y;
        myMousePosition.x = cursorPosition.x;
        myMousePosition.y = cursorPosition.y;
        return true;

    case WM_LBUTTONDOWN:
        myMouseMap[eMouseInput::eLPressed] = true;
        myMouseMap[eMouseInput::eLDown] = true;
        return true;
    case WM_LBUTTONUP:
        myMouseMap[eMouseInput::eLUp] = true;
        myMouseMap[eMouseInput::eLDown] = false;
        return true;
    case WM_RBUTTONDOWN:
        myMouseMap[eMouseInput::eRPressed] = true;
        myMouseMap[eMouseInput::eRDown] = true;
        return true;
    case WM_RBUTTONUP:
        myMouseMap[eMouseInput::eRUp] = true;
        myMouseMap[eMouseInput::eRDown] = false;
        return true;
    case WM_MBUTTONDOWN:
        myMouseMap[eMouseInput::eMiddlePressed] = true;
        myMouseMap[eMouseInput::eMiddleDown] = true;
        return true;
    case WM_MBUTTONUP:
        myMouseMap[eMouseInput::eMiddleUp] = true;
        myMouseMap[eMouseInput::eMiddleDown] = false;
        return true;
    case WM_MOUSEWHEEL:
        myScroll = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
        return true;
    }

    return false;
}

void CommonUtilities::InputManager::BindCustomKeys(int aCustomKey, std::initializer_list<int> aKeyCodes)
{
    for (auto& keyCode : aKeyCodes)
    {
        myCustomKeyBindings[aCustomKey].push_back(keyCode);
    }
}

bool CommonUtilities::InputManager::IsCustomKeyDown(int aCustomKey) const
{
    for (auto& keyCode : myCustomKeyBindings.at(aCustomKey))
    {
        if (IsKeyDown(keyCode))
        {
            return true;
        }
    }

    // None of the keys were held down
    return false;
}

bool CommonUtilities::InputManager::IsCustomKeyPressed(int aCustomKey) const
{
    for (auto& keyCode : myCustomKeyBindings.at(aCustomKey))
    {
        if (IsKeyPressed(keyCode))
        {
            return true;
        }
    }

    // None of the keys were pressed
    return false;
}
