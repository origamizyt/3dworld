/*************************************************************************
【文件名】 CollectionException.cpp
【功能模块和目的】 为 CollectionException.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <stdexcept>
#include <string>
#include "CollectionException.hpp"
using namespace std;

namespace C3w {

namespace Errors {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 以默认信息初始化异常。
【参数】
    Type: 执行操作的类型。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
CollectionException::CollectionException(const char* Type)
    : logic_error(
        string("failed to perform operation '")
        + string(Type)
        + string("' on collection")
    ) {}

}

}