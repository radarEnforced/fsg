package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

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

/** Languages class. */
public class Languages
{
    public static final String LOG_TAG = "Languages";

    /** Language data. */
    public static class Language
    {
        public String mCode = "";   ///<
        public String mName = "";   ///<
    }

    private static final Languages mInstance = new Languages();

    private static final String LANGUAGES_FILE = "languages.xml";   ///<

    private List< Language > mList = new ArrayList< Language >();   ///< supported languages list

    private int mCurrent = 0;       ///< current language index
    private int mDefault = 0;       ///< default language index

    /** */
    public static Languages getInstance()
    {
        return mInstance;
    }

    /** */
    private Languages()
    {
        reset();
    }

    /** */
    public int getCount()
    {
        return mList.size();
    }

    /** */
    public int getCurrent()
    {
        return mCurrent;
    }

    /** */
    int getIndexByCode( String code )
    {
        for ( int i = 0; i < mList.size(); i++ )
        {
            if ( mList.get( i ).mCode.equals( code ) )
            {
                return i;
            }
        }

        return mDefault;
    }

    /** */
    public void setCurrent( int index )
    {
        if ( index >= 0 && index < mList.size() )
        {
            mCurrent = index;
        }
    }

    /** */
    public void setCurrentByCode( String code )
    {
        setCurrent( getIndexByCode( code ) );
    }

    /** */
    public void reset()
    {
        try
        {
            mList.clear();

            mCurrent = 0;
            mDefault = 0;

            String filePath = DataPath.get( LANGUAGES_FILE );
            File xmlFile = new File( filePath );

            if ( xmlFile.exists() )
            {
                DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
                Document doc = docBuilder.parse( xmlFile );

                Node nodeRoot = doc.getDocumentElement();

                readLanguages( nodeRoot );
            }

            if ( mDefault >= 0 && mDefault < mList.size() )
            {
                mCurrent = mDefault;
            }
            else
            {
                mDefault = 0;
                mCurrent = 0;
            }
        }
        catch ( IOException | ParserConfigurationException | SAXException e )
        {
            e.printStackTrace();
        }
    }

    /** */
    private void readLanguages( Node nodeRoot )
    {
        if ( nodeRoot.getNodeType() == Node.ELEMENT_NODE )
        {
            Element elementRoot = (Element)nodeRoot;

            NodeList languageList;
            languageList = elementRoot.getElementsByTagName( "language" );

            for ( int i = 0; i < languageList.getLength(); i++ )
            {
                Node nodeLanguage = languageList.item( i );

                if ( nodeLanguage.getNodeType() == Node.ELEMENT_NODE )
                {
                    Element elementLanguage = (Element)nodeLanguage;

                    Language lang = new Language();

                    lang.mName = nodeLanguage.getTextContent();

                    if ( elementLanguage.hasAttribute( "code" ) )
                    {
                        lang.mCode = elementLanguage.getAttribute( "code" );
                    }

                    if ( elementLanguage.hasAttribute( "default" ) )
                    {
                        mDefault = i;
                    }

                    mList.add( lang );
                }
            }
        }
    }
}
