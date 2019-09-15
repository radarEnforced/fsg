package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;
import android.graphics.Typeface;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.omnitech_software.fsg.Units;

////////////////////////////////////////////////////////////////////////////////

/** */
public class AdapterSkins extends RecyclerView.Adapter<AdapterSkins.SkinViewHolder>
{
    public static final String LOG_TAG = "AdapterSkins";

    private SkinClickListener mOnClickListener = null;

    private int mNumberItems;
    private int mUnitIndex;

    private TextView mSelectedView = null;
    private int mItemSelected = -1;

    /** */
    public interface SkinClickListener
    {
        void onClick( int clickedItemIndex );
    }

    /** */
    public AdapterSkins( int itemSelected )
    {
        mNumberItems = 0;
        mItemSelected = itemSelected;
    }

    /** */
    @Override
    public SkinViewHolder onCreateViewHolder( ViewGroup viewGroup, int viewType )
    {
        Context context = viewGroup.getContext();

        int layoutIdForListItem = R.layout.item_livery;
        LayoutInflater inflater = LayoutInflater.from( context );
        boolean shouldAttachToParentImmediately = false;

        View view = inflater.inflate( layoutIdForListItem, viewGroup, shouldAttachToParentImmediately );
        SkinViewHolder viewHolder = new SkinViewHolder( view );

        return viewHolder;
    }

    /** */
    @Override
    public void onBindViewHolder( SkinViewHolder holder, int position )
    {
        holder.bind( position );

        if ( mItemSelected == position )
        {
            selectView( holder.getTextName() );
        }
    }

    /** */
    @Override
    public int getItemCount()
    {
        return mNumberItems;
    }

    /** */
    public void setOnClickListener( SkinClickListener listener )
    {
        mOnClickListener = listener;
    }

    /** */
    public void setItemSelected( int itemSelected )
    {
        mItemSelected = itemSelected;
        unselectView();
    }

    /** */
    public void unselectView()
    {
        if ( mSelectedView != null )
        {
            mSelectedView.setTypeface( null, Typeface.NORMAL );
        }

        mSelectedView = null;
    }

    /** */
    public void selectView( TextView v )
    {
        unselectView();

        mSelectedView = v;
        mSelectedView.setTypeface( null, Typeface.BOLD_ITALIC );
    }

    /** */
    public void setUnitIndex( int unitIndex )
    {
        mUnitIndex = unitIndex;

        if ( mUnitIndex >= 0 && mUnitIndex < Units.getInstance().getUnitsCount() )
        {
            mNumberItems = Units.getInstance().getUnit( mUnitIndex ).mLiveries.size();
        }
        else
        {
            mNumberItems = 0;
        }

        setItemSelected( 0 );
    }

    /** */
    class SkinViewHolder extends RecyclerView.ViewHolder
            implements View.OnClickListener
    {
        TextView mTextName;

        /** */
        public SkinViewHolder( View itemView )
        {
            //////////////////
            super( itemView );
            //////////////////

            mTextName = (TextView)  itemView.findViewById( R.id.item_liveries_tv_name );

            itemView.setOnClickListener( this );
        }

        /** */
        void bind( int listIndex )
        {
            mTextName.setText( Units.getInstance().getUnit( mUnitIndex ).mLiveries.get( listIndex ) );
        }

        /** */
        @Override
        public void onClick( View v )
        {
            selectView( mTextName );

            int clickedPosition = getAdapterPosition();

            if ( mOnClickListener != null )
            {
                mOnClickListener.onClick( clickedPosition );
            }
        }

        /** */
        TextView getTextName()
        {
            return mTextName;
        }
    }
}
