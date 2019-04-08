#include "game.h"
#include "utils.h"
#include "input.h"
#include "image.h"

#include <cmath>

Game* Game::instance = NULL;
Stage* currentstage = NULL;

Image font;
Image sprite;
Image test;
Color bgcolor(130, 80, 100);

Vector2 pos(0,0);
Vector2 camerapos2(0, 0);

Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	currentstage = new StartStage();
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;

	font.loadTGA("data/bitmap-font-white.tga"); //load bitmap-font image
	sprite.loadTGA("data/Monk.tga"); //example to load an sprite
	test.loadTGA("data/test.tga");

	//enableAudio(); //enable this line if you plan to add audio to your application
	//synth.playSample("data/coin.wav",1,true);
	//synth.osc1.amplitude = 0.5;
}

//what to do when the image has to be draw
void Game::render(void)
{
	//Create a new Image (or we could create a global one if we want to keep the previous frame)
	//Image framebuffer(128, 128); //do not change framebuffer size
	currentstage->render();
	Image framebuffer = currentstage->getFrameBuffer();
	//add your code here to fill the framebuffer
	//...

	//some new useful functions
		//framebuffer.fill( bgcolor );								//fills the image with one color
		//framebuffer.drawLine( 0, 0, 100,100, Color::RED );		//draws a line
		//framebuffer.drawImage( sprite, 0, 0 );					//draws full image
		//framebuffer.drawImage( sprite, 0, 0, 128, 128 );			//draws a scaled image

		//framebuffer.drawImage(test, -450- camerapos2.x, -450- camerapos2.y);
		//framebuffer.drawImage( sprite, int(pos.x-camerapos2.x), int(pos.y-camerapos2.y), Area(0,0,14,18) );	//draws only a part of an image
		//framebuffer.drawRectangle(0, 0, 128, 20, Color::GRAY);


		//framebuffer.drawText( "Hello World", 0, 0, font );				//draws some text using a bitmap font in an image (assuming every char is 7x9)
		//framebuffer.drawText( toString(time), 1, 10, minifont,4,6);	//draws some text using a bitmap font in an image (assuming every char is 4x6)

	//send image to screen
	showFramebuffer(&framebuffer);
}

//void Game::render(Stage* &s) {
//	showFramebuffer(&s->getFrameBuffer());
//}

void Game::update(double seconds_elapsed)
{
	currentstage->update(elapsed_time,time);

	//Read the keyboard state, to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (Input::isKeyPressed(SDL_SCANCODE_UP)) //if key up
	{
		currentstage->updatePlayerPosition(seconds_elapsed, Vector2(0, -1),3);
		//pos.y -= elapsed_time * 20;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_DOWN)) //if key down
	{
		currentstage->updatePlayerPosition(seconds_elapsed, Vector2(0, 1),0);

		//pos.y += elapsed_time * 20;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_RIGHT)) {
		currentstage->updatePlayerPosition(seconds_elapsed, Vector2(1,0),1);

		//pos.x += elapsed_time * 20;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_LEFT)) {
		currentstage->updatePlayerPosition(seconds_elapsed, Vector2(-1,0),2);

		//pos.x -= elapsed_time * 20;
	}

	//example of 'was pressed'
	if (Input::wasKeyPressed(SDL_SCANCODE_A)) //if key A was pressed
	{
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_Z)) //if key Z was pressed
	{
		currentstage->medMode();
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_X)) {
		currentstage->pickItem();
	}

	//to read the gamepad state
	if (Input::gamepads[0].isButtonPressed(A_BUTTON)) //if the A button is pressed
	{
	}

	if (Input::gamepads[0].direction & PAD_UP) //left stick pointing up
	{
		bgcolor.set(0, 255, 0);
	}
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
		case SDLK_n: SwapStages(); break; // Change the stages
		case SDLK_h:
			std::cout << currentstage->getPlayerPosition() << std::endl;
			break;
		case SDLK_r:
			currentstage = new StartStage();
			break;

	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onMouseMove(SDL_MouseMotionEvent event)
{
}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	window_width = width;
	window_height = height;
}

void Game::SwapStages() {
	switch (currentstage->getType()) {
		case 0:
			currentstage = new InstructStage();
			break;
		case 1:
			currentstage = new PlayStage(128,128);
			break;

	}
}

//sends the image to the framebuffer of the GPU
void Game::showFramebuffer(Image* img)
{
	static Image finalframe;

	if (window_width < img->width * 4 || window_height < img->height * 4)
	{
		finalframe = *img;
		finalframe.scale( window_width, window_height );
	}
	else
	{
		if (finalframe.width != window_width || finalframe.height != window_height)
		{
			finalframe.resize(window_width, window_height);
			finalframe.fill(Color::BLACK);
		}
		finalframe.drawImage(*img, (window_width - img->width * 4) * 0.5, (window_height - img->height * 4) * 0.5, img->width * 4, img->height * 4);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (1) //flip
	{
		glRasterPos2f(-1, 1);
		glPixelZoom(1, -1);
	}

	glDrawPixels(finalframe.width, finalframe.height, GL_RGBA, GL_UNSIGNED_BYTE, finalframe.pixels);
}

//AUDIO STUFF ********************

SDL_AudioSpec audio_spec;

void AudioCallback(void*  userdata,
	Uint8* stream,
	int    len)
{
	static double audio_time = 0;

	memset(stream, 0, len);//clear
	if (!Game::instance)
		return;

	Game::instance->onAudio((float*)stream, len / sizeof(float), audio_time, audio_spec);
	audio_time += len / (double)audio_spec.freq;
}

void Game::enableAudio()
{
	SDL_memset(&audio_spec, 0, sizeof(audio_spec)); /* or SDL_zero(want) */
	audio_spec.freq = 48000;
	audio_spec.format = AUDIO_F32;
	audio_spec.channels = 1;
	audio_spec.samples = 1024;
	audio_spec.callback = AudioCallback; /* you wrote this function elsewhere. */
	if (SDL_OpenAudio(&audio_spec, &audio_spec) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}
	SDL_PauseAudio(0);
}

void Game::onAudio(float *buffer, unsigned int len, double time, SDL_AudioSpec& audio_spec)
{
	//fill the audio buffer using our custom retro synth
	synth.generateAudio(buffer, len, audio_spec);
}
