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
