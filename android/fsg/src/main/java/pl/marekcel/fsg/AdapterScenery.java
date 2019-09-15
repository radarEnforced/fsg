package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.TextView;

import com.omnitech_software.fsg.Scenery;

////////////////////////////////////////////////////////////////////////////////

/** */
public class AdapterScenery extends RecyclerView.Adapter< AdapterScenery.SceneryViewHolder >
{
    public static final String LOG_TAG = "AdapterScenery";

    private SceneryClickListener mOnClickListener = null;

    private int mNumberItems = Scenery.getInstance().getCount();

    private View mSelectedView = null;
    private int mItemSelected = -1;

    /** */
    public interface SceneryClickListener
    {
        void onClick( int clickedItemIndex );
    }

    /** */
    public AdapterScenery( int itemSelected )
    {
        mNumberItems = Scenery.getInstance().getCount();
        mItemSelected = itemSelected;
    }

    /** */
    @Override
    public SceneryViewHolder onCreateViewHolder( ViewGroup viewGroup, int viewType )
    {
        Context context = viewGroup.getContext();

        int layoutIdForListItem = R.layout.item_scenery;
        LayoutInflater inflater = LayoutInflater.from( context );
        boolean shouldAttachToParentImmediately = false;

        View view = inflater.inflate( layoutIdForListItem, viewGroup, shouldAttachToParentImmediately );
        SceneryViewHolder viewHolder = new SceneryViewHolder( view );

        return viewHolder;
    }

    /** */
    @Override
    public void onBindViewHolder( SceneryViewHolder holder, int position )
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
    public void setOnClickListener(SceneryClickListener listener )
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
    class SceneryViewHolder extends RecyclerView.ViewHolder
            implements View.OnClickListener
    {
        View mItemView;

        ImageView mImageView;
        TextView mTextName;

        /** */
        public SceneryViewHolder( View itemView )
        {
            //////////////////
            super( itemView );
            //////////////////

            mItemView = itemView;

            //mImageView = (ImageView) itemView.findViewById( R.id.item_scenery_img_image );
            mTextName  = (TextView)  itemView.findViewById( R.id.item_scenery_tv_name );

            itemView.setOnClickListener( this );
        }

        /** */
        void bind( int listIndex )
        {
            mTextName.setText( Scenery.getInstance().getScenery( listIndex ) );
        }

        /** */
        @Override
        public void onClick( View v )
        {
            int clickedPosition = getAdapterPosition();

            selectView( v );

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
