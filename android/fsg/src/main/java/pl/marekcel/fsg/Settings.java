package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

////////////////////////////////////////////////////////////////////////////////

/** */
public class Settings
{
    public static final String LOG_TAG = "Settings";

    private Context mContext = null;

    private SharedPreferences mSharedPreferences = null;

    /** Constructor. */
    public Settings( Context context )
    {
        mContext = context;
        mSharedPreferences = PreferenceManager.getDefaultSharedPreferences( mContext );
    }

    /** */
    public boolean getInvertPitch()
    {
        return mSharedPreferences.getBoolean( mContext.getString( R.string.conf_invert_pitch_key ), false );
    }

    /** */
    public boolean getSilentMode()
    {
        return mSharedPreferences.getBoolean( mContext.getString( R.string.conf_silent_mode_key ), false );
    }

    /** */
    public boolean getNoController()
    {
        return mSharedPreferences.getBoolean( mContext.getString( R.string.conf_no_controller_key ), true );
    }
}
