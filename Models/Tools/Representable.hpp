/*************************************************************************
【文件名】 Representable.hpp
【功能模块和目的】 Representable 抽象类表示一个可以用字符串表示的对象。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef REPRESENTABLE_HPP
#define REPRESENTABLE_HPP

#include <ostream>
#include <string>
using namespace std;

namespace C3w {

namespace Tools {

/*************************************************************************
【类名】 Representable
【功能】 表示一个可以用字符串表示的对象。
【接口说明】 转化为字符串，流插入。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class Representable {
    public:
        /**********************************************************************
        【函数名称】 ToString
        【函数功能】 返回此对象的字符串表达形式。
        【参数】 无
        【返回值】 
            此对象的字符串表达形式。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual string ToString() const = 0;
        /**********************************************************************
        【函数名称】 operator<<
        【函数功能】 将可表对象插入到输出流中。
        【参数】 
            Stream: 要插入的流。
            Repr: 要插入的对象。
        【返回值】 
            输出流的引用。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        friend ostream& operator<<(ostream& Stream, const Representable& Repr);
};

}

}

#endif