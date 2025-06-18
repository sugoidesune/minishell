#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_list_el
{
	struct s_list_el	*next;
	struct s_list_el	*previous;
	void				*content;
}						t_list_el;

typedef struct s_list
{
	t_list_el			*head;
}						t_list;


// list_lib_1
int						ft_listsize(t_list *list);
t_list_el				*ft_new_list_el(void *content);
t_list_el				*ft_listlast(t_list *lst);
t_list_el				*ft_listfirst(t_list *lst);
void					ft_listiter(t_list *lst, void (*f)(void *));

// list_lib_2
t_list					*ft_new_list(void);
t_list					*ft_list_from_el(t_list_el *list_element);
t_list					*ft_list_append(t_list *list,
							t_list_el *new_listelement);
t_list					*ft_list_prepend(t_list *list,
							t_list_el *new_listelement);
t_list					*ft_list_prepend_new(t_list *list, void *content);

// list_lib_3
t_list					*ft_list_append_new(t_list *list, void *content);
void					ft_list_delete_el(t_list_el *list_el,
							void (*del)(void *));
void					ft_listclear(t_list *lst, void (*del)(void *));
t_list					*ft_listmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
t_list_el				*ft_list_at_index(t_list *list, int index);

// list_lib_4
bool					ft_swap_el_content(t_list_el *first, t_list_el *second);
t_list_el				*ft_detach_head(t_list *list);
t_list_el				*ft_detach_tail(t_list *list);
t_list					*array_to_list(long *array, int count,
							void *(*create_content)(long));
void					free_list(t_list **lst);

#endif