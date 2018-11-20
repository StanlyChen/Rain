#pragma once
#include "RainTypes.h"
#include "RainView.h"

namespace Rain
{
    
    class IMesh
    {
    public:
        IMesh();
        virtual ~IMesh();

    public:
        virtual void init(RainContext context) {} ;
        virtual void update(RainContext context)  {};
        virtual void release(RainContext context) {};
    };

}

