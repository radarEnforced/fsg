package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.TextView;

import com.omnitech_software.fsg.Campaign;
import com.omnitech_software.fsg.DataPath;
import com.omnitech_software.fsg.Units;

import java.io.File;

////////////////////////////////////////////////////////////////////////////////

/** */
public class AdapterUnits extends RecyclerView.Adapter< AdapterUnits.UnitViewHolder >
{
    public static final String LOG_TAG = "AdapterUnits";

    private UnitClickListener mOnClickListener = null;

    private int mNumberItems;

    private int mMode = -1;

    Campaign mCampaign = null;

    private View mSelectedView = null;
    private int mItemSelected = -1;

    /** */
    public interface UnitClickListener
    {
        void onClick( int clickedItemIndex );
    }

    /** */
    public AdapterUnits( int itemSelected, int mode, Context context )
    {
        mMode = mode;

        mCampaign = new Campaign( context );

        mItemSelected = itemSelected;

        if ( mMode == ActivityChooseUnit.MODE_OWNSHIP )
        {
            mNumberItems = Units.getInstance().getPlayableUnitsCount();
        }
        else if ( mMode == ActivityChooseUnit.MODE_FRIEND )
        {
            mNumberItems = Units.getInstance().getAllyUnitsCount();
        }
        else if ( mMode == ActivityChooseUnit.MODE_ENEMY )
        {
            mNumberItems = Units.getInstance().getOpponentUnitsCount();
        }
    }

    /** */
    @Override
    public UnitViewHolder onCreateViewHolder( ViewGroup viewGroup, int viewType )
    {
        Context context = viewGroup.getContext();

        int layoutIdForListItem = R.layout.item_unit;
        LayoutInflater inflater = LayoutInflater.from( context );
        boolean shouldAttachToParentImmediately = false;

        View view = inflater.inflate( layoutIdForListItem, viewGroup, shouldAttachToParentImmediately );
        UnitViewHolder viewHolder = new UnitViewHolder( view );

        return viewHolder;
    }

    /** */
    @Override
    public void onBindViewHolder( UnitViewHolder holder, int position )
    {
        holder.bind( position );

        if ( mItemSelected == position )
        {
            selectView( holder.getItemView() );
        }
    }

    /** */
    @Override
    public int getItemCount()
    {
        return mNumberItems;
    }

    /** */
    public void setOnClickListener( UnitClickListener listener )
    {
        mOnClickListener = listener;
    }

    /** */
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

    /** */
    public void selectView( View v )
    {
        unselectView();

        // run scale animation and make it bigger
        Animation anim = AnimationUtils.loadAnimation( v.getContext(), R.anim.scale_up );
        v.startAnimation( anim );
        anim.setFillAfter( true );

        mSelectedView = v;
    }

    /** */
    class UnitViewHolder extends RecyclerView.ViewHolder
            implements View.OnClickListener
    {
        View mItemView;

        ImageView mImageView;
        TextView mTextName;

        /** */
        public UnitViewHolder( View itemView )
        {
            //////////////////
            super( itemView );
            //////////////////

            mItemView = itemView;

            mImageView = (ImageView) itemView.findViewById( R.id.item_unit_img_image );
            mTextName  = (TextView)  itemView.findViewById( R.id.item_unit_tv_name   );

            itemView.setOnClickListener( this );
        }

        /** */
        void bind( int listIndex )
        {
            Units.Unit unitData = ActivityChooseUnit.getUnitData( mMode, listIndex );

            mTextName.setText( unitData.mName.get() );

            String iconFilePath = unitData.mIcon;

            if ( mCampaign.isMissionLocked( unitData.mUnlockMission ) )
            {
                iconFilePath = unitData.mIconLocked;
            }

            File imageFile = new File( DataPath.get( iconFilePath ) );

            if ( imageFile.exists() )
            {
                Bitmap bitmap = BitmapFactory.decodeFile( imageFile.getAbsolutePath() );

                if ( bitmap != null )
                {
                    mImageView.setImageBitmap( bitmap );
                }
            }
        }

        /** */
        @Override
        public void onClick( View v )
        {
            int clickedPosition = getAdapterPosition();

            Units.Unit unitData = ActivityChooseUnit.getUnitData( mMode, clickedPosition );

            if ( unitData.mIndex >= 0 && unitData.mIndex < Units.getInstance().getUnitsCount() )
            {
                if( !mCampaign.isMissionLocked( unitData.mUnlockMission ) )
                {
                    selectView( v );
                }
            }

            if ( mOnClickListener != null )
            {
                mOnClickListener.onClick( clickedPosition );
            }
        }

        /** */
        View getItemView()
        {
            return mItemView;
        }
    }
}
