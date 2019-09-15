package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.app.PendingIntent;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Messenger;
import android.util.Log;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.google.android.vending.expansion.downloader.DownloadProgressInfo;
import com.google.android.vending.expansion.downloader.DownloaderClientMarshaller;
import com.google.android.vending.expansion.downloader.DownloaderServiceMarshaller;
import com.google.android.vending.expansion.downloader.Helpers;
import com.google.android.vending.expansion.downloader.IDownloaderClient;
import com.google.android.vending.expansion.downloader.IDownloaderService;
import com.google.android.vending.expansion.downloader.IStub;

////////////////////////////////////////////////////////////////////////////////

/**
 * This is sample code for a project built against the downloader library. It
 * implements the IDownloaderClient that the client marshaler will talk to as
 * messages are delivered from the DownloaderService.
 */
public class ActivityDownload extends ActivityBase
    implements IDownloaderClient
{
    public static final String LOG_TAG = "ActivityDownload";

    private ProgressBar mProgressBar = null;    ///<

    private TextView mTvPercentage = null;      ///<
    private TextView mTvStatusText = null;      ///<

    private int mState;                         ///<

    private IDownloaderService mRemoteService;  ///<
    private IStub mDownloaderClientStub;        ///<

    /**
     * Called when the activity is first create; we wouldn't create a layout in
     * the case where we have the file and are moving to another activity
     * without downloading.
     */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        mDownloaderClientStub = DownloaderClientMarshaller.CreateStub(this, ServiceDownloader.class );

        setContentView( R.layout.activity_download );

        mProgressBar = (ProgressBar)findViewById( R.id.activity_download_progressBar );

        mTvPercentage = (TextView)findViewById( R.id.activity_download_percentage );
        mTvStatusText = (TextView)findViewById( R.id.activity_download_status );

        init();
    }

    /**
     * Connect the stub to our service on start.
     */
    @Override
    protected void onStart()
    {
        if ( mDownloaderClientStub != null )
        {
            mDownloaderClientStub.connect( this );
        }

        ////////////////
        super.onStart();
        ////////////////
    }

    /**
     * Disconnect the stub from our service on stop
     */
    @Override
    protected void onStop()
    {
        if ( mDownloaderClientStub != null )
        {
            mDownloaderClientStub.disconnect( this );
        }

        ///////////////
        super.onStop();
        ///////////////
    }

    /** */
    @Override
    protected void onDestroy()
    {
        //////////////////
        super.onDestroy();
        //////////////////
    }

    /**
     * Critical implementation detail. In onServiceConnected we create the
     * remote service and marshaler. This is how we pass the client information
     * back to the service so the client can be properly notified of changes. We
     * must do this every time we reconnect to the service.
     */
    @Override
    public void onServiceConnected( Messenger m )
    {
        mRemoteService = DownloaderServiceMarshaller.CreateProxy( m );
        mRemoteService.onClientUpdated( mDownloaderClientStub.getMessenger() );
    }

    /**
     * The download state should trigger changes in the UI --- it may be useful
     * to show the state as being indeterminate at times. This sample can be
     * considered a guideline.
     */
    @Override
    public void onDownloadStateChanged( int newState )
    {
        setState( newState );

        boolean indeterminate;

        switch ( newState )
        {
            case IDownloaderClient.STATE_IDLE:
                // STATE_IDLE means the service is listening, so it's
                // safe to start making calls via mRemoteService.
                indeterminate = true;
                break;
            case IDownloaderClient.STATE_CONNECTING:
            case IDownloaderClient.STATE_FETCHING_URL:
                indeterminate = true;
                break;
            case IDownloaderClient.STATE_DOWNLOADING:
                indeterminate = false;
                break;

            case IDownloaderClient.STATE_FAILED_CANCELED:
            case IDownloaderClient.STATE_FAILED:
            case IDownloaderClient.STATE_FAILED_FETCHING_URL:
            case IDownloaderClient.STATE_FAILED_UNLICENSED:
                indeterminate = false;
                break;

            case IDownloaderClient.STATE_PAUSED_NEED_CELLULAR_PERMISSION:
            case IDownloaderClient.STATE_PAUSED_WIFI_DISABLED_NEED_CELLULAR_PERMISSION:
                indeterminate = false;
                break;

            case IDownloaderClient.STATE_PAUSED_BY_REQUEST:
                indeterminate = false;
                break;

            case IDownloaderClient.STATE_PAUSED_ROAMING:
            case IDownloaderClient.STATE_PAUSED_SDCARD_UNAVAILABLE:
                indeterminate = false;
                break;

            case IDownloaderClient.STATE_COMPLETED:
                indeterminate = false;
                validate();
                return;

            default:
                indeterminate = true;
        }

        mProgressBar.setIndeterminate( indeterminate );
    }

    /**
     * Sets the state of the various controls based on the progressinfo object
     * sent from the downloader service.
     */
    @Override
    public void onDownloadProgress( DownloadProgressInfo progress )
    {
        //progress.mOverallTotal = progress.mOverallTotal;
        mProgressBar.setMax( (int) (progress.mOverallTotal >> 8) );
        mProgressBar.setProgress( (int) (progress.mOverallProgress >> 8) );

        mTvPercentage.setText(Long.toString(progress.mOverallProgress
                * 100 / progress.mOverallTotal) + "%");
    }

    protected void setState( int newState )
    {
        if ( mState != newState )
        {
            mState = newState;
            mTvStatusText.setText( Helpers.getDownloaderStringResourceIDFromState( newState ) );
        }
    }

    protected void init()
    {
        /**
         * Before we do anything, are the files we expect already here and
         * delivered (presumably by Market) For free titles, this is probably
         * worth doing. (so no Market request is necessary)
         */
        if ( !isExpansionFilesDelivered() )
        {
            try
            {
                Intent launchIntent = ActivityDownload.this.getIntent();

                Intent intentToLaunchThisActivityFromNotification = new Intent( ActivityDownload.this,
                                                                                ActivityDownload.this.getClass() );

                intentToLaunchThisActivityFromNotification.setFlags( Intent.FLAG_ACTIVITY_NEW_TASK
                                                                   | Intent.FLAG_ACTIVITY_CLEAR_TOP );

                intentToLaunchThisActivityFromNotification.setAction( launchIntent.getAction() );

                if ( launchIntent.getCategories() != null )
                {
                    for ( String category : launchIntent.getCategories() )
                    {
                        intentToLaunchThisActivityFromNotification.addCategory( category );
                    }
                }

                // Build PendingIntent used to open this activity from
                // Notification
                PendingIntent pendingIntent = PendingIntent.getActivity(ActivityDownload.this,
                                                                        0, intentToLaunchThisActivityFromNotification,
                                                                         PendingIntent.FLAG_UPDATE_CURRENT);

                // Request to start the download
                int startResult = DownloaderClientMarshaller.startDownloadServiceIfRequired(this,
                        pendingIntent, ServiceDownloader.class);

                if ( startResult != DownloaderClientMarshaller.NO_DOWNLOAD_REQUIRED )
                {
                    // The DownloaderService has started downloading the files,
                    // show progress
                    return;
                }
                // otherwise, download not needed so we fall through to starting the movie
            }
            catch ( PackageManager.NameNotFoundException e )
            {
                Log.e( LOG_TAG, "Cannot find expansion file package!" );
                e.printStackTrace();
            }

        }
        else
        {
            validate();
        }
    }

    /** */
    protected void summarize()
    {
        Intent intent = new Intent();
        setResult( RESULT_OK, intent );

        finish();
    }

    /**
     * Go through each of the Expansion APK files and open each as a zip file.
     * Calculate the CRC for each file and return false if any fail to match.
     *
     * @return true if XAPKZipFile is successful
     */
    protected void validate()
    {
        AsyncTask<Object, DownloadProgressInfo, Boolean> validationTask = new AsyncTask<Object, DownloadProgressInfo, Boolean>()
        {
            @Override
            protected void onPreExecute()
            {
                mTvStatusText.setText( ActivityDownload.this.getString( R.string.downloader_verifying_download ) );

                /////////////////////
                super.onPreExecute();
                /////////////////////
            }

            @Override
            protected Boolean doInBackground( Object... params )
            {
                return true;
            }

            @Override
            protected void onProgressUpdate( DownloadProgressInfo... values )
            {
                onDownloadProgress( values[0] );

                ///////////////////////////////
                super.onProgressUpdate(values);
                ///////////////////////////////
            }

            @Override
            protected void onPostExecute(Boolean result)
            {
                if ( result )
                {
                    mTvStatusText.setText( ActivityDownload.this.getString( R.string.downloader_validation_completed ) );
                }
                else
                {
                    mTvStatusText.setText( ActivityDownload.this.getString( R.string.downloader_validation_failed ) );
                }

                //////////////////////////////
                super.onPostExecute( result );
                //////////////////////////////

                if ( result )
                {
                    ActivityDownload.this.summarize();
                }
            }

        };

        validationTask.execute( new Object() );
    }
}
