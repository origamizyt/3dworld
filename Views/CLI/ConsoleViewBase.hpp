/*************************************************************************
【文件名】 ConsoleViewBase.hpp
【功能模块和目的】 ConsoleViewBase 类是所有控制台视图的基类。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef CONSOLE_VIEW_BASE_HPP
#define CONSOLE_VIEW_BASE_HPP

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "../ViewBase.hpp"
#include "../../Controllers/ControllerBase.hpp"
using namespace std;
using namespace C3w::Controllers;

namespace C3w {

namespace Views {

namespace Cli {

/*************************************************************************
【类名】 ConsoleViewBase
【功能】 所有视图的基类。
【接口说明】 
    继承于 C3w::Views::ViewBase:
        继承所有成员。
        实现 Display，循环提示用户输入命令。
    成员：
        Input: 输入流引用。
        Output: 输出流引用。
    构造与析构：
        接受控制器指针的构造函数。
        接受控制器指针与输入/输出流的构造函数。
        删除拷贝构造函数。
        删除移动构造函数。
    内嵌类型：
        Result: 与 ControllerBase::Result 正数部分相同，
                添加负数以处理 ConsoleViewBase 特有的异常。
        Palette: 枚举，表示屏幕显示的颜色。
        Command: 存储命令的结构。
    操作：
        Ask (protected): 询问用户特定问题。
        Select (protected): 让用户在选项中选择一项。
        ResultToString (protected): 将 Result 转化为字符串，虚函数。
        RegisterCommand (protected): 注册一个命令。子类应调用此函数。
        ShowHelp (protected): 显示帮助信息，用于 "?" 命令，虚函数。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class ConsoleViewBase: public ViewBase {
    public:
        // 构造函数

        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与标准输入/输出流初始化 ConsoleViewBase 类型实例。
        【参数】
            Controller: 控制器指针。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        ConsoleViewBase(shared_ptr<ControllerBase> Controller);
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与指定输入/输出流初始化 ConsoleViewBase 类型实例。
        【参数】
            Controller: 控制器指针。
            Input: 输入流。
            Output: 输出流。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        ConsoleViewBase(
            shared_ptr<ControllerBase> Controller, 
            istream& Input, 
            ostream& Output
        );
        // 删除拷贝构造函数
        ConsoleViewBase(const ConsoleViewBase& Other) = delete;
        // 删除移动构造函数
        ConsoleViewBase(ConsoleViewBase&& Other) = delete;

        // 成员
        
        // 输入流
        istream& Input;
        // 输出流
        ostream& Output;
        
        // 操作

        /**********************************************************************
        【函数名称】 Display
        【函数功能】 向用户展示此视图。
        【参数】 无
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void Display() override;

    protected:
        // 询问命令时的提示符
        string m_Prompt;

        /**********************************************************************
        【函数名称】 Ask
        【函数功能】 向控制台输出提示符并读入一行。
        【参数】
            Prompt: 询问的提示。
            Trim: 是否去除多余的空白字符。
        【返回值】
            从输入流读入的一行。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        string Ask(string Prompt, bool Trim = false) const;
        /**********************************************************************
        【函数名称】 Choose
        【函数功能】 让用户在选项中做出选择。
        【参数】
            Prompt: 询问的提示。
            Choices: 选项组成的向量。
        【返回值】
            用户选择的项，从 1 开始。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        size_t Select(string Prompt, const vector<string>& Choices) const;

        /**********************************************************************
        【类名】 Result
        【功能】 一个枚举，用于命令的返回值。
        【接口说明】 枚举，用于命令的返回值。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        enum class Result: short {
            INVALID_VALUE = -1,
            // 以下与 ControllerBase::Result 一致

            OK = 0,
            STORAGE_LOOKUP_ERROR,
            FILE_OPEN_ERROR,
            FILE_FORMAT_ERROR,
            INDEX_OVERFLOW,
            POINT_INDEX_OVERFLOW,
            POINT_COLLISION,
            ELEMENT_COLLISION
        };
        
        /**********************************************************************
        【函数名称】 ResultToString
        【函数功能】 将命令返回的结果转化为字符串。
        【参数】
            AResult: 要转化的 ConsoleViewBase::Result 枚举。
        【返回值】
            结果的字符串表示形式。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual string ResultToString(Result AResult) const;
        /**********************************************************************
        【函数名称】 RegisterCommand
        【函数功能】 注册一个基于回调的命令。
        【参数】
            Name: 命令名称。
            Handler: 命令处理器。
            Help: 命令帮助字符串。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void RegisterCommand(
            string Name, 
            function<Result()> Handler,
            string Help
        );

        /**********************************************************************
        【函数名称】 ShowHelp
        【函数功能】 显示帮助信息。
        【参数】 无
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual void ShowHelp() const;

        /**********************************************************************
        【类名】 Palette
        【功能】 一个颜色的枚举。
        【接口说明】 枚举，表示控制台显示的颜色。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        enum class Palette: short {
            CLEAR = 0,
            FG_GRAY = 90,
            FG_RED,
            FG_GREEN,
            FG_YELLOW,
            FG_BLUE,
            FG_PURPLE,
            FG_CYAN,
            FG_WHITE,
            BG_GRAY = 40,
            BG_RED,
            BG_GREEN,
            BG_YELLOW,
            BG_BLUE,
            BG_PURPLE,
            BG_CYAN,
            BG_WHITE,
        };

    private:
        // 存储命令的结构体
        struct Command {
            function<Result()> Handler;
            string Help;
        };
        // 存储命令的表
        map<string, Command> m_Commands;

        /**********************************************************************
        【函数名称】 Likelihood
        【函数功能】 计算两个字符串的相似程度。
        【参数】 
            Given: 用户提供的字符串。
            Has: 原有的字符串。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        static float Likelihood(string Given, string Has);

    /**********************************************************************
    【函数名称】 operator<<
    【函数功能】 将指定的颜色显示到流上。
    【参数】
        Stream: 要输出的流。
        APalette: 要显示的颜色。
    【返回值】 
        输出流的引用。
    【开发者及日期】 赵一彤 2024/7/24
    **********************************************************************/
    friend ostream& operator<<(
        ostream& Stream, 
        Palette APalette
    );
};

}

}

}

#endif