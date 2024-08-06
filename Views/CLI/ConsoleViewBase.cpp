/*************************************************************************
【文件名】 ConsoleViewBase.cpp
【功能模块和目的】 为 ConsoleViewBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include "../ViewBase.hpp"
#include "../../Controllers/ControllerBase.hpp"
#include "ConsoleViewBase.hpp"
using namespace std;
using namespace C3w::Controllers;

namespace C3w {

namespace Views {

namespace Cli {

/**********************************************************************
【函数名称】 Display
【函数功能】 向用户展示此视图。
【参数】 无
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
void ConsoleViewBase::Display() const {
    Output << Palette::FG_GRAY << "Type ? for help." << Palette::CLEAR << endl;
    while (true) {
        string line = Ask(m_Prompt, true);
        if (line == "?") {
            ShowHelp();
        }
        else if (line == "quit") {
            break;
        }
        else {
            bool found = false;
            for (auto& pair: m_Commands) {
                if (pair.first == line) {
                    auto result = pair.second.Handler();
                    if (result != Result::OK) {
                        Output << Palette::FG_RED;
                        Output << "error: " << ResultToString(result); 
                        Output << Palette::CLEAR << endl;
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                Output << Palette::FG_RED;
                Output << "error: Unrecognized command '" << line << "'."; 
                Output << Palette::CLEAR << endl;
            }
        }
    }
}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用控制器与标准输入/输出流初始化 ConsoleViewBase 类型实例。
【参数】
    controller: 控制器指针。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::ConsoleViewBase(shared_ptr<ControllerBase> controller)
    : ConsoleViewBase(controller, cin, cout) {}

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
ConsoleViewBase::ConsoleViewBase(
    shared_ptr<ControllerBase> controller, 
    istream& input, 
    ostream& output
): ViewBase(controller), Input(input), Output(output) {}

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
string ConsoleViewBase::Ask(string prompt, bool trim) const {
    Output << Palette::FG_BLUE << prompt << Palette::CLEAR;
    string answer;
    getline(Input, answer);
    if (trim) {
        size_t start = answer.find_first_not_of(" \t\n\r");
        size_t end = answer.find_last_not_of(" \t\n\r");
        if (start == std::string::npos || end == std::string::npos) {
            return "";
        }
        return answer.substr(start, end - start + 1);
    }
    return answer;
}

/**********************************************************************
【函数名称】 Choose
【函数功能】 让用户在选项中做出选择。
【参数】
    prompt: 询问的提示。
    choices: 选项组成的向量。
【返回值】
    用户选择的项，从 1 开始。如果输入不是数字返回 0。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
size_t ConsoleViewBase::Select(
    string prompt, 
    const vector<string>& choices
) const {
    Output << Palette::FG_BLUE << prompt << Palette::CLEAR << endl;
    for (size_t i = 0; i < choices.size(); i++) {
        Output << i + 1 << ". " << choices[i] << endl;
    }
    Output << Palette::FG_BLUE;
    if (choices.size() == 1) {
        Output << "[1]: ";
    }
    else {
        Output << "[1~" << choices.size() << "]: ";
    }
    Output << Palette::CLEAR;
    istringstream stream(Ask(""));
    size_t id;
    stream >> id;
    return stream.bad() ? 0 : id;
}

/**********************************************************************
【函数名称】 ResultToString
【函数功能】 将控制器返回的结果转化为字符串。
【参数】
    result: 要转化的 ControllerBase::Result 枚举。
【返回值】
    结果的字符串表示形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string ConsoleViewBase::ResultToString(Result result) const {
    switch (result) {
        case Result::STORAGE_LOOKUP_ERROR: {
            return "Cannot find appropriate im/exporter.";
        }
        case Result::FILE_OPEN_ERROR: {
            return "Cannot open given file.";
        }
        case Result::FILE_FORMAT_ERROR: {
            return "Given file contains invalid contents.";
        }
        case Result::INDEX_OVERFLOW: {
            return "The index given is not valid.";
        }
        case Result::POINT_INDEX_OVERFLOW: {
            return "The point index given is not valid.";
        }
        case Result::POINT_COLLISION: {
            return "Identical point already exists in element.";
        }
        case Result::ELEMENT_COLLISION: {
            return "Identical element already exists in model.";
        }
        case Result::INVALID_VALUE: {
            return "Entered value is invalid.";
        }
        default: {
            return "";
        }
    }
}

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
void ConsoleViewBase::RegisterCommand(
    string name, 
    function<Result()> handler,
    string help
) {
    m_Commands[name] = { handler, help };
}

/**********************************************************************
【函数名称】 ShowHelp
【函数功能】 显示帮助信息。
【参数】 无
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
void ConsoleViewBase::ShowHelp() const {
    Output << Palette::FG_PURPLE;
    Output << "Available commands:";
    Output << Palette::CLEAR << endl;
    Output << Palette::FG_PURPLE;
    Output << "?" << Palette::CLEAR << "\t- Show this message." << endl;
    Output << Palette::FG_PURPLE;
    Output << "quit" << Palette::CLEAR << "\t- Exit this view." << endl;
    size_t maxNameLength = 0;
    for (auto& pair: m_Commands) {
        if (pair.first.size() > maxNameLength) {
            maxNameLength = pair.first.size();
        }
    }
    size_t tabs = ceil((maxNameLength + 1) / 8.0);
    for (auto& pair: m_Commands) {
        Output << Palette::FG_PURPLE << pair.first << Palette::CLEAR;
        size_t tabsNeeded = ceil((tabs * 8 - pair.first.size()) / 8.0);
        for (size_t i = 0; i < tabsNeeded; i++) {
            Output << "\t";
        }
        Output << "- " << pair.second.Help << endl;
    }
}

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
ostream& operator<<(
    ostream& stream, 
    ConsoleViewBase::Palette palette
) {
    stream << "\033[" << static_cast<int>(palette) << "m";
    return stream;
}

}

}

}