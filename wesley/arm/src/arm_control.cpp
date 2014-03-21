/* arm_control.cpp
 * written by: Eric Gonzalez, Sarah Withee
 * date: 2014-01-18
 *
 * PURPOSE: Define and describe a control interface for the robotic arm
 *
 * TODO:
 * - give [Eric] a visual representation of the arms co-ordinate frame; which 
 *   way are the axes oriented. From this, I should be able to position the claw 
 *   as needed by issuing simple move_to(x, y, z, p) calls.
 *   (This is in person, not in code, but we still need to do it)      
 * - alter put(byte, byte) and p_put(byte, short) to work correctly.
 * - add in angle limits so that if anything goes beyond the range of the 
 *   allowed pulse widths it defaults to the min or max pulse width 
 *   appropriately.
 * - need a forward kinematic.
 *   -- sadly, this [Eric] did not add this in to the re-written code so you'll 
 *      need to find an old copy.
 * - Move internal 'helper' functions to private area
 * - Remove extraneous commented out code
 * - Make any 'magic' numbers precompiler constants for optimization
 *     
 */


// Remove Arduino.h if compiling with gcc or avr-gcc. Leave in if compiling
// with Arduino IDE
#include <Arduino.h>
#include <Servo.h>
#include "arm_control.h"

// Print debug info or not, comment out for not
//#define DEBUG

// Converts angle to pulse width for writing to a servo
#define topulse(a)     map(a, 0,  180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH)

// Values in millimeters
#define BASE_HGT 69.85      // base hight 2 3/4"
#define HUMERUS 146.05      // shoulder-to-elbow 5 3/4"
#define ULNA 215.9          // elbow-to-wrist 8 1/2"
#define GRIPPER 88.9        // gripper length 3 1/2"
                            // this gripper measure is to the outside
                            // screw-hole, not the tip of the hand.

// Park values...  update in one place for both initial_park() and park()
#define PARK_BASE     1368;		//  80°
#define PARK_SHOULDER 2245;		// 165°
#define PARK_ELBOW    600;		// 5.5°
#define PARK_WRIST_P  544;		//   0°
#define PARK_WRIST_R  1523;		//  95°
#define PARK_HAND     1472;		//  90°



// Define the delay length
#define TIMER_DELAY 5

// squares of certain lengths for later calculations
float hum_sq = HUMERUS*HUMERUS;
float uln_sq = ULNA*ULNA;




/* arm_control()
 * Constructor
 * PRE:
 * POST:
 */                         
arm_control::arm_control() {
	no_of_joints = 6;
	p_position = new short[no_of_joints];
	p_destination = new short[no_of_joints];
	arm = new Servo[no_of_joints];
	
	for (byte joint = 0; joint < no_of_joints; joint++) {
		p_destination[joint] = 0;
		p_position[joint] = 0;
	}
}


/* arm_control(byte joints)
 * Parameterized constructor
 * PRE:
 * POST:
 */                         
arm_control::arm_control(byte joints) {
	no_of_joints = joints;
	p_position = new short[no_of_joints];
	p_destination = new short[no_of_joints];
	arm = new Servo[no_of_joints];
	
	for (byte joint = 0; joint < no_of_joints; joint++) {
		p_destination[joint] = 0;
		p_position[joint] = 0;
	}
}


/* ~arm_control()
 * Deconstructor
 * PRE:
 * POST:
 */                         
arm_control::~arm_control() {
	delete(p_destination);
	delete(p_position);
	delete(arm);
}


/* void connect(byte argc, ...) {
 * Attaches a set of pins to the servos
 * PRE:
 * POST:
 */                         
void arm_control::connect(byte argc, ...) {
//	Serial.println("ARM :: connect --> entering");
	va_list argv;
	va_start(argv, argc);

	int pin = 0;
	for (byte joint = 0; joint < argc; joint++) {
		pin = va_arg(argv, int);
		arm[joint].attach(pin);
		p_position[joint] = arm[joint].readMicroseconds();
//		Serial.print("\tjoint("); Serial.print(joint, DEC);
//		Serial.print(") at ("); Serial.print(p_position[joint]);
//		Serial.println(")");
	}

	va_end(argv);
//	Serial.println("ARM :: connect --> leaving");
}


