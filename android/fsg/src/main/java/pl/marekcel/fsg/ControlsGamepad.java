package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;

////////////////////////////////////////////////////////////////////////////////

/** Gamepad controls class. */
public class ControlsGamepad extends Controls
{
    public static final String LOG_TAG = "ControlsGamepad";

    public final int AXIS_ROLL     = MotionEvent.AXIS_X;
    public final int AXIS_PITCH    = MotionEvent.AXIS_Y;
    public final int AXIS_YAW      = MotionEvent.AXIS_Z;
    public final int AXIS_THROTTLE = MotionEvent.AXIS_RZ;

    //public final int AXIS_ROLL     = MotionEvent.AXIS_Z;
    //public final int AXIS_PITCH    = MotionEvent.AXIS_RZ;
    //public final int AXIS_YAW      = MotionEvent.AXIS_X;
    //public final int AXIS_THROTTLE = MotionEvent.AXIS_Y;

    private float mAxisRoll     = 0.0f;                     ///<
    private float mAxisPitch    = 0.0f;                     ///<
    private float mAxisYaw      = 0.0f;                     ///<
    private float mAxisThrottle = 0.0f;                     ///<
    private float mAxisTriggerR = 0.0f;                     ///<
    private float mAxisTriggerL = 0.0f;                     ///<

    private boolean mButtR1 = false;                        ///<
    private boolean mButtR2 = false;                        ///<
    private boolean mButtL1 = false;                        ///<
    private boolean mButtL2 = false;                        ///<

