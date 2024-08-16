/*************************************************************************
【文件名】 StorageFactoryLookupException.hpp
【功能模块和目的】 定义无法找到特定的导入/导出器时抛出的异常。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef STORAGE_FACTORY_LOOKUP_EXCEPTION_HPP
#define STORAGE_FACTORY_LOOKUP_EXCEPTION_HPP

#include <cstddef>
#include <stdexcept>
#include <string>
using namespace std;

namespace C3w {

namespace Errors {

/**************************************************************************
【类名】 StorageFactoryLookupException
【功能】 无法找到特定的导入/导出器时抛出的异常。
【接口说明】 无
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class StorageFactoryLookupException: public invalid_argument {
    public:
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 以默认信息初始化异常。
        【参数】 无
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        StorageFactoryLookupException(string Extension, size_t Dimension);
};

}

}

#endif