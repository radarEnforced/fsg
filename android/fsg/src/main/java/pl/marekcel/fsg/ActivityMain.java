package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityMain extends ActivityBase
{
    public static final String LOG_TAG = "ActivityMain";
    public static final int CODE_DOWNLOAD_STATUS = 1;

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        initCommonData();
    }

    /** */
    @Override
    protected void onResume()
    {
        /////////////////
        super.onResume();
        /////////////////

        checkExpansionFile();
    }

    /** */
    @Override
    public void onRequestPermissionsResult( int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults )
    {
        ///////////////////////////////////////////////////////////////////////////
        super.onRequestPermissionsResult( requestCode, permissions, grantResults );
        ///////////////////////////////////////////////////////////////////////////

        checkExpansionFile();
    }

    /** */
    protected void initCommonData() {}

    /** */
    protected void requestPermissions()
    {
        ActivityCompat.requestPermissions( this, PERMISSIONS, REQUEST_PERMISSIONS );
    }

    /** */
    protected void checkExpansionFile()
    {
        if ( isPermissionsGranted() )
        {
            if ( ExpansionFile.doesMainExist( this ) || CommonData.TEST_ENABLED )
            {
                Intent intent = new Intent( this, ActivityHome.class );
                startActivity( intent );
            }
            else
            {
                Intent intent = new Intent( this, ActivityDownload.class );
                startActivityForResult( intent, CODE_DOWNLOAD_STATUS );
            }
        }
    }
}
