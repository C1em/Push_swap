
#include "push_swap.h"

int main(void)
{
	t_data_buff buff;

	buff.index = -1;
	fill_buffer(&buff, PB);
	fill_buffer(&buff, RRA);
	fill_buffer(&buff, PA);
	write_buff(&buff);
}
