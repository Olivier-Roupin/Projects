#ifndef PIPELINEOPERATION_H
#define PIPELINEOPERATION_H

#include "operation.h"

class PipelineOperation : public Operation
{
public:
    PipelineOperation();
    ~PipelineOperation();
    void addOperation(Operation* o);
    void cancel();
    bool is_Empty();
    virtual void process(const Image& in, Image& out) const;

protected:
    virtual float processPixel(unsigned int i, unsigned int j, unsigned int c, const Image& img) const;

private:
    std::vector<Operation*> _operations;
};

#endif // PIPELINEOPERATION_H
