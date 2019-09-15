package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.os.Bundle;
import android.view.View;
import android.widget.TableRow;
import android.widget.TextView;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityUnitEntry extends ActivityBase
{
    public static final String LOG_TAG = "ActivityUnitEntry";

    public static final String ARG_INDEX = "unit_index";

    private int mUnitIndex = 0;

    private ViewUnitEntry mViewEGL = null;

    private TextView mTvName = null;

    private TextView mTvRole         = null;
    private TextView mTvType         = null;
    private TextView mTvManufacturer = null;
    private TextView mTvFirstFlight  = null;
    private TextView mTvIntroduction = null;
    private TextView mTvRetired      = null;
    private TextView mTvNumberBuilt  = null;
    private TextView mTvPrimaryUser  = null;
    private TextView mTvCrew         = null;
    private TextView mTvDisplacement = null;
    private TextView mTvLength       = null;
    private TextView mTvWingspan     = null;
    private TextView mTvHeight       = null;
    private TextView mTvBeam         = null;
    private TextView mTvDraft        = null;
    private TextView mTvMTOW         = null;
    private TextView mTvMaxSpeed     = null;
    private TextView mTvRange        = null;
    private TextView mTvPowerplant   = null;
    private TextView mTvComplement   = null;
    private TextView mTvArmament     = null;

    private TableRow mTrRole         = null;
    private TableRow mTrType         = null;
    private TableRow mTrManufacturer = null;
    private TableRow mTrFirstFlight  = null;
    private TableRow mTrIntroduction = null;
    private TableRow mTrRetired      = null;
    private TableRow mTrNumberBuilt  = null;
    private TableRow mTrPrimaryUser  = null;
    private TableRow mTrCrew         = null;
    private TableRow mTrDisplacement = null;
    private TableRow mTrLength       = null;
    private TableRow mTrWingspan     = null;
    private TableRow mTrHeight       = null;
    private TableRow mTrBeam         = null;
    private TableRow mTrDraft        = null;
    private TableRow mTrMTOW         = null;
    private TableRow mTrMaxSpeed     = null;
    private TableRow mTrRange        = null;
    private TableRow mTrPowerplant   = null;
    private TableRow mTrComplement   = null;
    private TableRow mTrArmament     = null;

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        setContentView( R.layout.activity_unit_entry );

        mUnitIndex = getIntent().getIntExtra( ARG_INDEX, 0 );

        if ( savedInstanceState != null )
        {
            if ( savedInstanceState.containsKey( ARG_INDEX ) )
            {
                mUnitIndex = savedInstanceState.getInt( ARG_INDEX );
            }
        }

        mViewEGL = ( ViewUnitEntry )findViewById( R.id.activity_unit_entry_view_egl );
        mViewEGL.setUnitIndex( mUnitIndex );

        mTvName = (TextView)findViewById( R.id.activity_unit_entry_tv_name );

        mTvRole         = (TextView)findViewById( R.id.activity_unit_entry_tv_role );
        mTvType         = (TextView)findViewById( R.id.activity_unit_entry_tv_type );
        mTvManufacturer = (TextView)findViewById( R.id.activity_unit_entry_tv_manufacturer );
        mTvFirstFlight  = (TextView)findViewById( R.id.activity_unit_entry_tv_first_flight );
        mTvIntroduction = (TextView)findViewById( R.id.activity_unit_entry_tv_introduction );
        mTvRetired      = (TextView)findViewById( R.id.activity_unit_entry_tv_retired );
        mTvNumberBuilt  = (TextView)findViewById( R.id.activity_unit_entry_tv_number_built );
        mTvPrimaryUser  = (TextView)findViewById( R.id.activity_unit_entry_tv_primary_user );
        mTvCrew         = (TextView)findViewById( R.id.activity_unit_entry_tv_crew );
        mTvDisplacement = (TextView)findViewById( R.id.activity_unit_entry_tv_displacement );
        mTvLength       = (TextView)findViewById( R.id.activity_unit_entry_tv_length );
        mTvWingspan     = (TextView)findViewById( R.id.activity_unit_entry_tv_wingspan );
        mTvHeight       = (TextView)findViewById( R.id.activity_unit_entry_tv_height );
        mTvBeam         = (TextView)findViewById( R.id.activity_unit_entry_tv_beam );
        mTvDraft        = (TextView)findViewById( R.id.activity_unit_entry_tv_draft );
        mTvMTOW         = (TextView)findViewById( R.id.activity_unit_entry_tv_mtow );
        mTvMaxSpeed     = (TextView)findViewById( R.id.activity_unit_entry_tv_max_speed );
        mTvRange        = (TextView)findViewById( R.id.activity_unit_entry_tv_range );
        mTvPowerplant   = (TextView)findViewById( R.id.activity_unit_entry_tv_powerplant );
        mTvComplement   = (TextView)findViewById( R.id.activity_unit_entry_tv_complement );
        mTvArmament     = (TextView)findViewById( R.id.activity_unit_entry_tv_armament );

        mTrRole         = (TableRow)findViewById( R.id.activity_unit_entry_tr_role );
        mTrType         = (TableRow)findViewById( R.id.activity_unit_entry_tr_type );
        mTrManufacturer = (TableRow)findViewById( R.id.activity_unit_entry_tr_manufacturer );
        mTrFirstFlight  = (TableRow)findViewById( R.id.activity_unit_entry_tr_first_flight );
        mTrIntroduction = (TableRow)findViewById( R.id.activity_unit_entry_tr_introduction );
        mTrRetired      = (TableRow)findViewById( R.id.activity_unit_entry_tr_retired );
        mTrNumberBuilt  = (TableRow)findViewById( R.id.activity_unit_entry_tr_number_built );
        mTrPrimaryUser  = (TableRow)findViewById( R.id.activity_unit_entry_tr_primary_user );
        mTrCrew         = (TableRow)findViewById( R.id.activity_unit_entry_tr_crew );
        mTrDisplacement = (TableRow)findViewById( R.id.activity_unit_entry_tr_displacement );
        mTrLength       = (TableRow)findViewById( R.id.activity_unit_entry_tr_length );
        mTrWingspan     = (TableRow)findViewById( R.id.activity_unit_entry_tr_wingspan );
        mTrHeight       = (TableRow)findViewById( R.id.activity_unit_entry_tr_height );
        mTrBeam         = (TableRow)findViewById( R.id.activity_unit_entry_tr_beam );
        mTrDraft        = (TableRow)findViewById( R.id.activity_unit_entry_tr_draft );
        mTrMTOW         = (TableRow)findViewById( R.id.activity_unit_entry_tr_mtow );
        mTrMaxSpeed     = (TableRow)findViewById( R.id.activity_unit_entry_tr_max_speed );
        mTrRange        = (TableRow)findViewById( R.id.activity_unit_entry_tr_range );
        mTrPowerplant   = (TableRow)findViewById( R.id.activity_unit_entry_tr_powerplant );
        mTrComplement   = (TableRow)findViewById( R.id.activity_unit_entry_tr_complement );
        mTrArmament     = (TableRow)findViewById( R.id.activity_unit_entry_tr_armament );
    }

    /** */
    @Override
    protected void onResume()
    {
        /////////////////
        super.onResume();
        /////////////////

        mViewEGL.onResume();
        SimNativeLib.restart();

        mTvName.setText( Units.getInstance().getUnit( mUnitIndex ).mName.get() );

        Units.Unit unit = Units.getInstance().getUnit( mUnitIndex );

        if ( unit.mType == Units.Unit.AERIAL )
        {
            mTrRole.setVisibility( View.VISIBLE );
            mTrType.setVisibility( View.GONE );
            mTrManufacturer.setVisibility( View.VISIBLE );
            mTrFirstFlight.setVisibility( View.VISIBLE );
            mTrIntroduction.setVisibility( View.VISIBLE );
            mTrRetired.setVisibility( View.VISIBLE );
            mTrNumberBuilt.setVisibility( View.VISIBLE );
            mTrPrimaryUser.setVisibility( View.VISIBLE );
            mTrCrew.setVisibility( View.VISIBLE );
            mTrDisplacement.setVisibility( View.GONE );
            mTrLength.setVisibility( View.VISIBLE );
            mTrWingspan.setVisibility( View.VISIBLE );
            mTrHeight.setVisibility( View.VISIBLE );
            mTrBeam.setVisibility( View.GONE );
            mTrDraft.setVisibility( View.GONE );
            mTrMTOW.setVisibility( View.VISIBLE );
            mTrMaxSpeed.setVisibility( View.VISIBLE );
            mTrRange.setVisibility( View.VISIBLE );
            mTrPowerplant.setVisibility( View.VISIBLE );
            mTrComplement.setVisibility( View.GONE );
            mTrArmament.setVisibility( View.VISIBLE );

            mTvRole.setText( unit.mData.mAerial.mRole.get() );
            mTvManufacturer.setText( unit.mData.mAerial.mManufacturer );
            mTvFirstFlight.setText( unit.mData.mAerial.mFirstFlight );
            mTvIntroduction.setText( unit.mData.mAerial.mIntroduction );
            mTvRetired.setText( unit.mData.mAerial.mRetired );
            mTvNumberBuilt.setText( unit.mData.mAerial.mNumberBuilt );
            mTvPrimaryUser.setText( unit.mData.mAerial.mPrimaryUser );
            mTvCrew.setText( unit.mData.mAerial.mCrew );
            mTvLength.setText( unit.mData.mAerial.mLength );
            mTvWingspan.setText( unit.mData.mAerial.mWingspan );
            mTvHeight.setText( unit.mData.mAerial.mHeight );
            mTvMTOW.setText( unit.mData.mAerial.mMTOW );
            mTvMaxSpeed.setText( unit.mData.mAerial.mMaxSpeed );
            mTvRange.setText( unit.mData.mAerial.mRange );
            mTvPowerplant.setText( unit.mData.mAerial.mPowerplant.get() );
            mTvArmament.setText( unit.mData.mAerial.mArmament.get() );
        }
        else if ( unit.mType == Units.Unit.MARINE )
        {
            mTrRole.setVisibility( View.GONE );
            mTrType.setVisibility( View.VISIBLE );
            mTrManufacturer.setVisibility( View.GONE );
            mTrFirstFlight.setVisibility( View.GONE );
            mTrIntroduction.setVisibility( View.GONE );
            mTrRetired.setVisibility( View.GONE );
            mTrNumberBuilt.setVisibility( View.VISIBLE );
            mTrPrimaryUser.setVisibility( View.GONE );
            mTrCrew.setVisibility( View.GONE );
            mTrDisplacement.setVisibility( View.VISIBLE );
            mTrLength.setVisibility( View.VISIBLE );
            mTrWingspan.setVisibility( View.GONE );
            mTrHeight.setVisibility( View.GONE );
            mTrBeam.setVisibility( View.VISIBLE );
            mTrDraft.setVisibility( View.VISIBLE );
            mTrMTOW.setVisibility( View.GONE );
            mTrMaxSpeed.setVisibility( View.VISIBLE );
            mTrRange.setVisibility( View.GONE );
            mTrPowerplant.setVisibility( View.GONE );
            mTrComplement.setVisibility( View.VISIBLE );
            mTrArmament.setVisibility( View.VISIBLE );

            mTvType.setText( unit.mData.mMarine.mType.get() );
            mTvNumberBuilt.setText( unit.mData.mMarine.mNumberBuilt );
            mTvDisplacement.setText( unit.mData.mMarine.mDisplacement );
            mTvLength.setText( unit.mData.mMarine.mLength );
            mTvBeam.setText( unit.mData.mMarine.mBeam );
            mTvDraft.setText( unit.mData.mMarine.mDraft );
            mTvMaxSpeed.setText( unit.mData.mMarine.mMaxSpeed );
            mTvComplement.setText( unit.mData.mMarine.mComplement );
            mTvArmament.setText( unit.mData.mMarine.mArmament.get() );
        }
        else
        {
            mTrRole.setVisibility( View.GONE );
            mTrType.setVisibility( View.GONE );
            mTrManufacturer.setVisibility( View.GONE );
            mTrFirstFlight.setVisibility( View.GONE );
            mTrIntroduction.setVisibility( View.GONE );
            mTrRetired.setVisibility( View.GONE );
            mTrNumberBuilt.setVisibility( View.GONE );
            mTrPrimaryUser.setVisibility( View.GONE );
            mTrCrew.setVisibility( View.GONE );
            mTrDisplacement.setVisibility( View.GONE );
            mTrLength.setVisibility( View.GONE );
            mTrWingspan.setVisibility( View.GONE );
            mTrHeight.setVisibility( View.GONE );
            mTrBeam.setVisibility( View.GONE );
            mTrDraft.setVisibility( View.GONE );
            mTrMTOW.setVisibility( View.GONE );
            mTrMaxSpeed.setVisibility( View.GONE );
            mTrRange.setVisibility( View.GONE );
            mTrPowerplant.setVisibility( View.GONE );
            mTrComplement.setVisibility( View.GONE );
            mTrArmament.setVisibility( View.GONE );
        }
    }

    /** */
    @Override
    protected void onPause()
    {
        ////////////////
        super.onPause();
        ////////////////

        mViewEGL.onPause();
        SimNativeLib.pause();
    }

    /** */
    @Override
    protected void onSaveInstanceState( Bundle outState )
    {
        //////////////////////////////////////
        super.onSaveInstanceState( outState );
        //////////////////////////////////////

        outState.putInt( ARG_INDEX, mUnitIndex );
    }
}
