/*************************************************************************
【文件名】 MainConsoleView.hpp
【功能模块和目的】 MainConsoleView 类是程序入口显示的视图。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef MAIN_CONSOLE_VIEW_HPP
#define MAIN_CONSOLE_VIEW_HPP

#include "../../Controllers/ControllerBase.hpp"
#include "ConsoleViewBase.hpp"
using namespace std;
using namespace C3w::Controllers;

namespace C3w {

namespace Views {

namespace Cli {

/*************************************************************************
【类名】 MainConsoleView
【功能】 程序入口显示的视图。
【接口说明】 
    继承于 C3w::Views::ConsoleViewBase:
        继承所有接口。
        重写 Display，在循环前提示用户导入模型。
    构造函数：
        接受控制器指针的构造函数。
        接受控制器指针与输入/输出流的构造函数。
    操作：
        CommandLinesView (private): 实现 lines 命令。
        CommandFacesView (private): 实现 faces 命令。
        CommandShowStatistics (private): 实现 stat 命令。
        CommandSaveModel (private): 实现 save 命令。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class MainConsoleView: public ConsoleViewBase {
    public:
        // 构造函数

        // 使用基类的构造函数
        using ConsoleViewBase::ConsoleViewBase;
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与标准输入/输出流初始化 LinesConsoleView 类型实例。
        【参数】
            Controller: 控制器指针。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        MainConsoleView(shared_ptr<ControllerBase> Controller);
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 使用控制器与指定输入/输出流初始化 LinesConsoleView 类型实例。
        【参数】
            Controller: 控制器指针。
            Input: 输入流。
            Output: 输出流。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        MainConsoleView(
            shared_ptr<ControllerBase> Controller, 
            istream& Input, 
            ostream& Output
        );

        // 操作

        /**********************************************************************
        【函数名称】 Display
        【函数功能】 向用户展示此视图。
        【参数】 无
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void Display() const override;
    
    private:
        /**********************************************************************
        【函数名称】 CommandLinesView
        【函数功能】 实现 lines 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandLinesView() const;
        /**********************************************************************
        【函数名称】 CommandFacesView
        【函数功能】 实现 faces 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandFacesView() const;
        /**********************************************************************
        【函数名称】 CommandShowStatistics
        【函数功能】 实现 stat 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandShowStatistics() const;
        /**********************************************************************
        【函数名称】 CommandSaveModel
        【函数功能】 实现 save 命令。
        【参数】 无
        【返回值】
            命令发生的错误。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        Result CommandSaveModel() const;
};

}

}

}

#endif