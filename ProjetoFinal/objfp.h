#ifndef HEADER_OBJFP
#define HEADER_OBJFP
int read_args(char** argv, int argc, FILE** fp);
int parseOBJ(FILE* fp,
	List* ABE_flist,
	List* ABD_flist,
	List* BD_flist,
	List* BE_flist,
	List* H_flist,
	List* MD_flist,
	List* ME_flist,
	List* OE_flist,
	List* OD_flist,
	List* JE_flist,
	List* JD_flist,
	List* PD_flist,
	List* PE_flist,
	List* QD_flist,
	List* QE_flist,
	List* T_flist,
	List* CE_flist,
	List* CD_flist);

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
size_t getline_(char **lineptr, size_t *n, FILE *stream) {
    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    c = getc(stream);
    if (c == EOF) {
        return -1;
    }

    if (*lineptr == NULL) {
        *lineptr = malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while(c != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n + (*n >> 2);
            if (new_size < 128) {
                new_size = 128;
            }
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos ++] = c;
        if (c == '\n') {
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}

void vtx_store(char* ptr, List* v_list){
	char delim[] = " \t\n";
	char* v_cmp = "v";
	int idx=0;
	if(!strcmp(ptr, v_cmp)){
		float** vtx = (float**) malloc(sizeof(float*)); *vtx = (float*) malloc(3*sizeof(float));
		while(1==1){

			ptr = strtok(NULL, delim);
			if(ptr!=NULL){
				(*vtx)[idx] = (float) atof(ptr); idx++;
			}
			else{break;}
		}
		float color[3] = {0.0, 0.0, 0.0};
		//printf("vtx %f %f %f\n", (*vtx)[0], (*vtx)[1], (*vtx)[2]);
		listInsert(v_list, crtNode((void**) vtx, 0, color, 1.0), v_list->size);
		
		Node* test = listGetittem(v_list, v_list->size-1);
		//printf("vtx %f %f %f\n", (*((float**)test->points))[0], (*((float**)test->points))[1], (*((float**)test->points))[2]);
	}
}

void f_idx_store(char* ptr, List* idx_list){
	char face_delim[] = "/";
	char delim[] = " \t\n";
	char** PTN = (char**) malloc(3*sizeof(char*));
	int ptn_idx = 0;
	while(1==1){
		ptr = strtok(NULL, delim);
		if(ptr!=NULL){
			PTN[ptn_idx] = ptr; ptn_idx++;
		}
		else{break;}
	}
	int** vtx = (int**) malloc(sizeof(int*)); *vtx = (int*) malloc(3*sizeof(int));
	for(int i=0;i<3;i++){
		char* ptn_ittem = PTN[i];
		char* p_ptr = strtok(ptn_ittem, face_delim);
		(*vtx)[i] = atoi(p_ptr);
	}
	free(PTN);
	float color[3] = {0.0, 0.0, 0.0};
	//printf("face %d %d %d\n", (*vtx)[0], (*vtx)[1], (*vtx)[2]);
	listInsert(idx_list, crtNode((void**) vtx, 0, color, 1.0), idx_list->size);


	//Node* test = listGetittem(idx_list, idx_list->size-1);
	//printf("face %d %d %d\n", (*((int**)test->points))[0], (*((int**)test->points))[1], (*((int**)test->points))[2]);


}

void map_faces(List* idx_list, List* f_list, List* v_list){
	float color[3] = {0.0, 0.0, 0.0};

	for(int i=0;i<idx_list->size;i++){
		
		Node* fc_idxs = listGetittem(idx_list, i);
		int* ptr_vtx_idx = *((int**)fc_idxs->points);
		Node* ptr_vtl;

		//printf("map %d %d %d\n", ptr_vtx_idx[0], ptr_vtx_idx[1], ptr_vtx_idx[2]);
		ptr_vtl = crtNode(listGetittem(v_list, ptr_vtx_idx[0]-1)->points, 0, color, 1.0);
		listInsert(f_list, ptr_vtl, f_list->size);

		ptr_vtl = crtNode(listGetittem(v_list, ptr_vtx_idx[1]-1)->points, 0, color, 1.0);
		listInsert(f_list, ptr_vtl, f_list->size);

		ptr_vtl = crtNode(listGetittem(v_list, ptr_vtx_idx[2]-1)->points, 0, color, 1.0);
		listInsert(f_list, ptr_vtl, f_list->size);


	}
	//listClear(v_list);
	listClear(idx_list);
}

int parseOBJ(
	FILE* fp,
	List* ABE_flist,
	List* ABD_flist,
	List* BD_flist,
	List* BE_flist,
	List* H_flist,
	List* MD_flist,
	List* ME_flist,
	List* OE_flist,
	List* OD_flist,
	List* JE_flist,
	List* JD_flist,
	List* PD_flist,
	List* PE_flist,
	List* QD_flist,
	List* QE_flist,
	List* T_flist,
	List* CE_flist,
	List* CD_flist){

	List* vertex_list;
	List* face_list;
	listInit(&vertex_list); listInit(&face_list);
	char delim[] = " \t\n"; char face_delim[] = "/";
	char* v_cmp = "v"; char* f_cmp = "f"; char* o_cmp = "o";
	int ret;
	printf("--- Parsing ---\n");
	List* temp_list; listInit(&temp_list);
	while(1){
		size_t s;
		char* lineptr = NULL;
		ret = getline_(&lineptr, &s, fp);

		if(ret==-1){printf("--- End Parsing ---\n"); break;}
		char* ptr = strtok(lineptr, delim);

		if(!strcmp(ptr, "o")){

			map_faces(temp_list, face_list, vertex_list);

			ptr = strtok(NULL, delim);
			char* body_part = strtok(ptr, "_");
			//printf("%s\n", body_part);
			if(!strcmp(body_part, "ABE")){face_list = ABE_flist ;}
			else if(!strcmp(body_part, "ABD")){face_list = ABD_flist ;}
			else if(!strcmp(body_part, "BD")){face_list = BD_flist ;}
			else if(!strcmp(body_part, "BE")){face_list = BE_flist ;}
			else if(!strcmp(body_part, "MD")){face_list = MD_flist ;}
			else if(!strcmp(body_part, "ME")){face_list = ME_flist ;}
			else if(!strcmp(body_part, "OE")){face_list = OE_flist ;}	
			else if(!strcmp(body_part, "OD")){face_list = OD_flist ;}
			else if(!strcmp(body_part, "JE")){face_list = JE_flist ;}
			else if(!strcmp(body_part, "JD")){face_list = JD_flist ;}
			else if(!strcmp(body_part, "PD")){face_list = PD_flist ;}
			else if(!strcmp(body_part, "PE")){face_list = PE_flist ;}
			else if(!strcmp(body_part, "QE")){face_list = QE_flist ;}
			else if(!strcmp(body_part, "QD")){face_list = QD_flist ;}
			else if(!strcmp(body_part, "T")){face_list = T_flist ;}
			else if(!strcmp(body_part, "H")){face_list = H_flist ;}
			else if(!strcmp(body_part, "CE")){face_list = CE_flist ;}
			else if(!strcmp(body_part, "CD")){face_list = CD_flist ;}

		}

		if(!strcmp(ptr, v_cmp)){
			vtx_store(ptr, vertex_list);
		}

		else if(!strcmp(ptr, f_cmp)){
			f_idx_store(ptr, temp_list);
		}
	}

	map_faces(temp_list, face_list, vertex_list);
	listClear(vertex_list);

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