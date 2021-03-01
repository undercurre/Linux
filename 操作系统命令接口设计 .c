#include<windows.h>
#include <time.h>
#include<string.h>
#include<stdio.h>

DWORD dwTotalFileNum=0;
//////////////////////////////////////////////////////////
//获取系统时间
void GetTime()
{
	int sec, min, hour, MonthDay, month, year, WeekDay;//参数定义
	struct tm * timeptr;
	//struct tm {                //时钟结构
	//int tm_sec;         /* 秒，范围从 0 到 59        */
	//int tm_min;         /* 分，范围从 0 到 59        */
	//int tm_hour;        /* 小时，范围从 0 到 23        */
	//int tm_mday;        /* 一月中的第几天，范围从 1 到 31    */
	//int tm_mon;         /* 月，范围从 0 到 11        */
	//int tm_year;        /* 自 1900 年起的年数        */
	//int tm_wday;        /* 一周中的第几天，范围从 0 到 6    */
	//int tm_yday;        /* 一年中的第几天，范围从 0 到 365    */
	//int tm_isdst;       /* 夏令时                */
    //};
	char weekdayString[10];
	time_t calendar;   //日历时间类
	time(&calendar);//获取系统时间  &引用且返回 time（）计算当前日历时间
	timeptr = localtime(&calendar);//转化为当地时间 location（）把时间设为本地时区并转化为时钟结构
	year = timeptr->tm_year;//时钟结构体赋值赋值给相应变量
	month = timeptr->tm_mon;
	MonthDay = timeptr->tm_mday;
	WeekDay = timeptr->tm_wday;
	hour = timeptr->tm_hour;
	min = timeptr->tm_min;
	sec = timeptr->tm_sec;
	switch(WeekDay)
	{
	    case 01: strcpy(weekdayString,"Monday");break;
		case 02: strcpy(weekdayString,"Tuesday");break;
		case 03: strcpy(weekdayString,"Wednesday");break;
		case 04: strcpy(weekdayString,"Thursday");break;
		case 05: strcpy(weekdayString,"Friday");break;
		case 06: strcpy(weekdayString,"Saturday");break;
		case 07: strcpy(weekdayString,"Sunday");break;
	}
	printf("%4d-%02d-%02d %s %02d:%02d:%02d\n", 1900 + year, 1 + month, MonthDay, weekdayString, hour, min, sec);
}
////////////////////////////////////////////////////////////////////////////////////
//回显字符串
void ReviewString()
{
	char a[100];
	printf("请输入字符串\n");
	scanf("%s",a);
	printf("%s\n",a);
}
////////////////////////////////////////////////////////////////////////////////////
//创建目录
void CreateCatalogue()
{
	char a[30]; //在当前目录下创建子目录
	LPSTR szDirPath;  //注意再次新建的时候由于之前已经成功新建，就会提示创建失败 LPSTR是Win32和VC++所使用的一种字符串数据类型
	printf("请输入要创建目录的名称:\n");
	scanf("%s",a);
	szDirPath=a;
	if(!CreateDirectory(szDirPath,NULL))
			//函数原型：
				//BOOL CreateDirectory(
				//	LPCWSTR lpPathName,
				//	LPSECURITY_ATTRIBUTES lpSecurityAttributes
				// pPathName：长指针，指向一个空结束的字符串，该字符串指定要创建的目录的路径。);
	
	{
		printf("创建目录%s失败\n",szDirPath);
		return;
	}
	printf("创建目录%s成功\n",szDirPath);

}
//////////////////////////////////////////////////////////////////////////////////
//显示当前目录
void DisplayCatalogue()
{
	CHAR szCurrentDirectory[MAX_PATH];//用于储存当前路径，MAX_PATH是C语言运行时库中通过#define指令定义的一个宏常量，它定义了编译器所支持的最长全路径名的长度。
	DWORD dwCurDirPathlen;//当前路径的长度，也用于判断获取是否成功
	dwCurDirPathlen=GetCurrentDirectory(MAX_PATH,szCurrentDirectory);//获取当前路径
	//函数原型为
	//	DWORDGetCurrentDirectory(
	//		DWORDnBufferLength,// size of directory buffer 缓冲区的长度
	//		LPTSTRlpBuffer// directory buffer 指定一个预定义字串，用于装载当前目录
	//	);
	if(dwCurDirPathlen==0)
	{	
		printf("获取当前目录失误。\n");
		return;
	}
	printf("进程当前目录为%s\n",szCurrentDirectory);

}
////////////////////////////////////////////////////////////////////////////////////
//修改路径
void ChangeCatalog()
{
	CHAR szCurrentDirectory[MAX_PATH];//用于储存当前路径
	CHAR NewCurrentDirectory[MAX_PATH];
	DWORD dwCurDirPathlen;//当前路径的长度，也用于判断获取是否成功
	dwCurDirPathlen=GetCurrentDirectory(MAX_PATH,szCurrentDirectory);//获取当前路径
	printf("进程当前目录为%s\n",szCurrentDirectory);
	printf("输入新的路径");
	scanf("%s",NewCurrentDirectory);
	lstrcpy(szCurrentDirectory,NewCurrentDirectory);
	if(!SetCurrentDirectory(szCurrentDirectory))
	{
		printf("修改新路径失败");
		return ;
	}
	printf("修改后进程当前目录为%s\n",szCurrentDirectory);
	

}
////////////////////////////////////////////////////////////////////////////////
//显示目录结构
DWORD DisplayAllFileCatalogue(LPSTR szPath)
{
	CHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
//	WIN32_FIND_DATA结构描述了一个由FindFirstFile, FindFirstFileEx, 或FindNextFile函数查找到的文件信息，
//
//typedef struct _WIN32_FIND_DATA {
//
//　　 DWORD dwFileAttributes; //文件属性
//
//　　 FILETIME ftCreationTime; // 文件创建时间
//
//　　 FILETIME ftLastAccessTime; // 文件最后一次访问时间
//
//　　 FILETIME ftLastWriteTime; // 文件最后一次修改时间
//
//　　 DWORD nFileSizeHigh; // 文件长度高32位
//
//　　 DWORD nFileSizeLow; // 文件长度低32位
//
//　　 DWORD dwReserved0; // 系统保留
//
//　　 DWORD dwReserved1; // 系统保留
//
//　　 TCHAR cFileName[ MAX_PATH ]; // 长文件名
//
//　　 TCHAR cAlternateFileName[ 14 ]; // 8.3格式文件名
//
//} WIN32_FIND_DATA, *PWIN32_FIND_DATA;
	HANDLE hListFile; //定义句柄类型
	CHAR szFullPath[MAX_PATH];
	lstrcpy(szFilePath,szPath);
	lstrcat(szFilePath,"\\*");//该函数将字符串lpString2附加在另一个字符串lpString1后面。
	hListFile=FindFirstFile(szFilePath,&FindFileData);
	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("错误:%d",GetLastError());//取得上一个函数操作时所产生的错误代码并输出报错
		return 1;
	}
	else
	{
		do
		{
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0||lstrcmp(FindFileData.cFileName,TEXT(".."))==0)
			{//过滤本级目录和父级目录
				continue;
			}
			wsprintf(szFullPath,"%s\\%s",szPath,FindFileData.cFileName);
			dwTotalFileNum++;
			printf("\n%d\t%s\t",dwTotalFileNum,szFullPath);
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
				//判断目标文件的文件属性是否与文件夹属性一致，即判断该目标是否为文件夹
			{
				printf("<DIR>");
				DisplayAllFileCatalogue(szFullPath);
			}

		}
		while(FindNextFile(hListFile,&FindFileData));
	}
	return 0;
}

