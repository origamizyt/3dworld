/*************************************************************************
【文件名】 IndexOverflowException.hpp
【功能模块和目的】 定义下标越界访问时抛出的异常。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef INDEX_OVERFLOW_EXCEPTION_HPP
#define INDEX_OVERFLOW_EXCEPTION_HPP

#include <cstddef>
#include <stdexcept>
using namespace std;

namespace C3w {

namespace Errors {

/*************************************************************************
【类名】 IndexOverflowException
【功能】 下标越界时抛出的异常。
【接口说明】 无
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class IndexOverflowException: public out_of_range {
    public:
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 以默认信息初始化异常。
        【参数】
            Index: 用户给出的下标。
            Size: 容器实际的大小。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        IndexOverflowException(size_t Index, size_t Size);
};

}

}

#endif