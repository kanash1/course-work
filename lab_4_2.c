#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*===========================================================================*/
/*                                STRUCTURES                                 */
/*===========================================================================*/

typedef struct GAME 			// [queue's item]
{
	char* name;					// game's name
	char* dev;					// game's developer
	int date;					// game's release date
	int price;					// game's price
	int rating;					// game's rating
	struct GAME *next;			// next game in the queue
	struct GAME *prev;			// prev game in the queue
} GAME;

/*===========================================================================*/
/*                            FUNCTION PROTOTYPES                            */
/*===========================================================================*/

/*-----------------------functions for work with queue-----------------------*/

void put(GAME**, GAME**, GAME*);// add item to the top of the queue
void get(GAME**);				// remove item from the end of the queue
void view(GAME*);				// print item from the top of the queue
int getSize(GAME*);				// getting queue size

/*---------------------functions for forming queue's item--------------------*/

GAME* makeItem(GAME**);			// item of the queue creation
char* gameName(GAME**, GAME**);	// entering game name
char* gameDev(GAME**, GAME**);	// entering game developer
int gameDate();					// entering game release date
int gamePrice();				// entering game price
int gameRating();				// entering game rating

/*----------------------functions for work with strings----------------------*/

int strLen(char*);				// getting string length
int fromStrToNum(char*,int);	// conversation from string to num

/*------------------------------other functions------------------------------*/

int menu(GAME*);				// print menu items and get user choice
void queuePrint(GAME*);			// print all items from the queue
void delQueue(GAME**);			// delete all items from the queue
void help();					// print help
void errorMes();				// print error massage
void pause();					// pause program

/*===========================================================================*/
/*                               MAIN FUNCTION                               */
/*===========================================================================*/

int main()
{
	GAME
	*item,		// item in the queue
	*top,		// top of the queue
	*end;		// end of the queue

	char
	choice;		// user choice

	top = NULL;	// assignment of initial values
	end = NULL; // assignment of initial values

	do
	{
		choice = menu(top);	// print menu
		system("cls");
		switch(choice)
		{
			case '1':	// add item to the end of the queue
					item = makeItem(&top);
					put(&top, &end, item);
					break;
			case '2':	// remove item from the top of the queue
					if(top)
					{
						printf("Information about deleted game:\n\n");
						view(top);
						pause();
						get(&top);
						system("cls");
						printf("Successfully! Game was deleted.");
					}
					else
						printf("There aren't items in queue!");
					pause();
					break;
			case '3':	// print item from the top of the queue
					if(top)
					{
						printf("Information about game in top:\n\n");
						view(top);
					}
					else
						printf("There aren't items in queue!");
					pause();
					break;
			case '4':	// print all items from the queue
					if(top)
						queuePrint(top);
					else
						printf("There aren't items in queue!");
					pause();
					break;
			case '5':	// print queue size
					printf("Number of games in queue: %d", getSize(top));
					pause();
					break;
			case '6':	// print help
					help();
					pause();
					break;
			case '0':	// exit program
					delQueue(&top);
					break;
			case '\n':	// nothing input
					break;
			default:	// incorrect input
					printf("Incorrect command!");
					pause();
		}
	}
	while(choice != '0');

	return 0;
}

/*===========================================================================*/
/*                                 FUNCTIONS                                 */
/*===========================================================================*/

/*-----------------------functions for work with queue-----------------------*/

/*
 * [put add item to the end of the queue]
 * @param top  [pointer on top of the queue]
 * @param end  [pointer on end of the queue]
 * @param item [new item in the queue]
 */
void put(GAME **top, GAME **end, GAME *item)
{
	if(*end)
	{
		item->prev = *end;
		(*end)->next = item;
		*end = item;
	}
	else
	{
		*top = item;
		*end = item;
	}
}

/*
 * [get remove item from the top of the queue]
 * @param top [pointer on top of the queue]
 */
void get(GAME **top)
{
	GAME* tmp;	// temporary value

	tmp = (*top)->next;
	if((*top)->name)
		free((*top)->name);
	if((*top)->dev)
		free((*top)->dev);
	free(*top);
	*top = tmp;
}

/*
 * [view print item from the top of the queue]
 * @param top [top of the queue]
 */
void view(GAME *top)
{
	printf("<Name>         %s\n<Developer>    %s\n"
		"<Date>         %d\n<Price>        %d\n"
		"<Rating>       %d", top->name, top->dev,
		top->date, top->price, top->rating);
}

/*
 * [getSize getting string length]
 * @param  item [item in the queue]
 * @return      [queue size]
 */
