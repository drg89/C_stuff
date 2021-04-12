/* Tweet cleanser:
 * Removes non-alphanumeric characters from tweets
 *
 * Skeleton code written by Yi Han and Jianzhong Qi, April 2019
 * Rest of code written by Xin Hui Chen; ID: 1003433
 * 
 * 
 * algorithms are fun
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*only for Q5*/
#include <string.h>

/* stage numbers */
#define STAGE_NUM_ONE 1 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5
#define STAGE_HEADER "Stage %d\n==========\n"	/* stage header format string */

#define MAX_TWEET_LENGTH 280					/* maximum length of a tweet */
#define MAX_NUM_TWEETS 100						/* maximum number of tweets */

typedef char tweet_t[MAX_TWEET_LENGTH+1];		/* a tweet */

/****************************************************************/

/* function prototypes */
void read_one_tweet(tweet_t one_tweet, int max_len);
void print_stage_header(int stage_num);
void tweet_tolower(tweet_t one_tweet);

void stage_one(tweet_t one_tweet);
void stage_two(tweet_t tweets[], int *num_tweets);
void stage_three(tweet_t tweets[], int num_tweets);
void stage_four(tweet_t tweets[], int num_tweets);
void stage_five(tweet_t tweets[], int num_tweets);

/* add your own function prototypes here */
char *str_append(char *dest, char *src);
int len(char s[]);
void read_tweets(tweet_t tweets[], int *lines);
void clean_tweet(char tweet[MAX_TWEET_LENGTH+1]);
int contained(char *source, char *target);
char replace(char *dest, char *src);
int compare(const void* str1, const void* str2);
/****************************************************************/

/* main function controls all the action, do NOT modify this function */
int
main(int argc, char *argv[]) {
	/* to hold all input tweets */
	tweet_t tweets[MAX_NUM_TWEETS];	
	/* to hold the number of input tweets */
	int num_tweets = 0;					

	/* stage 1: reading the first tweet */
	stage_one(tweets[num_tweets]);
	num_tweets++;
	
	/* stage 2: removing non-alphanumeric characters */
	stage_two(tweets, &num_tweets);
	
	/* stage 3: removing extra asterisks and finding the longest tweet */ 
	stage_three(tweets, num_tweets);
	
	/* stage 4: finding the non-contained tweets */
	stage_four(tweets, num_tweets);
	
	/* stage 5: sorting the tweets */
	stage_five(tweets, num_tweets);
	
	/* all done; take some rest */
	return 0;
}

