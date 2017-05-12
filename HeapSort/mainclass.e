note
    description : "root class of the application"
    date        : "$Date$"
    revision    : "$Revision$"

class
    APPLICATION

inherit
    ARGUMENTS
    DOUBLE_MATH

create
    make
feature
    h: HEAP
    
feature
    make    -- Run application.
        local
            i: INTEGER
            x: INTEGER
           -- y: DOUBLE
        do
            -- Add your code here
            
            create h.make
            from
                i := 1
            until
                i =4
            loop
                print("%NEnter an  integer%N")
                print("Enter 1.Insert 2.Retrieve 3.Print and Quit")
                Io.read_integer
                x:=Io.last_integer
                inspect x 
                when 1 then

                  print ("ENTER AN INTEGER TO INSERT")
                  Io.read_integer
                  x:=Io.last_integer
                  h.insert(x)
                  
                when 2 then
                   
                    x:=h.retrieve
                     print ("THE RETRIEVING(TOP -MINIMUM) VALUE IS----- ")
                    print(x.out)
                when 3 then
                    
                    h.display
                    i:=4
                else
                  print ("Invalid")
                end
            end
        end
    end