void DisplayAllCatalogue()
{
	int argc=1;
	if(argc==2)
	{
		DisplayAllFileCatalogue(NULL);
	}
	else
	{
		CHAR szCurrentPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,szCurrentPath);
		DisplayAllFileCatalogue(szCurrentPath);
	}
	printf("\n");

}
///////////////////////////////////////////////////////////////////////
//列目录
DWORD EnumerateFileInDrectory(LPSTR szPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	CHAR szFilePath[MAX_PATH];
	//构造代表子目录和文件夹路径的字符串，使用通配符"*"
	lstrcpy(szFilePath,szPath);
	lstrcat(szFilePath,"\\*");
	hListFile=FindFirstFile(szFilePath,&FindFileData);//查找第一个文件\目录，获得查找句柄
	//判断句柄
	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("错误:%d",GetLastError());
		return 1;
	}
	else
	{
		do
		{
			/*if(lstrcmp(FindFileData.cFileName,TEXT("."))==0||lstrcmp(FindFileData.cFileName,TEXT(".."))==0)
			{
			continue;
			}*/
			//打印文件名，目录名
			printf("   %s\t\t",FindFileData.cFileName);
			//判断文件属性，是否为加密文件或者文件夹
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_ENCRYPTED)
			{ 
				printf("<加密>");
			}
			//判断文件属性，是否为隐藏文件或者文件夹
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN);
			{
				printf("<隐藏>");
			}
			//判断文件属性，是否为目录
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY);
			{
				printf("<DIR>");
			}
			printf("\n");
		}
		while(FindNextFile(hListFile,&FindFileData));
	}
	return 0;
}

