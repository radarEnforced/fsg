package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityTest extends ActivityBase
{
    public static final String LOG_TAG = "ActivityTest";

    private Campaign mCampaign = null;

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        mCampaign = new Campaign( this );

        setContentView( R.layout.activity_test );
    }

    /** */
    public void onButtonUnlockOneClicked( View view )
    {
        for ( int i = 0; i < mCampaign.getMissionsCount(); i++ )
        {
            Mission mission = mCampaign.getMission( i );

            if ( mission != null )
            {
                if ( !mission.isCompleted() )
                {
                    mission.setCompleted();

                    Toast toast = Toast.makeText( this, "Mission " + String.valueOf( i ) + " unlocked.", Toast.LENGTH_SHORT );
                    toast.show();

                    break;
                }
            }
        }
    }

    /** */
    public void onButtonLockClicked( View view )
    {
        mCampaign.setCompletedMissions( 1 );

        Toast toast = Toast.makeText( this, "All missions locked.", Toast.LENGTH_LONG );
        toast.show();
    }

    /** */
    public void onButtonUnlockClicked( View view )
    {
        for ( int i = 0; i < mCampaign.getMissionsCount(); i++ )
        {
            Mission mission = mCampaign.getMission( i );

            if ( mission != null )
            {
                mission.setCompleted();
            }
        }

        Toast toast = Toast.makeText( this, "All missions unlocked.", Toast.LENGTH_LONG );
        toast.show();
    }
}
