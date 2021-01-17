/**
 * @file	inc\UGKInterpolator.h
 *
 * @brief	Declares the interpolator class.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

#pragma once;

template < typename T >

/**
 * @class	UGKParticleInterpolator
 *
 * @brief	An interpolator.
 */

class UGKParticleInterpolator
{
public:

    /**
     * @typedef	std::map< float, typename T > Map
     *
     * @brief	Defines an alias representing the map.
     */

    typedef std::map< float, typename T > Map;

    /**
     * @typedef	typename Map::iterator Iterator
     *
     * @brief	Defines an alias representing the iterator.
     */

    typedef typename Map::iterator Iterator;

    /**
     * @typedef	typename Map::const_iterator ConstIterator
     *
     * @brief	Defines an alias representing the constant iterator.
     */

    typedef typename Map::const_iterator ConstIterator;

    UGKParticleInterpolator( const T& defaultValue = T() )
        : m_DefaultValue( defaultValue )
    {}  ///< .
    /**
     * @fn	void UGKParticleInterpolator::AddValue( float time, const T& value );
     *
     * @brief	Add a value at time into the graph.
     *
     * @param	time 	The time.
     * @param	value	The value.
     */

    void AddValue( float time, const T& value );

    /**
     * @fn	T UGKParticleInterpolator::GetValue( float time ) const;
     *
     * @brief	Get the interpolated value at time.
     *
     * @param	time	The time.
     *
     * @return	The value.
     */

    T GetValue( float time ) const;

protected:

private:
    Map m_Values;   ///< The values
    T   m_DefaultValue; ///< The default value
};

template< typename T >

/**
 * @fn	void UGKParticleInterpolator<T>::AddValue( float time, const T& value )
 *
 * @brief	Adds a value to 'value'.
 *
 * @tparam	T	Generic type parameter.
 * @param	time 	The time.
 * @param	value	The value.
 */

void UGKParticleInterpolator<T>::AddValue( float time, const T& value )
{
    m_Values[time] = value;
}

/**
 * @fn	template< typename T > T UGKParticleInterpolator<T>::GetValue( float time ) const
 *
 * @brief	Gets a value.
 *
 * @tparam	T	Generic type parameter.
 * @param	time	The time.
 *
 * @return	The value.
 */

template< typename T >
T UGKParticleInterpolator<T>::GetValue( float time ) const
{
    // Case 1. There are no elements
    if ( m_Values.size() < 1 ) return m_DefaultValue;
    // Case 2. There is exactly one element
    if ( m_Values.size() == 1 ) return m_Values.begin()->second;
    // Case 3. There are 2 or more elements

    // Search through the map, stop when we found values between time.
    ConstIterator iter0 = m_Values.begin();
    ConstIterator iter1 = iter0;

    while ( iter1 != m_Values.end() )
    {
        if ( iter1->first > time ) 
        {
            break;
        }
        iter0 = iter1;
        ++iter1;
    }
    
    if ( iter1 == m_Values.end() )
    {
        return iter0->second;
    }

    // Linear Interpolate between iter0 and iter1
    float t0 = iter0->first;
    float t1 = iter1->first;

    float ratio = ( time - t0 ) / ( t1 - t0 );

    const T& value0 = iter0->second;
    const T& value1 = iter1->second;

    return value0 * ( 1.0f - ratio ) + ( value1 * ratio );
}