#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

#define DIE(assertion, call_description)	

#include "structs.h"

#define MAX 256

int add_last(void **arr, int *len, data_structure *data);

int add_at(void **arr, int *len, data_structure *data, int index);

void find(void *data_block, int len, int index) 
{

}

int delete_at(void **arr, int *len, int index)
{

}

// used to create a data structure
void create_data(char *line, data_structure *data_block, char *token);

// used to print stored data
void print_data(void **arr, int len);

int main() {
	// the vector of bytes u have to work with
	// good luck :)
	void *arr = NULL;
	int len = 0;  // used for counting the number of structures in arr
	int go = 1;
	char *line = malloc(256 * sizeof(char));
	if (!line) {
		fprintf(stderr, "Malloc failed\n");
		return -1;
	}

	char *token;
	data_structure *data_block = malloc(sizeof(*data_block));
	DIE(!data_block, "Malloc failed\n");

	data_block->header = malloc(sizeof(head));
	DIE(!data_block->header, "Malloc failed\n");
	if (!data_block->header) {
		fprintf(stderr, "Malloc failed\n");
		return -1;
	}
	while (go) {
		fgets(line, MAX, stdin);
		line[strlen(line) - 1] = '\0';
		if (line[0] != 'p' && line[0] != 'e') {
			token = strtok(line, " ");
			if (strcmp(token, "insert") == 0) {
				create_data(line, data_block, token);
				if (add_last(&arr, &len, data_block) != 0) {
					return -1;
				}
				free(data_block->data);  // we have to free auxiliars
			} else if (strcmp(token, "insert_at") == 0) {
				token = strtok(NULL, " ");
				int index = atoi(token);
				create_data(line, data_block, token);
				if (add_at(&arr, &len, data_block, index) != 0) {
					return -1;
				}
			}
		} else if (line[0] == 'p' || line[0] == 'e') {
			if (strcmp(line, "print") == 0) {
				print_data(&arr, len);
			}
		}
	}
	return 0;
}

int add_last(void **arr, int *len, data_structure *data)
{
	if (*arr == NULL) {
		unsigned int len_to_alloc = sizeof(unsigned char) + sizeof(unsigned int) + data->header->len;
		*arr = malloc(len_to_alloc);
		DIE(!(*arr), "Malloc failed\n");
		memcpy(*arr, &data->header->type, sizeof(unsigned char));
		memcpy((*arr + sizeof(unsigned char)), &data->header->len, sizeof(unsigned int));
		memcpy((*arr + len_to_alloc - data->header->len), data->data, data->header->len);
		(*len)++;
		return 0;
	} else {
		unsigned int aux_len = 0;
		for (int i = 0; i < *len; i++) {
			unsigned char type = *(unsigned char *)(*arr + aux_len);
			unsigned int len_of_data = *(unsigned int *)(*arr + aux_len + sizeof(type));
			aux_len += sizeof(type) + sizeof(len_of_data) + len_of_data;
		}
		unsigned int new_len = aux_len + sizeof(unsigned char) + sizeof(unsigned int) + data->header->len;
		*arr = realloc(*arr, new_len);
		memcpy((*arr + aux_len), &data->header->type, sizeof(unsigned char));
		memcpy((*arr + aux_len + sizeof(unsigned char)), &data->header->len, sizeof(unsigned int));
		memcpy((*arr + new_len - data->header->len), data->data, data->header->len);
		(*len)++;
		return 0;
	}
	return -1;
}

int add_at(void **arr, int *len, data_structure *data, int index) {
	if (index < 0) {
		return -1;
	}

	if (index >= *len) {
		return add_last(arr, len, data);
	}

	while (index > 0) {

	}
}

