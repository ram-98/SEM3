class
    HEAP

inherit
    ARGUMENTS
    DOUBLE_MATH
create
    make
feature
    my_array : ARRAY[INTEGER]
    left :INTEGER
    right : INTEGER
    iter : INTEGER
    index:INTEGER
    largest:INTEGER             ---take largest as smallest index
    swap:INTEGER
    i:INTEGER

feature 
   make 
      require
        TRUE
      local
         last_index : INTEGER 
         base_index : INTEGER 
         x: INTEGER
      do
         last_index:=15
         base_index :=1
         index:=0   
         create my_array.make(base_index,last_index)       
                ----creating an array from index number 1 to 15
         print("%NEnter the integers untill 0 to intial input %N")
         from 
            iter:=1
        until 
            iter=16
        loop
            print("%NEnter the integer %N")
            Io.read_integer
            x:=Io.last_integer
            if x=0 then
                iter:=15
            else
                my_array.put(x, iter)
                index:=index+1
            end
           iter:=iter+1
          end
         ------Code to build min heap
         --print("%N Building Min heap  %N")
        from
            i:=index//2
        until
            i=0
        loop
            left:=2*i
            right:=2*i+1
            if left<= index and my_array[left]< my_array[i] then
                largest:=left
            else
                largest:=i
            end
            if right<= index and my_array[right]< my_array[largest] then
                largest:=right
            end
            if largest /~ i then
                swap:=my_array[largest]
                my_array[largest]:=my_array[i]
                my_array[i]:=swap
                min_heapify(largest)
            end
            i:=i-1
        end
        ensure
            TRUE
      end
            ------- END of make 
            -------Display mehtod to print in sorted order
    display
        require
            TRUE
        do
            print("%N Printing in  ascending sorted order %N")
            from
                iter := 1
            until
                index=0
             loop
                print(retrieve.out+"  ")
                iter:=iter+1
             end
        ensure
            
         end
feature
    ------------------Min heapify at an index 'a'
    min_heapify(a:INTEGER)
        do
            left:=2*a
            right:=2*a+1
            if left<= index and my_array[left]< my_array[a] then
                largest:=left
            else
                largest:=a
            end
            if right<= index and my_array[right]< my_array[largest] then
                largest:=right
            end
            if largest /~ a then
                swap:=my_array[largest]
                my_array[largest]:=my_array[a]
                my_array[a]:=swap
                min_heapify(largest)
            end
         end
    ----------Insert an element 
    insert(b:INTEGER)
        
        require
            TRUE
        local
            check_insertion: INTEGER
        do 
            check_insertion:=my_array.occurrences(b)
            index:=index+1
             my_array.put(b, index)
            --print("%N Building Min heap  %N")
            from
                i:=index//2
            until
                i=0
            loop
                left:=2*i
                right:=2*i+1
                if left<= index and my_array[left]< my_array[i] then
                    largest:=left
                else
                    largest:=i
                end
                if right<= index and my_array[right]< my_array[largest] then
                    largest:=right
                end
                if largest /~ i then
                    swap:=my_array[largest]
                    my_array[largest]:=my_array[i]
                    my_array[i]:=swap
                    min_heapify(largest)
                end
                i:=i-1
            end 
            from
                iter:=1
            until
                iter=index+1
            loop
                print(my_array[iter].out+" ")
                iter:=iter+1
            end
            ensure
                1=findinarray(b)
        end
    -----------Retrieveing the top position
    retrieve:INTEGER
        require
            index>0
        do 
            Result:=my_array[1]
            my_array[1]:=my_array[index]
            index:=index-1
            from
                i:=index//2
            until
                i=0
            loop
                left:=2*i
                right:=2*i+1
                if left<= index and my_array[left]< my_array[i] then
                    largest:=left
                else
                    largest:=i
                end
                if right<= index and my_array[right]< my_array[largest] then
                    largest:=right
                end
                if largest /~ i then
                    swap:=my_array[largest]
                    my_array[largest]:=my_array[i]
                    my_array[i]:=swap
                    min_heapify(largest)
                end
                i:=i-1
            end 
            print(" Heap remaining is%N")
            from
                iter:=1
            until
                iter=index+1
            loop
                print(my_array[iter].out+" ")
                iter:=iter+1
            end
            ensure
                old my_array[1]=Result
        end
    findinarray(b:INTEGER):INTEGER
        do
            from
                iter := 1
            until
                iter=index+1
             loop
                if b=my_array[iter] then
                    Result:=1
                end
                iter:=iter+1
             end
        end
        
        invariant
            index<=15
            
end
