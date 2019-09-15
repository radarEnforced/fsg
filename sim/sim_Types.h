#ifndef SIM_TYPES_H
#define SIM_TYPES_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Quat>
#include <osg/Vec3d>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

////////////////////////////////////////////////////////////////////////////////

typedef unsigned char  UInt8;   ///< 8-bits unsigned integer type
typedef unsigned short UInt16;  ///< 16-bits unsigned integer type
typedef unsigned int   UInt32;  ///< 32-bits unsigned integer type

typedef osg::Quat  Quat;        ///< common quaternion
typedef osg::Vec3d Vec3;        ///< common vector

////////////////////////////////////////////////////////////////////////////////

/** Unit affiliation enum. */
enum Affiliation
{
    Unknown = 0,                ///< unknown
    Friend  = 1,                ///< friend
    Hostile = 2,                ///< hostile
    Neutral = 3                 ///< neutral
};

////////////////////////////////////////////////////////////////////////////////

/** Message text allignment. */
enum Alignment
{
    Left   = 0,                 ///< left
    Center = 1,                 ///< center
    Right  = 2                  ///< right
};

////////////////////////////////////////////////////////////////////////////////

/** Entity state enum. */
enum State
{
    Active   = 0,               ///< active
    Standby  = 1,               ///< stand-by
    Inactive = 2,               ///< innctive (e.g. destroyed)
};

////////////////////////////////////////////////////////////////////////////////

/** Mission, stages and objectives status enum. */
enum Status
{
    Pending = 0,                ///< pending (neither failure nor success)
    Failure = 1,                ///< failure
    Success = 2                 ///< success
};

////////////////////////////////////////////////////////////////////////////////

/** Tutorial tips eum. */
enum TutorialTip
{
    NoTip     = 0,              ///< no tip
    BankLeft  = 1,              ///< bank left
    BankRight = 2,              ///< bank right
    PitchUp   = 3,              ///< pitch up
    PitchDown = 4               ///< pitch down
};

////////////////////////////////////////////////////////////////////////////////

/** View type enum. */
enum ViewType
{
    ViewChase = 0,              ///< chase view
    ViewFlyby = 1,              ///< flyby view
    ViewFront = 2,              ///< front view
    ViewOrbit = 3,              ///< orbit view
    ViewPilot = 4,              ///< pilot view
    ViewShift = 5,              ///< shift view
    ViewWorld = 6               ///< world view
};

////////////////////////////////////////////////////////////////////////////////

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_TYPES_H