/* void initial_park()
 * This needs to be called immediately after connect.
 * this sets the arm into a sane, locked position.
 * these values can be adjusted as necessary.
 * PRE:
 * POST:
 */                         
void arm_control::initial_park() {
#ifdef DEBUG
//	Serial.println("ARM :: park() --> entering");
	Serial.flush();
#endif
	/* here, define, in pulse, what angles to place the
	 *    servos at. these will then be moved below */
	p_position[BASE] 	 = PARK_BASE;
	p_position[SHOULDER] = PARK_SHOULDER;
	p_position[ELBOW]	 = PARK_ELBOW;
	p_position[WRIST_P]	 = PARK_WRIST_P;
	p_position[WRIST_R]	 = PARK_WRIST_R;
	p_position[HAND]	 = PARK_HAND;
	
	/* for testing purposes, this will proceed in order
	 *    and directly place the successive joints at
	 *    the prescribed angle defined above.
	 * the ORDER in which these are placed is not set in
	 *    stone. it may prove useful in the future to set
	 *    a specific order. something like: 5 3 4 0 2 1 */
	for (byte joint = 0; joint < no_of_joints; joint++) {
		arm[joint].writeMicroseconds(p_position[joint]);
	}
}
	

/* void park()
 * Puts the arm in a good resting (parked) position
 * PRE:
 * POST:
 */                         
void arm_control::park() {
#ifdef DEBUG
//	Serial.println("ARM :: park() --> entering");
	Serial.flush();
#endif
	/* here, define, in pulse, what angles to place the
	 *    servos at. these will then be moved below */
	p_position[BASE] 	 = PARK_BASE;
	p_position[SHOULDER] = PARK_SHOULDER;
	p_position[ELBOW]	 = PARK_ELBOW;
	p_position[WRIST_P]	 = PARK_WRIST_P;
	p_position[WRIST_R]	 = PARK_WRIST_R;
	p_position[HAND]	 = PARK_HAND;
	
	/* for testing purposes, this will proceed in order
	 *    and directly place the successive joints at
	 *    the prescribed angle defined above.
	 * the ORDER in which these are placed is not set in
	 *    stone. it may prove useful in the future to set
	 *    a specific order. something like: 5 3 4 0 2 1 */
//	for (byte joint = 0; joint < no_of_joints; joint++) {
//		arm[joint].writeMicroseconds(p_destination[joint]);
//	}
	
	update();
//	Serial.println("ARM :: park() --> leaving");
//	Serial.flush();
}



/* void carry()
 * This puts the arm in a good position to carry a tool as the bot 
 * drives around. Wrist will point up.
 * PRE:
 * POST:
 */                         
void arm_control::carry() {
#ifdef DEBUG
	Serial.println("ARM :: carry() --> entering");
	Serial.flush();
#endif
	// here, define a secondary park location to use
	//    while carrying a tool.
	p_destination[BASE] 	= 1368;
	p_destination[SHOULDER]	= 2245;
	p_destination[ELBOW]	= 600;
	p_destination[WRIST_P]	= 2348;
	p_destination[WRIST_R]	= 544;
	p_destination[HAND]		= 1472;

	update();
#ifdef DEBUG
	Serial.println("ARM :: carry() --> leaving");
	Serial.flush();
#endif
}



/* byte read(const byte joint)
 * Returns the angle value of the servo
 * PRE:
 * POST:
 */                         
byte arm_control::read(const byte joint) {
	return arm[joint].read();
}



/* void p_put(const byte joint, short pulse)
 * Directly write a pulse to the servo, would take the place of the 
 * function put (byte, byte)         
 * PRE:
 * POST:
 */                         
void arm_control::p_put(const byte joint, short pusle) {
    // TODO
}



/* void put(const byte joint, const byte angle)
 * Directly put the given joint to the given angle,
 * converting first to pulse width
 * PRE:
 * POST:
 */                         
void arm_control::put(const byte joint, const byte angle) {
	// this function currently writes the pulse to the motor
	//    from a given angle. this should translate the angle
	//    and pass both joint and pulse to the above p_put().
	arm[joint].writeMicroseconds(topulse(angle));
	p_position[joint] = arm[joint].readMicroseconds();
}



