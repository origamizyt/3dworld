/*************************************************************************
【文件名】 LinesConsoleView.cpp
【功能模块和目的】 为 LinesConsoleView.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "ConsoleViewBase.hpp"
#include "../../Controllers/ControllerBase.hpp"
#include "LinesConsoleView.hpp"
using namespace std;
using namespace C3w::Controllers;

namespace C3w {

namespace Views {

namespace Cli {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用控制器与标准输入/输出流初始化 LinesConsoleView 类型实例。
【参数】
    Controller: 控制器指针。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
LinesConsoleView::LinesConsoleView(shared_ptr<ControllerBase> Controller)
    : LinesConsoleView(Controller, cin, cout) {}

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
LinesConsoleView::LinesConsoleView(
    shared_ptr<ControllerBase> Controller,
    istream& Input,
    ostream& Output
): ConsoleViewBase(Controller, Input, Output) {
    m_Prompt = "lines#> ";
    RegisterCommand(
        "list",
        bind(&LinesConsoleView::CommandListLines, this),
        "Lists all lines in model."
    );
    RegisterCommand(
        "get",
        bind(&LinesConsoleView::CommandGetLine, this),
        "Describes given line."
    );
    RegisterCommand(
        "add",
        bind(&LinesConsoleView::CommandAddLine, this),
        "Adds a line to model."
    );
    RegisterCommand(
        "edit",
        bind(&LinesConsoleView::CommandModifyLine, this),
        "Modifies a line in model."
    );
    RegisterCommand(
        "del",
        bind(&LinesConsoleView::CommandRemoveLine, this),
        "Removes a line from model."
    );
}

/**********************************************************************
【函数名称】 ResultToString
【函数功能】 将命令返回的结果转化为字符串。
【参数】
    AResult: 要转化的 ConsoleViewBase::Result 枚举。
【返回值】
    结果的字符串表示形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string LinesConsoleView::ResultToString(Result AResult) const {
    switch (AResult) {
        case Result::POINT_COLLISION: {
            return "Identical point already exists in line.";
        }
        case Result::ELEMENT_COLLISION: {
            return "Identical line already exists in model.";
        }
        default: {
            return ConsoleViewBase::ResultToString(AResult);
        }
    }
}

/**********************************************************************
【函数名称】 CommandListLines
【函数功能】 实现 list 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result LinesConsoleView::CommandListLines() const {
    auto Lines = m_pController->GetLines();
    Output << Palette::FG_BLUE << "Lines in '" << m_pController->GetName();
    Output << "' (" << Lines.size() << "):" << Palette::CLEAR << endl;
    for (size_t i = 0; i < Lines.size(); i++) {
        Output << i + 1 << ". ";
        switch (Lines[i].ElementStatus) {
            case ControllerBase::Status::CREATED: {
                Output << Palette::FG_CYAN;
                break;
            }
            case ControllerBase::Status::MODIFIED: {
                Output << Palette::FG_YELLOW;
                break;
            }
        }
        Output << Lines[i].String << Palette::CLEAR << endl;
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 CommandGetLine
【函数功能】 实现 get 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result LinesConsoleView::CommandGetLine() const {
    istringstream Stream(Ask("Index of desired line (1~): "));
    size_t Index;
    Stream >> Index;
    if (Stream.bad()) {
        return Result::INDEX_OVERFLOW;
    }
    vector<string> Points;
    auto Res = static_cast<Result>(
        m_pController->GetLinePoints(Index - 1, Points)
    );
    if (Res == Result::OK) {
        Output << Palette::FG_PURPLE << "Points in line #" << Index;
        Output << ":" << Palette::CLEAR << endl;
        for (size_t i = 0; i < Points.size(); i++) {
            Output << "  " << i + 1 << ". " << Points[i] << endl;
        }
    }
    return Res;
}

/**********************************************************************
【函数名称】 CommandAddLine
【函数功能】 实现 add 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result LinesConsoleView::CommandAddLine() const {
    istringstream First(Ask("1st point (x y z): "));
    double x1;
    double y1;
    double z1;
    First >> x1 >> y1 >> z1;
    if (First.bad()) {
        return Result::INVALID_VALUE;
    }
    istringstream Second(Ask("2nd point (x y z): "));
    double x2;
    double y2;
    double z2;
    Second >> x2 >> y2 >> z2;
    if (Second.bad()) {
        return Result::INVALID_VALUE;
    }
    auto Res = static_cast<Result>(
        m_pController->AddLine(x1, y1, z1, x2, y2, z2)
    );
    if (Res == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully added line.";
        Output << Palette::CLEAR << endl;
    }
    return Res;
}

/**********************************************************************
【函数名称】 CommandModifyLine
【函数功能】 实现 edit 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result LinesConsoleView::CommandModifyLine() const {
    vector<string> Choices;
    for (auto& Line: m_pController->GetLines()) {
        Choices.push_back(Line.String);
    }
    size_t Index = Select("Select a line to modify:", Choices);
    if (Index == 0) {
        return Result::INVALID_VALUE;
    }
    Choices.clear();
    auto Res = static_cast<Result>(
        m_pController->GetLinePoints(Index - 1, Choices)
    );
    if (Res != Result::OK) {
        return Res;
    }
    size_t PointIndex = Select("Select a point to modify:", Choices);
    if (PointIndex == 0) {
        return Result::INVALID_VALUE;
    }
    istringstream Coords(Ask("Set point to (x y z): "));
    double x;
    double y;
    double z;
    Coords >> x >> y >> z;
    if (Coords.bad()) {
        return Result::INVALID_VALUE;
    }
    Res = static_cast<Result>(
        m_pController->ModifyLine(Index - 1, PointIndex - 1, x, y, z)
    );
    if (Res == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully modified line #" << Index;
        Output << "." << Palette::CLEAR << endl;
    }
    return Res;
}

/**********************************************************************
【函数名称】 CommandRemoveLine
【函数功能】 实现 del 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result LinesConsoleView::CommandRemoveLine() const {
    vector<string> Choices;
    for (auto& Line: m_pController->GetLines()) {
        Choices.push_back(Line.String);
    }
    size_t Index = Select("Select a line to delete:", Choices);
    if (Index == 0) {
        return Result::INVALID_VALUE;
    }
    auto Res = static_cast<Result>(m_pController->RemoveLine(Index - 1));
    if (Res == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully deleted line #" << Index;
        Output << "." << Palette::CLEAR << endl;
    }
    return Res;
}

}

}

}