int getSize(GAME *item)
{
	int size;	// queue size

	size = 0;
	while (item)
	{
		item = item->next;
		size++;
	}

	return size;
}

/*---------------------functions for forming queue's item--------------------*/

/*
 * [makeItem item of the queue creation]
 * @param  top [pointer on top of the queue]
 * @return     [description]
 */
GAME* makeItem(GAME **top)
{
	GAME* item;	// new item

	item = (GAME*)malloc(sizeof(GAME));
	if(item)
	{
		item->name = gameName(top, &item);
		item->dev = gameDev(top, &item);
		item->date = gameDate();
		item->price = gamePrice();
		item->rating = gameRating();
		item->next = NULL;
		item->prev = NULL;
	}
	else
	{
		delQueue(top);
		errorMes();
		exit(-1);
	}

	return item;
}

/*
 * [gameName entering game name]
 * @param  top [pointer on top of the queue]
 * @return     [game name]
 */
char* gameName(GAME **top, GAME **item)
{
	char *name;		// game name
	int len;		// string length

	// game's name adding
	name = (char*)malloc(22 * sizeof(char));

	if (name)
	{
		system("cls");
		do
		{
			printf("Enter the name of the game\n"
				"(maximum length 20 characters)\n\n"
				"Input: ");
			fgets(name, 22, stdin);
			fflush(stdin);
			len = strLen(name);	// real name's length

			system("cls");
			if(len == 21)
				puts("You have entered more"
					"than 20 characters!"
					"Try again!\n");
		} while (!len || (len == 21));

		name[len] = '\0';

		// freeing up extra memory
		name = (char*)realloc(name, (len + 1) * sizeof(char));
		if (!name)
		{
			delQueue(top);
			get(item);
			errorMes();
			exit(-1);
		}
	}
	else
	{
		delQueue(top);
		get(item);
		errorMes();
		exit(-1);
	}

	return name;
}

/*
 * [gameName entering game developer]
 * @param  top [pointer on top of the queue]
 * @return     [game developer]
 */
char* gameDev(GAME **top, GAME **item)
{
	char *dev;	// game developer
	int len;	// string length

	dev = (char*)malloc(21 * sizeof(char));

	if (dev)
	{
		system("cls");
		do
		{
			printf("Enter developer name\n"
				"(maximum length 20 characters)\n\n"
				"Input: ");
			fgets(dev, 21, stdin);
			fflush(stdin);
			len = strLen(dev);	//real name's length

			system("cls");
			if(len == 21)
				puts("You have entered more"
					"than 20 characters!"
					"Try again!\n");
		} while (!len || (len == 21));

		dev[len] = '\0';

		// freeing up extra memory
		dev = (char*)realloc(dev, (len + 1) * sizeof(char));
		if (!dev)
		{
			delQueue(top);
			get(item);
			errorMes();
			exit(-1);
		}
	}
	else
	{
		delQueue(top);
		get(item);
		errorMes();
		exit(-1);
	}

	return dev;
}

/*
 * [gameDate game date formation]
 * @return [game release date]
 */
int gameDate()
{
	int
	date,			// release date
	len;			// real length of text

	char str[6];	// temporary string

	system("cls");
	do
	{
		printf("Enter release year\n"
			"(minimum value - 1940, "
			"maximum value - 2020)\n\n"
			"Input: ");

		fgets(str, 6, stdin);
		fflush(stdin);
		len = strLen(str);	// real length

		//conrol of year
		if (len)
		{
			date = fromStrToNum(str, len+ 1);
			system("cls");
			if (date == -1)
				puts("You entered an invalid year. "
					"Try again!\n");
			else
				if (date < 1940)
					puts("It is impossible!\n"
						"The first computer game was"
						" released only in 1940!\n"
						"You entered an invalid year. "
						"Try again!\n");
				else
					if (date > 2020)
						puts("You cannot enter a year, "
							"that has not yet arrived!\n"
							"Try again!\n");
		}
		else
		{
			date = -1;
			system("cls");
		}
	} while (date < 1940 || date > 2020);

	return date;
}

/*
 * [gamePrice game price formation]
 * @return [game price]
 */
int gamePrice()
{
	int
	price,			// game price
	len;			// real length of text

	char str[7];	// temporary string

	do
	{
		printf("Enter the price in rubles\n"
			"(minimum value - 0, "
			"maximum value - 20000):\n\n"
			"Input: ");

		fgets(str, 7, stdin);
		fflush(stdin);
		len = strLen(str);	// real length

		// control of price
		if (len)
		{
			price = fromStrToNum(str, len + 1);
			system("cls");
			if (price == -1)
				puts("You entered an incorrect price. "
					"Try again!\n");
			else
				if (price > 20000)
					puts("The price is too high!. "
						"The maximum price of 20,000 rubles.\n"
						"Try again!\n");
		}
		else
		{
			price = -1;
			system("cls");
		}
	} while (price < 0 || price > 20000);

	return price;
}

