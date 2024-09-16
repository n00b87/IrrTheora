#ifndef IRRTHEORA_H_INCLUDED
#define IRRTHEORA_H_INCLUDED

#include <iostream>
#include <irrlicht.h>
#include <SDL2/SDL_mixer.h>
#include "theoraplay.h"

namespace irrtheora
{

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

typedef struct AudioQueue
{
    const THEORAPLAY_AudioPacket *audio;
    int offset;
    struct AudioQueue *next;
} AudioQueue;

static volatile AudioQueue *audio_queue = NULL;
static volatile AudioQueue *audio_queue_tail = NULL;

THEORAPLAY_Decoder *decoder = NULL;
const THEORAPLAY_VideoFrame *t_video = NULL;
const THEORAPLAY_AudioPacket *t_audio = NULL;
ITexture * overlay = NULL;
ITexture * t_video_target = NULL;
void * overlay_pixels;
int pitch;
Uint32 framems = 0;
int initfailed = 0;
int quit = 0;
bool rc_video_isPlaying = false;
Uint32 rc_video_position = 0;
bool rc_video_reset = false;
int rc_video_loops = 0;
const THEORAPLAY_AudioPacket * first_audio = NULL;
const THEORAPLAY_VideoFrame * first_video = NULL;
bool rc_audio_isOpen = false;
bool rc_video_isLoaded = false;
std::string rc_video_file = "";
bool rc_video_isPaused = false;
Uint32 rc_video_pauseTicks = 0;
bool rc_video_end = false;
irr::core::rect<s32> rc_video_dstrect;
int rc_video_width = 0;
int rc_video_height = 0;
int rc_video_length = 0;
int rc_video_fps = 0;
int rc_video_currentLoop = 0;
irr::IrrlichtDevice* t_video_device;
static Uint32 baseticks = 0;

int video_volume = 128;

#ifdef RC_USE_TREMOR
void videoPlayer_audio_callback(void *userdata, Uint8 *stream, int len)
{
    // !!! FIXME: this should refuse to play if item->playms is in the future.
    //const Uint32 now = SDL_GetTicks() - baseticks;
    Sint16 *dst = (Sint16 *) stream;

    while (audio_queue && (len > 0))
    {
        volatile AudioQueue *item = audio_queue;
        AudioQueue *next = item->next;
        const int channels = item->audio->channels;

        const Sint32 *src = (Sint32 *) (item->audio->samples + (item->offset * channels));

        int cpy = (item->audio->frames - item->offset) * channels;
        int i;

        if (cpy > (len / sizeof (Sint16)))
            cpy = len / sizeof (Sint16);

        for (i = 0; i < cpy; i++)
        {
            const Sint32 val = *(src++);

            if (val < -32768)
                *(dst++) = -32768;
            else if (val > 32767)
                *(dst++) = 32767;
            else
            {
                *(dst++) = (Sint16) (val);
            }
        } // for

        item->offset += (cpy / channels);
        len -= cpy * sizeof (Sint16);

        if (item->offset >= item->audio->frames)
        {
            THEORAPLAY_freeAudio(item->audio);
            free((void *) item);
            audio_queue = next;
        } // if
    } // while

    if (!audio_queue)
        audio_queue_tail = NULL;

    if (len > 0)
        memset(dst, '\0', len);
} // audio_callback
#else
void videoPlayer_audio_callback(void *userdata, Uint8 *stream, int len)
{
    // !!! FIXME: this should refuse to play if item->playms is in the future.
    //const Uint32 now = SDL_GetTicks() - baseticks;
    Sint16 *dst = (Sint16 *) stream;

    float audio_vol = ( ((float)video_volume)/((float)MIX_MAX_VOLUME) ) * 32767.0f;

    while (audio_queue && (len > 0))
    {
        volatile AudioQueue *item = audio_queue;
        AudioQueue *next = item->next;
        const int channels = item->audio->channels;

        const float *src = item->audio->samples + (item->offset * channels);
        int cpy = (item->audio->frames - item->offset) * channels;
        int i;

        if (cpy > (len / sizeof (Sint16)))
            cpy = len / sizeof (Sint16);

        for (i = 0; i < cpy; i++)
        {
            const float val = *(src++);
            if (val < -1.0f)
                *(dst++) = -32768;
            else if (val > 1.0f)
                *(dst++) = 32767;
            else
                *(dst++) = (Sint16) (val * audio_vol);
        } // for

        item->offset += (cpy / channels);
        len -= cpy * sizeof (Sint16);

        if (item->offset >= item->audio->frames)
        {
            THEORAPLAY_freeAudio(item->audio);
            free((void *) item);
            audio_queue = next;
        } // if
    } // while

    if (!audio_queue)
        audio_queue_tail = NULL;

    if (len > 0)
        memset(dst, '\0', len);
} // audio_callback
#endif

static void videoPlayer_queue_audio(const THEORAPLAY_AudioPacket *audio)
{
    AudioQueue *item = (AudioQueue *) malloc(sizeof (AudioQueue));
    if (!item)
    {
        THEORAPLAY_freeAudio(audio);
        return;  // oh well.
    } // if

    item->audio = audio;
    item->offset = 0;
    item->next = NULL;

    //SDL_LockAudio();
    if (audio_queue_tail)
        audio_queue_tail->next = item;
    else
        audio_queue = item;
    audio_queue_tail = item;
    //SDL_UnlockAudio();
} // queue_audio

void init_irrTheora(irr::IrrlichtDevice* device)
{
    t_video_device = device;
}

void loadVideo(std::string fname)
{
    decoder = THEORAPLAY_startDecodeFile(fname.c_str(), 30, THEORAPLAY_VIDFMT_RGBA);
    if(!decoder)
    {
        decoder = NULL;
        std::cout << "Failed to load video: " << fname << std::endl;
        return;
    }

    rc_video_file = fname;
    while (!t_audio || !t_video)
    {
        if (!t_audio) t_audio = THEORAPLAY_getAudio(decoder);
        if (!t_video) t_video = THEORAPLAY_getVideo(decoder);
        t_video_device->sleep(10);
    }

    irr::video::IVideoDriver* driver = t_video_device->getVideoDriver();

    overlay = driver->addTexture(core::dimension2d<u32>(t_video->width, t_video->height), "THEORA_VIDEO");

    framems = (t_video->fps == 0.0) ? 0 : ((Uint32) (1000.0 / t_video->fps));
    rc_video_dstrect = irr::core::rect<s32>(irr::core::vector2d<s32>(0,0), irr::core::vector2d<s32>(t_video->width, t_video->height));
    rc_video_width = t_video->width;
    rc_video_height = t_video->height;

    if (!overlay)
    {
        std::cout << "Video failed: Could not create texture target" << std::endl;
        return;
    }

    initfailed = quit = (!overlay);
    rc_video_end = false;
}

int getVideoStats(std::string fname, double * v_len, double * v_fps, double * v_width, double * v_height)
{
    if(decoder)
        return 0;
    decoder = THEORAPLAY_startDecodeFile(fname.c_str(), 30, THEORAPLAY_VIDFMT_RGBA);
    if(!decoder)
    {
        decoder = NULL;
        std::cout << "Failed to load video: " << fname << std::endl;
        return 0;
    }

    while(THEORAPLAY_isDecoding(decoder))
    {
        if(!t_video)
            t_video = THEORAPLAY_getVideo(decoder);
        if(t_video)
        {
            rc_video_length = t_video->playms;
            rc_video_fps = t_video->fps;
            rc_video_width = t_video->width;
            rc_video_height = t_video->height;
            THEORAPLAY_freeVideo(t_video);
            t_video = NULL;
        }

        if(!t_audio)
            t_audio = THEORAPLAY_getAudio(decoder);
        if(t_audio)
        {
            THEORAPLAY_freeAudio(t_audio);
            t_audio = NULL;
        }

        //SDL_Delay(1);
    }

    THEORAPLAY_stopDecode(decoder);
    decoder = NULL;

    *v_len = rc_video_length;
    *v_fps = rc_video_fps;
    *v_width = rc_video_width;
    *v_height = rc_video_height;
    rc_video_length = 0;
    rc_video_fps = 0;
    rc_video_width = 0;
    rc_video_height = 0;
    return 1;
}

void getVideoSize(double * w, double * h)
{
    *w = rc_video_width;
    *h = rc_video_height;
}

void setVideoDrawRect(int x, int y, int w, int h)
{
    rc_video_dstrect = irr::core::rect(irr::core::vector2d<s32>(x,y), irr::core::dimension2d<u32>(w, h));
}

void getVideoDrawRect(double * x, double * y, double * w, double * h)
{
    *x = rc_video_dstrect.UpperLeftCorner.X;
    *y = rc_video_dstrect.UpperLeftCorner.Y;
    *w = rc_video_dstrect.getWidth();
    *h = rc_video_dstrect.getHeight();
}

void rc_cleanResume()
{
    if (t_video) THEORAPLAY_freeVideo(t_video);
    if (t_audio) THEORAPLAY_freeAudio(t_audio);
    if (decoder) THEORAPLAY_stopDecode(decoder);

    rc_video_isPlaying = false;
    t_video = NULL;
    t_audio = NULL;
    decoder = NULL;
    decoder = THEORAPLAY_startDecodeFile(rc_video_file.c_str(), 30, THEORAPLAY_VIDFMT_RGBA);
    while(!t_audio && !t_video && THEORAPLAY_isDecoding(decoder))
    {
        t_audio = THEORAPLAY_getAudio(decoder);
        t_video = THEORAPLAY_getVideo(decoder);
        if(t_audio)
        {
            if(t_audio->playms <= rc_video_pauseTicks)
            {
                THEORAPLAY_freeAudio(t_audio);
                t_audio = NULL;
            }
        }

        if(t_video)
        {
            if(t_video->playms <= rc_video_pauseTicks)
            {
                THEORAPLAY_freeVideo(t_video);
                t_video = NULL;
            }
        }
    }
}

void playVideo(int loops, ITexture * t_video_tgt)
{
    if(rc_video_isPlaying)
        return;
    if(rc_video_reset)
    {
        decoder = THEORAPLAY_startDecodeFile(rc_video_file.c_str(), 30, THEORAPLAY_VIDFMT_RGBA);
        if(!decoder)
        {
            std::cout << "Video Reset Error: Could not allocate decoder" << std::endl;
        }
        while(!t_audio || !t_video)
        {
            if(!t_audio) t_audio = THEORAPLAY_getAudio(decoder);
            if(!t_video) t_video = THEORAPLAY_getVideo(decoder);
            t_video_device->sleep(10);
        }
        rc_video_reset = false;
    }

    Mix_CloseAudio();
    rc_video_currentLoop = 0;
    rc_video_loops = loops;
    rc_video_isPlaying = true;

    if(Mix_OpenAudio(t_audio->freq, AUDIO_S16SYS, t_audio->channels, 2048) < 0)
    {
        rc_audio_isOpen = false;
        std::cout << "Open Audio Error: " << Mix_GetError() << std::endl;
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cout << "Open Audio Error: " << Mix_GetError() << std::endl;
        }
        quit = 1;
        return;
    }

