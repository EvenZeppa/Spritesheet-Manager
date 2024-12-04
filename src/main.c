#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <BOX/BOX.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

SDL_Color	color_red()
{
	SDL_Color	color_red = {255, 0, 0, 255};
	return (color_red);
}

BOX_Margin	margin_10()
{
	BOX_Margin	margin_10 = {10, 10, 10, 10};
	return (margin_10);
}

BOX_Margin	margin_50()
{
	BOX_Margin	margin_50 = {50, 50, 50, 50};
	return (margin_50);
}

SDL_Texture	*snake_texture(SDL_Renderer *renderer)
{
	SDL_Surface	*snake_surface = IMG_Load("snake.p8.png");
	SDL_Texture	*snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);
	SDL_FreeSurface(snake_surface);
	return (snake_texture);
}

void	reverse_direction(BOX_Box *box)
{
	if (box->styles.direction == BOX_DIRECTION_COLUMN)
		box->styles.direction = BOX_DIRECTION_COLUMN_REVERT;
	else if (box->styles.direction == BOX_DIRECTION_COLUMN_REVERT)
		box->styles.direction = BOX_DIRECTION_COLUMN;
	else if (box->styles.direction == BOX_DIRECTION_ROW)
		box->styles.direction = BOX_DIRECTION_ROW_REVERT;
	else if (box->styles.direction == BOX_DIRECTION_ROW_REVERT)
		box->styles.direction = BOX_DIRECTION_ROW;
}

void	reverse_all(BOX_Box *box)
{
	BOX_Box	*screen_box = BOX_get_last_parent(box);

	BOX_apply_to_depth_children(screen_box, -1, &reverse_direction);
	BOX_update_children_absolute_rect(screen_box);
}

void	add_margin(BOX_Box *box)
{
	box->styles.margin.left += 3.0f;
	box->styles.margin.top += 3.0f;
	box->styles.margin.right += 3.0f;
	box->styles.margin.bottom += 3.0f;

	BOX_update_children_absolute_rect(BOX_get_depth_parent(box, 1));
}

void	add_padding(BOX_Box *box)
{
	box->styles.margin.left += 3.0f;
	box->styles.margin.top += 3.0f;
	box->styles.margin.right += 3.0f;
	box->styles.margin.bottom += 3.0f;

	BOX_update_children_absolute_rect(BOX_get_depth_parent(box, 1));
}


void	prepare_screen_box(SDL_Renderer *renderer, BOX_Box *screen_box)
{
	(void) renderer;
	BOX_Box	*styles_box = BOX_create_box(0, 0, 1.0f, 0.4f, BOX_TYPE_BOX);
	styles_box->styles.padding = margin_10();
	styles_box->styles.direction = BOX_DIRECTION_ROW;

	BOX_add_front_child(screen_box, styles_box);

	BOX_Box	*bg_color_box = BOX_create_box(0, 0, 0.3f, 1.0f, BOX_TYPE_BOX);
	bg_color_box->styles.margin = margin_10();
	bg_color_box->styles.background_color = color_red();
	
	BOX_Box	*border_width_box = BOX_create_box(0, 0, 0.3f, 1.0f, BOX_TYPE_BOX);
	border_width_box->styles.margin = margin_10();
	border_width_box->styles.border_width = 10;
	
	BOX_Box	*texture_box = BOX_create_box(0, 0, 0.3f, 1.0f, BOX_TYPE_BOX);
	texture_box->styles.margin = margin_10();
	texture_box->styles.border_color = color_red();
	texture_box->texture = snake_texture(renderer);

	BOX_add_front_child(styles_box, bg_color_box);
	BOX_add_back_child(styles_box, border_width_box);
	BOX_add_next_to_child(border_width_box, texture_box);

	BOX_Box	*inverse_box = BOX_create_box(0, 0, 1.0f, 0.2f, BOX_TYPE_BUTTON);
	inverse_box->styles.visible = false;
	inverse_box->on_click = &reverse_all;
	BOX_set_box_text(inverse_box, "Click to reverse all directions !!!");
	BOX_update_box_text_texture(renderer, inverse_box);

	BOX_add_back_child(screen_box, inverse_box);

	BOX_Box	*events_box = BOX_create_box(0, 0, 1.0f, 0.3f, BOX_TYPE_BOX);
	events_box->styles.visible = false;
	events_box->styles.padding = margin_10();
	events_box->styles.direction = BOX_DIRECTION_ROW;

	BOX_add_back_child(screen_box, events_box);

	BOX_Box	*inputs_box = BOX_create_box(0, 0, 0.4f, 1.0f, BOX_TYPE_BOX);
	inputs_box->styles.margin = margin_50();

	BOX_add_front_child(events_box, inputs_box);

	BOX_Box	*input_box_1 = BOX_create_box(0, 0, 1.0f, 0.5f, BOX_TYPE_INPUT);
	input_box_1->styles.margin = margin_10();
	BOX_set_box_text(input_box_1, "Click and Write !");
	BOX_update_box_text_texture(renderer, input_box_1);
	
	BOX_Box	*input_box_2 = BOX_create_box(0, 0, 1.0f, 0.5f, BOX_TYPE_INPUT);
	input_box_2->styles.margin = margin_10();
	input_box_2->styles.padding = margin_50();
	BOX_set_box_text(input_box_2, "Here too !");
	BOX_update_box_text_texture(renderer, input_box_2);

	BOX_add_back_child(inputs_box, input_box_1);
	BOX_add_back_child(inputs_box, input_box_2);

	BOX_Box	*margins_box = BOX_create_box(0, 0, 0.4f, 1.0f, BOX_TYPE_BOX);
	margins_box->styles.margin = margin_50();

	BOX_add_back_child(events_box, margins_box);

	BOX_Box	*margin_box = BOX_create_box(0, 0, 1.0f, 0.5f, BOX_TYPE_BUTTON);
	BOX_set_box_text(margin_box, "Margin");
	BOX_update_box_text_texture(renderer, margin_box);
	margin_box->on_click = &add_margin;

	BOX_Box	*padding_box = BOX_create_box(0, 0, 1.0f, 0.5f, BOX_TYPE_BUTTON);
	BOX_set_box_text(padding_box, "Padding");
	BOX_update_box_text_texture(renderer, padding_box);
	padding_box->on_click = &add_padding;

	BOX_add_front_child(margins_box, margin_box);
	BOX_add_next_to_child(margin_box, padding_box);
}

int	main(int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window	*window = SDL_CreateWindow("SDL_Boxes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	SDL_Renderer	*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	BOX_Box	*screen_box = BOX_create_box(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BOX_TYPE_BOX);
	screen_box->absolute_rect.width= SCREEN_WIDTH;
	screen_box->absolute_rect.height = SCREEN_HEIGHT;
	screen_box->styles.padding = margin_50();

	prepare_screen_box(renderer, screen_box);

	BOX_update_children_absolute_rect(screen_box);

	int	running = true;
	while (running)
	{
		SDL_Event	event;

		BOX_do_events(renderer, event, screen_box);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
						int newWidth = event.window.data1;
						int newHeight = event.window.data2;
						
						screen_box->absolute_rect.width= newWidth;
						screen_box->absolute_rect.height = newHeight;
						BOX_update_children_absolute_rect(screen_box);
					}
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_KEYDOWN:
				break;

			default:
				break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		BOX_render_box(renderer, screen_box);
		BOX_render_children(renderer, screen_box);

		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}
	BOX_free_box(screen_box);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}