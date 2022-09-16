#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

const int TELA_LARGURA = 640;
const int TELA_ALTURA = 480;

int main(int argc, char** argv)
{
	al_init();
	al_init_font_addon();
	ALLEGRO_DISPLAY* display = al_create_display(TELA_LARGURA, TELA_ALTURA);
	ALLEGRO_FONT* font = al_create_builtin_font();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "EXULT");
	al_flip_display();
	al_rest(5.0);
	return 0;
}