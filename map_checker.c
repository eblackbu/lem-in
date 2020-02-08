#include "lem-in.h"

t_roomlist		*check_map(void)
{
	t_roomlist		*roomlist;
	char 			*first_link;

	roomlist = NULL;
	first_link = get_rooms(&roomlist);
	set_links(&roomlist, first_link);//TODO распарсить связи в матрицу по количеству комнат, записать в каждую комнату глубину, количество выходов и входов
	return (roomlist);
}

