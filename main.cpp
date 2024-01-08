#include <iostream>
#include <irrlicht/irrlicht.h>
#include "irrtheora.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


int main()
{
    IrrlichtDevice *device =
        createDevice( video::EDT_OPENGL, dimension2d<u32>(720, 480), 16,
            false, false, false, 0);

    if (!device)
        return 1;

    device->setWindowCaption(L"Theora Video Playback in Irrlicht");

    IVideoDriver* driver = device->getVideoDriver();

    //irrTheora needs a render target to output the video to
    ITexture* video_target = 0;
    if(driver->queryFeature(video::EVDF_RENDER_TO_TARGET))
    {
        video_target = driver->addRenderTargetTexture(core::dimension2d<u32>(720,480), "THEORA_VIDEO");
    }


    //Initialize irrTheora
    irrtheora::init_irrTheora(device);

    //Load a video
    irrtheora::loadVideo("bunny.ogg");

    //Set the video as playing for 0 loops and have it render to video_target
    irrtheora::playVideo(0, video_target);

    while(device->run())
    {
        //updateVideo() will query the next frame of the video until the video is done playing the specified number of loops (0 will play the video once)
        irrtheora::updateVideo();

        driver->beginScene(true, true, SColor(255,100,101,140));


        driver->draw2DImage(video_target, irr::core::position2d<s32>(0, 0));

        driver->endScene();

        //videoEnd() returns true when the video is done playing
        if(irrtheora::videoEnd())
            break;

    }

    //deleteVideo() will free up the memory used by the video playback
    irrtheora::deleteVideo();

    device->drop();

    return 0;
}
