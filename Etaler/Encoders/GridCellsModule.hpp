#pragma once

#include <Etaler/Core/Tensor.hpp>
#include <vector>
#include <array>
#include <cmath>
#include <random>

#include <Etaler/Core/Random.hpp>
#include <Etaler/Core/Tensor.hpp>
#include <Etaler/Core/Backend.hpp>

#define MAX_MODULES 16 
namespace et
{

    namespace encoder
    {

        struct GridCellsModule 
        {
            public:
                Tensor t;
                size_t seed=42;
                int * syn_conn[MAX_MODULES]; // array of connections per module 
                int activity[MAX_MODULES]; // bumpo location per module
                int wrap_around[MAX_MODULES];
                int module_size;

                
                Tensor connections_;

        };

        typedef struct GridCellsModule GC;        
        void GridCellActivate(GC * gc, int pulse);
        void GridCellInit(GC * gc, int module_size);
        void GridCellAnkor(GC * gc, int * ankor);
        void GridCellPrint(GC* gc);
    
    }
}