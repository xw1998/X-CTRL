#include "ButtonEvent.h"

//说明：按键事件构造函数
//参数：引脚编号；按键释放时的状态；长按超时设置
ButtonEvent::ButtonEvent(uint8_t Pin, bool NoPressState, uint16_t LongPressTimeMs_Set)
{
    Button_Pin = Pin;
    Button_NoPressState = NoPressState;
    LongPressTimeMs = LongPressTimeMs_Set;

    PressKey_TimePoint = 0;
    IS_Pressed = false;

    ButtonPress_Function = 0;
    ButtonLongPress_Function = 0;
    ButtonRelease_Function = 0;
    ButtonChange_Function = 0;
}

ButtonEvent::ButtonEvent(bool NoPressState, uint16_t LongPressTimeMs_Set)
{
    Button_NoPressState = NoPressState;
    LongPressTimeMs = LongPressTimeMs_Set;

    PressKey_TimePoint = 0;
    IS_Pressed = false;

    ButtonPress_Function = 0;
    ButtonLongPress_Function = 0;
    ButtonRelease_Function = 0;
    ButtonChange_Function = 0;
}

//说明：按键初始化函数
//参数：按键所接IO模式配置
void ButtonEvent::Init(uint8_t PinMode)
{
    pinMode(Button_Pin, PinMode);
}

//说明：按键按下事件绑定
//参数：回调函数指针
void ButtonEvent::EventAttach_Press(ButtonEvent_FuncCallBack_t Function)
{
    ButtonPress_Function = Function;
}

//说明：按键长按事件绑定
//参数：回调函数指针
void ButtonEvent::EventAttach_LongPress(ButtonEvent_FuncCallBack_t Function)
{
    ButtonLongPress_Function = Function;
}

//说明：按键释放事件绑定
//参数：回调函数指针
void ButtonEvent::EventAttach_Release(ButtonEvent_FuncCallBack_t Function)
{
    ButtonRelease_Function = Function;
}

//说明：按键改变事件绑定
//参数：回调函数指针
void ButtonEvent::EventAttach_Change(ButtonEvent_FuncCallBack_t Function)
{
    ButtonChange_Function = Function;
}

//说明：用软件消抖的方式读取按键
//参数：无
void ButtonEvent::Read_WipeShake()
{
#define IS_ButtonDown() (digitalRead(Button_Pin) != Button_NoPressState)
    if (!IS_Pressed && IS_ButtonDown())
    {
        delay(10);
        if (IS_ButtonDown())
        {
            Button_NowState = IS_Pressed = true;
            PressKey_TimePoint = millis() + LongPressTimeMs;
            if(ButtonPress_Function)ButtonPress_Function();
            if(ButtonChange_Function)ButtonChange_Function();
        }
    }
    else if (IS_Pressed && millis() >= PressKey_TimePoint && IS_ButtonDown())
    {
        Button_NowState = true;
        if(ButtonLongPress_Function)ButtonLongPress_Function();
    }
    else if (IS_Pressed && !IS_ButtonDown())
    {
        delay(10);
        if (!IS_ButtonDown())
        {
            Button_NowState = IS_Pressed = false;
            if(ButtonRelease_Function)ButtonRelease_Function();
            if(ButtonChange_Function)ButtonChange_Function();
        }
    }
}

//说明：直接读取按键
//参数：按键IO的状态
void ButtonEvent::Read_NoWipeShake(uint8_t NowState)
{
    if (!IS_Pressed && (NowState != Button_NoPressState))
    {
        Button_NowState = IS_Pressed = true;
        PressKey_TimePoint = millis() + LongPressTimeMs;
        if(ButtonPress_Function) ButtonPress_Function();
        if(ButtonChange_Function)ButtonChange_Function();
    }
    else if (IS_Pressed && millis() >= PressKey_TimePoint && (NowState != Button_NoPressState))
    {
        Button_NowState = true;
        if(ButtonLongPress_Function) ButtonLongPress_Function();
    }
    else if (IS_Pressed && (NowState == Button_NoPressState))
    {
        Button_NowState = IS_Pressed = false;
        if(ButtonRelease_Function) ButtonRelease_Function();
        if(ButtonChange_Function) ButtonChange_Function();
    }
}

//说明：重映射引脚
//参数：引脚编号，IO输入模式
void ButtonEvent::Remap_Pin(uint8_t Pin, uint8_t PinMode)
{
    Button_Pin = Pin;
    pinMode(Button_Pin, PinMode);
}

//说明：获取按键状态
//参数：无
bool ButtonEvent::GetState()
{
    return Button_NowState;
}

//说明：清除按键状态
//参数：无
void ButtonEvent::ClearState()
{
    Button_NowState = false;
}
