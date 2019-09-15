package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.Toast;

import java.io.File;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityCampaign extends ActivityBase
{
    public static final String LOG_TAG = "ActivityCampaign";

    /** */
    public class OnFocusChangedListener implements View.OnFocusChangeListener
    {
        @Override
        public void onFocusChange( View v, boolean hasFocus )
        {
            if ( hasFocus )
            {
                ( (ItemSelectedListener)mGridView.getOnItemSelectedListener() ).focusIn();
            }
            else
            {
                ( (ItemSelectedListener)mGridView.getOnItemSelectedListener() ).unselectView();
            }
        }
    }

    /** */
    public class ItemClickListener implements AdapterView.OnItemClickListener
    {
        @Override
        public void onItemClick( AdapterView<?> parent, View v, int position, long id )
        {
            int index = position + 1;

            if ( !mCampaign.isMissionLocked( index ) )
            {
                ActivityCampaign.this.startActivityMission( index );
            }
            else
            {
                Toast.makeText( ActivityCampaign.this,
                        ActivityCampaign.this.getString( R.string.mission_locked ), Toast.LENGTH_SHORT ).show();
            }
        }
    }

    /** */
    public class ItemSelectedListener implements AdapterView.OnItemSelectedListener
    {
        private int mSelectedPosition = 0;
        private View mSelectedView = null;

        public void focusIn()
        {
            if ( mSelectedPosition == mGridView.getSelectedItemPosition() )
            {
                selectView( mGridView.getSelectedView() );
            }
        }

        @Override
        public void onItemSelected( AdapterView< ? > parent, View v, int position, long id )
        {
            selectView( v );

            mSelectedPosition = position;
        }

        @Override
        public void onNothingSelected( AdapterView< ? > parent )
        {
            unselectView();
        }

        public void selectView( View v )
        {
            unselectView();

            // run scale animation and make it bigger
            Animation anim = AnimationUtils.loadAnimation( v.getContext(), R.anim.scale_up );
            v.startAnimation( anim );
            anim.setFillAfter( true );

            mSelectedView = v;
        }

        public void unselectView()
        {
            if ( mSelectedView != null )
            {
                // run scale animation and make it smaller
                Animation anim = AnimationUtils.loadAnimation( mSelectedView.getContext(), R.anim.scale_dn );
                mSelectedView.startAnimation( anim );
                anim.setFillAfter( true );
            }

            mSelectedView = null;
        }
    }

    private Campaign mCampaign = null;  ///<
    private GridView mGridView = null;  ///<

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        mCampaign = new Campaign( this );

        setContentView( R.layout.activity_campaign );

        mGridView = (GridView)findViewById( R.id.activity_campaign_gridView );
        mGridView.setAdapter( new MissionAdapter( this ) );

        mGridView.setOnItemClickListener( new ItemClickListener() );
        mGridView.setOnFocusChangeListener( new OnFocusChangedListener() );
        mGridView.setOnItemSelectedListener( new ItemSelectedListener() );
    }

    @Override
    protected void onResume()
    {
        /////////////////
        super.onResume();
        /////////////////

        mCampaign.reset();

        if ( mGridView != null )
        {
            mGridView.invalidateViews();
        }
    }

    /** */
    public void startActivityMission( int index )
    {
        Intent intent = new Intent( this, ActivityMission.class );
        intent.putExtra( ActivityMission.ARG_INDEX, index );
        startActivity( intent );
    }

    /** */
    public class MissionAdapter extends BaseAdapter
    {
        Context mContext = null;

        public MissionAdapter( Context context )
        {
            ////////
            super();
            ////////

            mContext = context;
        }

        /** */
        public int getCount()
        {
            return mCampaign.getMissionsCount() - 1;
        }

        /** */
        public Object getItem( int position )
        {
            return null;
        }

        /** */
        public long getItemId( int position )
        {
            return 0;
        }

        /**
         * create a new ImageView for each item referenced by the Adapter
         */
        public View getView( int position, View convertView, ViewGroup parent )
        {
            int index = position + 1;

            View itemView = null;

            if ( convertView == null )
            {
                LayoutInflater inflater = (LayoutInflater) mContext.getSystemService( Context.LAYOUT_INFLATER_SERVICE );
                itemView = inflater.inflate( R.layout.item_campaign, null );
            }
            else
            {
                itemView = convertView;
            }

            ImageView imageView = (ImageView)itemView.findViewById( R.id.item_campaign_img_image );

            Mission mission = mCampaign.getMission( index );

            String iconFilePath = mission.getIconLocked();

            if ( !mCampaign.isMissionLocked( index ) )
            {
                iconFilePath = mission.getIcon();
            }

            File imageFile = new File( DataPath.get( iconFilePath ) );

            if ( imageFile.exists() )
            {
                Bitmap bitmap = BitmapFactory.decodeFile( imageFile.getAbsolutePath() );

                if ( bitmap != null )
                {
                    imageView.setImageBitmap( bitmap );
                }
            }

            imageView.setFocusable( false );
            imageView.setClickable( false );

            return itemView;
        }
    }
}
