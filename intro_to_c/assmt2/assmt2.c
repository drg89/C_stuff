/*Algorithms are fun!
COMP10002 ASSIGNMENT 2
STUDENT NUMBER: 1003433*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

/* stage numbers */
#define STAGE_NUM_ONE 1 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "========================= Stage %d =========================\n"
#define LENGTH_WORD 20
#define LENGTH_FORM 23
#define MAX_WORDS 100
#define MAX_FORMS 93
#define LENGTH_HASH 2

typedef struct words {
	char root[LENGTH_WORD + 1];
	int score;
	char forms[MAX_FORMS];
} word_t;

typedef struct node node_t;

struct node {
	char word[LENGTH_WORD];
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

typedef struct data data_t;

struct data {
	char form[LENGTH_FORM];
	char root[LENGTH_WORD];
	int score;
	data_t *next;
};
typedef struct hash hash_t;

struct hash {
	char key;
	data_t *right;
	hash_t *next;
};
/* array of lists = table*/

/*****************************function declarations*************************/
void stage_one(word_t *dict[100]);
void stage_two(word_t *dict[100], int *num_words);
void stage_three(list_t *list);
void stage_four(list_t *list, word_t *dict[100]);
void stage_five(list_t *list, word_t *dict[100]);
void print_stage_header(int stage_num);
word_t *read_word();
list_t *create(void);
list_t *append(list_t *list, char word[LENGTH_WORD]);
int getword(char W[]);
void print_list(list_t *list);
void free_list(list_t *list);
char list_to_arr(list_t *list, char array[MAX_WORDS][LENGTH_FORM]);
void print(char *arr[]);
int cmp_str_dict(const void *q, const void *p);
char hash(char word[]);
list_t *append_down(list_t *list, char hash);
char hash_to_arr(list_t *list, char array[MAX_WORDS][LENGTH_FORM]);
list_t *append_right(list_t *list, char form[LENGTH_FORM],
	 char root[LENGTH_WORD], int score);


/*=============================== MAIN =================================*/
int
main(int argc, char *argv[]) {			
	word_t dict[MAX_WORDS];
	list_t *list;
	list = create();
	int *num_words;
	num_words = malloc(sizeof(int));
	stage_one(dict);
	stage_two(dict, num_words);
	stage_three(list);
	stage_four(list, dict);
	stage_five(list, dict);
	
	/* freeing memory*/
	free(num_words);
	free_list(list);
	return 0;
}
/*====================================================*/
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/*========================= STAGES =================================*/
/*stage 1 code*/
void
stage_one(word_t *dict[100]) {
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	dict[0] = read_word();
	printf("First word: %s \nSentiment Score: %d \nForms: %s\n"
	, dict[0]->root, dict[0]->score, dict[0]->forms);
}
/*stage 2 code*/
void
stage_two(word_t *dict[100], int *num_words) {
	print_stage_header(STAGE_NUM_TWO);
	word_t *word;
	int i = 1, j, avg_c = 0, avg_s = 0;
	while ((word = read_word())){
		dict[i] = word;
		i++;
	}
	for(j = 0; j < i; j++){
		avg_c += strlen(dict[j]->root);
		avg_s += dict[j]->score;
	}
	*num_words = i;
	printf("Num words: %d\nAvg Char: %.2f\nAvg Score: %.2f\n", i, 
	(float)avg_c/i, (float)avg_s/i);
	free(word);
}
/*stage 3 code*/
void 
stage_three(list_t *list){
	print_stage_header(STAGE_NUM_THREE);
	char word[LENGTH_WORD];
	while (getword(word) != EOF){
		append(list, word);
	}
	print_list(list);
}
/******************************stage 4 code***********************************/
void stage_four(list_t *list, word_t *dict[100]){
	int i = 0, arr_size, dict_len, score = 0;
	char words[MAX_WORDS][LENGTH_FORM] = {}, *key;
	word_t **result;
	print_stage_header(STAGE_NUM_FOUR);
	list_to_arr(list, words);
	arr_size = (sizeof(words)/ sizeof(words[0]));	
	dict_len = 6;
	/*CMP FUNCTION WORKS!*/
	while(*words[i]){
		key = words[i];
		result = bsearch(key, dict, dict_len, sizeof(dict), cmp_str_dict);
		if (result){
			score += (*result) -> score;
			printf("%-25s %d\n", (*result)->root, (*result)->score);
		}
		else{
			printf("%-25s %d\n", key, 0);
		}
		i += 1;
	}
	printf("Overall Score: %d\n", score);
	free(result);
}
/*==============================STAGE 5=================================*/
/*TODO LIST:
MAKE HASH FUNCTION !!
MAKE HASH TABLE
STRUCTURE FOR NODES !!
INSERT FUNCTION 
SEARCH FUNCTION
make array of linked lists
*/
void stage_five(list_t *list, word_t *dict[100]){
	print_stage_header(STAGE_NUM_FIVE);
	char input[MAX_WORDS][LENGTH_FORM] = {}, *temp, ch;
	int i = 0, j = 0;
	list_t *hash_table;
	hash_table = create();
	/*make index of hash table, then insert values to the right of index*/
	while ((temp = dict[i]->root) != NULL){
		printf("hashing: %s", temp);
		append_down(hash_table, hash(temp));
		/* insert values to the right of each index */
		char form[LENGTH_FORM] = {};
		while((dict[i]->forms[j]) != EOF && dict[i]->forms[j] != '*'){
			form[j++] = dict[i]->forms[j++];
		}
		append_right(hash(form), form, dict[i] -> root, dict[i] -> score);
		i++;
	}
	
	/*search hash table for input, bsearch on index, linear search on word*/
	while(*input[i]){
		
		i++;
	}	
}




/*========================= My Functions =================================*/

/*reads a word*/
word_t 
*read_word() {
	word_t *word = (int*)malloc(sizeof(word_t));
	int c;
	/* Looking for "#" that starts every word*/
	if ((c = getchar()) != EOF && c != '%'){
		scanf("%s\n%d\n", word->root, &(word->score));
		getchar();
		fgets(word->forms, (MAX_FORMS), stdin);
		return word;
	} else return NULL;
}
/* create empty list from listops.c*/
list_t
*create(void) {
	list_t *list;
	list = (list_t *)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}
/*append node at end of list, copied from listops.c*/
list_t
*append(list_t *list, char word[LENGTH_WORD]) {
	node_t *newNode;
	newNode = (node_t *)malloc(sizeof(*newNode));
	assert(list!=NULL && newNode!=NULL);
	/* newNode->word = word; */
	strcpy(newNode -> word, word);
	newNode->next = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list -> foot = newNode;
	} else {
		list->foot -> next = newNode;
		list->foot = newNode;
	}
	return 0;
}