void create_data(char *line, data_structure *data_block, char *token) {
	char *name_1, *name_2;
	data_block->header->len = 0;
				token = strtok(NULL, " ");
				data_block->header->type = *(unsigned char *)token;
				token = strtok(NULL, " ");
				name_1 = malloc((strlen(token) + 1) * sizeof(char));
				DIE(!name_1, "Malloc failed\n");
				strcpy(name_1, token);
				data_block->data = malloc(strlen(name_1) + 1);
				memcpy(data_block->data, name_1, strlen(name_1) + 1);
				data_block->header->len += strlen(name_1) + 1;
				token = strtok(NULL, " ");

				//  now testing for each case to see how we store data
				if (data_block->header->type == '1') {
					data_block->header->len += 2 * sizeof(int8_t);
					int8_t sum_1 = atoi(token);
					token = strtok(NULL, " ");
					int8_t sum_2 = atoi(token);
					data_block->data = realloc(data_block->data, data_block->header->len);
					memcpy(data_block->data + strlen(name_1) + 1, &sum_1, sizeof(int8_t));
					memcpy(data_block->data + strlen(name_1) + 1 + sizeof(int8_t), &sum_2,
						   sizeof(int8_t));
				} else if (data_block->header->type == '2') {
					data_block->header->len += sizeof(int16_t) + sizeof(int32_t);
					int16_t sum_1 = atoi(token);
					token = strtok(NULL, " ");
					int32_t sum_2 = atoi(token);
					data_block->data = realloc(data_block->data, data_block->header->len);
					memcpy(data_block->data + strlen(name_1) + 1, &sum_1, sizeof(int16_t));
					memcpy(data_block->data + strlen(name_1) + 1 + sizeof(int16_t), &sum_2,
						   sizeof(int32_t));
				} else {
					data_block->header->len += 2 * sizeof(int32_t);
					int32_t sum_1 = atoi(token);
					token = strtok(NULL, " ");
					int32_t sum_2 = atoi(token);
					data_block->data = realloc(data_block->data, data_block->header->len);
					memcpy(data_block->data + strlen(name_1) + 1, &sum_1, sizeof(int32_t));
					memcpy(data_block->data + strlen(name_1) + 1 + sizeof(int32_t), &sum_2,
						   sizeof(int32_t));
				}
				token = strtok(NULL, " ");
				name_2 = malloc((strlen(token) + 1) * sizeof(char));
				strcpy(name_2, token);
				data_block->header->len += strlen(name_2) + 1;
				data_block->data = realloc(data_block->data, data_block->header->len);
				memcpy(data_block->data + data_block->header->len - strlen(name_2) - 1,
					   name_2, strlen(name_2) + 1);
	free(name_1);
	free(name_2);  // we have to free auxiliars
}

void print_data(void **arr, int len) {
	unsigned int aux_len = 0;
	for (int i = 0; i < len; i++) {
		unsigned char type = *(unsigned char *)(*arr + aux_len);
		unsigned int len_of_data = *(unsigned int *)(*arr + aux_len + sizeof(type));
		aux_len += sizeof(type) + sizeof(len_of_data);
		if (type == '1') {
			printf("Tipul 1\n");
			char *name_1 = (char *)(*arr + aux_len);
			printf("%s pentru ", name_1);
			int8_t sum_1 = *(int8_t *)(*arr + aux_len + strlen(name_1) + 1);
			int8_t sum_2 = *(int8_t *)(*arr + aux_len + strlen(name_1) + 1 + sizeof(int8_t));
			char *name_2 = (char *)(*arr + aux_len + strlen(name_1) + 1 + 2 * sizeof(int8_t));
			printf("%s\n", name_2);
			printf("%"PRId8"\n", sum_1);
			printf("%"PRId8"\n", sum_2);
			printf("\n");
			aux_len += len_of_data;
		} else if (type == '2') {
			printf("Tipul 2\n");
			char *name_1 = (char *)(*arr + aux_len);
			printf("%s pentru ", name_1);
			int16_t sum_1 = *(int16_t *)(*arr + aux_len + strlen(name_1) + 1);
			int32_t sum_2 = *(int32_t *)(*arr + aux_len + strlen(name_1) + 1 + sizeof(int16_t));
			char *name_2 = (char *)(*arr + aux_len + strlen(name_1) + 1 + sizeof(int16_t) + sizeof(int32_t));
			printf("%s\n", name_2);
			printf("%"PRId16"\n", sum_1);
			printf("%"PRId32"\n", sum_2);
			printf("\n");
			aux_len += len_of_data;
		} else {
			printf("Tipul 3\n");
			char *name_1 = (char *)(*arr + aux_len);
			printf("%s pentru ", name_1);
			int32_t sum_1 = *(int32_t *)(*arr + aux_len + strlen(name_1) + 1);
			int32_t sum_2 = *(int32_t *)(*arr + aux_len + strlen(name_1) + 1 + sizeof(int32_t));
			char *name_2 = (char *)(*arr + aux_len + strlen(name_1) + 1 + 2 * sizeof(int32_t));
			printf("%s\n", name_2);
			printf("%"PRId32"\n", sum_1);
			printf("%"PRId32"\n", sum_2);
			printf("\n");
			aux_len += len_of_data;
		}
	}
}
