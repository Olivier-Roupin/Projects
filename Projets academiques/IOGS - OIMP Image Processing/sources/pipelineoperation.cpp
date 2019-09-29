#include "pipelineoperation.h"

PipelineOperation::PipelineOperation()
{

}

PipelineOperation::~PipelineOperation()
{
    for(unsigned int i=0 ; i<_operations.size() ; ++i)
        delete _operations[i];
}

void PipelineOperation::addOperation(Operation *o)
{
    _operations.push_back(o);
}

void PipelineOperation::cancel()
{
    delete _operations.back();
    _operations.pop_back();
}

bool PipelineOperation::is_Empty()
{
    return _operations.empty();
}

float PipelineOperation::processPixel(unsigned int i, unsigned int j, unsigned int c, const Image &img) const
{
    return 0;
}

void PipelineOperation::process(const Image &in, Image &out) const
{
    Image img = in;
    out = in;
    for(unsigned int i=0 ; i<_operations.size() ; ++i)
    {
        _operations[i]->process(img, out);
        img = out;
    }
}

