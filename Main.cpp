#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>				//incluindo bibliotecas
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//__________________________________________
//Variaveis globais

ALLEGRO_SAMPLE* trilha_sonora = NULL;
ALLEGRO_SAMPLE_INSTANCE* inst_trilha_sonora = NULL;  //instanciar evita conflitos e permite functions a mais

enum KEYS { UP, DOWN, LEFT, RIGHT };

int main(void)
{

	int width = 640;
	int height = 480;

	bool done = false;	
	int  pos_x = width / 2;
	int pos_y = height / 2;                        //declarando variáveis

	bool keys[4] = { false, false, false, false };

		ALLEGRO_DISPLAY *display = NULL;
		ALLEGRO_EVENT_QUEUE* event_queue = NULL;

		if (!al_init())                                          //iniciando allegro
			return -1;
		  
		display = al_create_display(width, height);              //criando display
		 
		if (!display)                                            //teste display
			return -1;

//-------------------------------------
		//inicializacao de ADDONS e INSTALACOES

		al_install_audio();
		al_init_acodec_addon();
		al_init_primitives_addon();
		al_install_keyboard();

		al_reserve_samples(15);  //"quantos audios vai ter no jogo"

//-------------------------------------
		//criacao de filas

		event_queue = al_create_event_queue();

		trilha_sonora = al_load_sample("trilha-sonora.wav"); //carrega qual arquivo vai tocar
		inst_trilha_sonora = al_create_sample_instance(trilha_sonora); //instancia ela
		al_attach_sample_instance_to_mixer(inst_trilha_sonora, al_get_default_mixer()); //faz com que ela fique num padrao ja definido poupando trabalho
		al_set_sample_instance_playmode(inst_trilha_sonora, ALLEGRO_PLAYMODE_LOOP); //coloca a soundtrack em loop
		al_set_sample_instance_gain(inst_trilha_sonora, 0.4); // VOLUME

		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_display_event_source(display));

		
		while (!done)			
		{
			ALLEGRO_EVENT ev;									//evento das teclas para MOVIMENTAÇÃO
			al_wait_for_event(event_queue, &ev);
			al_play_sample_instance(inst_trilha_sonora);
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					keys[UP] = true;
				break;

				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = true;
					break;

				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = true;
					break;
				}
			}

				else if (ev.type == ALLEGRO_EVENT_KEY_UP)
			{
				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					keys[UP] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					keys[DOWN] = false;
					break;

				case ALLEGRO_KEY_LEFT:
					keys[LEFT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					keys[RIGHT] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;

				}
			}

				else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)  //para fechar o display ao apertar o X
			{
				done = true;                            
			}

			pos_y -= keys[UP] * 10;
			pos_y += keys[DOWN] * 10;
			pos_x -= keys[LEFT] * 10;
			pos_x += keys[RIGHT] * 10;


			al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(200, 0, 055));  //desenho do SQUARE, posição e cor
			al_flip_display();
			al_clear_to_color(al_map_rgb(192, 192, 192));

			

		}

//----------------------------------------
		//FINALIZACOES e DESTROYS

		al_destroy_sample(trilha_sonora);
		al_destroy_sample_instance(inst_trilha_sonora);
		al_destroy_display(display);                            

		return 0;
}