#if 0
#include <stdio.h>
#include <stdlib.h>
#include "genann.h"

const char* save_name = "example/xor.ann";

int main( int argc, char* argv[] ) {
    printf( "GENANN example 3.\n" );
    printf( "Load a saved ANN to solve the XOR function.\n" );


    FILE* saved = fopen( save_name, "r" );
    if ( !saved ) {
        printf( "Couldn't open file: %s\n", save_name );
        exit( 1 );
    }

    genann* ann = genann_read( saved );
    fclose( saved );

    if ( !ann ) {
        printf( "Error loading ANN from file: %s.", save_name );
        exit( 1 );
    }


    /* Input data for the XOR function. */
    const double input[ 4 ][ 2 ] = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };

    /* Run the network and see what it predicts. */
    printf( "Output for [%1.f, %1.f] is %1.f.\n", input[ 0 ][ 0 ], input[ 0 ][ 1 ], *genann_run( ann, input[ 0 ] ) );
    printf( "Output for [%1.f, %1.f] is %1.f.\n", input[ 1 ][ 0 ], input[ 1 ][ 1 ], *genann_run( ann, input[ 1 ] ) );
    printf( "Output for [%1.f, %1.f] is %1.f.\n", input[ 2 ][ 0 ], input[ 2 ][ 1 ], *genann_run( ann, input[ 2 ] ) );
    printf( "Output for [%1.f, %1.f] is %1.f.\n", input[ 3 ][ 0 ], input[ 3 ][ 1 ], *genann_run( ann, input[ 3 ] ) );

    genann_free( ann );


    printf( "\n\n" );
    system( "pause" );  // 按任意键退出控制台
    return 0;
}

#endif

#if 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genann.h"

int main( int argc, char* argv[] ) {
    printf( "GENANN example 1.\n" );
    printf( "Train a small ANN to the XOR function using backpropagation.\n" );

    /* This will make the neural network initialize differently each run. */
    /* If you don't get a good result, try again for a different result. */
    srand( time( 0 ) );

    /* Input and expected out data for the XOR function. */
    const double input[ 4 ][ 2 ] = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };
    const double output[ 4 ]     = { 0, 1, 1, 0 };
    int          i;

    /* New network with 2 inputs,
     * 1 hidden layer of 2 neurons,
     * and 1 output. */
    genann* ann = genann_init( 2, 3, 6, 1 );  // 中间多层隐藏层神经元数量一致

    /* Train on the four labeled data points many times. */
    for ( i = 0; i < 500; ++i ) {
        genann_train( ann, input[ 0 ], output + 0, 3 );
        genann_train( ann, input[ 1 ], output + 1, 3 );
        genann_train( ann, input[ 2 ], output + 2, 3 );
        genann_train( ann, input[ 3 ], output + 3, 3 );
    }

    /* Run the network and see what it predicts. */
    printf( "Output for [%1.f, %1.f] is %1.f.\n", input[ 0 ][ 0 ], input[ 0 ][ 1 ], *genann_run( ann, input[ 0 ] ) );
    printf( "Output for [%1.f, %1.f] is %1.f.\n", input[ 1 ][ 0 ], input[ 1 ][ 1 ], *genann_run( ann, input[ 1 ] ) );
    printf( "Output for [%1.f, %1.f] is %1.f.\n", input[ 2 ][ 0 ], input[ 2 ][ 1 ], *genann_run( ann, input[ 2 ] ) );
    printf( "Output for [%1.f, %1.f] is %1.f.\n", input[ 3 ][ 0 ], input[ 3 ][ 1 ], *genann_run( ann, input[ 3 ] ) );

    printf( "\n" );
    printf( "中间隐藏层神经元数量一致：%d \n", ann->hidden );
    printf( "ANN神经元总数：%d \n", ann->total_weights );

    genann_free( ann );

    printf( "\n\n" );
    system( "pause" );  // 按任意键退出控制台
    return 0;
}


#endif