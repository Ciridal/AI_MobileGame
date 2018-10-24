#include <SDL.h>

int main(int argc, char **argv)
{
	SDL_Window      *window;
	SDL_Renderer    *renderer;
	SDL_Surface     *surface;
	SDL_Texture     *texture;

	window = SDL_CreateWindow("hello world", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	if (window == NULL)
		return 1;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		return 2;

	surface = SDL_LoadBMP("player.bmp");
	if (surface == NULL)
		return 3;

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		return 4;

	SDL_FreeSurface(surface);

	bool running = true;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
			else if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_ESCAPE)
					running = false;
		}
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_Rect src = { 0, 0, 64, 64 };
		SDL_Rect dst = { 368, 268, 64, 64 };
		SDL_RenderCopy(renderer, texture, &src, &dst);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}