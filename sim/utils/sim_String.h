#ifndef SIM_STRING_H
#define SIM_STRING_H

////////////////////////////////////////////////////////////////////////////////

#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Text string utilities class. */
class String
{
public:

    /**
     * Compares strings. This function is case insensitive.
     * @param str_1 1st string to compare
     * @param str_2 2nd string to compare
     * @return integer result of the comparison (returns 0 if strings are equal)
     */
    static int icompare( const std::string &str_1, const std::string &str_2 );

    /**
     * Returns string with leading white spaces removed.
     * @param str string to be processed
     * @return string with leading white spaces removed
     */
    static std::string stripLeadingSpaces( const std::string &str );

    /** Converts string into variable. */
    static bool toBool( const std::string &str );

    /** Converts string into variable. */
    static int toInt( const std::string &str );

    /** Converts string into variable. */
    static float toFloat( const std::string &str );

    /** Converts variable into string. */
    static std::string toString( int value );

    /** Converts variable into string. */
    static std::string toString( float value );

    /** Converts wide string into string. */
    static std::string toString( const std::wstring &str );

    /** Converts string to lower case. */
    static std::string toLower( const std::string &str );

    /** Converts wide string to lower case. */
    static std::wstring toLower( const std::wstring &str );

    /** Converts string to upper case. */
    static std::string toUpper( const std::string &str );

    /** Converts wide string to upper case. */
    static std::wstring toUpper( const std::wstring &str );

    /** Converts string to wide string. */
    static std::wstring toWideString( const char *str );

    /** Converts string to wide string. */
    static std::wstring toWideString( const std::string &str );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_STRING_H