/* void update(const byte arc, ...)
 * Call update with update(NO_OF_JOINTS, <a list of joints to mov
 * PRE:
 * POST:
 */                           
void arm_control::update() {
#ifdef DEBUG
	Serial.println("ARM :: update(...) --> entering");
	Serial.flush();
#endif
	// destroy the argument list - we're done.
	
//	short* step = new short[argc];
	short step[no_of_joints];
	// this is likely unneccessary.
	// clean up a new array
	for (byte jth = 0; jth < no_of_joints; jth++) {
		step[jth] = 0;
	}
#ifdef DEBUG
	Serial.println("ARM :: update(...) --> step cleared");
	Serial.flush();
#endif
	// find the width of the distance for each joint to be moved
	short max_distance = 0;
	for (byte jth = 0; jth < no_of_joints; jth++) {
		step[jth] = abs(p_destination[jth] - p_position[jth]);
		if (step[jth] > max_distance) {
			max_distance = step[jth];
		}
	}
#ifdef DEBUG
	Serial.println("ARM :: update(...) --> disatnce found");
	Serial.flush();
#endif

	// calculate the step value for each other moving joint
	for (byte jth = 0; jth < no_of_joints; jth++) {
		step[jth] = (step[jth] / (max_distance / 10));
#ifdef DEBUG
		Serial.print("\tstep: [");
		Serial.print(step[jth], DEC);
		Serial.println("]");
#endif
	}

	// lower the number of movement steps that will be taken
	max_distance /= 10;
	for (; max_distance > 0; max_distance--) {
		for (byte jth = 0; jth < no_of_joints; jth++) {
			// adjust position in the correct direction.
			// if dest > position,
			//    position increases
			// else
			//    position descreses
			//
			// this is due to the arc of movement is absolute
			//    from 0 to 180
			//    or 544 to 2400
			if (p_position[jth] != p_destinationp[jth]) {
				p_position[jth] = p_destination[jth] > p_position[jth] ?
						  p_position[jth] += step[jth] :
						  p_position[jth] -= step[jth] ;
				// write this change to the servo.
				// this should be changed to p_put
				arm[jth].writeMicroseconds(p_position[jth]);
				delay(TIMER_DELAY);
			}
		}
	}

	// run through the joints one more time and directly put
	//    them to their final position in case any came up
	//    short after the above step cucles.
	for (byte joint = 0; joint < no_of_joints; joint++) {
		arm[joint].writeMicroseconds(p_destination[joint]);
	}

	//*/
#ifdef DEBUG
	Serial.println("ARM :: update(...) --> leaving");
	Serial.flush();
#endif
}



/* void move_to( float x, float y, float z, float grip_angle_d, bool moveSmooth = true )
 * Places at (x, y, z) - this is an inverse kinematic
 *    equation that translates the (x, y, z) into
 *    angualr measures from an origin defined at the
 *    base of the arm.
 * PRE:
 * POST:
 */                  
