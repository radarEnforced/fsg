# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required( VERSION 3.4.1 )

####################################################################################################

# It seems that -O2 option is set in Release and -O0 is set in Debug
# setting CXX_FLAGS -O2 manually causes error
# set( CMAKE_CXX_FLAGS "-O2" )

####################################################################################################

# Setting FreeType paths
set( FREETYPE_PATH ${ANDROID_LIBS}/freetype-2.6.3/${ANDROID_ARCH_NAME} )
set( FREETYPE_INCLUDE ${FREETYPE_PATH}/include/freetype2 )
set( FREETYPE_LIB ${FREETYPE_PATH}/lib )

# Setting include and link directories
include_directories( ${FREETYPE_INCLUDE} )
link_directories( ${FREETYPE_LIB} )

add_library( freetype STATIC IMPORTED GLOBAL )

set_target_properties( freetype PROPERTIES IMPORTED_LOCATION ${FREETYPE_LIB}/libfreetype.a )

####################################################################################################

# Setting libxml2 paths
set( LIBXML2_PATH ${ANDROID_LIBS}/libxml2-2.9.1/${ANDROID_ARCH_NAME} )
set( LIBXML2_INCLUDE ${LIBXML2_PATH}/include/libxml2 )
set( LIBXML2_LIB ${LIBXML2_PATH}/lib )

# Setting include and link directories
include_directories( ${LIBXML2_INCLUDE} )
link_directories( ${LIBXML2_LIB} )

add_library( libxml2 STATIC IMPORTED GLOBAL )

set_target_properties( libxml2 PROPERTIES IMPORTED_LOCATION ${LIBXML2_LIB}/libxml2.a )

####################################################################################################

# Setting OpenSceneGraph paths
set( OSG_PATH ${ANDROID_LIBS}/osg-3.4.0/GLES1/${ANDROID_NDK_ABI_NAME} )
set( OSG_INCLUDE ${OSG_PATH}/include )
set( OSG_LIB ${OSG_PATH}/lib )
set( OSG_PLUGINS ${OSG_LIB}/osgPlugins-3.4.0 )

# Setting include and link directories
include_directories( ${OSG_INCLUDE} )
include_directories( ./src/main/cpp )
link_directories( ${OSG_LIB} )
link_directories( ${OSG_PLUGINS} )

# ??????
add_library( osgdb_rgb STATIC IMPORTED GLOBAL )
add_library( osgdb_osg STATIC IMPORTED GLOBAL )
add_library( osgdb_ive STATIC IMPORTED GLOBAL )
add_library( osgdb_freetype STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osgviewer STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osgvolume STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osgtext STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osgterrain STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osgsim STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osgshadow STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osgparticle STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osgfx STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osganimation STATIC IMPORTED GLOBAL )
add_library( osgdb_deprecated_osg STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osgvolume STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osgtext STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osgterrain STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osgsim STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osgshadow STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osgparticle STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osgmanipulator STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osgfx STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osganimation STATIC IMPORTED GLOBAL )
add_library( osgdb_serializers_osg STATIC IMPORTED GLOBAL )
add_library( osgViewer STATIC IMPORTED GLOBAL )
add_library( osgVolume STATIC IMPORTED GLOBAL )
add_library( osgTerrain STATIC IMPORTED GLOBAL )
add_library( osgText STATIC IMPORTED GLOBAL )
add_library( osgShadow STATIC IMPORTED GLOBAL )
add_library( osgSim STATIC IMPORTED GLOBAL )
add_library( osgParticle STATIC IMPORTED GLOBAL )
add_library( osgManipulator STATIC IMPORTED GLOBAL )
add_library( osgGA STATIC IMPORTED GLOBAL )
add_library( osgFX STATIC IMPORTED GLOBAL )
add_library( osgDB STATIC IMPORTED GLOBAL )
add_library( osgAnimation STATIC IMPORTED GLOBAL )
add_library( osgUtil STATIC IMPORTED GLOBAL )
add_library( osg STATIC IMPORTED GLOBAL )
add_library( OpenThreads STATIC IMPORTED GLOBAL )

