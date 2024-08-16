/*************************************************************************
【文件名】 ConsoleController.cpp
【功能模块和目的】 为 ConsoleController.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <memory>
#include <string>
#include <sstream>
#include "../ControllerBase.hpp"
#include "../../Models/Core/Line.hpp"
#include "../../Models/Core/Face.hpp"
#include "ConsoleController.hpp"
using namespace std;

namespace C3w {

namespace Controllers {

namespace Cli {

// 初始化空指针。
shared_ptr<ConsoleController> ConsoleController::m_pInstance { nullptr };

/**********************************************************************
【函数名称】 GetInstance
【函数功能】 获取 ConsoleController 的唯一实例。
【参数】 无
【返回值】
    ConsoleController 的唯一实例。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
shared_ptr<ConsoleController> ConsoleController::GetInstance() {
    if (!m_pInstance) {
        m_pInstance.reset(new ConsoleController());
    }
    return m_pInstance;
}

/**********************************************************************
【函数名称】 PointToString
【函数功能】 获取点的字符串表达形式。
【参数】
    APoint: 要转化的点。
【返回值】
    点的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string ConsoleController::PointToString(const Point<3>& APoint) const {
    return APoint.ToString();
}

/**********************************************************************
【函数名称】 LineToString
【函数功能】 获取线段及其状态的字符串表达形式。
【参数】
    ALine: 要转化的线段。
    AStatus: 线段的状态。
【返回值】
    线段的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string ConsoleController::LineToString(
    const Line<3>& ALine, 
    Status AStatus
) const {
    ostringstream Stream;
    Stream << ALine.ToString() << ", length=" << ALine.GetLength();
    switch (AStatus) {
        case Status::CREATED: {
            Stream << " *created";
            break;
        }
        case Status::MODIFIED: {
            Stream << " *modified";
            break;
        }
    }
    return Stream.str();
}

/**********************************************************************
【函数名称】 FaceToString
【函数功能】 获取面的字符串表达形式。
【参数】
    AFace: 要转化的面。
    AStatus: 面的状态。
【返回值】
    面的字符串表达形式。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
string ConsoleController::FaceToString(
    const Face<3>& AFace, 
    Status AStatus
) const {
    ostringstream Stream;
    Stream << AFace.ToString() << ", area=" << AFace.GetArea();
    switch (AStatus) {
        case Status::CREATED: {
            Stream << " *created";
            break;
        }
        case Status::MODIFIED: {
            Stream << " *modified";
            break;
        }
    }
    return Stream.str();
}

}

}

}