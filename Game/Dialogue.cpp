#include "Basic.h"
#include "Map.h"
#include "Dialogue.h"
#include "NPCAnimation.h"
#include "Motion.h"

DialogueBox dialogueBox;
Quests quest;

void Dialogue()
{
	SDL_Event event;
	int mouseX, mouseY;

	TTF_Font* font = TTF_OpenFont("Monocraft.ttf", 100);

	switch (npc.rects[npc.index].type)
	{
	case 8:
	{
		switch (character.quest)
		{
		case BREAD:
			switch (dialogueBox.progress)
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
				dialogueBox.allowChoice = true;
				break;
			case 2:
				strcpy_s(dialogueBox.stringText1, 40, "Thank you for your kindness. In      ");
				strcpy_s(dialogueBox.stringText2, 40, "exchange, this man will share with   ");
				strcpy_s(dialogueBox.stringText3, 40, "you some information. The village    ");
				strcpy_s(dialogueBox.stringText4, 40, "upper is having severe problems with ");
				break;
			case 3:
				strcpy_s(dialogueBox.stringText1, 40, "monsters attacking them. If you can  ");
				strcpy_s(dialogueBox.stringText2, 40, "deal with it they surely will reward ");
				strcpy_s(dialogueBox.stringText3, 40, "you. Now go upper if you're not      ");
				strcpy_s(dialogueBox.stringText4, 40, "afraid.                              ");
				break;
			default:
				character.quest = MONSTERS;
				quest.bread = true;
				state.isDialouge = false;
				state.isGaming = true;
				break;
			}
			break;
		default:
			if (quest.bread)
			{
				state.isDialouge = false;
				state.isGaming = true;
			}
			break;
		}
	}
	break;
	case 11:
	{
		switch (dialogueBox.progress)
		{
		case 0:
			strcpy_s(dialogueBox.stringText1, 40, "I have some goods for you! Feel free ");
			strcpy_s(dialogueBox.stringText2, 40, "to look around.                      ");
			strcpy_s(dialogueBox.stringText3, 40, "Buy something                        ");
			strcpy_s(dialogueBox.stringText4, 40, "I don't need anything yet            ");
			dialogueBox.allowChoice = true;
			break;
		case 1:
			state.isDialouge = false;//ÑÞÄÀ ÔÓÍÊÖÈÞ ÌÀÃÀÇÈÍÀ
			state.isGaming = true;
			break;
		default:
			state.isDialouge = false;
			state.isGaming = true;
		}
		break;
	}
	case 12:
	{
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
	}
	break;
	case 14:
	{
		switch (character.quest)
		{
		case MONSTERS:
		{
			switch (dialogueBox.progress)
			{
			case 0:
				strcpy_s(dialogueBox.stringText1, 40, "Hello, dear traveller. As you can    ");
				strcpy_s(dialogueBox.stringText2, 40, "know, this village was harmed by     ");
				strcpy_s(dialogueBox.stringText3, 40, "lots of monsters many times by now.  ");
				strcpy_s(dialogueBox.stringText4, 40, "It would be very good if you don't   ");
				break;
			case 1:
				strcpy_s(dialogueBox.stringText1, 40, "mind to help me and the villagers.   ");
				strcpy_s(dialogueBox.stringText2, 40, "Please, come to the forest and get   ");
				strcpy_s(dialogueBox.stringText3, 40, "rid of monsters. Be careful, it's    ");
				strcpy_s(dialogueBox.stringText4, 40, "very dark there!                     ");
				break;
			default:
				int enemySlain = 5;//ÑÞÄÀ Ñ×ÅÒ×ÈÊ ÓÁÈÒÛÕ ÌÎÍÑÒÐÎÂ Â ÒÐÅÒÜÅÉ ËÎÊÅ
				if (enemySlain == 5)
				{
					character.quest = SEWERS;
					quest.monsters = true;
				}
				state.isDialouge = false;
				state.isGaming = true;
				break;
			}
			break;
		}
		break;
		case SEWERS:
		{
			switch (dialogueBox.progress)
			{
			case 0:
				strcpy_s(dialogueBox.stringText1, 40, "I'm so grateful. Thank you for your  ");
				strcpy_s(dialogueBox.stringText2, 40, "assistance. Now we can go in the     ");
				strcpy_s(dialogueBox.stringText3, 40, "forest again. I'm too old to protect ");
				strcpy_s(dialogueBox.stringText4, 40, "our villagers, traveller, can you go ");
				break;
			case 1:
				strcpy_s(dialogueBox.stringText1, 40, "down in the sewers to deal with      ");
				strcpy_s(dialogueBox.stringText2, 40, "monsters, please? You need to do it  ");
				strcpy_s(dialogueBox.stringText3, 40, "quick, sewers are full of toxic mist.");
				strcpy_s(dialogueBox.stringText4, 40, "And, please, come with the thing.    ");
				break;
			case 2:
				strcpy_s(dialogueBox.stringText1, 40, "I have lost it long time ago in my   ");
				strcpy_s(dialogueBox.stringText2, 40, "youth and now I'm sorry about it.    ");
				strcpy_s(dialogueBox.stringText3, 40, "Now go, traveller. Be careful on your");
				strcpy_s(dialogueBox.stringText4, 40, "way...                               ");
				break;
			default:
				int enemySlain = 5;//ÑÞÄÀ ÍÀËÈ×ÈÅ ÏÐÎÊËßÒÎÉ ÂÅÙÈ Â ÈÍÂÅÍÒÀÐÅ
				if (enemySlain == 5)
				{
					character.quest = BOSS;
					quest.monsters = true;
				}
				state.isDialouge = false;
				state.isGaming = true;
				break;
			}
			break;
		}
		break;
		case BOSS:
		{
			switch (dialogueBox.progress)
			{
			case 0:
				strcpy_s(dialogueBox.stringText1, 40, "So you really found it, thank you. I ");
				strcpy_s(dialogueBox.stringText2, 40, "know for sure it wasn't easy for you.");
				strcpy_s(dialogueBox.stringText3, 40, "I want you to rest, but there's one  ");
				strcpy_s(dialogueBox.stringText4, 40, "threat left. If you have noticed,    ");
				break;
			case 1:
				strcpy_s(dialogueBox.stringText1, 40, "the sewers have another one way      ");
				strcpy_s(dialogueBox.stringText2, 40, "deeper. I feel the dark magic out    ");
				strcpy_s(dialogueBox.stringText3, 40, "there. I'm afraid it may be some evil");
				strcpy_s(dialogueBox.stringText4, 40, "spirit. Please, protect us, warderer!");
				break;
			case 2:
				strcpy_s(dialogueBox.stringText1, 40, "Pay attention to your preparation for");
				strcpy_s(dialogueBox.stringText2, 40, "fight and, please, be careful. I wish");
				strcpy_s(dialogueBox.stringText3, 40, "you all the good luck, traveller!    ");
				strcpy_s(dialogueBox.stringText4, 40, "                                     ");
				break;
			default:
				int enemySlain = 5;//ÑÞÄÀ ÊÀÊÎÉ ÍÈÁÓÄÜ ÔËÀÃ ÏÎÁÈÒÎÃÎ ÁÎÑÑÀ
				if (enemySlain == 5)
				{
					character.quest = END;
					quest.boss = true;
				}
				state.isDialouge = false;
				state.isGaming = true;
				break;
			}
			break;
		}
		case END:
		{
			switch (dialogueBox.progress)
			{
			case 0:
				strcpy_s(dialogueBox.stringText1, 40, "You did it, traveller! Everyone in   ");
				strcpy_s(dialogueBox.stringText2, 40, "the village was worrying about you.  ");
				strcpy_s(dialogueBox.stringText3, 40, "We're glad that you're wasn't hurt by");
				strcpy_s(dialogueBox.stringText4, 40, "this dark entity. Thank to your deeds");
				break;
			case 1:
				strcpy_s(dialogueBox.stringText1, 40, "we can sleep calmly. No one will ever");
				strcpy_s(dialogueBox.stringText2, 40, "forget about you and your glory will ");
				strcpy_s(dialogueBox.stringText3, 40, "stay eternal in our village.         ");
				strcpy_s(dialogueBox.stringText4, 40, "Thank you, traveller!                ");
				break;
			default:
				character.quest = END;
				quest.end = true;
				state.isDialouge = false;
				state.isGaming = true;
				break;
			}
			break;
		}
		default:
			if (quest.monsters)
			{
				state.isDialouge = false;
				state.isGaming = true;
			}
			break;
		}
	}
	break;
	default:
		state.isDialouge = false;
		state.isGaming = true;
	}

	if (dialogueBox.allowChoice)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouseX, &mouseY);
				if (mouseX >= dialogueBox.dstRect3.x * scaleX && mouseX <= (dialogueBox.dstRect3.x + dialogueBox.dstRect3.w) * scaleX && mouseY >= dialogueBox.dstRect3.y * scaleY && mouseY <= (dialogueBox.dstRect3.y + dialogueBox.dstRect3.h) * scaleY)
					dialogueBox.colour3 = { 180, 180, 180, 255 };
				else
					dialogueBox.colour3 = { 0, 0, 0, 255 };

				if (mouseX >= dialogueBox.dstRect4.x * scaleX && mouseX <= (dialogueBox.dstRect4.x + dialogueBox.dstRect4.w) * scaleX && mouseY >= dialogueBox.dstRect4.y * scaleY && mouseY <= (dialogueBox.dstRect4.y + dialogueBox.dstRect4.h) * scaleY)
					dialogueBox.colour4 = { 180, 180, 180, 255 };
				else
					dialogueBox.colour4 = { 0, 0, 0, 255 };
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mouseX, &mouseY);
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					if (mouseX >= dialogueBox.dstRect3.x * scaleX && mouseX <= (dialogueBox.dstRect3.x + dialogueBox.dstRect3.w) * scaleX && mouseY >= dialogueBox.dstRect3.y * scaleY && mouseY <= (dialogueBox.dstRect3.y + dialogueBox.dstRect3.h) * scaleY)
					{
						dialogueBox.progress++;
						dialogueBox.allowChoice = false;
						dialogueBox.colour3 = { 0, 0, 0, 255 };
						dialogueBox.colour4 = { 0, 0, 0, 255 };
					}

					if (mouseX >= dialogueBox.dstRect4.x * scaleX && mouseX <= (dialogueBox.dstRect4.x + dialogueBox.dstRect4.w) * scaleX && mouseY >= dialogueBox.dstRect4.y * scaleY && mouseY <= (dialogueBox.dstRect4.y + dialogueBox.dstRect4.h) * scaleY)
					{
						dialogueBox.allowChoice = false;
						state.isDialouge = false;
						state.isGaming = true;
						dialogueBox.colour3 = { 0, 0, 0, 255 };
						dialogueBox.colour4 = { 0, 0, 0, 255 };
					}
				}
			}
		}
	}

	if (state.isDialouge)
	{
		SDL_DestroyTexture(dialogueBox.boxTexture);
		dialogueBox.boxTexture = LoadTexture("Assets\\Box.png", &dialogueBox.boxTextureRect);
		SDL_RenderCopy(ren, dialogueBox.boxTexture, &dialogueBox.boxTextureRect, &dialogueBox.boxDstRect);

		SDL_DestroyTexture(dialogueBox.text1);
		dialogueBox.text1 = GenerateTextureText(dialogueBox.stringText1, font, &dialogueBox.textRect1, dialogueBox.colour);
		SDL_RenderCopy(ren, dialogueBox.text1, &dialogueBox.textRect1, &dialogueBox.dstRect1);

		SDL_DestroyTexture(dialogueBox.text2);
		dialogueBox.text2 = GenerateTextureText(dialogueBox.stringText2, font, &dialogueBox.textRect2, dialogueBox.colour);
		SDL_RenderCopy(ren, dialogueBox.text2, &dialogueBox.textRect2, &dialogueBox.dstRect2);

		SDL_DestroyTexture(dialogueBox.text3);
		dialogueBox.text3 = GenerateTextureText(dialogueBox.stringText3, font, &dialogueBox.textRect3, dialogueBox.colour3);
		SDL_RenderCopy(ren, dialogueBox.text3, &dialogueBox.textRect3, &dialogueBox.dstRect3);

		SDL_DestroyTexture(dialogueBox.text4);
		dialogueBox.text4 = GenerateTextureText(dialogueBox.stringText4, font, &dialogueBox.textRect4, dialogueBox.colour4);
		SDL_RenderCopy(ren, dialogueBox.text4, &dialogueBox.textRect4, &dialogueBox.dstRect4);
	}
	else
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

double CheckNPC()
{
	double s = 0;
	double minS = LONG_MAX;
	for (int i = 0; i < npc.count; i++)
	{
		{
			s = sqrt((npc.rects[i].dstRect.x - character.destinationRect.x) * (npc.rects[i].dstRect.x - character.destinationRect.x) + (npc.rects[i].dstRect.y - character.destinationRect.y) * (npc.rects[i].dstRect.y - character.destinationRect.y));
			if (s < minS)
			{
				minS = s;
				npc.index = i;
			}
		}
	}
	return minS;
}
