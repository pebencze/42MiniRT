
#include "minirt.h"

int	parse_a(t_data *data, char *line)
{
	char	**info;
	int		i;

	if (line[ft_strlen(line)] == ' ')
		ft_exit(1, data, SPACE_ERR);
	info = ft_split(line, ' ');
	if (!info)
		ft_exit(1, data, ALLOC_ERR);
	if (ft_arr_len(info) != 3)
	{
		free_arr(info, NULL);
		ft_exit(1, data, LEN_ERR);
	}
	if (check_identifier(info[0], data, "element")
		|| check_ratio(info[1], data, 'A') || check_color(info[2], data, 'A'))
	{
		free_arr(info, NULL);
		ft_exit(1, data, NULL);
	}
	return (1);
}