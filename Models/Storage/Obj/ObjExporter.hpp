/*************************************************************************
【文件名】 ObjExporter.hpp
【功能模块和目的】 ObjExporter 类定义了一个 .obj 文件的导出器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#pragma once

#include <fstream>
#include "../ExporterBase.hpp"
#include "../../Core/Model.hpp"
using namespace std;
using namespace C3w;
using namespace C3w::Storage;

namespace C3w {

namespace Storage {

namespace Obj {

/*************************************************************************
【类名】 ObjExporter
【功能】 定义一个 .obj 文件的导出器。
【接口说明】 导出至指定的文件。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
class ObjExporter: public ExporterBase<3> {
    protected:
        /**********************************************************************
        【函数名称】 InnerExport
        【函数功能】 导出指定模型到文件流中。
        【参数】 
            stream: 已经打开的文件流。
            model: 模型的可变引用。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void InnerExport(
            ofstream& stream, 
            const Model<3>& model
        ) const override;
};

}

}

}