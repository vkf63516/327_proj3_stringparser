/*
 * StringParserClass.cpp
 *
 *  Created on: Nov 11, 2020
 *      Author: Vishal Fenn
 */

#include <vector>
#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;
using namespace KP_StringParserClass;
StringParserClass::StringParserClass(void) {
	pEndTag = NULL;
	pStartTag = NULL;
	areTagsSet = false;
}

//call cleanup to release any allocated memory
StringParserClass::~StringParserClass(void) {
	cleanup();

}

int StringParserClass::setTags(const char *pStart, const char *pEnd) {
	if (pStart == NULL || pEnd == NULL) {
		return (ERROR_TAGS_NULL);
	}

	pStartTag = new char[strlen(pStart) + 1];
	pEndTag = new char[strlen(pEnd) + 1];
	strncpy(pStartTag, pStart, strlen(pStart));
	strncpy(pEndTag, pEnd, strlen(pEnd));

	areTagsSet = true;
	return (SUCCESS);

}

int StringParserClass::getDataBetweenTags(char *pDataToSearchThru,
        vector<string> &myVector) {

	myVector.clear();

	if (pStartTag == NULL || pEndTag == NULL) {
		return (ERROR_TAGS_NULL);
	}
	if (pDataToSearchThru == NULL) {
		return (ERROR_DATA_NULL);
	}
	char *start1Ptr = pDataToSearchThru;
	char *end1Ptr;
	char *start2Ptr = pDataToSearchThru;
	char *end2Ptr;

	while (findTag(pStartTag, start1Ptr, end1Ptr) == SUCCESS
	        && findTag(pEndTag, start2Ptr, end2Ptr) == SUCCESS) {
		string data = "";
		++end1Ptr;
		while (end1Ptr != start2Ptr) {
			data += *end1Ptr;
			++end1Ptr;
		}
		myVector.push_back(data);
		start1Ptr = end2Ptr;
		end1Ptr = start1Ptr;
	}

	return (SUCCESS);
}

void StringParserClass::cleanup() {
	if (pStartTag) {
		delete[] pStartTag;
		pStartTag = 0;
	}
	if (pEndTag) {
		delete[] pEndTag;
		pEndTag = 0;
	}

}
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
        char *&pEnd) {

	if (pStart == NULL || pEnd == NULL) {
		return (ERROR_TAGS_NULL);
	}
	pEnd = pStart;

	while (*pEnd != '\0') {
		if (*pStart == *pTagToLookFor) {
			char *tagTemp = pTagToLookFor;
			while (*pEnd == *tagTemp) {
				++tagTemp;
				if (*tagTemp == '\0') {
					return (SUCCESS);
				}
				++pEnd;
			}
		}
		pStart++;
		pEnd = pStart;
	}
	return (FAIL);
}

