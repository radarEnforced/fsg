package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

////////////////////////////////////////////////////////////////////////////////

/** */
public class ActivityQuickAction extends ActivityInterstitial
{
    public static final String LOG_TAG = "ActivityQuickAction";

    public static final int CODE_SIM_STATUS      =  1;  ///<
    public static final int CODE_CHOOSE_SCENERY  =  2;  ///<
    public static final int CODE_CHOOSE_OWNSHIP  =  3;  ///<
    public static final int CODE_CHOOSE_WINGMAN  =  4;  ///<
    public static final int CODE_CHOOSE_FRIEND_1 =  5;  ///<
    public static final int CODE_CHOOSE_FRIEND_2 =  6;  ///<
    public static final int CODE_CHOOSE_ENEMY_1  =  7;  ///<
    public static final int CODE_CHOOSE_ENEMY_2  =  8;  ///<
    public static final int CODE_CHOOSE_ENEMY_3  =  9;  ///<
    public static final int CODE_CHOOSE_ENEMY_4  = 10;  ///<

    private int mIndexScenery = 0;          ///<

    private int mIndexOwnshipType = Units.getInstance().getUnitPlayable( 0 ).mIndex;
    private int mIndexWingmanType = -1;     ///<
    private int mIndexFriendType1 = -1;     ///<
    private int mIndexFriendType2 = -1;     ///<
    private int mIndexEnemyType1  = -1;     ///<
    private int mIndexEnemyType2  = -1;     ///<
    private int mIndexEnemyType3  = -1;     ///<
    private int mIndexEnemyType4  = -1;     ///<

    private int mIndexOwnshipLivery =  0;   ///<
    private int mIndexWingmanLivery = -1;   ///<
    private int mIndexFriendLivery1 = -1;   ///<
    private int mIndexFriendLivery2 = -1;   ///<
    private int mIndexEnemyLivery1  = -1;   ///<
    private int mIndexEnemyLivery2  = -1;   ///<
    private int mIndexEnemyLivery3  = -1;   ///<
    private int mIndexEnemyLivery4  = -1;   ///<

    TextView mTextViewScenery;              ///<
    TextView mTextViewOwnshipType;          ///<
    TextView mTextViewWingmanType;          ///<
    TextView mTextViewFriendType1;          ///<
    TextView mTextViewFriendType2;          ///<
    TextView mTextViewEnemyType1;           ///<
    TextView mTextViewEnemyType2;           ///<
    TextView mTextViewEnemyType3;           ///<
    TextView mTextViewEnemyType4;           ///<

    /** */
    @Override
    protected void onCreate( Bundle savedInstanceState )
    {
        /////////////////////////////////////
        super.onCreate( savedInstanceState );
        /////////////////////////////////////

        setContentView( R.layout.activity_quick_action );

        mTextViewScenery     = (TextView)findViewById( R.id.activity_skirmish_tv_scenery  );
        mTextViewOwnshipType = (TextView)findViewById( R.id.activity_skirmish_tv_ownship  );
        mTextViewWingmanType = (TextView)findViewById( R.id.activity_skirmish_tv_wingman  );
        mTextViewFriendType1 = (TextView)findViewById( R.id.activity_skirmish_tv_friend_1 );
        mTextViewFriendType2 = (TextView)findViewById( R.id.activity_skirmish_tv_friend_2 );
        mTextViewEnemyType1  = (TextView)findViewById( R.id.activity_skirmish_tv_enemy_1  );
        mTextViewEnemyType2  = (TextView)findViewById( R.id.activity_skirmish_tv_enemy_2  );
        mTextViewEnemyType3  = (TextView)findViewById( R.id.activity_skirmish_tv_enemy_3  );
        mTextViewEnemyType4  = (TextView)findViewById( R.id.activity_skirmish_tv_enemy_4  );

        updateView();
    }

    /** */
    @Override
    protected void onResume()
    {
        /////////////////
        super.onResume();
        /////////////////

        loadInterstitial();
    }

    /** */
    public void onButtonStartMissionClicked( View view )
    {
        if ( isInterstitialLoaded() )
        {
            showInterstitial();
        }
        else
        {
            startMission();
        }
    }

