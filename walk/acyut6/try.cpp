#include <stdio.h>
#include "leg.h"
#include "communication.h"
#include <math.h>
#include "AcYut.h"
#include <signal.h>

bool quit = false;

void doquit(int para)
{
	quit = true;
}

float scurve(float in,float fi,float t, float tot)
{
	float frac=(float)t/(float)tot;
	if(frac>1)
	frac=1;
	float retfrac=frac*frac*(3-2*frac);
	float mval=in + (fi-in)*retfrac;
	return mval;
}

float linear(float in,float fi,float t, float tot)
{
	if(t>=0&&t<=tot)
	return in*(1-t/tot)+fi*(t/tot);
	else if(t<0)
	return in;
	else
	return fi;
}


void moveTo(Leg* leg, Communication &comm, float fx, float fy, float fz, float ftheta)
{
	float totalTime = 2;
	float fps = 60;
	float x = 390, y = 0, z = 0, theta = 0;
	for(float t = 0.0; t < totalTime; t += 1/fps)
	{
		x = scurve(390, fx, t, totalTime);
		y = scurve(0, fy, t, totalTime);
		z = scurve(0, fz, t, totalTime);
		theta = scurve(0, ftheta, t, totalTime);
		printf("Going to %f %f %f %f\n", x, y, z, theta);
		leg->move(x, y, z, theta);
		comm.syncFlush();
		usleep(1000000.0/fps);
	}
}

float xleft, yleft, zleft;
float xright, yright, zright;

void moveBoth(AcYut &bot, Communication &comm, float fx1, float fy1, float fz1, float fx2, float fy2, float fz2, float totalTime = 1)
{
	float fps = 60;
	float x1 = xleft, y1 = yleft, z1 = zleft;
	float x2 = xright, y2 = yright, z2 = zright;
	for(float t = 0.0; t < totalTime; t += 1/fps)
	{
		x1 = scurve(xleft, fx1, t, totalTime);
		y1 = scurve(yleft, fy1, t, totalTime);
		z1 = scurve(zleft, fz1, t, totalTime);
		printf("Left: Going to %f %f %f\n", x1, y1, z1);
		bot.left_leg->move(x1, y1, z1, 0);

		x2 = scurve(xright, fx2, t, totalTime);
		y2 = scurve(yright, fy2, t, totalTime);
		z2 = scurve(zright, fz2, t, totalTime);
		printf("Right: Going to %f %f %f\n", x2, y2, z2);
		bot.right_leg->move(x2, y2, z2, 0);
		comm.syncFlush();
		usleep(1000000.0/fps);
	}
	xleft = x1;
	xright = x2;
	yleft = y1;
	yright = y2;
	zleft = z1;
	zright = z2;
}


int main()
{
	(void) signal(SIGINT,doquit);
	Communication comm;
	AcYut bot(&comm);
	xleft = xright = 390;
	yleft = yright = zleft = zright = 0;
	// moveTo(bot.right_leg, comm, 390, 0, 20, 10);
	// moveTo(bot.left_leg, comm, 390, 0, 20, 10);
	// return 0;
	// bot.right_leg->move(390,10,0,0);
	// bot.left_leg->move(390,0,0,0);
	// comm.syncFlush();
	// moveTo(bot.left_leg, comm, 390, 0, -80);
	// moveTo(bot.right_leg, comm, 350, 40, 80);
	//zright + yright should always be greater than some number (50? 60?)
	moveBoth(bot, comm, xleft, yleft, 25, xright, yright, 25);

	double z = 25;
	double t = 0;
	double fps = 60;
	double x;
	double MUL = 7.5;
	double PI = 3.1415926535;
	double TP = 2*PI/MUL;
	double xstart = TP*0.5*0.3333;
	double xend = TP*0.5*0.6666;
	double ystart = TP*0.5*0.4;
	double yend = TP*0.5*0.6;
	double y = 0;
	// t = 0;
	t = TP/2;
	while(1)
	{
		z = 25*sin((t)*MUL);
		double thalf;
		double signMult;
		if(t < TP/2)
		{
			thalf = t;
			signMult = 1.0;
		}
		else
		{
			thalf = t - TP/2;
			signMult = -1.0;
		}

		if(thalf < xstart || thalf > xend)
		{
			x = 0;
		}
		else
		{
			//to change direction of turning, change y from 1 leg to another and change > to < or vice versa
			x = 40*sin((thalf - xstart)*PI/((xend-xstart)))*signMult;
			if(signMult > 0)
				y = 2*sin((thalf - xstart)*PI/(2*(xend-xstart)));
			else
				y = 2 - 2*sin((thalf - xstart)*PI/(2*(xend-xstart)));
		}
	

		double yreal = -7*sin((t+PI/2)*MUL);
		// y = 6*sin((t)*MUL - PI/2) + 6;

		// if(thalf < ystart || thalf > yend)
		// 	y = 0;
		// else
		// 	y = 20*sin((thalf - ystart)*PI/((yend-xstart)))*signMult;
	
		t = t + 1/fps;
		if(t > TP)
			t = t - TP;
		printf("y = %lf\n", y);
		double x1, x2;
		if(x > 0)
		{
			x1 = 390 - x;
			x2 = 390;
		}
		else
		{
			x1 = 390;
			x2 = 390 + x;
		}
		// bot.right_leg->move(x1, -y, z+5,0);
		// bot.left_leg->move(x2, y, -z+5,0);
		bot.right_leg->move(x1, yreal, z+25,y);
		bot.left_leg->move(x2, -yreal, -z+25,0);
		comm.syncFlush();
		usleep(1000000/fps);
		if(quit && fabs(z) < 0.1)
			break;
	}
	printf("Quit\n");
	return 0;

	
}