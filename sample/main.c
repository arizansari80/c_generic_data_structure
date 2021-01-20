/*
 * main.c
 *
 *  Created on: 20-Dec-2019
 *      Author: arizansari80
 */
#include "main.h"

/*
    STRING_SET initialize_set(STRING_SET,NULL,NULL);
    MODIFIED_STRING_SET initialize_set(STRING_SET,YourComparatorFunction,YourDisplayFunction);
    DEFAULT_SET is INTEGER SET
    DEFAULT_SET initialize_set(DEFAULT_SET,NULL,NULL);
*/
typedef struct points
{
    int x;
    int y;
} points;

long double points_compare(const void *P1, const void *P2)
{
    points p1 = *(points *)P1;
    points p2 = *(points *)P2;
    if (p1.x == p2.x)
        return p1.y - p2.y;
    return p1.x - p2.x;
}

void points_display(const void *P)
{
    points p = *(points *)P;
    printf("(%d,%d)", p.x, p.y);
}

long double key_compare(const void *P1, const void *P2)
{
    return strcmp(P1,P2);
}

long double value_compare(const void *P1, const void *P2)
{
    return *(int *)P1 - *(int *)P2;
}

void map_display(const void *key,const void *value)
{
    printf("\n\t(key : %s | value : %f)",STRINGAT(key),FLOATAT(value));
    //printf("\n\t(key : %f | value : %s)",FLOATAT(key),STRINGAT(value));
}

