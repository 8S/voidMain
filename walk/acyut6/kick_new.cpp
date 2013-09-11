#include <stdio.h>
#include "leg.h"
#include "communication.h"
#include <math.h>
#include "AcYut.h"

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

int main()
{
	Communication *comm=new Communication;
	AcYut bot(comm);
	
	float x,xr,y,yr,z,zr,phi;
	float t=0.2;
	int fps=60;
	int sleep=16666;
	
	for(int i=0;i<t*fps;i++)
	{
		x=scurve(390,380,i,t*fps);
		xr=x;
		
		y=0;
		yr=0;
		
		z=0;
		zr=0;
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
	t=0.5;
	for(int i=0;i<t*fps;i++)
	{
		x=380;
		xr=380;
		
		y=0;
		yr=0;
		
		z=scurve(0,75,i,t*fps);
		zr=-0.8*z;
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
	t=0.5;
	for(int i=0;i<t*fps;i++)
	{
		x=scurve(380,330,i,t*fps);
		xr=380;
		
		y=0;
		yr=0;
		
		z=75;
		zr=-60;
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
	t=0.5;
	for(int i=0;i<t*fps;i++)
	{
		phi=linear(0,10,i,t*fps);
		x=330;
		xr=380*cos(phi*3.14/180);
		
		y=0;
		yr=380*sin(phi*3.14/180);
		
		z=75;
		zr=-60;
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
	t=0.1;
	for(int i=0;i<t*fps;i++)
	{
		phi=linear(10,-10,i,t*fps);
		x=330;
		xr=380*cos(phi*3.14/180);
		
		y=0;
		yr=380*sin(phi*3.14/180);
		
		z=75;
		zr=-60;
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
	t=0.5;
	for(int i=0;i<t*fps;i++)
	{
		phi=linear(-10,0,i,t*fps);
		x=330;
		xr=380*cos(phi*3.14/180);
		
		y=0;
		yr=380*sin(phi*3.14/180);
		
		z=75;
		zr=-60;
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
	t=0.5;
	for(int i=0;i<t*fps;i++)
	{
		x=scurve(330,380,i,t*fps);;
		xr=380;
		
		y=0;
		yr=0;
		
		z=75;
		zr=-60;
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
	t=0.5;
	for(int i=0;i<t*fps;i++)
	{
		x=380;
		xr=380;
		
		y=0;
		yr=0;
		
		z=scurve(75,0,i,t*fps);
		zr=scurve(-60,0,i,t*fps);
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
	for(int i=0;i<t*fps;i++)
	{
		x=scurve(380,390,i,t*fps);
		xr=x;
		
		y=0;
		yr=0;
		
		z=0;
		zr=0;
		
		printf("\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t",x,xr,y,yr,z,zr);
		
		bot.right_leg->move(x,y,z,0);
		bot.left_leg->move(xr,yr,zr,0);
		comm->syncFlush();
		
		usleep(sleep);
	}
}