/* Tweet cleanser:
 * Removes non-alphanumeric characters from tweets
 *
 * Skeleton code written by Yi Han and Jianzhong Qi, April 2019
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
void str_append(char *dest, char *src);
int len(char s[]);
void read_tweets(tweet_t tweets[], int *lines);
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
void
str_append(char *dest, char *src){
	int i, j;
	/* Get len of dest */
	for(i=0; ((dest[i]!='\0') && (dest[i]!= '\n')); i++);
	dest[i] = '\n';
	for(j=0; ((src[j]!='\0') && (src[j]!= '\n')); j++, i++)
    {
        dest[i]=src[j];
    }
    dest[i]='\0';
}
/*void
read_tweets(tweet_t tweets, int *lines){
	int ch;
	lines = 0;
	while ((ch = scanf("%c", tweets)) != EOF){
		if (ch == '\n' || ch == '\r'){
			*lines+=1;
		}
	}
} */
void
read_tweets(tweet_t tweets[], int *lines){
	char buffer[MAX_TWEET_LENGTH + 1];
    while(fgets(buffer, MAX_TWEET_LENGTH + 1, stdin)){
		int i = 0;
		str_append(tweets[i], buffer);
		*lines += 1;
		i += 1;
		
	}
}
int
len(char s[]){
	int n;
	for(n = 0; ((s[n]!='\0') && (s[n]!= '\n')); n++);
	return n;
}



/* stage 1: reading the first tweet */
void 
stage_one(tweet_t one_tweet) {
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);
	read_one_tweet(one_tweet, MAX_TWEET_LENGTH + 1);
	tweet_tolower(one_tweet);
	printf("%s\n\n", one_tweet);
}


/* stage 2: removing non-alphanumeric characters */
void 
stage_two(tweet_t tweets[], int *num_tweets) {
	/* PRINT HEADER */
	print_stage_header(STAGE_NUM_TWO);
    int i = 0;
    char buffer[MAX_TWEET_LENGTH + 1] = "";
    while(fgets(buffer, MAX_TWEET_LENGTH + 1, stdin)){
        str_append(*(tweets+i), buffer);
        i+=280;
    }
    for (i = 0; i < *num_tweets; i++){
    printf("xx%d,%d\n",*num_tweets ,len(tweets[i]));
    }
}


/* stage 3: removing extra asterisks and finding the longest tweet */ 
void 
stage_three(tweet_t tweets[], int num_tweets) {
	/* add code for stage 3 */
	
}

/* stage 4: finding the non-contained tweets */
void 
stage_four(tweet_t tweets[], int num_tweets) {
	/* add code for stage 4 */
	
}

/* stage 5: sorting the tweets */
void 
stage_five(tweet_t tweets[], int num_tweets) {
	/* add code for stage 5 (optional stage) */
	
}
