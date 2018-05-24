#include "Debuginfo.h"
#include <GL/freeglut.h>
#include <string>
#include "GameObject.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include "collisionComponent.h"

#define WHITESPACE -120
#define DEBUG_STROKE    GLUT_STROKE_ROMAN

extern int FPS;
extern int width;		//dont proper resize
extern int height;
extern GameObject* player;
extern std::list<GameObject*> objects;
extern float flapspeed;
float fapspeed;

void draw_debug_display(bool on) {
	if (on){
		glTranslatef(width-(width/3.0f), -20.0f, 0.0f);		//some how 0 isnt up so used -20
		glScalef(.1f, -.1f, 1);
		debug_println("DEBUG\n");


		debug_println("PLAYER LOCATION:");
		std::string val = "";
		std::stringstream ss;

		ss << std::fixed << std::setprecision(1) << player->position.x;
		val.append("X: ");
		val.append(ss.str());

		std::stringstream().swap(ss);			//clear the string stream

		ss << std::fixed << std::setprecision(1) << player->position.y;
		val.append(" Y: ");
		val.append(ss.str());

		std::stringstream().swap(ss);			//clear the string stream

		ss << std::fixed << std::setprecision(1) << player->position.z;
		val.append(" Z: ");		
		val.append(ss.str());
		debug_println(val);


		debug_println("\nPLAYER ROTATION:");
		val = "";
		std::stringstream().swap(ss);			//clear the string stream

		ss << std::fixed << std::setprecision(1) << player->rotation.x;
		val.append("X: ");
		val.append(ss.str());

		std::stringstream().swap(ss);			//clear the string stream

		ss << std::fixed << std::setprecision(1) << player->rotation.y;
		val.append(" Y: ");
		val.append(ss.str());

		std::stringstream().swap(ss);			//clear the string stream

		ss << std::fixed << std::setprecision(1) << player->rotation.z;
		val.append(" Z: ");
		val.append(ss.str());
		debug_println(val);

		if (flapspeed > 0) { fapspeed = flapspeed; }
		val = "\nFAPSPEED: ";
		std::stringstream().swap(ss);			//clear the string stream
		ss << std::fixed << std::setprecision(1) << fapspeed;
		debug_println(val + ss.str());

		val = "\nFPS: ";
		val.append(std::to_string(FPS));
		debug_println(val);
	}
}

void debug_println(std::string s){
	unsigned char val[33];					//max 32 chars per line
	std::copy(s.begin(), s.end(), val);
	glutStrokeString(DEBUG_STROKE, val);
	glTranslatef(-glutStrokeLengthf(DEBUG_STROKE,val),WHITESPACE, 0);			//translate x back to the begining of string and y a whitespace down
}