    Mix_HookMusic(videoPlayer_audio_callback, NULL);

    rc_audio_isOpen = true;

    if(!rc_video_isLoaded)
    {
        while (t_audio)
        {
            videoPlayer_queue_audio(t_audio);
            t_audio = THEORAPLAY_getAudio(decoder);
        } // while
    }

    baseticks = t_video_device->getTimer()->getTime();
    rc_video_isLoaded = true;
    t_video_target = t_video_tgt;

    if (!quit)
        Mix_Pause(-1);
}

void stopVideo()
{
    if (t_video) THEORAPLAY_freeVideo(t_video);
    if (t_audio) THEORAPLAY_freeAudio(t_audio);
    if (decoder) THEORAPLAY_stopDecode(decoder);
    t_video_device->sleep(1500);

    rc_video_isPlaying = false;
    rc_video_loops = 0;
    rc_video_currentLoop = 0;
    rc_video_position = 0;
    rc_video_reset = true;
    rc_video_end = false;
    t_video = NULL;
    t_audio = NULL;
    decoder = NULL;
}

static bool updateVideo()
{
    if(!rc_video_isPlaying)
        return false;

    int isDecode = THEORAPLAY_isDecoding(decoder);
    if(isDecode)
        rc_video_end = false;
    else
    {
        rc_video_currentLoop++;
        if((rc_video_currentLoop <= rc_video_loops) || (rc_video_loops < 0))
        {
            stopVideo();
            playVideo(rc_video_loops, t_video_target);
            return true;
        }
        rc_video_end = true;
        rc_video_isPlaying = false;
    }

    if (!quit && isDecode)
    {
        const Uint32 now = t_video_device->getTimer()->getTime() - baseticks;
        rc_video_pauseTicks = now;
        rc_video_position = now;

        if (!t_video)
            t_video = THEORAPLAY_getVideo(decoder);

        // Play video frames when it's time.
        if (t_video && (t_video->playms <= now))
        {
            if ( framems && ((now - t_video->playms) >= framems) )
            {
                // Skip frames to catch up, but keep track of the last one
                //  in case we catch up to a series of dupe frames, which
                //  means we'd have to draw that final frame and then wait for
                //  more.
                const THEORAPLAY_VideoFrame *last = t_video;
                while ((t_video = THEORAPLAY_getVideo(decoder)) != NULL)
                {
                    THEORAPLAY_freeVideo(last);
                    last = t_video;
                    if ((now - t_video->playms) < framems)
                        break;
                } // while

                if (!t_video)
                    t_video = last;
            } // if

            overlay_pixels = overlay->lock(irr::video::ETLM_WRITE_ONLY);


            if (!t_video)  // do nothing; we're far behind and out of options.
            {
                static int warned = 0;
                if (!warned)
                {
                    warned = 1;
                    std::cout << "WARNING: Playback can't keep up!" << std::endl;
                } // if
            } // if
            else if (!overlay_pixels)
            {
                static int warned = 0;
                if (!warned)
                {
                    warned = 1;
                    std::cout << "Couldn't lock video frame" << std::endl;
                } // if
            } // else if
            else
            {
                const int w = t_video->width;
                const int h = t_video->height;
                Uint8 *dst;

                Uint8 * vbuf = (Uint8*)t_video->pixels;

                dst = (Uint8*)overlay_pixels;
                SDL_memcpy(dst, vbuf, w*h*4);

                if (t_video_target)
                {
                    // set render target texture
                    t_video_device->getVideoDriver()->setRenderTarget(t_video_target);
                    t_video_device->getVideoDriver()->draw2DImage(overlay, rc_video_dstrect, irr::core::rect<s32>(0,0,w,h));
                    t_video_device->getVideoDriver()->setRenderTarget(0, false, false);
                }
                else
                {
                    std::cout << "Could not display video frame: No render target set" << std::endl;
                }
            }

            overlay->unlock();

            THEORAPLAY_freeVideo(t_video);
            t_video = NULL;

        } // if
        else  // no new video frame? Give up some CPU.
        {
            t_video_device->sleep(10);
        } // else

        while ((t_audio = THEORAPLAY_getAudio(decoder)) != NULL)
            videoPlayer_queue_audio(t_audio);

        return true;
    } // while
    return false;

} // playfile

