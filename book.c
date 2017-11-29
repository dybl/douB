#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
        printf(">ÐÂÔöÍ¼Êé¡­..\n");
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
	   printf(">¼ÌÐøÌí¼ÓÍ¼ÊéÂð£¿(y or n):");
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
        printf("|         ÊéÃû       |         ×÷Õß        |\n");
        printf("+-----------------------------------------------------------------------------------+\n");
        while(p!=NULL)
        {
        	printf("|%20s|%20s|\n",p->bi.book_name,p->bi.author);
            printf("+-------------------------------------------------------------------------------+\n");
            count++;
            if(count==5)
            {
                count=0;
                printf(">ÏÔÊ¾ÏÂÒ»Ò³Âð£¿(y or n):");
                getchar();
                input=getchar();
                if(input != 'y' && input != 'Y')
                {
                	break;
                }
            }
        p=p->next;
        }
        printf(">ÔÙ´Îä¯ÀÀÍ¼ÊéÂð£¿(y or n):");
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
	printf(">²éÕÒÍ¼Êé¡­..\n");
	while(input == 'Y' || input == 'y')
	{
		count=0;
		p=first_book;
		memset(s,0,MAX_BOOK_NAME);
		printf(">ÇëÊäÈëÊéÃû£¨×î´ó³¤¶È%d£©:",MAX_BOOK_NAME);
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
			printf(">Ã»ÓÐÕÒµ½Í¼Êé%¡£¼ÌÐø²éÕÒÂð£¿(y or n):",s);
			getchar();
			input=getchar();
			continue;
		}
		printf(">¹²ÕÒµ½%d±¾Í¼Êé¡­\n",count);
		printf(">¼ÌÐø²éÕÒÂð£¿(y or n):");
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
	printf(">²éÕÒÍ¼Êé...\n");
	while (input == 'Y' || input == 'y')
	{
		count = 0;
		p = first_book; 
		memset(s, 0, MAX_AUTHOR);
		printf(">ÇëÊäÈë×÷Õß (×î´ó³¤¶ÈÎª %d):", MAX_AUTHOR);
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
			printf(">Ã»ÓÐÕÒµ½×÷ÕßÎª %s µÄÍ¼Êé¡£¼ÌÐø²éÕÒÂð£¿(y or n):", s);
			getchar();
			input = getchar();
			continue;
		}
		printf(">¹²ÕÒµ½ %d ±¾Í¼Êé...\n", count);
		printf(">¼ÌÐø²éÕÒÂð£¿(y or n):");
		getchar();
		input = getchar();
	}
}





void search_book_by_publisher()
{
	book*p = NULL;
	char s[MAX_PUBLISHER] = {0}; /*³ö°æÉçÐÅÏ¢*/
	char input = 'Y';
	int count = 0;
	int i = 0;


	printf(">²éÕÒÍ¼Êé...\n");


	while (input == 'Y' || input == 'y')
	{
		count = 0;
		p = first_book;
		memset(s,0,MAX_AUTHOR);
		printf(">ÇëÊäÈë³ö°æÉç £¨×î´ó³¤¶ÈÎª %d):", MAX_PUBLISHER);
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
			printf(">Ã»ÓÐÕÒµ½³ö°æÉçÎª %s µÄÍ¼Êé¡£¼ÌÐø²éÕÒÂð£¿(y or n):", s);
			getchar();
			input = getchar();
			continue;


		}
		printf(">¹²ÕÒµ½ %d ±¾Í¼Êé...\n", count);


		printf(">¼ÌÐø²éÕÒÂð£¿(y or n):");
		getchar();
		input = getchar();
	}
}


