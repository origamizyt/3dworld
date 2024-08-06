/*************************************************************************
【文件名】 ExporterBase.hpp
【功能模块和目的】 ExporterBase 类定义了一个抽象的导出器。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/

#pragma once

#include <cstddef>
#include <fstream>
#include <string>
#include "../Core/Model.hpp"
using namespace std;
using namespace C3w;

namespace C3w {

namespace Storage {

/*************************************************************************
【类名】 ExporterBase
【功能】 定义一个抽象的导出器。
【接口说明】 导出至指定的文件。
【开发者及日期】 赵一彤 2024/7/24
*************************************************************************/
template <size_t N>
class ExporterBase {
    public:
        // 操作

        /**********************************************************************
        【函数名称】 Export
        【函数功能】 导出指定模型到文件中。
        【参数】 
            path: 文件所在路径。
            model: 模型的可变引用。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        void Export(string path, const Model<N>& model) const;

        // 虚析构函数
        virtual ~ExporterBase() = default;

    protected:
        /**********************************************************************
        【函数名称】 InnerExport
        【函数功能】 导出指定模型到文件流中。
        【参数】 
            stream: 已经打开的文件流。
            model: 模型的常引用。
        【返回值】 无
        【开发者及日期】 赵一彤 2024/7/24
        **********************************************************************/
        virtual void InnerExport(
            ofstream& stream,
            const Model<N>& model
        ) const = 0;
};

}

}

#include "ExporterBase.tpp"