#ifndef FPS_HPP_INCLUDED
#define FPS_HPP_INCLUDED

Time thetime;
Clock elapsed;

string IntToString(int d)
{
    stringstream ss;
    ss << d;
    return ss.str();
}

string GetFrameRate()
{
    static int frameCounter = 0;
    static int fps = 0;
    frameCounter++;
    thetime = elapsed.getElapsedTime();
    if(thetime.asMilliseconds() > 999)
    {
        fps = frameCounter;
        frameCounter = 0;
        elapsed.restart();
    }

    return IntToString(fps);
}
#endif
