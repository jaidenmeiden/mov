/**	Definition of the class Super Ship

	Class Prefix: CSJ_

	@author Jaiden Riaño
	@version 2021-01-07
*/


#ifndef CSJ_JAIDENMEIDEN
#define CSJ_JAIDENMEIDEN

#include <ExplosiveChar.h>
#include <SIMessage.h>

//Definitions for the game
#define CSJ_MAX_FILE_NAME		 25
#define CSJ_MAX_HEALTH			500 //Maximun amount of health of a given Supply Ship by default
#define CSJ_MAX_HIT_DURATION	500

#define CSJ_MAX_X_SHIFT			  4

#define CSJ_SHOOT_SPEED		  0.017f

/** \typedef CSJ_EXTRA_TIMERS

*	Types of different local timing managed by any supplyship
*/
typedef enum {
    CSJ_UPD_PERIOD,
    CSJ_RND_PERIOD,
    CSJ_MAX_TIMERS
} CSJ_EXTRA_TIMERS;

typedef enum {
    CSJ_NO_SUPPLY_SHIP, ///For management purpouses
    CSJ_SUPPLY_SHIP,
    CSJ_BIG_SUPPLY_SHIP,	//Super powerful supply ship. More health, bigger and can launch ships from inside. Only in 3D mode
    CSJ_MAXTYPE
} CSJ_TYPE;

///Artificial Intelligence
///Different states for the FSMs that control the SS behaviour
typedef enum {
    CSJ_UNBORN=0,	///For management purpouses only
    CSJ_BORN,		///The character is just born but it is not still operative (living)
    CSJ_LIVING,		///Everything this character may do while it is alive 
    CSJ_DYING,		///The character has been touched so many times that its life has gone negative. So it has to burst before being died. Starts an explosion and dies
    CSJ_DEAD,		///The character is no operative. Reached after dying
    CSJ_MAXSTATE	///For management purpouses only
} CSJ_JAIDENMEIDEN_STATE;	///Generic character possible states that can be any character by default

///Different transitions for the FSMs that control the SS behaviour
typedef enum {
    CSJ_DEFAULT=0,				///For management purpouses only
    CSJ_BORNING,				///The character is just borning. Passing from UNBORN to BORN states
    CSJ_GETTING_ALIVE,			///Passing from BORN to LIVING states
    CSJ_MOVING,					///Remaining in LIVING state while moving the Supply Ship
    CSJ_DISPLAYING,				///Remaining in LIVING state while displaying the Supply Ship
    CSJ_HEALTHING,				///Remaining in LIVING state while increasing the health of the Supply Ship
    CSJ_BURST,					///The character has been touched so many times that its life has gone negative. So it has to burst. Passing from LIVING to DYING states
    CSJ_DIE,					///The character is no operative. Reached after dying
    CSJ_FINISHED,				///The character is no operative. Reached after the game has finished: player has lost or win the level or game is exited
    CSJ_RESURRECTING,			///Passing to Unborn state
    CSJ_MAXTRANSITION			///For management purpouses only
} CSJ_JAIDENMEIDEN_TRANSITIONS;	///Generic character possible states that can be any character by default

///The ships that contains the captain of the enemy navy. They are moving over the whole navy. It has a different geometry
class CJaidenMeiden: public CExplosiveChar
{
    //Attributes
public:
    /// Type of supplyship
    CSJ_TYPE	SubType;
    ///When the ships loses its life, it burst. This is the particle system to perform the explosion

    //RT-DESK
    double		timeRTdeskMsg;		//Tiempo Mensaje RTDESK
    cMsgNavy	*msg;
    cMsgNavy	*msgUpd;			//RTDESK Message Time

    //Methods
    void Init ();

    //AI Methods
    ///Increasing health while time passes by
    void AI_Healthing	();
    ///Moving the Supply Ship
    void AI_Move		();
    ///The supply ship is going to burst before being dead
    void AI_Die			();
    ///What to do when the supply ship is dead
    void AI_Death		();
    bool OutEvent		(CSJ_JAIDENMEIDEN_TRANSITIONS EventName);

    //Physics
    void Collided		(CCharacter *CollidedChar);

    ///Shows the supplyship on the screen
    void Render				(void);
    ///Change the way the supplyship is going to be rendered on the screen
    void ChangeRenderMode	(CHAR_RENDER_MODE Mode);

    void Update(void);
    void DiscreteUpdate(void);

    void ReceiveMessage(RTDESK_CMsg *pMsg);

    ///Constructor of the class
    CJaidenMeiden();
    ~CJaidenMeiden(){}
};

//External methods to use with the class internal FSM
///Called everytime a time slot happens and its health has to be increased
void *CSJ_FSM_Healthing	(LPSTR *args, CJaidenMeiden *JaidenMeiden);
///Called everytime a time slot happens and a moving has to be done
void *CSJ_FSM_Move		(LPSTR *args, CJaidenMeiden *JaidenMeiden);
///Called when the supply ship is going to burst before dying
void *CSJ_FSM_Dye		(LPSTR *args, CJaidenMeiden *JaidenMeiden);
void *CSJ_FSM_Dying		(LPSTR *args, CJaidenMeiden *JaidenMeiden);
void *CSJ_FSM_Death		(LPSTR *args, CJaidenMeiden *JaidenMeiden);
///Called when the supply ship passed from death to unborn states
void *CSJ_FSM_Unborning (LPSTR *args, CJaidenMeiden *JaidenMeiden);
///ACHTUNG: Temporalmente. Cambiar en el futuro
void *CSJ_display		(LPSTR *args, CJaidenMeiden *JaidenMeiden);

#endif
