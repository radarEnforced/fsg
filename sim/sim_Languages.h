#ifndef SIM_LANGUAGES_H
#define SIM_LANGUAGES_H

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <sim/sim_Types.h>

#include <sim/utils/sim_Singleton.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** */
class Languages : public sim::Singleton< Languages >
{
    friend class sim::Singleton< Languages >;

public:

    typedef std::vector< std::string > List;

private:

    /** Default constructor. */
    Languages();

    /** Copy constructor. */
    Languages( const Languages & ) : sim::Singleton< Languages >() {}

public:

    /** Destructor. */
    virtual ~Languages();

    /** */
    inline UInt8 getCurrent() const { return m_current; }

    /** */
    inline UInt8 getDefault() const { return m_default; }

    /** */
    std::string getCodeByIndex( UInt8 index ) const;

    /** */
    int getIndexByCode( const std::string &code ) const;

    /** */
    inline unsigned int getCount() const { return m_list.size(); }

    /** */
    bool isCodeValid( const std::string &code ) const;

    /** */
    void setCurrent( UInt8 current );

private:

    List m_list;        ///< supported languages list

    UInt8 m_current;    ///< current language index
    UInt8 m_default;    ///< default language index

    void readLanguages();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_LANGUAGES_H
