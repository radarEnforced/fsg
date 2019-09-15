#ifndef SIM_SINGLETON_H
#define SIM_SINGLETON_H

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Singleton template class. */
template < class TYPE >
class Singleton
{
public:

    /** Instace accessor. */
    inline static TYPE* instance()
    {
        if ( !m_instance )
        {
            m_instance = new TYPE();
        }

        return m_instance;
    }

public:

    /** Destructor. */
    virtual ~Singleton() {}

protected:

    /** Constructor. */
    Singleton() {}

    /** Constructor. */
    Singleton( const Singleton & ) {}

private:

    static TYPE *m_instance;    ///< instance
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

template < class TYPE > TYPE* sim::Singleton< TYPE >::m_instance = 0;

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_SINGLETON_H
