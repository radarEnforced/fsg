package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;

import com.google.android.vending.expansion.downloader.DownloaderClientMarshaller;
import com.google.android.vending.expansion.downloader.impl.DownloaderService;

////////////////////////////////////////////////////////////////////////////////

/**
 * This class demonstrates the minimal client implementation of the
 * DownloaderService from the Downloader library.
 */
public class ServiceDownloader extends DownloaderService
{
    public static final String LOG_TAG = "ServiceDownloader";

    /** Google Play publisher account licensing public key (Services and API's) */
    private static final String BASE64_PUBLIC_KEY = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqt/58xf8qB8lNl9/N+5PBVWwXpjBOBGoVDxBuLug0WiRGgNAUcM4K4jd3e5RaBS/b75b5VpgXJQYtsI/2rOCdc493eJemRA0lOrutZ7uVeT7aB2dWe4NlaLiEiTGnL9bqNlO/J1flfPNVhGIn4ldvM5MkSauq1t4l/T79JVZhfvIRqOJXHNn/1nylVGgb65CrSWI0ItAWkmo0S4MRkah0zAQmeY+kqIoMoja0mKYIO8T2uiBeg/NwdPQw1nO1CH6+6kbpbHLcSIOWmhoolMyymLpKulffZUc9/wygctMEjWc1z2f99EtoyBBj3NR7zKsOK5qMTylqluGJ22M61zvYwIDAQAB";

    /**
     * Salt used by the preference obfuscater to make sure that your
     * obfuscated preferences are different than the ones used by other
     * applications.
     */
    private static final byte[] SALT = new byte[]
    {
        1, -44, 24, 20, 66, 8, 50, -71, 27, 22, 55, -92, 61, 81, 91, 88, 12, -45, 21, 84
    };

    @Override
    public String getPublicKey()
    {
        return BASE64_PUBLIC_KEY;
    }

    @Override
    public byte[] getSALT()
    {
        return SALT;
    }

    /**
     * Fill this in with the class name for your alarm receiver. We do this
     * because receivers must be unique across all of Android (it's a good idea
     * to make sure that your receiver is in your unique package)
     */
    @Override
    public String getAlarmReceiverClassName()
    {
        return ReceiverAlarm.class.getName();
    }

    /**
     * You should start your derived downloader class when this receiver gets the message
     * from the alarm service using the provided service helper function within the
     * DownloaderClientMarshaller. This class must be then registered in your AndroidManifest.xml
     * file with a section like this:
     *         <receiver android:name=".SampleAlarmReceiver"/>
     */
    protected class ReceiverAlarm extends BroadcastReceiver
    {
        public static final String LOG_TAG = "ReceiverAlarm";

        @Override
        public void onReceive( Context context, Intent intent )
        {
            try
            {
                DownloaderClientMarshaller.startDownloadServiceIfRequired( context, intent, ServiceDownloader.class );
            }
            catch ( PackageManager.NameNotFoundException e )
            {
                e.printStackTrace();
            }
        }

    }

}
