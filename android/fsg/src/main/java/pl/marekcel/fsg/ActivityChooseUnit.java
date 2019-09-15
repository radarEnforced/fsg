package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityChooseUnit extends ActivityBase
{
    public static final String LOG_TAG = "ActivityChooseUnit";

    public static final int MODE_OWNSHIP = 1;       ///<
    public static final int MODE_FRIEND  = 2;       ///<
    public static final int MODE_ENEMY   = 3;       ///<

    public static final String ARG_MODE = "mode";   ///<
    public static final String ARG_UNIT = "unit";   ///<
    public static final String ARG_SKIN = "skin";   ///<

    /** */
    private class SkinClickListener
            implements AdapterSkins.SkinClickListener
    {
        /** */
        @Override
        public void onClick( int clickedItemIndex )
        {
            if ( mIndexUnit >= 0 && mIndexUnit < Units.getInstance().getUnitsCount() )
            {
                if ( clickedItemIndex >= 0 && clickedItemIndex < Units.getInstance().getUnit( mIndexUnit ).mLiveries.size() )
                {
                    mIndexSkin = clickedItemIndex;
                }
                else
                {
                    mIndexSkin = -1;
                }
            }
            else
            {
                mIndexSkin = -1;
            }
        }
    }

    /** */
    private class UnitClickListener
            implements AdapterUnits.UnitClickListener
    {
        /** */
        @Override
        public void onClick( int clickedItemIndex )
        {
            Units.Unit unitData = getUnitData( mMode, clickedItemIndex );

            if ( isUnitUnlocked( unitData.mIndex ) )
            {
                mIndexUnit = unitData.mIndex;

                mAdapterSkins.setUnitIndex( mIndexUnit );
                mAdapterSkins.notifyDataSetChanged();

                mUnitItemIndex = clickedItemIndex;
            }
            else
            {
                //Toast.makeText( ActivityChooseUnit.this, getString( R.string.skirmish_aircraft_locked ), Toast.LENGTH_SHORT ).show();

                String message = getString( R.string.skirmish_finish_mission );
                message += " \"";
                message += mCampaign.getMission( unitData.mUnlockMission - 1 ).getName();
                message += "\" ";
                message += getString( R.string.skirmish_to_unlock_this_aircraft );

                Toast.makeText( ActivityChooseUnit.this, message, Toast.LENGTH_LONG ).show();
            }
        }
    }

    private ImageView mImageViewBack = null;        ///<

    private AdapterUnits mAdapterUnits;             ///<
    private AdapterSkins mAdapterSkins;             ///<

    private RecyclerView mRecyclerViewUnits;        ///<
    private RecyclerView mRecyclerViewSkins;        ///<

    private int mMode = -1;                         ///<

    private int mIndexUnit = -1;                    ///<
    private int mIndexSkin = -1;                    ///<
    
    private int mUnitItemIndex = -1;                ///<

    private Campaign mCampaign;                     ///<

    /** */
    public static Units.Unit getUnitData( int mode, int clickedItemIndex )
    {
        Units.Unit unitData = new Units.Unit();

        if ( mode == MODE_OWNSHIP )
        {
            unitData = Units.getInstance().getUnitPlayable( clickedItemIndex );
        }
        else if ( mode == MODE_FRIEND )
        {
            unitData = Units.getInstance().getUnitAlly( clickedItemIndex );
        }
        else if ( mode == MODE_ENEMY )
        {
            unitData = Units.getInstance().getUnitOpponent( clickedItemIndex );
        }

        return unitData;
    }

    /** */
    public static int getUnitItemIndex( int mode, int unitIndex )
    {
        int unitItemIndex = -1;

        if ( mode == MODE_OWNSHIP )
        {
            unitItemIndex = Units.getInstance().getUnitPlayableByIndex( unitIndex );
        }
        else if ( mode == MODE_FRIEND )
        {
            unitItemIndex = Units.getInstance().getUnitAllyByIndex( unitIndex );
        }
        else if ( mode == MODE_ENEMY )
        {
            unitItemIndex = Units.getInstance().getUnitOpponentByIndex( unitIndex );
        }

        return unitItemIndex;
    }

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        mCampaign = new Campaign( this );

        mMode = getIntent().getIntExtra( ARG_MODE, MODE_OWNSHIP );

        mIndexUnit = getIntent().getIntExtra( ARG_UNIT, 0 );
        mIndexSkin = getIntent().getIntExtra( ARG_SKIN, 0 );

        mUnitItemIndex = getUnitItemIndex( mMode, mIndexUnit );

        setContentView( R.layout.activity_choose_unit );

        mImageViewBack = (ImageView)findViewById( R.id.activity_choose_unit_img_back);
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

        mRecyclerViewUnits = (RecyclerView)findViewById( R.id.activity_choose_unit_rv_units );
        mRecyclerViewSkins = (RecyclerView)findViewById( R.id.activity_choose_unit_rv_skins );

        LinearLayoutManager layoutManagerUnits = new LinearLayoutManager( this );
        LinearLayoutManager layoutManagerSkins = new LinearLayoutManager( this );

        mRecyclerViewUnits.setLayoutManager( layoutManagerUnits );
        mRecyclerViewSkins.setLayoutManager( layoutManagerSkins );

        mRecyclerViewUnits.setHasFixedSize( true );

        mAdapterUnits = new AdapterUnits( mUnitItemIndex, mMode, this );
        mAdapterSkins = new AdapterSkins( mIndexSkin );

        mRecyclerViewSkins.setAdapter( mAdapterSkins );
        mRecyclerViewUnits.setAdapter( mAdapterUnits );

        mAdapterUnits.setOnClickListener( new UnitClickListener() );
        mAdapterSkins.setOnClickListener( new SkinClickListener() );
        
        mAdapterSkins.setUnitIndex( mIndexUnit );
        mAdapterSkins.notifyDataSetChanged();

        mRecyclerViewUnits.scrollToPosition( mUnitItemIndex );
        mRecyclerViewSkins.scrollToPosition( mIndexSkin );
    }

    /** */
    public void onButtonOkClicked( View view )
    {
        Intent intent = new Intent();
        intent.putExtra( ARG_MODE, mMode );
        intent.putExtra( ARG_UNIT, mIndexUnit );
        intent.putExtra( ARG_SKIN, mIndexSkin );
        setResult( RESULT_OK, intent );

        finish();
    }

    /** */
    private boolean isUnitUnlocked( int index )
    {
        if ( index >= 0 && index < Units.getInstance().getUnitsCount() )
        {
            return !mCampaign.isMissionLocked( Units.getInstance().getUnit( index ).mUnlockMission );
        }

        return false;
    }
}
