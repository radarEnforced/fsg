package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityMission extends ActivityInterstitial
{
    public static final String LOG_TAG = "ActivityMission";

    public static final int MODE_INTRO = 0;             ///<
    public static final int MODE_OUTRO = 1;             ///<

    public static final String ARG_INDEX  = "index";    ///<
    public static final String ARG_MODE   = "mode";     ///<
    public static final String ARG_STATUS = "status";   ///<

    public static final int CODE_SIM_STATUS = 1;        ///<

    private Campaign mCampaign = null;                  ///<

    private int mMissionIndex  = -1;                    ///<
    private int mMissionMode   = MODE_INTRO;            ///<
    private int mMissionStatus = 0;                     ///<

    private TextView mTvName = null;                    ///<
    private TextView mTvInfo = null;                    ///<

    private ImageView mImImage = null;                  ///<

    private TextView mTvTotalTime        = null;        ///<
    private TextView mTvFriendsDestroyed = null;        ///<
    private TextView mTvEnemiesDestroyed = null;        ///<
    private TextView mTvOwnshipDestroyed = null;        ///<

    private Button mBtnAction = null;                   ///<

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        setContentView( R.layout.activity_mission );

        mTvName = (TextView)findViewById( R.id.activity_mission_tv_name );
        mTvInfo = (TextView)findViewById( R.id.activity_mission_tv_introduction );

        mImImage = (ImageView)findViewById( R.id.activity_mission_img_image );

        mTvTotalTime        = (TextView)findViewById( R.id.activity_mission_tv_total_time );
        mTvFriendsDestroyed = (TextView)findViewById( R.id.activity_mission_tv_friends_destroyed );
        mTvEnemiesDestroyed = (TextView)findViewById( R.id.activity_mission_tv_enemies_destroyed );
        mTvOwnshipDestroyed = (TextView)findViewById( R.id.activity_mission_tv_ownship_destroyed );

        mBtnAction = (Button)findViewById( R.id.activity_mission_btn_action );

        mCampaign = new Campaign( this );

        mMissionIndex = getIntent().getIntExtra( ARG_INDEX, 0 );

        if ( savedInstanceState != null )
        {
            if ( savedInstanceState.containsKey( ARG_MODE ) )
            {
                mMissionMode = savedInstanceState.getInt( ARG_MODE );
            }

            if ( savedInstanceState.containsKey( ARG_INDEX ) )
            {
                mMissionIndex = savedInstanceState.getInt( ARG_INDEX );
            }

            if ( savedInstanceState.containsKey( ARG_STATUS ) )
            {
                mMissionStatus = savedInstanceState.getInt( ARG_STATUS );
            }
        }

        if ( mMissionMode == MODE_OUTRO )
        {
            setMissionOutro();
        }
        else
        {
            setMissionIntro();
        }
    }

    @Override
    protected void onResume()
    {
        /////////////////
        super.onResume();
        /////////////////

        if ( !isInterstitialLoadingStarted() )
        {
            loadInterstitial();
        }
    }

    @Override
    protected void onPause()
    {
        ////////////////
        super.onPause();
        ////////////////
    }

    /** */
    @Override
    protected void onActivityResult( int requestCode, int resultCode, Intent data )
    {
        ////////////////////////////////////////////////////////
        super.onActivityResult( requestCode, resultCode, data );
        ////////////////////////////////////////////////////////

        if ( requestCode == CODE_SIM_STATUS )
        {
            mMissionMode = MODE_OUTRO;
            mMissionStatus = Simulation.STATUS_FAILURE;

            if ( data != null )
            {
                mMissionStatus = data.getIntExtra( ActivitySimulation.ARG_SIM_STATUS, Simulation.STATUS_FAILURE );
            }

            if ( mMissionStatus == Simulation.STATUS_SUCCESS )
            {
                Mission mission = mCampaign.getMission( mMissionIndex );

                if ( mission != null )
                {
                    if ( !mission.isCompleted() )
                    {
                        mission.setCompleted();

                        if ( mMissionIndex < mCampaign.getMissionsCount() - 1 )
                        {
                            String message = getString( R.string.mission_mission )
                                    + " \"" + mCampaign.getMission( mMissionIndex + 1 ).getName()
                                    + "\" " + getString( R.string.mission_unlocked );
                            Toast toast = Toast.makeText( this, message, Toast.LENGTH_LONG );
                            toast.show();

                            for ( int i = 0; i < Units.getInstance().getUnitsCount(); i++ )
                            {
                                Units.Unit unitData = Units.getInstance().getUnit( i );

                                if ( unitData.mUnlockMission == mMissionIndex + 1 )
                                {
                                    Toast toast2 = Toast.makeText( this, unitData.mName.get() + " " + getString( R.string.mission_aircraft_unlocked ), Toast.LENGTH_LONG );
                                    toast2.show();
                                }
                            }
                        }
                        else
                        {
                            Toast toast = Toast.makeText( this, getString( R.string.mission_campaign_finished), Toast.LENGTH_LONG );
                            toast.show();
                        }
                    }
                }
            }
        }

        setMissionOutro();
    }

    /** */
    @Override
    public void onInterstitialClosed()
    {
        if ( !isInterstitialLoadingStarted() )
        {
            loadInterstitial();
        }

        startMission();
    }

    /** */
    @Override
    protected void onSaveInstanceState( Bundle outState )
    {
        //////////////////////////////////////
        super.onSaveInstanceState( outState );
        //////////////////////////////////////

        outState.putInt( ARG_MODE   , mMissionMode   );
        outState.putInt( ARG_INDEX  , mMissionIndex  );
        outState.putInt( ARG_STATUS , mMissionStatus );
    }

    /** */
    public void onButtonStartMissionClicked( View view )
    {
        if ( mMissionStatus == Simulation.STATUS_SUCCESS )
        {
            mMissionStatus = Simulation.STATUS_PENDING;

            if ( mMissionIndex + 1 < mCampaign.getMissionsCount() )
            {
                mMissionIndex++;
                setMissionIntro();
            }
        }
        else
        {
            if ( !mCampaign.isMissionLocked( mMissionIndex ) )
            {
                if ( isInterstitialLoaded() )
                {
                    showInterstitial();
                }
                else
                {
                    startMission();
                }
            }
            else
            {
                Toast.makeText( this, getString( R.string.mission_locked ), Toast.LENGTH_SHORT ).show();
            }
        }
    }

    /** */
    private void startMission()
    {
        SimNativeLib.destroy();
        Simulation.setup( mMissionIndex );

        Intent intent = new Intent( this, ActivitySimulation.class );
        startActivityForResult( intent, CODE_SIM_STATUS );
    }

    /** */
    private void setMissionIntro()
    {
        mImImage.setVisibility( View.VISIBLE );

        Mission mission = mCampaign.getMission( mMissionIndex );

        if ( mission != null )
        {
            mTvName.setText( mission.getName() );
            mTvInfo.setText( mission.getIntroduction() );

            String imageFilePath = mission.getImage();

            if ( mCampaign.isMissionLocked( mMissionIndex ) )
            {
                imageFilePath = mission.getImageLocked();
            }

            File imageFile = new File( DataPath.get( imageFilePath ) );

            if ( imageFile.exists() )
            {
                Bitmap bitmap = BitmapFactory.decodeFile( imageFile.getAbsolutePath() );

                if ( bitmap != null )
                {
                    mImImage.setImageBitmap( bitmap );
                }
            }
        }

        mBtnAction.setText( getString( R.string.mission_start ) );
    }

    /** */
    private void setMissionOutro()
    {
        mImImage.setVisibility( View.GONE );

        Mission mission = mCampaign.getMission( mMissionIndex );

        if ( mission != null )
        {
            mTvName.setText( mission.getName().toUpperCase() );

            if ( mMissionStatus == Simulation.STATUS_SUCCESS )
            {
                mTvInfo.setText( mission.getSummarySuccess() );

                if ( mMissionIndex + 1 < mCampaign.getMissionsCount() )
                {
                    mBtnAction.setText( getString( R.string.mission_proceed ) );
                }
                else
                {
                    mBtnAction.setText( getString( R.string.mission_restart ) );
                }
            }
            else
            {
                mTvInfo.setText( mission.getSummaryFailure() );
                mBtnAction.setText( getString( R.string.mission_restart ) );
            }

            int min = SimNativeLib.getFlightTime() / 60;
            int sec = SimNativeLib.getFlightTime() - 60 * min;

            mTvTotalTime.setText( getString( R.string.mission_summary_time ) + " " + String.format( "%02d", min ) + ":" + String.format( "%02d", sec ) );
            mTvFriendsDestroyed.setText( getString( R.string.mission_summary_friends_destroyed ) + " " + String.valueOf( SimNativeLib.getFriendsDestroyed() )
                    + " " + getString( R.string.of ) + " "
                    + String.valueOf( SimNativeLib.getFriendsActivated() ) );
            mTvEnemiesDestroyed.setText( getString( R.string.mission_summary_enemies_destroyed ) + " " + String.valueOf( SimNativeLib.getEnemiesDestroyed() )
                    + " " + getString( R.string.of ) + " "
                    + String.valueOf( SimNativeLib.getEnemiesActivated() ) );
            mTvOwnshipDestroyed.setText( getString( R.string.mission_summary_ownship_destroyed ) + " " + String.valueOf( SimNativeLib.getOwnshipDestroyed() ) );
        }
    }
}