//int main()
//{
//    set intSet, intSet1;
//    long message;
//    int myArr[] = {34, 25, 68, 90, 12, 34, 56, 78, 25, 90, 34};
//    int myArr1[] = {64, 36, 56, 17, 78, 97, 34, 36, 17, 78, 64};
//
//    int size = sizeof(myArr) / sizeof(myArr[0]);
//    int i = 0;
//    intSet = Set.getSet(DEFAULT_SET, NULL, NULL);
//    intSet1 = Set.getSet(DEFAULT_SET, NULL, NULL);
//    for (; i < size; i++)
//        Set.addInSet(&intSet, &myArr[i]);
//    i = 0;
//    size = sizeof(myArr1) / sizeof(myArr1[0]);
//    for (; i < size; i++)
//        Set.addInSet(&intSet1, &myArr1[i]);
//
//    printf("\nSet 1 is\n");
//    Set.printSet(intSet);
//    printf("\nSet 2 is\n");
//    Set.printSet(intSet1);
//
//    set unionSet, intersectSet, diffSet;
//
//    unionSet = Set.setUnion(intSet, intSet1, &message);
//    intersectSet = Set.setIntersection(intSet, intSet1, &message);
//    diffSet = Set.setDifference(intSet, intSet1, &message);
//
//    printf("\nSet 1 Union pset 2is\n");
//    Set.printSet(unionSet);
//    printf("\nSet 1 Intersection pset 2 is\n");
//    Set.printSet(intersectSet);
//    printf("\nSet 1 Difference pset 2 is\n");
//    Set.printSet(diffSet);
//    return 0;
//}
//int main(int argc, char *args[])
//{
//	set intSet,intSet1;
//    long message;
//    int myArr[] = {8, 6, 2, 1, 4, 3, 5, 7, 10, 12, 9, 13, 11};
//
//    int size = sizeof(myArr) / sizeof(myArr[0]);
//    int z = 100;
//    int i = 0;
//    intSet = Set.getSet(DEFAULT_SET, NULL, NULL);
//    for (; i < size; i++)
//        Set.addInSet(&intSet, &myArr[i]);
//	Set.printSet(intSet);
//	set_iterator iter = Set.getIterator(&intSet);
//	while (iter != NULL)
//	{
//		printf("%d\n",*(int *)(iter->data));
//		free(iter);
//		iter = Set.nextIterator(&intSet);
//	}
//    Set.printSet(intSet);
//
//    int myArr1[] = {64, 36, 56, 17, 78, 97, 34, 36, 17, 78, 64};
//    i = 0;
//    size = sizeof(myArr1) / sizeof(myArr1[0]);
//    intSet1 = Set.getSet(DEFAULT_SET, NULL, NULL);
//    for (; i < size; i++)
//        Set.addInSet(&intSet1, &myArr1[i]);
//    Set.printSet(intSet1);
//    free(iter);
//	iter = Set.getIterator(&intSet1);
//	while (iter != NULL)
//	{
//		printf("%d\n",*(int *)(iter->data));
//		free(iter);
//		iter = Set.nextIterator(&intSet1);
//	}
//
//	return 0;
//}
//
//    //int delElem;
//
//    /*i = 0;
//    for (; i < 5; i++) {
//        printf("Enter Number to be deleted from Set1 ");
//        scanf("%d",&delElem);
//        bool b = intSet.DeleteInSet(&intSet,&delElem);
//        if (b) {
//            printf("Element %d is deleted successfully and Modified pset After Operation is \n",delElem);
//            intSet.print_set(intSet);
//        }
//        else
//            printf("Element %d Not Found in pset 1\n",delElem);
//        printf("Number of Element in pset 1 is %d\n",intSet.ctr);
//    }*/
//
//    printf("\n\n\nCo-Ordinate Example Begins\n\n\n");
//    set pset1, pset2;
//    pset1 = initialize_set(sizeof(points), points_compare, points_display);
//    pset2 = initialize_set(sizeof(points), points_compare, points_display);
//
//    points parr1[] = {{5, 8}, {6, 9}, {5, 4}, {8, 3}, {7, 2}, {7, 9}, {5, 8}, {4, 9}, {9, 5}, {3, 9}, {4, 8}};
//    points parr2[] = {{8, 3}, {4, 4}, {2, 6}, {7, 2}, {1, 7}, {3, 5}, {7, 9}, {3, 7}, {2, 6}, {3, 5}, {5, 8}};
//    i = 0;
//    size = sizeof(parr1) / sizeof(parr1[0]);
//    for (; i < size; i++)
//        add_in_set(&pset1, &parr1[i]);
//
//    size = sizeof(parr2) / sizeof(parr2[0]);
//    i = 0;
//    for (; i < size; i++)
//        add_in_set(&pset2, &parr2[i]);
//
//    print_set(pset1);
//    print_set(pset2);
//
//    unionSet = set_union(pset1, pset2, &message);
//    intersectSet = set_intersection(pset1, pset2, &message);
//    diffSet = set_difference(pset1, pset2, &message);
//
//    printf("\nSet 1 Union pset 2is\n");
//    print_set(unionSet);
//    printf("\nSet 1 Intersection pset 2 is\n");
//    print_set(intersectSet);
//    printf("\nSet 1 Difference pset 2 is\n");
//    print_set(diffSet);
//
//    printf("\n\n\nDefault String pset Example Begins\n\n\n");
//    set stringSet;
//    stringSet = initialize_set(STRING_SET, NULL, NULL);
//
//    char *ch[12] = {"this", "is", "my", "test", "My", "test", "new", "TesT", "function", "set", "obj", "Obj"};
//    size = 12;
//    i = 0;
//    for (; i < size; i++)
//        add_in_set(&stringSet, (void *)ch[i]);
//
//    print_set(stringSet);
//
//    printf("\n\n\nModified String pset Example Begins\n\n\n");
//    stringSet = initialize_set(MODIFIED_STRING_SET, string_compare, string_display);
//    size = 12;
//    i = 0;
//    for (; i < size; i++)
//        add_in_set(&stringSet, (void *)ch[i]);
//
//    print_set(stringSet);
//    return 0;
//}




