#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define ERROR_CHECK errorCheck(error, &head, &param, &oth, &fname);

/*===========================================================================*/
/*                                STRUCTURES                                 */
/*===========================================================================*/

typedef struct GAME_NODE				// [list's game]
{
	char* name;							// game's name
	char* dev;							// game's developer
	int date;							// game's release date
	int price;							// game's price
	int rating;		    				// game's rating
	struct GAME_NODE* next;				// next game in list
} GN;

typedef struct GAME_HEAD				// [list's head]
{
	GN* first;							// first game in list
	GN* last;							// last game in list
} GH;

/*===========================================================================*/
/*                            FUNCTION PROTOTYPES                            */
/*===========================================================================*/

/*------------------------------menu functions-------------------------------*/

char mainMenu();								// print main menu items
char enterMenu();								// print enter menu items
char creamodMenu();								// print create/modify menu items
char addMenu();									// print add menu items
char remMenu();									// print remove menu items
char outputMenu();								// print output menu items
char processMenu();								// print processing menu items
char changeMenu();								// print change menu items
char printMenu();								// print output modify menu items
char sortMenu();								// print sort menu items
char filtMenu();								// print filter menu items
char getChoice();								// input choice

/*------------------------functions for forming list-------------------------*/

GH* makeHead(int*);								// head list creation
void addFirst(GH*,GN*);							// add a game to the top
void addLast(GH*,GN*);							// add a game to the end
void addAfter(GH*,GN*,int);						// add after selected game
void addBefore(GH*,GN*,int);					// add before selected game
void remFirst(GH**);							// remove a game from the top
void remLast(GH**);								// remove a game from the end
void remAfter(GH**,int);						// remove after selected game
void remBefore(GH**,int);						// remove before selected game
int addRemCon(GH*,int,int,int);					// position for add/remove

/*-------------------functions for forming list's element--------------------*/

GN* makeNode(int*);								// game of list creation
GN* gameInput(int*);							// entering structure fields
void gameChange(GH*,char*,int,int*);			// change structure fields info
char* gameName(GN**,int,int*);					// entering game name
char* gameDev(GN**,int,int*);					// entering game developer
int gameDate(int,int);							// entering game release date
int gamePrice(int,int);							// entering game price
int gameRating(int,int);						// entering game rating

/*-----------------------functions for work with list------------------------*/

int getSize(GH*);								// getting list size
GN* gameCopy(GN*,int*);							// copy game
GH* listCopy(GH*,int*);							// copy list

/*-------------------------list conversion functions-------------------------*/

void sort(GH*,int(*)(GN*,GN*),int);				// sort list
void filter(GH*,GH**,char*,int(**)(GN*,GN*));	// filter list
int sortFieldSelect();							// field selection for sorting
int sortDirSelect();							// direction selection for sortin
GH* paramMake(char*,int*);						// parametrs creation

/*------------------------information output functions-----------------------*/

void listPrint(GH*);							// output list
void gamePrint(GH*,int);						// output game
void sortParamPrint(int,int);					// output sort parametrs
void filtParamPrint(GH*);						// output filter parametrs

/*---------------------------comparison functions----------------------------*/

int cmpName(GN*,GN*);							// name comparison
int cmpDev(GN*,GN*);							// developer comparison
int cmpDate(GN*,GN*);							// date comparison
int cmpPrice(GN*,GN*);							// price comparison
int cmpRating(GN*,GN*);							// rating comparison

/*----------------------functions for work with strings----------------------*/

int fromStrToNum(char*, int);					// conversation from char to num
int findSym(char*,char, int, int);				// search symbol in string
int strLen(char*);								// getting string length
int strCmp(char*,char*);						// string comparison
void strCopy(char*,char*,int);					// copy string

/*-------------------------functions to free memory--------------------------*/

void freeGame(GN**);							// remove game
void freeHead(GH**);							// remove list
void delAll(GH**,GH**,GH**);					// delete all data
void errorCheck(int,GH**,GH**,GH**,char**);		// delete all data and emergency exit

/*----------------------functions for work with strings----------------------*/

char* fileName();								// enter file name
int parser(char*,int);							// parsing file name
GH* readFile(char*,int*);						// read file
void saveFile(GH*,char*);						// save file
int needSave(GH*,int*);							// choice save or not

/*---------------------------------messages----------------------------------*/

void errorMes();								// print message about error
void emptyMes();								// print message about empty list
void incMes();								    // print message about comand
void cntMes(int);								// print message about file error
void succMes();									// print message about succesfull

/*-----------------------------------other-----------------------------------*/

int getPos(GH*);								// choice position in list
void fieldChoice(char*,int);					// make choice about fields
void pause();									// pause program

/*===========================================================================*/
/*                               MAIN FUNCTION                               */
/*===========================================================================*/

