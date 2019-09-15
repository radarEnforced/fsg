package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

/** */
public class DataPath
{
    public static final String LOG_TAG = "DataPath";

    private static boolean mInited = false;     ///<
    private static String mBasePath = "/";      ///<

    /** */
    public static String get( String path )
    {
        return mBasePath + path;
    }

    /** */
    public static boolean isInited()
    {
        return mInited;
    }

    /** */
    public static void setBasePath( String basePath )
    {
        mBasePath = basePath;
        SimNativeLib.setBasePath( basePath );
        mInited = true;
    }
}