set_target_properties( osgdb_rgb PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_rgb.a )
set_target_properties( osgdb_osg PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_osg.a )
set_target_properties( osgdb_ive PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_ive.a )
set_target_properties( osgdb_freetype PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_freetype.a )
set_target_properties( osgdb_deprecated_osgviewer PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osgviewer.a )
set_target_properties( osgdb_deprecated_osgvolume PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osgvolume.a )
set_target_properties( osgdb_deprecated_osgtext PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osgtext.a )
set_target_properties( osgdb_deprecated_osgterrain PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osgterrain.a )
set_target_properties( osgdb_deprecated_osgsim PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osgsim.a )
set_target_properties( osgdb_deprecated_osgshadow PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osgshadow.a )
set_target_properties( osgdb_deprecated_osgparticle PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osgparticle.a )
set_target_properties( osgdb_deprecated_osgfx PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osgfx.a )
set_target_properties( osgdb_deprecated_osganimation PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osganimation.a )
set_target_properties( osgdb_deprecated_osg PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_deprecated_osg.a )
set_target_properties( osgdb_serializers_osgvolume PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osgvolume.a )
set_target_properties( osgdb_serializers_osgtext PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osgtext.a )
set_target_properties( osgdb_serializers_osgterrain PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osgterrain.a )
set_target_properties( osgdb_serializers_osgsim PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osgsim.a )
set_target_properties( osgdb_serializers_osgshadow PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osgshadow.a )
set_target_properties( osgdb_serializers_osgparticle PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osgparticle.a )
set_target_properties( osgdb_serializers_osgmanipulator PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osgmanipulator.a )
set_target_properties( osgdb_serializers_osgfx PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osgfx.a )
set_target_properties( osgdb_serializers_osganimation PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osganimation.a )
set_target_properties( osgdb_serializers_osg PROPERTIES IMPORTED_LOCATION ${OSG_PLUGINS}/libosgdb_serializers_osg.a )
set_target_properties( osgViewer PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgViewer.a )
set_target_properties( osgVolume PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgVolume.a )
set_target_properties( osgTerrain PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgTerrain.a )
set_target_properties( osgText PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgText.a )
set_target_properties( osgShadow PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgShadow.a )
set_target_properties( osgSim PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgSim.a )
set_target_properties( osgParticle PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgParticle.a )
set_target_properties( osgManipulator PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgManipulator.a )
set_target_properties( osgGA PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgGA.a )
set_target_properties( osgFX PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgFX.a )
set_target_properties( osgDB PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgDB.a )
set_target_properties( osgAnimation PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgAnimation.a )
set_target_properties( osgUtil PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosgUtil.a )
set_target_properties( osg PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libosg.a )
set_target_properties( OpenThreads PROPERTIES IMPORTED_LOCATION ${OSG_LIB}/libOpenThreads.a )

####################################################################################################

set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--exclude-libs,libfreetype.a -Wl,--exclude-libs,libxml2.a" )

