package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.MobileAds;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityInterstitial extends ActivityBase
{
    public static final String LOG_TAG = "ActivityInterstitial";
    public static final boolean ENABLED = true;

    protected InterstitialAd mInterstitial = null;  ///<
    protected boolean mShown = false;               ///<

    /** */
    public void loadInterstitial()
    {
        if ( ENABLED )
        {
            mShown = false;

            mInterstitial = new InterstitialAd( this );

            MobileAds.initialize( this, CommonData.mAdMobAppId );
            mInterstitial.setAdUnitId( CommonData.mAdMobInterstitialAdUnitId );

            mInterstitial.setAdListener(new AdListener() {
                @Override
                public void onAdClosed() {
                    onInterstitialClosed();
                }
            });

            mInterstitial.loadAd( ( new AdRequest.Builder() ).build() );
        }
    }

    /** */
    public void onInterstitialClosed() {}

    /** */
    public boolean isInterstitialLoaded()
    {
        if ( ENABLED && mInterstitial != null && !mShown )
        {
            return mInterstitial.isLoaded();
        }

        return false;
    }
    
    /** */
    public boolean isInterstitialLoadingStarted()
    {
        if ( ENABLED && mInterstitial != null && !mShown )
        {
            return true;
        }

        return false;
    }

    /** */
    public void showInterstitial()
    {
        if ( ENABLED && mInterstitial != null && !mShown )
        {
            mShown = true;

            if ( mInterstitial.isLoaded() )
            {
                mInterstitial.show();
            }
        }
    }
}
