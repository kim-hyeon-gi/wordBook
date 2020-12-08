#include <wordBook.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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