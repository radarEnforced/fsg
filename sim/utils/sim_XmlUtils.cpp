#include <sim/utils/sim_XmlUtils.h>

#include <sim/sim_Defs.h>
#include <sim/sim_Languages.h>

#include <sim/utils/sim_Misc.h>
#include <sim/utils/sim_String.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

int XmlUtils::read( const XmlNode &node, int &value )
{
    if ( node.isValid() )
    {
        XmlNode textNode = node.getFirstChild();

        if ( textNode.isValid() && textNode.isText() )
        {
            std::string text = String::stripLeadingSpaces( textNode.getText() );

            value = String::toInt( text );

            if ( Misc::isValid( value ) )
            {
                return SIM_SUCCESS;
            }
        }
    }

    return SIM_FAILURE;
}

////////////////////////////////////////////////////////////////////////////////

int XmlUtils::read( const XmlNode &node, float &value )
{
    if ( node.isValid() )
    {
        XmlNode textNode = node.getFirstChild();

        if ( textNode.isValid() && textNode.isText() )
        {
            std::string text = String::stripLeadingSpaces( textNode.getText() );

            value = String::toFloat( text );

            if ( Misc::isValid( value ) )
            {
                return SIM_SUCCESS;
            }
        }
    }

    return SIM_FAILURE;
}

////////////////////////////////////////////////////////////////////////////////

int XmlUtils::read( const XmlNode &node, std::string &str )
{
    if ( node.isValid() )
    {
        XmlNode textNode = node.getFirstChild();

        if ( textNode.isValid() && textNode.isText() )
        {
            str = textNode.getText();

            return SIM_SUCCESS;
        }
    }

    return SIM_FAILURE;
}

////////////////////////////////////////////////////////////////////////////////

int XmlUtils::read( const XmlNode &node, Text &text )
{
    if ( node.isValid() )
    {
        XmlNode textNode = node.getFirstChildElement( "text" );

        while ( textNode.isValid() )
        {
            std::string str = "";

            if ( SIM_SUCCESS == read( textNode, str ) )
            {
                std::string lang = textNode.getAttribute( "lang" );

                int index = Languages::instance()->getIndexByCode( lang );

                if ( index >= 0 )
                {
                    text.set( index, str );
                }
            }

            textNode = textNode.getNextSiblingElement( "text" );
        }

        return SIM_SUCCESS;
    }

    return SIM_FAILURE;
}

////////////////////////////////////////////////////////////////////////////////

int XmlUtils::read( const XmlNode &node, Vec3 &vect )
{
    if ( node.isValid() )
    {
        XmlNode textNode = node.getFirstChild();

        if ( textNode.isValid() && textNode.isText() )
        {
            std::string text = String::stripLeadingSpaces( textNode.getText() );

            double x = std::numeric_limits< double >::quiet_NaN();
            double y = std::numeric_limits< double >::quiet_NaN();
            double z = std::numeric_limits< double >::quiet_NaN();

            int valRead = sscanf( text.c_str(),
                                  "%lf %lf %lf",
                                  &x, &y, &z );

            if ( valRead == 3 )
            {
                vect.x() = x;
                vect.y() = y;
                vect.z() = z;

                return SIM_SUCCESS;
            }
        }
    }

    return SIM_FAILURE;
}
