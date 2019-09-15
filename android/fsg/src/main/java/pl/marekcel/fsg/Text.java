package pl.marekcel.fsg;

////////////////////////////////////////////////////////////////////////////////

import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.util.ArrayList;
import java.util.List;

////////////////////////////////////////////////////////////////////////////////

/** Text class. */
public class Text
{
    public static final String LOG_TAG = "Text";

    private List< String > mStrings = new ArrayList< String >();

    /**
     * Reads text from XML file.
     * @param node
     * @return
     */
    public static Text readText( Node node )
    {
        Text text = new Text();

        if ( node.getNodeType() == Node.ELEMENT_NODE )
        {
            Element element = (Element)node;

            NodeList textList;
            textList = element.getElementsByTagName( "text" );

            for ( int i = 0; i < textList.getLength(); i++ )
            {
                Node nodeText = textList.item( i );

                if ( nodeText.getNodeType() == Node.ELEMENT_NODE )
                {
                    String str = nodeText.getTextContent();

                    Element elementText = (Element)nodeText;

                    if ( elementText.hasAttribute( "lang" ) )
                    {
                        int index = Languages.getInstance().getIndexByCode( elementText.getAttribute( "lang" ) );

                        text.set( index, str );
                    }
                }
            }
        }

        return text;
    }

    /** Default constructor. */
    public Text()
    {
        mStrings.clear();
        
        for ( int i = 0; i < Languages.getInstance().getCount(); i++ )
        {
            mStrings.add( "" );
        }
    }

    /** */
    public String get()
    {
        return mStrings.get( Languages.getInstance().getCurrent() );
    }

    /** */
    public void set( int index, String str )
    {
        if ( index >= 0 )
        {
            if ( index < mStrings.size() )
            {
                mStrings.set( index, str );
            }
//            else if ( index == mStrings.size() )
//            {
//                mStrings.add( str );
//            }
        }
    }
}
