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

/** Scenery data class. */
public class Scenery
{
    public static final String LOG_TAG = "Scenery";

    private static final Scenery mInstance = new Scenery();
    
    private static final String SCENERY_FILE = "scenery.xml";
    
    private List< String > mScenery = new ArrayList< String >();
    
        /** */
    public static Scenery getInstance()
    {
        return mInstance;
    }

    /** */
    private Scenery()
    {
        reset();
    }
    
    /** */
    public String getScenery( int index )
    {
        if ( index >= 0 && index < mScenery.size() )
        {
            return mScenery.get( index );
        }

        return "";
    }
    
    /** */
    public int getCount()
    {
        return mScenery.size();
    }
    
    /** */
    public void reset()
    {
        try
        {
            File xmlFile = new File( DataPath.get( SCENERY_FILE ) );
            
            if ( xmlFile.exists() )
            {
                DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
                Document doc = docBuilder.parse( xmlFile );

                Node nodeRoot = doc.getDocumentElement();

                readScenery( nodeRoot );
            }
        }
        catch ( IOException | ParserConfigurationException | SAXException e )
        {
            e.printStackTrace();
        }
    }
    
    /** */
    private void readScenery( Node nodeRoot )
    {
        if ( nodeRoot.getNodeType() == Node.ELEMENT_NODE )
        {
            mScenery.clear();

            Element elementRoot = (Element)nodeRoot;

            NodeList sceneryList;
            sceneryList = elementRoot.getElementsByTagName( "scenery" );

            for ( int i = 0; i < sceneryList.getLength(); i++ )
            {
                Node nodeScenery = sceneryList.item( i );

                if ( nodeScenery.getNodeType() == Node.ELEMENT_NODE )
                {
                    Element elementScenery = (Element)nodeScenery;
                    
                    String name = "Scenery #" + String.valueOf( i + 1 );
                    
                    if ( elementScenery.hasAttribute( "name" ) )
                    {
                        name = elementScenery.getAttribute( "name" );
                    }

                    mScenery.add( name );
                }
            }
        }
    }
}
