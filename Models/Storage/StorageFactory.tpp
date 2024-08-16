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
#include "StorageFactory.hpp"
#include "../Errors/StorageFactoryLookupException.hpp"
using namespace std;
using namespace C3w::Errors;

namespace C3w {

namespace Storage {

/**********************************************************************
【函数名称】 Register
【函数功能】 将 Importer 和 Exporter 注册为一对导入/导出器。
【参数】
    Extension: 要注册的扩展名。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, typename Importer, typename Exporter>
typename enable_if<
    is_base_of<ImporterBase<N>, Importer>::value &&
    is_base_of<ExporterBase<N>, Exporter>::value
>::type StorageFactory::Register(string Extension) {
    Register<N, Importer, Exporter>(
        Extension,
        MakeConstructor<Importer>(),
        MakeConstructor<Exporter>()
    );
}

/**********************************************************************
【函数名称】 Register
【函数功能】 注册一对自定义的导入/导出器。
【参数】
    Extension: 要注册的扩展名。
    ImporterFactory: 一个构造导入器的函数。
    ExporterFactory: 一个构造导出器的函数。
【返回值】 无
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N, typename Importer, typename Exporter>
typename enable_if<
    is_base_of<ImporterBase<N>, Importer>::value &&
    is_base_of<ExporterBase<N>, Exporter>::value
>::type StorageFactory::Register(
    string Extension,
    function<Importer*()> ImporterFactory,
    function<Exporter*()> ExporterFactory
) {
    m_Map.insert({ Extension, { N, ImporterFactory, ExporterFactory }});
}

/**********************************************************************
【函数名称】 GetImporter
【函数功能】 根据维数与文件扩展名获取导入器。
【参数】
    Extension: 文件扩展名。
【返回值】
    指向导入器的指针。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
unique_ptr<ImporterBase<N>> StorageFactory::GetImporter(string Extension) {
    auto Range = m_Map.equal_range(Extension);
    for (auto it = Range.first; it != Range.second; ++it) {
        if (it->second.Dimension == N) {
            return unique_ptr<ImporterBase<N>>(
                static_cast<ImporterBase<N>*>(it->second.ImporterFactory())
            );
        }
    }
    throw StorageFactoryLookupException(Extension, N);
}

/**********************************************************************
【函数名称】 GetExporter
【函数功能】 根据维数与文件扩展名获取导出器。
【参数】
    Extension: 文件扩展名。
【返回值】
    指向导出器的指针。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <size_t N>
unique_ptr<ExporterBase<N>> StorageFactory::GetExporter(string Extension) {
    auto Range = m_Map.equal_range(Extension);
    for (auto it = Range.first; it != Range.second; ++it) {
        if (it->second.Dimension == N) {
            return unique_ptr<ExporterBase<N>>(
                static_cast<ExporterBase<N>*>(it->second.ExporterFactory())
            );
        }
    }
    throw StorageFactoryLookupException(Extension, N);
}

/**********************************************************************
【函数名称】 MakeConstructor
【函数功能】 创建特定类型的一个“构造函数”。
【参数】 
    Args: 构造函数需要的参数。
【返回值】 一个返回特定类型指针的函数。
【开发者及日期】 赵一彤 2024/7/24
**********************************************************************/
template <typename T, typename ...A>
constexpr function<T*()> StorageFactory::MakeConstructor(A&& ...Args) {
    return [=]() { return new T(forward<A>(Args)...); };
}

}

}