/*************************************************************************
【文件名】 ExporterBase.tpp
【功能模块和目的】 为 ExporterBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <fstream>
#include <string>
#include "../Core/Model.hpp"
#include "../Errors/FileOpenException.hpp"
#include "ExporterBase.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Errors;

namespace C3w {

namespace Storage {

/**********************************************************************
【函数名称】 Export
【函数功能】 导出指定模型到文件中。
【参数】 
    Path: 文件所在路径。
    Model: 模型的可变引用。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
void ExporterBase<N>::Export(string Path, const Model<N>& Model) const {
    ofstream Stream(Path, ios::trunc);
    if (!Stream.is_open()) {
        throw FileOpenException(Path);
    }
    try {
        InnerExport(Stream, Model);
    }
    catch (...) {
        Stream.close();
        throw;
    }
}

}

}