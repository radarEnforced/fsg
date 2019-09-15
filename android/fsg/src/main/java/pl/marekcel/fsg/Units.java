package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

////////////////////////////////////////////////////////////////////////////////

/** Units data class. */
public class Units
{
    public static final String LOG_TAG = "Units";

    private static final Units mInstance = new Units();
    
    private static final String UNITS_FILE = "units.xml";

    /** Unit data. */
    public static class Unit
    {
        public static final int AERIAL = 0;         ///< aerial unit type
        public static final int MARINE = 1;         ///< marine unit type
        public static final int GROUND = 2;         ///< ground unit type

        /** Unit data. */
        public static class Data
        {
            /** Aerial unit data. */
            public static class Aerial
            {
                public Text   mRole         = new Text();
                public String mManufacturer = "";   ///<
                public String mFirstFlight  = "";   ///<
                public String mIntroduction = "";   ///<
                public String mRetired      = "";   ///<
                public String mNumberBuilt  = "";   ///<
                public String mPrimaryUser  = "";   ///<
                public String mCrew         = "";   ///<
                public String mLength       = "";   ///<
                public String mWingspan     = "";   ///<
                public String mHeight       = "";   ///<
                public String mMTOW         = "";   ///<
                public String mMaxSpeed     = "";   ///<
                public String mRange        = "";   ///<
                public Text   mPowerplant   = new Text();
                public Text   mArmament     = new Text();
            }

            /** Marine unit data. */
            public static class Marine
            {
                public Text   mType         = new Text();
                public String mNumberBuilt  = "";   ///<
                public String mDisplacement = "";   ///<
                public String mLength       = "";   ///<
                public String mBeam         = "";   ///<
                public String mDraft        = "";   ///<
                public String mMaxSpeed     = "";   ///<
                public String mComplement   = "";   ///<
                public Text   mArmament     = new Text();
            }

            /** Ground unit data. */
            public static class Ground
            {

            }

            public Aerial mAerial = new Aerial();   ///< aerial unit data
            public Marine mMarine = new Marine();   ///< marine unit data
            public Ground mGround = new Ground();   ///< ground unit data
        }

        public int mIndex;

        public int    mType;                        ///< unit type
        public Text   mName = new Text();           ///< unit name
        public String mIcon;                        ///< unit icon
        public String mIconLocked = "";             ///< unit icon
        public Data   mData = new Data();           ///< unit data

        public boolean mPlayable = false;   ///<
        public boolean mOpponent = false;   ///<

        public int mUnlockMission = 0;      ///<

        public List< String > mLiveries = new ArrayList< String >();    ///< liveries list
    }

    private List< Unit > mUnits     = new ArrayList< Unit >();  ///< units
    private List< Unit > mPlayables = new ArrayList< Unit >();  ///< playables
    private List< Unit > mAllies    = new ArrayList< Unit >();  ///< allies
    private List< Unit > mOpponents = new ArrayList< Unit >();  ///< opponents

    /** */
    public static Units getInstance()
    {
        return mInstance;
    }

    /** */
    private Units()
    {
        reset();
    }

    /** */
    public Unit getUnit( int index )
    {
        if ( index >= 0 && index < mUnits.size() )
        {
            return mUnits.get( index );
        }

        return null;
    }
    
    /** */
    public Unit getUnitPlayable( int index )
    {
        if ( index >= 0 && index < mPlayables.size() )
        {
            return mPlayables.get( index );
        }

        return null;
    }
    
    /** */
    public int getUnitPlayableByIndex( int index )
    {
        for ( int i = 0; i < mPlayables.size(); i++ )
        {
            if ( mPlayables.get( i ).mIndex == index )
            {
                return i;
            }
        }
    
        return -1;
    }
    
    /** */
    public Unit getUnitAlly( int index )
    {
        if ( index >= 0 && index < mAllies.size() )
        {
            return mAllies.get( index );
        }

        return null;
    }
    
    /** */
    public int getUnitAllyByIndex( int index )
    {
        for ( int i = 0; i < mAllies.size(); i++ )
        {
            if ( mAllies.get( i ).mIndex == index )
            {
                return i;
            }
        }
    
        return -1;
    }
    
    /** */
    public Unit getUnitOpponent( int index )
    {
        if ( index >= 0 && index < mOpponents.size() )
        {
            return mOpponents.get( index );
        }

        return null;
    }
    
    /** */
    public int getUnitOpponentByIndex( int index )
    {
        for ( int i = 0; i < mOpponents.size(); i++ )
        {
            if ( mOpponents.get( i ).mIndex == index )
            {
                return i;
            }
        }
    
        return -1;
    }

