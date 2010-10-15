/**
 *   Based on code from instructables.com 4x4x4 cube
 *   4x4x4 LED Cube project By Christian Moen 2008 (chr@syntaks.org)
 */ 


// Launches one of those fancy effects.
void launch_effect (int effect) {
  if (buttonPressed) return;
  
  switch (effect) {
    // Lights all the layers one by one
  case 0:
    loadbar(150);
    break;

    // A pixel bouncing randomly around
  case 1:
    // blink
    boingboing(150,75,0x03,0x01);
    break;

    // Randomly fill the cube
    // Randomly empty the cube
  case 2:
    fill(0x00);
    random_filler(150,1,75,1);
    if (buttonPressed) return;
    random_filler(150,1,75,0);
    break;

    // Send voxels randomly back and forth the Z axis
  case 3:
    sendvoxels_rand_z(150,75,300);
    break;

    // Spinning spiral
  case 4:
    effect_spiral(1,75,150);
    break;

    // A coordinate bounces randomly around the cube
    // For every position the status of that voxel is toggled.
  case 5:
    // toggle
    boingboing(150,75,0x03,0x02);
    break;

    // Random raindrops
  case 6:
    effect_rain(20,50,150,60);
    break;

    // A snake randomly bounce around the cube.
  case 7:
    // snake
    boingboing(150,125,0x03,0x03);
    break;

    // Spinning plane
  case 8:
    effect_spinning_plane(1,50,150);
    break;

    // set x number of random voxels, delay, unset them.
    // x increases from 1 to 20 and back to 1.
  case 9:
    random_2();
    break;

    // Set all 64 voxels in a random order.
    // Unset all 64 voxels in a random order.
  case 10:
    random_filler2(75,1);
    if (buttonPressed) return;
    delay(300);
    random_filler2(75,0);
    delay(150);
    break;

    // bounce a plane up and down all the directions.
  case 11:
    flyplane('z',1,150);
    delay(500);
    flyplane('y',1,150);
    delay(500);
    flyplane('x',1,150);
    delay(500);
    flyplane('z',0,150);
    delay(500);
    flyplane('y',0,150);
    delay(500);
    flyplane('x',0,150);
    delay(500);
    break;

    // Fade in and out at low framerate
  case 12:
    blinky2();
    break;

  case 13:
    sendplane_rand_z(0,100,100);
    if (buttonPressed) return;
    delay(1000);
    sendplane_rand_z(4,100,100);
    break;
  }
}

