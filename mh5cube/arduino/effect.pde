/**
 *   Based on code from instructables.com 4x4x4 cube
 *   4x4x4 LED Cube project By Christian Moen 2008 (chr@syntaks.org)
 */ 

#include <avr/pgmspace.h>

// 6 frame animation of line spinning around the center of the cube
// the animation is in 2 dimensions.
prog_uchar  spinning_line[6][2] PROGMEM = {
	{ 0x84, 0x21 },
	{ 0x0c, 0x30 },
	{ 0x03, 0xc0 },
	{ 0x12, 0x48 },
	{ 0x22, 0x44 },
	{ 0x44, 0x22 },
};

// Shows an animation of a spinning spiral
// delay in milliseconds
void effect_spiral(int direction, int iterations, int delayTime) {
      fill(0x0);

	for (int i=0;i<iterations;i++)
	{
		// Loop cube levels
		for (int z=0;z<5;z++)
		{
			// Read the animation from program memory and put it in the cube buffer.
			// y=0 and y=2 is stored in the upper nibble of the byte, and must be bitshifted into place.
			cube[z][0] = (pgm_read_byte(&spinning_line[(i+z)%6][0]) >> 4);
			cube[z][1] = pgm_read_byte(&spinning_line[(i+z)%6][0]);
			cube[z][2] = (pgm_read_byte(&spinning_line[(i+z)%6][1]) >> 4);
			cube[z][3] = pgm_read_byte(&spinning_line[(i+z)%6][1]);
			cube[z][4] = pgm_read_byte(&spinning_line[(i+z)%6][1]);
			// the +z makes the animation iterate one step for each plane
			// making it into a spiral
		}
		delay(delayTime);
	}
}

// Shows an animation of a spinning plane.
// delay in milliseconds
void effect_spinning_plane(int direction, int iterations, int delayTime)
{
	int i;
	int z;		// cube level

	for (i=0;i<iterations;i++)
	{
		// Loop cube levels.
		for (z=0;z<5;z++)
		{
			cube[z][0] = (pgm_read_byte(&spinning_line[(i)%6][0]) >> 4);
			cube[z][1] = pgm_read_byte(&spinning_line[(i)%6][0]);
			cube[z][2] = (pgm_read_byte(&spinning_line[(i)%6][1]) >> 4);
			cube[z][3] = pgm_read_byte(&spinning_line[(i)%6][1]);
			cube[z][4] = pgm_read_byte(&spinning_line[(i)%6][1]);
		}
		delay(delayTime);
	}
}

// Random voxels light up at the top layer and falls to the bottom layer.
// delay in milliseconds
// hold in milliseconds
void effect_rain (int iterations, int delayTime, int hold, int speed)
{
	int i;
	int p;		// Position of the raindrop on Z
	int z;		// cube layer
	int y;		// byte
	
	fill(0x00);
	
	for (i = 0; i < iterations; i++)
	{
		// Start by setting a random pixel on layer 0.
		setled(rand()%5,rand()%5,0);
		delay(hold);
		
		// The raindrop has to step down one layer 4 times
		// in order to travel from the top, and exit out the bottom.
		for (p=1;p<5;p++)
		{
			// Shift all the layers one position down,
			for (z=4;z>0;z--)
			{
				for (y=0;y<5;y++)
				{
					cube[z][y] = cube[z-1][y];
				}
			}
			
			// and a blank image on the top layer.
			cube[0][0] = 0x00;
			cube[0][1] = 0x00;
			cube[0][2] = 0x00;
			cube[0][3] = 0x00;
			cube[0][4] = 0x00;
			
			// Accelerate the raindrop as it falls.
			// (speed/p) will decrease as p increases.
			delay(speed+(speed/p));
		}
		
		fill(0x00);
		delay(delayTime);
	}
}

