#include <sim/sim_Captions.h>

#include <sim/sim_Base.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlDoc.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Captions::Captions()
{
    readCaptions();
}

////////////////////////////////////////////////////////////////////////////////

Captions::~Captions() {}

////////////////////////////////////////////////////////////////////////////////

void Captions::readCaptions()
{
    XmlDoc doc( Base::getPath( "captions.xml" ) );

    if ( doc.isOpen() )
    {
        XmlNode rootNode = doc.getRootNode();

        if ( rootNode.isValid() )
        {
            if ( 0 == String::icompare( rootNode.getName(), "captions" ) )
            {
                // loading
                XmlNode node_loading = rootNode.getFirstChildElement( "loading" );

                if ( node_loading.isValid() )
                {
                    Text temp;

                    if ( SIM_SUCCESS == XmlUtils::read( node_loading, temp ) )
                    {
                        m_loading = temp;
                    }
                }

                // resume
                XmlNode node_resume = rootNode.getFirstChildElement( "resume" );

                if ( node_resume.isValid() )
                {
                    Text temp;

                    if ( SIM_SUCCESS == XmlUtils::read( node_resume, temp ) )
                    {
                        m_resume = temp;
                    }
                }

                // begin
                XmlNode node_begin = rootNode.getFirstChildElement( "begin" );

                if ( node_begin.isValid() )
                {
                    Text temp;

                    if ( SIM_SUCCESS == XmlUtils::read( node_begin, temp ) )
                    {
                        m_begin = temp;
                    }
                }

                // mission_accomplished
                XmlNode node_mission_accomplished = rootNode.getFirstChildElement( "mission_accomplished" );

                if ( node_mission_accomplished.isValid() )
                {
                    Text temp;

                    if ( SIM_SUCCESS == XmlUtils::read( node_mission_accomplished, temp ) )
                    {
                        m_mission_accomplished = temp;
                    }
                }

                // mission_failed
                XmlNode node_mission_failed = rootNode.getFirstChildElement( "mission_failed" );

                if ( node_mission_failed.isValid() )
                {
                    Text temp;

                    if ( SIM_SUCCESS == XmlUtils::read( node_mission_failed, temp ) )
                    {
                        m_mission_failed = temp;
                    }
                }

                // friendly_fire
                XmlNode node_friendly_fire = rootNode.getFirstChildElement( "friendly_fire" );

                if ( node_friendly_fire.isValid() )
                {
                    Text temp;

                    if ( SIM_SUCCESS == XmlUtils::read( node_friendly_fire, temp ) )
                    {
                        m_friendly_fire = temp;
                    }
                }

                // target_killed
                XmlNode node_target_killed = rootNode.getFirstChildElement( "target_killed" );

                if ( node_target_killed.isValid() )
                {
                    Text temp;

                    if ( SIM_SUCCESS == XmlUtils::read( node_target_killed, temp ) )
                    {
                        m_target_killed = temp;
                    }
                }

                // target_hit
                XmlNode node_target_hit = rootNode.getFirstChildElement( "target_hit" );

                if ( node_target_hit.isValid() )
                {
                    Text temp;

                    if ( SIM_SUCCESS == XmlUtils::read( node_target_hit, temp ) )
                    {
                        m_target_hit = temp;
                    }
                }
            }
        }
    }
}
