/*************************************************************************
【文件名】 FacesConsoleView.hpp
【功能模块和目的】 FacesConsoleView 类是操作面时显示的视图。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef FACES_CONSOLE_VIEW_HPP
#define FACES_CONSOLE_VIEW_HPP

#include <iostream>
#include <memory>
#include <string>
#include "ConsoleViewBase.hpp"
#include "../../Controllers/ControllerBase.hpp"
using namespace std;
using namespace C3w::Controllers;

namespace C3w {

namespace Views {

namespace Cli {

/*************************************************************************
【类名】 FacesConsoleView
【功能】 操作面时显示的视图。
【接口说明】
    继承于 C3w::Views::ConsoleViewBase:
        继承全部接口。
        重写 ResultToString。
    构造与析构：
        接受控制器指针的构造函数。
        接受控制器指针与输入/输出流的构造函数。
    操作：
        CommandListFaces: 实现 list 命令。
        CommandGetFace: 实现 get 命令。
        CommandAddFace: 实现 add 命令。
        CommandModifyFace: 实现 edit 命令。
        CommandRemoveFace: 实现 del 命令。
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
            Controller: 控制器指针。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        FacesConsoleView(shared_ptr<ControllerBase> Controller);
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与指定输入/输出流初始化 FacesConsoleView 类型实例。
        【参数】
            Controller: 控制器指针。
            Input: 输入流。
            Output: 输出流。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        FacesConsoleView(
            shared_ptr<ControllerBase> Controller,
            istream& Input,
            ostream& Output
        );
    
    protected:
        /**********************************************************************
        【函数名称】 ResultToString
        【函数功能】 将命令返回的结果转化为字符串。
        【参数】
            AResult: 要转化的 ConsoleViewBase::Result 枚举。
        【返回值】
            结果的字符串表示形式。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        string ResultToString(Result AResult) const override;
        
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

}

}

#endif