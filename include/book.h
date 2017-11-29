#define MAX_BOOK_NAME 20
#define MAX_PUBLISHER 20
#define MAX_DATE 10
#define MAX_AUTHOR 20
#define MAX_ISBN 20
typedef struct _book_info
{
	char book_name[MAX_BOOK_NAME];
	char author[MAX_AUTHOR];
	char publisher[MAX_PUBLISHER];
	char pub_date[MAX_DATE];
	char ISBN[MAX_ISBN];
	int pages;
}book_info;
typedef struct _book
{
	book_info bi;
	struct _book *next;
}book;
void init_book();
void load_books();
void add_book();
void view_book();
void delete_book();
void save_books();
void clear_books();

void search_book_by_name();
void search_book_by_author();
void search_book_by_publisher();
void search_book_by_pubdate();
void search_book_by_isbn();

int findstr(char *source,char *str);
void save_books_to_file();
book *get_last_book();
book *get_previous_book(book *p);
void input_book(book_info *info);
void show_book(book_info *info); 

