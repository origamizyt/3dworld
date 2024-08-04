/*************************************************************************
【文件名】 ViewBase.cpp
【功能模块和目的】 为 ViewBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <memory>
#include "../Controllers/ControllerBase.hpp"
#include "ViewBase.hpp"
using namespace std;
using namespace c3w::controllers;

namespace c3w::views {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 使用控制器初始化 ViewBase 类型实例。
【参数】
    controller: 使用的控制器指针。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
ViewBase::ViewBase(shared_ptr<ControllerBase> controller)
    : m_pController(controller) {}

}