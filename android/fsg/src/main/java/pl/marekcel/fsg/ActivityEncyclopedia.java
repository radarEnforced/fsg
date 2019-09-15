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

import java.io.File;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityEncyclopedia extends ActivityBase
{
    public static final String LOG_TAG = "ActivityEncyclopedia";

    /** */
    public class OnFocusChangedListener implements View.OnFocusChangeListener
    {
        @Override
        public void onFocusChange( View v, boolean hasFocus )
        {
            if ( hasFocus )
            {
                ( (ActivityEncyclopedia.ItemSelectedListener )mGridView.getOnItemSelectedListener() ).focusIn();
            }
            else
            {
                ( (ActivityEncyclopedia.ItemSelectedListener )mGridView.getOnItemSelectedListener() ).unselectView();
            }
        }
    }

    /** */
    public class ItemClickListener implements AdapterView.OnItemClickListener
    {
        @Override
        public void onItemClick( AdapterView<?> parent, View v, int position, long id )
        {
            showUnit( position );
        }
    }

    /** */
    public class ItemSelectedListener implements AdapterView.OnItemSelectedListener
    {
        protected View mSelectedView = null;
        private int mSelectedPosition = 0;

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

    private GridView mGridView = null;  ///<

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        Units.getInstance().reset();

        setContentView( R.layout.activity_encyclopedia );

        Units.getInstance().reset();

        mGridView = (GridView)findViewById( R.id.activity_encyclopedia_gridView );
        mGridView.setAdapter( new UnitAdapter( this ) );

        mGridView.setOnItemClickListener( new ItemClickListener() );
        mGridView.setOnFocusChangeListener( new OnFocusChangedListener() );
        mGridView.setOnItemSelectedListener( new ItemSelectedListener() );
    }

    /** */
    public void showUnit( int index )
    {
        SimNativeLib.destroy();

        Intent intent = new Intent( this, ActivityUnitEntry.class );
        intent.putExtra( ActivityUnitEntry.ARG_INDEX, index );
        startActivity( intent );
    }

    /** */
    public class UnitAdapter extends BaseAdapter
    {
        private Context mContext;

        public UnitAdapter( Context context )
        {
            mContext = context;
        }

        public int getCount()
        {
            return Units.getInstance().getUnitsCount();
        }

        public Object getItem( int position )
        {
            return null;
        }

        public long getItemId( int position )
        {
            return 0;
        }

        /**
         * create a new ImageView for each item referenced by the Adapter
         */
        public View getView( int position, View convertView, ViewGroup parent )
        {
            View itemView = null;

            if ( convertView == null )
            {
                LayoutInflater inflater = (LayoutInflater) mContext.getSystemService( Context.LAYOUT_INFLATER_SERVICE );
                itemView = inflater.inflate( R.layout.item_encyclopedia, null );
            }
            else
            {
                itemView = convertView;
            }

            ImageView imageView = (ImageView)itemView.findViewById( R.id.item_encyclopedia_img_image );

            String iconFilePath = Units.getInstance().getUnit( position ).mIcon;
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