void search_book_by_pubdate()
{
	book *p = NULL;
	char s[MAX_DATE] = {0};/*³ö°æÈÕÆÚ*/
    char input = 'Y';
	int count = 0;
	int i =0;


	printf(">²éÕÒÍ¼Êé...\n");


	while (input == 'Y' || input == 'y')
	{
		count = 0;
		p = first_book;
		memset(s, 0, MAX_DATE);
		printf(">ÇëÊäÈë³ö°æÈÕÆÚ (×î´ó³¤¶ÈÎª %d):", MAX_DATE);
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
			printf(">Ã»ÓÐÕÒµ½³ö°æÉçÈÕÆÚÎª %s µÄÍ¼Êé.¼ÌÐø²éÕÒÂð£¿(y or n):", s);
			getchar();
		    input = getchar();
			continue;
		}


		printf(">¹²ÕÒµ½ %d ±¾Í¼Êé...\n):");


		printf(">¼ÌÐø²éÕÒÂð£¿(y or n):");
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
		printf(">²éÕÒÍ¼Êé...\n");
		printf(">ÇëÊäÈëISBN (×î´ó³¤¶ÈÎª %d):", MAX_ISBN);
		scanf("%s", isbn);
		p = first_book; /* pÖ¸ÏòµÚÒ»¸ö½Úµã */
		result = NULL;
		/*ÔÚÍ¼ÊéÁ´±íÖÐ²éÕÒÊäÈëµÄISBNÊÇ·ñ´æÔÚ*/
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
			printf(">²éÕÒÍ¼Êé...\n");
			show_book(&(result->bi)); /*µ÷ÓÃshow_bookÏÔÊ¾²éµ½µÄÍ¼ÊéÐÅÏ¢*/
		}
		else
		{
			printf(">¼ÌÐø²éÕÒÂð£¿(y or n)");
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
		printf(">É¾³ýÍ¼Êé...\n");
		printf(">ÇëÊäÈëISBN (×î´ó³¤¶ÈÎª %d):",MAX_ISBN);
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
			printf(">È·ÈÏÉ¾³ýÂð?(y or n)");
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
			printf(">Ã»ÓÐÕÒµ½ISBNÎª %sµÄÍ¼Êé.\n",isbn);
		}
		printf(">¼ÌÐøÉ¾³ýÆäËûÍ¼ÊéÂð?(y or n)");
		getchar();
		input = getchar();
	}
}

void save_books()
{
	save_books_to_file();
	printf(">±£´æ³É¹¦£¡ ");
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
			printf("²»ÄÜ´´½¨ÎÄ¼þ£¬°´ÈÎÒâ¼üÍË³ö...");
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
	printf(">ÇëÊäÈëÊéÃû(×î´ó³¤¶ÈÎª %d):",MAX_BOOK_NAME);
    scanf("%s",info->book_name);
	printf(">ÇëÊäÈë×÷Õß(×î´ó³¤¶ÈÎª %d):",MAX_AUTHOR);
	scanf("%s",info->author);
	printf(">ÇëÊäÈë³ö°æÉç(×î´ó³¤¶ÈÎª %d):",MAX_PUBLISHER);
	scanf("%s",info->publisher);
	printf(">ÇëÊäÈë³ö°æÈÕÆÚ(×î´ó³¤¶ÈÎª %d):",MAX_DATE);
	scanf("%s",info->pub_date);
	printf(">ÇëÊäÈëISBN(×î´ó³¤¶ÈÎª %d):",MAX_ISBN);
	scanf("%s",info->ISBN);
	printf(">ÇëÊäÈëÒ³Êý:");
	scanf("%d",&(info->pages));
}

void show_book(book_info *info)
{
	printf("------------------------------\n");
    printf("ÊéÃû:%s\n",info->book_name);
	printf("×÷Õß:%s\n",info->author);
	printf("³ö°æÉç:%s\n",info->publisher);
	printf("³ö°æÈÕÆÚ:%s\n",info->pub_date);
	printf("..............................\n");
	printf("ISBN:%s\n",info->ISBN);
	printf("Ò³Êý:%s\n",info->pages);
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




