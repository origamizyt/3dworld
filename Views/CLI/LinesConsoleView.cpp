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
        case Result::POINT_COLLISION : {
            return "Identical point already exists in line.";
        }
        case Result::ELEMENT_COLLISION : {
            return "Identical line already exists in model.";
        }
        default : {
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
            case ControllerBase::Status::CREATED : {
                Output << Palette::FG_CYAN;
                break;
            }
            case ControllerBase::Status::MODIFIED : {
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
    size_t ullIndex;
    Stream >> ullIndex;
    if (Stream.bad()) {
        return Result::INDEX_OVERFLOW;
    }
    vector<string> Points;
    Result Res = static_cast<Result>(
        m_pController->GetLinePoints(ullIndex - 1, Points)
    );
    if (Res == Result::OK) {
        Output << Palette::FG_PURPLE << "Points in line #" << ullIndex;
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
    double rX1;
    double rY1;
    double rZ1;
    First >> rX1 >> rY1 >> rZ1;
    if (First.bad()) {
        return Result::INVALID_VALUE;
    }
    istringstream Second(Ask("2nd point (x y z): "));
    double rX2;
    double rY2;
    double rZ2;
    Second >> rX2 >> rY2 >> rZ2;
    if (Second.bad()) {
        return Result::INVALID_VALUE;
    }
    Result Res = static_cast<Result>(
        m_pController->AddLine(rX1, rY1, rZ1, rX2, rY2, rZ2)
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
    size_t ullIndex = Select("Select a line to modify:", Choices);
    if (ullIndex == 0) {
        return Result::INVALID_VALUE;
    }
    Choices.clear();
    Result Res = static_cast<Result>(
        m_pController->GetLinePoints(ullIndex - 1, Choices)
    );
    if (Res != Result::OK) {
        return Res;
    }
    size_t ullPointIndex = Select("Select a point to modify:", Choices);
    if (ullPointIndex == 0) {
        return Result::INVALID_VALUE;
    }
    istringstream Coords(Ask("Set point to (x y z): "));
    double rX;
    double rY;
    double rZ;
    Coords >> rX >> rY >> rZ;
    if (Coords.bad()) {
        return Result::INVALID_VALUE;
    }
    Res = static_cast<Result>(
        m_pController->ModifyLine(ullIndex - 1, ullPointIndex - 1, rX, rY, rZ)
    );
    if (Res == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully modified line #";
        Output << ullIndex << "." << Palette::CLEAR << endl;
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
    size_t ullIndex = Select("Select a line to delete:", Choices);
    if (ullIndex == 0) {
        return Result::INVALID_VALUE;
    }
    Result Res = static_cast<Result>(m_pController->RemoveLine(ullIndex - 1));
    if (Res == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully deleted line #";
        Output << ullIndex << "." << Palette::CLEAR << endl;
    }
    return Res;
}

}

}

}