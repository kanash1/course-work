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
