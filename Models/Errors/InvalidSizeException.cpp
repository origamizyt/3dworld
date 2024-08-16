/*************************************************************************
【文件名】 InvalidSizeException.cpp
【功能模块和目的】 为 InvalidSizeException.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <stdexcept>
#include <string>
#include "InvalidSizeException.hpp"
using namespace std;

namespace C3w {

namespace Errors {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 以默认信息初始化异常。
【参数】
    Given: 用户给定的大小。
    Expected: 期望的大小。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
InvalidSizeException::InvalidSizeException(size_t Given, size_t Expected)
    : invalid_argument(
        string("expected ") 
        + to_string(Expected)
        + string(", got ")
        + to_string(Given)
    ) {}

}

}