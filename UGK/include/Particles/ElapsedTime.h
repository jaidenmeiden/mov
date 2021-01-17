// Helper class to count frame time

/**
 * @class	ElapsedTime
 *
 * @brief	An elapsed time.
 * 			
 * @author	Joaquin Taverner y Fran Munyoz
 * @date	25/02/2017
 */

class ElapsedTime
{
public:

    /**
     * @fn	ElapsedTime::ElapsedTime( float maxTimeStep = 0.03333f );
     *
     * @brief	Constructor.
     *
     * @param	maxTimeStep	(Optional) The maximum time step.
     */

    ElapsedTime( float maxTimeStep = 0.03333f );

    /**
     * @fn	float ElapsedTime::GetElapsedTime() const;
     *
     * @brief	Gets elapsed time.
     *
     * @return	The elapsed time.
     */

    float GetElapsedTime() const;

private:
    float m_fMaxTimeStep;   ///< The maximum time step

    /**
     * @property	mutable float m_fPrevious
     *
     * @brief	Gets the previous.
     *
     * @return	The m f previous.
     */

    mutable float m_fPrevious;
};
