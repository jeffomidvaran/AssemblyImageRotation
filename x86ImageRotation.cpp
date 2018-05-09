

#define RANDOMIZE_CALLEE_REGISTERS __asm mov ebx, 0xAFAFAFAF \
                                   __asm mov esi, 0xAFAFAFAF \
                                   __asm mov edi, 0xAFAFAFAF 
#define RANDOMIZE_CALLER_REGISTERS __asm mov eax, 0xAFAFAFAF \
                                   __asm mov ecx, 0xAFAFAFAF \
                                   __asm mov edx, 0xAFAFAFAF


void imageRotation(unsigned int* image, int dim, int n) {


    unsigned int a0, a90, a180, a270;

    __asm 
    {
        // YOUR CODE STARTS HERE
		/*
		n = number of times it rotates
		d = width/height
		original =(r,c)
		new = (c, dim-1-r)
		*/
		
		//Start of n loop
		mov ebx, 0 // n loop counter
		StartOfNLoop:
		cmp ebx, n
		jge EndOfNLoop
			push ebx  // save n loop counter on the stack
			
			mov ecx, 0   // ecx = start
			mov edx, dim // edx = end
			sub edx, 2


			mov eax, dim  // rows that will be traversed through (dim div 2)-1
			shr eax, 1
			sub eax,1 

			
			
			// Start while loop
			mov ebx, 0 // ebx = counter for while loop
			StartofRowLoop:
			cmp ebx, eax  // rcounter = ebx , row2i = eax 
			jg EndofRowLoop
				
				push ebx // save row loop counter
				push ecx // save start value
				push edx // save end value
				

				//start range loop
				StartOfColumnLoop:
				cmp ecx, edx // ecx=start ecx=column			 
				jg EndOfColumnLoop
					
					push ebx // store the row held through column loop
					push ecx // save column loop counter 
					push edx // save colum loop max 
					
					mov esi, ebx // esi = r
					mov edi, ecx // edi = c 

					// get index (r*dim + c)
					mov eax, dim
					mul esi
					add eax, edi 

					// put value at index into a0
					mov ebx, image
					mov ecx, [ebx+eax*4] // !!!! ERROR HERE!!!!!!
					mov a0, ecx

					//change r,c
					// (r,c) -> (c, dim-1-r)
					mov ebx, dim // dim-1
					dec ebx
					mov eax, esi // save r
					sub ebx, eax // dim-1-r

					mov esi, edi // c to r  should be 0 
					mov edi, ebx // dim-1-c to c should be 2

					// get index (r*dim + c)
					mov eax, dim
					mul esi
					add eax, edi // eax = index offset

					// put array[index] in a90
					mov ebx, image
					mov ecx, [ebx+eax*4]
					mov a90, ecx

					// put a0 into array[index] 
					mov ecx, a0
					mov [ebx+eax*4], ecx

					
					//change r,c
					// (r,c) -> (c, dim-1-r)
					mov ebx, dim // dim-1
					dec ebx
					mov eax, esi // save r
					sub ebx, eax // dim-1-r

					mov esi, edi // c to r  should be 2 
					mov edi, ebx // dim-1-c to c should be 2

					// get index (r*dim + c)
					mov eax, dim
					mul esi
					add eax, edi // eax = index offset

					// put array index into a180
					mov ebx, image
					mov ecx, [ebx + eax * 4]
					mov a180, ecx

					// put a90 into array[index]
					mov ecx, a90
					mov[ebx + eax * 4], ecx

					
					//change r,c
					// (r,c) -> (c, dim-1-r)
					mov ebx, dim // dim-1
					dec ebx
					mov eax, esi // save r
					sub ebx, eax // dim-1-r

					mov esi, edi // c to r  should be 2 
					mov edi, ebx // dim-1-c to c should be 0

					// get index (r*dim + c)
					mov eax, dim
					mul esi
					add eax, edi // eax = index offset

					// put array index into a270
					mov ebx, image
					mov ecx, [ebx + eax * 4]
					mov a270, ecx

					// put a180 into array[index]
					mov ecx, a180
					mov[ebx + eax * 4], ecx

					//change r,c
					// (r,c) -> (c, dim-1-r)
					mov ebx, dim // dim-1
					dec ebx
					mov eax, esi // save r
					sub ebx, eax // dim-1-r

					mov esi, edi // c to r  should be 0 
					mov edi, ebx // dim-1-c to c should be 0

					// get index (r*dim + c)
					mov eax, dim
					mul esi
					add eax, edi // eax = index offset

					// put a270 into array[index]
					mov ebx, image
					mov ecx, a270
					mov[ebx + eax * 4], ecx

					pop edx // restore column loop max
					pop ecx // restore column loop counter 
					pop ebx // restore the row held through the column loop
					inc ecx
				jmp StartOfColumnLoop
				EndOfColumnLoop:
				

				pop edx // restore end value
				pop ecx // restore start value
				pop ebx // restore row loop counter

				inc ecx // start+1
				dec edx // end-1

				
				inc ebx // 
			jmp StartofRowLoop
			EndofRowLoop:


			pop ebx // get rid of values in ebx and restore the n loop counter
		inc ebx  // ebx = n loop counter
		jmp StartOfNLoop
		EndOfNLoop:
		
        // YOUR CODE ENDS HERE
    }
}

