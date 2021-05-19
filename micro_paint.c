#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		write (1, tab[i], ft_strlen(tab[i]));
		write(1, "\n", 1);
		i++;
	}
}

int ft_is_rec(float tile_x, float tile_y, float x, float y, float height, float width, float total_height, float total_width)
{
    float check = 1.00000000;
    if ((tile_x < x) || (x + width < tile_x) || (tile_y < y) || (y + height < tile_y))
        return (0);
    if (((tile_x - x) < check) || ((x + width) - tile_x < check) || ((tile_y - y) < check) || ((y + height) - tile_y < check))
        return (2);
    return (1);
}

void	ft_draw_rect(char id, float x, float y, float width, float height, char fill, char **tab, int total_height, int total_width)
{
	int	i;
	int	j;
	int	is_rec;

	i = 0;
	j = 0;
	while (i < total_height)
	{
		while (j < total_width)
		{
			is_rec = ft_is_rec(j, i, x, y, height, width, total_height, total_width);
			 if ((id == 'r' && is_rec == 2) || (id == 'R' && is_rec))
				tab[i][j] = fill;
			j++;
		}
		j = 0;
		i++;
	}
}

int	check_rect(float height, float width, char id, float x, float y, char fill)
{
	if (height <= 0.00000000 || width <= 0.00000000)
		return (1);
	if (id != 'r' && id != 'R')
		return (1);
	return (0);
}

int	ft_read_rectangle(char **tab, FILE *file, int total_height, int total_width)
{
	char	id = '\0';
	float	x = 0;
	float	y = 0;
	float	width = 0;
	float	height = 0;
	char	fill = '\0';
	int		ret;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &id, &x, &y, &width, &height, &fill)) == 6)
	{
		if (check_rect(height, width, id, x, y, fill))
			return (1);
		ft_draw_rect(id, x, y, width, height, fill, tab, total_height, total_width);
	}
	if (ret != -1)
		return (1);
	return (0);
}

void	ft_free_all(FILE *file, char **tab)
{
	int	i;

	fclose(file);
	if (tab != NULL)
		free(tab);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	char	**tab;
	int		i;
	int		j;
	int		height;
	int		width;
	char	fill_char;

	i = 0;
	j = 0;
	if (argc != 2)
	{
		write (1, "Error: argument\n", ft_strlen("Error: argument\n"));
		return (1);
	}
	if (!(file = fopen(argv[1], "r")))
	{
		write (1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
		return (1);
	}
	if (fscanf(file, "%d %d %c\n", &height, &width, &fill_char) != 3)
	{
		write (1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
		return (1);
	}
	if (height <= 0 || height > 300 || width <= 0 || width > 300)
	{
		write (1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
		return (1);
	}
	tab = malloc(sizeof(char *) * (height + 1));
	tab[height] = 0;
	while (i < height)
	{
		tab[i] = malloc(sizeof(char) * (width + 1));
		tab[i][width] = '\0';
		while (j < width)
		{
			tab[i][j] = fill_char;
			j++;
		}
		j = 0;
		i++;
	}
	if (ft_read_rectangle(tab, file, height, width) == 1)
	{
		write (1, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
		return (1);
	}
	ft_print_tab(tab);
	ft_free_all(file, tab);
	return (0);
}