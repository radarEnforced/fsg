package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;

import com.google.android.vending.expansion.downloader.Helpers;

import java.io.File;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ExpansionFile
{
    public static final String LOG_TAG = "ExpansionFile";

    /** */
    public static String getMainPath( Context context )
    {
        return Helpers.getExpansionAPKFileName( context, true, CommonData.mExpansionFileMainVersion );
    }

    /** */
    public static String getMainFullPath( Context context )
    {
        return context.getObbDir().getPath()+ File.separator + getMainPath( context );
    }

    /** */
    public static boolean doesMainExist( Context context )
    {
        return Helpers.doesFileExist( context, getMainPath( context ), CommonData.mExpansionFileMainSize, false );
    }
}
