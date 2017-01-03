extern "C" {
#include <stdlib.h>
#include <stdio.h>
}

#include "garbageCollection.h"

typedef struct GarbageList GarbageList;
typedef GarbageList* GarbageListPtr;

struct GarbageList {
	void* cleanOne;
	GarbageListPtr parent;
	GarbageListPtr child;
};

static GarbageListPtr garbageHead;
static GarbageListPtr garbageTail;

void auto_cleanup(void* obj) {
	if(garbageHead == NULL) {
		garbageHead = (GarbageListPtr) malloc(sizeof(GarbageList));
		garbageHead->cleanOne = obj;
		garbageTail = garbageHead;
	} else {
		garbageTail->child = (GarbageListPtr) malloc(sizeof(GarbageList));
		garbageTail->child->cleanOne = obj;
		garbageTail->child->parent = garbageTail;
		garbageTail = garbageTail->child;
	}
}

void free_all() {
	if(garbageHead != NULL) {
		GarbageListPtr curPtr = garbageTail;
		while(1) {
			free(curPtr->cleanOne);
			if(curPtr->parent != NULL) {
				curPtr = curPtr->parent;
				free(curPtr->child);
			} else {
				free(curPtr);
				break;
			}		
		}
		garbageHead = NULL;
		garbageTail = NULL;
	}
}