// Send a voxel flying from one side of the cube to the other
// It its at the bottom, send it to the top..
// delay in milliseconds
void sendvoxel_z (unsigned char x, unsigned char y, unsigned char z, int delayTime) {
    int ii;
	for (int i=0; i<5; i++)
	{
		if (z == 4)
		{
			ii = 4-i;
			clearled(x,y,ii+1);
		} else
		{
			ii = i;
			clearled(x,y,ii-1);
		}
		setled(x,y,ii);
		delay(delayTime);
	}
}

// Send all the voxels from one side of the cube to the other
// Start at z and send to the opposite side.
// Sends in random order.
// wait in milliseconds
// delay in milliseconds
void sendplane_rand_z (unsigned char z, int delayTime, int wait)
{
	unsigned char loop = 25;
	unsigned char x, y;

	fill(0x00);

	setplane_z(z);
	
	// Send voxels at random untill all 16 have crossed the cube.
	while(loop)
	{
		x = rand()%5;
		y = rand()%5;
		if (getled(x,y,z))
		{
			// Send the voxel flying
			sendvoxel_z(x,y,z,delayTime);
			delay(wait);
			loop--; // one down, loop-- to go. when this hits 0, the loop exits. 
		}
	}
}

// For each coordinate along X and Y, a voxel is set either at level 0 or at level 4
// for n iterations, a random voxel is sent to the opposite side of where it was.
// wait in milliseconds
// delay in milliseconds
void sendvoxels_rand_z (int iterations, int delayTime, int wait) {
	unsigned char x, y, last_x, last_y, i;

	fill(0x00);

	// Loop through all the X and Y coordinates
	for (x=0;x<5;x++)
	{
		for (y=0;y<5;y++)
		{
			// Then set a voxel either at the top or at the bottom
			if (rand()%2 == 0)
			{
				setled(x,y,0);
			} else
			{
				setled(x,y,4);
			}
		}
	}

	for (i=0;i<iterations;i++)
	{
		// Pick a random x,y position
		x = rand()%5;
		y = rand()%5;
		// but not the sameone twice in a row
		if (y != last_y && x != last_x)
		{
			// If the voxel at this x,y is at the bottom
			if (getled(x,y,0))
			{
				// send it to the top
				sendvoxel_z(x,y,0,delayTime);
			} else
			{
				// if its at the top, send it to the bottom
				sendvoxel_z(x,y,4,delayTime);
			}
			delay(wait);
			
			// Remember the last move
			last_y = y;
			last_x = x;
		}
	}

}

// Set n number of voxels at random positions
// delay in milliseconds
void random_1 (int iterations, int voxels, int delayTime)
{
	int i;
	int v;
	for (i = 0; i < iterations; i++)
	{
		for (v=0;v<=voxels;v++)
			setled(rand()%5,rand()%5,rand()%5);
			
		delay(delayTime);
		fill(0x00);
	}
}

// blink 1 random voxel, blink 2 random voxels..... blink 20 random voxels
// and back to 1 again.
void random_2 (void)
{
	int i;
	
	for (i=1;i<50;i++)
	{
		random_1(5,i,75);
	}
	
	for (i=50;i>=1;i--)
	{
		random_1(5,i,75);
	}
	
}

// Randomly fill or empty the cube with n voxels.
// delay in milliseconds
void random_filler (int iterations, int pixels, int delayTime, int state) {
	for (int i = 0; i < iterations; i++) {
		for (int p=0;p<=pixels;p++) {
			alterled(rand()%5,rand()%5,rand()%5,state);
                }
			
		delay(delayTime);
	}
}

// Set or clear exactly 64 voxels in a random order.
void random_filler2 (int delayTime, int state) {
	int x,y,z;
	int loop = 0;
	
	while (loop<124)
	{
		x = rand()%5;
		y = rand()%5;
		z = rand()%5;

		if ((state == 0 && getled(x,y,z) == 0x01) || (state == 1 && getled(x,y,z) == 0x00))
		{
			alterled(x,y,z,state);
			delay(delayTime);
			loop++;
		}	
	}
}