    /** */
    public int getUnitsCount()
    {
        return mUnits.size();
    }
    
    /** */
    public int getPlayableUnitsCount()
    {
        return mPlayables.size();
    }
    
    /** */
    public int getAllyUnitsCount()
    {
        return mAllies.size();
    }
    
    /** */
    public int getOpponentUnitsCount()
    {
        return mOpponents.size();
    }
    
    /** */
    public void reset()
    {
        try
        {
            File xmlFile = new File( DataPath.get( UNITS_FILE ) );
            
            if ( xmlFile.exists() )
            {
                DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
                Document doc = docBuilder.parse( xmlFile );

                Node nodeRoot = doc.getDocumentElement();

                readUnits( nodeRoot );
            }
        }
        catch ( IOException | ParserConfigurationException | SAXException e )
        {
            e.printStackTrace();
        }
    }

    /** */
    private void readUnits( Node nodeRoot )
    {
        if ( nodeRoot.getNodeType() == Node.ELEMENT_NODE )
        {
            mUnits.clear();

            Element elementRoot = (Element)nodeRoot;

            Node nodeAerial = elementRoot.getElementsByTagName( "aerial" ).item( 0 );
            Node nodeMarine = elementRoot.getElementsByTagName( "marine" ).item( 0 );
            Node nodeGround = elementRoot.getElementsByTagName( "ground" ).item( 0 );

            if ( nodeAerial != null ) readUnits( nodeAerial, Unit.AERIAL );
            if ( nodeMarine != null ) readUnits( nodeMarine, Unit.MARINE );
            if ( nodeGround != null ) readUnits( nodeGround, Unit.GROUND );
        }
    }

    /** */
    private void readUnits( Node nodeUnits, int type )
    {
        if ( nodeUnits.getNodeType() == Node.ELEMENT_NODE )
        {
            Element elementUnits = (Element)nodeUnits;

            NodeList unitsList;
            unitsList = elementUnits.getElementsByTagName( "unit" );

            for ( int i = 0; i < unitsList.getLength(); i++ )
            {
                Node nodeUnit = unitsList.item( i );

                if ( nodeUnit.getNodeType() == Node.ELEMENT_NODE )
                {
                    Element elementUnit = (Element)nodeUnit;

                    Unit unit = new Unit();

                    unit.mType = type;
                    unit.mName = Text.readText( elementUnit.getElementsByTagName( "name" ).item( 0 ) );
                    unit.mIcon = elementUnit.getElementsByTagName( "icon" ).item( 0 ).getTextContent();

                    unit.mIconLocked = readUnitData( elementUnit,"icon_locked" );

                    unit.mLiveries = readLiveries( elementUnit );

                    switch ( type )
                    {
                        case Unit.AERIAL:
                            unit.mData.mAerial = readUnitAerial( elementUnit );
                            break;

                        case Unit.MARINE:
                            unit.mData.mMarine = readUnitMarine( elementUnit );
                            break;

                        case Unit.GROUND:
                            unit.mData.mGround = readUnitGround( elementUnit );
                            break;
                    }

                    unit.mIndex = mUnits.size();

                    mUnits.add( unit );

                    if ( elementUnit.hasAttribute( "playable" ) )
                    {
                        unit.mPlayable = Integer.valueOf( elementUnit.getAttribute( "playable" ) ) != 0;
                    }

                    if ( elementUnit.hasAttribute( "opponent" ) )
                    {
                        unit.mOpponent = Integer.valueOf( elementUnit.getAttribute( "opponent" ) ) != 0;
                    }

                    unit.mUnlockMission = 0;

                    if ( elementUnit.hasAttribute( "unlock_mission" ) )
                    {
                        unit.mUnlockMission = Integer.valueOf( elementUnit.getAttribute( "unlock_mission" ) );
                    }
                    
                    if ( unit.mPlayable )
                    {
                        mPlayables.add( unit );
                    }

                    if ( type == Unit.AERIAL )
                    {
                        if ( unit.mOpponent )
                        {
                            mOpponents.add( unit );
                        }
                        else
                        {
                            mAllies.add( unit );
                        }
                    }
                }
            }
        }
    }

