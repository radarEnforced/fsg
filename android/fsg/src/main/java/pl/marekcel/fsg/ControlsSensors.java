package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.os.SystemClock;
import android.view.MotionEvent;
import android.view.View;

////////////////////////////////////////////////////////////////////////////////

/** Sensor controls class. */
public class ControlsSensors extends Controls
    implements SensorEventListener
{
    public static final String LOG_TAG = "ControlsSensors";

    private static final float mMaxRoll  = (float)Math.toRadians( 30.0f );
    private static final float mMaxPitch = (float)Math.toRadians( 30.0f );

    private float mRawRoll  = 0.0f;                 ///<
    private float mRawPitch = 0.0f;                 ///<

    private float mPitchOffset = 0.0f;              ///<

    private int mIndexThrottle = -1;                ///<
    private int mIndexTrigger  = -1;                ///<

    private int mCenterX = 0;                       ///< [px] view center x coordinate
    private int mCenterY = 0;                       ///< [px] view center y coordinate

    private int mThrottleX  = 0;                    ///< [px]
    private int mThrottleW2 = 0;                    ///< [px]
    private int mThrottleH2 = 0;                    ///< [px]
    private int mThrottleDY = 0;                    ///< [px]
    private int mThrottleMY = 0;                    ///< [px]

    private int mTriggerX  = 0;                     ///< [px]
    private int mTriggerY  = 0;                     ///< [px]
    private int mTriggerR  = 0;                     ///< [px]
    private int mTriggerR2 = 0;                     ///< [px]

    private boolean mResInited = false;             ///<

    private long mTimeNew = 0;                      ///<
    private long mTimeOld = 0;                      ///<

    private double mTimeStep = 0.0;                 ///< [s]

    /** Constructor. */
    public ControlsSensors()
    {
        ////////
        super();
        ////////
        
        mType = SENSORS;
    }

    /** */
    public void onAccuracyChanged( Sensor sensor, int accuracy ) {}

    /** */
    public void onSensorChanged( SensorEvent event )
    {
        if ( event.sensor.getType() == Sensor.TYPE_ACCELEROMETER )
        {
            float accX = event.values[ 0 ];
            float accY = event.values[ 1 ];
            float accZ = event.values[ 2 ];

            float accXY = (float) Math.sqrt( accX * accX + accY * accY ) * Math.signum( accX );
            float accXZ = (float) Math.sqrt( accX * accX + accZ * accZ );

            mRawRoll  = (float) Math.atan2(  accY, accXZ );
            mRawPitch = (float) Math.atan2( -accZ, accXY );

            if ( !mInited )
            {
                mTimeNew  = SystemClock.uptimeMillis();
                mTimeStep = (double)( mTimeNew - mTimeOld ) / 1000.0;
                mTimeOld  = mTimeNew;

                mPitchOffset = (float)( mPitchOffset + ( 1.0 - Math.exp( -mTimeStep / 0.1 ) ) * ( mRawPitch - mPitchOffset ) );
            }

            mRawPitch -= mPitchOffset;

            mCtrlRoll  = mRawRoll  / mMaxRoll;
            mCtrlPitch = mRawPitch / mMaxPitch;

            if ( mCtrlRoll < -1.0f ) mCtrlRoll = -1.0f;
            if ( mCtrlRoll >  1.0f ) mCtrlRoll =  1.0f;

            if ( mCtrlPitch < -1.0f ) mCtrlPitch = -1.0f;
            if ( mCtrlPitch >  1.0f ) mCtrlPitch =  1.0f;
        }
    }

    /**
     *
     * @param view
     * @param event
     * @return True if the event was handled, false otherwise.
     */
    @Override
    public boolean onTouch( View view, MotionEvent event )
    {
        int action = event.getAction() & MotionEvent.ACTION_MASK;
        int points = event.getPointerCount();

        for ( int i = 0; i < points; i++ )
        {
            if ( mInited && !SimNativeLib.isPaused() )
            {
                if ( SimNativeLib.isPending() )
                {
                    if ( action == MotionEvent.ACTION_DOWN || action == MotionEvent.ACTION_POINTER_DOWN )
                    {
                        int eventX = (int) event.getX( i );
                        int eventY = (int) event.getY( i );

                        if ( eventX > mCenterX )
                        {
                            int deltaX = eventX - mTriggerX;
                            int deltaY = eventY - mTriggerY;

                            int r2 = deltaX * deltaX + deltaY * deltaY;

                            if ( r2 < mTriggerR2 )
                            {
                                mTrigger = true;
                                mIndexTrigger = i;
                            }
                        }
                        else
                        {
                            int throttleY = (int)( (0.5f - mThrottle) * mThrottleMY  + mCenterY - mThrottleDY );

                            int deltaX = eventX - mThrottleX;
                            int deltaY = eventY - throttleY;

                            if ( Math.abs(deltaX) < mThrottleW2  && Math.abs(deltaY) < mThrottleH2 )
                            {
                                mIndexThrottle = i;
                            }
                        }
                    }
                    else if ( action == MotionEvent.ACTION_MOVE )
                    {
                        int eventX = (int) event.getX( i );
                        int eventY = (int) event.getY( i );

                        if ( eventX > mCenterX )
                        {
                            int deltaX = eventX - mTriggerX;
                            int deltaY = eventY - mTriggerY;

                            int r2 = deltaX * deltaX + deltaY * deltaY;

                            if ( r2 < mTriggerR2 )
                            {
                                mTrigger = true;
                                mIndexTrigger = i;
                            }
                            else
                            {
                                if ( i == mIndexTrigger )
                                {
                                    mTrigger = false;
                                    mIndexTrigger = -1;
                                }
                            }
                        }
                        else
                        {
                            int deltaX = eventX - mThrottleX;

                            if ( deltaX < mThrottleW2 )
                            {
                                mThrottle = 0.5f - (float)( eventY - mCenterY  + mThrottleDY ) / (float)mThrottleMY;

                                if ( mThrottle < 0.0f ) mThrottle = 0.0f;
                                if ( mThrottle > 1.0f ) mThrottle = 1.0f;

                                mIndexThrottle = i;
                            }
                            else
                            {
                                if ( i == mIndexThrottle )
                                {
                                    mIndexThrottle = -1;
                                }
                            }
                        }
                    }
                    else if ( action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_POINTER_UP )
                    {
                        if ( i == mIndexTrigger )
                        {
                            mTrigger = false;
                            mIndexTrigger = -1;
                        }
                        else if ( i == mIndexThrottle )
                        {
                            mIndexThrottle = -1;
                        }
                    }
                }
                else
                {
                    mTrigger = false;

                    mIndexThrottle = -1;
                    mIndexTrigger  = -1;
                }
            }
            else
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
        }

        return true;
    }

    /** */
    public void setResolution( int w, int h )
    {
        if ( !mResInited )
        {
            float w2h = (float) w / (float) h;

            float throttleX = 100 * w2h - 30.0f;
            float triggerX  = 100 * w2h - 30.0f;

            mCenterX = w / 2;
            mCenterY = h / 2;

            float coef = (float) h / 200.0f;

            mThrottleX  = (int) ( -throttleX * coef ) + mCenterX;
            mThrottleW2 = (int) (  20.0f * coef );
            mThrottleH2 = (int) (  10.0f * coef );
            mThrottleDY = (int) (  10.0f * coef );
            mThrottleMY = (int) ( 100.0f * coef );

            mTriggerX  = (int) ( triggerX * coef ) + mCenterX;
            mTriggerY  = (int) (  0.0f * coef ) + mCenterY;
            mTriggerR  = (int) ( 25.0f * coef );
            mTriggerR2 = mTriggerR * mTriggerR;

            mResInited = true;
        }
    }
}
