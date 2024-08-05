/*************************************************************************
【文件名】 ConsoleViewBase.hpp
【功能模块和目的】 ConsoleViewBase 类是所有控制台视图的基类。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#pragma once

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

namespace C3w::Views::Cli {

/*************************************************************************
【类名】 ConsoleViewBase
【功能】 所有视图的基类。
【接口说明】 基于命令的视图。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class ConsoleViewBase: public ViewBase {
    public:
        // 构造函数

        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与标准输入/输出流初始化 ConsoleViewBase 类型实例。
        【参数】
            controller: 控制器指针。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        ConsoleViewBase(shared_ptr<ControllerBase> controller);
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与指定输入/输出流初始化 ConsoleViewBase 类型实例。
        【参数】
            controller: 控制器指针。
            input: 输入流。
            output: 输出流。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        ConsoleViewBase(
            shared_ptr<ControllerBase> controller, 
            istream& input, 
            ostream& output
        );
        // 删除拷贝构造函数
        ConsoleViewBase(const ConsoleViewBase& other) = delete;
        // 删除移动构造函数
        ConsoleViewBase(ConsoleViewBase&& other) = delete;

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
        void Display() const override;

    protected:
        // 询问命令时的提示符
        string m_Prompt;

        /**********************************************************************
        【函数名称】 Ask
        【函数功能】 向控制台输出提示符并读入一行。
        【参数】
            prompt: 询问的提示。
            trim: 是否去除多余的空白字符。
        【返回值】
            从输入流读入的一行。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        string Ask(string prompt, bool trim = false) const;
        /**********************************************************************
        【函数名称】 Choose
        【函数功能】 让用户在选项中做出选择。
        【参数】
            prompt: 询问的提示。
            choices: 选项组成的向量。
        【返回值】
            用户选择的项，从 1 开始。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        size_t Select(string prompt, const vector<string>& choices) const;

        /**********************************************************************
        【类名】 Palette
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
        【函数功能】 将控制器返回的结果转化为字符串。
        【参数】
            result: 要转化的 ControllerBase::Result 枚举。
        【返回值】
            结果的字符串表示形式。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual string ResultToString(Result result) const;
        /**********************************************************************
        【函数名称】 RegisterCommand
        【函数功能】 注册一个基于回调的命令。
        【参数】
            name: 命令名称。
            handler: 命令处理器。
            help: 命令帮助字符串。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void RegisterCommand(
            string name, 
            function<Result()> handler,
            string help
        );

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
        【函数名称】 ShowHelp
        【函数功能】 显示帮助信息。
        【参数】 无
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void ShowHelp() const;

    /**********************************************************************
    【函数名称】 operator<<
    【函数功能】 将指定的颜色显示到流上。
    【参数】
        stream: 要输出的流。
        palette: 要显示的颜色。
    【返回值】 
        输出流的引用。
    【开发者及日期】 赵一彤 2024/7/24
    **********************************************************************/
    friend ostream& operator<<(
        ostream& stream, 
        Palette palette
    );
};

}