// Light all leds layer by layer,
// then unset layer by layer
// delay in milliseconds
void loadbar(int delayTime)
{
	fill(0x00);
	
	for (int z=0;z<5;z++) {
		for (int y=0;y<5;y++) {
			cube[z][y] = 0xff;
		}	
		delay(delayTime);
	}
	
	delay(delayTime*3);
	
	for (int z=0;z<5;z++) {
		for (int y=0;y<5;y++) {
			cube[z][y] = 0x00;
		}	
		delay(delayTime);
	}
}

//delay in milliseconds
void flyplane (unsigned char plane,unsigned char direction, int delayTime)
{
	int i,ii;
	
	fill(0x00);
	
	for (i=0;i<5;i++)
	{
		if (direction != 0)
		{
			ii = 4-i;
		} else
		{
			ii = i;
		}
		
		setplane(plane,ii,1);
		delay(delayTime);
		setplane(plane,ii,0);
	}
	
	for (i=2;i>=0;i--)
	{
		if (direction != 0)
		{
			ii = 4-i;
		} else
		{
			ii = i;
		}
		
		setplane(plane,ii,1);
		delay(delayTime);
		setplane(plane,ii,0);
	}
}

void blinky()
{
	int a;

	fill(0x00);
	delay(2000);
	
	for (a=0;a<3;a++)
	{
		fill(0xff);
		delay(50);
		fill(0x00);
		
		delay(1500);
		
		fill(0xff);
		delay(30);
		fill(0x00);
		
		delay(7000);
	}
	
	
}

void blinky2()
{
	int i,r;
	fill(0x00);
	
	for (r=0;r<2;r++)
	{
		i = 750;
		while (i>0)
		{
			fill(0x00);
			delay(i);
			
			fill(0xff);
			delay(100);
			
			i = i - (15+(1000/(i/10)));
		}
		
		delay(1000);
		
		i = 750;
		while (i>0)
		{
			fill(0x00);
			delay(751-i);
			
			fill(0xff);
			delay(100);
			
			i = i - (15+(1000/(i/10)));
		}
	}

}