int main()
{
	GH
	*head,						// current file-cabinet
	*param,						// filtering options
	*oth;						// auxiliary file-cabinet

	GN *game;					// another card in the file cabinet

	char
	lvl1,						// user choice in the 1 level menu
	lvl2,						// user choice in the 2 level menu
	lvl3,						// user choice in the 3 level menu
	lvl4,						// user choice in the 4 level menu
	*fname,						// file name
	ffield[7],					// game fields that need to be changed
	cfield[7];					// game fields to be filtered

	int
	(*cmp[5])(GN*, GN*),		// array of pointers to function call points
	flag,						// file save token
	_filt,						// file-cabinet filter marker
	error,						// error marker
	pos,						// position in file-cabinet
	sfield,						// game field to be sorted
	sdir;						// sorting direction

    
    // assignment of initial values
	ffield[0] = '\0';
	cfield[0] = '\0';

	_filt = 0;
	flag = 0;
	error = 0;
	sfield = -1;
    sdir = -1;

	cmp[0] = cmpName;
	cmp[1] = cmpDev;
	cmp[2] = cmpDate;
	cmp[3] = cmpPrice;
	cmp[4] = cmpRating;

	head = NULL;
	param = NULL;
	oth = NULL;

	// conclusion greeting
	printf("Welcome to GAME DATABASE");
	pause();
	
	do
	{
		lvl1 = mainMenu();	// main menu
		switch(lvl1)
		{
			case '1':	// enter file-cabinet
					do
					{
						lvl2 = enterMenu();	// enter file-cabinet
						system("cls");
						switch(lvl2)
						{
							case '1':	// create new in console
                                    if(head)
									{
										if(!flag)
										{
											flag = needSave(head, &error);
											ERROR_CHECK
										}
										freeHead(&head);
									}
									do
									{
										lvl3 = creamodMenu();	// create menu
										system("cls");
										switch(lvl3)
										{
											case '1':	// add game
													do
													{
														lvl4 = addMenu();	// add menu
														system("cls");
														switch(lvl4)
														{
															case '1':	// add first
																	if (!head)
																		head = makeHead(&error);
																	ERROR_CHECK
																	flag = 0;
																	game = gameInput(&error);
																	ERROR_CHECK
																	addFirst(head, game);
																	break;
															case '2':	// add last
																	if(!head)
																		head = makeHead(&error);
																	ERROR_CHECK
																	flag = 0;
																	game = gameInput(&error);
																	ERROR_CHECK
																	addLast(head, game);
																	break;
															case '3':	// add after selected game
																	if(!head)
																		head = makeHead(&error);
																	ERROR_CHECK
																	pos = addRemCon(head, getSize(head), 0, 0);
																	flag = 0;
																	game = gameInput(&error);
																	ERROR_CHECK
																	addAfter(head, game, pos);
																	break;
															case '4':	// add after selected game
																	if(!head)
																		head = makeHead(&error);
																	ERROR_CHECK
																	pos = addRemCon(head, getSize(head), 0, 1);
																	flag = 0;
																	game = gameInput(&error);
																	ERROR_CHECK
																	addBefore(head, game, pos);
																	break;
															case '0':	// back
																	break;
															case '\n':
																	break;
															default:
																	incMes();
														}
													}
													while(lvl4 != '0');
													break;
											case '2':	// remove game
													if (head)
													{
														do
														{
															lvl4 = remMenu();	// remove menu
															system("cls");
															switch(lvl4)
															{
																case '1':	// remove first
																		remFirst(&head);
																		flag = 0;
																		succMes();
																		break;
																case '2':	// remove last
																		remLast(&head);
																		flag = 0;
																		succMes();
																		break;
																case '3':	// remove after selected game
																		pos = addRemCon(head, getSize(head), 1, 0);
																		remAfter(&head, pos);
																		flag = 0;
																		succMes();
																		break;
																case '4':	// remove before selected game
																		pos = addRemCon(head, getSize(head), 1, 1);
																		remBefore(&head, pos);
																		flag = 0;
																		succMes();
																		break;
																case '5':	// remove all games
																		freeHead(&head);
																		flag = 1;
																		succMes();
																		break;
																case '0':	// back
																		break;
																case '\n':
																		break;
																default:
																		incMes();
															}
														}
														while(lvl4 != '0' && head);
													}
													else
														emptyMes();
													break;
											case '3':	// change game info
													if (head)
													{
														do
														{
															lvl4 = changeMenu();	// change menu
															system("cls");
															switch(lvl4)
															{
																case '1':	// make a choice
																		fieldChoice(cfield, 1);
																		break;
																case '2':	// change info of selected game
																		if(cfield[0] != '\0')
																		{
																			flag = 0;
																			pos = getPos(head);
																			gameChange(head, cfield, pos, &error);
																			ERROR_CHECK
																		}
																		else
																		{
																			printf("First, specify the fields you want to change.");
																			pause();
																		}
																		break;
																case '0':	// back
																		break;
																case '\n':
																		break;
																default:
																		incMes();
															}
														}
														while(lvl4 != '0');
													}
													else
														emptyMes();
													break;
											case '4':	// output file-cabinet
													if (head) {
														do
														{
															lvl4 = outputMenu();	// output menu
															system("cls");
															switch(lvl4)
															{
																case '1':	// output file-cabinet size
																		printf("Game in file-cabinet: %d", getSize(head));
																		pause();
																		break;
																case '2':	// output selected game
																		pos = getPos(head);
																		gamePrint(head, pos);
																		break;
																case '3':	// output all file-cabinet
																		listPrint(head);
																		break;
																case '4':	// save file-cabinet in file
																		fname = fileName(&error);
																		ERROR_CHECK
																		if(fname)
					                                                    {
																			saveFile(head, fname);
																			if(head)
																				flag = 1;
																			free(fname);
																			fname = NULL;
																		}
																		break;
																case '0':	// back
																		break;
																case '\n':
																		break;
																default:
																		incMes();
															}
														}
														while(lvl4 != '0');
													}
													else
														emptyMes();
													break;
											case '0':	// back
													break;
											case '\n':
													break;
											default:
													incMes();
										}
									}
									while(lvl3 != '0');
									break;
							case '2':	// enter file-cabinet from file
									if(head)
									{
										if(!flag)
										{
											flag = needSave(head, &error);
											ERROR_CHECK
											if(!flag) freeHead(&head);
											ERROR_CHECK
										}
									}
									fname = fileName(&error);
									ERROR_CHECK
									if(fname)
                                    {
										head = readFile(fname, &error);
										ERROR_CHECK
										if(head)
										{
											system("cls");
								        	succMes();
											flag = 1;
										}
										free(fname);
										fname = NULL;
									}
									break;
							case '0':	// back
									break;
							case '\n':
									break;
							default:
									incMes();
						}
					}
					while (lvl2 != '0');
					break;
			case '2':	// output selected file-cabinet
					do
					{
						lvl2 = printMenu();	// modify output menu
						system("cls");
						switch(lvl2)
						{
							case '1':	// output current file-cabinet
									if(head)
									{
										do
										{
											lvl3 = outputMenu();	// output menu
											system("cls");
											switch(lvl3)
											{
												case '1':	// output file-cabinet size
														printf("Game in file-cabinet: %d", getSize(head));
														pause();
														break;
												case '2':	// output selected game
														pos = getPos(head);
														gamePrint(head, pos);
														break;
												case '3':	// output all file-cabinet
														listPrint(head);
														break;
												case '4':	// save file-cabinet in file
														fname = fileName(&error);
														ERROR_CHECK
														if(fname)
						                                {
															saveFile(head, fname);
															if(head)
																flag = 1;
															free(fname);
															fname = NULL;
														}
														break;
												case '0':	// back
														break;
												case '\n':
														break;
												default:
														incMes();
											}
										}
										while(lvl3 != '0');
									}
									else
										emptyMes();
									break;
							case '2':	// output file-cabinet from file
									system("cls");
									fname = fileName(&error);
									ERROR_CHECK
									if(fname)
                                    {
										oth = readFile(fname, &error);
										ERROR_CHECK
										if(oth)
										{
											listPrint(oth);
											freeHead(&oth);
										}
										free(fname);
										oth = NULL;
										fname = NULL;
									}
									break;
							case '0':	// back
									break;
							case '\n':
									break;
							default:
									incMes();
						}

					}
					while(lvl2 != '0');
					break;
			case '3':	// data processing
					if(head)
					{
						do
						{
							lvl2 = processMenu();	// data processing menu
							system("cls");
							switch(lvl2)
							{
								case '1':	// modify
										do
										{
											lvl3 = creamodMenu();	// modify menu
											system("cls");
											switch(lvl3)
											{
												case '1':	// add game
													do
													{
														lvl4 = addMenu();	// add menu
														system("cls");
														switch(lvl4)
														{
															case '1':	// add first
																	if (!head)
																		head = makeHead(&error);
																	ERROR_CHECK
																	flag = 0;
																	game = gameInput(&error);
																	ERROR_CHECK
																	addFirst(head, game);
																	break;
															case '2':	// add last
																	if(!head)
																		head = makeHead(&error);
																	ERROR_CHECK
																	flag = 0;
																	game = gameInput(&error);
																	ERROR_CHECK
																	addLast(head, game);
																	break;
															case '3':	// add after selected game
																	if(!head)
																		head = makeHead(&error);
																	ERROR_CHECK
																	pos = addRemCon(head, getSize(head), 0, 0);
																	flag = 0;
																	game = gameInput(&error);
																	ERROR_CHECK
																	addAfter(head, game, pos);
																	break;
															case '4':	// add before selected game
																	if(!head)
																		head = makeHead(&error);
																	ERROR_CHECK
																	pos = addRemCon(head, getSize(head), 0, 1);
																	flag = 0;
																	game = gameInput(&error);
																	ERROR_CHECK
																	addBefore(head, game, pos);
																	break;
															case '0':	// back
																	break;
															case '\n':
																	break;
															default:
																	incMes();
														}
													}
													while(lvl4 != '0');
													break;
											case '2':	// remove game
													if (head)
													{
														do
														{
															lvl4 = remMenu();	// remove menu
															system("cls");
															switch(lvl4)
															{
																case '1':	// remove first
																		remFirst(&head);
																		flag = 0;
																		succMes();
																		break;
																case '2':	// remove last
																		remLast(&head);
																		flag = 0;
																		succMes();
																		break;
																case '3':	// remove after selected game
																		pos = addRemCon(head, getSize(head), 1, 0);
																		remAfter(&head, pos);
																		flag = 0;
																		succMes();
																		break;
																case '4':	// remove before selected game
																		pos = addRemCon(head, getSize(head), 1, 1);
																		remBefore(&head, pos);
																		flag = 0;
																		succMes();
																		break;
																case '5':	// remove all games
																		freeHead(&head);
																		flag = 1;
																		succMes();
																		break;
																case '0':	// back
																		break;
																case '\n':
																		break;
																default:
																		incMes();
															}
														}
														while(lvl4 != '0' && head);
													}
													else
														emptyMes();
													break;
											case '3':	// change game info
													if (head)
													{
														do
														{
															lvl4 = changeMenu();	// change menu
															system("cls");
															switch(lvl4)
															{
																case '1':	// make choice
																		fieldChoice(cfield, 1);
																		break;
																case '2':	// change selected game
																		if(cfield[0] != '\0')
																		{
																			flag = 0;
																			pos = getPos(head);
																			gameChange(head, cfield, pos, &error);
																			ERROR_CHECK
																		}
																		else
																		{
																			printf("First, specify the fields you want to change.");
																			pause();
																		}
																		break;
																case '0':	// back
																		break;
																case '\n':
																		break;
																default:
																		incMes();
															}
														}
														while(lvl4 != '0');
													}
													else
														emptyMes();
													break;
											case '4':	// output file-cabinet
													if (head) {
														do
														{
															lvl4 = outputMenu();	// output menu
															system("cls");
															switch(lvl4)
															{
																case '1':	// output file-cabinet size
																		printf("Game in file-cabinet: %d", getSize(head));
																		pause();
																		break;
																case '2':	// output selected game
																		pos = getPos(head);
																		gamePrint(head, pos);
																		break;
																case '3':	// output all file-cabinet
																		listPrint(head);
																		break;
																case '4':	// save file-cabinet in file
																		fname = fileName(&error);
																		ERROR_CHECK
																		if(fname)
					                                                    {
																			saveFile(head, fname);
																			if(head)
																				flag = 1;
																			free(fname);
																			fname = NULL;
																		}
																		break;
																case '0':	// back
																		break;
																case '\n':
																		break;
																default:
																		incMes();
															}
														}
														while(lvl4 != '0');
													}
													else
														emptyMes();
													break;
											case '0':	// back
													break;
											case '\n':
													break;
											default:
													incMes();
										}
										}
										while(lvl3 != '0');
										break;
								case '2':	// sort file-cabinet
										do
										{
											lvl3 = sortMenu();	// sort menu
											system("cls");
											switch (lvl3)
											{
												case '1':	// make choice about field
														if (oth)
															freeHead(&oth);
														sfield = sortFieldSelect();
														break;
												case '2':	// make choice about direction
														if (oth)
															freeHead(&oth);
														sdir = sortDirSelect();
														break;
												case '3':	// sort
														if ((sfield != -1) && (sdir != -1))
														{
															if (oth)
																freeHead(&oth);
															oth = listCopy(head, &error);
															ERROR_CHECK
															sort(oth, cmp[sfield], sdir);
															succMes();
														}
														else
														{
															if (sfield == -1)
																printf("You didn't choose sorting parameter! ");
															if (sdir == -1)
																printf("You didn't choose sorting direction!");
															pause();
														}
														break;
												case '4':	// output sort parametrs
														if ((sfield != -1) || (sdir != -1))
															sortParamPrint(sfield,sdir);
														else
														{
															if (sfield == -1)
																printf("You didn't choose sorting parameter! ");
															if (sdir == -1)
																printf("You didn't choose sorting direction!");
															pause();
														}
														break;
												case '5':	// output sorted file-cabinet
														if(oth)
															listPrint(oth);
														else
														{
															printf("You didn't sort file-cabinet!");
															pause();
														}
														break;
												case '6':	// save file-cabinet
														if(oth)
														{
															fname = fileName(&error);
															ERROR_CHECK
															if(fname)
							                                {
																saveFile(oth, fname);
																free(fname);
																fname = NULL;
															}
														}
														else
														{
															printf("You didn't sort file-cabinet!");
															pause();
														}
														break;
												case '0':	// back
														break;
												case '\n':
														break;
												default:
													incMes();
											}
										} while (lvl3 != '0');
										freeHead(&oth);
										break;
								case '3':	// filter
										do
										{
											lvl3 = filtMenu();	// filter menu
											system("cls");
											switch(lvl3)
											{
												case '1':	// make a choice about fields
														if (oth)
															freeHead(&oth);
														if (param)
															freeHead(&param);
														_filt = 0;
														fieldChoice(ffield, 0);
														param = paramMake(ffield, &error);
														ERROR_CHECK
														break;
												case '2':	// filter
														if(ffield[0] != '\0')
														{
															if(oth)
																freeHead(&oth);
															oth = listCopy(head, &error);
															ERROR_CHECK
															filter(param, &oth, ffield, cmp);
															_filt = 1;
															if(oth)
																succMes();
															else
															{
																printf("There are no games matching the parameters"
																	   " in the file cabinet\n\n");
																filtParamPrint(param);
															}
														}
														else
														{
															printf("You didn't choose filtering parameter!");
															pause();
														}
														break;
												case '3':	// output filter parametrs
														if (param)
															filtParamPrint(param);
														else
														{
															printf("You didn't choose filtering parameter!");
															pause();
														}
														break;
												case '4':	// output filtered file-cabinet
														if(oth)
															listPrint(oth);
														else
														{
															if(_filt)
															{
																printf("There are no games matching the parameters"
																	   " in the file cabinet\n\n");
																filtParamPrint(param);
															}
															else
															{
																printf("You didn't filter file-cabinet!");
																pause();
															}
														}
														break;
												case '5':	// save file-cabinet
														if(oth)
														{
															fname = fileName(&error);
															ERROR_CHECK
															if(fname)
							                                {
																saveFile(oth, fname);
																free(fname);
																fname = NULL;
															}
														}
														else
														{
															if(_filt)
															{
																printf("There are no games matching the parameters"
																	   " in the file cabinet\n\n");
																filtParamPrint(param);
															}
															else
															{
																printf("You didn't filter file-cabinet!");
																pause();
															}
														}
														break;
												case '0':	// back
														break;
												case '\n':
														break;
												default:
														incMes();
											}
										}
										while(lvl3 != '0');
										_filt = 0;
										freeHead(&oth);
										break;
								case '0':	// back
										break;
								case '\n':
										break;
								default:
										incMes();
							}
						}
						while(lvl2 != '0' && head);
					}
					else
						emptyMes();
					break;
			case '4':	// help
					break;
			case '0':	// exit
					if(head)
					{
						if(!flag)
						{
							flag = needSave(head, &error);
							ERROR_CHECK
							if(!flag) freeHead(&head);
							ERROR_CHECK
						}
					}
					delAll(&head, &param, &oth);
					system("cls");
					printf("Thanks for using the program!");
					pause();
					break;
			case '\n':
					break;
			default:
					incMes();
		}
	}
	while(lvl1 != '0');

	return 0;
}

