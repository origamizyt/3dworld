/*************************************************************************
【文件名】 ImporterBase.tpp
【功能模块和目的】 为 ImporterBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <fstream>
#include <string>
#include "../Errors/FileOpenException.hpp"
#include "../Core/Model.hpp"
#include "ImporterBase.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Errors;

namespace C3w {

namespace Storage {

/**********************************************************************
【函数名称】 Import
【函数功能】 导入指定文件到模型中。
【参数】 
    Path: 文件所在路径。
    Model: 模型的可变引用。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
void ImporterBase<N>::Import(string Path, Model<N>& Model) const {
    ifstream Stream(Path, ios::in);
    if (!Stream.is_open()) {
        throw FileOpenException(Path);
    }
    try {
        InnerImport(Stream, Model);
    }
    catch (...) {
        Stream.close();
        throw;
    }
}

}

}