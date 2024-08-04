/*************************************************************************
【文件名】 FacesConsoleView.hpp
【功能模块和目的】 FacesConsoleView 类是操作面时显示的视图。
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
【类名】 FacesConsoleView
【功能】 操作面时显示的视图。
【接口说明】 继承自 ConsoleViewBase。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class FacesConsoleView: public ConsoleViewBase {
    public:
        // 构造函数

        // 使用基类的构造函数
        using ConsoleViewBase::ConsoleViewBase;
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与标准输入/输出流初始化 FacesConsoleView 类型实例。
        【参数】
            controller: 控制器指针。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        FacesConsoleView(shared_ptr<ControllerBase> controller);
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与指定输入/输出流初始化 FacesConsoleView 类型实例。
        【参数】
            controller: 控制器指针。
            input: 输入流。
            output: 输出流。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        FacesConsoleView(
            shared_ptr<ControllerBase> controller,
            istream& input,
            ostream& output
        );
        
    private:
        /**********************************************************************
        【函数名称】 CommandListFaces
        【函数功能】 实现 list 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandListFaces() const;
        /**********************************************************************
        【函数名称】 CommandGetFace
        【函数功能】 实现 get 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandGetFace() const;
        /**********************************************************************
        【函数名称】 CommandAddFace
        【函数功能】 实现 add 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandAddFace() const;
        /**********************************************************************
        【函数名称】 CommandModifyFace
        【函数功能】 实现 edit 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandModifyFace() const;
        /**********************************************************************
        【函数名称】 CommandRemoveFace
        【函数功能】 实现 del 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandRemoveFace() const;
};

}