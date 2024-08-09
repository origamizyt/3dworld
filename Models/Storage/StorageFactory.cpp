/*************************************************************************
【文件名】 StorageFactory.cpp
【功能模块和目的】 为 StorageFactory.hpp 提供非模板的实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <functional>
#include <string>
#include <unordered_map>
#include "Obj/ObjImporter.hpp"
#include "Obj/ObjExporter.hpp"
#include "StorageFactory.hpp"
using namespace std;

namespace C3w {

namespace Storage {

// 导入/导出器表
unordered_multimap<string, const StorageFactory::Pair> StorageFactory::m_Map {
    { 
        ".obj",
        { 
            .Dimension = 3, 
            .ImporterFactory = []() { return new Obj::ObjImporter(); },
            .ExporterFactory = []() { return new Obj::ObjExporter(); }
        } 
    }
};

}

}