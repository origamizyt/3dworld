/*************************************************************************
【文件名】 StorageFactoryLookupException.cpp
【功能模块和目的】 为 StorageFactoryLookupException.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <stdexcept>
#include <string>
#include "StorageFactoryLookupException.hpp"
using namespace std;

namespace C3w {

namespace Errors {

/**********************************************************************
【函数名称】 构造函数
【函数功能】 以默认信息初始化异常。
【参数】 无
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
StorageFactoryLookupException::StorageFactoryLookupException(
    string Extension, 
    size_t Dimension
): invalid_argument(
    string("cannot find appropriate im/exporter for '")
    + Extension
    + string("' files at dimension ")
    + to_string(Dimension)
) {}

}

}