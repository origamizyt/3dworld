/*************************************************************************
【文件名】 InvalidSizeException.hpp
【功能模块和目的】 定义初始化列表大小不符时抛出的异常。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef INVALID_SIZE_EXCEPTION_HPP
#define INVALID_SIZE_EXCEPTION_HPP

#include <cstddef>
#include <stdexcept>
using namespace std;

namespace C3w {

namespace Errors {

/**************************************************************************
【类名】 InvalidSizeException
【功能】 初始化列表大小不符时抛出的异常。
【接口说明】 无
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class InvalidSizeException: public invalid_argument {
    public:
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 以默认信息初始化异常。
        【参数】
            Given: 用户给定的大小。
            Expected: 期望的大小。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        InvalidSizeException(size_t Given, size_t Expected);
};

}

}

#endif