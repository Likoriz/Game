//#include "stats.h"
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//const unsigned char items[num_of_items][12] = {"test_item", "phys_sword", "cryo_sword", "pyro_sword", "phys_book", "cryo_book", "pyro_book", "heal", "key", "mana", "cursed_book" };
//enum items
//{
//	phys_sword = 1,
//	cryo_sword = 2,
//	pyro_sword = 3,
//	phys_book = 4,
//	cryo_book = 5,
//	pyro_book = 6,
//	heal = 7,
//	key = 8,
//	mana = 9,
//	cursed_book = 10
//};
//enum classes_of_player
//{
//	enchantress = 1,
//	knight = 2
//};
//Player init_player_stats(unsigned char class_of_player)
//{
//	switch(class_of_player)
//	{
//	case enchantress: Player player_stats = {class_of_player , 100, 50, phys_sword, cryo_book, 100, 0, 1, 0, {}, 0, 0}; break;
//	case knight: Player player_stats = {class_of_player , 150, 100, phys_sword, phys_book, 0, 0, 1, 0, {}, 0, 0 }; break;
//	}
//	player_stats.inventory++;
//}
//void print_inventory(Player player_stats)
//{
//	TTF_Font* font = TTF_OpenFont("Monocraft.ttf", 100);
//	SDL_Color colour = { 0, 0, 0, 255 };
//	SDL_Rect text_rect = { 200, 200, 200, 400 };
//	SDL_FRect rect_to_write = {};
//	if(player_stats.inventory[-1])
//		SDL_Texture* text = GenerateTextureText("Now in your inventory you have: ", font, &text_rect, colour);
//		for(int i=0;i<player_stats.inventory[-1];i++)
//		{
//
//		}
//	else
//		SDL_Texture* text = GenerateTextureText("You have nothing in your inventory : c", font, &text_rect, colour);
//	SDL_RenderCopyF(ren, text, &text_rect, &text_rect);
//	SDL_DestroyTexture(text);
//}