// Big ugly function :p but it looks pretty
// delay in milliseconds
void boingboing(uint16_t iterations, int delayTime, unsigned char mode, unsigned char drawmode)
{
	fill(0x00);		// Blank the cube

	int x, y, z;		// Current coordinates for the point
	int dx, dy, dz;	// Direction of movement
	int lol, i;		// lol?
	unsigned char crash_x, crash_y, crash_z;

	// Coordinate array for the snake.
	int snake[5][3];
	for (i=0;i<5;i++)
	{
		snake[i][0] = 0;
		snake[i][1] = 0;
		snake[i][2] = 0;
	}
	
	y = rand()%5;
	x = rand()%5;
	z = rand()%5;
	
	dx = 1;
	dy = 1;
	dz = 1;
	
	while(iterations)
	{
		crash_x = 0;
		crash_y = 0;
		crash_z = 0;
	

		// Let's mix things up a little:
		if (rand()%3 == 0)
		{
			// Pick a random axis, and set the speed to a random number.
			lol = rand()%3;
			if (lol == 0)
				dx = rand()%3 - 1;
			
			if (lol == 1)
				dy = rand()%3 - 1;
				
			if (lol == 2)
				dz = rand()%3 - 1;
		}

	
		if (dx == -1 && x == 0)
		{
			crash_x = 0x01;
			if (rand()%3 == 1)
			{
				dx = 1;
			} else
			{
				dx = 0;
			}
		}
		
		if (dy == -1 && y == 0)
		{
			crash_y = 0x01;
			if (rand()%3 == 1)
			{
				dy = 1;
			} else
			{
				dy = 0;
			}
		}
		
		if (dz == -1 && z == 0)
		{
			crash_z = 0x01;
			if (rand()%3 == 1)
			{
				dz = 1;
			} else
			{
				dz = 0;
			}
		}
			
		if (dx == 1 && x == 4)
		{
			crash_x = 0x01;
			if (rand()%3 == 1)
			{
				dx = -1;
			} else
			{
				dx = 0;
			}
		}
		
		if (dy == 1 && y == 4)
		{
			crash_y = 0x01;
			if (rand()%3 == 1)
			{
				dy = -1;
			} else
			{
				dy = 0;
			}
		}
		
		if (dz == 1 && z == 4)
		{
			crash_z = 0x01;
			if (rand()%3 == 1)
			{
				dz = -1;
			} else
			{
				dz = 0;
			}
		}
		
		// mode bit 0 sets crash action enable
		if (mode | 0x01)
		{
			if (crash_x)
			{
				if (dy == 0)
				{
					if (y == 4)
					{
						dy = -1;
					} else if (y == 0)
					{
						dy = +1;
					} else
					{
						if (rand()%2 == 0)
						{
							dy = -1;
						} else
						{
							dy = 1;
						}
					}
				}
				if (dz == 0)
				{
					if (z == 4)
					{
						dz = -1;
					} else if (z == 0)
					{
						dz = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dz = -1;
						} else
						{
							dz = 1;
						}
					}	
				}
			}
			
			if (crash_y)
			{
				if (dx == 0)
				{
					if (x == 4)
					{
						dx = -1;
					} else if (x == 0)
					{
						dx = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dx = -1;
						} else
						{
							dx = 1;
						}
					}
				}
				if (dz == 0)
				{
					if (z == 4)
					{
						dz = -1;
					} else if (z == 0)
					{
						dz = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dz = -1;
						} else
						{
							dz = 1;
						}
					}	
				}
			}
			
			if (crash_z)
			{
				if (dy == 0)
				{
					if (y == 4)
					{
						dy = -1;
					} else if (y == 0)
					{
						dy = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dy = -1;
						} else
						{
							dy = 1;
						}
					}	
				}
				if (dx == 0)
				{
					if (x == 4)
					{
						dx = -1;
					} else if (x == 0)
					{
						dx = 1;
					} else
					{
						if (rand()%2 == 0)
						{
							dx = -1;
						} else
						{
							dx = 1;
						}
					}	
				}
			}
		}
		
		// mode bit 1 sets corner avoid enable
		if (mode | 0x02)
		{
			if (	// We are in one of 8 corner positions
				(x == 0 && y == 0 && z == 0) ||
				(x == 0 && y == 0 && z == 3) ||
				(x == 0 && y == 4 && z == 0) ||
				(x == 0 && y == 4 && z == 4) ||
				(x == 4 && y == 0 && z == 0) ||
				(x == 4 && y == 0 && z == 4) ||
				(x == 4 && y == 4 && z == 0) ||
				(x == 4 && y == 4 && z == 4) 				
			)
			{
				// At this point, the voxel would bounce
				// back and forth between this corner,
				// and the exact opposite corner
				// We don't want that!
			
				// So we alter the trajectory a bit,
				// to avoid corner stickyness
				lol = rand()%3;
				if (lol == 0)
					dx = 0;
				
				if (lol == 1)
					dy = 0;
					
				if (lol == 2)
					dz = 0;
			}
		}
	
		// Finally, move the voxel.
		x = x + dx;
		y = y + dy;
		z = z + dz;
		
		if (drawmode == 0x01) // show one voxel at time
		{
			setled(x,y,z);
			delay(delayTime);
			clearled(x,y,z);	
		} else if (drawmode == 0x02) // flip the voxel in question
		{
			flipled(x,y,z);
			delay(delayTime);
		} if (drawmode == 0x03)
		{
			for (i=4;i>=0;i--)
			{
				snake[i][0] = snake[i-1][0];
				snake[i][1] = snake[i-1][1];
				snake[i][2] = snake[i-1][2];
			}
			snake[0][0] = x;
			snake[0][1] = y;
			snake[0][2] = z;
				
			for (i=0;i<5;i++)
			{
				setled(snake[i][0],snake[i][1],snake[i][2]);
			}
			delay(delayTime);
			for (i=0;i<5;i++)
			{
				clearled(snake[i][0],snake[i][1],snake[i][2]);
			}
		}
		
	
		iterations--;
	}
}
