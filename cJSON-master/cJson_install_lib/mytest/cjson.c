#include <stdio.h>
#include "cJSON.h"
 
int main(int argc, char* argv[])
{
	cJSON *root	, *mes, *date_pack;
	char* out;

	root=cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "status", cJSON_CreateNumber(0));
	cJSON_AddItemToObject(root, "message", cJSON_CreateString(""));
	//
	date_pack = cJSON_CreateArray();
	//CJSON_CHK_FAIL(date_pack, NULL) ;
	cJSON_AddItemToObject(root, "date", date_pack);

	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);


	//char buf[1024] = {" {\"date\":\"20190829\"} "};//要解析的json数据

	//cJSON * root = cJSON_Parse(buf);//将字符串格式的json数据转化为JSON对象格式
	//if(root == NULL)
	//{
	//	printf("parse error\n");
	//	return -1;
	//}

	//cJSON *value = cJSON_GetObjectItem(root, "date");//根据键"date"获取其对应的值
	//if(value == NULL)
	//{
	//	printf("getvalue error\n");
	//	return -1;
	//}

	//char *data = cJSON_Print(value);//将获取值转化为字符串格式
	//if(data == NULL)
	//{
	//	printf("printf error\n");
	//	return -1;
	//}

	//printf("data=%s\n", data);//打印获取到的json数据
	//
	//return 0;
}

