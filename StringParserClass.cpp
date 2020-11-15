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
namespace KP_StringParserClass {
	StringParserClass::StringParserClass() {
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

		pEndTag = (char*) malloc(strlen(pStart) * sizeof(char));
		pStartTag = (char*) malloc(strlen(pEnd) * sizeof(char));

		strcpy(pStartTag, pStart);
		strcpy(pEndTag, pEnd);

		return (SUCCESS);
	}

	int StringParserClass::getDataBetweenTags(char *pDataToSearchThru,
			vector<string> &myVector) {

		if (pStartTag == NULL || pEndTag == NULL) {
			return (ERROR_TAGS_NULL);
		}

		if (pDataToSearchThru == NULL) {
			return (ERROR_DATA_NULL);
		}

		myVector.clear();
		char *startTag1 = pDataToSearchThru;
		char *startTag2;

		char *endTag1 = pDataToSearchThru;
		char *endTag2;

		while (findTag(pStartTag, startTag1, startTag2) == SUCCESS
				&& findTag(pEndTag, endTag1, endTag2) == SUCCESS) {
			string data = "";
			++startTag2;
			while (startTag2 != endTag1) {
				data += *startTag2;
				++startTag2;
			}
			myVector.push_back(data);
			startTag1 = endTag2++;
			endTag1 = startTag1;
		}

		return (SUCCESS);
	}

	void StringParserClass::cleanup() {

	}

	int StringParserClass::findTag(char *pTagToLookFor, char *&pStart,
			char *&pEnd) {

		if (pStart == NULL || pEnd == NULL) {
			return (ERROR_TAGS_NULL);
		}
		pEnd = pStart;
		while (*pEnd != '\0') {
			if (*pStart == *pTagToLookFor) {
				char *temp = pTagToLookFor;
				while (*pEnd == *temp) {
					++temp;
					if (*temp == '\0') {
						return (SUCCESS);
					}
					++pEnd;
				}
			}
			++pStart;
			pEnd = pStart;
		}

		return (FAIL);
	}
}