####################################################################################################

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             simNativeLib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/simNativeLib.cpp
             src/main/cpp/SimulationOSG.cpp

             src/main/cpp/sim/sim_Captions.cpp
             src/main/cpp/sim/sim_Creator.cpp
             src/main/cpp/sim/sim_Elevation.cpp
             src/main/cpp/sim/sim_Languages.cpp
             src/main/cpp/sim/sim_ListScenery.cpp
             src/main/cpp/sim/sim_ListUnits.cpp
             src/main/cpp/sim/sim_Manager.cpp
             src/main/cpp/sim/sim_Ownship.cpp
             src/main/cpp/sim/sim_Route.cpp
             src/main/cpp/sim/sim_Simulation.cpp
             src/main/cpp/sim/sim_Statistics.cpp

             src/main/cpp/sim/cgi/sim_Camera.cpp
             src/main/cpp/sim/cgi/sim_Color.cpp
             src/main/cpp/sim/cgi/sim_Effects.cpp
             src/main/cpp/sim/cgi/sim_FindNode.cpp
             src/main/cpp/sim/cgi/sim_FogScene.cpp
             src/main/cpp/sim/cgi/sim_Fonts.cpp
             src/main/cpp/sim/cgi/sim_Gates.cpp
             src/main/cpp/sim/cgi/sim_Geometry.cpp
             src/main/cpp/sim/cgi/sim_HUD.cpp
             src/main/cpp/sim/cgi/sim_ManipulatorOrbit.cpp
             src/main/cpp/sim/cgi/sim_ManipulatorShift.cpp
             src/main/cpp/sim/cgi/sim_ManipulatorWorld.cpp
             src/main/cpp/sim/cgi/sim_Models.cpp
             src/main/cpp/sim/cgi/sim_Module.cpp
             src/main/cpp/sim/cgi/sim_OTW.cpp
             src/main/cpp/sim/cgi/sim_Scenery.cpp
             src/main/cpp/sim/cgi/sim_SkyDome.cpp
             src/main/cpp/sim/cgi/sim_SplashScreen.cpp
             src/main/cpp/sim/cgi/sim_Textures.cpp
             src/main/cpp/sim/cgi/sim_UnitViewer.cpp

             src/main/cpp/sim/entities/sim_Aircraft.cpp
             src/main/cpp/sim/entities/sim_Balloon.cpp
             src/main/cpp/sim/entities/sim_Bomb.cpp
             src/main/cpp/sim/entities/sim_Bomber.cpp
             src/main/cpp/sim/entities/sim_BomberDive.cpp
             src/main/cpp/sim/entities/sim_BomberLevel.cpp
             src/main/cpp/sim/entities/sim_BomberTorpedo.cpp
             src/main/cpp/sim/entities/sim_Building.cpp
             src/main/cpp/sim/entities/sim_Bullet.cpp
             src/main/cpp/sim/entities/sim_Entities.cpp
             src/main/cpp/sim/entities/sim_Entity.cpp
             src/main/cpp/sim/entities/sim_Explosion.cpp
             src/main/cpp/sim/entities/sim_Fighter.cpp
             src/main/cpp/sim/entities/sim_Flak.cpp
             src/main/cpp/sim/entities/sim_Group.cpp
             src/main/cpp/sim/entities/sim_Gunner.cpp
             src/main/cpp/sim/entities/sim_Kamikaze.cpp
             src/main/cpp/sim/entities/sim_Munition.cpp
             src/main/cpp/sim/entities/sim_Torpedo.cpp
             src/main/cpp/sim/entities/sim_Tracer.cpp
             src/main/cpp/sim/entities/sim_Unit.cpp
             src/main/cpp/sim/entities/sim_UnitAerial.cpp
             src/main/cpp/sim/entities/sim_UnitGround.cpp
             src/main/cpp/sim/entities/sim_UnitMarine.cpp
             src/main/cpp/sim/entities/sim_UnitSurface.cpp
             src/main/cpp/sim/entities/sim_Warship.cpp
             src/main/cpp/sim/entities/sim_Wreckage.cpp
             src/main/cpp/sim/entities/sim_WreckageAircraft.cpp
             src/main/cpp/sim/entities/sim_WreckageSurface.cpp

             src/main/cpp/sim/missions/sim_Mission.cpp
             src/main/cpp/sim/missions/sim_Objective.cpp
             src/main/cpp/sim/missions/sim_ObjectiveAirspeed.cpp
             src/main/cpp/sim/missions/sim_ObjectiveAltitude.cpp
             src/main/cpp/sim/missions/sim_ObjectiveHeading.cpp
             src/main/cpp/sim/missions/sim_ObjectiveDefend.cpp
             src/main/cpp/sim/missions/sim_ObjectiveDestroy.cpp
             src/main/cpp/sim/missions/sim_ObjectiveDistance.cpp
             src/main/cpp/sim/missions/sim_ObjectiveTimeout.cpp
             src/main/cpp/sim/missions/sim_ObjectiveWaypoint.cpp
             src/main/cpp/sim/missions/sim_Stage.cpp

             src/main/cpp/sim/sfx/sim_SFX.cpp
             src/main/cpp/sim/sfx/sim_BufferQueuePlayer.cpp
             src/main/cpp/sim/sfx/sim_EngineOpenSLES.cpp

             src/main/cpp/sim/utils/sim_Angles.cpp
             src/main/cpp/sim/utils/sim_PID.cpp
             src/main/cpp/sim/utils/sim_Random.cpp
             src/main/cpp/sim/utils/sim_String.cpp
             src/main/cpp/sim/utils/sim_Text.cpp
             src/main/cpp/sim/utils/sim_XmlDoc.cpp
             src/main/cpp/sim/utils/sim_XmlNode.cpp
             src/main/cpp/sim/utils/sim_XmlUtils.cpp )

####################################################################################################

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

find_library( egl-lib EGL )
find_library( gles1-lib GLESv1_CM )

find_library( sles-lib OpenSLES )

find_library( zlib-lbrary z )

####################################################################################################

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       simNativeLib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}

                       # Links to GLES libs
                       ${egl-lib}
                       ${gles1-lib}

                       # Links to SLES lib
                       ${sles-lib}

                       -Wl,--start-group

                       # Links to zlib
                       ${zlib-lbrary}

                       # Links the target library to the FreeType library
                       freetype

                       # Links the target library to the libxml2 library
                       libxml2

                       # Links the target library to the OSG libraries
                       osgdb_rgb
                       osgdb_osg
                       osgdb_ive
                       osgdb_freetype
                       osgdb_deprecated_osgviewer
                       osgdb_deprecated_osgvolume
                       osgdb_deprecated_osgtext
                       osgdb_deprecated_osgterrain
                       osgdb_deprecated_osgsim
                       osgdb_deprecated_osgshadow
                       osgdb_deprecated_osgparticle
                       osgdb_deprecated_osgfx
                       osgdb_deprecated_osganimation
                       osgdb_deprecated_osg
                       osgdb_serializers_osgvolume
                       osgdb_serializers_osgtext
                       osgdb_serializers_osgterrain
                       osgdb_serializers_osgsim
                       osgdb_serializers_osgshadow
                       osgdb_serializers_osgparticle
                       osgdb_serializers_osgmanipulator
                       osgdb_serializers_osgfx
                       osgdb_serializers_osganimation
                       osgdb_serializers_osg
                       osgViewer
                       osgVolume
                       osgTerrain
                       osgText
                       osgShadow
                       osgSim
                       osgParticle
                       osgManipulator
                       osgGA
                       osgFX
                       osgDB
                       osgAnimation
                       osgUtil
                       osg
                       OpenThreads

                       -Wl,--end-group )
