/*************************************************************************
【文件名】 NotImplementedException.hpp
【功能模块和目的】 为 NotImplementedException.cpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <stdexcept>
#include <string>
#include "NotImplementedException.hpp"
using namespace std;

namespace C3w {

namespace Errors {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 以默认信息初始化异常。
【参数】
    Name: 函数名称。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
NotImplementedException::NotImplementedException(string Name)
    : logic_error(
        string("method '")
        + Name
        + string("' is not implemented")
    ) {}

}

}