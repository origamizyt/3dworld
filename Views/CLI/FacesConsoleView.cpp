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
    Controller: 控制器指针。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
FacesConsoleView::FacesConsoleView(shared_ptr<ControllerBase> Controller)
    : FacesConsoleView(Controller, cin, cout) {}

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
FacesConsoleView::FacesConsoleView(
    shared_ptr<ControllerBase> Controller,
    istream& Input,
    ostream& Output
): ConsoleViewBase(Controller, Input, Output) {
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
    AResult: 要转化的 ConsoleViewBase::Result 枚举。
【返回值】
    结果的字符串表示形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string FacesConsoleView::ResultToString(Result AResult) const {
    switch (AResult) {
        case Result::POINT_COLLISION : {
            return "Identical point already exists in face.";
        }
        case Result::ELEMENT_COLLISION : {
            return "Identical face already exists in model.";
        }
        default : {
            return ConsoleViewBase::ResultToString(AResult);
        }
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
    auto Faces = m_pController->GetFaces();
    Output << Palette::FG_BLUE << "Faces in '" << m_pController->GetName();
    Output << "' (" << Faces.size() << "):" << Palette::CLEAR << endl;
    for (size_t i = 0; i < Faces.size(); i++) {
        Output << i + 1 << ". ";
        switch (Faces[i].ElementStatus) {
            case ControllerBase::Status::CREATED : {
                Output << Palette::FG_CYAN;
                break;
            }
            case ControllerBase::Status::MODIFIED : {
                Output << Palette::FG_YELLOW;
                break;
            }
        }
        Output << Faces[i].String << Palette::CLEAR << endl;
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
    istringstream Stream(Ask("Index of desired face (1~): "));
    size_t ullIndex;
    Stream >> ullIndex;
    if (Stream.bad()) {
        return Result::INDEX_OVERFLOW;
    }
    vector<string> Points;
    Result Res = static_cast<Result>(
        m_pController->GetFacePoints(ullIndex - 1, Points)
    );
    if (Res == Result::OK) {
        Output << Palette::FG_PURPLE << "Points in face #" << ullIndex;
        Output << ":" << Palette::CLEAR << endl;
        for (size_t i = 0; i < Points.size(); i++) {
            Output << "  " << i + 1 << ". " << Points[i] << endl;
        }
    }
    return Res;
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
    istringstream Third(Ask("3rd point (x y z): "));
    double rX3;
    double rY3;
    double rZ3;
    Third >> rX3 >> rY3 >> rZ3;
    if (Third.bad()) {
        return Result::INVALID_VALUE;
    }
    Result Res = static_cast<Result>(
        m_pController->AddFace(rX1, rY1, rZ1, rX2, rY2, rZ2, rX3, rY3, rZ3)
    );
    if (Res == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully added face.";
        Output << Palette::CLEAR << endl;
    }
    return Res;
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
    vector<string> Choices;
    for (auto& Face: m_pController->GetFaces()) {
        Choices.push_back(Face.String);
    }
    size_t ullIndex = Select("Select a face to modify:", Choices);
    if (ullIndex == 0) {
        return Result::INVALID_VALUE;
    }
    Choices.clear();
    Result Res = static_cast<Result>(
        m_pController->GetFacePoints(ullIndex - 1, Choices)
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
        m_pController->ModifyFace(ullIndex - 1, ullPointIndex - 1, rX, rY, rZ)
    );
    if (Res == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully modified face #";
        Output << ullIndex << "." << Palette::CLEAR << endl;
    }
    return Res;
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
    vector<string> Choices;
    for (auto& Face: m_pController->GetFaces()) {
        Choices.push_back(Face.String);
    }
    size_t ullIndex = Select("Select a face to delete:", Choices);
    if (ullIndex == 0) {
        return Result::INVALID_VALUE;
    }
    Result Res = static_cast<Result>(m_pController->RemoveFace(ullIndex - 1));
    if (Res == Result::OK) {
        Output << Palette::FG_GREEN << "Successfully deleted face #";
        Output << ullIndex << "." << Palette::CLEAR << endl;
    }
    return Res;
}

}

}

}