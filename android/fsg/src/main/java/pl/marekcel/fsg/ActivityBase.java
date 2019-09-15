package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.storage.OnObbStateChangeListener;
import android.os.storage.StorageManager;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.WindowManager;

import com.google.android.vending.expansion.downloader.Helpers;

import java.io.File;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityBase extends AppCompatActivity
{
    public static final String LOG_TAG = "ActivityBase";

    /**
     * This is a little helper class that demonstrates simple testing of an
     * Expansion APK file delivered by Market. You may not wish to hard-code
     * things such as file lengths into your executable... and you may wish to
     * turn this code off during application development.
     */
    protected static class ExpansionFileData
    {
        public final boolean mMain;
        public final int mVersion;
        public final long mSize;

        ExpansionFileData( boolean main, int version, long size )
        {
            mMain    = main;
            mVersion = version;
            mSize    = size;
        }
    }

    /**
     * Here is where you place the data that the validator will use to determine
     * if the file was delivered correctly. This is encoded in the source code
     * so the application can easily determine whether the file has been
     * properly delivered without having to talk to the server. If the
     * application is using LVL for licensing, it may make sense to eliminate
     * these checks and to just rely on the server.
     */
    protected static final ExpansionFileData[] EXPANSION_FILES_DATA =
    {
        new ExpansionFileData(
            true,
            CommonData.mExpansionFileMainVersion,
            CommonData.mExpansionFileMainSize
        )
    };

    protected File mExpansionFile = null;                       ///<

    protected StorageManager      mStorageManager      = null;  ///<
    protected StateChangeListener mStateChangeListener = null;  ///<

    protected static final int REQUEST_PERMISSIONS = 0;         ///< Id to identify a permission request

    /** */
    protected static String[] PERMISSIONS =
    {
        Manifest.permission.MODIFY_AUDIO_SETTINGS,
        Manifest.permission.READ_EXTERNAL_STORAGE,
        Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        mStorageManager      = (StorageManager)getSystemService( STORAGE_SERVICE );
        mStateChangeListener = new StateChangeListener();
    }

    /** */
    @Override
    protected void onResume()
    {
        /////////////////
        super.onResume();
        /////////////////

        getWindow().setFlags( WindowManager.LayoutParams.FLAG_FULLSCREEN,
                              WindowManager.LayoutParams.FLAG_FULLSCREEN );

        getWindow().getDecorView().setSystemUiVisibility( View.SYSTEM_UI_FLAG_FULLSCREEN
                                                        | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                                                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                                                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                                                        | View.SYSTEM_UI_FLAG_LAYOUT_STABLE );

        mountExpansionFile();
        setLanguage();
    }

    /** */
    @Override
    public void onWindowFocusChanged( boolean hasFocus )
    {
        ///////////////////////////////////////
        super.onWindowFocusChanged( hasFocus );
        ///////////////////////////////////////

        getWindow().getDecorView().setSystemUiVisibility( View.SYSTEM_UI_FLAG_FULLSCREEN
                                                        | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                                                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                                                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                                                        | View.SYSTEM_UI_FLAG_LAYOUT_STABLE );
    }

    /**
     * Go through each of the APK Expansion files defined in the structure above
     * and determine if the files are present and match the required size. Free
     * applications should definitely consider doing this, as this allows the
     * application to be launched for the first time without having a network
     * connection present. Paid applications that use LVL should probably do at
     * least one LVL check that requires the network to be present, so this is
     * not as necessary.
     *
     * @return true if they are present.
     */
    protected boolean isExpansionFilesDelivered()
    {
        for ( ExpansionFileData xf : EXPANSION_FILES_DATA )
        {
            String fileName = Helpers.getExpansionAPKFileName( this, xf.mMain, xf.mVersion );

            if ( !Helpers.doesFileExist( this, fileName, xf.mSize, false ) )
            {
                return false;
            }
        }

        return true;
    }

    /** */
    protected void mountExpansionFile()
    {
        if ( mStorageManager != null )
        {
            File obbFile = new File( ExpansionFile.getMainFullPath( this ) );

            if ( obbFile.exists() )
            {
                if ( !mStorageManager.isObbMounted( obbFile.getAbsolutePath() ) )
                {
                    mStorageManager.mountObb( obbFile.getAbsolutePath(), null, mStateChangeListener );
                }
                else
                {
                    if ( !DataPath.isInited() )
                    {
                        String mountedFilePath = mStorageManager.getMountedObbPath( obbFile.getAbsolutePath() );

                        if ( mountedFilePath.length() > 0 )
                        {
                            mExpansionFile = new File( mountedFilePath );
                            DataPath.setBasePath( mExpansionFile.getAbsolutePath() + File.separator );

                            setLanguage();
                        }
                    }
                }
            }
        }
    }

    /** */
    protected boolean isPermissionsGranted()
    {
        return
            ( ContextCompat.checkSelfPermission( this, Manifest.permission.MODIFY_AUDIO_SETTINGS )  == PackageManager.PERMISSION_GRANTED )
            &&
            ( ContextCompat.checkSelfPermission( this, Manifest.permission.READ_EXTERNAL_STORAGE )  == PackageManager.PERMISSION_GRANTED )
            &&
            ( ContextCompat.checkSelfPermission( this, Manifest.permission.WRITE_EXTERNAL_STORAGE ) == PackageManager.PERMISSION_GRANTED );
    }

    /** */
    protected void setLanguage()
    {
        if ( mExpansionFile != null )
        {
            Languages.getInstance().setCurrentByCode( getString( R.string.language_code ) );
            int currentLanguageCode = Languages.getInstance().getCurrent();
            SimNativeLib.setLanguage( currentLanguageCode );
        }
    }

    /** */
    protected class StateChangeListener extends OnObbStateChangeListener
    {
        @Override
        public void onObbStateChange( String path, int state )
        {
            //////////////////////////////////////
            super.onObbStateChange( path, state );
            //////////////////////////////////////

            if ( state == OnObbStateChangeListener.MOUNTED )
            {
                String mountedFilePath = mStorageManager.getMountedObbPath( path );

                if ( mountedFilePath.length() > 0 )
                {
                    mExpansionFile = new File( mountedFilePath );
                    DataPath.setBasePath( mExpansionFile.getAbsolutePath() + File.separator );

                    setLanguage();
                }
            }
        }
    }
}
