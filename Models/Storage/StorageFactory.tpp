/*************************************************************************
【文件名】 StorageFactory.tpp
【功能模块和目的】 为 StorageFactory.hpp 提供模板实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include "ImporterBase.hpp"
#include "ExporterBase.hpp"
#include "../Core/Errors.hpp"
#include "StorageFactory.hpp"
using namespace std;
using namespace c3w::errors;

namespace c3w::storage {

/**********************************************************************
【函数名称】 Register
【函数功能】 将 Importer 和 Exporter 注册为一对导入/导出器。
【参数】
    extension: 要注册的扩展名。
    dimension: 要注册的维度。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename Importer, typename Exporter>
void StorageFactory::Register(string extension, size_t dimension) {
    Register(
        extension,
        dimension,
        []() { return new Importer(); },
        []() { return new Exporter(); }
    );
}

/**********************************************************************
【函数名称】 GetImporter
【函数功能】 根据维数与文件路径获取导入器。
【参数】
    path: 文件路径。
【返回值】
    指向导入器的指针。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
unique_ptr<ImporterBase<N>> StorageFactory::GetImporter(string path) {
    string extension = "";
    size_t dotpos = path.find_last_of('.');
    if (dotpos != string::npos) {
        extension = path.substr(dotpos);
    }
    for (auto& pair: m_Pairs) {
        if (extension == pair.Extension && N == pair.Dimension) {
            return unique_ptr<ImporterBase<N>>(
                static_cast<ImporterBase<N>*>(pair.ImporterFactory())
            );
        }
    }
    throw StorageFactoryLookupException();
}

/**********************************************************************
【函数名称】 GetExporter
【函数功能】 根据维数与文件路径获取导出器。
【参数】
    path: 文件路径。
【返回值】
    指向导出器的指针。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
unique_ptr<ExporterBase<N>> StorageFactory::GetExporter(string path) {
    string extension = "";
    size_t dotpos = path.find_last_of('.');
    if (dotpos != string::npos) {
        extension = path.substr(dotpos);
    }
    for (auto& pair: m_Pairs) {
        if (extension == pair.Extension && N == pair.Dimension) {
            return unique_ptr<ExporterBase<N>>(
                static_cast<ExporterBase<N>*>(pair.ExporterFactory())
            );
        }
    }
    throw StorageFactoryLookupException();
}

}