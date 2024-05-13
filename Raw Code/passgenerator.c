#include "hash.h"
#define error(m, c) do{fprintf(stderr, "%s\n", m);exit(c);}while(0)
hashset h;
char* words[100000];
static int N;
typedef struct{
	int from_index;
	int to_index;
}producer_task;
static pthread_mutex_t mutex;
void* producer(void* args){
	producer_task* task = (producer_task*)args;
	for(int j = task->from_index; j <= task->to_index;j++){
		pthread_mutex_lock(&mutex);
		insert(&h, words[j]);
		pthread_mutex_unlock(&mutex);
	}
}

static int m;
static int k;
static int l;
void* consumer(void* args){
	char password[25*l];
	for(int i = 0; i < k/m;i++){
		for(int j = 0; j < l;j++){
			char* random_word = words[rand()%N];
			pthread_mutex_lock(&mutex);
			int was_deleted = delete_value(&h,random_word);
			pthread_mutex_unlock(&mutex);
			if(!was_deleted){
				j--;
				continue;
			}
			if(j)
				sprintf(password, "%s%s", password, random_word);
			else
				strcpy(password, random_word);
		}
		printf("%s\n", password);
	}
}
int main(int argc, char** argv) {
	srand(time(NULL));
	pthread_mutex_init(&mutex, NULL);
	int n;
	char* file;
	if(argc != 11)
		error("fatal error: use the following command Arguments: -p n -c m -f -n k file -l l", 1);
	char* message = (char*) malloc(100);
	while(*++argv){
		if(argv[0][0] != '-'){
			sprintf(message, "fatal error: illegal command-line detected: %s", *argv);
			error(message, 2);
		}
		switch(argv[0][1]){
			case 'p':
			sscanf(*(++argv), "%d", &n);
			break;
			case 'c':
			sscanf(*(++argv), "%d", &m);
			break;
			case 'l':
			sscanf(*(++argv), "%d", &l);
			break;
			case 'n':
			sscanf(*(++argv), "%d", &k);
			break;
			case 'f':
			file = (char*) malloc(100);
			sscanf(*(++argv), "%s", file);
			break;
			default:
			sprintf(message, "fatal error: flag -%c is not supported", argv[0][1]);
			error(message, 3);
		}
	}
	if(k % m)
		error("fatal error: requested number of passwords is not divisible by the given number of consumers", 4);
	h = set_init();
	char word[500];
	FILE* f = fopen(file, "r");
	int i = 0;
	while(fgets(word, 500, f)){
		int n = strlen(word);
		if(!n)continue;
		if(word[n-1] == '\n')
			word[n-1] = '\0';
		words[i++] = strdup(word);
	}
	fclose(f);
	N = i;

	pthread_t pthreads[n];
	producer_task tasks[n];
	for(int s = 0; s < n; s++){
		tasks[s].from_index = s * N / n;
		tasks[s].to_index = (s + 1) * N / n - 1;

		pthread_create(&pthreads[s], NULL, producer, &tasks[s]);
	}

	for(int s = 0; s < n; s++)
		pthread_join(pthreads[s], NULL);
	pthread_t cthreads[m];
	for(int s = 0; s < m; s++){
		pthread_create(&cthreads[s], NULL, consumer, NULL);
	}
	for(int s = 0; s < m; s++)
		pthread_join(cthreads[s], NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}