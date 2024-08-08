/*************************************************************************
【文件名】 StorageFactory.hpp
【功能模块和目的】 StorageFactory 用于静态获取导入/导出器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#pragma once

#include <cstddef>
#include <string>
#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include "ImporterBase.hpp"
#include "ExporterBase.hpp"
using namespace std;

namespace C3w {

namespace Storage {

/*************************************************************************
【类名】 StorageFactory
【功能】 静态类，用于获取导入/导出器。
【接口说明】 注册/获取导入/导出器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class StorageFactory final {
    public:
        // 操作

        /**********************************************************************
        【函数名称】 Register
        【函数功能】 将 Importer 和 Exporter 注册为一对导入/导出器。
        【参数】
            extension: 要注册的扩展名。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        template <size_t N, typename Importer, typename Exporter>
        static typename enable_if<
            is_base_of<ImporterBase<N>, Importer>::value &&
            is_base_of<ExporterBase<N>, Exporter>::value
        >::type Register(string extension);
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
        static typename enable_if<
            is_base_of<ImporterBase<N>, Importer>::value &&
            is_base_of<ExporterBase<N>, Exporter>::value
        >::type Register(
            string extension,
            function<Importer*()> importerFactory,
            function<Exporter*()> exporterFactory
        );
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
        static unique_ptr<ImporterBase<N>> GetImporter(string path);
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
        static unique_ptr<ExporterBase<N>> GetExporter(string path);
        
    private:
        /**********************************************************************
        【类名】 Pair
        【功能】 存储导入/导出器。
        【接口说明】 简单数据类型，无函数。
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        struct Pair {
            // 维数
            size_t Dimension;
            // 导入器“构造函数”
            function<void*()> ImporterFactory;
            // 导出器“构造函数”
            function<void*()> ExporterFactory;
        };

        // 导入/导出器表
        static unordered_multimap<string, const Pair> m_Map;

        // 静态类，隐藏构造函数。
        StorageFactory();
};

}

}

#include "StorageFactory.tpp"