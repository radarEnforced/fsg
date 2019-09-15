/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <jni.h>

#include "SimulationOSG.h"

////////////////////////////////////////////////////////////////////////////////

SimulationOSG sim;

////////////////////////////////////////////////////////////////////////////////

extern "C"
{
    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_initCampaign( JNIEnv *env, jobject obj,
                                                                           jint width, jint height,
                                                                           jboolean silent,
                                                                           jint mission_index );

    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_initSkirmish( JNIEnv *env, jobject obj,
                                                                           jint width, jint height,
                                                                           jboolean silent,
                                                                           jint scenery_index,
                                                                           jint ownship_type , jint ownship_livery,
                                                                           jint wingman_type , jint wingman_livery,
                                                                           jint ally_1_type  , jint ally_1_livery,
                                                                           jint ally_2_type  , jint ally_2_livery,
                                                                           jint enemy_1_type , jint enemy_1_livery,
                                                                           jint enemy_2_type , jint enemy_2_livery,
                                                                           jint enemy_3_type , jint enemy_3_livery,
                                                                           jint enemy_4_type , jint enemy_4_livery );
    
    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_initUnitView( JNIEnv *env, jobject obj,
                                                                           jint width, jint height,
                                                                           jint unitIndex );

    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_pause( JNIEnv *env, jobject obj );
    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_unpause( JNIEnv *env, jobject obj );
    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_restart( JNIEnv *env, jobject obj );
    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_destroy( JNIEnv *env, jobject obj );

    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_update( JNIEnv *env, jobject obj,
                                                                     jdouble timeStep );

    JNIEXPORT jfloat JNICALL Java_pl_marekcel_fsg_SimNativeLib_getInitThrottle( JNIEnv *env, jobject obj );

    JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getStatus( JNIEnv *env, jobject obj );

    JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getFriendsActivated( JNIEnv *env, jobject obj );
    JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getFriendsDestroyed( JNIEnv *env, jobject obj );
    JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getEnemiesActivated( JNIEnv *env, jobject obj );
    JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getEnemiesDestroyed( JNIEnv *env, jobject obj );
    JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getOwnshipDestroyed( JNIEnv *env, jobject obj );
    JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getFlightTime( JNIEnv *env, jobject obj );

    JNIEXPORT jboolean JNICALL Java_pl_marekcel_fsg_SimNativeLib_isFinished( JNIEnv *env, jobject obj );
    JNIEXPORT jboolean JNICALL Java_pl_marekcel_fsg_SimNativeLib_isPaused( JNIEnv *env, jobject obj );
    JNIEXPORT jboolean JNICALL Java_pl_marekcel_fsg_SimNativeLib_isPending( JNIEnv *env, jobject obj );

    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_setBasePath( JNIEnv *env, jobject obj,
                                                                          jstring basePath );

    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_setControls( JNIEnv *env, jobject obj,
                                                                          jboolean trigger,
                                                                          jfloat ctrlRoll,
                                                                          jfloat ctrlPitch,
                                                                          jfloat ctrlYaw,
                                                                          jfloat throttle );

    JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_setLanguage( JNIEnv *env, jobject obj,
                                                                          jint index );
};

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_initCampaign( JNIEnv *env, jobject obj,
                                                                       jint width, jint height,
                                                                       jboolean silent,
                                                                       jint mission_index )
{
    sim.initCampaign( 0, 0, width, height, silent, mission_index );
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_initSkirmish( JNIEnv *env, jobject obj,
                                                                       jint width, jint height,
                                                                       jboolean silent,
                                                                       jint scenery_index,
                                                                       jint ownship_type , jint ownship_livery,
                                                                       jint wingman_type , jint wingman_livery,
                                                                       jint ally_1_type  , jint ally_1_livery,
                                                                       jint ally_2_type  , jint ally_2_livery,
                                                                       jint enemy_1_type , jint enemy_1_livery,
                                                                       jint enemy_2_type , jint enemy_2_livery,
                                                                       jint enemy_3_type , jint enemy_3_livery,
                                                                       jint enemy_4_type , jint enemy_4_livery )
{
    sim.initSkirmish( 0, 0, width, height, silent,
                      scenery_index,
                      ownship_type , ownship_livery,
                      wingman_type , wingman_livery,
                      ally_1_type  , ally_1_livery,
                      ally_2_type  , ally_2_livery,
                      enemy_1_type , enemy_1_livery,
                      enemy_2_type , enemy_2_livery,
                      enemy_3_type , enemy_3_livery,
                      enemy_4_type , enemy_4_livery );
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_initUnitView( JNIEnv *env, jobject obj,
                                                                       jint width, jint height,
                                                                       jint unitIndex )
{
    sim.initUnitView( 0, 0, width, height, unitIndex );
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_pause( JNIEnv *env, jobject obj )
{
    sim.pause();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_unpause( JNIEnv *env, jobject obj )
{
    sim.unpause();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_restart( JNIEnv *env, jobject obj )
{
    sim.restart();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_destroy( JNIEnv *env, jobject obj)
{
    sim.destroy();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_update( JNIEnv *env, jobject obj,
                                                                 jdouble timeStep )
{
    sim.update( timeStep );
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jfloat JNICALL Java_pl_marekcel_fsg_SimNativeLib_getInitThrottle( JNIEnv *env, jobject obj )
{
    return sim.getInitThrottle();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getStatus( JNIEnv *env, jobject obj )
{
    return sim.getStatus();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getFriendsActivated( JNIEnv *env, jobject obj )
{
    return sim.getFriendsActivated();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getFriendsDestroyed( JNIEnv *env, jobject obj )
{
    return sim.getFriendsDestroyed();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getEnemiesActivated( JNIEnv *env, jobject obj )
{
    return sim.getEnemiesActivated();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getEnemiesDestroyed( JNIEnv *env, jobject obj )
{
    return sim.getEnemiesDestroyed();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getOwnshipDestroyed( JNIEnv *env, jobject obj )
{
    return sim.getOwnshipDestroyed();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jint JNICALL Java_pl_marekcel_fsg_SimNativeLib_getFlightTime( JNIEnv *env, jobject obj )
{
    return sim.getFlightTime();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jboolean JNICALL Java_pl_marekcel_fsg_SimNativeLib_isFinished( JNIEnv *env, jobject obj )
{
    return sim.isFinished();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jboolean JNICALL Java_pl_marekcel_fsg_SimNativeLib_isPaused( JNIEnv *env, jobject obj )
{
    return sim.isPaused();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT jboolean JNICALL Java_pl_marekcel_fsg_SimNativeLib_isPending( JNIEnv *env, jobject obj )
{
    return sim.isPending();
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_setBasePath( JNIEnv *env, jobject obj,
                                                                      jstring basePath )
{
    //if ( !basePath ) LString();

    const jsize len = env->GetStringUTFLength( basePath );
    const char* str = env->GetStringUTFChars( basePath, (jboolean*)0 );

    std::string basePathStr( str, len );

    env->ReleaseStringUTFChars( basePath, str );

    sim.setBasePath( basePathStr );
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_setControls( JNIEnv *env, jobject obj,
                                                                      jboolean trigger,
                                                                      jfloat ctrlRoll,
                                                                      jfloat ctrlPitch,
                                                                      jfloat ctrlYaw,
                                                                      jfloat throttle )
{
    sim.setControls( trigger, ctrlRoll, ctrlPitch, ctrlYaw, throttle );
}

////////////////////////////////////////////////////////////////////////////////

JNIEXPORT void JNICALL Java_pl_marekcel_fsg_SimNativeLib_setLanguage( JNIEnv *env, jobject obj,
                                                                      jint index )
{
    sim.setLanguage( index );
}
