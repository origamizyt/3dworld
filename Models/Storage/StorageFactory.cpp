/*************************************************************************
【文件名】 StorageFactory.cpp
【功能模块和目的】 为 StorageFactory.hpp 提供非模板的实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <functional>
#include <list>
#include <string>
#include "StorageFactory.hpp"
using namespace std;

namespace c3w::storage {

// 导入/导出器列表
list<StorageFactory::Pair> StorageFactory::m_Pairs {
    { ".obj", 3, 
        [](){ return new obj::ObjImporter(); },
        [](){ return new obj::ObjExporter(); }
    }
};

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
void StorageFactory::Register(
    string extension,
    size_t dimension,
    function<void*()> importerFactory,
    function<void*()> exporterFactory
) {
    m_Pairs.push_back(Pair { 
        extension, dimension, importerFactory, exporterFactory 
    });
}

}