/* read a line of input into one_tweet */
void
read_one_tweet(tweet_t one_tweet, int max_len) {
	int i = 0, c;
	
	while (((c = getchar()) != EOF) && (c != '\n') && (c != '\r')) {
		if (i < max_len) {
			one_tweet[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	one_tweet[i] = '\0';
}

/* print stage header given stage number */
void 
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */

/* scan a tweet and convert all English letters into lowercase */
void 
tweet_tolower(tweet_t one_tweet) {
	int i;
    for(i = 0; i < MAX_TWEET_LENGTH + 1; i++){
        if ( (one_tweet[i] >= 'A') && (one_tweet[i] <= 'Z') ){
            one_tweet[i] += 32;
        }
    }
}
/*reads tweets from stdin, applies tweet_lower*/
void read_tweets(tweet_t tweets[], int *lines){
	char buffer[MAX_TWEET_LENGTH + 1];
	while (fgets(buffer,sizeof(buffer), stdin) != NULL){
		tweet_tolower(buffer);
		str_append(tweets[*lines], buffer);
		*lines+=1;
	}
	
}
/*filter tweet for alphanum + *, overwrites tweet with replace*/
void clean_tweet(char tweet[MAX_TWEET_LENGTH+1]){
	int c, k = 0;
		char tmp[MAX_TWEET_LENGTH+1] = "";
		for(c = 0; c < len(tweet); c++){
			int ch;
			if ((isalnum((ch = tweet[c])) || (ch == 42))) {
				tmp[k] = ch;
				k++;
			}
		}
	replace(tweet, tmp);
}
/*append characters from src to dest */
char
*str_append(char *dest, char *src){
	int n = MAX_TWEET_LENGTH + 1;
	char *ptr = dest;
	/*get to end of dest*/
	while(*dest){
		dest++;
	}
	while (n--){
		if (!(*dest++ = *src++)){
			return ptr;
		}
	/*terminate str*/
	*dest = '\0';
	}
	return ptr;
}
/*get length of string*/
int
len(char s[]){
	int n;
	for(n = 0; ((s[n]!='\0') && (s[n]!= '\n')); n++);
	return n;
}
/*checks if source in target with dark magic ie. pointer arithmetic*/
int
contained(char *source, char *target){
	char *start_src, *start_tar;
	int i = 0;
	start_src = source;
	start_tar = target;
	while(*target){
		while (*source == *target){
			source++;
			target++;
		}
		if (!(*source)){
			return 1;
		}
		i++;
		source = start_src;
		target = start_tar+i;
	}
	return 0;
}
/* replces dest with src */
char
replace(char *dest, char *src){
    char *ptr;
	ptr = dest;
    while ((*dest++ = *src++));
    return *ptr;
}
/*comparestrings*/
int compare(const void* str1, const void* str2) 
{
    char *string1 = (char*)str1; 
    char *string2 = (char*)str2; 
    return strcmp(string1, string2); 
} 


/* stage 1: reading the first tweet */
void 
stage_one(tweet_t one_tweet) {
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	int lines;
	read_tweets(one_tweet, &lines);
	printf("%s\n\n", one_tweet);
}


/* stage 2: removing non-alphanumeric characters */
void 
stage_two(tweet_t tweets[], int *num_tweets) {
	/* PRINT HEADER */
	print_stage_header(STAGE_NUM_TWO);
	int i = 0, line;
	while(len(*(tweets+i)) != 0){
		i++;
	}
	*num_tweets = i;
	for (line = 0; line < *num_tweets; line++){
		clean_tweet(tweets[line]);
		printf("%s\n",tweets[line]);
	} 
	printf("\n");
}


/* stage 3: removing extra asterisks and finding the longest tweet */ 
void 
stage_three(tweet_t tweets[], int num_tweets) {
	print_stage_header(STAGE_NUM_THREE);
	tweet_t clean[MAX_TWEET_LENGTH + 1];
	char *longest;
	int ch, i, j, line, offset, length = 0;
	for (line = 0; line < num_tweets; line++){
		i = 0;
		j = 0;
		while((ch = tweets[line][i]) != '\0'){
			clean[line][j] = ch;
			i++;
			j++;
			if(ch == 42){
				offset = 0;
				while((tweets[line][i + offset]) == 42){
					offset++;
				}
				i += offset;
			}

		}
		/*overwriting tweets */
		replace(tweets[line], clean[line]);
		printf("%s\n",tweets[line]);
		if (len(clean[line]) > length){
			length = len(clean[line]);
			longest = clean[line];
		}

	}
	printf("Total: %d\n", num_tweets);
	printf("Longest: %s\n", longest);
	printf("Length = %d\n\n", length);
}

/* stage 4: finding the non-contained tweets */
void 
stage_four(tweet_t tweets[], int num_tweets) {
	print_stage_header(STAGE_NUM_FOUR);
	int i, j, k, l = 0, arr[num_tweets];
	for(i = 0; i < num_tweets; i++){
		k = -1;
		for(j = 0; j < num_tweets; j++){
			if (i != j){
				if ((contained(tweets[i], tweets[j])) == 1){
					k = i;
				}
			}
		}
		arr[i] = k;
	}
	for(i=0;i<num_tweets;i++){
		if (arr[i] > 0){
			l++;
		}
		else{
			printf("%s\n",tweets[i]);
		}
	}
	printf("Non-contained: %d\n\n", num_tweets - l);
}

/* stage 5: sorting the tweets */
/*Using QSORT from STDLIB, COMPARE contains STRCMP as return */
void 
stage_five(tweet_t tweets[], int num_tweets) {
	/* add code for stage 5 (optional stage) */
	print_stage_header(STAGE_NUM_FIVE);
	int line;
	qsort(tweets, num_tweets, sizeof(tweets[0]), compare);
	for(line = 0; line < num_tweets; line ++){
	printf("%s\n",tweets[line]);
	}
}