    /** */
    @Override
    protected void onActivityResult( int requestCode, int resultCode, Intent data )
    {
        ////////////////////////////////////////////////////////
        super.onActivityResult( requestCode, resultCode, data );
        ////////////////////////////////////////////////////////

        if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_SCENERY )
        {
            mIndexScenery = data.getIntExtra( ActivityChooseScenery.ARG_SCENERY, 0 );
        }
        else if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_OWNSHIP )
        {
            mIndexOwnshipType = data.getIntExtra( ActivityChooseUnit.ARG_UNIT, 0 );
            mIndexOwnshipLivery = data.getIntExtra( ActivityChooseUnit.ARG_SKIN, -1 );
        }
        else if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_WINGMAN )
        {
            mIndexWingmanType = data.getIntExtra( ActivityChooseUnit.ARG_UNIT, 0 );
            mIndexWingmanLivery = data.getIntExtra( ActivityChooseUnit.ARG_SKIN, -1 );
        }
        else if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_FRIEND_1 )
        {
            mIndexFriendType1 = data.getIntExtra( ActivityChooseUnit.ARG_UNIT, 0 );
            mIndexFriendLivery1 = data.getIntExtra( ActivityChooseUnit.ARG_SKIN, -1 );
        }
        else if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_FRIEND_2 )
        {
            mIndexFriendType2 = data.getIntExtra( ActivityChooseUnit.ARG_UNIT, 0 );
            mIndexFriendLivery2 = data.getIntExtra( ActivityChooseUnit.ARG_SKIN, -1 );
        }
        else if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_ENEMY_1 )
        {
            mIndexEnemyType1 = data.getIntExtra( ActivityChooseUnit.ARG_UNIT, 0 );
            mIndexEnemyLivery1 = data.getIntExtra( ActivityChooseUnit.ARG_SKIN, -1 );
        }
        else if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_ENEMY_2 )
        {
            mIndexEnemyType2 = data.getIntExtra( ActivityChooseUnit.ARG_UNIT, 0 );
            mIndexEnemyLivery2 = data.getIntExtra( ActivityChooseUnit.ARG_SKIN, -1 );
        }
        else if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_ENEMY_3 )
        {
            mIndexEnemyType3 = data.getIntExtra( ActivityChooseUnit.ARG_UNIT, 0 );
            mIndexEnemyLivery3 = data.getIntExtra( ActivityChooseUnit.ARG_SKIN, -1 );
        }
        else if ( resultCode == RESULT_OK && requestCode == CODE_CHOOSE_ENEMY_4 )
        {
            mIndexEnemyType4 = data.getIntExtra( ActivityChooseUnit.ARG_UNIT, 0 );
            mIndexEnemyLivery4 = data.getIntExtra( ActivityChooseUnit.ARG_SKIN, -1 );
        }

        updateView();
    }

    /** */
    @Override
    public void onInterstitialClosed()
    {
        startMission();
    }


    public void onButtonChangeSceneryClicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseScenery.class );
        intent.putExtra( ActivityChooseScenery.ARG_SCENERY, mIndexScenery );
        startActivityForResult( intent, CODE_CHOOSE_SCENERY );
    }

    public void onButtonChangeOwnshipClicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseUnit.class );
        intent.putExtra( ActivityChooseUnit.ARG_MODE, ActivityChooseUnit.MODE_OWNSHIP );
        intent.putExtra( ActivityChooseUnit.ARG_UNIT, mIndexOwnshipType );
        intent.putExtra( ActivityChooseUnit.ARG_SKIN, mIndexOwnshipLivery );
        startActivityForResult( intent, CODE_CHOOSE_OWNSHIP );
    }

    public void onButtonChangeWingmanClicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseUnit.class );
        intent.putExtra( ActivityChooseUnit.ARG_MODE, ActivityChooseUnit.MODE_FRIEND );
        intent.putExtra( ActivityChooseUnit.ARG_UNIT, mIndexWingmanType );
        intent.putExtra( ActivityChooseUnit.ARG_SKIN, mIndexWingmanLivery );
        startActivityForResult( intent, CODE_CHOOSE_WINGMAN );
    }

    public void onButtonChangeAlly1Clicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseUnit.class );
        intent.putExtra( ActivityChooseUnit.ARG_MODE, ActivityChooseUnit.MODE_FRIEND );
        intent.putExtra( ActivityChooseUnit.ARG_UNIT, mIndexFriendType1 );
        intent.putExtra( ActivityChooseUnit.ARG_SKIN, mIndexFriendLivery1 );
        startActivityForResult( intent, CODE_CHOOSE_FRIEND_1 );
    }

    public void onButtonChangeAlly2Clicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseUnit.class );
        intent.putExtra( ActivityChooseUnit.ARG_MODE, ActivityChooseUnit.MODE_FRIEND );
        intent.putExtra( ActivityChooseUnit.ARG_UNIT, mIndexFriendType2 );
        intent.putExtra( ActivityChooseUnit.ARG_SKIN, mIndexFriendLivery2 );
        startActivityForResult( intent, CODE_CHOOSE_FRIEND_2 );
    }

    public void onButtonChangeEnemy1Clicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseUnit.class );
        intent.putExtra( ActivityChooseUnit.ARG_MODE, ActivityChooseUnit.MODE_ENEMY );
        intent.putExtra( ActivityChooseUnit.ARG_UNIT, mIndexEnemyType1 );
        intent.putExtra( ActivityChooseUnit.ARG_SKIN, mIndexEnemyLivery1 );
        startActivityForResult( intent, CODE_CHOOSE_ENEMY_1 );
    }

    public void onButtonChangeEnemy2Clicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseUnit.class );
        intent.putExtra( ActivityChooseUnit.ARG_MODE, ActivityChooseUnit.MODE_ENEMY );
        intent.putExtra( ActivityChooseUnit.ARG_UNIT, mIndexEnemyType2 );
        intent.putExtra( ActivityChooseUnit.ARG_SKIN, mIndexEnemyLivery2 );
        startActivityForResult( intent, CODE_CHOOSE_ENEMY_2 );
    }

    public void onButtonChangeEnemy3Clicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseUnit.class );
        intent.putExtra( ActivityChooseUnit.ARG_MODE, ActivityChooseUnit.MODE_ENEMY );
        intent.putExtra( ActivityChooseUnit.ARG_UNIT, mIndexEnemyType3 );
        intent.putExtra( ActivityChooseUnit.ARG_SKIN, mIndexEnemyLivery3 );
        startActivityForResult( intent, CODE_CHOOSE_ENEMY_3 );
    }

    public void onButtonChangeEnemy4Clicked( View view )
    {
        Intent intent = new Intent( this, ActivityChooseUnit.class );
        intent.putExtra( ActivityChooseUnit.ARG_MODE, ActivityChooseUnit.MODE_ENEMY );
        intent.putExtra( ActivityChooseUnit.ARG_UNIT, mIndexEnemyType4 );
        intent.putExtra( ActivityChooseUnit.ARG_SKIN, mIndexEnemyLivery4 );
        startActivityForResult( intent, CODE_CHOOSE_ENEMY_4 );
    }

    /** */
    private void startMission()
    {
        SimNativeLib.destroy();
        Simulation.setup( mIndexScenery,
                mIndexOwnshipType , mIndexOwnshipLivery,
                mIndexWingmanType , mIndexWingmanLivery,
                mIndexFriendType1 , mIndexFriendLivery1,
                mIndexFriendType2 , mIndexFriendLivery2,
                mIndexEnemyType1  , mIndexEnemyLivery1,
                mIndexEnemyType2  , mIndexEnemyLivery2,
                mIndexEnemyType3  , mIndexEnemyLivery3,
                mIndexEnemyType4  , mIndexEnemyLivery4 );

        Intent intent = new Intent( this, ActivitySimulation.class );
        startActivityForResult( intent, CODE_SIM_STATUS );
    }

    /** */
    private void updateView()
    {
        if ( mIndexScenery >= 0 && mIndexScenery < Scenery.getInstance().getCount() )
        {
            mTextViewScenery.setText( Scenery.getInstance().getScenery( mIndexScenery ) );
        }
        else
        {
            mTextViewScenery.setText( getString( R.string.skirmish_unknown_scenery ) );
        }
        
        updateUnitTextView( mTextViewOwnshipType , mIndexOwnshipType );
        updateUnitTextView( mTextViewWingmanType , mIndexWingmanType );
        updateUnitTextView( mTextViewFriendType1 , mIndexFriendType1 );
        updateUnitTextView( mTextViewFriendType2 , mIndexFriendType2 );
        updateUnitTextView( mTextViewEnemyType1  , mIndexEnemyType1  );
        updateUnitTextView( mTextViewEnemyType2  , mIndexEnemyType2  );
        updateUnitTextView( mTextViewEnemyType3  , mIndexEnemyType3  );
        updateUnitTextView( mTextViewEnemyType4  , mIndexEnemyType4  );
    }

    /** */
    private void updateUnitTextView( TextView textView, int unitIndex )
    {
        if ( unitIndex >= 0 && unitIndex < Units.getInstance().getUnitsCount() )
        {
            textView.setText( Units.getInstance().getUnit( unitIndex ).mName.get() );
        }
        else
        {
            textView.setText( getString( R.string.skirmish_empty_slot ) );
        }
    }
}
