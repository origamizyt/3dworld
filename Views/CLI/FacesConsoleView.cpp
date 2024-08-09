/*************************************************************************
【文件名】 FacesConsoleView.cpp
【功能模块和目的】 为 FacesConsoleView.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "ConsoleViewBase.hpp"
#include "../../Controllers/ControllerBase.hpp"
#include "FacesConsoleView.hpp"
using namespace std;
using namespace C3w::Controllers;

namespace C3w {

namespace Views {

namespace Cli {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用控制器与标准输入/输出流初始化 FacesConsoleView 类型实例。
【参数】
    controller: 控制器指针。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
FacesConsoleView::FacesConsoleView(shared_ptr<ControllerBase> controller)
    : FacesConsoleView(controller, cin, cout) {}

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
FacesConsoleView::FacesConsoleView(
    shared_ptr<ControllerBase> controller,
    istream& input,
    ostream& output
): ConsoleViewBase(controller, input, output) {
    m_Prompt = "faces#> ";
    RegisterCommand(
        "list",
        bind(&FacesConsoleView::CommandListFaces, this),
        "Lists all faces in model."
    );
    RegisterCommand(
        "get",
        bind(&FacesConsoleView::CommandGetFace, this),
        "Describes given face."
    );
    RegisterCommand(
        "add",
        bind(&FacesConsoleView::CommandAddFace, this),
        "Adds a face to model."
    );
    RegisterCommand(
        "edit",
        bind(&FacesConsoleView::CommandModifyFace, this),
        "Modifies a face in model."
    );
    RegisterCommand(
        "del",
        bind(&FacesConsoleView::CommandRemoveFace, this),
        "Removes a face from model."
    );
}

/**********************************************************************
【函数名称】 ResultToString
【函数功能】 将命令返回的结果转化为字符串。
【参数】
    result: 要转化的 ConsoleViewBase::Result 枚举。
【返回值】
    结果的字符串表示形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string FacesConsoleView::ResultToString(Result result) const {
    if (result == Result::ELEMENT_COLLISION) {
        return "Identical face already exists in model.";
    }
    else {
        return ConsoleViewBase::ResultToString(result);
    }
}

/**********************************************************************
【函数名称】 CommandListFaces
【函数功能】 实现 list 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result FacesConsoleView::CommandListFaces() const {
    auto faces = m_pController->GetFaces();
    Output << Palette::FG_BLUE << "Faces in '" << m_pController->GetName();
    Output << "' (" << faces.size() << "):" << Palette::CLEAR << endl;
    for (size_t i = 0; i < faces.size(); i++) {
        Output << i + 1 << ". ";
        switch (faces[i].ElementStatus) {
            case ControllerBase::Status::CREATED: {
                Output << Palette::FG_CYAN;
                break;
            }
            case ControllerBase::Status::MODIFIED: {
                Output << Palette::FG_YELLOW;
                break;
            }
        }
        Output << faces[i].String << Palette::CLEAR << endl;
    }
    return Result::OK;
}

/**********************************************************************
【函数名称】 CommandGetFace
【函数功能】 实现 get 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result FacesConsoleView::CommandGetFace() const {
    istringstream stream(Ask("Index of desired face (1~): "));
    size_t index;
    stream >> index;
    if (stream.bad()) {
        return Result::INDEX_OVERFLOW;
    }
    vector<string> points;
    auto result = static_cast<Result>(
        m_pController->GetFacePoints(index - 1, points)
    );
    if (result == Result::OK) {
        Output << Palette::FG_PURPLE << "Points in face #" << index;
        Output << ":" << Palette::CLEAR << endl;
        for (size_t i = 0; i < points.size(); i++) {
            Output << "  " << i + 1 << ". " << points[i] << endl;
        }
    }
    return result;
}

/**********************************************************************
【函数名称】 CommandAddFace
【函数功能】 实现 add 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result FacesConsoleView::CommandAddFace() const {
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
    istringstream third(Ask("3rd point (x y z): "));
    double x3;
    double y3;
    double z3;
    third >> x3 >> y3 >> z3;
    if (third.bad()) {
        return Result::INVALID_VALUE;
    }
    auto result = static_cast<Result>(
        m_pController->AddFace(x1, y1, z1, x2, y2, z2, x3, y3, z3)
    );
    if (result == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully added face.";
        Output << Palette::CLEAR << endl;
    }
    return result;
}

/**********************************************************************
【函数名称】 CommandModifyFace
【函数功能】 实现 edit 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result FacesConsoleView::CommandModifyFace() const {
    vector<string> choices;
    for (auto& face: m_pController->GetFaces()) {
        choices.push_back(face.String);
    }
    size_t index = Select("Select a face to modify:", choices);
    if (index == 0) {
        return Result::INVALID_VALUE;
    }
    choices.clear();
    auto result = static_cast<Result>(
        m_pController->GetFacePoints(index - 1, choices)
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
        m_pController->ModifyFace(index - 1, pointIndex - 1, x, y, z)
    );
    if (result == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully modified face #" << index;
        Output << "." << Palette::CLEAR << endl;
    }
    return result;
}

/**********************************************************************
【函数名称】 CommandRemoveFace
【函数功能】 实现 del 命令。
【参数】 无
【返回值】
    命令发生的错误。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ConsoleViewBase::Result FacesConsoleView::CommandRemoveFace() const {
    vector<string> choices;
    for (auto& face: m_pController->GetFaces()) {
        choices.push_back(face.String);
    }
    size_t index = Select("Select a face to delete:", choices);
    if (index == 0) {
        return Result::INVALID_VALUE;
    }
    auto result = static_cast<Result>(m_pController->RemoveFace(index - 1));
    if (result == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully deleted face #" << index;
        Output << "." << Palette::CLEAR << endl;
    }
    return result;
}

}

}

}