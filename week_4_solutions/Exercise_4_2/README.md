Solutions to Exercise 4.2  

p[-1] : this would be outside of the memory/boundary assigned to the array, and gives undefined behaviour.
It points to an address before the array, assigning it a random value

p: is the array. With indexing, the values of the array can be printed. When p is printed alone, as no value 
is assigned, it prints some random value. When p is printed as a pointer, it gives back the address.
But p is not the address.

*p : is a pointer and as a standalone, points to the first value of the array

&p : is basically a pointer to the address of the array p. When this is 
assigned a value, eg *address = &p, the address is stored.

*(p+1) : is a pointer to the second value of the array. 
It points to the address p (which is the first value of p) and adds one to the address.
Due to the storage in the memory, arrays are stored continuously, adding one goes to the 
next element in the array.

*p + 1 : *p points to the first value of the array. It takes that value and adds 1

*q = p-1 : pointer q points to the int in memory that is at -1st position of the array p.
This isn't further defined, and is just some random value

q[0] : As q is not further defined, as it is outside of the boundaries
of p, the first value is assigned a random value

*(q+10) : is a pointer, it starts by pointing at the address of the first value in q,
which has no assigned value. It then adds 10 to that address, in the sense that it goes
10 values further. As *q is pointing to the -1st position of p, *(q+10) points to the 10th
value of p, which has a value assigned  

*(q+11) :  is a pointer, points to the 11th int in memory. As pointer *q is based on p,
it is a place in memory outside of the array, and it is 0.

M : M in the end is an int. The definition via **M makes this a pointer to a pointer to an int.

*M : points to an array of pointers.

**M : points to an array of pointers which in turn point to values in an array

M[1][3] : Is the value of the second (C++ is zero based) array, the fourth value

*(M[0] + 1) : points to the index of the first array + one, so to the second array

*(*(M+1)+3) : points to the second array of pointers, from where it points to the fourth value

The arrays are not stored next to each other in memory. (at least according to the print statement executed)

