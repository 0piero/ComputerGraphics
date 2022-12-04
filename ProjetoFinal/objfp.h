

#ifndef HEADER_OBJFP
#define HEADER_OBJFP
int read_args(char** argv, int argc, FILE** fp);
int parseOBJ(FILE* fp, List* vertex_list, List* face_list);

int read_args(char** argv, int argc, FILE** fp){
	for (int i = 1; i < argc; ++i){
		printf("--- Reading %s ---\n", argv[i]);
		if(i==1){
			*fp = fopen(argv[1], "r");
			if(*fp == NULL){
				printf("Error");   
				exit(1);             
			}
		}
	}
	return 0;
}
int parseOBJ(FILE* fp, List* vertex_list, List* face_list){
	char delim[] = " \t\n"; char face_delim[] = "/";
	char* v_cmp = "v"; char* f_cmp = "f";
	int ret;
	printf("--- Parsing ---\n");
	List* temp_list; listInit(&temp_list);
	while(1){
		size_t s;
		char* lineptr = NULL;
		ret = getline(&lineptr, &s, fp);

		if(ret==-1){printf("--- End Parsing ---\n"); break;}
		char* ptr = strtok(lineptr, delim);
		int idx = 0;
		
		if(!strcmp(ptr, v_cmp)){
			float** vtx = (float**) malloc(sizeof(float*)); *vtx = (float*) malloc(3*sizeof(float));
			while(1==1){
				//printf("%s\n", ptr);
				ptr = strtok(NULL, delim);
				if(ptr!=NULL){
					(*vtx)[idx] = (float) atof(ptr); idx++;
				}
				else{break;}
			}
			float color[3] = {0.0, 0.0, 0.0};
			listInsert(vertex_list, crtNode((void**) vtx, 0, color, 1.0), vertex_list->size);
		}
		else if(!strcmp(ptr, f_cmp)){
			char** PTN = (char**) malloc(3*sizeof(char*));
			int ptn_idx = 0;
			while(1==1){
				ptr = strtok(NULL, delim);
				int size=0;
				if(ptr!=NULL){
					PTN[ptn_idx] = ptr; ptn_idx++;
				}
				else{break;}
			}
			int** vtx = (int**) malloc(sizeof(int*)); *vtx = (int*) malloc(4*sizeof(int));
			for(int i=0;i<3;i++){
				char* ptn_ittem = PTN[i];
				//printf("%s\n", ptn_ittem);
				char* p_ptr = strtok(ptn_ittem, face_delim);
				//printf("point> %s\n", ptn_ittem);
				(*vtx)[i] = atoi(p_ptr);
			}
			free(PTN);
			float color[3] = {0.0, 0.0, 0.0};
			listInsert(temp_list, crtNode((void**) vtx, 0, color, 1.0), temp_list->size);
		}
	}
	float color[3] = {0.0, 0.0, 0.0};
	for(int i=0;i<temp_list->size;i++){
		Node* fc_idxs = listGetittem(temp_list, i);
		int* ptr_vtx_idx = *((int**)fc_idxs->points);
		Node* ptr_vtl;

		ptr_vtl = crtNode(listGetittem(vertex_list, ptr_vtx_idx[0]-1)->points, 0, color, 1.0);
		listInsert(face_list, ptr_vtl, face_list->size);
		ptr_vtl = crtNode(listGetittem(vertex_list, ptr_vtx_idx[1]-1)->points, 0, color, 1.0);
		listInsert(face_list, ptr_vtl, face_list->size);
		ptr_vtl = crtNode(listGetittem(vertex_list, ptr_vtx_idx[2]-1)->points, 0, color, 1.0);
		listInsert(face_list, ptr_vtl, face_list->size);
		//ptr_vtl = crtNode(listGetittem(vertex_list, ptr_vtx_idx[3]-1)->points, 0, color, 1.0);
		//listInsert(face_list, ptr_vtl, face_list->size);
	}

}
/*
int main(int argc, char** argv){
	listInit(&VList);
	listInit(&FList);
	FILE* OBJfp = (FILE*) malloc(sizeof(FILE));
	read_args(argv, argc, &OBJfp);
	parseOBJ(OBJfp, VList, FList);
	//for(int i=0;i<LIST_SIZE;i++){
	//	Node* nod = listGetittem(List, i);
	//	printf("vertex: %f %f %f\n", (*(nod->points))[0], (*(nod->points))[1], (*(nod->points))[2]);
	//}
	return 0;
}
*/
#endif