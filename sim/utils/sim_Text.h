#ifndef SIM_TEXT_H
#define SIM_TEXT_H

////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>

#include <sim/sim_Types.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Text class. */
class Text
{
public:

    typedef std::map< UInt8, std::string > Strings;

    /** Default constructor. */
    Text();

    /** Cppy constructor. */
    Text( const Text &text );

    /** Destructor. */
    virtual ~Text();

    void append( const char *str );

    void append( const std::string &str );

    void append( const Text &text );

    /** */
    std::string get() const;

    /** */
    void set( UInt8 index, const std::string &str );

private:

    Strings m_strings;
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_TEXT_H
