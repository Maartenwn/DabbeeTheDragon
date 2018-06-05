#define _USE_MATH_DEFINES

#include "Debuginfo.h"
#include <GL/freeglut.h>
#include <string>
#include "GameObject.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include "collisionComponent.h"
#include <math.h>

#define WHITESPACE 120
#define DEBUG_STROKE    GLUT_STROKE_ROMAN

int Camindx = 0;
extern bool keys[256];
extern Vec3f cameraOffset;
extern Vec3f fpsCamOff;
extern int FPS;
extern int width;		//dont proper resize
extern int height;
extern GameObject* player;
extern std::list<GameObject*> objects;
extern float flapspeed;
float fapspeed;
Vec3f cameraoffsets[6] = { Vec3f(0, 0, 0), Vec3f(-5, 5, 3), Vec3f(-10, 0, 0), Vec3f(0, -1, 3),  Vec3f(-12, -1, 3), Vec3f(0,0,10)};

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
		if (keys['0']) { Camindx = 0; }
		if (keys['1']) { Camindx = 1; }
		if (keys['2']) { Camindx = 2; }
		if (keys['3']) { Camindx = 3; }						//first person view
		if (keys['4']) { Camindx = 4; }						//side view
		if (keys['5']) { Camindx = 5; }						
		debug_println("CAMERA: " + std::to_string(Camindx));

		cameraOffset = cameraoffsets[Camindx];
		if (3 == Camindx) {		//first person
			float z = sin(player->rotation.x * (M_PI / 180) + M_PI/4) * 2.3f;
			float y = cos(player->rotation.x * (M_PI / 180) + M_PI/4) * 2.3f;
			cameraOffset.y += y;
			cameraOffset.z += z;
			fpsCamOff = cameraOffset;
			fpsCamOff.y += y;
			fpsCamOff.z += z;
		}
		else {
			fpsCamOff = Vec3f(0, 0, 0);
		}

		if (keys['r']) { 
			player->position = Vec3f(0, 0, 0);
			keys[' '] = true;
		}	//should be a decent rest function
	} 
	else { Camindx = 0; }
}

void debug_println(std::string s){
	unsigned char val[33];					//max 32 chars per line
	std::copy(s.begin(), s.end(), val);
	glColor3f(1.0f, 1.0f, 1.0f);
	glDisable(GL_LIGHTING);
	glutStrokeString(DEBUG_STROKE, val);
	glTranslatef(-glutStrokeLengthf(DEBUG_STROKE,val),-WHITESPACE, 0);			//translate x back to the begining of string and y a whitespace down
	glEnable(GL_LIGHTING);

}