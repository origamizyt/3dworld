/*************************************************************************
【文件名】 StorageFactory.tpp
【功能模块和目的】 为 StorageFactory.hpp 提供模板实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include "ImporterBase.hpp"
#include "ExporterBase.hpp"
#include "../Core/Errors.hpp"
#include "StorageFactory.hpp"
using namespace std;
using namespace C3w::Errors;

namespace C3w {

namespace Storage {

/**********************************************************************
【函数名称】 Register
【函数功能】 将 Importer 和 Exporter 注册为一对导入/导出器。
【参数】
    extension: 要注册的扩展名。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, typename Importer, typename Exporter>
typename enable_if<
    std::is_base_of<ImporterBase<N>, Importer>::value &&
    std::is_base_of<ExporterBase<N>, Exporter>::value
>::type StorageFactory::Register(string extension) {
    Register<N, Importer, Exporter>(
        extension,
        []() { return new Importer(); },
        []() { return new Exporter(); }
    );
}

/**********************************************************************
【函数名称】 Register
【函数功能】 注册一对自定义的导入/导出器。
【参数】
    extension: 要注册的扩展名。
    importerFactory: 一个构造导入器的函数。
    exporterFactory: 一个构造导出器的函数。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, typename Importer, typename Exporter>
typename enable_if<
    std::is_base_of<ImporterBase<N>, Importer>::value &&
    std::is_base_of<ExporterBase<N>, Exporter>::value
>::type StorageFactory::Register(
    string extension,
    function<Importer*()> importerFactory,
    function<Exporter*()> exporterFactory
) {
    m_Pairs.push_back(Pair {
        extension, N,
        importerFactory,
        exporterFactory
    });
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

}