void DisplayFile()
{
	int argc=1;
	if(argc==2)
	{
		EnumerateFileInDrectory(NULL);
	}
	else
	{
		CHAR szCurrentPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,szCurrentPath);
		EnumerateFileInDrectory(szCurrentPath);
	}
	printf("\n");

}
///////////////////////////////////////////////////////////////////////
//删除文本文件
void MyDeleteFile()
{
	char str[20];
	CHAR szCurrentPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szCurrentPath);
	printf("请输入要删除文件名\n");
	scanf("%s",str);
	strcat(szCurrentPath,"\\");
	strcat(szCurrentPath,str); 
	if(!DeleteFile(szCurrentPath))
	printf("删除文件失败!");
	else
	printf("删除文件成功!");
}
/////////////////////////////////////////////////////////////////////////
//显示版本信息
void ShowVersion()
{
	printf("                 +++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("                 +   Mcrosoft Windows XP [版本2019.0.1]      +\n");
	printf("                 +                                           +\n");
	printf("                 +++++++++++++++++++++++++++++++++++++++++++++\n");
}
////////////////////////////////////////////////////////////////////////
//清屏功能
void ClearScreen()
{  

	system("cls");
}

//////////////////////////////////////////////////////////////////////////
//删除目录，也就是删除文件夹
void MyDeleteCatalogue()
{
	char str[20];
	CHAR szCurrentPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szCurrentPath);
	printf("请输入要删除目录名称\n");
	scanf("%s",str);
	strcat(szCurrentPath,"\\");
	strcat(szCurrentPath,str); 
	if(RemoveDirectory(szCurrentPath)==0)
	printf("删除目录%s失败!\n",szCurrentPath);
	else
	printf("删除目录%s成功!\n",szCurrentPath);
}
////////////////////////////////////////////////////////////////////////
//显示文本信息
void ShowFileMessage()
{
	FILE *fp;
	char str[20];
	char ch;
	printf("请输入要打开的文本名称:\n");
	scanf("%s",str);	
	if((fp=fopen(str,"rt"))==NULL) 
	{ 
		printf("\n打开文件失败%s!",str); 
		exit(1); 
	} 
	ch=fgetc(fp); 
	while(ch!=EOF) 
	{ 
		putchar(ch); 
		ch=fgetc(fp); 
	} 
	printf("\n");
	fclose(fp);

}
///////////////////////////////////////////////////////////////////////////
//打印文档
void PrintFile()
{
	char b[256];
	FILE *fp;
	fp = fopen("a.txt","wt+");
	printf("输入要打印的内容:");
	scanf("%s",b);
	fprintf(fp,b);
	fclose(fp);
	printf("打印文档内容%s成功!\n",b);
}
//////////////////////////////////////////////////////////////////////////
void RenameFile()  //对文件重命名
{
	char oldname[30],newname[30];
	int result;
	printf("请输入要修改的文件的名称:\n");
	scanf("%s",oldname);
	printf("请输入新的文件名称:\n");
	scanf("%s",newname);
	result= rename( oldname , newname );
	if ( result == 0 )
	puts ( "文件重命名成功!" );
	else
	perror( "文件重命名失败!" );
}
///////////////////////////////////////////////////////////////////////////
void Help()
{
	
	
	printf("\n*************************************************************************\n");
	printf("显示时间日期 ShowTime\n");
    printf("回显字符串 ReviewString\n");  
	printf("创建目录 CreateCatalogue\n");  
	printf("删除目录 DeleteCatalogue\n");  
	printf("显示当前目录 ShowCatalogue\n");  
	printf("更改路径 ChangePath\n");  
	printf("删除文件 DeleteFile\n");  
	printf("打印文本 PrintFile\n");  
	printf("文件重命名 FileRename\n");  
	printf("显示文本 ShowFile\n");  
	printf("显示版本 ShowVersion\n");  
    printf("显示目录结构 ShowCatalogueStructure\n");
    printf("清屏 ClearSrceen\n");
	printf("列目录 ShowCatalogue file\n");
	printf("帮助 Help\n");
	printf("退出 Esc\n");
	printf("*************************************************************************\n");

}
///////////////////////////////////////////////////////////////////////////

