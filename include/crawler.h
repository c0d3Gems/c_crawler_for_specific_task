

	#ifndef CRAWLER_H
	#define CRAWLER_H

		#pragma once
		//to speed up the compilation process


		#include <stdio.h>
		#include <stdlib.h>
		#include <pthread.h>
		#include <string.h>
		#include <time.h>
		#include <unistd.h>
		#include <curl/curl.h>
		// standard libraries


		#include "string.h"
		#include "threading.h"
		#include "requests.h"
		#include "log.h"
		#include "time.h"
		// custom libraries



		#ifndef false
			#define false 0
			#define true !false
		#endif

		#ifndef NULL
			#define NULL ((void*)0)
		#endif

		#ifndef LOGFILE
			#define LOGFILE "log.txt"
			#define MAX_LOGFILE_SIZE 512024 //max number of bytes for the logFile 
		#endif	

		#ifndef CONCAT
			#define CONCAT(a,b) (const char*)(a b)
		#endif	

		#ifndef DOWNLOAD_DIRECTORY
			#define DOWNLOAD_DIRECTORY	(const char*)"dlds/"
		#endif


		extern unsigned short LOGGING_MODE;
		//variable used for log writing modes

		extern unsigned long long LOGFILE_SIZE;
		//for keeping track of the log file size

		static const char* sources[]={									
				"https://www.nytimes.com/", 	
				"https://www.wsj.com/",	
				"https://techcrunch.com/", 
				"https://www.theverge.com/",
				"https://www.recode.net/",
				"https://www.cnet.com/news/", 
				"https://www.reuters.com/",
				"https://www.theguardian.com/us",
				"http://www.bbc.com/news",
				"http://www.telegraph.co.uk/news/",
				(const char*)NULL
			};

		static const char* fpath[]={									
				"dlds/nytimes", 	
				"dlds/wsj",	
				"dlds/techcrunch", 
				"dlds/theverge",
				"dlds/recode",
				"dlds/cnet", 
				"dlds/reuters",
				"dlds/theguardian",
				"dlds/bbc",
				"dlds/telegraph",
				(const char*)NULL
			};
	
		struct imgListStruct
		{
			char **img;
			unsigned long long numberOfImages;
		};

		struct articleStruct
		{
			unsigned long long urlSize;
			unsigned long long titleSize;
			unsigned long long contentSize;
			char *url;
			char *title;
			char *content;
			struct imgListStruct** imgList;
		};

		struct wrapperStruct
		{
			unsigned long long urlSize;
			unsigned long long fpathSize;
			unsigned long long numberOfArticles;
			char* url;
			char* fpath;
			struct articleStruct** article;
		};

	extern struct wrapperStruct* wrapperArray[];
//crawler specific function headers	

	unsigned long long getFileSize(const char *fpath);
	//function that returns 0 if file could not be opened
	//						1 if file exists, but it's empty
	//					   	the file size +1


	void printLog(char* str);
	//custom writing function for log & console operation information


		
	char *getSourceFromUrl(const char* url);
	//basic string manipulation to get a decent filename from a url



	// unsigned short
	// customWriteFunction(void* payload,size_t size,size_t times,struct string* str);
	//custom fwrite implmentation to fit our crawler's needs



	const char* genIndexFileName(char* str);
	//function to generate a index file name and appending it to the download directory.


	
	char *getFilePath(char* fname);
	//function that returns the full path of the web page we've downloaded.
	//gets the index fileName from the upper function and concatenates the DOWNLOAD_DIRECTORY in front of it


	void* threadFunc(void* param);
	// function enclosure for our thread spawning
	


	size_t checkForNewContent(const char **sources, size_t vecSize);
	// in a multi threaded environment, here we spawn the threads

	void newLogFile();
	//creates a new empty log file and moves the content of the already existent log file in lastLog.txt



	void wrapperArrayInit();
	//wrapper Array initializer


	void freeWrapperArray();
	//free the memory occupied by the wrapper array and its elements


	void printSources();
	//print url sources to the command line (standard output)

	void printPaths();
	//print paths to the command line (standard output)

	
	size_t customWriteFunction(char* payload, size_t size, size_t nmemb, const char* dest);
	//custom write function for threaded writing of output to a variable

	char* getContentFromUrl(const char* url);
	//sends a custom request to the url mentioned as parameter

	void initContentInWrapperObject(const char* url, struct wrapperStruct* pWrapper);
	//this allocates space for the content in the wrapper object that has the same url

	void extractLinks(char *,struct string **);
	//function that analyzes the rawHtml (first parameter)
	//and returns all of the relevant links from an article in 
	//an array of strings (second parameter)

	void scrapeContent(struct wrapperStruct* pWrapper);
	//this function will remove the irellevant code from the page. 





	#endif	