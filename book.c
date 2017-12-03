#include "book.h"
#define BOOK_FILE "books.dat"
book *first_book=NULL;
void add_book()
{
	char try_again = 'Y';
    book *p = NULL;
    book *new_book = NULL;

	while(try_again == 'Y' || try_again == 'y')
	{
		new_book = (book*)malloc(sizeof(book));
        memset(new_book, 0, sizeof(book));
        new_book->next=NULL;
        printf(">新增图书…..\n");
        input_book(&(new_book->bi));
        p=get_last_book();
	   if(p==NULL)
	   {
	   	first_book=new_book;
	   }
	   else
	   {
	   	p->next=new_book;
	   }
	   printf(">继续添加图书吗？(y or n):");
	   getchar();
	   try_again=getchar();
	}
}

void view_book()
{
	book *p=NULL;
	char input = 'Y';
	int count=0;
	while(input == 'y' || input == 'Y')
	{
		count=0;
		p=first_book;
        printf("+-----------------------------------------------------------------------------------+\n");
        printf("|         书名       |         作者        |\n");
        printf("+-----------------------------------------------------------------------------------+\n");
        while(p!=NULL)
        {
        	printf("|%20s|%20s|\n",p->bi.book_name,p->bi.author);
            printf("+-------------------------------------------------------------------------------+\n");
            count++;
            if(count==5)
            {
                count=0;
                printf(">显示下一页吗？(y or n):");
                getchar();
                input=getchar();
                if(input != 'y' && input != 'Y')
                {
                	break;
                }
            }
        p=p->next;
        }
        printf(">再次浏览图书吗？(y or n):");
        getchar();
        input = getchar();
    }
}




void search_book_by_name()
{
	book *p=NULL;
	char s[MAX_BOOK_NAME]={0};
	char input = 'Y';
	int count=0;
	int i=0;
	printf(">查找图书…..\n");
	while(input == 'Y' || input == 'y')
	{
		count=0;
		p=first_book;
		memset(s,0,MAX_BOOK_NAME);
		printf(">请输入书名（最大长度%d）:",MAX_BOOK_NAME);
		scanf("%s",s);
		while(p != NULL)
		{
			if(findstr(p->bi.book_name,s)!=-1)
			{
				show_book(&(p->bi));
				count++;
			}
			p=p->next;
		}
		if(count==0)
		{
			printf(">没有找到图书%。继续查找吗？(y or n):",s);
			getchar();
			input=getchar();
			continue;
		}
		printf(">共找到%d本图书…\n",count);
		printf(">继续查找吗？(y or n):");
		getchar();
		input=getchar();
	}
}


void search_book_by_author()
{
	book *p = NULL;
	char s[MAX_AUTHOR] = {0}; 
	char input = 'Y';
	int count = 0;
	int i = 0;
	printf(">查找图书...\n");
	while (input == 'Y' || input == 'y')
	{
		count = 0;
		p = first_book; 
		memset(s, 0, MAX_AUTHOR);
		printf(">请输入作者 (最大长度为 %d):", MAX_AUTHOR);
		scanf("%s", s);
		while(p != NULL)
		{
			if (findstr(p->bi.author, s) != -1)
			{
				show_book(&(p->bi));
				count++;
			}
			p = p->next;
		}
		if (count == 0)
		{
			printf(">没有找到作者为 %s 的图书。继续查找吗？(y or n):", s);
			getchar();
			input = getchar();
			continue;
		}
		printf(">共找到 %d 本图书...\n", count);
		printf(">继续查找吗？(y or n):");
		getchar();
		input = getchar();
	}
}





void search_book_by_publisher()
{
	book*p = NULL;
	char s[MAX_PUBLISHER] = {0}; /*出版社信息*/
	char input = 'Y';
	int count = 0;
	int i = 0;


	printf(">查找图书...\n");


	while (input == 'Y' || input == 'y')
	{
		count = 0;
		p = first_book;
		memset(s,0,MAX_AUTHOR);
		printf(">请输入出版社 （最大长度为 %d):", MAX_PUBLISHER);
		scanf("%s", s);
		while(p != NULL)
		{
			if (findstr(p->bi.publisher, s) != -1)
			{
				show_book(&(p->bi));
				count++;
			}p = p->next;
		}


		if (count == 0)
		{
			printf(">没有找到出版社为 %s 的图书。继续查找吗？(y or n):", s);
			getchar();
			input = getchar();
			continue;


		}
		printf(">共找到 %d 本图书...\n", count);


		printf(">继续查找吗？(y or n):");
		getchar();
		input = getchar();
	}
}


void search_book_by_pubdate()
{
	book *p = NULL;
	char s[MAX_DATE] = {0};/*出版日期*/
    char input = 'Y';
	int count = 0;
	int i =0;


	printf(">查找图书...\n");


	while (input == 'Y' || input == 'y')
	{
		count = 0;
		p = first_book;
		memset(s, 0, MAX_DATE);
		printf(">请输入出版日期 (最大长度为 %d):", MAX_DATE);
		scanf("%s", s);
		while(p != NULL)
		{
			if (findstr(p->bi.pub_date, s) != -1)
			{
				show_book(&(p->bi));
				count++;
			}
			p = p->next;
		}


		if (count == 0)
		{
			printf(">没有找到出版社日期为 %s 的图书.继续查找吗？(y or n):", s);
			getchar();
		    input = getchar();
			continue;
		}


		printf(">共找到 %d 本图书...\n):");


		printf(">继续查找吗？(y or n):");
		getchar();
		input = getchar();
	}
}


