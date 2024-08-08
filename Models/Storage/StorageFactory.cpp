/*************************************************************************
【文件名】 StorageFactory.cpp
【功能模块和目的】 为 StorageFactory.hpp 提供非模板的实现。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#include <functional>
#include <list>
#include <string>
#include "Obj/ObjImporter.hpp"
#include "Obj/ObjExporter.hpp"
#include "StorageFactory.hpp"
using namespace std;

namespace C3w {

namespace Storage {

// 导入/导出器列表
list<StorageFactory::Pair> StorageFactory::m_Pairs {
    { ".obj", 3, 
        [](){ return new Obj::ObjImporter(); },
        [](){ return new Obj::ObjExporter(); }
    }
};

}

}