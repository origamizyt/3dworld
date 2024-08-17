/*************************************************************************
【文件名】 ObjImporter.hpp
【功能模块和目的】 ObjImporter 类定义了一个 .Obj 文件的导入器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#ifndef OBJ_IMPORTER_HPP
#define OBJ_IMPORTER_HPP

#include <fstream>
#include "../ImporterBase.hpp"
#include "../../Core/Model.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Storage;

namespace C3w {

namespace Storage {

namespace Obj {

/*************************************************************************
【类名】 ObjImporter
【功能】 定义一个 .obj 文件的导入器。
【接口说明】 
    继承于 C3w::Storage::ImporterBase<3>:
        继承全部接口。
        实现 InnerImport。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class ObjImporter: public ImporterBase<3> {
    protected:
        /**********************************************************************
        【函数名称】 InnerImport
        【函数功能】 导入指定文件流到模型中。
        【参数】 
            Stream: 已经打开的文件流。
            Model: 模型的可变引用。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void InnerImport(ifstream& Stream, Model<3>& Model) const override;
};

}

}

}

#endif