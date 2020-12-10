#pragma warning(disable:4996)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wordBook.h"

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