void  guide()
{
	char tr[10];
	printf("请输入help进入操作指南");
	scanf("%s",tr);
	if(stricmp(tr,"help")==0)
	Help();

}

///////////////////////////////////////////////////////////////////////////
void Esc() //退出
{
	exit(1);
}
////////////////////////////////////////////////////////////////////////////
//比较输入的字符串指令是否合法
void Command_interpreter()
{
	while(1)

	{
		char ch[30];
		printf("\n请输入相应的操作指令:");
		scanf("%s",ch);
		if(stricmp(ch,"ShowTime")==0)  GetTime();
		else if(stricmp(ch,"ReviewString")==0)  ReviewString();
		else if(stricmp(ch,"CreateCatalogue")==0)  CreateCatalogue();
		else if(stricmp(ch,"DeleteCatalogue")==0)  MyDeleteCatalogue();
		else if(stricmp(ch,"ShowCatalogue")==0)  DisplayCatalogue();
		else if(stricmp(ch,"ChangePath")==0)  ChangeCatalog();
		else if(stricmp(ch,"DeleteFile")==0)  MyDeleteFile();
		else if(stricmp(ch,"PrintFile")==0)  PrintFile();
		else if(stricmp(ch,"FileRename")==0)  RenameFile();
		else if(stricmp(ch,"ShowFile")==0)  ShowFileMessage();
		else if(stricmp(ch,"ShowVersion")==0)  ShowVersion();
		else if(stricmp(ch,"ShowCatalogueStructure")==0) DisplayAllCatalogue();
		else if(stricmp(ch,"ClearSrceen")==0)  {ClearScreen(); guide();}
		else if(stricmp(ch,"Esc")==0)  Esc();
		else if(stricmp(ch,"Help")==0)  Help();
		else if(stricmp(ch,"ShowCatalogueFile")==0)  DisplayFile();
		else  printf("无法识别的指令，请输入正确的指令!\n");
	}
}

///////////////////////////////////////////////////////////////////////////
//命令解释器

////////////////////////////////////////////////////////////////////////////
void main()
{   char ar[10];
	int i=0,j=3;
	char d[10];
	printf("\n                               欢迎进入此系统               \n");
	ShowVersion();
	printf("请输入cmd进入命令解释器:");
	scanf("%s",d);
	for(i=0;i<2;i++)
	{
		if(stricmp(d,"cmd")==0)
		{
			printf("\n请输入help了解操作指南:");
	        scanf("%s",ar);
	        if(stricmp(ar,"help")==0)
	        Help();
			Command_interpreter();
		}
		else
		{
			j=j-1;
			printf("你还有%d次机会!",j);
			printf("请输入cmd进入命令解释器:");
			scanf("%s",d);
		}
	}
	printf("连续输入错误，退出程序!");
}
