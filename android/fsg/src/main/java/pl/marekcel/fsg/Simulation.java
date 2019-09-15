package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.hardware.Sensor;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.KeyEvent;
import android.view.MotionEvent;

////////////////////////////////////////////////////////////////////////////////

/** Main simulation singleton class. */
public class Simulation
{
    public static final String LOG_TAG = "Simulation";

    public static final int STATUS_PENDING = 0; ///<
    public static final int STATUS_FAILURE = 1; ///<
    public static final int STATUS_SUCCESS = 2; ///<
    
    public static final int MODE_CAMPAIGN = 0;  ///<
    public static final int MODE_SKIRMISH = 1;  ///<
    
    public static final int MAX_WIDTH = 1280;   ///< [px] maximum viewport width

    private static int mScaledWidth  = 0;       ///< [px] viewport width
    private static int mScaledHeight = 0;       ///< [px] viewport height
    
    private static int mViewWidth  = 0;         ///< [px] EGL view width
    private static int mViewHeight = 0;         ///< [px] EGL view height
    
    private static int mMode = MODE_CAMPAIGN;   ///<

    private static int mMissionIndex  = -1;     ///< current mission index
    private static int mSceneryIndex  = -1;     ///<
    private static int mOwnshipType   = -1;     ///<
    private static int mWingmanType   = -1;     ///<
    private static int mAllyType1     = -1;     ///<
    private static int mAllyType2     = -1;     ///<
    private static int mEnemyType1    = -1;     ///<
    private static int mEnemyType2    = -1;     ///<
    private static int mEnemyType3    = -1;     ///<
    private static int mEnemyType4    = -1;     ///<
    private static int mOwnshipLivery = -1;     ///<
    private static int mWingmanLivery = -1;     ///<
    private static int mAllyLivery1   = -1;     ///<
    private static int mAllyLivery2   = -1;     ///<
    private static int mEnemyLivery1  = -1;     ///<
    private static int mEnemyLivery2  = -1;     ///<
    private static int mEnemyLivery3  = -1;     ///<
    private static int mEnemyLivery4  = -1;     ///<
    
    private static boolean mInited = false;     ///<
    private static boolean mUpdate = false;     ///<

    private static boolean mSilent = false;     ///<
    
    private static Controls mControls = null;   ///<

    /** Sets up simulation. */
    public static void setup( int missionIndex )
    {
        mMode = MODE_CAMPAIGN;
        
        mMissionIndex = missionIndex;
        mSceneryIndex = -1;
        
        mOwnshipType = -1;
        mWingmanType = -1;
        mAllyType1   = -1;
        mAllyType2   = -1;
        mEnemyType1  = -1;
        mEnemyType2  = -1;
        mEnemyType3  = -1;
        mEnemyType4  = -1;
        
        mOwnshipLivery = -1;
        mWingmanLivery = -1;
        mAllyLivery1   = -1;
        mAllyLivery2   = -1;
        mEnemyLivery1  = -1;
        mEnemyLivery2  = -1;
        mEnemyLivery3  = -1;
        mEnemyLivery4  = -1;
    }

    /** Sets up simulation. */
    public static void setup( int sceneryIndex,
                              int ownshipType , int ownshipLilvery,
                              int wingmanType , int wingmanLilvery,
                              int allyType1   , int allyLilvery1,
                              int allyType2   , int allyLilvery2,
                              int enemyType1  , int enemyLilvery1,
                              int enemyType2  , int enemyLilvery2,
                              int enemyType3  , int enemyLilvery3,
                              int enemyType4  , int enemyLilvery4 )
    {
        mMode = MODE_SKIRMISH;
        
        mMissionIndex = -1;
        mSceneryIndex = sceneryIndex;
        
        mOwnshipType = ownshipType;
        mWingmanType = wingmanType;
        mAllyType1   = allyType1;
        mAllyType2   = allyType2;
        mEnemyType1  = enemyType1;
        mEnemyType2  = enemyType2;
        mEnemyType3  = enemyType3;
        mEnemyType4  = enemyType4;
        
        mOwnshipLivery = ownshipLilvery;
        mWingmanLivery = wingmanLilvery;
        mAllyLivery1   = allyLilvery1;
        mAllyLivery2   = allyLilvery2;
        mEnemyLivery1  = enemyLilvery1;
        mEnemyLivery2  = enemyLilvery2;
        mEnemyLivery3  = enemyLilvery3;
        mEnemyLivery4  = enemyLilvery4;
    }

