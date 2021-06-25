#include <Etaler/Core/Tensor.hpp>
#include <vector>
#include <array>
#include <cmath>
#include <random>

#include <Etaler/Core/Random.hpp>
#include <Etaler/Core/Tensor.hpp>
#include <Etaler/Core/Backend.hpp>
#include <Etaler/Encoders/GridCellsModule.hpp>

namespace et
{

    namespace encoder
    {
  
        void GridCellInit(GC * gc, int module_size)
        {
            gc->module_size = module_size;
            for (int m=0;m<MAX_MODULES;m++)
            {
                gc->syn_conn[m] = (int *)malloc(sizeof(int)*module_size); 
                memset(gc->syn_conn[m],0,module_size*sizeof(int));
                gc->activity[m] = 0;
                float f = 1.4; // taken from papers on GC modules ratio
                gc->wrap_around[m] = (int)(100*pow(f,m)); // simulate a 1.4 ratio between modules 
            }
            
        }

        void GridCellActivate(GC * gc, int pulse)
        {
            for (int m=0;m<MAX_MODULES;m++)
            {
                // erase the previous bump
                gc->syn_conn[m][(gc->activity[m]*gc->module_size)/gc->wrap_around[m]] = 0;
                // calculate a new one
                gc->activity[m] += pulse;
                gc->activity[m] %= gc->wrap_around[m];
                gc->syn_conn[m][(gc->activity[m]*gc->module_size)/gc->wrap_around[m]] = 1;
            }
           
        }

        // this function resets the GC to an array of activities per module
        void GridCellAnkor(GC * gc, int * ankor)
        {

        }

        void GridCellPrint(GC* gc)
        {   
            printf("********************************\n");
            for (int m=0;m<MAX_MODULES;m++)
            {
                for (int phase = 0; phase < gc->module_size; phase++)
                {
                    printf(" %01d",gc->syn_conn[m][phase]);
                }
                printf("\n");
            }
        }
    }
}