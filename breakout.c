//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// height and width of paddle
#define P_HEIGHT 10
#define P_WIDTH 40

// height and width of brick
#define B_HEIGHT 10
#define B_WIDTH 30

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
 
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initial velocity on Y axis
    double velocity_Y = 2;
    // random velocity of X axis
    double velocity = drand48() * 2;
   

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {            
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
            
        // if mouse event
        if (event != NULL)
        {
            // allows paddle to follow mouse
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle)/2;
                double y = 500;
                setLocation(paddle, x, y);
            }      
        }
        
        // moves ball
        move(ball, velocity, velocity_Y);
            
        // slows down ball
        pause(10);
            
        // causes ball to bounce off right side
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity = -velocity;
        }
            
        // causes ball to bounce off left side
        if (getX(ball) <= 0)
        {
            velocity = -velocity;
        }
            
        // causes ball to ball off top
        if (getY(ball) <= 0)
        {
            velocity_Y = -velocity_Y;
        }
            
        // if ball hits bottom 
        if(getY(ball) + + getHeight(ball) > getY(paddle)+ P_HEIGHT)
        {
            lives--;
            setLocation(ball,200, 300);
               
            waitForClick();
                    
        }
            
        // detects if ball hits paddle or brick
        GObject object = detectCollision(window, ball);
        
         
        // if ball hits paddle
        if (object == paddle)
        {
            velocity_Y = -velocity_Y;
        }
              
        if (object !=NULL)
        {    
            
            // if ball hits brick
            if (strcmp(getType(object), "GRect") == 0  && object != paddle)
            {
                // removes brick
                removeGWindow(window, object);
                // changes direction of ball
                velocity_Y = -velocity_Y;
                    
                // subtracts total # of bricks
                bricks--;
                // increases points
                points++;
                // scoreboard
                updateScoreboard(window, label, points);
            }  
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int x = 9;
    int y = 10;
    string colors[ROWS] = {"BLUE", "GREEN", "YELLOW", "ORANGE", "RED"};
    
    // creates rows
    for (int i = 1; i <= ROWS; i++)
    {
        // creates columns
        for (int j = 1; j <= COLS; j++)
        {
            // creates brick and sets color by row
            GRect brick = newGRect(x, y, B_WIDTH, B_HEIGHT);
            setFilled(brick, true);
            setColor(brick, colors[i - 1]);
            add(window, brick);
            
            // updates x to position new columns
            x = x + B_WIDTH + 9;
        }
        
        // sets x back to column 1
        x = 9;
        // updates y to position new rows
        y = y + B_HEIGHT + 10;      
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // creates ball and adds to center of window
    GOval ball = newGOval((WIDTH/2) - RADIUS, (HEIGHT/2) - RADIUS, RADIUS, RADIUS);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // creates paddle and adds to window 
    GRect paddle = newGRect((WIDTH - P_WIDTH)/2, HEIGHT - 50, P_WIDTH, P_HEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // creates label for score
    GLabel label = newGLabel("");
    setFont(label, "SanSerif-36");
    setColor(label, "RED");
    add(window, label);
    setLocation(label, 250, 250);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
