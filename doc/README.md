# so_long

## Environment Setup

### First things first
At the project's time, I'm (was) using a WIN11 with WSL2. On WSL2 I've installed an Arch Linux using this [repo](https://github.com/yuk7/ArchWSL) and this tutorial [video](https://www.youtube.com/watch?v=sjrW74Hx5Po&t=2676s).

WIN11 has a Linux GUI support for WSL2, so I simply follow this [doc](https://docs.microsoft.com/en-us/windows/wsl/tutorials/gui-apps):

1. Download and install the GPU driver for WSL.

2. Run the following commands on PowerShell as admin to update and restart the WSL2:

```PowerShell
wsl --update
wsl --shutdown
```
> :warning: I've an issue with my keyboard map on X Apps and poorly solve it using [xorg-setxkbmap](https://archlinux.org/packages/extra/x86_64/xorg-setxkbmap/) tool to set my keyboard as follow: `setxkbmap -model abnt2 -layout br -variant abnt2`

3. For test pourpose, I've intalled [chromium](https://archlinux.org/packages/extra/x86_64/chromium/).
![chromium-test.png](chromium-test.png "Chromium Test")

### MiniLibX
> :book: [reference material](https://harm-smits.github.io/42docs/libs/minilibx) from [harmsmits](https://www.linkedin.com/in/harmsmits/)

"MiniLibX is an easy way to create graphical software, without any X-Window programming knowledge. It provides simple window creation, a drawing tool, image and basic events management." - from `man mlx`.

#### Installation
> :bulb: double check if you have [libx11](https://archlinux.org/packages/extra/x86_64/libx11/) and [libxext](https://archlinux.org/packages/extra/x86_64/libxext/) installed

1. From the project subject, download the `minilibx-linux.tgz` [file](https://projects.intra.42.fr/uploads/document/document/8443/minilibx-linux.tgz).

2. `tar -zxvf minilibx-linux.tgz`.

3. Compile the lib running: `cd minilibx-linux && make`.

4. There's a test folder to check if everything is working properly: `cd test && ./run_tests.sh` or `cd test && ./mlx-test`.

5. I like to always run my own ~~dummy~~ "tiny" test :arrow_right: (based on the reference material).
```c
#include "mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		i;
	int		j;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");

	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	i = -1;
	while (i++ < 100)
		my_mlx_pixel_put(&img, 50 + i, 50 + i, 0x00FFFFFF);
	j = -1;
	while (j++ < 100)
	{
		my_mlx_pixel_put(&img, 50 + j, 300 + j, 0x00FFFFFF);
	}

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);	

	return (0);
}
```

6. To run it: `cd minilibx-linux && gcc 1.c -Wall -Wextra -Werror -L . -lmlx -lXext -lX11 && ./a.out`
![mlx-own-test.png](mlx-own-test.png "Own Test")

#### Lib files' setup

1. To have all MiniLibX files in the "default" paths:
   1. `cd minilibx-linux && mv man/man3/mlx* /usr/share/man/man3`
   2. `cd minilibx-linux && mv mlx.h /usr/include`
   3. `cd minilibx-linux && mv libmlx.a	/usr/lib`

2. Them, you can run the compiler without the options -L -I for these files: `gcc 1.c -Wall -Wextra -Werror -lmlx -lXext -lX11 && ./a.out`

## Makefile

Nothing new here, it's a pretty straightforward Makefile, but... as I've never explain it to myself, here we go!

The fisrt "half" of the file contains eigther the **aliases** for some commands or **variables** that will be consumed by Makefile. In my case:

| Alias | Command   | Description                                                                           |
| ----- | --------- | ------------------------------------------------------------------------------------- |
| CC    | cc -> gcc | C Compiler                                                                            |
| AR    | ar rcsv   | It will create an archive (aka lib, in this case) with all objects compiled before.   |
|       |           | The option `r` insert the files into archive, replacing the files with the same name. |
|       |           | The option `c` implies to create the archive.                                         |
|       |           | The option `s` creates/updates an index for each object-file.                         |
|       |           | The option `v` add more verbosity in the output.                                      |
| RM    | rm -rf    | Remove command                                                                        |
---

| Variable       | Content               | Description                                   |
| -------------- | --------------------- | --------------------------------------------- |
| CC_FLAGS       | -Wall -Wextra -Werror | Mandatory C warning flags for 42 projects     |
| MLX_FLAGS      | -lmlx -lXext -lX11    | MiniLibX C lib linking flags                  |
| LIBFT_HEADER   | -I libft              | Path to Libft header file                     |
| LIBFT_LIB      | libft/libft.a         | Path to Libft archive (aka lib :smile:)       |
| LIBFT_LIB_LINK | -L libft -l:libft.a   | Explicity C lib linkig flag to Libft lib      |
| SRCS           | *.c                   | All project's C source files                  |
| OBJS           | \$(SRCS:.c=.o)        | Result \$() of %.c to %.o compilation process |
| NAME           | so_long               | Project name :video_game:                     |
---

The second part, contains de **recipes**. A recipe could have pre-req rules and will have it's commads. If no recipe is provide with the `make` command, the first explicit recipe present in the file will be executed.

| Recipe          | Content                                                               | Description                                                                                                   |
| --------------- | --------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- |
| .c.o:           | `$(CC) \$(CC_FLAGS) $(LIBFT_HEADER) -c $< -o $(<:.c=.o)`              | Explicitly describes how the .c=.o rule will behaves.                                                         |
|                 |                                                                       | In this case, will run the `CC` command, with the `CC_FLAGS` variable plus the `LIBFT_HEADER` variable.       |
|                 |                                                                       | On top of that, for each `.c` file, the recipe will add the `-c` option.                                      |
|                 |                                                                       | Meaning that the compiler mustn't link the object files generated to an executable output file.               |
|                 |                                                                       | Finnaly, the `-o` option will sets the name of it object file to the same of the source file `$< -o $...` .   |
|                 |                                                                       | Heres is an example of this recipe translated: `cc -Wall -Wextra -Werror -I libft -c so_long.c -o so_long.o`. |
| `$(NAME)`:      | pre-req: `$(LIBFT_LIB) $(OBJS)`                                       | This recipe have 2 rules as pre-req.                                                                          |
| `$(NAME)`:      | `$(CC) $(CC_FLAGS) $(OBJS) $(LIBFT_LIB_LINK) $(MLX_FLAGS) -o $(NAME)` | After the pre-reqs being fullfilled, it will run the `CC` command passing the gererated object files `OBJS`.  |
|                 |                                                                       | The following options will be passed to compiler: `CC_FLAGS`, `LIBFT_LIB_LINK`, `MLX_FLAGS`.                  |
|                 |                                                                       | The result of the recipe will be the `NAME` output file generated by the `-o` option.                         |
| `$(LIBFT_LIB)`: | make -C libft                                                         | This recipe simply call the `make` command passing the `-C` options that indicates the Makefile directory.    |
|                 |                                                                       | In this case, it will run the first recipe from libft Makefile.                                               |
| all:            | pre-req: `$(NAME)`                                                    | This recipe have 1 rule as pre-req. In pratical terms will run the recipe `NAME`.                             |
| clean:          | make clean -C libft; `$(RM) $(OBJS)`                                  | This recipe will run the `make clean` command inside libft directory.                                         |
|                 |                                                                       | And will run the `RM` command to all objects `OBJS`.                                                          |
| fclean:         | pre-req: clean                                                        | This recipe have 1 rule as pre-req.                                                                           |
| fclean:         | make fclean -C libft; `$(RM) $(NAME)`; `$(RM) *.out`; `$(RM) *.a`     | It will run a full clean, meaning that, remove all objects except the source files.                           |
| re:             | pre-req: fclean all                                                   | This recipe have 1 rule as pre-req.                                                                           |
| .PHONY:         | all clean fclean re                                                   | "These special targets are called phony and you can explicitly tell Make they're not associated with files".  |
|                 |                                                                       | https://stackoverflow.com/questions/2145590/what-is-the-purpose-of-phony-in-a-makefile                        |
---

## Project To-Do
- [ ] to-do 1
- [ ] to-do 2
- [ ] to-do 3

:page_with_curl: :end: