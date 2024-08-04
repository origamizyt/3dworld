/*************************************************************************
【文件名】 ImporterBase.tpp
【功能模块和目的】 为 ImporterBase.hpp 提供实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <fstream>
#include <string>
#include "../Core/Errors.hpp"
#include "../Core/Model.hpp"
#include "ImporterBase.hpp"
using namespace std;
using namespace c3w;
using namespace c3w::storage;
using namespace c3w::errors;

/**********************************************************************
【函数名称】 Import
【函数功能】 导入指定文件到模型中。
【参数】 
    path: 文件所在路径。
    model: 模型的可变引用。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
void ImporterBase<N>::Import(string path, Model<N>& model) const {
    ifstream stream(path, ios::in);
    if (!stream.is_open()) {
        throw FileOpenException();
    }
    try {
        InnerImport(stream, model);
    }
    catch (...) {
        stream.close();
        throw;
    }
}