/* getword.c from Textbook */
int
getword(char W[]) {
	int c, len=0 , limit = LENGTH_WORD;
	/* first, skip over any non alphabetics */
	while ((c=getchar())!=EOF && !isalpha(c)) {
		/* do nothing */
	}
	if (c==EOF) {
		return EOF;
	}
	/* ok, first character of next word has been found */
	W[len++] = c;
	while (len<limit && (c=getchar())!=EOF && isalpha(c)) {
		/* another character to be stored */
		W[len++] = c;
	}
	/* now close off the string */
	W[len] = '\0';
	return 0;
}
/* tracerse list and print words in node*/
void print_list(list_t *list){
    node_t *temp;
    if(list -> head == NULL)
    {
        printf("cant traverse empty list\n");
        return;
    }
    temp = list -> head;
    while(temp != NULL)
    {
        printf("%s\n", temp->word);
        temp = temp->next;
    }
}
/*Put linked list into array; returns array of words*/
char list_to_arr(list_t *list, char array[MAX_WORDS][LENGTH_FORM]){
    node_t *temp;
	int i = 0;
    if(list -> head == NULL)
    {
        printf("cant traverse empty list\n");
        return;
    }
    temp = list -> head;
    while(temp != NULL)
    {
        strcpy(array[i++], temp->word);
        temp = temp->next;
    }
	return array;
}

/*print all elements of an array*/
void print(char *arr[]){
	while (*arr){
		printf("%s", *arr);
		arr += 1;
	}
}
/* free list */
void
free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}
/*wraps strncmp to compares a string to root word in dict*/
int cmp_str_dict(const void *q, const void *p){
	char *wordq = (char*)q;
	word_t **wordp = ((word_t **) p);
	/*printf("%s, %s", wordq, (*wordp)->root);*/
	return strncmp(wordq, (*wordp)->root, LENGTH_WORD);
}
/*hash function, returns first two letters of given word*/
char hash(char word[]){
	char hashKey[LENGTH_HASH] = {word[0], word[1]};
	return hashKey;
}

list_t
*append_down(list_t *list, char hash) {
	hash_t *newNode;
	newNode = (hash_t *)malloc(sizeof(*newNode));
	assert(list!=NULL && newNode!=NULL);
	/* newNode->word = word; */
	newNode -> key = hash;
	newNode->next = NULL;
	newNode->right = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list -> foot = newNode;
	} else {
		list->foot -> next = newNode;
		list->foot = newNode;
	}
	return 0;
}

/*Put list of hash index into array; returns array of words*/
char hash_to_arr(list_t *list, char array[MAX_WORDS][LENGTH_FORM]){
    hash_t *temp;
	int i = 0;
    if(list -> head == NULL)
    {
        printf("cant traverse empty list\n");
        return;
    }
    temp = list -> head;
    while(temp != NULL)
    {
        strcpy(array[i++], temp->key);
        temp = temp->next;
    }
	return array;
}
/*append nodes to the right of index*/
list_t 
*append_right(list_t *list, char form[LENGTH_FORM],
	 char root[LENGTH_WORD], int score){
		 data_t *newNode;
	newNode = (data_t *)malloc(sizeof(*newNode));
	assert(list!=NULL && newNode!=NULL);
	/* newNode->word = word; */
	strcpy(newNode -> form, form);
	strcpy(newNode -> root, root);
	newNode -> score = score;
	newNode->next = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list -> foot = newNode;
	} else {
		list->foot -> next = newNode;
		list->foot = newNode;
	}
	return 0;
}