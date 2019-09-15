package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

/** */
public class SimNativeLib
{
    static
    {
        System.loadLibrary("simNativeLib");
    }

    /**
     * @param width the current view width
     * @param height the current view height
     * @param silent
     * @param mission_index
     */
    public static native void initCampaign( int width, int height, boolean silent,
                                            int mission_index );

    public static native void initSkirmish( int width, int height, boolean silent,
                                            int scenery_index,
                                            int ownship_type , int ownship_lilvery,
                                            int wingman_type , int wingman_lilvery,
                                            int ally_1_type  , int ally_1_lilvery,
                                            int ally_2_type  , int ally_2_lilvery,
                                            int enemy_1_type , int enemy_1_lilvery,
                                            int enemy_2_type , int enemy_2_lilvery,
                                            int enemy_3_type , int enemy_3_lilvery,
                                            int enemy_4_type , int enemy_4_lilvery );

    /**
     * @param width the current view width
     * @param height the current view height
     * @param unit_index
     */
    public static native void initUnitView( int width, int height, int unit_index );

    /** */
    public static native void pause();

    /** */
    public static native void unpause();

    /** */
    public static native void restart();

    /** */
    public static native void destroy();

    /**
     * @param timeStep [s]
     */
    public static native void update( double timeStep );

    /** */
    public static native float getInitThrottle();

    /** */
    public static native int getStatus();

    /** */
    public static native int getFriendsActivated();

    /** */
    public static native int getFriendsDestroyed();

    /** */
    public static native int getEnemiesActivated();

    /** */
    public static native int getEnemiesDestroyed();

    /** */
    public static native int getOwnshipDestroyed();

    /** */
    public static native int getFlightTime();

    /** */
    public static native boolean isFinished();

    /** */
    public static native boolean isPaused();

    /** */
    public static native boolean isPending();

    /** */
    public static native void setBasePath( String basePath );

    /** */
    public static native void setControls( boolean trigger,
                                           float ctrlRoll,
                                           float ctrlPitch,
                                           float ctrlYaw,
                                           float throttle );

    /** */
    public static native void setLanguage( int index );
}
