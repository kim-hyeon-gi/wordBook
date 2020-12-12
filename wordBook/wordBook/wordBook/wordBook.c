#pragma warning(disable:4996)
#include <stdio.h>
#include "wordBook.h"
#include <stdlib.h>
#include <string.h>


#if 0
int main(int args, char* argv[]) {
	WordBook wordBook;
	Long(*indexes) = NULL;
	Long count;
	Long index;
	Create(&wordBook, 3);
	count = Load(&wordBook);
	index = Record(&wordBook, "view", "동사", "보다", "esdsdsds");
	printf("%d %s %s %s %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].mean, wordBook.words[index].example);
	index = Record(&wordBook, "find", "동사", "보다", "esdsdsds");
	printf("%d %s %s %s %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].mean, wordBook.words[index].example);
	index = Record(&wordBook, "preods", "동사", "보다", "esdsdsds");
	printf("%d %s %s %s %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].mean, wordBook.words[index].example);
	index = Record(&wordBook, "vadsad", "동사", "보다", "esdsdsds");
	printf("%d %s %s %s %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].mean, wordBook.words[index].example);
	index = Record(&wordBook, "qweqweqw", "동사", "보다", "esdsdsds");
	printf("%d %s %s %s %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].mean, wordBook.words[index].example);

	printf("찾기");
	FindSpelling(&wordBook, "find", &indexes, &count);
	index = 0;
	printf("%d %s %s %s %s\n", index + 1, wordBook.words[indexes[index]].spelling, wordBook.words[indexes[index]].wordClass, wordBook.words[indexes[index]].mean, wordBook.words[indexes[index]].example);
	printf("고치기\n");
	index = Correct(&wordBook, 2, "동사", "섭취하다", "ㄷㄴㅁ");
	printf("%d %s %s %s %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].mean, wordBook.words[index].example);

	index = Erase(&wordBook, 2);
	if (index == -1) {
		printf("지웠음");
	}

	index = 0;
	printf("지운거 확인");
	while (index < wordBook.length) {
		printf("%d %s %s %s %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].mean, wordBook.words[index].example);
		index++;
	}

	Arrange(&wordBook);
	index = 0;
	printf("정렬\n");
	while (index < wordBook.length) {
		printf("%d %s %s %s %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].mean, wordBook.words[index].example);
		index++;
	}




	Save(&wordBook);
	if (indexes != NULL) {
		free(indexes);
	}





	Destroy(&wordBook);

	return 0;
}
#endif

void Create(WordBook* wordBook, Long capacity) {

	wordBook->words = (Word(*))calloc(capacity, sizeof(Word));
	wordBook->capacity = capacity;
	wordBook->length = 0;
}
void Destroy(WordBook* wordBook) {

	if (wordBook->words != NULL) {
		free(wordBook->words);
		printf("%s", "할당 해제되었습니다.");
	}
}

Long Load(WordBook* wordBook) {
	Word(*words) = NULL;
	Word word;
	Long index;
	Long i = 0;
	size_t flag;
	FILE* file;
	file = fopen("WordBook.dat", "rb");
	if (file != NULL) {
		flag = fread(&word, sizeof(Word), 1, file);
		while (!feof(file) && flag != 0) {
			if (wordBook->length >= wordBook->capacity) {
				words = (Word(*))calloc(wordBook->capacity + 1, sizeof(Word));
				while (i < wordBook->length) {
					words[i] = wordBook->words[i];
					i++;
				}
				if (wordBook->words != NULL) {
					free(wordBook->words);
				}
				wordBook->words = words;
				wordBook->capacity++;
			}
			index = wordBook->length;
			wordBook->words[index] = word;
			wordBook->length++;
			flag = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return wordBook->length;
}
Long Save(WordBook* wordBook) {
	Long i = 0;
	FILE* file;
	file = fopen("WordBook.dat", "wb");
	if (file != NULL) {
		while (i < wordBook->length) {
			fwrite(wordBook->words + i, sizeof(Word), 1, file);
			i++;
		}
		fclose(file);
	}
	return wordBook->length;
}

Long Record(WordBook* wordBook, char(*spelling), char(*wordClass), char(*mean), char(*example)) {
	Long index = 0;
	Word(*words) = NULL;
	Long i = 0;
	if (wordBook->length >= wordBook->capacity) {
		words = (Word(*))calloc(wordBook->capacity + 1, sizeof(Word));
		while (i <= wordBook->length) {
			words[i] = wordBook->words[i];
			i++;
		}

		if (wordBook->words != NULL) {
			free(wordBook->words);
		}
		wordBook->words = words;
		wordBook->capacity++;
	}

	index = wordBook->length;
	strcpy(wordBook->words[index].spelling, spelling);
	strcpy(wordBook->words[index].wordClass, wordClass);
	strcpy(wordBook->words[index].mean, mean);
	strcpy(wordBook->words[index].example, example);
	wordBook->length++;
	return index;
}

void FindSpelling(WordBook* wordBook, char(*spelling), Long* (*indexes), Long* count) {
	Long index = 0;
	Long i = 0;
	*count = 0;
	*indexes = NULL;
	while (index < wordBook->length) {
		if (strcmp(wordBook->words[index].spelling, spelling) == 0) {
			(*count)++;
		}
		index++;
	}
	if (*count > 0) {
		*indexes = (Long(*))calloc(*count, sizeof(Long));
		index = 0;
		while (index < wordBook->length) {
			if (strcmp(wordBook->words[index].spelling, spelling) == 0) {
				*indexes[i] = index;
				i++;
			}
			index++;
		}
	}
}
Long Correct(WordBook* wordBook, Long index, char(*wordClass), char(*mean), char(*example)) {
	strcpy(wordBook->words[index].wordClass, wordClass);
	strcpy(wordBook->words[index].mean, mean);
	strcpy(wordBook->words[index].example, example);
	return index;
}
void FindMean(WordBook* wordBook, char(*mean), Long* (*indexes), Long* count) {
	Long index = 0;
	Long i = 0;
	*count = 0;
	*indexes = NULL;
	while (index < wordBook->length) {
		if (strcmp(wordBook->words[index].mean, mean) == 0) {
			(*count)++;
		}
		index++;
	}
	if (*count > 0) {
		*indexes = (Long(*))calloc(*count, sizeof(Long));
		index = 0;
		while (index < wordBook->length) {
			if (strcmp(wordBook->words[index].mean, mean) == 0) {
				*indexes[i] = index;
				i++;
			}
			index++;
		}
	}
}
Long Erase(WordBook* wordBook, Long index) {
	Word(*words) = NULL;
	Long i = 0;
	if (wordBook->capacity > 1) {
		words = (Word(*))calloc(wordBook->capacity - 1, sizeof(Word));
		while (i < index) {
			words[i] = wordBook->words[i + 1];
			i++;
		}
		while (i < wordBook->length - 1) {
			words[i] = wordBook->words[i + 1];
			i++;

		}
	}
	if (wordBook->words != NULL) {
		free(wordBook->words);
	}
	if (wordBook->capacity > 1) {
		wordBook->words = words;
	}
	wordBook->capacity--;
	wordBook->length--;
	index = -1;
	return index;
}
