/*************************************************************************
【文件名】 Representable.cpp
【功能模块和目的】 为 Representable.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <ostream>
#include "Representable.hpp"

namespace C3w {

namespace Tools {
    /**********************************************************************
    【函数名称】 operator<<
    【函数功能】 将可表对象插入到输出流中。
    【参数】 
        stream: 要插入的流。
        repr: 要插入的对象。
    【返回值】 
        输出流的引用。
    【开发者及日期】 赵一彤 2024/7/24
    **********************************************************************/
    ostream& operator<<(ostream& stream, const Representable& repr) {
        stream << repr.ToString();
        return stream;
    }
}

}