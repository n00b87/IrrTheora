# IrrTheora
A library for playing theora (*.ogg, *.ogv) videos in Irrlicht. It requires SDL2 and SDL2_Mixer.


## Reference ( Note: All functions are in the irrTheora namespace )

void init_irrTheora( IrrlichtDevice* device ) - Must be called before using the library

void loadVideo( string fname ) - Loads a video file ( Note: Currently, only one video can be loaded at a time )

int getVideoStats( std::string fname, double * v_len, double * v_fps, double * v_width, double * v_height ) - Gets the length, fps, and resolution of a video file  ( Note: This function is slow )

void getVideoSize( double * w, double * h ) - Gets the resolution of a video

void setVideoDrawRect( int x, int y, int w, int h ) - Sets the size of the rendered output

void getVideoDrawRect(double * x, double * y, double * w, double * h) - Gets the size of the rendered output

void playVideo( int loops, ITexture * t_video_tgt ) - Tells the library you want to start playing a video for the given loops.  t_video_tgt is the render target the video will play on.  ( Note: loops is the number of times to repeat the video after it finishes playing the first time so set it to 0 if you only want to play once. Set it to -1 if you want to play infinitely. )

void stopVideo() - You will never guess what this does  ;)

static bool updateVideo() - Must be called every frame to render the current video frame

void deleteVideo() - Frees the loaded video from memory

void pauseVideo() - Pauses the currently playing video

void resumeVideo() - Resumes a video if it is paused

void setVideoPosition(Uint32 vpos) - Jumps to vpos milliseconds in the current video

bool videoIsPlaying() - Returns true if video is currently playing

bool videoEnd() - Returns true if video has reached the end of its playback

bool videoExists() - Returns true if there is a video loaded
