/*************************************************************************
【文件名】 StorageFactory.hpp
【功能模块和目的】 StorageFactory 用于静态获取导入/导出器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#pragma once

#include <cstddef>
#include <string>
#include <list>
#include <functional>
#include <memory>
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
            dimension: 要注册的维度。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        template <typename Importer, typename Exporter>
        static void Register(string extension, size_t dimension);
        /**********************************************************************
        【函数名称】 Register
        【函数功能】 注册一对自定义的导入/导出器。
        【参数】
            extension: 要注册的扩展名。
            dimension: 要注册的维度。
            importerFactory: 一个构造导入器的函数。
            exporterFactory: 一个构造导出器的函数。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        static void Register(
            string extension,
            size_t dimension,
            function<void*()> importerFactory,
            function<void*()> exporterFactory
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
        // 一个存储导入/导出器的结构
        struct Pair {
            // 文件的扩展名
            string Extension;
            // 模型的维度
            size_t Dimension;
            // 导入器构造函数/工厂
            function<void*()> ImporterFactory;
            // 导出器构造函数/工厂
            function<void*()> ExporterFactory;
        };

        // 导入/导出器列表
        // 使用链表获得更好的性能
        static list<Pair> m_Pairs;

        // 静态类，隐藏构造函数。
        StorageFactory();
};

}

}

#include "StorageFactory.tpp"