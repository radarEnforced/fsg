package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivitySettings extends ActivityBase
{
    public static final String LOG_TAG = "ActivitySettings";

    private ImageView mImageViewBack = null;    ///<

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        super.onCreate( savedInstanceState );

        setContentView( R.layout.activity_settings );

        mImageViewBack = (ImageView)findViewById( R.id.activity_settings_img_back );
        mImageViewBack.setOnClickListener( new View.OnClickListener()
        {
            @Override
            public void onClick( View view )
            {
                onBackPressed();
            }
        } );
    }
}
