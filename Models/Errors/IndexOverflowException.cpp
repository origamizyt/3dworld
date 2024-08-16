/*************************************************************************
【文件名】 IndexOverflowException.cpp
【功能模块和目的】 为 IndexOverflowException.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <stdexcept>
#include <string>
#include "IndexOverflowException.hpp"
using namespace std;

namespace C3w {

namespace Errors {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 以默认信息初始化异常。
【参数】
    Index: 用户给出的下标。
    Size: 容器实际的大小。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
IndexOverflowException::IndexOverflowException(size_t Index, size_t Size)
    : out_of_range(
        string("expected [0, ")
        + to_string(Size)
        + string("), got ")
        + to_string(Index)
    ) {}

}

}