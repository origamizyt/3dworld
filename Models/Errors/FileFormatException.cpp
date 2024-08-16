/*************************************************************************
【文件名】 FileFormatException.cpp
【功能模块和目的】 为 FileFormatException.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <stdexcept>
#include <string>
#include "FileFormatException.hpp"
using namespace std;

namespace C3w {

namespace Errors {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 以默认信息初始化异常。
【参数】
    Line: 行号。
    Details: 错误详细信息。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
FileFormatException::FileFormatException(unsigned int Line, string Details)
    : runtime_error(
        string("At line ")
        + to_string(Line)
        + string(": ")
        + Details
    ) {}

}

}