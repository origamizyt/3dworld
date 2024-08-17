/*************************************************************************
【文件名】 NotImplementedException.hpp
【功能模块和目的】 定义函数没有实现时抛出的异常。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef NOT_IMPLEMENTED_EXCEPTION_HPP
#define NOT_IMPLEMENTED_EXCEPTION_HPP

#include <cstddef>
#include <stdexcept>
#include <string>
using namespace std;

namespace C3w {

namespace Errors {

/*************************************************************************
【类名】 NotImplementedException
【功能】 函数没有实现时抛出的异常。
【接口说明】 无
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class NotImplementedException: public logic_error {
    public:
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 以默认信息初始化异常。
        【参数】
            Name: 函数名称。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        NotImplementedException(string Name);
};

}

}

#endif