    private List< String > readLiveries( Element elementUnit )
    {
        List< String > liveries = new ArrayList< String >();

        Node nodeLiveries = elementUnit.getElementsByTagName( "liveries" ).item( 0 );

        if ( nodeLiveries != null )
        {
            if ( nodeLiveries.getNodeType() == Node.ELEMENT_NODE )
            {
                Element elementLiveries = (Element)nodeLiveries;

                NodeList liveriesList;
                liveriesList = elementLiveries.getElementsByTagName( "livery" );

                for ( int j = 0; j < liveriesList.getLength(); j++ )
                {
                    Node nodeLivery = liveriesList.item( j );

                    if ( nodeLivery.getNodeType() == Node.ELEMENT_NODE )
                    {
                        Element elementLivery = (Element)nodeLivery;

                        if ( elementLivery.hasAttribute( "name" ) )
                        {
                            liveries.add( elementLivery.getAttribute( "name" ) );
                        }
                        else
                        {
                            liveries.add( "Livery #" + String.valueOf( liveries.size() + 1 ) );
                        }
                    }
                }
            }
        }

        return liveries;
    }

    /** */
    private Unit.Data.Aerial readUnitAerial( Element elementUnit )
    {
        Unit.Data.Aerial data = new Unit.Data.Aerial();
        
        Node nodeInfo = elementUnit.getElementsByTagName( "info" ).item( 0 );

        if ( nodeInfo.getNodeType() == Node.ELEMENT_NODE )
        {
            Element elementInfo = (Element)nodeInfo;

            data.mRole         = Text.readText( elementInfo.getElementsByTagName( "role" ).item( 0 ) );
            data.mManufacturer = readUnitData( elementInfo, "manufacturer" );
            data.mFirstFlight  = readUnitData( elementInfo, "first_flight" );
            data.mIntroduction = readUnitData( elementInfo, "introduction" );
            data.mRetired      = readUnitData( elementInfo, "retired"      );
            data.mNumberBuilt  = readUnitData( elementInfo, "number_built" );
            data.mPrimaryUser  = readUnitData( elementInfo, "primary_user" );
            data.mCrew         = readUnitData( elementInfo, "crew"         );
            data.mLength       = readUnitData( elementInfo, "length"       );
            data.mWingspan     = readUnitData( elementInfo, "wingspan"     );
            data.mHeight       = readUnitData( elementInfo, "height"       );
            data.mMTOW         = readUnitData( elementInfo, "mtow"         );
            data.mMaxSpeed     = readUnitData( elementInfo, "max_speed"    );
            data.mRange        = readUnitData( elementInfo, "range"        );
            data.mPowerplant   = Text.readText( elementInfo.getElementsByTagName( "powerplant" ).item( 0 ) );
            data.mArmament     = Text.readText( elementInfo.getElementsByTagName( "armament" ).item( 0 ) );
        }

        return data;
    }

    /** */
    private Unit.Data.Marine readUnitMarine( Element elementUnit )
    {
        Unit.Data.Marine data = new Unit.Data.Marine();
        
        Node nodeInfo = elementUnit.getElementsByTagName( "info" ).item( 0 );

        if ( nodeInfo.getNodeType() == Node.ELEMENT_NODE )
        {
            Element elementInfo = (Element)nodeInfo;

            data.mType         = Text.readText( elementInfo.getElementsByTagName( "type" ).item( 0 ) );
            data.mNumberBuilt  = readUnitData( elementInfo, "number_built" );
            data.mDisplacement = readUnitData( elementInfo, "displacement" );
            data.mLength       = readUnitData( elementInfo, "length"       );
            data.mBeam         = readUnitData( elementInfo, "beam"         );
            data.mDraft        = readUnitData( elementInfo, "draft"        );
            data.mMaxSpeed     = readUnitData( elementInfo, "max_speed"    );
            data.mComplement   = readUnitData( elementInfo, "complement"   );
            data.mArmament     = Text.readText( elementInfo.getElementsByTagName( "armament" ).item( 0 ) );
        }

        return data;
    }

    /** */
    private Unit.Data.Ground readUnitGround( Element elementUnit )
    {
        Unit.Data.Ground data = new Unit.Data.Ground();
        
        Node nodeInfo = elementUnit.getElementsByTagName( "info" ).item( 0 );

        if ( nodeInfo.getNodeType() == Node.ELEMENT_NODE )
        {
            Element elementInfo = (Element)nodeInfo;
        }

        return data;
    }

    /** */
    private String readUnitData( Element elementData, String tagName )
    {
        String result = "";

        NodeList list = elementData.getElementsByTagName( tagName );

        if ( list.getLength() > 0 )
        {
            result = list.item( 0 ).getTextContent();
        }

        return result;
    }
}