    /** Initializes simulation.  */
    public static void init()
    {
        if ( !mInited )
        {
            mInited = true;

            if ( mControls instanceof ControlsSensors )
            {
                ControlsSensors controlsSensors = (ControlsSensors)mControls;

                if ( controlsSensors != null )
                {
                    controlsSensors.setResolution( mViewWidth, mViewHeight );
                }
            }

            switch ( mMode )
            {
                case MODE_CAMPAIGN:
                    SimNativeLib.initCampaign( mScaledWidth, mScaledHeight, mSilent,
                            mMissionIndex );
                    break;

                case MODE_SKIRMISH:
                    SimNativeLib.initSkirmish( mScaledWidth, mScaledHeight, mSilent,
                            mSceneryIndex,
                            mOwnshipType , mOwnshipLivery,
                            mWingmanType , mWingmanLivery,
                            mAllyType1   , mAllyLivery1,
                            mAllyType2   , mAllyLivery2,
                            mEnemyType1  , mEnemyLivery1,
                            mEnemyType2  , mEnemyLivery2,
                            mEnemyType3  , mEnemyLivery3,
                            mEnemyType4  , mEnemyLivery4 );
                    break;
            }
                                         
            mUpdate = true;
        }
    }
    
    /** Updates simulation. */
    public static void update( double timeStep )
    {
        if ( mInited && mUpdate )
        {
            SimNativeLib.update( timeStep );

            if ( !SimNativeLib.isPaused() && mControls != null )
            {
                mControls.update( timeStep );

                SimNativeLib.setControls( mControls.getTrigger(),
                                          mControls.getCtrlRoll(),
                                          mControls.getCtrlPitch(),
                                          mControls.getCtrlYaw(),
                                          mControls.getThrottle() );
            }
        }
    }
    
    /** Initializes simulation.  */
    public static void stop()
    {
        mInited = false;
        mUpdate = false;
    }

    /** */
    public static boolean processGenericMotionEvent( MotionEvent event )
    {
        return mControls.processGenericMotionEvent( event );
    }

    /** */
    public static boolean processKeyDownEvent( int keyCode, KeyEvent event )
    {
        return mControls.processKeyDownEvent( keyCode, event );
    }

    /** */
    public static boolean processKeyUpEvent( int keyCode, KeyEvent event )
    {
        return mControls.processKeyUpEvent( keyCode, event );
    }
    
    /** */
    public static void registerSensorEventListener( SensorManager sensorManager,
                                                    Controls controls,
                                                    Sensor accelerometer )
    {
        if ( controls instanceof SensorEventListener )
        {
            SensorEventListener sensorEventListener = (SensorEventListener)controls;

            if ( sensorEventListener != null )
            {
                sensorManager.registerListener( sensorEventListener,
                        accelerometer, SensorManager.SENSOR_DELAY_GAME );
            }
        }
    }
    
    /** */
    public static void unregisterSensorEventListener( SensorManager sensorManager,
                                                      Controls controls )
    {
        if ( controls instanceof SensorEventListener )
        {
            SensorEventListener sensorEventListener = (SensorEventListener)controls;

            if ( sensorEventListener != null )
            {
                sensorManager.unregisterListener( sensorEventListener );
            }
        }
    }
    
    /** */
    public static int getScaledWidth()
    {
        return mScaledWidth;
    }
    
    /** */
    public static int getScaledHeight()
    {
        return mScaledHeight;
    }
    
    /** */
    public static int getViewWidth()
    {
        return mViewWidth;
    }
    
    /** */
    public static int getViewHeight()
    {
        return mViewHeight;
    }
    
    /** */
    public static void setControls( Controls controls )
    {
        mControls = controls;
    }
    
    /** */
    public static void setResolution( int width, int height )
    {
        mViewWidth  = width;
        mViewHeight = height;

        mScaledWidth  = mViewWidth;
        mScaledHeight = mViewHeight;

        float w2h = (float)mViewWidth / (float)mViewHeight;

        if ( mViewWidth > MAX_WIDTH )
        {
            mScaledWidth  = MAX_WIDTH;
            mScaledHeight = (int)( (float)MAX_WIDTH / w2h );
        }
    }

    /** */
    public static void setSilent( boolean silent )
    {
        mSilent = silent;
    }
}
