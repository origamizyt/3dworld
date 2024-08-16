/*************************************************************************
【文件名】 FileFormatException.hpp
【功能模块和目的】 定义文件内容无效时抛出的异常。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef FILE_FORMAT_EXCEPTION_H
#define FILE_FORMAT_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

namespace C3w {

namespace Errors {

/**************************************************************************
【类名】 FileFormatException
【功能】 文件内容无效时抛出的异常。
【接口说明】 无
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class FileFormatException: public runtime_error {
    public:
        /**********************************************************************
        【函数名称】 构造函数
        【函数功能】 以默认信息初始化异常。
        【参数】
            Line: 行号。
            Details: 错误详细信息。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        FileFormatException(unsigned int Line, string Details);
};

}

}

#endif