void arm_control::move_to( float x, float y, float z, float grip_angle_d, bool moveSmooth)
{
    /* this function is borrowed from:
     * http://www.circuitsathome.com/mcu/robotic-arm-inverse-kinematics-on-arduino
     * which, conincedentilelery is the same arm as the one we have
     */

#ifdef DEBUG
	Serial.print("ARM :: put(xyz) --> (");
	Serial.print(x), Serial.print(", ");
	Serial.print(y), Serial.print(", ");
	Serial.print(z), Serial.print(") ");
	Serial.print(grip_angle_d); Serial.println();
#endif

	//grip angle in radians for use in calculations
	float grip_angle_r = radians( grip_angle_d );    
	/* Base angle and radial distance from x,y coordinates */
	float bas_angle_r = atan2( x, y );
	float rdist = sqrt(( x * x ) + ( y * y ));
	/* rdist is y coordinate for the arm */
	y = rdist;
	/* Grip offsets calculated based on grip angle */
	float grip_off_z = ( sin( grip_angle_r )) * GRIPPER;
	float grip_off_y = ( cos( grip_angle_r )) * GRIPPER;
	/* Wrist position */
	float wrist_z = ( z - grip_off_z ) - BASE_HGT;
	float wrist_y = y - grip_off_y;
	/* Shoulder to wrist distance ( AKA sw ) */
	float s_w = ( wrist_z * wrist_z ) + ( wrist_y * wrist_y );
	float s_w_sqrt = sqrt( s_w );
	/* s_w angle to ground */
	//float a1 = atan2( wrist_y, wrist_z );
	float a1 = atan2( wrist_z, wrist_y );
	/* s_w angle to humerus */
	float a2 = acos((( hum_sq - uln_sq ) + s_w ) / ( 2 * HUMERUS * s_w_sqrt ));
	/* shoulder angle */
	float shl_angle_r = a1 + a2;
	float shl_angle_d = degrees( shl_angle_r );
	/* elbow angle */
	float elb_angle_r = acos(( hum_sq + uln_sq - s_w ) / ( 2 * HUMERUS * ULNA ));
	float elb_angle_d = degrees( elb_angle_r );
//	float elb_angle_dn = -( 180.0 - elb_angle_d );
	/* wrist angle */
//	float wri_angle_d = grip_angle_d;// ( grip_angle_d - elb_angle_d ) - shl_angle_d;
	float wri_angle_d = ( wrist_pitch_d + 90 + ( 180 - (shl_angle_d + elb_angle+d )))

	/* Servo pulses */
//	float bas_servopulse = 1500.0 - (( degrees( bas_angle_r )) * 11.11 );
//	float shl_servopulse = 1500.0 + (( shl_angle_d - 90.0 ) * 6.6 );
//	float elb_servopulse = 1500.0 -  (( elb_angle_d - 90.0 ) * 6.6 );
//	float wri_servopulse = 1500 + ( wri_angle_d  * 11.1 );

	/* Set Servos, using arm*
	put(BASE, degrees(bas_angle_r) );
	put(WRIST_P, wri_angle_d );
	put(SHOULDER, shl_angle_d );
	put(ELBOW, elb_angle_d );
	//*/
	
	// update the pulse_destination array and then prepare
	//    to call update 

    // Move smoothly or not
    if(moveSmooth)
    {
    	p_destination[BASE] = topulse(degrees(bas_angle_r));
    	p_destination[WRIST_P] = topulse(wri_angle_d);
    	p_destination[SHOULDER] = topulse(shl_angle_d);
    	p_destination[ELBOW] = topulse(elb_angle_d);
        update();
    }
    else
    {
        put(BASE, degrees(bas_angle_r));
        put(SHOULDER, shl_angle_d);
        put(WRIST_P, wri_angle_d);
        put(ELBOW, elb_angle_d);
        
    }
	
}

// EOF

struct point getxyz() {
// this function should return the XYZ position of the arm.
// do we worry about the roll of the wrist? shouldn't have to.
//    the point of consideration lies along the wrists roll axis.
//	Serial.println("ARM :: getxyz() --> entering");
	double  cosB,  sinB;
	double hcosS, hsinS, sumofpiecesX;
	double ucosE, usinE, sumofpiecesY;
	double gcosW, gsinW, sumofpiecesZ;

	int B = arm[BASE].read();					double B_r = radians(B);
	int S = arm[SHOULDER].read();				double S_r = radians(S);
//	int E = -(169 - S - arm[ELBOW].read());		double E_r = radians(E);
	int E = -(180 - S - arm[ELBOW].read());		double E_r = radians(E);
	int W = -(90 - arm[WRIST_P].read() - E);	double W_r = radians(W);

	cosB = cos(B_r);
	sinB = sin(B_r);

	// x and y components of various bones
	hcosS = HUMERUS * cos(S_r);
	ucosE = ULNA * cos(E_r);
	gcosW = GRIPPER * cos(W_r);

	// z components
	hsinS = HUMERUS * sin(S_r);
	usinE = ULNA * sin(E_r);
	gsinW = GRIPPER * sin(W_r);

	sumofpiecesX = cosB * (hcosS + ucosE + gcosW);
	sumofpiecesY = sinB * (hcosS + ucosE + gcosW);
	sumofpiecesZ = BASE_HGT + hsinS + usinE + gsinW;

	struct point pillow(-sumofpiecesX, sumofpiecesY, sumofpiecesZ);

	return(pillow);
}
