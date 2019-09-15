package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.app.DialogFragment;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.WindowManager;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivitySimulation extends ActivityBase
    implements DialogAskYesNo.DialogAbortListener, ViewSimulation.OnFinishedListener
{
    public static final String LOG_TAG = "ActivitySimulation";

    public static final String ARG_SIM_STATUS = "status";   ///<

    private Sensor mAccelerometer = null;                   ///<
    private SensorManager mSensorManager = null;            ///<

    private ViewSimulation mViewEGL = null;                 ///<

    private Controls mControls = null;                      ///<
    private Settings mSettings = null;                      ///<

    private boolean mSummarizing = false;                   ///<

    /** This function is called on activity created. */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        getWindow().addFlags( WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON );

        mSensorManager = (SensorManager)getSystemService( SENSOR_SERVICE );
        mAccelerometer = mSensorManager.getDefaultSensor( Sensor.TYPE_ACCELEROMETER );

        mSettings = new Settings( this );

        if ( ControlsGamepad.isGamepadConnected() && !mSettings.getNoController() )
        {
            mControls = new ControlsGamepad();
        }
        else
        {
            mControls = new ControlsSensors();
        }
        
        if ( mSettings.getInvertPitch() )
        {
            mControls.setPitchCoef( -1.0f );
        }
        
        Simulation.setControls( mControls );
        Simulation.setSilent( mSettings.getSilentMode() );
        
        setContentView( R.layout.activity_simulation );

        mViewEGL = ( ViewSimulation )findViewById( R.id.activity_simulation_view_egl );
        mViewEGL.setFocusable( true );
        mViewEGL.setFocusableInTouchMode( true );
        mViewEGL.setOnTouchListener( mControls );
        mViewEGL.setOnFinishedListener( this );
    }

    /** This function is called on activity resumed. */
    @Override
    protected void onResume()
    {
        /////////////////
        super.onResume();
        /////////////////

        mSummarizing = false;

        mViewEGL.onResume();
        SimNativeLib.restart();
        Simulation.registerSensorEventListener( mSensorManager, mControls, mAccelerometer );
    }

    /** This function is called on activity paused. */
    @Override
    protected void onPause()
    {
        ////////////////
        super.onPause();
        ////////////////

        mViewEGL.onPause();
        SimNativeLib.pause();
        Simulation.unregisterSensorEventListener( mSensorManager, mControls );

        if ( !mSummarizing ) moveTaskToBack( true );
    }

    /** This function is called on back button pressed. */
    @Override
    public void onBackPressed()
    {
        SimNativeLib.pause();
        showDialogAskYesNo();
    }

    /** */
    @Override
    public void onDialogPositiveClick( DialogFragment dialog )
    {
        summarize();
    }

    /** */
    @Override
    public void onDialogNegativeClick( DialogFragment dialog ) {}

    /** */
    @Override
    public boolean dispatchGenericMotionEvent( MotionEvent event )
    {
        /////////////////////////////////////////////////
        return super.dispatchGenericMotionEvent( event );
        /////////////////////////////////////////////////
    }

    /** */
    public void showDialogAskYesNo()
    {
        DialogAskYesNo dialog = new DialogAskYesNo();
        dialog.setListener( this );
        dialog.setQuestion(  getString( R.string.do_you_want_to_abort )  );
        dialog.show( getFragmentManager(), null );
    }

    /** */
    public void summarize()
    {
        mSummarizing = true;

        Simulation.stop();

        int status = Simulation.STATUS_FAILURE;

        if ( SimNativeLib.getStatus() == Simulation.STATUS_SUCCESS )
        {
            status = Simulation.STATUS_SUCCESS;
        }

        Intent intent = new Intent();
        intent.putExtra( ARG_SIM_STATUS, status );
        setResult( RESULT_OK, intent );

        finish();
    }
}
