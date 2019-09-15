package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;

////////////////////////////////////////////////////////////////////////////////

public class ActivityChooseScenery extends ActivityBase
{
    public static final String LOG_TAG = "ActivityChooseScenery";

    public static final String ARG_SCENERY = "scenery";

    /** */
    private class SceneryClickListener
            implements AdapterScenery.SceneryClickListener
    {
        /** */
        @Override
        public void onClick( int clickedItemIndex )
        {
            if ( clickedItemIndex >= 0 && clickedItemIndex < Scenery.getInstance().getCount() )
            {
                mIndexScenery = clickedItemIndex;
            }
            else
            {
                mIndexScenery = 0;
            }
        }
    }

    private ImageView mImageViewBack = null;    ///<

    private AdapterScenery mAdapterScenery;     ///<

    private RecyclerView mRecyclerViewScenery;  ///<

    private int mIndexScenery = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        mIndexScenery = getIntent().getIntExtra( ARG_SCENERY, 0 );

        setContentView( R.layout.activity_choose_scenery );

        mImageViewBack = (ImageView)findViewById( R.id.activity_choose_scenery_img_back);
        mImageViewBack.setOnClickListener( new View.OnClickListener()
        {
            @Override
            public void onClick( View view )
            {
                Intent intent = new Intent();
                setResult( RESULT_CANCELED, intent );

                finish();
            }
        } );

        mRecyclerViewScenery = (RecyclerView)findViewById( R.id.activity_choose_scenery_rv_scenery );

        LinearLayoutManager layoutManagerScenery = new LinearLayoutManager( this );

        mRecyclerViewScenery.setLayoutManager( layoutManagerScenery );
        mRecyclerViewScenery.setHasFixedSize( true );

        mAdapterScenery = new AdapterScenery( mIndexScenery );

        mRecyclerViewScenery.setAdapter( mAdapterScenery );

        mAdapterScenery.setOnClickListener( new SceneryClickListener() );
    }

    /** */
    public void onButtonOkClicked( View view )
    {
        Intent intent = new Intent();
        intent.putExtra( ARG_SCENERY, mIndexScenery );
        setResult( RESULT_OK, intent );

        finish();
    }
}