void search_book_by_isbn()
{
	char input = 'Y';
	char isbn[MAX_ISBN] = {0};
	book *p = NULL;
	book *result = NULL;


	while(input == 'Y' || input == 'y')
	{
		printf(">查找图书...\n");
		printf(">请输入ISBN (最大长度为 %d):", MAX_ISBN);
		scanf("%s", isbn);
		p = first_book; /* p指向第一个节点 */
		result = NULL;
		/*在图书链表中查找输入的ISBN是否存在*/
		while (p != NULL)
		{
			if (strcmp(p->bi.ISBN, isbn)== 0 )
			{
				result = p;
				break;
			}
			p = p->next;
		}
		if (result != NULL)
		{
			printf(">查找图书...\n");
			show_book(&(result->bi)); /*调用show_book显示查到的图书信息*/
		}
		else
		{
			printf(">继续查找吗？(y or n)");
			getchar();
			input = getchar();
		}
	}
}


void delete_book()
{
	char input = 'Y';
	char isbn[MAX_ISBN]= {0};
	book *p = NULL;
	book *result = NULL;
	while(input == 'Y' || input == 'y')
	{
		printf(">删除图书...\n");
		printf(">请输入ISBN (最大长度为 %d):",MAX_ISBN);
		scanf("%s",isbn);
		p = first_book;
		result = NULL;
		while (p != NULL)
		{
			if (strcmp(p->bi.ISBN,isbn) == 0)
			{
				result = p;
				break;
			}
			p = p->next;
		}
		if(result != NULL)
		{
			show_book(&(result->bi));
			printf(">确认删除吗?(y or n)");
			getchar();
			input = getchar();
			if(input == 'y' || input == 'Y')
			{
				get_previous_book(p)->next = p->next;
				free(p);
			}
		}
		else
		{
			printf(">没有找到ISBN为 %s的图书.\n",isbn);
		}
		printf(">继续删除其他图书吗?(y or n)");
		getchar();
		input = getchar();
	}
}

void save_books()
{
	save_books_to_file();
	printf(">保存成功！ ");
	getchar();
	getchar();
}

void save_books_to_file()
{
	FILE *fp = fopen(BOOK_FILE,"wb");
	book *p = first_book;
	while(p != NULL)
	{
		fwrite(&(p->bi),sizeof(book_info),1,fp);
		fseek(fp,0,SEEK_END);
		p = p->next;
	}
	fclose(fp);
}

void init_book()
{
	FILE *fp = NULL;
	fp = fopen(BOOK_FILE,"r");
	if (fp == NULL)
	{
		fp = fopen(BOOK_FILE,"w");
		if(fp == NULL)
		{
			printf("不能创建文件，按任意键退出...");
			 getchar();
			 exit(0);
		}
	}
	fclose(fp);
}

void load_books()
{
	book *b = NULL;
	book *last = NULL;
	FILE *fp = NULL;
	int count = 0;
	b = (book*)malloc(sizeof(book));
	b->next = NULL;
	fp = fopen(BOOK_FILE, "rb");
	while(fread(&(b->bi),sizeof(book_info),1,fp) == 1)
	{
		if (first_book == NULL)
		{
			first_book = b;
		}
		else
		{
			last = get_last_book();
			last->next = b;
		}
		count++;
		fseek(fp,count *sizeof(book_info),SEEK_SET);
		b = (book*)malloc(sizeof(book));
		memset(b,0,sizeof(book));
		b->next = NULL;
	}
	free(b);
	b = NULL;
	fclose(fp);
}


void clear_books()
{
	book *p=NULL;
	while(first_book!=NULL)
	{
		if(first_book->next!=NULL)
		{
			p=first_book;
			first_book=first_book->next;
			free(p);
			p=NULL;
		}
		else
		{
			free(first_book);
			first_book=NULL;
		}
	}
}
int findstr(char *source,char *str)
{
	int pos=-1;
	int i=0;
	int j=0;
	int m=strlen(source);
	int n=strlen(str);
	if(m==0||n==0||m<n)
	{
		return pos;
	}
	if(m==n)
	{
		if(strcmp(source,str)==0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	for(i=0;i<(m-n);i++)
	{
		pos=i;
		for(j=0;j<n;j++)
		{
			if(source[i+j]!=str[j])
			{
				pos=-1;
				break;
			}
		}
		if(pos!=-1)
		{
			break;
		}
	}
	return pos;
}

void input_book(book_info *info)
{
	printf(">请输入书名(最大长度为 %d):",MAX_BOOK_NAME);
    scanf("%s",info->book_name);
	printf(">请输入作者(最大长度为 %d):",MAX_AUTHOR);
	scanf("%s",info->author);
	printf(">请输入出版社(最大长度为 %d):",MAX_PUBLISHER);
	scanf("%s",info->publisher);
	printf(">请输入出版日期(最大长度为 %d):",MAX_DATE);
	scanf("%s",info->pub_date);
	printf(">请输入ISBN(最大长度为 %d):",MAX_ISBN);
	scanf("%s",info->ISBN);
	printf(">请输入页数:");
	scanf("%d",&(info->pages));
}

void show_book(book_info *info)
{
	printf("------------------------------\n");
    printf("书名:%s\n",info->book_name);
	printf("作者:%s\n",info->author);
	printf("出版社:%s\n",info->publisher);
	printf("出版日期:%s\n",info->pub_date);
	printf("..............................\n");
	printf("ISBN:%s\n",info->ISBN);
	printf("页数:%s\n",info->pages);
	printf("\n");
}

book *get_last_book()
{
	book *p=first_book;
	if(p==NULL)
	{
		return p;
	}
	while((p!=NULL)&&(p->next!=NULL))
	{
		p=p->next;
	}
	return p;
}

book *get_previous_book(book *p)
{
	book *previous = first_book;
	while(previous != NULL)
	{
		if(previous->next == p)
		{
			break;
		}
		previous = previous->next;
	}
	return previous;
}



