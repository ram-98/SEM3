note
    description : "root class of the application"
    date        : "$Date$"
    revision    : "$Revision$"

class
    MAIN

inherit
    ARGUMENTS
    DOUBLE_MATH

create
    make
feature
    r: RECTANGLE
    
feature
    make    -- Run application.
        local
            i: INTEGER
            x: INTEGER
            y: DOUBLE
        do
            -- Add your code here
            create r.make
            print("Herld!%N")
            from
                i := 1
            until
                i =4
            loop
                print("%NEnter an  integer%N")
                print("Enter 1.Translate 2.Scaling 3.Rotate 4.Quit")
                Io.read_integer
                x:=Io.last_integer
                inspect x 
                when 1 then
                  print ("x is 1")
                  print("Enter translation in X axis")
                  Io.read_double
                  y:=Io.last_double
                 r.translate_x(y)
                  print("Enter translation in Y axis")
                  Io.read_double
                  y:=Io.last_double
                 r.translate_y(y)
                when 2 then
                    print ("x is 2")
                    print("Enter scaling factor")
                    Io.read_double
			        y:=Io.last_double
                    r.scaling(y)
                when 3 then
                    print ("x is 3")
                    print("Enter angle in degrees")
                    Io.read_double
                    y:=Io.last_double
                   r.rotate(y)
                when 4 then
                    print ("QUITTING x is 4")
                    i:=4
                else
                  print ("Invalid")
                end
                print ("%NResult :: (x1, y1), (x2, y2), (x3, y3), (x4, y4)")
               print ("%N("+r.x1.out+", "+r.y1.out+")")
                print ("%N("+r.x2.out+", "+r.y2.out+")")
                print ("%N("+r.x3.out+", "+r.y3.out+")")
                print ("%N("+r.x4.out+", "+r.y4.out+")")
                end
            print ("%NBYEBYE")
        end
    end
