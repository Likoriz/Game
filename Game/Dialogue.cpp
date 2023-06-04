#include "Basic.h"
#include "Map.h"
#include "Dialogue.h"
#include "NPCAnimation.h"
#include "Motion.h"

DialogueBox dialogueBox;

void Dialogue()
{
	SDL_DestroyTexture(dialogueBox.boxTexture);
	dialogueBox.boxTexture = LoadTexture("Assets\\Box.png", &dialogueBox.boxTextureRect);
	SDL_RenderCopy(ren, dialogueBox.boxTexture, &dialogueBox.boxTextureRect, &dialogueBox.boxDstRect);

	TTF_Font* font = TTF_OpenFont("Monocraft.ttf", 100);

	switch (npc.rects[npc.index].type)
	{
	case 8:
		switch(dialogueBox.progress)
		{
		case 0:
			strcpy_s(dialogueBox.stringText1, 40, "Wanderer, please, help this poor man.");
			strcpy_s(dialogueBox.stringText2, 40, "Share some food and this old man will");
			strcpy_s(dialogueBox.stringText3, 40, "tell a secret he's learned recently. ");
			strcpy_s(dialogueBox.stringText4, 40, "I'm sure, it will be worth your help.");
			break;
		case 1:
			strcpy_s(dialogueBox.stringText1, 40, "Would you like to spare me some food?");
			strcpy_s(dialogueBox.stringText2, 40, "                                     ");
			strcpy_s(dialogueBox.stringText3, 40, "Give food to the beggar              ");
			strcpy_s(dialogueBox.stringText4, 40, "Ignore him                           ");
			break;
		default:
			state.isDialouge = false;
			state.isGaming = true;
		}
		break;
	case 12:
		switch (dialogueBox.progress)
		{
		case 0:
			strcpy_s(dialogueBox.stringText1, 40, "Wanderer, do you mind telling me     ");
			strcpy_s(dialogueBox.stringText2, 40, "your story? Maybe it will become a   ");
			strcpy_s(dialogueBox.stringText3, 40, "great legend someday!                ");
			strcpy_s(dialogueBox.stringText4, 40, "                                     ");
			break;
		case 1:
			Save();
			strcpy_s(dialogueBox.stringText1, 40, "Game has been saved!                 ");
			strcpy_s(dialogueBox.stringText2, 40, "                                     ");
			strcpy_s(dialogueBox.stringText3, 40, "                                     ");
			strcpy_s(dialogueBox.stringText4, 40, "                                     ");
			break;
		default:
			state.isDialouge = false;
			state.isGaming = true;
		}
		break;
	}

	SDL_DestroyTexture(dialogueBox.text1);
	dialogueBox.text1 = GenerateTextureText(dialogueBox.stringText1, font, &dialogueBox.textRect1, dialogueBox.colour);
	SDL_RenderCopy(ren, dialogueBox.text1, &dialogueBox.textRect1, &dialogueBox.dstRect1);

	SDL_DestroyTexture(dialogueBox.text2);
	dialogueBox.text2 = GenerateTextureText(dialogueBox.stringText2, font, &dialogueBox.textRect2, dialogueBox.colour);
	SDL_RenderCopy(ren, dialogueBox.text2, &dialogueBox.textRect2, &dialogueBox.dstRect2);

	SDL_DestroyTexture(dialogueBox.text3);
	dialogueBox.text3 = GenerateTextureText(dialogueBox.stringText3, font, &dialogueBox.textRect3, dialogueBox.colour);
	SDL_RenderCopy(ren, dialogueBox.text3, &dialogueBox.textRect3, &dialogueBox.dstRect3);

	SDL_DestroyTexture(dialogueBox.text4);
	dialogueBox.text4 = GenerateTextureText(dialogueBox.stringText4, font, &dialogueBox.textRect4, dialogueBox.colour);
	SDL_RenderCopy(ren, dialogueBox.text4, &dialogueBox.textRect4, &dialogueBox.dstRect4);

	if (!state.isDialouge)
	{
		SDL_DestroyTexture(dialogueBox.boxTexture);
		SDL_DestroyTexture(dialogueBox.text1);
		SDL_DestroyTexture(dialogueBox.text2);
		SDL_DestroyTexture(dialogueBox.text3);
		SDL_DestroyTexture(dialogueBox.text4);
		dialogueBox.progress = 0;
	}

	TTF_CloseFont(font);
}

double CheckInteraction()
{
	double s = 0;
	double minS = LONG_MAX;
	for (int i = 0; i < npc.count; i++)
	{
		s = sqrt((npc.rects[i].dstRect.x - character.destinationRect.x) * (npc.rects[i].dstRect.x - character.destinationRect.x) + (npc.rects[i].dstRect.y - character.destinationRect.y) * (npc.rects[i].dstRect.y - character.destinationRect.y));
		if (s < minS)
		{
			minS = s;
			npc.index = i;
		}
	}
	return minS;
}
