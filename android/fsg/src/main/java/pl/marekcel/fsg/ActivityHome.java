package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.app.DialogFragment;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.widget.ImageView;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityHome extends ActivityBase
    implements DialogAskYesNo.DialogAbortListener
{
    public static final String LOG_TAG = "ActivityHome";

    public static final String KEY_FIRST_START = "key_activity_home_first_start";

    public class OnLogoClickListener implements View.OnClickListener
    {
        @Override
        public void onClick( View view )
        {
            long newClick = System.currentTimeMillis() / 1000;

            if ( mClickCount == 0 || mLastClick + 10 > newClick )
            {
                mLastClick = newClick;
                mClickCount++;
            }
            else
            {
                mClickCount = 0;
            }

            if ( mClickCount > 10 )
            {
                mImageViewTest.setVisibility( View.VISIBLE );
            }
        }
    }

    private ImageView mImageViewConf = null;    ///<
    private ImageView mImageViewExit = null;    ///<
    private ImageView mImageViewLogo = null;    ///<
    private ImageView mImageViewTest = null;    ///<

    private int mClickCount = 0;                ///<
    private long mLastClick = 0;                ///<

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        setContentView( R.layout.activity_home);

        mImageViewConf = (ImageView)findViewById( R.id.activity_home_img_conf );
        mImageViewExit = (ImageView)findViewById( R.id.activity_home_img_exit );
        mImageViewLogo = (ImageView)findViewById( R.id.activity_home_img_logo );
        mImageViewTest = (ImageView)findViewById( R.id.activity_home_img_test );

        mImageViewConf.setOnClickListener( new View.OnClickListener()
        {
            @Override
            public void onClick( View view )
            {
                Intent intent = new Intent( ActivityHome.this, ActivitySettings.class );
                startActivity( intent );
            }
        } );

        mImageViewExit.setOnClickListener( new View.OnClickListener()
        {
            @Override
            public void onClick( View view )
            {
                onBackPressed();
            }
        } );

        if ( CommonData.TEST_ENABLED )
        {
            mImageViewLogo.setOnClickListener( new OnLogoClickListener() );
            mImageViewTest.setOnClickListener( new View.OnClickListener()
            {
                @Override
                public void onClick( View view )
                {
                    Intent intent = new Intent( ActivityHome.this, ActivityTest.class );
                    startActivity( intent );
                }
            } );
        }

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences( this );

        if ( sharedPreferences.getBoolean( KEY_FIRST_START, true ) )
        {
            SharedPreferences.Editor editor = sharedPreferences.edit();

            editor.putBoolean( KEY_FIRST_START, false );
            editor.apply();

            DialogAskYesNo dialog = new DialogAskYesNo();
            dialog.setListener( this );
            dialog.setQuestion(  getString( R.string.do_you_want_to_start_tutorial )  );
            dialog.show( getFragmentManager(), null );
        }
    }

    @Override
    protected void onResume()
    {
        /////////////////
        super.onResume();
        /////////////////
    }

    /** */
    @Override
    public void onBackPressed()
    {
        moveTaskToBack( true );
    }

    /** */
    @Override
    public void onDialogPositiveClick( DialogFragment dialog )
    {
        startTutorial();
    }

    /** */
    @Override
    public void onDialogNegativeClick( DialogFragment dialog ) {}

    /** */
    public void onButtonTutorialClicked( View view )
    {
        startTutorial();
    }

    /** */
    public void onButtonCampaignClicked( View view )
    {
        Intent intent = new Intent( this, ActivityCampaign.class );
        startActivity( intent );
    }

    /** */
    public void onButtonQuickActionClicked( View view )
    {
        Intent intent = new Intent( this, ActivityQuickAction.class );
        startActivity( intent );
    }

    /** */
    public void onButtonEncyclopediaClicked( View view )
    {
        Intent intent = new Intent( this, ActivityEncyclopedia.class );
        startActivity( intent );
    }

    /** */
    private void startTutorial()
    {
        SimNativeLib.destroy();
        Simulation.setup( 0 );

        Intent intent = new Intent( this, ActivitySimulation.class );
        startActivityForResult( intent, 0 );
    }
}