void deleteVideo()
{
    if(rc_video_isPlaying)
        stopVideo();

    if (overlay) t_video_device->getVideoDriver()->removeTexture(overlay);
        overlay = NULL;

    if (t_video) THEORAPLAY_freeVideo(t_video);
        t_video = NULL;

    if (t_audio) THEORAPLAY_freeAudio(t_audio);
        t_audio = NULL;

    if (decoder) THEORAPLAY_stopDecode(decoder);
        decoder = NULL;


    rc_video_file = "";
    rc_video_isLoaded = false;
    rc_video_isPlaying = false;
    rc_video_loops = 0;
    rc_video_position = 0;
    rc_video_length = 0;
    rc_video_width = 0;
    rc_video_height = 0;
    rc_video_dstrect = irr::core::rect(0,0,0,0);
}

void pauseVideo()
{
    //if(rc_video_isPaused)
    //    return;
    rc_video_isPlaying = false;
    if (t_video) THEORAPLAY_freeVideo(t_video);
    if (t_audio) THEORAPLAY_freeAudio(t_audio);
    Mix_Pause(-1);
    t_video_device->sleep(1500);

    if(rc_audio_isOpen)
    {
        Mix_CloseAudio();
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            std::cout << "OpenAudio Error: " << Mix_GetError() << std::endl;
        }
        rc_audio_isOpen = false;
    }
    t_video = NULL;
    t_audio = NULL;
    rc_video_isPaused = true;
}

