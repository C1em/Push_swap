void				empty_b(t_all_data *data)
{
	size_t	rot_count;
	t_llist	*tmp_a_rot;
	t_llist	*tmp_a_rev_rot;

	if (!data->piles->b)
		return ;
	rot_count = 0;
	tmp_a_rev_rot = data->piles->a;
	tmp_a_rot = data->piles->a;
	while (!is_destof(data->piles->b, tmp_a_rot->nb))
	{
		if (is_destof(data->piles->b, tmp_a_rev_rot->nb))
		{
			tmp_a_rot = data->piles->a;
			data->piles->a = tmp_a_rev_rot;
			return (push_all(data, tmp_a_rot, rot_count, 1));
		}
		tmp_a_rot = tmp_a_rot->next;
		tmp_a_rev_rot = tmp_a_rev_rot->prev;
		++rot_count;
	}
	tmp_a_rev_rot = (rot_count) ? data->piles->a : NULL;
	data->piles->a = tmp_a_rot;
	return (push_all(data, tmp_a_rev_rot, rot_count, 0));
}
