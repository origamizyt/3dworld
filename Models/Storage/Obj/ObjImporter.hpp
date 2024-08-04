/*************************************************************************
【文件名】 ObjImporter.hpp
【功能模块和目的】 ObjImporter 类定义了一个 .obj 文件的导入器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#pragma once

#include <fstream>
#include "../ImporterBase.hpp"
#include "../../Core/Model.hpp"
using namespace std;
using namespace c3w;
using namespace c3w::storage;

namespace c3w::storage::obj {

/*************************************************************************
【类名】 ObjImporter
【功能】 定义一个 .obj 文件的导入器。
【接口说明】 导入指定的文件。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class ObjImporter: public ImporterBase<3> {
    protected:
        /**********************************************************************
        【函数名称】 InnerImport
        【函数功能】 导入指定文件流到模型中。
        【参数】 
            stream: 已经打开的文件流。
            model: 模型的可变引用。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void InnerImport(ifstream& stream, Model<3>& model) const override;
};

}