//extern GLOBAL_MAP_OBJECT Map;
//
//int main()
//{
//    char *key[] = {"Ariz","Ansari","Muhammad","ariz","ansari","muhammad"};
//    float value[] = {10.067,20.0836,10.067,40.9573,10.067,60.0584};
//    map mymap = Map.getMap(STRING_CASE_INSENSITIVE_KEY,FLOAT_VALUE,NULL,NULL,map_display);
//    int i = 0;
//    char *name;
//    int rollno;
//    for (; i < 6; i++)
//        printf("%d\n",Map.addInMap(&mymap,key[i],&value[i]));
//    Map.printMap(mymap);
//    char *tKey = "key1";
//    bool b/* = Map.containsKeyWithValue(mymap,key[2],&value[2])*/;
//    //b = Map.containsKeyWithValue(mymap,key[2],&value[3]);
////    b = Map.removeKeyFromMap(&mymap,key[3]);
////    b = Map.removeKeyFromMap(&mymap,tKey);
////    b = Map.removeKeyWithValueFromMap(&mymap,key[4],&value[5]);
////    b = Map.removeKeyWithValueFromMap(&mymap,key[4],&value[4]);
//
////    for (i = 0; i < 6; i++)
////        printf("%d\n",Map.deleteFromMap(&mymap,key[i]));
////    Map.printMap(mymap);
//    //Map.destroyMapObject(&mymap);
////    float f = 20.56748;
//    map_iterator iter;
//    b = Map.getIterator(&mymap,&iter);
//	while (b)
//	{
//        //memcpy(iter->data->key,&f,sizeof(float));
//		printf("Key is %s and Value is %f\n",STRINGAT(iter.data->key),FLOATAT(iter.data->value));
//		b = Map.nextIterator(&mymap,&iter);
//	}
//
//
//    Map.printMap(mymap);
//	/*b = Map.replaceValueOfKey(&mymap,&value[3],key[2],key[4]);
//	b = Map.replaceValueOfKey(&mymap,&value[3],key[3],key[4]);*/
//	b = Map.replaceOldValueOfKeyWithNewValue(&mymap,key[2],&value[3],&value[4]);
//	b = Map.replaceOldValueOfKeyWithNewValue(&mymap,key[3],&value[3],&value[4]);
//	FLOATAT(Map.getValue(mymap,key[3])) = 100302.4830;
//
//	Map.printMap(mymap);
//	return 0;
//}


extern const GLOBAL_STRING_OBJECT String;

int k_main(int argc, char *args[])
{
    string str = String.getString();
    puts(str);

    return 0;
}

//extern GLOBAL_SET_OBJECT Set;
//
//int main(int argc, char *args[])
//{
//	set intSet;
//    long message;
//    int myArr[] = {8, 12, 6, 10, 9, 11/*, 14, 16, 68, 35, 2, 4, 8, 90, 76, 2, 1, 4, 3, 5, 7, 10, 12, 9, 13, 11*/};
//
//    int size = sizeof(myArr) / sizeof(myArr[0]);
//    int z = 100;
//    int i = 0;
//    intSet = Set.getSet(DEFAULT_SET, NULL, NULL);
//    for (; i < size; i++)
//        Set.addInSet(&intSet, &myArr[i]);
//	Set.printSet(intSet);
//	Set.deleteFromSet(&intSet,&myArr[0]);
//	// Set.destroySetObject(&intSet);
//	set_iterator iter;
//	bool b = Set.getIterator(&intSet,&iter);
//	while (iter.data != NULL)
//    {
//        printf("%d\n",INTAT(iter.data));
//        b = Set.nextIterator(&intSet,&iter);
//    }
//	Set.printSet(intSet);
//	for (i = 0; i < size; i++)
//        Set.deleteFromSet(&intSet, &myArr[i]);
//	/*Set.destroySetObject(&intSet);
//	b = Set.getIterator(&intSet,&iter);
//	while (iter.data != NULL)
//    {
//        printf("%d\n",INTAT(iter.data));
//        b = Set.nextIterator(&intSet,&iter);
//    }*/
//	Set.printSet(intSet);
//	return 0;
//}
