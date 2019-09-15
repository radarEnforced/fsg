package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;

////////////////////////////////////////////////////////////////////////////////

/** Controls base class. */
public class Controls
    implements View.OnTouchListener
{
    public static final String LOG_TAG = "Controls";

    public static final int GENERIC = 0;    ///<
    public static final int SENSORS = 1;    ///<
    public static final int GAMEPAD = 2;    ///<
    
    protected int mType = GENERIC;          ///<
    
    protected float mCtrlRoll  = 0.0f;      ///<
    protected float mCtrlPitch = 0.0f;      ///<
    protected float mCtrlYaw   = 0.0f;      ///<

    protected float mThrottle = 0.5f;       ///<

    protected boolean mTrigger = false;     ///<

    protected boolean mInited = false;      ///<
    
    protected float mPitchCoef = 1.0f;      ///< pitch controls scaling coefficient
    
    /** */
    public void update( double timeStep ) {}

    /** */
    public boolean onTouch( View v, MotionEvent event )
    {
        int action = event.getAction() & MotionEvent.ACTION_MASK;

        if ( SimNativeLib.isPaused() )
        {
            if ( action == MotionEvent.ACTION_DOWN )
            {
                if ( !mInited )
                {
                    mInited = true;
                    mThrottle = SimNativeLib.getInitThrottle();
                }

                SimNativeLib.unpause();
            }
        }

        return true;
    }

    /** */
    public boolean processGenericMotionEvent( MotionEvent event )
    {
        return false;
    }

    /** */
    public boolean processKeyDownEvent( int keyCode, KeyEvent event )
    {
        return false;
    }

    /** */
    public boolean processKeyUpEvent( int keyCode, KeyEvent event )
    {
        return false;
    }
    
    public float getCtrlRoll()  { return mCtrlRoll;  }
    public float getCtrlPitch() { return mCtrlPitch * mPitchCoef; }
    public float getCtrlYaw()   { return mCtrlYaw;   }

    public float getThrottle() { return mThrottle; }

    public boolean getTrigger() { return mTrigger; }
    
    public int getType() { return mType; }

    /** */
    public void setPitchCoef( float pitchCoef )
    {
        mPitchCoef = pitchCoef;
    }
}
