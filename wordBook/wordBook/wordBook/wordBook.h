#pragma once
#ifndef _WORDBOOK_H
#define _WORDBOOK_H
typedef signed long int Long;
typedef struct _word {
	char spelling[64];
	char wordClass[16];
	char mean[16];
	char example[256];
} Word;

typedef struct _wordBook {
	Word(*words);
	Long capacity;
	Long length;
} WordBook;

void Create(WordBook* wordBook, Long capacity);
void Destroy(WordBook* wordBook);
Long Record(WordBook* wordBook, char(*spelling), char(*wordClass), char(*mean), char(*example));
Long Correct(WordBook* wordBook, Long index, char(*wordClass), char(*mean), char(*example));
void FindSpelling(WordBook* wordBook, char(*spelling), char(*indexes), Long* count);
void FindMean(WordBook* wordBook, char(*mean), Long* (*indexes));
Long Save(WordBook* wordBook);
Long Load(WordBook* wordBook);

#endif // _WORDBOOK_H
