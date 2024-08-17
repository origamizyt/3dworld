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
        if (line.empty()) {
            continue;
        }
        else if (line == "?") {
            ShowHelp();
        }
        else if (line == "quit") {
            break;
        }
        else {
            bool found = false;
            for (auto& Pair: m_Commands) {
                if (Pair.first == line) {
                    auto result = Pair.second.Handler();
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
                for (auto& Pair: m_Commands) {
                    if (Likelihood(line, Pair.first) >= 0.75f) {
                        Output << Palette::FG_GRAY;
                        Output << "Perhaps you mean '" << Pair.first;
                        Output << "'?" << Palette::CLEAR << endl;
                        break;
                    }
                }
            }
        }
    }
}

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用控制器与标准输入/输出流初始化 ConsoleViewBase 类型实例。
【参数】
    Controller: 控制器指针。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::ConsoleViewBase(shared_ptr<ControllerBase> Controller)
    : ConsoleViewBase(Controller, cin, cout) {}

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
ConsoleViewBase::ConsoleViewBase(
    shared_ptr<ControllerBase> Controller, 
    istream& Input, 
    ostream& Output
): ViewBase(Controller), Input(Input), Output(Output) {}

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
string ConsoleViewBase::Ask(string Prompt, bool Trim) const {
    Output << Palette::FG_BLUE << Prompt << Palette::CLEAR;
    string Answer;
    getline(Input, Answer);
    if (Trim) {
        size_t Start = Answer.find_first_not_of(" \t\n\r");
        size_t End = Answer.find_last_not_of(" \t\n\r");
        if (Start == std::string::npos || End == std::string::npos) {
            return "";
        }
        return Answer.substr(Start, End - Start + 1);
    }
    return Answer;
}

/**********************************************************************
【函数名称】 Select
【函数功能】 让用户在选项中做出选择。
【参数】
    Prompt: 询问的提示。
    Choices: 选项组成的向量。
【返回值】
    用户选择的项，从 1 开始。如果输入不是数字返回 0。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
size_t ConsoleViewBase::Select(
    string Prompt, 
    const vector<string>& Choices
) const {
    Output << Palette::FG_BLUE << Prompt << Palette::CLEAR << endl;
    for (size_t i = 0; i < Choices.size(); i++) {
        Output << i + 1 << ". " << Choices[i] << endl;
    }
    Output << Palette::FG_BLUE;
    if (Choices.size() == 1) {
        Output << "[1]: ";
    }
    else {
        Output << "[1~" << Choices.size() << "]: ";
    }
    Output << Palette::CLEAR;
    istringstream Stream(Ask(""));
    size_t Id;
    Stream >> Id;
    return Stream.bad() ? 0 : Id;
}

/**********************************************************************
【函数名称】 ResultToString
【函数功能】 将控制器返回的结果转化为字符串。
【参数】
    AResult: 要转化的 ControllerBase::Result 枚举。
【返回值】
    结果的字符串表示形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string ConsoleViewBase::ResultToString(Result AResult) const {
    switch (AResult) {
        case Result::STORAGE_LOOKUP_ERROR : {
            return "Cannot find appropriate im/exporter.";
        }
        case Result::FILE_OPEN_ERROR : {
            return "Cannot open given file.";
        }
        case Result::FILE_FORMAT_ERROR : {
            return "Given file contains invalid contents.";
        }
        case Result::INDEX_OVERFLOW : {
            return "The index given is not valid.";
        }
        case Result::POINT_INDEX_OVERFLOW : {
            return "The point index given is not valid.";
        }
        case Result::POINT_COLLISION : {
            return "Identical point already exists in element.";
        }
        case Result::ELEMENT_COLLISION : {
            return "Identical element already exists in model.";
        }
        case Result::INVALID_VALUE : {
            return "Entered value is invalid.";
        }
        default : {
            return "";
        }
    }
}

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
void ConsoleViewBase::RegisterCommand(
    string Name, 
    function<Result()> Handler,
    string Help
) {
    m_Commands[Name] = { Handler, Help };
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
    size_t MaxNameLength = 0;
    for (auto& Pair: m_Commands) {
        if (Pair.first.size() > MaxNameLength) {
            MaxNameLength = Pair.first.size();
        }
    }
    size_t Tabs = ceil((MaxNameLength + 1) / 8.0);
    for (auto& Pair: m_Commands) {
        Output << Palette::FG_PURPLE << Pair.first << Palette::CLEAR;
        size_t TabsNeeded = ceil((Tabs * 8 - Pair.first.size()) / 8.0);
        for (size_t i = 0; i < TabsNeeded; i++) {
            Output << "\t";
        }
        Output << "- " << Pair.second.Help << endl;
    }
}

/**********************************************************************
【函数名称】 Likelihood
【函数功能】 计算两个字符串的相似程度。
【参数】 
    Given: 用户提供的字符串。
    Has: 原有的字符串。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
float ConsoleViewBase::Likelihood(string Given, string Has) {
    auto Denominator = max(Given.size(), Has.size());
    auto ValidLength = min(Given.size(), Has.size());
    int Numerator = 0;
    for (size_t i = 0; i < ValidLength; i++) {
        if (Given[i] == Has[i]) {
            Numerator++;
        }
    }
    return static_cast<float>(Numerator) / Denominator;
}

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
ostream& operator<<(
    ostream& Stream, 
    ConsoleViewBase::Palette APalette
) {
    Stream << "\033[" << static_cast<int>(APalette) << "m";
    return Stream;
}

}

}

}