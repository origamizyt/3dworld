/*************************************************************************
【文件名】 ExporterBase.tpp
【功能模块和目的】 为 ExporterBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <fstream>
#include <string>
#include "../Core/Model.hpp"
#include "ExporterBase.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Errors;

namespace C3w::Storage {

/**********************************************************************
【函数名称】 Export
【函数功能】 导出指定模型到文件中。
【参数】 
    path: 文件所在路径。
    model: 模型的可变引用。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
void ExporterBase<N>::Export(string path, const Model<N>& model) const {
    ofstream stream(path, ios::trunc);
    if (!stream.is_open()) {
        throw FileOpenException();
    }
    try {
        InnerExport(stream, model);
    }
    catch (...) {
        stream.close();
        throw;
    }
}

}