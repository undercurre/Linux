#include<windows.h>
#include <time.h>
#include<string.h>
#include<stdio.h>

DWORD dwTotalFileNum=0;
//////////////////////////////////////////////////////////
//��ȡϵͳʱ��
void GetTime()
{
	int sec, min, hour, MonthDay, month, year, WeekDay;//��������
	struct tm * timeptr;
	//struct tm {                //ʱ�ӽṹ
	//int tm_sec;         /* �룬��Χ�� 0 �� 59        */
	//int tm_min;         /* �֣���Χ�� 0 �� 59        */
	//int tm_hour;        /* Сʱ����Χ�� 0 �� 23        */
	//int tm_mday;        /* һ���еĵڼ��죬��Χ�� 1 �� 31    */
	//int tm_mon;         /* �£���Χ�� 0 �� 11        */
	//int tm_year;        /* �� 1900 ���������        */
	//int tm_wday;        /* һ���еĵڼ��죬��Χ�� 0 �� 6    */
	//int tm_yday;        /* һ���еĵڼ��죬��Χ�� 0 �� 365    */
	//int tm_isdst;       /* ����ʱ                */
    //};
	char weekdayString[10];
	time_t calendar;   //����ʱ����
	time(&calendar);//��ȡϵͳʱ��  &�����ҷ��� time�������㵱ǰ����ʱ��
	timeptr = localtime(&calendar);//ת��Ϊ����ʱ�� location������ʱ����Ϊ����ʱ����ת��Ϊʱ�ӽṹ
	year = timeptr->tm_year;//ʱ�ӽṹ�帳ֵ��ֵ����Ӧ����
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
//�����ַ���
void ReviewString()
{
	char a[100];
	printf("�������ַ���\n");
	scanf("%s",a);
	printf("%s\n",a);
}
////////////////////////////////////////////////////////////////////////////////////
//����Ŀ¼
void CreateCatalogue()
{
	char a[30]; //�ڵ�ǰĿ¼�´�����Ŀ¼
	LPSTR szDirPath;  //ע���ٴ��½���ʱ������֮ǰ�Ѿ��ɹ��½����ͻ���ʾ����ʧ�� LPSTR��Win32��VC++��ʹ�õ�һ���ַ�����������
	printf("������Ҫ����Ŀ¼������:\n");
	scanf("%s",a);
	szDirPath=a;
	if(!CreateDirectory(szDirPath,NULL))
			//����ԭ�ͣ�
				//BOOL CreateDirectory(
				//	LPCWSTR lpPathName,
				//	LPSECURITY_ATTRIBUTES lpSecurityAttributes
				// pPathName����ָ�룬ָ��һ���ս������ַ��������ַ���ָ��Ҫ������Ŀ¼��·����);
	
	{
		printf("����Ŀ¼%sʧ��\n",szDirPath);
		return;
	}
	printf("����Ŀ¼%s�ɹ�\n",szDirPath);

}
//////////////////////////////////////////////////////////////////////////////////
//��ʾ��ǰĿ¼
void DisplayCatalogue()
{
	CHAR szCurrentDirectory[MAX_PATH];//���ڴ��浱ǰ·����MAX_PATH��C��������ʱ����ͨ��#defineָ����һ���곣�����������˱�������֧�ֵ��ȫ·�����ĳ��ȡ�
	DWORD dwCurDirPathlen;//��ǰ·���ĳ��ȣ�Ҳ�����жϻ�ȡ�Ƿ�ɹ�
	dwCurDirPathlen=GetCurrentDirectory(MAX_PATH,szCurrentDirectory);//��ȡ��ǰ·��
	//����ԭ��Ϊ
	//	DWORDGetCurrentDirectory(
	//		DWORDnBufferLength,// size of directory buffer �������ĳ���
	//		LPTSTRlpBuffer// directory buffer ָ��һ��Ԥ�����ִ�������װ�ص�ǰĿ¼
	//	);
	if(dwCurDirPathlen==0)
	{	
		printf("��ȡ��ǰĿ¼ʧ��\n");
		return;
	}
	printf("���̵�ǰĿ¼Ϊ%s\n",szCurrentDirectory);

}
////////////////////////////////////////////////////////////////////////////////////
//�޸�·��
void ChangeCatalog()
{
	CHAR szCurrentDirectory[MAX_PATH];//���ڴ��浱ǰ·��
	CHAR NewCurrentDirectory[MAX_PATH];
	DWORD dwCurDirPathlen;//��ǰ·���ĳ��ȣ�Ҳ�����жϻ�ȡ�Ƿ�ɹ�
	dwCurDirPathlen=GetCurrentDirectory(MAX_PATH,szCurrentDirectory);//��ȡ��ǰ·��
	printf("���̵�ǰĿ¼Ϊ%s\n",szCurrentDirectory);
	printf("�����µ�·��");
	scanf("%s",NewCurrentDirectory);
	lstrcpy(szCurrentDirectory,NewCurrentDirectory);
	if(!SetCurrentDirectory(szCurrentDirectory))
	{
		printf("�޸���·��ʧ��");
		return ;
	}
	printf("�޸ĺ���̵�ǰĿ¼Ϊ%s\n",szCurrentDirectory);
	

}
////////////////////////////////////////////////////////////////////////////////
//��ʾĿ¼�ṹ
DWORD DisplayAllFileCatalogue(LPSTR szPath)
{
	CHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
//	WIN32_FIND_DATA�ṹ������һ����FindFirstFile, FindFirstFileEx, ��FindNextFile�������ҵ����ļ���Ϣ��
//
//typedef struct _WIN32_FIND_DATA {
//
//���� DWORD dwFileAttributes; //�ļ�����
//
//���� FILETIME ftCreationTime; // �ļ�����ʱ��
//
//���� FILETIME ftLastAccessTime; // �ļ����һ�η���ʱ��
//
//���� FILETIME ftLastWriteTime; // �ļ����һ���޸�ʱ��
//
//���� DWORD nFileSizeHigh; // �ļ����ȸ�32λ
//
//���� DWORD nFileSizeLow; // �ļ����ȵ�32λ
//
//���� DWORD dwReserved0; // ϵͳ����
//
//���� DWORD dwReserved1; // ϵͳ����
//
//���� TCHAR cFileName[ MAX_PATH ]; // ���ļ���
//
//���� TCHAR cAlternateFileName[ 14 ]; // 8.3��ʽ�ļ���
//
//} WIN32_FIND_DATA, *PWIN32_FIND_DATA;
	HANDLE hListFile; //����������
	CHAR szFullPath[MAX_PATH];
	lstrcpy(szFilePath,szPath);
	lstrcat(szFilePath,"\\*");//�ú������ַ���lpString2��������һ���ַ���lpString1���档
	hListFile=FindFirstFile(szFilePath,&FindFileData);
	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("����:%d",GetLastError());//ȡ����һ����������ʱ�������Ĵ�����벢�������
		return 1;
	}
	else
	{
		do
		{
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0||lstrcmp(FindFileData.cFileName,TEXT(".."))==0)
			{//���˱���Ŀ¼�͸���Ŀ¼
				continue;
			}
			wsprintf(szFullPath,"%s\\%s",szPath,FindFileData.cFileName);
			dwTotalFileNum++;
			printf("\n%d\t%s\t",dwTotalFileNum,szFullPath);
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
				//�ж�Ŀ���ļ����ļ������Ƿ����ļ�������һ�£����жϸ�Ŀ���Ƿ�Ϊ�ļ���
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
//��Ŀ¼
DWORD EnumerateFileInDrectory(LPSTR szPath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;
	CHAR szFilePath[MAX_PATH];
	//���������Ŀ¼���ļ���·�����ַ�����ʹ��ͨ���"*"
	lstrcpy(szFilePath,szPath);
	lstrcat(szFilePath,"\\*");
	hListFile=FindFirstFile(szFilePath,&FindFileData);//���ҵ�һ���ļ�\Ŀ¼����ò��Ҿ��
	//�жϾ��
	if(hListFile==INVALID_HANDLE_VALUE)
	{
		printf("����:%d",GetLastError());
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
			//��ӡ�ļ�����Ŀ¼��
			printf("   %s\t\t",FindFileData.cFileName);
			//�ж��ļ����ԣ��Ƿ�Ϊ�����ļ������ļ���
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_ENCRYPTED)
			{ 
				printf("<����>");
			}
			//�ж��ļ����ԣ��Ƿ�Ϊ�����ļ������ļ���
			if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN);
			{
				printf("<����>");
			}
			//�ж��ļ����ԣ��Ƿ�ΪĿ¼
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
//ɾ���ı��ļ�
void MyDeleteFile()
{
	char str[20];
	CHAR szCurrentPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szCurrentPath);
	printf("������Ҫɾ���ļ���\n");
	scanf("%s",str);
	strcat(szCurrentPath,"\\");
	strcat(szCurrentPath,str); 
	if(!DeleteFile(szCurrentPath))
	printf("ɾ���ļ�ʧ��!");
	else
	printf("ɾ���ļ��ɹ�!");
}
/////////////////////////////////////////////////////////////////////////
//��ʾ�汾��Ϣ
void ShowVersion()
{
	printf("                 +++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("                 +   Mcrosoft Windows XP [�汾2019.0.1]      +\n");
	printf("                 +                                           +\n");
	printf("                 +++++++++++++++++++++++++++++++++++++++++++++\n");
}
////////////////////////////////////////////////////////////////////////
//��������
void ClearScreen()
{  

	system("cls");
}

//////////////////////////////////////////////////////////////////////////
//ɾ��Ŀ¼��Ҳ����ɾ���ļ���
void MyDeleteCatalogue()
{
	char str[20];
	CHAR szCurrentPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szCurrentPath);
	printf("������Ҫɾ��Ŀ¼����\n");
	scanf("%s",str);
	strcat(szCurrentPath,"\\");
	strcat(szCurrentPath,str); 
	if(RemoveDirectory(szCurrentPath)==0)
	printf("ɾ��Ŀ¼%sʧ��!\n",szCurrentPath);
	else
	printf("ɾ��Ŀ¼%s�ɹ�!\n",szCurrentPath);
}
////////////////////////////////////////////////////////////////////////
//��ʾ�ı���Ϣ
void ShowFileMessage()
{
	FILE *fp;
	char str[20];
	char ch;
	printf("������Ҫ�򿪵��ı�����:\n");
	scanf("%s",str);	
	if((fp=fopen(str,"rt"))==NULL) 
	{ 
		printf("\n���ļ�ʧ��%s!",str); 
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
//��ӡ�ĵ�
void PrintFile()
{
	char b[256];
	FILE *fp;
	fp = fopen("a.txt","wt+");
	printf("����Ҫ��ӡ������:");
	scanf("%s",b);
	fprintf(fp,b);
	fclose(fp);
	printf("��ӡ�ĵ�����%s�ɹ�!\n",b);
}
//////////////////////////////////////////////////////////////////////////
void RenameFile()  //���ļ�������
{
	char oldname[30],newname[30];
	int result;
	printf("������Ҫ�޸ĵ��ļ�������:\n");
	scanf("%s",oldname);
	printf("�������µ��ļ�����:\n");
	scanf("%s",newname);
	result= rename( oldname , newname );
	if ( result == 0 )
	puts ( "�ļ��������ɹ�!" );
	else
	perror( "�ļ�������ʧ��!" );
}
///////////////////////////////////////////////////////////////////////////
void Help()
{
	
	
	printf("\n*************************************************************************\n");
	printf("��ʾʱ������ ShowTime\n");
    printf("�����ַ��� ReviewString\n");  
	printf("����Ŀ¼ CreateCatalogue\n");  
	printf("ɾ��Ŀ¼ DeleteCatalogue\n");  
	printf("��ʾ��ǰĿ¼ ShowCatalogue\n");  
	printf("����·�� ChangePath\n");  
	printf("ɾ���ļ� DeleteFile\n");  
	printf("��ӡ�ı� PrintFile\n");  
	printf("�ļ������� FileRename\n");  
	printf("��ʾ�ı� ShowFile\n");  
	printf("��ʾ�汾 ShowVersion\n");  
    printf("��ʾĿ¼�ṹ ShowCatalogueStructure\n");
    printf("���� ClearSrceen\n");
	printf("��Ŀ¼ ShowCatalogue file\n");
	printf("���� Help\n");
	printf("�˳� Esc\n");
	printf("*************************************************************************\n");

}
///////////////////////////////////////////////////////////////////////////

void  guide()
{
	char tr[10];
	printf("������help�������ָ��");
	scanf("%s",tr);
	if(stricmp(tr,"help")==0)
	Help();

}

///////////////////////////////////////////////////////////////////////////
void Esc() //�˳�
{
	exit(1);
}
////////////////////////////////////////////////////////////////////////////
//�Ƚ�������ַ���ָ���Ƿ�Ϸ�
void Command_interpreter()
{
	while(1)

	{
		char ch[30];
		printf("\n��������Ӧ�Ĳ���ָ��:");
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
		else  printf("�޷�ʶ���ָ���������ȷ��ָ��!\n");
	}
}

///////////////////////////////////////////////////////////////////////////
//���������

////////////////////////////////////////////////////////////////////////////
void main()
{   char ar[10];
	int i=0,j=3;
	char d[10];
	printf("\n                               ��ӭ�����ϵͳ               \n");
	ShowVersion();
	printf("������cmd�������������:");
	scanf("%s",d);
	for(i=0;i<2;i++)
	{
		if(stricmp(d,"cmd")==0)
		{
			printf("\n������help�˽����ָ��:");
	        scanf("%s",ar);
	        if(stricmp(ar,"help")==0)
	        Help();
			Command_interpreter();
		}
		else
		{
			j=j-1;
			printf("�㻹��%d�λ���!",j);
			printf("������cmd�������������:");
			scanf("%s",d);
		}
	}
	printf("������������˳�����!");
}