/*
 * [gameRating game rating formation]
 * @return [game rating]
 */
int gameRating()
{
	int
	rating,	// game rating
	len;	// real length of text

	char
	str[4];	// temporary string

	do
	{
		printf("Enter user rating\n"
			"(minimum value - 1, "
			"maximum value - 10):\n\n"
			"Input: ");

		fgets(str, 4, stdin);
		fflush(stdin);
		len = strLen(str);	// real length

		// control of rating
		if (len)
		{
			rating = fromStrToNum(str, len + 1);
			system("cls");
			if (rating < 1)
				puts("You have entered an incorrect rating. "
					"Try again!\n");
			else
				if (rating > 10)
					puts("Rating is too high!. "
						"Maximum rating 10.\n"
						"Try again!\n");
		}
		else
		{
			rating = 0;
			system("cls");
		}
	} while (rating < 1 || rating > 10);

	return rating;
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

/*------------------------------other functions------------------------------*/

/*
 * [menu print menu items and get user choice]
 * @param  top [top of the queue]
 * @return     [description]
 */
int menu(GAME *top)
{
	char
	choice[3],	// user choice
	*mes;		// message

	if (!top)
		mes = " (unavailable)";
	else
		mes = "";

	system("cls");

	// print menu
	printf("\n\n\t\t\t\t   MENU\n\n"
		"\t\t     1 - Add game to end of the queue\n\n"
		"\t\t     2 - Remove game from top of the queue%s\n\n"
		"\t\t     3 - Output game from top of the queue%s\n\n"
		"\t\t     4 - Output all games from the queue%s\n\n"
		"\t\t     5 - Output size of the queue\n\n"
		"\t\t     6 - Help\n\n\t\t     0 - Exit\n\n"
		"\t\t     Input: ", mes, mes, mes);

	fgets(choice, 3, stdin);
	fflush(stdin);

	//input validation
	if(choice[0] != '\n')
	    if(choice[1] != '\n')
	        choice[0] = '\0';

    return choice[0];
}

/*
 * [queuePrint print all items from the queue]
 * @param item [item in the queue]
 */
void queuePrint(GAME *item)
{
	int
	size,	// size of queue
	i;		// loop parametr

	size = getSize(item);

	//some information for user
	if(size > 8)
		puts("\t\t     To output the next group of\n"
			"\t\t  games from the steck, press any key\n");

	puts("  +---+----------------------+------------"
		"----------+------+-------+--------+\n"
		"  | N |                 Name |            Developer "
		"| Date | Price | Rating |\n"
		"  +---+----------------------+------------"
		"----------+------+-------+--------+");

	for (i = 0; i < size; i++)
	{
		printf("  |%2.d | %20s | %20s | %d | %5.1d |   %2.d   |\n"
			"  +---+----------------------+------------"
			"----------+------+-------+--------+\n",
			i + 1, item->name,
			item->dev, item->date,
			item->price, item->rating);

		if ((i + 1) % 8 == 0 && size > 8)
			getch();

		item = item->next;
	}
}

/*
 * [delQueue delete all items from the queue]
 * @param top [top of the queue]
 */
void delQueue(GAME **top)
{
	while(*top)
		get(top);
}

/*
 * [errorMes print error massage]
 */
void errorMes()
{
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

/*
 * [help print help]
 */
void help()
{
	puts("\t\t\t\t HELP\n\n"
		 "Developer: kanashi\n"
		 "Release year: 2020\n"
		 "Assigning program options:\n\n"
		 "    -Add game to end of the queue:\n"
		 "     Option number: 1\n"
		 "     Appointment: Add game to end of the queue\n\n"
		 "    -Remove game from top of the queue:\n"
		 "     Option number: 2\n"
		 "     Appointment: Remove game from top of the queue\n\n"
		 "    -Output game from top of the queue:\n"
		 "     Option number: 3\n"
		 "     Appointment: Output game from top of the queue\n\n"
		 "    -Output all games from the queue:\n"
		 "     Option number: 4\n"
		 "     Appointment: Output all games from the queue\n\n"
		 "    -Output size of the queue:\n"
		 "     Option number: 5\n"
		 "     Appointment: Output size of the queue\n\n"
		 "    -Help:\n"
		 "     Option number: 6\n"
		 "     Appointment: Help output\n\n"
		 "    -Exit:\n"
		 "     Option number: 0\n"
		 "     Appointment: Exit from the program");	
}