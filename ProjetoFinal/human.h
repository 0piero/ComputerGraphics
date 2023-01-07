#ifndef LHT_HEADER
#define LHT_HEADER
List* ABE_flist;
List* ABD_flist;
List* BD_flist;
List* BE_flist;
List* H_flist;
List* MD_flist;
List* ME_flist;
List* OE_flist;
List* OD_flist;
List* JE_flist;
List* JD_flist;
List* PD_flist;
List* PE_flist;
List* QD_flist;
List* QE_flist;
List* T_flist;
List* CE_flist;
List* CD_flist;
float V2E_ref[] = {-2.583185, -1.309285, -0.063695};
float V2D_ref[] = {2.586259, -1.309285, -0.063695};
float V1E_ref[] = {-0.902937, -1.167153, -0.021232};
float V1D_ref[] = {0.906011, -1.167153, -0.021232};
float V3E_ref[] = {-4.002482, -1.378129, 0.014796};
float V3D_ref[] = {4.005557, -1.378129, 0.014796};
float P1E_ref[] = {0.609648, -4.297810, 0.000000};
float P1D_ref[] = {-0.606574, -4.297810, 0.000000};
float P2E_ref[] = {0.522193, -6.688396, 0.000000};
float P2D_ref[] = {-0.519119, -6.688396, 0.000000};
float P3D_ref[] = {0.521860, -9.103373, 0.000000};
float P3E_ref[] = {-0.518786, -9.103373, 0.000000};
float C_ref[] = {0.019854, -0.867079, -0.076779};
float* ref_joints[] = {V1E_ref, V1D_ref,V2E_ref,V2D_ref,V3E_ref,V3D_ref,P1E_ref,P1D_ref,P2E_ref,P2D_ref,P3E_ref,P3D_ref,C_ref};

struct Human{
	List** parts;
	int num_parts;
};
typedef struct Human Human;
Human human;

void setParts(Human* h){
	h->parts = (List**)malloc(18 * sizeof(List*));
	(h->parts)[0] = ABE_flist;
	(h->parts)[1] = ABD_flist;
	(h->parts)[2] = BD_flist;
	(h->parts)[3] = BE_flist;
	(h->parts)[4] = H_flist;
	(h->parts)[5] = MD_flist;
	(h->parts)[6] = ME_flist;
	(h->parts)[7] = OE_flist;
	(h->parts)[8] = OD_flist;
	(h->parts)[9] = JE_flist;
	(h->parts)[10] = JD_flist;
	(h->parts)[11] = PD_flist;
	(h->parts)[12] = PE_flist;
	(h->parts)[13] = QD_flist;
	(h->parts)[14] = QE_flist;
	(h->parts)[15] = T_flist;
	(h->parts)[16] = CE_flist;
	(h->parts)[17] = CD_flist;
	h->num_parts = 18;
}



#endif