void resumeVideo()
{
    if(!rc_video_isPaused)
        return;


    int dec_cycle = 0;

    while(!t_audio || !t_video)
    {
        if(!t_audio) t_audio = THEORAPLAY_getAudio(decoder);
        if(!t_video) t_video = THEORAPLAY_getVideo(decoder);
        t_video_device->sleep(10);

        dec_cycle++;
        if(dec_cycle == 100)
            rc_cleanResume();
        if(dec_cycle >= 200)
        {
            rc_video_isPaused = false;
            stopVideo();
            return;
        }
    }

    if(!rc_audio_isOpen)
        Mix_CloseAudio();
    rc_video_isPlaying = true;

    if(!rc_audio_isOpen)
    {
        if(Mix_OpenAudio(t_audio->freq, AUDIO_S16SYS, t_audio->channels, 2048) < 0)
        {
            std::cout << "Open Audio Error: " << Mix_GetError() << std::endl;
            if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                std::cout << "OpenAudio Error: " << Mix_GetError() << std::endl;
            }
            quit = 1;
            return;
        }
        rc_audio_isOpen = true;
    }

    if(!rc_video_isLoaded)
    {
        while (t_audio)
        {
            videoPlayer_queue_audio(t_audio);
            t_audio = THEORAPLAY_getAudio(decoder);
        } // while
    }

    baseticks = t_video_device->getTimer()->getTime() - rc_video_pauseTicks;
    rc_video_isLoaded = true;
    rc_video_isPaused = false;

    if (!quit)
        Mix_Pause(-1);

}

Uint32 videoPosition()
{
    return rc_video_position;
}

void setVideoPosition(Uint32 vpos)
{
    bool is_playing = rc_video_isPlaying;
    if(is_playing) pauseVideo();
    rc_video_pauseTicks = vpos;
    rc_video_position = vpos;
    if(is_playing) resumeVideo();
}

bool videoIsPlaying()
{
    return rc_video_isPlaying;
}

bool videoEnd()
{
    return rc_video_end;
}

bool videoExists()
{
    if(decoder)
        return true;
    return false;
}

void setVideoVolume(int vol)
{
	if(vol < 0)
		return;

	if(vol > 128)
		video_volume = 128;
	else
		video_volume = vol;
}

int getVideoVolume()
{
	return video_volume;
}


} // namespace irrtheora

#endif // IRRTHEORA_H_INCLUDED
