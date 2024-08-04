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

namespace c3w::views::cli {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用控制器与标准输入/输出流初始化 LinesConsoleView 类型实例。
【参数】
    controller: 控制器指针。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
LinesConsoleView::LinesConsoleView(shared_ptr<ControllerBase> controller)
    : LinesConsoleView(controller, cin, cout) {}

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
LinesConsoleView::LinesConsoleView(
    shared_ptr<ControllerBase> controller,
    istream& input,
    ostream& output
): ConsoleViewBase(controller, input, output) {
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
【函数名称】 CommandListLines
【函数功能】 实现 list 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result LinesConsoleView::CommandListLines() const {
    auto lines = m_pController->GetLines();
    Output << Palette::FG_BLUE << "Lines in '" << m_pController->GetName();
    Output << "' (" << lines.size() << "):" << Palette::CLEAR << endl;
    for (size_t i = 0; i < lines.size(); i++) {
        Output << i + 1 << ". ";
        switch (lines[i].ElementStatus) {
            case ControllerBase::Status::CREATED: {
                Output << Palette::FG_CYAN;
                break;
            }
            case ControllerBase::Status::MODIFIED: {
                Output << Palette::FG_YELLOW;
                break;
            }
        }
        Output << lines[i].String << Palette::CLEAR << endl;
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
    istringstream stream(Ask("Index of desired line (1~): "));
    size_t index;
    stream >> index;
    if (stream.bad()) {
        return Result::INDEX_OVERFLOW;
    }
    vector<string> points;
    auto result = static_cast<Result>(
        m_pController->GetLinePoints(index - 1, points)
    );
    if (result == Result::OK) {
        Output << Palette::FG_PURPLE << "Points in line #" << index;
        Output << ":" << Palette::CLEAR << endl;
        for (size_t i = 0; i < points.size(); i++) {
            Output << "  " << i + 1 << ". " << points[i] << endl;
        }
    }
    return result;
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
    istringstream first(Ask("1st point (x y z): "));
    double x1;
    double y1;
    double z1;
    first >> x1 >> y1 >> z1;
    if (first.bad()) {
        return Result::INVALID_VALUE;
    }
    istringstream second(Ask("2nd point (x y z): "));
    double x2;
    double y2;
    double z2;
    second >> x2 >> y2 >> z2;
    if (second.bad()) {
        return Result::INVALID_VALUE;
    }
    auto result = static_cast<Result>(
        m_pController->AddLine(x1, y1, z1, x2, y2, z2)
    );
    if (result == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully added line.";
        Output << Palette::CLEAR << endl;
    }
    return result;
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
    vector<string> choices;
    for (auto& line: m_pController->GetLines()) {
        choices.push_back(line.String);
    }
    size_t index = Select("Select a line to modify:", choices);
    if (index == 0) {
        return Result::INVALID_VALUE;
    }
    choices.clear();
    auto result = static_cast<Result>(
        m_pController->GetLinePoints(index - 1, choices)
    );
    if (result != Result::OK) {
        return result;
    }
    size_t pointIndex = Select("Select a point to modify:", choices);
    if (pointIndex == 0) {
        return Result::INVALID_VALUE;
    }
    istringstream coords(Ask("Set point to (x y z): "));
    double x;
    double y;
    double z;
    coords >> x >> y >> z;
    if (coords.bad()) {
        return Result::INVALID_VALUE;
    }
    result = static_cast<Result>(
        m_pController->ModifyLine(index - 1, pointIndex - 1, x, y, z)
    );
    if (result == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully modified line #" << index;
        Output << "." << Palette::CLEAR << endl;
    }
    return result;
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
    vector<string> choices;
    for (auto& line: m_pController->GetLines()) {
        choices.push_back(line.String);
    }
    size_t index = Select("Select a line to delete:", choices);
    if (index == 0) {
        return Result::INVALID_VALUE;
    }
    auto result = static_cast<Result>(m_pController->RemoveLine(index - 1));
    if (result == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully deleted line #" << index;
        Output << "." << Palette::CLEAR << endl;
    }
    return result;
}

}