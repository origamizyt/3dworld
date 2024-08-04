/*************************************************************************
【文件名】 LinesConsoleView.hpp
【功能模块和目的】 LinesConsoleView 类是操作线段时显示的视图。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#pragma once

#include <iostream>
#include <memory>
#include "ConsoleViewBase.hpp"
#include "../../Controllers/ControllerBase.hpp"
using namespace std;
using namespace c3w::controllers;

namespace c3w::views::cli {

/*************************************************************************
【类名】 LinesConsoleView
【功能】 操作线段时显示的视图。
【接口说明】 继承自 ConsoleViewBase。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class LinesConsoleView: public ConsoleViewBase {
    public:
        // 构造函数

        // 使用基类的构造函数
        using ConsoleViewBase::ConsoleViewBase;
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与标准输入/输出流初始化 LinesConsoleView 类型实例。
        【参数】
            controller: 控制器指针。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        LinesConsoleView(shared_ptr<ControllerBase> controller);
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与指定输入/输出流初始化 LinesConsoleView 类型实例。
        【参数】
            controller: 控制器指针。
            input: 输入流。
            output: 输出流。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        LinesConsoleView(
            shared_ptr<ControllerBase> controller,
            istream& input,
            ostream& output
        );
        
    private:
        /**********************************************************************
        【函数名称】 CommandListLines
        【函数功能】 实现 list 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandListLines() const;
        /**********************************************************************
        【函数名称】 CommandGetLine
        【函数功能】 实现 get 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandGetLine() const;
        /**********************************************************************
        【函数名称】 CommandAddLine
        【函数功能】 实现 add 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandAddLine() const;
        /**********************************************************************
        【函数名称】 CommandModifyLine
        【函数功能】 实现 edit 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandModifyLine() const;
        /**********************************************************************
        【函数名称】 CommandRemoveLine
        【函数功能】 实现 del 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandRemoveLine() const;
};

}