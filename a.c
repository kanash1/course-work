void sort(NODE *top)
{
	NODE
	*item,		// game in list
	*tmp,		// temporary variable
	*p_item;		// previous game in list

	int
	i,			// loop parametr
	j,			// loop parametr
	size,		// size of head
	flag;		// result of condition

	size = getSize(top);

	// optimized bubble sort
	i = 0;
	do
	{
		flag = 0;
		item = top;
		p_item = NULL;
		for (j = 0; j < size - i - 1; j++)
		{
			if ((cmp(item, item->next) % 2) ^ sdir)
			{
				// swap extreme elements
				tmp = item->next;
				if ((p_item != tmp) && p_item)
					p_item->next = tmp;
				item->next = tmp->next;
				p_item = tmp;
				tmp->next = item;
				flag = 1;
			}
			else
			{
				// just moving on down the list
				p_item = item;
				item = item->next;
			}
		}
		i++;

	} while (flag);
}

int getSize(NODE *top)
{
	NODE* item;	// another game in list
	int size;	// list size
	if(top)
		game = top;
	else
		game = NULL;
	size = 0;
	while (game)
	{
		item = item->next;
		size++;
	}
	return size;
}

int cmp(NODE* item_1, NODE* item_2)
{
	int res;	// result

	res = strCmp(item_1->name, item_2->name);

	if (res == 0)
    {
		if (strLen(item_1->name) > strLen(item_2->name))
			res = 3;
		else
			if(strLen(item_1->name) < strLen(item_2->name))
				res = 4;
    }

	return res;
}

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

int strLen(char *str)
{
	int len;	//loop parameter and length of string

	len = 0;
	while (str[len] != '\n' && str[len] != '\0')
		len++;

	return len;
}