    public static boolean isGamepadConnected()
    {
        int[] deviceIds = InputDevice.getDeviceIds();

        for ( int deviceId : deviceIds )
        {
            int sources = InputDevice.getDevice( deviceId ).getSources();

            if ( ( ( sources & InputDevice.SOURCE_GAMEPAD ) == InputDevice.SOURCE_GAMEPAD  )
              || ( ( sources & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK ) )
            {
                return true;
            }
        }

        return false;
    }

    /** Constructor. */
    public ControlsGamepad()
    {
        ////////
        super();
        ////////
        
        mType = GAMEPAD;
    }

    /** */
    @Override
    public void update( double timeStep )
    {
        mTrigger = false;

        if ( !SimNativeLib.isPaused() && SimNativeLib.isPending() )
        {
            //mCtrlRoll  = mCtrlRoll  + (float)timeStep * mAxisRoll;
            //mCtrlPitch = mCtrlPitch + (float)timeStep * mAxisPitch;
            //mCtrlYaw   = mCtrlYaw   + (float)timeStep * mAxisYaw;
            mCtrlRoll  = mAxisRoll;
            mCtrlPitch = mAxisPitch;
            mCtrlYaw   = mAxisYaw;
            mThrottle  = mThrottle  - (float)timeStep * mAxisThrottle;

            mCtrlRoll  = (float)Math.min( Math.max( mCtrlRoll  , -1.0 ), 1.0 );
            mCtrlPitch = (float)Math.min( Math.max( mCtrlPitch , -1.0 ), 1.0 );
            mCtrlYaw   = (float)Math.min( Math.max( mCtrlYaw   , -1.0 ), 1.0 );
            mThrottle  = (float)Math.min( Math.max( mThrottle  ,  0.0 ), 1.0 );

            if ( mButtR1 || mButtR2 || mAxisTriggerR > 0.5f )
            {
                mTrigger = true;
            }
        }
    }

    /**
     * @param event
     * @return True if the event was handled, false otherwise.
     */
    @Override
    public boolean processGenericMotionEvent( MotionEvent event )
    {
        if ( event.getAction() == MotionEvent.ACTION_MOVE
          || event.getAction() == MotionEvent.ACTION_HOVER_MOVE )
        {
            int eventSource = event.getSource();

            if ( ( eventSource & InputDevice.SOURCE_GAMEPAD  ) == InputDevice.SOURCE_GAMEPAD
              || ( eventSource & InputDevice.SOURCE_JOYSTICK ) == InputDevice.SOURCE_JOYSTICK )
            {
                int deviceId = event.getDeviceId();

                if ( deviceId != -1 )
                {
                    mAxisRoll     = event.getAxisValue( AXIS_ROLL  );
                    mAxisPitch    = event.getAxisValue( AXIS_PITCH );
                    mAxisYaw      = event.getAxisValue( AXIS_YAW   );
                    mAxisThrottle = event.getAxisValue( AXIS_THROTTLE );
                    mAxisTriggerR = event.getAxisValue( MotionEvent.AXIS_RTRIGGER );
                    mAxisTriggerL = event.getAxisValue( MotionEvent.AXIS_LTRIGGER );

                    //float axisBrake    = event.getAxisValue( MotionEvent.AXIS_BRAKE );
                    //float axisGas      = event.getAxisValue( MotionEvent.AXIS_GAS );
                    //float axisThrottle = event.getAxisValue( MotionEvent.AXIS_THROTTLE );

                    //if ( axisGas      > mAxisTriggerR ) mAxisTriggerR = axisGas;
                    //if ( axisThrottle > mAxisTriggerR ) mAxisTriggerR = axisThrottle;
                    //if ( axisBrake    > mAxisTriggerL ) mAxisTriggerL = axisBrake;

                    return true;
                }
            }
        }

        return false;
    }

    /**
     * @param keyCode
     * @param event
     * @return True if the event was handled, false otherwise.
     */
    @Override
    public boolean processKeyDownEvent( int keyCode, KeyEvent event )
    {
        int eventSource = event.getSource();

        if ( ( eventSource & InputDevice.SOURCE_GAMEPAD ) == InputDevice.SOURCE_GAMEPAD )
        {
            if ( !SimNativeLib.isPaused() )
            {
                int deviceId = event.getDeviceId();

                if ( deviceId != -1 )
                {
                    if ( keyCode == KeyEvent.KEYCODE_BUTTON_R1
                      || keyCode == KeyEvent.KEYCODE_BUTTON_R2
                      || keyCode == KeyEvent.KEYCODE_BUTTON_L1
                      || keyCode == KeyEvent.KEYCODE_BUTTON_L2 )
                    {
                        mButtR1 = mButtR1 || ( keyCode == KeyEvent.KEYCODE_BUTTON_R1 );
                        mButtR2 = mButtR2 || ( keyCode == KeyEvent.KEYCODE_BUTTON_R2 );
                        mButtL1 = mButtL1 || ( keyCode == KeyEvent.KEYCODE_BUTTON_L1 );
                        mButtL2 = mButtL2 || ( keyCode == KeyEvent.KEYCODE_BUTTON_L2 );

                        return true;
                    }
                }
            }
            else
            {
                SimNativeLib.unpause();

                return true;
            }
        }

        return false;
    }

    /**
     * @param keyCode
     * @param event
     * @return True if the event was handled, false otherwise.
     */
    @Override
    public boolean processKeyUpEvent( int keyCode, KeyEvent event )
    {
        int eventSource = event.getSource();

        if ( ( eventSource & InputDevice.SOURCE_GAMEPAD  ) == InputDevice.SOURCE_GAMEPAD )
        {
            int deviceId = event.getDeviceId();

            if ( deviceId != -1 )
            {
                if ( keyCode == KeyEvent.KEYCODE_BUTTON_R1
                  || keyCode == KeyEvent.KEYCODE_BUTTON_R2
                  || keyCode == KeyEvent.KEYCODE_BUTTON_L1
                  || keyCode == KeyEvent.KEYCODE_BUTTON_L2 )
                {
                    mButtR1 = mButtR1 && !( keyCode == KeyEvent.KEYCODE_BUTTON_R1 );
                    mButtR2 = mButtR2 && !( keyCode == KeyEvent.KEYCODE_BUTTON_R2 );
                    mButtL1 = mButtL1 && !( keyCode == KeyEvent.KEYCODE_BUTTON_L1 );
                    mButtL2 = mButtL2 && !( keyCode == KeyEvent.KEYCODE_BUTTON_L2 );

                    return true;
                }
            }
        }

        return false;
    }
}
