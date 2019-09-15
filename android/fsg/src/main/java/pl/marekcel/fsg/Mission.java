package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import android.content.Context;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.xml.sax.SAXException;

import java.io.File;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

////////////////////////////////////////////////////////////////////////////////

/** */
public class Mission
{
    public static final String LOG_TAG = "Mission";

    private Campaign mCampaign = null;  ///<

    private final int mIndex;           ///< mission index

    private String mIcon;               ///<
    private String mIconLocked;         ///<
    private String mImage;              ///<
    private String mImageLocked;        ///<

    private Text mName           = new Text();  ///< mission name
    private Text mIntroduction   = new Text();  ///< mission info
    private Text mSummaryFailure = new Text();  ///<
    private Text mSummarySuccess = new Text();  ///<

    /** */
    public Mission( Campaign campaign, int index, String file )
    {
        mCampaign = campaign;
        mIndex = index;

        try
        {
            File xmlFile = new File( file );

            DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
            Document doc = docBuilder.parse( xmlFile );

            Node nodeRoot = doc.getDocumentElement();

            readMission( nodeRoot );
        }
        catch ( IOException | ParserConfigurationException | SAXException e )
        {
            e.printStackTrace();
        }
    }

    public int getIndex()  { return mIndex; }

    public String getIcon() { return mIcon; }
    public String getIconLocked() { return mIconLocked; }
    public String getImage() { return mImage; }
    public String getImageLocked() { return mImageLocked; }
    public String getName() { return mName.get(); }
    public String getIntroduction() { return mIntroduction.get(); }
    public String getSummaryFailure() { return mSummaryFailure.get(); }
    public String getSummarySuccess() { return mSummarySuccess.get(); }

    /** */
    public boolean isCompleted()
    {
        return mIndex < mCampaign.getCompletedMissions();
    }

    /** */
    public void setCompleted()
    {
        mCampaign.setCompletedMissions( mIndex + 1 );
    }

    /** */
    private void readMission( Node nodeRoot )
    {
        if ( nodeRoot.getNodeType() == Node.ELEMENT_NODE )
        {
            Element elementRoot = (Element)nodeRoot;

            Node nodeData = elementRoot.getElementsByTagName( "data" ).item( 0 );

            if ( nodeData.getNodeType() == Node.ELEMENT_NODE )
            {
                Element elementData = (Element)nodeData;

                mIcon = elementData.getElementsByTagName( "icon" ).item( 0 ).getTextContent();
                mIconLocked = elementData.getElementsByTagName( "icon_locked" ).item( 0 ).getTextContent();
                mImage = elementData.getElementsByTagName( "image" ).item( 0 ).getTextContent();
                mImageLocked = elementData.getElementsByTagName( "image_locked" ).item( 0 ).getTextContent();

                mName = Text.readText( elementData.getElementsByTagName( "name" ).item( 0 ) );
                mIntroduction = Text.readText( elementData.getElementsByTagName( "introduction" ).item( 0 ) );
                mSummaryFailure = Text.readText( elementData.getElementsByTagName( "summary_failure" ).item( 0 ) );
                mSummarySuccess = Text.readText( elementData.getElementsByTagName( "summary_success" ).item( 0 ) );
            }
        }
    }
}