/*===========================================================================*/
/*                                 FUNCTIONS                                 */
/*===========================================================================*/

/*-------------------------------menu fuctions-------------------------------*/

char mainMenu()
{
	char choice;
	system("cls");
	printf("         MENU\n\n"
		   "1 - Enter file-cabinet\n\n"
		   "2 - Output file-cabinet\n\n"
		   "3 - File-cabinet processing\n\n"
		   "4 - Help\n\n"
		   "0 - Exit\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char enterMenu()
{
	char choice;
	system("cls");
	printf("       ENTER MENU\n\n"
		   "1 - Create new file-cabinet\n\n"
		   "2 - Enter from file\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char printMenu()
{
	char choice;
	system("cls");
	printf("     OUTPUT TYPE MENU\n\n"
		   "1 - Output current file-cabinet\n\n"
		   "2 - Output from file\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char creamodMenu()
{
	char choice;
	system("cls");
	printf("     CREATE/MODIFY MENU\n\n"
		   "1 - Add game to file-cabinet\n\n"
		   "2 - Remove game from file-cabinet\n\n"
		   "3 - Change file-cabinet game field\n\n"
		   "4 - Data output\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char addMenu()
{
	char choice;
	system("cls");
	printf("                ADD MENU\n\n"
		   "1 - Add to the top of the file-cabinet\n\n"
		   "2 - Add to the end of the file-cabinet\n\n"
		   "3 - Add after selected game\n\n"
		   "4 - Add before selected game\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char remMenu()
{
	char choice;
	system("cls");
	printf("              REMOVE MENU\n\n"
		   "1 - Remove from the top of the file-cabinet\n\n"
		   "2 - Remove from the end of the file-cabinet\n\n"
		   "3 - Remove after selected game\n\n"
		   "4 - Remove before selected game\n\n"
		   "5 - Remove all games from file-cabinet\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char changeMenu()
{
	char choice;
	system("cls");
	printf("        CHANGE MENU\n\n"
		   "1 - Choose fields for change\n\n"
		   "2 - Change game info\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}



char outputMenu()
{
	char choice;
	system("cls");
	printf("          OUTPUT MENU\n\n"
		   "1 - Output size of file-cabinet\n\n"
		   "2 - Output selected game\n\n"
		   "3 - Output the file-cabinet\n\n"
		   "4 - Output in file\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char processMenu()
{
	char choice;
	system("cls");
	printf("    PROCESSING MENU\n\n"
		   "1 - Modify file-cabinet\n\n"
		   "2 - Sort file-cabinet\n\n"
		   "3 - Filter file-cabinet\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char sortMenu()
{
	char choice;
	system("cls");
	printf("          SORT MENU\n\n"
		   "1 - Select a field to sort\n\n"
		   "2 - Select a direction to sort\n\n"
		   "3 - Sort games in file-cabinet\n\n"
		   "4 - Output sort parametrs\n\n"
		   "5 - Output sorted the file-cabinet\n\n"
		   "6 - Output in file\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

char filtMenu()
{
	char choice;
	system("cls");
	printf("          FILTER MENU\n\n"
		   "1 - Select a fields to filter\n\n"
		   "2 - Filt games in file-cabinet\n\n"
		   "3 - Output filter parametrs\n\n"
		   "4 - Output filtered the file-cabinet\n\n"
		   "5 - Output in file\n\n"
		   "0 - Return to the menu\n\n\n"
		   "Input: ");
	choice = getChoice();
	return choice;
}

/*
 * [getChoice input]
 * @return [choice]
 */
char getChoice()
{
	char choice[3];	//user's choice

	fgets(choice, 3, stdin);
	fflush(stdin);

	//input validation
	if(choice[0] != '\n')
	    if(choice[1] != '\n')
	        choice[0] = '\0';

	return choice[0];
}

/*
 * [makeHead head list creation]
 * @param  all_head [pointers to all available lists]
 * @return          [head of a new list]
 */
GH* makeHead(int *error)
{
	GH *head;	// new head

	head = (GH*)malloc(sizeof(GH));	// memory allocation

	if (head)	// head initialization
	{
		head->first = NULL;
		head->last = NULL;
	}
	else
	{
		*error = 1;
		errorMes();
	}

	return head;
}

/*
 * [addFirst add a game to the top of the list]
 * @param head [head of the list]
 * @param game [added game]
 */
void addFirst(GH* head, GN* game)
{
	game->next = head->first;
	if (!(head->first))
		head->last = game;
	head->first = game;
}

/*
 * [addLast add a game to the end of the list]
 * @param head [head of the list]
 * @param game [added game]
 */
void addLast(GH* head, GN* game)
{
	if (!head->first)
		head->first = game;
	else
		(head->last)->next = game;
	head->last = game;
}

/*
 * [addAfter add after selected game]
 * @param head [head of the list]
 * @param game [added game]
 * @param pos  [position]
 */
void addAfter(GH* head, GN* game, int pos)
{
	GN *tmp;	// temporary pointer to the game
	int i;		// loop parametr

	if(pos == getSize(head) || !(getSize(head)))
		addLast(head, game);
	else
	{
		tmp = head->first;
		for(i = 1; i < pos; i++)
			tmp = tmp->next;
		game->next = tmp->next;
		tmp->next = game;
	}
}

/*
 * [addBefore add before selected game]
 * @param head [head of the list]
 * @param game [added game]
 * @param pos  [position]
 */
void addBefore(GH* head, GN* game, int pos)
{
	GN *tmp;	// temporary pointer to the game
	int i;		// loop parametr

	if(pos == 1 || !(getSize(head)))
		addFirst(head, game);
	else
	{
		tmp = head->first;
		for(i = 1; i < pos - 1; i++)
			tmp = tmp->next;
		game->next = tmp->next;
		tmp->next = game;
	}
}

/*
 * [remFirst remove from the top of the list]
 * @param head [source head pointer]
 */
void remFirst(GH** head)
{
	GN *game;
    if((*head)->first == (*head)->last)
		freeHead(head);
    else
    {
    	game = ((*head)->first);
        (*head)->first = game->next;
        freeGame(&game);
    }
}

/*
 * [remLast remove from the end of the list]
 * @param head [source head pointer]
 */
void remLast(GH** head)
{
	GN *game;
	if((*head)->first == (*head)->last)
		freeHead(head);
    else
    {
    	game = (*head)->first;
    	while((game->next)->next)
    		game = game->next;
        (*head)->last = game;
        freeGame(&(game->next));
        game->next = NULL;
    }
}

/*
 * [remAfter remove after selected game]
 * @param head [source head pointer]
 * @param pos  [position]
 */
void remAfter(GH** head, int pos)
{
	GN
	*game,
	*tmp;	// temporary 2 pointer to the game
	int i;	// loop parametr
	if(pos == getSize((*head)))
		remLast(head);
	else
	{
		tmp = (*head)->first;
		for(i = 1; i < pos; i++)
			tmp = tmp->next;
		game = tmp->next;
		tmp->next = game->next;
		freeGame(&game);
	}
}

/*
 * [remBefore remove before selected game]
 * @param head [source head pointer]
 * @param pos  [position]
 */
void remBefore(GH** head, int pos)
{
	GN
	*game,	// temporary 1 pointer to the game
	*tmp;	// temporary 2 pointer to the game
	int i;	// loop parametr
	if(pos == 1)
		remFirst(head);
	else
	{
		tmp = (*head)->first;
		for(i = 1; i < pos - 1; i++)
			tmp = tmp->next;
		game = tmp->next;
		tmp->next = game->next;
		freeGame(&game);
	}
}

/*
 * [makeNode element (game) of list creation]
 * @param  all_head [pointers to all available lists]
 * @return          [element (game) of list creation]
 */
GN* makeNode(int *error)
{
	GN* game;	// game that added in list

	game = (GN*)malloc(sizeof(GN));	// memory allocation

	// game initialization
	if (game)
	{
		game->name = NULL;
		game->dev = NULL;
		game->next = NULL;
	}
	else
	{
		*error = 1;
		errorMes();
	}

	return game;
}

/*
 * [gameInput entering game fields]
 * @param  all_head [pointers to all available lists]
 * @return          [game for list]
 */
GN* gameInput(int *error)
{
	GN* game; // game for list

	//new game struct adding
	game = makeNode(error);

	if(!(*error))
	{
		game->name = gameName(&game, 0, error);
		if(!(*error))
		{
			game->dev = gameDev(&game, 0, error);
			if(!(*error))
			{
				game->date = gameDate(1940, 0);
				game->price = gamePrice(0, 0);
				game->rating = gameRating(1, 0);
			}
		}
	}

	return game;
}


/*
 * [gameName entering game name]
 * @param  game     [pointer to game]
 * @param  all_head [pointers to all available lists]
 * @return          [game name]
 */
char* gameName(GN **game, int mode, int *error)
{
	char
	*mes,
	*name;		// game name

	int
	flag,
	len;		// string length

	if(mode)
		mes = "Enter all or part of game name";
	else
		mes = "Enter the name of the game";

	// game's name adding
	name = (char*)malloc(22 * sizeof(char));

	if (name)
	{
		system("cls");
		do
		{
			flag = 0;
			printf("You cannot use ',' in game name. %s\n"
				   "(maximum length 20 characters)\n\nInput: ", mes);
			fgets(name, 22, stdin);
			fflush(stdin);
			len = strLen(name);	// real name's length

			system("cls");
			if(len == 21)
				printf("You have entered more than 20 characters! Try again!\n\n");
			else
			{
				flag = findSym(name, ',', 0, len + 1);
				if(flag)
					printf("There is ',' in game name! Try again!\n\n");
			}
		} while (!len || (len == 21) || flag);

		name[len] = '\0';

		// freeing up extra memory
		name = (char*)realloc(name, (len + 1) * sizeof(char));
		if (!name)
		{
			*error = 1;
			freeGame(game);
			errorMes();
		}
	}
	else
	{
		*error = 1;
		freeGame(game);
		errorMes();
	}

	return name;
}

/*
 * [gameName entering game developer]
 * @param  game     [pointer to game]
 * @param  all_head [pointers to all available lists]
 * @return          [game developer]
 */
char* gameDev(GN **game, int mode, int *error)
{
	char
	*mes,
	*dev;	// game developer

	int
	flag,
	len;	// string length

	if(mode)
		mes = "Enter all or part of developer name";
	else
		mes = "Enter the name of the developer";

	dev = (char*)malloc(22 * sizeof(char));

	if (dev)
	{
		system("cls");
		do
		{
			flag = 0;
			printf("You cannot use ',' in developer name. %s\n"
				   "(maximum length 20 characters)\n\nInput: ", mes);
			fgets(dev, 22, stdin);
			fflush(stdin);
			len = strLen(dev);	//real name's length

			system("cls");
			if(len == 21)
				puts("You have entered more than 20 characters! Try again!\n");
			else
			{
				flag = findSym(dev, ',', 0, len + 1);
				if(flag)
					printf("There is ',' in developer name! Try again!\n\n");
			}
		} while (!len || (len == 21) || flag);

		dev[len] = '\0';

		// freeing up extra memory
		dev = (char*)realloc(dev, (len + 1) * sizeof(char));
		if (!dev)
		{
			*error = 1;
			freeGame(game);
			errorMes();
		}
	}
	else
	{
		*error = 1;
		freeGame(game);
		errorMes();
	}

	return dev;
}

/*
 * [gameDate game date formation]
 * @return [game release date]
 */
int gameDate(int min, int mode)
{
	int
	date,			// release date
	len;			// real length of text

	char
	*mes1,
	*mes2,
	str[6];	// temporary string

	if(min == 1940)
	{
		mes1 = "It is impossible!\nThe first computer game was released only in 1940!\n";
		if(mode)
			mes2 = " MINIMUM";
		else
			mes2 = " ";
	}
	else
	{
		mes1 = "Maximum year release cannot be less then minimum!\n";
		mes2 = " MAXIMUM";
	}

	system("cls");
	do
	{
		printf("Enter%s release year\n(minimum value - %d, maximum value - 2020)\n\nInput: ", mes2, min);

		fgets(str, 6, stdin);
		fflush(stdin);
		len = strLen(str);	// real length

		//conrol of year
		if (len)
		{
			date = fromStrToNum(str, len+ 1);
			system("cls");
			if (date == -1)
				printf("You entered an invalid year. Try again!\n\n");
			else
				if (date < min)
					printf("%sYou entered an invalid year. Try again!\n\n", mes1);
				else
					if (date > 2020)
						printf("You cannot enter a year, that has not yet arrived! Try again!\n\n");
		}
		else
		{
			date = -1;
			system("cls");
		}
	} while (date < min || date > 2020);

	return date;
}

/*
 * [gamePrice game price formation]
 * @return [game price]
 */
int gamePrice(int min, int mode)
{
	int
	price,			// game price
	len;			// real length of text

	char
	*mes,
	str[7];	// temporary string

	if(mode)
	{
		if(min)
			mes = " MAXIMUM";
		else
			mes = " MINIMUM";
	}
	else
		mes = " ";

	do
	{
		printf("Enter%s the price in rubles\n(minimum value - %d, "
			   "maximum value - 20000):\n\nInput: ", mes, min);

		fgets(str, 7, stdin);
		fflush(stdin);
		len = strLen(str);	// real length

		// control of price
		if (len)
		{
			price = fromStrToNum(str, len + 1);
			system("cls");
			if (price == -1)
				printf("You entered an incorrect price. Try again!\n\n");
			else
				if(price < min)
					printf("Maximum game price cannot be less then minimum!\n\n");
				else
					if (price > 20000)
						printf("The price is too high!. The maximum price of "
						 	   "20,000 rubles.\nTry again!\n\n");
		}
		else
		{
			price = -1;
			system("cls");
		}
	} while (price < min || price > 20000);

	return price;
}

/*
 * [gameRating game rating formation]
 * @return [game rating]
 */
int gameRating(int min, int mode)
{
	int
	rating,	// game rating
	len;	// real length of text

	char
	*mes,
	str[4];	// temporary string

	if(mode)
	{
		if(min)
			mes = " MAXIMUM";
		else
			mes = " MINIMUM";
	}
	else
		mes = " ";

	do
	{
		printf("Enter%s user rating\n(minimum value - %d, maximum value - 10):\n\nInput: ", mes, min);

		fgets(str, 4, stdin);
		fflush(stdin);
		len = strLen(str);	// real length

		// control of rating
		if (len)
		{
			rating = fromStrToNum(str, len + 1);
			system("cls");
			if (rating < 1)
				printf("You have entered an incorrect rating. Try again!\n\n");
			else
				if (rating < min)
					printf("Maximum game rating cannot be less then minimum!\n\n");
				else
					if (rating > 10)
						printf("Rating is too high!. Maximum rating 10.\nTry again!\n\n");
		}
		else
		{
			rating = 0;
			system("cls");
		}
	} while (rating < min || rating > 10);

	return rating;
}

/*
 * [getSize getting list size]
 * @param  head [head of list]
 * @return      [list size]
 */
int getSize(GH *head)
{
	GN* game;	// another game in list
	int size;	// list size

	if(head)
		game = head->first;
	else
		game = NULL;

	size = 0;
	while (game)
	{
		game = game->next;
		size++;
	}

	return size;
}

/*
 * [listCopy copy list]
 * @param  head     [source head pointer]
 * @param  all_head [pointers to all available lists]
 * @return          [copied of source list]
 */
GH* listCopy(GH *head, int *error)
{
	GH
	*chead;		// copied head

	GN
	*game,		// copied element
	*tmp;		// helper variable

	chead = makeHead(error); // allocating memory

	if(!(*error))
	{
		game = gameCopy(head->first, error);
		if(!(*error))
		{
			chead->first = game;

			while (game->next && !(*error))
			{
				tmp = gameCopy(game->next, error);	// copy the element
				if(!(*error))
				{
					game->next = tmp;
					game = game->next;	// shift the original list
				}
				else
				{
					freeHead(&chead);
					errorMes();
				}
			}
		}
		else
		{
			freeHead(&chead);
			errorMes();
		}

		chead->last = game;
	}

	return chead;
}

/*
 * [gameCopy copy game]
 * @param  orig     [original game]
 * @param  all_head [pointers to all available lists]
 * @return          [copied game]
 */
GN* gameCopy(GN *orig, int *error)
{
	GN *copy;	// copied game
	char *str;	// temporary string
	int len;	// length of string

	copy = makeNode(error);	// allocating memory
	if(copy)
	{
		// copy the fields of the element from the original
		len = strLen(orig->name) + 1;
		str = (char*)malloc(len * sizeof(char));
		if (str)
		{
			strCopy(str, orig->name, len);
			copy->name = str;
			len = strLen(orig->dev) + 1;
			str = (char*)malloc(len * sizeof(char));
			if (str)
			{
				strCopy(str, orig->dev, len);
				copy->dev = str;
				copy->date = orig->date;
				copy->price = orig->price;
				copy->rating = orig->rating;
				copy->next = orig->next;
			}
			else
			{
				*error = 1;
				freeGame(&copy);
				errorMes();
			}
		}
		else
		{
			*error = 1;
			freeGame(&copy);
			errorMes();
		}
	}
	else
		errorMes();

	return copy;
}

/*-------------------------list conversion functions-------------------------*/

/*
 * [sort sorting source list]
 * @param  head  [source head pointer]
 * @param  all_head [pointers to all available lists]
 * @param  cmp   [pointer to function call point]
 * @return       [source list]
 */
void sort(GH *head, int (*cmp)(GN*, GN*), int sdir)
{
	GN
	*game,		// game in list
	*tmp,		// temporary variable
	*pgame;		// previous game in list

	int
	i,			// loop parametr
	j,			// loop parametr
	size,		// size of head
	flag;		// result of condition

	size = getSize(head);

	// optimized bubble sort
	i = 0;
	do
	{
		flag = 0;
		game = head->first;
		pgame = NULL;
		for (j = 0; j < size - i - 1; j++)
		{
			if ((cmp(game, game->next) % 2) ^ sdir)
			{
				// swap extreme elements
				tmp = game->next;
				if ((pgame != tmp) && pgame)
					pgame->next = tmp;
				if(j == 0)
					head->first = tmp;
				game->next = tmp->next;
				pgame = tmp;
				tmp->next = game;
				flag = 1;
			}
			else
			{
				// just moving on down the list
				pgame = game;
				game = game->next;
			}
		}
		if (!i)
			head->last = game;
		i++;

	} while (flag);
}

/*
 * [filter filtering source list]
 * @param  head  [source head pointer]
 * @param  all_head [pointers to all available lists]
 * @param  cmp   [pointer to the first element in an array of function pointers]
 * @return       [copied game]
 */
void filter(GH *param, GH **head, char *ffield, int (**cmp)(GN*, GN*))
{
	GN
	*game,		// game in list
	*tmp,		// temporary variable
	*pgame;		// previous game in list

	int
	i,			// loop parametr
	j;			// parametr

	// filter until parameters or list ends
	i = 0;
	while(*head && ffield[i] != '\0')
	{
		j = (int)(ffield[i] - 49);

		game = (*head)->first;
		pgame = NULL;

		while (game)
		{
			if (((*cmp[j])(param->first, game) % 2) ||		// G < P1 -> remove
				(((*cmp[j])(game, param->last) % 2) &&	// G > P2 -> remove
				((*cmp[j])(game, param->last) != 3)))	// additional condition for string
			{
				tmp = game;
				if (pgame)
					pgame->next = game->next;
				else
					(*head)->first = game->next;
				freeGame(&tmp);
			}
			else
				pgame = game;

			game = game->next;
		}

		(*head)->last = pgame;

		if(!((*head)->first))
			freeHead(head);
		i++;
	}
}

/*---------------------------comparison functions----------------------------*/

/*
 * [cmpDate date comparison]
 * @param  game1 [game in list]
 * @param  game2 [game in list]
 * @return       [comparison result]
 */
int cmpDate(GN* game1, GN* game2)
{
	int res;	// result

	if (game1->date == game2->date)
		res = 0;
	else
		if (game1->date > game2->date)
			res = 1;
		else
			res = 2;

	return res;
}

/*
 * [cmpRating rating comparison]
 * @param  game1 [game in list]
 * @param  game2 [game in list]
 * @return       [comparison result]
 */
int cmpRating(GN* game1, GN* game2)
{
	int res;	// result

	if (game1->rating == game2->rating)
		res = 0;
	else
		if (game1->rating > game2->rating)
			res = 1;
		else
			res = 2;

	return res;
}

/*
 * [cmpPrice price comparison]
 * @param  game1 [game in list]
 * @param  game2 [game in list]
 * @return       [comparison result]
 */
int cmpPrice(GN* game1, GN* game2)
{
	int res;	// result

	if (game1->price == game2->price)
		res = 0;
	else
		if (game1->price > game2->price)
			res = 1;
		else
			res = 2;

	return res;
}

/*
 * [cmpName name comparison]
 * @param  game1 [game in list]
 * @param  game2 [game in list]
 * @return       [comparison result]
 */
int cmpName(GN* game1, GN* game2)
{
	int res;	// result

	res = strCmp(game1->name, game2->name);

	if (res == 0)
    {
		if (strLen(game1->name) > strLen(game2->name))
			res = 3;
		else
			if(strLen(game1->name) < strLen(game2->name))
				res = 4;
    }

	return res;
}

/*
 * [cmpDev developer comparison]
 * @param  game1 [game in list]
 * @param  game2 [game in list]
 * @return       [comparison result]
 */
int cmpDev(GN* game1, GN* game2)
{
	int res;	// result

	res = strCmp(game1->dev, game2->dev);

	if (res == 0)
    {
		if (strLen(game1->dev) > strLen(game2->dev))
			res = 3;
		else
			if(strLen(game1->dev) < strLen(game2->dev))
				res = 4;
    }

	return res;
}

/*
 * [listPrint output list]
 * @param head [head of some list]
 */
void listPrint(GH* head)
{
	GN* game;	// game in list

	int
	size,		// size pf list
	i;			// loop parametr

	game = head->first;
	size = getSize(head);
	system("cls");

	//some information for user
	if(size > 8)
		puts("\t\t     To output the next group of\n"
			"\t\t games from the sequence, press any key\n");

	printf("  Total games are listed: %d\n", size);

	//header
	puts("  +---+----------------------+------------"
		"----------+------+-------+--------+\n"
		"  | N |                 Name |            Developer "
		"| Date | Price | Rating |\n"
		"  +---+----------------------+------------"
		"----------+------+-------+--------+");

	//main information
	for (i = 0; i < size; i++)
	{
		printf("  |%2.d | %20s | %20s | %d | %5.1d |   %2.d   |\n"
			"  +---+----------------------+------------"
			"----------+------+-------+--------+\n",
			i + 1, game->name,
			game->dev, game->date,
			game->price, game->rating);

		if ((i + 1) % 8 == 0 && size > 8)
			getch();

		game = game->next;
	}
	pause();
}

/*----------------------functions for work with strings----------------------*/

/*
 * [strLen string length determination]
 * @param  str [string]
 * @return     [length of string]
 */
int strLen(char *str)
{
	int len;	//loop parameter and length of string

	len = 0;
	while (str[len] != '\n' && str[len] != '\0')
		len++;

	return len;
}

/*
 * [findSym searching symbol in string]
 * @param  str [string]
 * @param  sym [symbol]
 * @param  len [kength]
 * @return     [result of searching]
 */
int findSym(char* str, char sym, int pos, int len)
{
	int res;	// result

	res = 0;

	for(int i = pos; i < len && !res; i++)
		if(*(str + i) == sym)
			res = 1;

	return res;
}

/*
 * [fromCharToNum conversation from char to num]
 * @param  str [string]
 * @param  len [length of string]
 * @return     [converted number]
 */
int fromStrToNum(char *str, int len)
{
	int
	i,		// loop parameter
	num,	// converted number
	step;	// step of 10

	// assignment of initial values
	num = 0;
	step = 1;

	// loop of conversion
	if (str[0] != '0' || (str[0] == '0' && len == 2))
		for (i = len - 2; i >= 0 && num >= 0; i--)
		{
			if ('0' <= str[i] && str[i] <= '9')
			{
				num += (int)(str[i] - 48) * step;
				step *= 10;
			}
			else
				num = -1;
		}
	else
		num = -1;

	return num;
}

/*
 * [strCopy copy string]
 * @param  cstr [copy string]
 * @param  ostr [original strung]
 * @param  len  [length of string]
 */
void strCopy(char *cstr, char *ostr, int len)
{
	int i;		// loop parametr

	for (i = 0; i < len; i++)
		cstr[i] = ostr[i];
}

/*
 * [strCmp comparison strings]
 * @param  str1 [string]
 * @param  str2 [string]
 * @return      [comparison result]
 */
int strCmp(char* str1, char* str2)
{
	int min_len,	// smallest length among two strings
		res,		// comparison result
		i;			// loop's parameter / string's position

	res = 0;	// assignment of initial values

	// determination of the smallest length
	if (strLen(str1) < strLen(str2))
		min_len = strLen(str1);
	else
		min_len = strLen(str2);

	// string character comparison loop
	for (i = 0; i < min_len && !res; i++)
		if (str1[i] != str2[i])
		{
			if(str1[i] > str2[i])
				res = 1;
			else
				res = 2;
		}

	return res;
}

/*
 * [errorMes print error massage]
 */
void errorMes()
{
	system("cls");
	printf("Memory allocation error! The program ends its work");
	pause();
}

/*
 * [pause pause program]
 */
void pause()
{
	printf("\n\nTo continue, press any key ...");
	getch();
}


void freeGame(GN** game)
{
	if(*game)
	{
		if ((*game)->name)
		{
			free((*game)->name);
			(*game)->name = NULL;
		}
		if ((*game)->dev)
		{
			free((*game)->dev);
			(*game)->dev = NULL;
		}

		free(*game);
		*game = NULL;
	}
}


void freeHead(GH** head)
{
	GN
	*game,
	*tmp;
	if (*head)
	{
		if((*head)->first)
		{
			game = (*head)->first;
			while(game)
			{
				tmp = game->next;
				freeGame(&game);
				game = tmp;
			}
		}
		free(*head);
		*head = NULL;
	}
}


void delAll(GH** head, GH** param, GH** oth)
{
	if (*head)
        freeHead(head);
    if (*param)
        freeHead(param);
    if (*oth)
        freeHead(oth);
}

void saveFile(GH *head, char *fname)
{
    FILE
    *file;

    GN *game;

    char
    choice,
    str[7];

    int
    flag,
    amt;

    amt = 0;
    flag = 1;

    file = fopen(fname, "r");
    if (file != NULL)
    {
    	rewind(file);
    	fseek(file, 0, SEEK_END);
    	amt = ftell(file);
    	rewind(file);
    	fclose(file);
    }

    if(amt)
    {
    	system("cls");
    	do
		{
			printf("The file already contains some information. "
    		       "Having saved the current card file in it,\n"
    		       "the information contained in it will be lost. "
    		       "Continue? (0 - no, 1 - yes)\n\nInput: ");
			choice = getChoice();
			system("cls");
			if(choice != '0' && choice!= '1' && choice != '\n')
			{
				printf("Incorrect command. Try again!\n\n");
			}
		}
		while(choice != '0' && choice != '1');

		if(choice == '0')
			flag = 0;
    }

    if(flag)
    {
	    if ((file = fopen(fname, "w")) != NULL)
	    {
	    	game = head->first;
	    	while (game)
	    	{
	        	fputs(game->name, file);
	        	fputc(',', file);
	        	fputs(game->dev, file);
	        	fputc(',', file);
	        	fputs(itoa(game->date, str, 10), file);
	        	fputc(',', file);
	        	fputs(itoa(game->price, str, 10), file);
	        	fputc(',', file);
	        	fputs(itoa(game->rating, str, 10), file);
	        	fputc('\n', file);
	        	game = game->next;
	        }
	        fclose(file);
	        system("cls");
	        printf("Successfull!");
	        pause();
	    }
	    else
	    {
	    	system("cls");
	    	printf("The specified directory does not exist! "
	    		   "The file-cabinet isn't saved.");
	    	pause();
	    }
	}
	else
	{
		system("cls");
    	printf("The file-cabinet isn't saved.");
    	pause();
	}
}

GH* readFile(char *fname, int *error)
{
	FILE *file;

    GH *head;

    GN *game;

    int
    i,
    flag,
    cnt,
    row,
    amt;

    char
    sym,
    str[22];

    head = NULL;
    amt = 0;
    cnt = 0;
    row = 1;
    game = NULL;

    if ((file = fopen(fname, "r")) != NULL)
	{
		rewind(file);
        fseek(file, 0, SEEK_END);
        amt = ftell(file);
        rewind(file);

        if(amt)
        {
        	amt = 0;
        	while((sym = fgetc(file)) != EOF) amt++;
        	rewind(file);

	        head = makeHead(error);
	        if(!(*error))
	        {
	        	game = makeNode(error);
	    		head->first = game;
		        head->last = game;
	        }

	        flag = 0;
	        while(amt != cnt && !flag && !(*error))
	        {
	        	if(row > 1)
	    		{
	    			game->next = makeNode(error);
	    			game = game->next;
	    		}

	    		if(!(*error))
	    		{
		    		i = 0;
		    		sym = '\0';
		    		while(i < 22 && sym != ',' && cnt != amt)
		    		{
		    			sym = fgetc(file);
						if (sym != ',')
							str[i] = sym;
						i++;
						cnt++;
		    		}

		    		if(sym != ',')
		    		{
		    			flag = 1;
						system("cls");
		    			printf("Error! The name of the game in line %d exceeds the allowed size!\n"
							   "Maximum string length is 20", row);
		    			pause();
		    		}
		    		else
		    		{
		    			str[i-1] = '\0';
						game->name = (char*)malloc(i * sizeof(char));
						if (game->name)
							strCopy(game->name, str, i);
						else
						{
							*error = 1;
							freeHead(&head);
							errorMes();
						}
		    		}

		    		if(!flag && !(*error))
	    			{
			    		i = 0;
			    		sym = '\0';
			    		while(i < 22 && sym != ',' && cnt != amt)
			    		{
			    			sym = fgetc(file);
							if (sym != ',')
								str[i] = sym;
							i++;
							cnt++;
			    		}

			    		if(sym != ',')
			    		{
			    			flag = 1;
							system("cls");
			    			printf("Error! The developer of the game in line %d exceeds the allowed size!\n"
								   "Maximum string length is 20", row);
			    			pause();
			    		}
			    		else
			    		{
			    			str[i-1] = '\0';
							game->dev = (char*)malloc(i * sizeof(char));
							if (game->dev)
								strCopy(game->dev, str, i);
							else
							{
								*error = 1;
								freeHead(&head);
								errorMes();
							}
			    		}

			    		if(!flag && !(*error))
			    		{
				    		i = 0;
				    		sym = '\0';
				    		while(i < 5 && sym != ',' && cnt != amt)
				    		{
				    			sym = fgetc(file);
				    			if (sym != ',')
									str[i] = sym;
								i++;
								cnt++;
				    		}

				    		if(sym != ',')
				    		{
				    			game->date = fromStrToNum(str, i + 1);
				    			flag = 1;
				    			system("cls");
								if (game->date == -1)
									printf("Error! Invalid date in line %d.", row);
								else
									printf("Error! You cannot enter a year, that has not yet arrived!\n"
										   "Date in line %d doesn't meet the requirements.", row);
								pause();
				    		}
				    		else
				    		{
				    			str[i-1] = '\0';
								game->date = fromStrToNum(str, i);
								if (game->date == -1)
								{
									flag = 1;
									system("cls");
									printf("Error! Invalid date in line %d.", row);
									pause();
								}
								else
									if (game->date < 1940)
									{
										flag = 1;
										system("cls");
										printf("Error! The first computer game was released only in 1940!\n"
											   "Date in line %d doesn't meet the requirements.", row);
										pause();
									}
									else
										if (game->date > 2020)
										{
											flag = 1;
											system("cls");
											printf("Error! You cannot enter a year, that has not yet arrived!\n"
											       "Date in line %d doesn't meet the requirements.", row);
											pause();
										}
				    		}

				    		if(!flag && !(*error))
				    		{
					    		i = 0;
					    		sym = '\0';
					    		while(i < 6 && sym != ',' && cnt != amt)
					    		{
					    			sym = fgetc(file);
					    			if (sym != ',')
										str[i] = sym;
									i++;
									cnt++;
					    		}

					    		if(sym != ',')
					    		{
					    			game->price = fromStrToNum(str, i + 1);
					    			flag = 1;
					    			system("cls");
									if (game->price == -1)
										printf("Error! Invalid price in line %d.", row);
									else
										printf("Error! Price is too high! The maximum price of 20,000 rubles.\n"
											   "Price in line %d doesn't meet the requirements.", row);
									pause();
					    		}
					    		else
					    		{
					    			str[i-1] = '\0';
									game->price= fromStrToNum(str, i);
									if (game->price == -1)
									{
										flag = 1;
										system("cls");
										printf("Error! Invalid price in line %d.", row);
										pause();
									}
									else
										if (game->price > 20000)
										{
											flag = 1;
											system("cls");
											printf("Error! Price is too high! The maximum price of 20,000 rubles.\n"
										   		   "Price in line %d doesn't meet the requirements.", row);
											pause();
										}
					    		}

					    		if(!flag && !(*error))
					    		{
						    		i = 0;
						    		sym = '\0';
						    		while(i < 3 && sym != '\n' && cnt != amt)
						    		{
						    			sym = fgetc(file);
						    			if (sym != '\n')
											str[i] = sym;
										i++;
										cnt++;
						    		}

						    		if(sym != '\n' && cnt != amt)
						    		{
						    			game->rating = fromStrToNum(str, i + 1);
						    			flag = 1;
						    			system("cls");
										if (game->rating == -1)
											printf("Error! Invalid rating in line %d.", row);
										else
											printf("Error! Rating is too high!. Maximum rating 10.\n"
												   "Rating in line %d doesn't meet the requirements.", row);
										pause();
						    		}
						    		else
						    		{
						    			if(sym != '\n')
						    				i++;
						    			str[i-1] = '\0';
										game->rating = fromStrToNum(str, i);
										if (game->rating == -1)
										{
											flag = 1;
											system("cls");
											printf("Error! Invalid rating in line %d.", row);
											pause();
										}
										else
											if (game->rating > 20000)
											{
												flag = 1;
												system("cls");
												printf("Error! Rating is too high!. Maximum rating 10.\n"
											   		   "Rating in line %d doesn't meet the requirements.", row);
												pause();
											}
						    		}
						    		row++;
						    	}
					    	}
				    	}
			    	}
		    	}
	        }
	        if(flag || *error)
	        	freeHead(&head);
	        else
	        	head->last = game;
	   	}
	   	else
	   	{
	   		system("cls");
    		printf("File is empty!");
    		pause();
	   	}
        fclose(file);
	}
	else
	{
		system("cls");
    	printf("The specified directory or file doesn't exist! "
    		   "The file was not read.");
    	pause();
	}

	return head;
}

void cntMes(int row)
{
	system("cls");
	printf("Error on line %d. There is not enough data in the file", row);
	pause();
}


char* fileName(int *error)
{
	int
	len,
	flag;

	char* fname;

	fname = (char*)malloc((MAX_PATH + 1) * sizeof(char));
	if(fname)
	{
		system("cls");
		do
		{
			flag = 0;

			printf("Enter file name in format:\nC:\\...\\filename.csv\n\n"
				   "Max length of name %d.\n"
				   "You can use only \"txt\" or \"csv\" format.\n"
				   "If you want to go back, enter 0.\n\n"
				   "Your location rigth now:\n", MAX_PATH);
			system("cd");
			printf("\n\nInput: ");

			fgets(fname, 261, stdin);
			fflush(stdin);

			len = strLen(fname);
			fname[len] = '\0';

			if(len == 0 && fname[0] == '\0')
			{
				flag = 1;
				system("cls");
			}
			else
				if(len == 1 && fname[0] == '0')
				{
					free(fname);
					fname = NULL;
				}
				else
				{
					if(len > MAX_PATH)
					{
						system("cls");
						printf("You enter more then %d symbols. Try again!\n\n", MAX_PATH);
						flag = 1;
					}
					else
						if(!(parser(fname, len + 1)))
						{
							system("cls");
							printf("You specified an impossible file path. Try again!\n\n");
							flag = 1;
						}
						else
							if(len < 4)
							{
								system("cls");
								printf("You can use only \"txt\" or \"csv\" format. Try again!\n\n");
								flag = 1;
							}
							else
								if((fname[len-3] != 't' || fname[len-2] != 'x' || fname[len-1] != 't') &&
									(fname[len-3] != 'c' || fname[len-2] != 's' || fname[len-1] != 'v'))
								{
									system("cls");
									printf("You can use only \"txt\" or \"csv\" format. Try again!\n\n");
									flag = 1;
								}
								else
									if((fname = (char*)realloc(fname, (len + 1) * sizeof(char))) == NULL)
									{
										*error = 1;
										errorMes();
									}
				}
		}
		while(flag);
	}
	else
	{
		*error = 1;
		errorMes();
	}

	return fname;
}

int parser(char* str, int len)
{
	int
	i,
	flag,
	res;

	flag = 0;
	res = 1;

	if('A' <= str[0] && str[0] <= 'Z' && str[1] == ':' && str[2] == '\\')
	{
		i = 3;
		if(str[i] == '.')
			res = 0;
	}
	else
	{
		i = 0;
		if(str[0] == '\\')
			res = 0;
	}

	while(i < len && res)
	{
		if(findSym("/:*?\"<>|+%!@", str[i], 0, 12))
			res = 0;
		else
			if(str[i] == '\\' && (str[i-1] == '\\' || str[i-1] == ' '))
				res = 0;
			else
				if(str[i] == '.')
				{
					flag = 1;
					if(i + 1 == len)
						res = 0;
					else
						if(findSym(str, '.', i + 1, len))
							res = 0;
				}
		i++;
	}

	if(res)
	{
		if(!flag)
			res = 0;
		if(str[len - 1] == '.')
			res = 0;
	}

	return res;
}

int needSave(GH *head, int *error)
{
	char
	*fname,
	choice;

	int flag;

	flag = 0;

	system("cls");
	do
	{

		printf("You didn't save file-cabinet on computer!\n"
			   "Save it? (0 - no, 1 - yes)\n\n"
			   "Input: ");
		choice = getChoice();
		if(choice != '0' && choice!= '1' && choice != '\n')
		{
			system("cls");
			printf("Incorrect command. Try again!\n\n");
		}
	}
	while(choice != '0' && choice != '1');

	if(choice == '1')
	{
		fname = fileName(error);
		if(fname && !(*error))
        {
			saveFile(head, fname);
			if(head)
				flag = 1;
			free(fname);
			fname = NULL;
		}
		else
		{
			system("cls");
			printf("File-cabinet didn't saved!\n");
			pause();
		}
	}

	return flag;
}

void errorCheck(int error, GH **head, GH **param, GH **oth, char **fname)
{
	if(error)
	{
		delAll(head, param, oth);
		if(*fname)
            free(*fname);
		exit(-1);
	}
}

void gameChange(GH *head, char *field, int pos, int *error)
{
	int i;
	GN *game;

	game = head->first;
	for(i = 0; i < pos - 1; i++)
		game = game->next;

	for(i = 0; i < strLen(field) + 1 && !(*error); i++)
	{
		if(field[i] == '1')
		{
			free(game->name);
			game->name = NULL;
			game->name = gameName(NULL, 0, error);
		}

		if(field[i] == '2')
		{
			free(game->dev);
			game->dev = NULL;
			game->dev = gameDev(NULL, 0, error);
		}

		if(field[i] == '3')
			game->date = gameDate(1940, 0);

		if(field[i] == '4')
			game->price = gamePrice(0, 0);

		if(field[i] == '5')
			game->rating = gameRating(1, 0);
	}
}

void fieldChoice(char* field, int mode)
{
	int
	i,		// loop parametr
	j,		// loop parametr
	flag,	// condition check
	len; 	// length of string

	char *mes;

	if(mode)
		mes = "Enter fields that you want to change.";
	else
		mes = "Enter fields for filtering.";

	do
	{
		printf("%s\nThe line should not be empty and contain extraneous "
			   "characters including the space character.\n"
			   "In the line, the selected numbers should not be repeated!\n\n"
			   "Choose one of the field:\n\n"
			   "\t1 - game name\n"
			   "\t2 - developer name\n"
			   "\t3 - release date\n"
			   "\t4 - game price\n"
			   "\t5 - game rating\n\n"
			   "Input: ", mes);

		fgets(field, 7, stdin);
		fflush(stdin);

		len = strLen(field);
		field[len] = '\0';

		// checking data
		if(!len)
			flag = 0;
		else
		{
			flag = 1;
			for(i = 0; i < len && flag; i++)
				flag = findSym("12345", field[i], 0, 5);
		}
		system("cls");

		// check data for retry
		if(flag)
		{
			for(i = 0; i < len && flag; i++)
				for(j = 0; j < len && flag; j++)
					if(j != i && field[i] == field[j])
						flag = 0;
			if(!flag)

				puts("The line has duplicate commands. Try again!\n");
		}
		else
			if(field[0] != '\0')
				puts("In the line there are symbols in addition\n"
					"to the numbers of the selected parameters. Try again!\n");
	}
	while(!flag);
}

int getPos(GH* head)
{
	int
	size,
	pos,		// position
	len;		// real length of text

	char
	str[11];	// temporary string

	size = getSize(head);

	system("cls");
	do
	{
		printf("Elements in list: %d\n\n"
               "Enter position of game in list"
               "(minimum value - 1, maximum value - %d)"
               "\n\nInput: ", size, size);
		fgets(str, 11, stdin);
		fflush(stdin);
		len = strLen(str);

		// conrol of position
		system("cls");
		if (len)
		{
			pos = fromStrToNum(str, len+ 1);
			if (pos == -1)
				printf("Invalid input. Try again!\n");
			else
				if (pos < 1)
					printf("It is impossible! Minimum value - 1. Try again!\n");
				else
					if(pos > size)
						printf("It is impossible! Maximum value value - %d. Try again!\n", size);
		}
		else
			pos = 0;
	} while (pos < 1 || pos > size);

	return pos;
}

void emptyMes()
{
	system("cls");
	printf("There are no games in the file-cabinet!");
	pause();
}

void incMes()
{
	system("cls");
	printf("Incorrect command!");
    pause();
}

void gamePrint(GH* head, int pos)
{
    GN *game;   // game in list
    int i;      // loop parametr

    game = head->first;

    for(i = 0; i < pos - 1; i++)
        game = game->next;

    printf("Information on the game in %d position:\n\n"
        "<Name>         %s\n<Developer>    %s\n<Date>         %d\n"
        "<Price>        %d\n<Rating>       %d",
        pos, game->name, game->dev, game->date, game->price, game->rating);
    pause();
}

/*
 * [sortFieldSelect field selection for sorting]
 * @return [user's choice]
 */
int sortFieldSelect()
{
	char choice; // user's choice

	// do while there is no correct input
	do
	{
		system("cls");

		// print options for choosing
		printf("Choose one of the items:\n\n"
			"\t1 - Sort by name\n"
			"\t2 - Sort by developer\n"
			"\t3 - Sort by game release date\n"
			"\t4 - Sort by price of game\n"
			"\t5 - Sort by rating of game\n\n");
		printf("Input: ");

		// user make choice
		choice = getChoice();

		// output if invalid input
		if(choice < '1' || choice > '5')
			incMes();
	}
	while (choice < '1' || choice > '5');

	return (int)(choice - 49);
}

/*
 * [sortDirSelect selection of direction for sorting]
 * @return [user's choice]
 */
int sortDirSelect()
{
	char choice; // user's choice

	// do while there is no correct input
	do
	{
		system("cls");

		// print menu
		printf("Note: The characters in the original order (from smallest to largest)\n"
			"are arranged according to the order in the ASCII table.\n\n"
			"Choose one of the items:\n\n"
			"\t1 - Sort the list in ascending order\n"
			"\t2 - Sort the list in descending order\n\n"
			"Input: ");

		// user make choice
		choice = getChoice();

		// output if invalid input
		if(choice < '1' || choice > '2')
			incMes();
	}
	while (choice < '1' || choice > '2');

	return (int)(choice - 49);
}


/*
 * [sortParamPrint output sort parametr]
 * @param sfield [field for sort]
 * @param sdir   [direction for sort]
 */
void sortParamPrint(int sfield, int sdir)
{
	system("cls");
	printf("Selected options for sorting the list\n\n"
		"<Field>        ");

	switch (sfield)
	{
		case 0:
			printf("Name");
			break;
		case 1:
			printf("Developer");
			break;
		case 2:
			printf("Date");
			break;
		case 3:
			printf("Price");
			break;
		case 4:
			printf("Rating");
			break;
		default:
			printf("!nothing!");
	}

	printf("\n\n<Direction>    ");

	switch (sdir)
	{
		case 0:
			printf("Ascending");
			break;
		case 1:
			printf("Descending");
			break;
		default:
			printf("!nothing!");
	}

	pause();

}

GH* paramMake(char *ffield, int *error)
{
	GH* param;
	int len;

	len = strLen(ffield);

	param = makeHead(error);
	if(!(*error))
	{
		param->first = makeNode(error);
		if(!(*error))
		{
			param->last = makeNode(error);
			(param->first)->next = param->last;
			if(!(*error))
			{
				if(findSym(ffield, '1', 0, len))
				{
					(param->first)->name = gameName(&(param->first), 1, error);
					(param->last)->name = (param->first)->name;
				}

				// parametrs developer formation
				if(findSym(ffield, '2', 0, len))
				{
					(param->first)->dev = gameDev(&(param->first), 1, error);
					(param->last)->dev = (param->first)->dev;
				}

				// parametrs date formation
				if(findSym(ffield, '3', 0, len))
				{
					(param->first)->date = gameDate(1940, 1);
					if((param->first)->date != 2020)
						(param->last)->date = gameDate((param->first)->date, 1);
					else
						(param->last)->date = 2020;
				}
				else
				{
					(param->first)->date = -1;
					(param->last)->date = -1;
				}

				// parametrs price formation
				if(findSym(ffield, '4', 0, len))
				{
					(param->first)->price = gamePrice(0, 1);
					if((param->first)->price != 20000)
						(param->last)->price = gamePrice((param->first)->price, 1);
					else
						(param->last)->price = 20000;
				}
				else
				{
					(param->first)->price = -1;
					(param->last)->price = -1;
				}

				// parametrs rating formation
				if(findSym(ffield, '5', 0, len))
				{
					(param->first)->rating = gameRating(1, 1);
					if((param->first)->rating != 10)
						(param->last)->rating = gamePrice((param->first)->rating, 1);
					else
						(param->last)->rating = 10;
				}
				else
				{
					(param->first)->rating = -1;
					(param->last)->rating = -1;
				}
			}
			else
				errorMes();
		}
		else
			errorMes();
	}
	else
		errorMes();

	return param;
}

void filtParamPrint(GH* param)
{
	printf("Selected options for filtering\n"
		   "the list and their values:\n\n");

	if((param->first)->name)
		printf("<Name>         %s\n", (param->first)->name);

	if((param->first)->dev)
		printf("<Developer>    %s\n", (param->first)->dev);

	if((param->first)->date != -1)
    {
		if((param->first)->date != (param->last)->date)
			printf("<Min date>     %d\n"
				   "<Max date>     %d\n",
				   (param->first)->date, (param->last)->date);
		else
			printf("<Date>         %d\n",
				   (param->first)->date);
    }

	if((param->first)->price != -1)
    {
		if((param->first)->price != (param->last)->price)
			printf("<Min price>    %d\n"
				   "<Max price>    %d\n",
				   (param->first)->price, (param->last)->price);
		else
			printf("<Price>        %d\n",
				   (param->first)->price);
    }

	if((param->first)->rating != -1)
    {
		if((param->first)->rating != (param->last)->rating)
			printf("<Min rating>   %d"
				   "<Max rating>   %d",
				   (param->first)->rating, (param->last)->rating);
		else
			printf("<Rating>       %d",
				   (param->first)->rating);
    }
    pause();
}

int addRemCon(GH* head, int size, int mode1, int mode2)
{
	int pos;
	char *mes;

    mes = (mode2) ? "before": "after";

	if(!size)
	{
		pos = 1;
		printf("This will be the first game in the file cabinet");
		pause();
	}

	if(size == 1)
	{
		pos = 1;
		printf("There is only one game in the file cabinets.\n");
		if(!mode1)
			printf("The current one will be added %s it.", mes);
		else
			printf("It will be deleted.");
		pause();
	}

    if(size == 2 && mode1)
    {
        printf("There is only two game in the file cabinets.\n");
        pos = (!mode2) ? 1: 2;
        printf("The current one will be removed %s %d", mes, pos);
        pause();
    }

	if((size > 1 && !mode2) || size > 2)
        pos = getPos(head);

	return pos;
}

void succMes()
{
	system("cls");
	printf("Successfully!");
	pause();
}
