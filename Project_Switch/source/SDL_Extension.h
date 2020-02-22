#pragma once
#include "SDL2/SDL.h"
class SDL_Extension
{
private:
	SDL_Extension() {}
	~SDL_Extension() {}
public:
	static int SDL_RenderPolygon(SDL_Renderer * renderer, const Sint16* vx, const Sint16* vy, int n)
	{
		int result;
		int i, nn;
		SDL_Point* points;
		if (vx == NULL)
			return -1;
		if (vy == NULL)
			return -1;


		nn = n;
		points = (SDL_Point*)malloc(sizeof(SDL_Point) * nn);
		if (points == NULL)
			return -1;
		for (i = 0; i < n; i++)
		{
			points[i].x = vx[i];
			points[i].y = vy[i];
		}
		//points[n].x = vx[0];
		//points[n].y = vy[0];

		result |= SDL_RenderDrawLines(renderer, points, nn);
		free(points);

		return result;
	}
	static int SDL_RenderArc(SDL_Renderer * renderer, int centerX, int centerY, int radius, int begin, int end)
	{
		double PI = 3.141592653589793;
		int result;
		double angle, start_angle, end_angle;
		double deltaAngle;
		double dr;
		int numPoints, i;
		Sint16 *vx, *vy;

		if (radius < 1)
			return -1;

		begin = begin % 360;
		end = end % 360;

		if (radius == 0)
			return SDL_RenderDrawPoint(renderer, centerX, centerY);
		
		dr = (double)radius;
		deltaAngle = 3.0 / dr;
		start_angle = (double)begin * (PI / 180.0);
		end_angle = (double)end * (PI / 180.0);
		if (begin > end)
		{
			end_angle += (2.0 * PI);
		}

		numPoints = 0;

		angle = start_angle;
		while (angle < end_angle)
		{
			angle += deltaAngle;
			numPoints++;
		}

		vx = vy = (Sint16 *)malloc(2 * sizeof(Uint16) * numPoints);

		if (vx == NULL)
		{
			return -1;
		}
		
		vy += numPoints;

		//vx[0] = centerX;
		//vy[0] = centerY;

		i = 0;
		angle = start_angle;
		while (angle < end_angle)
		{
			angle += deltaAngle;
			if (angle > end_angle)
			{
				angle = end_angle;
			}
			vx[i] = centerX + (int)(dr * cos(angle));
			vy[i] = centerY + (int)(dr * sin(angle));
			i++;
				
		}
		result = SDL_RenderPolygon(renderer, vx, vy, numPoints);
		free(vx);
		//https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
		return result;
	}
	static int SDL_RenderCircle(SDL_Renderer * renderer, int centerX, int centerY, int radius)
	{
		const int diameter = (radius * 2);

		int x = (radius - 1);
		int y = 0;
		int tx = 1;
		int ty = 1;
		int error = (tx - diameter);
		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			if (SDL_RenderDrawPoint(renderer, centerX + x, centerY - y) != 0)return -1;
			if (SDL_RenderDrawPoint(renderer, centerX + x, centerY + y) != 0)return -1;
			if (SDL_RenderDrawPoint(renderer, centerX - x, centerY - y) != 0)return -1;
			if (SDL_RenderDrawPoint(renderer, centerX - x, centerY + y) != 0)return -1;
			if (SDL_RenderDrawPoint(renderer, centerX + y, centerY - x) != 0)return -1;
			if (SDL_RenderDrawPoint(renderer, centerX + y, centerY + x) != 0)return -1;
			if (SDL_RenderDrawPoint(renderer, centerX - y, centerY - x) != 0)return -1;
			if (SDL_RenderDrawPoint(renderer, centerX - y, centerY + x) != 0)return -1;

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
		return 0;
	}
	
	static inline float ToRad(float deg)
	{
		return deg * 3.141592653589793 / 180;
	}
	
	static inline float ToDeg(float rad)
	{
		return rad / 3.141592653589793 * 180;
	}
};