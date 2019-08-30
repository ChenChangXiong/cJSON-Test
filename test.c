#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

char* out ;

struct date_buf {
	char* supplierCode ;
	char* workOrderCode ;
	char* testCode ;
	char* plantCode ;
	char* deviceCode ;
	char* checkTime ;
	char* allowableError ;
	char*  realError ;
	char* conclusion ;
} ;
//报文数据
struct post_buf {
	char* supplierCode ;
	char* salesOrderCode;
	char* salesOrderProjectNo ;
	char* materialsNum ;
	char* deliveryDate ;
	char* deliveryPlace ;
	char* sgFrameworkCode ;
	char* sgPurchaseOrder ;
	char* sgPurchaseOrderProjectNo ;
	char* sgProjectName ;
	char* sgEntityId ;
} ;
//请求报文
struct request_buf{
	char* deviceNo ;
	char* points ;
	char* startTime ;
	char* endTime ;
};
/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
	cJSON *json;
	
	json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);
		cJSON_Delete(json);
		printf("%s\n",out);
		free(out);
	}
}

/* Read a file, parse, render back, etc. */
void dofile(char *filename)
{
	FILE *f;long len;char *data;
	
	f=fopen(filename,"rb");fseek(f,0,SEEK_END);len=ftell(f);fseek(f,0,SEEK_SET);
	data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
	doit(data);
	free(data);
}
char* status_message(void)
{
	cJSON *root	, *fld, *date_pack;
	char i ;
	
	struct date_buf  fields[2]={
		{"GYS414432", "GDH-4234234", "NYSJ-001", "CNBH-23423", "JCX-342342", "2019-08-29 15:33:22", "±0.5s/d", "±0.4s/d", "0"},
		{"GYS414432", "GDH-4234234", "NYSJ-002", "CNBH-23423", "JCX-342342", "2019-08-29 15:35:22", "±0.5s/d", "±0.5s/d", "1"},
	};
	root=cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "status",cJSON_CreateNumber(0));
	cJSON_AddItemToObject(root, "message",cJSON_CreateString(""));
	//
	date_pack = cJSON_CreateArray();
	cJSON_AddItemToObject(root, "date", date_pack);
	
	for (i=0;i<2;i++)
	{
		cJSON_AddItemToArray(date_pack, fld=cJSON_CreateObject());
		cJSON_AddStringToObject(fld, "supplierCode", fields[i].supplierCode);
		cJSON_AddStringToObject(fld, "workOrderCode", fields[i].workOrderCode);
		cJSON_AddStringToObject(fld, "testCode", fields[i].testCode);
		cJSON_AddStringToObject(fld, "plantCode", fields[i].plantCode);
		cJSON_AddStringToObject(fld, "deviceCode", fields[i].deviceCode);
		cJSON_AddStringToObject(fld, "checkTime", fields[i].checkTime);
		cJSON_AddStringToObject(fld, "allowableError", fields[i].allowableError);
		cJSON_AddStringToObject(fld, "realError", fields[i].realError);
		cJSON_AddStringToObject(fld, "conclusion", fields[i].conclusion);
	}
	
	out=cJSON_Print(root);	cJSON_Delete(root);	free(out);	/* Delete the cJSON, print it, release the string.*/
	return out ;
}

char* post_message(void)
{
	cJSON *root,  *fld, *body, *dat;

	struct post_buf post_pack = {"GYS414432", "2019060002", "1", "3000", "2019-09-01", "企业浙江分公司", "0711-32353CA010201", \
	                              "SD-WZ-(2019)050616号", "1", "企业XXX项目", "00001"} ;

	root=cJSON_CreateObject();	
	///header
	cJSON_AddItemToObject(root, "header", fld=cJSON_CreateObject());
	cJSON_AddStringToObject(fld, "orisys", "0");
	cJSON_AddStringToObject(fld, "operatetyoe", "add");
	//body
	cJSON_AddItemToObject(root, "body", body=cJSON_CreateObject());
	cJSON_AddItemToObject(body, "date", dat=cJSON_CreateObject());

	cJSON_AddStringToObject(dat, "supplierCode", post_pack.supplierCode);
	cJSON_AddStringToObject(dat, "salesOrderCode", post_pack.salesOrderCode);
	cJSON_AddStringToObject(dat, "salesOrderProjectNo", post_pack.salesOrderProjectNo);
	cJSON_AddStringToObject(dat, "materialsNum", post_pack.materialsNum);
	cJSON_AddStringToObject(dat, "deliveryDate", post_pack.deliveryDate);
	cJSON_AddStringToObject(dat, "deliveryPlace", post_pack.deliveryPlace);
	cJSON_AddStringToObject(dat, "sgFrameworkCode", post_pack.sgFrameworkCode);
	cJSON_AddStringToObject(dat, "sgPurchaseOrder", post_pack.sgPurchaseOrder);
	cJSON_AddStringToObject(dat, "sgPurchaseOrderProjectNo", post_pack.sgPurchaseOrderProjectNo);
	cJSON_AddStringToObject(dat, "sgProjectName", post_pack.sgProjectName);
	cJSON_AddStringToObject(dat, "sgEntityId", post_pack.sgEntityId);
	
	out=cJSON_Print(root);	cJSON_Delete(root);	free(out);	/* Delete the cJSON, print it, release the string.*/
	return out ;
}
int main (int argc, char * argv[])
 {
	//printf("\n %s \n", status_message()) ;
	//printf("%s \n", post_message()) ;
	

	return 0;
}


void  analysis_pack(void)
{
	cJSON *root, *get, *date, *ArrayNode ;

    root = cJSON_Parse(status_message()) ;
	get = cJSON_GetObjectItem(root, "message");
	printf("Get age value : %s\n", get->valuestring);
    //get Array
	date = cJSON_GetObjectItem(root, "date");
	int size = cJSON_GetArraySize(date);
	printf("size = %d\n", size) ;

	ArrayNode = cJSON_GetArrayItem(date, 0) ; //获取第一个数组
	get = cJSON_GetObjectItem(ArrayNode,  "supplierCode");

	printf("Get age supplierCode : %s\n", get->valuestring);

}
