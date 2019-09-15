package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;

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

/** */
public class Campaign
{
    public static final String LOG_TAG = "Campaign";

    public static final String CAMPAIGN_FILE = "missions/campaign.xml";

    public static final String KEY_MISSIONS_COUNT = "key_campaign_missions_count";

    public static final String KEY_COMPLETED_MISSIONS_NEW = "key_campaign_completed_missions";
    public static final String KEY_COMPLETED_MISSIONS_OLD = "conf_completed_missions";

    private SharedPreferences mSharedPreferences = null;

    private List< Mission > mMissions = new ArrayList< Mission >(); ///< missions

    /** */
    public Campaign( Context context )
    {
        mSharedPreferences = PreferenceManager.getDefaultSharedPreferences( context );
        
        readCampaign();

        int missionsCount = mSharedPreferences.getInt( KEY_MISSIONS_COUNT, 0 );

        if ( missionsCount != mMissions.size() && mMissions.size() > 0 )
        {
            SharedPreferences.Editor editor = mSharedPreferences.edit();

            editor.putInt( KEY_MISSIONS_COUNT, mMissions.size() );
            editor.apply();
        }
    }

    /** */
    public int getCompletedMissions()
    {
        int completedMissionsOld = mSharedPreferences.getInt( KEY_COMPLETED_MISSIONS_OLD, 1 );
        int completedMissionsNew = mSharedPreferences.getInt( KEY_COMPLETED_MISSIONS_NEW, 1 );

        if ( completedMissionsOld > completedMissionsNew )
        {
            return completedMissionsOld;
        }

        return completedMissionsNew;
    }

    /** */
    public int getMissionsCount()
    {
        return mMissions.size();
    }

    /** */
    public Mission getMission( int index )
    {
        if ( index >=0 && index < mMissions.size() )
        {
            return mMissions.get( index );
        }

        return null;
    }
    
    /** */
    public boolean isMissionLocked( int index )
    {
        if ( index == 0 || index == 1 )
        {
            // tutorial and first mission
            return false;
        }
        else if ( index > 0 )
        {
            Mission previousMission = mMissions.get( index - 1 );

            if ( previousMission != null )
            {
                if ( previousMission.isCompleted() )
                {
                    return false;
                }
            }
        }

        return true;
    }

    /** */
    public void setCompletedMissions( int value )
    {
        SharedPreferences.Editor editor = mSharedPreferences.edit();

        editor.putInt( KEY_COMPLETED_MISSIONS_NEW, value );
        editor.apply();
    }
    
    /** */
    public void reset()
    {
        readCampaign();
    }

    /** */
    private void readCampaign()
    {
        try
        {
            File xmlFile = new File( DataPath.get( CAMPAIGN_FILE ) );

            if ( xmlFile.exists() )
            {
                DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
                Document doc = docBuilder.parse( xmlFile );

                Node nodeRoot = doc.getDocumentElement();

                readCampaign( nodeRoot );
            }
        }
        catch ( IOException | ParserConfigurationException | SAXException e )
        {
            e.printStackTrace();
        }
    }

    /** */
    private void readCampaign( Node nodeRoot )
    {
        if ( nodeRoot.getNodeType() == Node.ELEMENT_NODE )
        {
            mMissions.clear();
            
            Element elementRoot = (Element)nodeRoot;

            NodeList missionsList;
            missionsList = elementRoot.getElementsByTagName( "mission" );

            for ( int i = 0; i < missionsList.getLength(); i++ )
            {
                Node nodeMission = missionsList.item( i );

                if ( nodeMission.getNodeType() == Node.ELEMENT_NODE )
                {
                    Element elementMission = (Element)nodeMission;

                    String missionFile = DataPath.get( "missions/" + elementMission.getAttribute( "file" ) );

                    mMissions.add( new Mission( this, i, missionFile ) );
                }
            }
        }
    }
}
